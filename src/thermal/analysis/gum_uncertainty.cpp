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

  std::cout << sDerivative( model::labels::Name::asub )  <<"\n" ;
  std::cout << sDerivative( model::labels::Name::gammaEff )  <<"\n" ;
  std::cout << sDerivative( model::labels::Name::lambda )  <<"\n" ;
  std::cout << sDerivative( model::labels::Name::E1 )  <<"\n" ;
}

void Taylor_uncertainty::experimentalData( void ) {
}

void Taylor_uncertainty::modelData( void ) {
}

void Taylor_uncertainty::modelDataDerivative( void ) {
}

double Taylor_uncertainty::sDerivative( enum model::labels::Name derive ) {

  typedef std::vector<double> vectorData;
  typedef boost::numeric::ublas::vector<double> uVector;
  using boost::numeric::ublas::element_prod;
  using algorithm::vector::stdVector2ublasVector;


  uVector model = stdVector2ublasVector( thermalData->predictedEmission );
  uVector exper = stdVector2ublasVector(thermalData->experimentalEmission);


  const double dh = 0.00001;
  const double dhx2 = dh * 2 ;
  const double fullValue = 1;
  vector< pair< enum model::labels::Name, double > >
    listplus= { make_pair( derive, fullValue + dh ) } ;
  vector< pair< enum model::labels::Name, double > >
    listminus= { make_pair( derive, fullValue - dh ) } ;
  
  vectorData omegas = thermalData->omegas;
  uVector modelplus = stdVector2ublasVector( emission::phase99Pertrub( *coreSystem, omegas,listplus) );
  uVector modelmins = stdVector2ublasVector( emission::phase99Pertrub( *coreSystem, omegas,listminus) );

  uVector DerivativeModel = ( modelplus - modelmins ) / ( dhx2 ) ;
  uVector DerivativeSpreSum = 2 * element_prod( DerivativeModel, model - exper);
  
  const double output = boost::numeric::ublas::sum( DerivativeSpreSum ) ;
  
  
  return output;
}

 
  
  
  
  
}}