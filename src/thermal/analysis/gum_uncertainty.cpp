//
//  gum_uncertainty.cpp
//  tat
//
//  Created by Raymond Valdes on 9/10/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//
#include <algorithm>
#include <memory>
#include <iostream>
#include "thermal/analysis/gum_uncertainty.h"
#include "thermal/emission/phase99.hpp"
#include "algorithm/vector/subtract.h"
#include "algorithm/vector/stdVector2ublasVector.h"
#include "math/numericalAnalysis/differentiation/firstDerivative/central_difference.h"
#include "math/numericalAnalysis/matrixs/inversion.h"
#include "math/numericalAnalysis/ublas/apply_to_all.h"

using std::pair;
using std::make_pair;
using std::vector;
using std::make_shared;
using std::shared_ptr;
using math::estimation::unknownList;

using algorithm::vector::subtract;
using algorithm::vector::stdVector2ublasVector;
using thermal::emission::phase99Pertrub;
using math::numericalAnalysis::differentiation::firstDerivative::centralDifference;
using math::numericalAnalysis::differentiation::firstDerivative::central_difference_partial;
using boost::numeric::ublas::sum;
using boost::numeric::ublas::element_prod;
typedef vector<double> vectorData;

typedef boost::numeric::ublas::zero_vector<double> uZero_Vector;
typedef boost::numeric::ublas::unit_vector<double> uUnit_Vector;
typedef boost::numeric::ublas::matrix<double> uMatrix;
using boost::numeric::ublas::prod ;
typedef const enum thermal::model::labels::Name label;
typedef vector< enum thermal::model::labels::Name > EnumList ;
typedef const vector< pair < enum thermal::model::labels::Name, double > > List;

typedef boost::numeric::ublas::vector<double> uVector;
typedef const uVector cuVector;


