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

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

using std::pair;
using std::make_pair;
using std::vector;
using algorithm::vector::subtract;
typedef boost::numeric::ublas::vector<double> uVector;

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

double Taylor_uncertainty::first_Derivative( enum model::labels::Name derive ) {

  return 0;
}

double Taylor_uncertainty::sDerivative( enum model::labels::Name derive )
{
  typedef std::vector<double> vectorData;
  using boost::numeric::ublas::element_prod;
  using algorithm::vector::stdVector2ublasVector;


  uVector model = stdVector2ublasVector( thermalData->predictedEmission ) ;
  uVector exper = stdVector2ublasVector( thermalData->experimentalEmission) ;

  const double dh = 1e-10;
  const double dhx2 = dh * 2 ;
  const double fullValue = 1;
  vector< pair< enum model::labels::Name, double > >
    listplus= { make_pair( derive, fullValue + dh ) } ;
  vector< pair< enum model::labels::Name, double > >
    listminus= { make_pair( derive, fullValue - dh ) } ;
  
  vectorData omegas = thermalData->omegas;
  uVector modelplus = stdVector2ublasVector(
                      emission::phase99Pertrub( *coreSystem, omegas, listplus));
  uVector modelmins = stdVector2ublasVector(
                      emission::phase99Pertrub( *coreSystem, omegas,listminus));

  uVector DerivativeModel = ( modelplus - modelmins ) / ( dhx2 ) ;
  uVector DerivativeSpreSum = 2 * element_prod( DerivativeModel, model - exper);
  
  const double output = boost::numeric::ublas::sum( DerivativeSpreSum ) ;

  
  return output;
}

}}