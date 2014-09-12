//
//  gum_uncertainty.cpp
//  tat
//
//  Created by Raymond Valdes on 9/10/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "thermal/analysis/gum_uncertainty.h"
#include "thermal/emission/phase99.hpp"
#include "algorithm/vector/subtract.h"
#include "algorithm/vector/stdVector2ublasVector.h"

using std::pair;
using std::make_pair;
using std::vector;
using algorithm::vector::subtract;
using algorithm::vector::stdVector2ublasVector;

typedef boost::numeric::ublas::vector<double> uVector;
typedef std::vector<double> vectorData;
typedef boost::numeric::ublas::matrix<double> uMatrix;

namespace thermal {
namespace analysis {

Taylor_uncertainty::Taylor_uncertainty( void ) {}
Taylor_uncertainty::~Taylor_uncertainty( ){}

void Taylor_uncertainty::solve(
         const std::shared_ptr< math::estimation::unknownList > &list_in,
         const std::shared_ptr< ThermalData > &thermalData_in,
         const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in){
  ///use the inputs
  unknownParameters = list_in ;
  thermalData = thermalData_in ;
  coreSystem = coreSystem_in ;
  
  uVector output = sDerivativeVector();
  for( auto& val: output )
    std::cout << val << "\n";
  
}

void Taylor_uncertainty::experimentalData( void ) {
}

void Taylor_uncertainty::modelData( void ) {
}

void Taylor_uncertainty::modelDataDerivative( void ) {
}

boost::numeric::ublas::vector<double>
Taylor_uncertainty::sDerivativeVector( void )
{
  uVector output( unknownParameters->size() ) ;
  
  size_t i = 0 ;
  for( auto& val: unknownParameters->vectorUnknowns)
      output[i++] = sDerivative( val.label() )  ;
  
  return output;
}

uVector Taylor_uncertainty::first_D_model( enum model::labels::Name derive ,
                                           const double dh )
{
  const double dhx2 = dh * 2 ;
  const double fullValue = 1 ;
  
  vector< pair< enum model::labels::Name, double > >
    listplus= { make_pair( derive, fullValue + dh ) } ;
  vector< pair< enum model::labels::Name, double > >
    listminus= { make_pair( derive, fullValue - dh ) } ;
  
  const vectorData omegas = thermalData->omegas ;
  const uVector modelplus =
    stdVector2ublasVector( emission::phase99Pertrub( *coreSystem, omegas, listplus ) ) ;
  const uVector modelmins =
    stdVector2ublasVector( emission::phase99Pertrub( *coreSystem, omegas, listminus ) ) ;
  
  uVector DerivativeModel = ( modelplus - modelmins ) / ( dhx2 ) ;

  return DerivativeModel;
}


uVector Taylor_uncertainty::second_D_model(
  enum model::labels::Name d_first , enum model::labels::Name d_second,
  const double dh )
{
  const double fV = 1;
  const vectorData omegas = thermalData->omegas ;
  typedef const vector< pair< enum model::labels::Name, double > > List;
  using emission::phase99Pertrub;

  const auto eval = [&]( List list )
  {
    return stdVector2ublasVector( phase99Pertrub( *coreSystem, omegas, list ) );
  };

  List list_pp = { make_pair( d_first, fV + dh),make_pair( d_second, fV + dh )};
  List list_pm = { make_pair( d_first, fV + dh),make_pair( d_second, fV - dh )};
  List list_mp = { make_pair( d_first, fV - dh),make_pair( d_second, fV + dh )};
  List list_mm = { make_pair( d_first, fV - dh),make_pair( d_second, fV - dh )};

  const uVector model_pp = eval( list_pp ) ;
  const uVector model_pm = eval( list_pm ) ;
  const uVector model_mp = eval( list_mp ) ;
  const uVector model_mm = eval( list_mm ) ;

  const
  uVector diMi = model_pp - model_pm - model_mp + model_mm / ( 4 * dh * dh ) ;

  return diMi ;
}

double Taylor_uncertainty::derivative_M(
  enum model::labels::Name d_first , enum model::labels::Name d_second,
  const double dh )
{
  using boost::numeric::ublas::sum;
  using boost::numeric::ublas::element_prod;

  
  const uVector model = stdVector2ublasVector( thermalData->predictedEmission ) ;
  const uVector exper = stdVector2ublasVector( thermalData->experimentalEmission) ;
  
  const uVector first_DModel = first_D_model( d_first, dh ) ;
  const uVector second_DModel = first_D_model( d_second, dh ) ;
  const uVector second_D_Model = second_D_model( d_first, d_second, dh ) ;
  
  const uVector derivative_M_i =
    2 * element_prod( second_D_Model, model - exper  )
  + 2 * element_prod( first_DModel, second_DModel ) ;

  const double output = sum( derivative_M_i ) ;
  return output;
}


uMatrix Taylor_uncertainty::jacobianY( void )
{
  const size_t N = unknownParameters->size();
  const double dh = 1e-10;
  
  typedef const std::vector< enum model::labels::Name > EnumList ;
  EnumList myEnumList = unknownParameters->get_enum_list() ;
  
  uMatrix output( N , N ) ;
  
  for( size_t i = 0 ; i < N ; ++i )
    for( size_t j= 0; j < N ; ++j )
      output( i , j ) = derivative_M( myEnumList[i], myEnumList[j] , dh) ;
 
  return output;
}


double Taylor_uncertainty::sDerivative( enum model::labels::Name derive )
{
  using boost::numeric::ublas::element_prod;
  const double dh = 1e-10;

  const uVector model = stdVector2ublasVector( thermalData->predictedEmission ) ;
  const uVector exper = stdVector2ublasVector( thermalData->experimentalEmission) ;

  const uVector DerivativeModel = first_D_model( derive, dh ) ;
  const uVector DerivativeSpreSum = 2 * element_prod( DerivativeModel, model - exper);
  
  const double output = boost::numeric::ublas::sum( DerivativeSpreSum ) ;

  
  return output;
}

}}