namespace thermal {
namespace analysis {

Taylor_uncertainty::Taylor_uncertainty( void ) noexcept{}

Taylor_uncertainty::~Taylor_uncertainty( ) noexcept {}

void Taylor_uncertainty::solve(
         const std::shared_ptr< math::estimation::unknownList > &list_in,
         const std::shared_ptr< ThermalData > &thermalData_in,
         const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept {
  ///use the inputs
  assignPointer( list_in , thermalData_in , coreSystem_in ) ;
  
  N_unknowns = unknownParameters->size() ;
  N_parameters = thermal::model::labels::numberOfLabels() ;
  N_knowns = N_parameters - N_unknowns ;
  N_dataPoints = thermalData->size();

  const uVector output = sDerivativeVector();
  for( const auto& val : output )
    std::cout << val << "\n";
}

void Taylor_uncertainty::saveModel() noexcept {
  SavedState.updateObjects( *coreSystem, *thermalData, *unknownParameters ) ;
}

void Taylor_uncertainty::resetModel() noexcept {
  updateObjects( *SavedState.coreSystem,
                 *SavedState.thermalData,
                 *SavedState.unknownParameters) ;
}

void Taylor_uncertainty::modifyModel( label derive,
                                      const double val,
                                      const size_t ith ) noexcept
{
  List listmodifiers = { make_pair( derive, val ) } ;
  
  const pair< shared_ptr< Kernal >, vector<double> > perturbedVales =
  coreSystem->updateCoreOmegaFromList( thermalData->omegas, listmodifiers, ith ) ;
  
  const auto popteaPerturb = perturbedVales.first;
  const auto omegasPertrubed = perturbedVales.second;
  
  thermalData->omegas = omegasPertrubed;
  updateObjects( *popteaPerturb, *thermalData, *unknownParameters) ;
}

uVector Taylor_uncertainty::uncertaintyResults( void ) noexcept{

  using model::labels::Name::experimentalData;
  using model::labels::Name::omega;

  const size_t N = N_unknowns ;
  const size_t M = 2 * N_dataPoints + ( N - 2 ) ;
  const uVector uncertaintyVector( M );

  const EnumList myKnownList = get_list_knowns();

  const auto eval = [&]( const model::labels::Name label, const size_t i )
  {
    const uUnit_Vector unitVector( M, i ) ;
  
    const uVector unitUncertainty = element_prod( uncertaintyVector,  unitVector ) ;
    const uMatrix dJ= Djacobian( label , i ) ;
  
    uVector output = prod( dJ, unitUncertainty ) ;
    return output = element_prod( output, output ) ;
  };
  
  uVector output( N ) ;
  
  for( size_t i = 0 ; i < N_dataPoints ; ++i ) {
    output += eval(experimentalData, i) ;
  }
    
  for( size_t i = 0 ; i < N_dataPoints ; ++i ) {
    output += eval( omega , i ) ;
  }
    
  for( size_t i = 0 ; i < N_knowns ; ++i ) {
    output += eval( myKnownList[i] , N_dataPoints ) ;
  }
  
  using math::numericalAnalysis::ublas::apply_to_all;
  using math::numericalAnalysis::ublas::functor::sqrt;
  
  return apply_to_all< sqrt<double> > ( output );
}

uMatrix Taylor_uncertainty::Djacobian( label derive, const size_t ith ) noexcept {

  ///Basically I need to be able to get the derivative of the jacobian
  ///with respect to the label.
  
  saveModel();
  
  modifyModel( derive, fullVal + dh , ith ) ;
  uMatrix modelplus = jacobian();
  resetModel();

  modifyModel( derive, fullVal - dh , ith ) ;
  uMatrix modelmins = jacobian();
  resetModel();
  
  const uMatrix DerivativeModel = centralDifference( modelplus, modelmins, dh );
  return DerivativeModel;
}

uMatrix Taylor_uncertainty::jacobian( void ) noexcept {
  using math::numericalAnalysis::matrix::InvertMatrix ;

  const uMatrix Jy = jacobianY() ;
  const uMatrix Jx = jacobianX() ;
  const uMatrix invJy = InvertMatrix( Jy ) ;
  
  const uMatrix J = -prod( invJy, Jx ) ;
  return J ;
}

double Taylor_uncertainty::sDerivative( label derive, const size_t ith ) noexcept
{
  cuVector model = stdVector2ublasVector( thermalData->predictedEmission ) ;
  cuVector exper = stdVector2ublasVector( thermalData->experimentalEmission ) ;

  cuVector DerivativeModel = first_D_model( derive, ith ) ;
  cuVector DerivativeSpreSum = 2 * element_prod( DerivativeModel, model - exper ) ;
  
  return sum( DerivativeSpreSum ) ;
}

uVector Taylor_uncertainty::sDerivativeVector( void ) noexcept
{
  uVector output( N_unknowns ) ;

  size_t i = 0 ;
  for( auto& val: unknownParameters->vectorUnknowns )
      output[i++] = sDerivative( val.label() , N_dataPoints )  ;
  
  return output;
}


uMatrix Taylor_uncertainty::jacobianY( void ) noexcept
{
  const EnumList myList = get_list_knowns() ;
  
  uMatrix output( N_unknowns , N_unknowns ) ;
  for  ( size_t i = 0 ; i < N_unknowns ; ++i ) {
    for( size_t j = 0 ; j < N_unknowns ; ++j )
      output( i , j ) = derivative_M( myList[i], myList[j] , N_dataPoints ) ;
  }
  
  return output;
}

vector< enum thermal::model::labels::Name >
Taylor_uncertainty::get_list_knowns( void ) noexcept
{
  using std::sort;
  const thermal::model::labels myLabel;

  const EnumList myParameterList = myLabel.getEnumList();
  const EnumList listunknowns = unknownParameters->get_enum_list() ;

  const size_t sizeOfKnowns = myParameterList.size() - listunknowns.size() ;
  EnumList listKnowns;
  
  for( const auto& parameter : myParameterList) {
    bool trackParameter = true;
    for( const auto& unknown: listunknowns ) {
      if( parameter == unknown )
        trackParameter = false;
    }
    if( trackParameter == true )
      listKnowns.push_back(parameter) ;
  }
  
  
  assert( listKnowns.size() == sizeOfKnowns ) ;
  
  return listunknowns;
}

uMatrix Taylor_uncertainty::jacobianX( void ) noexcept
{
  using model::labels::Name::experimentalData;
  using model::labels::Name::omega;

  const size_t N = N_unknowns ;
  const size_t M = 2 * N_dataPoints + ( N_knowns - 2 ) ;
  
  const EnumList myList = unknownParameters->get_enum_list() ;
  const EnumList myKnownList = get_list_knowns();
  
  uMatrix output( N , M ) ;
  for( size_t i = 0 ; i < N ; ++i ) {
  
    for( size_t j = 0 ; j < N_dataPoints ; ++j ) {
      output( i , j ) = derivative_M( myList[i],
                                      experimentalData ,
                                      j ) ;
    }
    
    for( size_t j = N_dataPoints ; j < 2 * N_dataPoints ; ++j ) {
      output( i , j ) = derivative_M( myList[i],
                                      omega ,
                                      j - N_dataPoints ) ;
    }
    
    for( size_t j = 2 * N_dataPoints ; j < M ; ++j ) {
      output( i , j ) = derivative_M( myList[i],
                                      myKnownList[j - 2 * N_dataPoints] ,
                                      N_dataPoints ) ;
    }
  }
  
  return output;
}


double Taylor_uncertainty::derivative_M(
  const label d_first ,
  const label d_second,
  const size_t ith ) noexcept
{
  cuVector model = stdVector2ublasVector( thermalData->predictedEmission ) ;
  cuVector exper = stdVector2ublasVector( thermalData->experimentalEmission ) ;
  
  cuVector dSd1 = first_D_model( d_first, ith ) ;
  cuVector dSd2 = first_D_model( d_second, ith ) ;
  cuVector ddSd1d2 = second_D_model( d_first, d_second, ith ) ;

  const uZero_Vector myZeroVector( N_dataPoints ) ;
  uVector dXd2 = myZeroVector ;
  if( ith < N_dataPoints )
    dXd2 = derivativeCi( N_dataPoints, ith ) ;

  
  cuVector output = 2 * (
       element_prod( dSd1,  dXd2 - dSd2 )               // DOUBLE CHECK
    +  element_prod( ddSd1d2 , exper - model ) );       // DOUBLE CHECK

  return sum( output ) ;
}

uVector Taylor_uncertainty::evalModel( List list, const size_t ith ) noexcept {
  return stdVector2ublasVector( phase99Pertrub( *coreSystem,
                                                thermalData->omegas,
                                                list, ith ) ) ;
}

uVector Taylor_uncertainty::first_D_model( label derive , const size_t ith ) noexcept {
  using model::labels::Name::experimentalData;
  const uZero_Vector myZeroVector( N_dataPoints ) ;

  const bool modelParametersOnly = derive != experimentalData;
  uVector DerivativeModel = myZeroVector ;
  
  if( modelParametersOnly )
  {
    const double fullValue = 1 ;
    List listplus  = { make_pair( derive, fullValue + dh ) } ;
    List listminus = { make_pair( derive, fullValue - dh ) } ;
    
    cuVector modelplus = evalModel( listplus, ith ) ;
    cuVector modelmins = evalModel( listminus, ith ) ;
    
    DerivativeModel =
    centralDifference( modelplus, modelmins, dh ) ;
  }
  
  return DerivativeModel;
}

uVector Taylor_uncertainty::second_D_model( label d_first , label d_second,
                                            const size_t ith ) noexcept
{
  const auto listMaker = [&]( const bool mod1, const bool mod2 )
  {
    const int modifier1 = mod1 ? 1 : -1 ;
    const int modifier2 = mod2 ? 1 : -1 ;
    List list_xx = {  make_pair( d_first, fullVal + (modifier1 * dh) ),
                      make_pair( d_second, fullVal + (modifier2 * dh ) ) };
    return list_xx;
  };
  
  List list_pp = listMaker( true, true ) ;
  List list_pm = listMaker( true, false ) ;
  List list_mp = listMaker( false, true ) ;
  List list_mm = listMaker( false, false ) ;
  
  cuVector model_pp = evalModel( list_pp, ith ) ;
  cuVector model_pm = evalModel( list_pm, ith ) ;
  cuVector model_mp = evalModel( list_mp, ith ) ;
  cuVector model_mm = evalModel( list_mm, ith ) ;

  return central_difference_partial( model_pp, model_pm, model_mp, model_mm,dh);
}

uUnit_Vector Taylor_uncertainty::derivativeCi( const size_t maxSize,
  const size_t ith) noexcept
{
  const uUnit_Vector output( maxSize, ith) ;
  return output;
}





}}
