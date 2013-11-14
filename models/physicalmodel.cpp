#include "../Header.h"

double property::Current(const double temperature) const
{
    if(!tempDependent) return offset;

    double
    currT = temperature;
    currT *= slope;
    currT += offset;

    return currT;
//        return offset + slope * temperature;
}

double property::Projected(const double temperature1, const double temperature2)
const
{
    if(!tempDependent) return offset;

    double
    projT = temperature1;
    projT -= temperature2;
    projT *= slope;
    projT += Current(temperature1) ;

    return projT;
//        return Current(temperature1) + slope * (temperature1 - temperature2);
}

double property::Current(const std::vector<std::vector<double>>& T, const size_t n,
               const size_t j) const
{
    if(!tempDependent) return offset;

    return offset + slope * T[n][j];
}

double property::Current(const std::vector<std::vector<double>>& T, const size_t n,
               const size_t j1, const size_t j2) const
{
    if(!tempDependent) return offset;

    return mean( Current( T[n][j1] ) , Current( T[n][j2] ) );
}


double property::Current(const class Temperature Tprofile, const size_t n,
               const size_t j) const
{
    if(!tempDependent) return offset;

    return offset + slope * Tprofile.eval(n,j);
}

double property::Current(const class Temperature Tprofile, const size_t n,
               const size_t j1, const size_t j2) const
{
    if(!tempDependent) return offset;

    return mean( Current( Tprofile.eval(n, j1 ) ) ,
                 Current( Tprofile.eval(n,j2  ) ) );
}


double property::Projected(const std::vector<std::vector<double>>& T,
                           const size_t n, const size_t j) const
{
    if(!tempDependent) return offset;

    if( n == 0 ) return Current( T[n][j] );


    return Current(T[n][j]) + slope * (T[n][j] - T[n-1][j]);
}

double property::Projected(const std::vector<std::vector<double>>& T, const size_t n,
                 const size_t j1, const size_t j2)
const
{
    if(!tempDependent) return offset;
    if( n == 0 )
    {
        return mean( Current(  T[n][j1] ) , Current( T[n][j2] ) );
    }

    return mean( Projected(T, n, j1), Projected(T, n, j2) );
}

double property::Projectedt(const std::vector<std::vector<double>>& T,
                            const size_t n,const size_t /*n1*/, const size_t j)
const
{
    if(!tempDependent) return offset;

    return mean( Current(T, n, j) ,  Projected(T, n, j));
}

double property::Projected(const class Temperature Tprofile,
                           const size_t n, const size_t j) const
{
    if(!tempDependent) return offset;

    if( n == 0 ) return Current( Tprofile.eval(n,j) );


    return Current(Tprofile.eval(n,j)) + slope * (Tprofile.eval(n,j) -
                                        Tprofile.eval(n-1,j));
}

double property::Projected(const class Temperature Tprofile, const size_t n,
                 const size_t j1, const size_t j2)
const
{
    if(!tempDependent) return offset;
    if( n == 0 )
    {
        return mean( Current(  Tprofile.eval(n,j1) ) ,
                    Current( Tprofile.eval(n,j2) ) );
    }

    return mean( Projected(Tprofile, n, j1), Projected(Tprofile, n, j2) );
}

double property::Projectedt(const class Temperature Tprofile,
                            const size_t n,const size_t /*n1*/, const size_t j)
const
{
    if(!tempDependent) return offset;

    return mean( Current(Tprofile, n, j) ,  Projected(Tprofile, n, j));
}

property::property(double offset_, double slope_)
    : offset(offset_), slope(slope_)
{}

property::property(void){}





namespace physicalModel
{
temperatureScale::temperatureScale(const double tolerance_,
                                   const double referance_,
                                   const double base_, const double rear_):
    tolerance(tolerance_), referance(referance_), base(base_), rear(rear_)
{}

radiativeSysProp::radiativeSysProp(double R0_, double R1_, double Emit1_)
    : R0(R0_), R1(R1_), Emit1(Emit1_)
{}

layer::layer(struct property kthermal_, struct property psithermal_,
             double depth_, double lambda_)
    : kthermal(kthermal_), psithermal(psithermal_), depth(depth_),
      lambda(lambda_)
{}

double layer::opticalPenetration(void)
{
    return lambda*depth;
}

double layer::thermalDiffusivity(void)
{
    return thermal::effusivity(kthermal.offset, psithermal.offset);
}
double layer::thermalEffusivity(void)
{
    return thermal::effusivity(kthermal.offset, psithermal.offset);
}




TBCsystem::TBCsystem(struct layer coating_, struct layer substrate_,
                     struct temperatureScale Temp_,
                     struct radiativeSysProp optical_,
                     double radius_)
    : coating(coating_), substrate(substrate_), Temp(Temp_), optical(optical_),
      radius(radius_)
{}

double TBCsystem::gamma(void)
{
    return 0;
}
double TBCsystem::epsilon(void)
{
    return 0;
}
double TBCsystem::a_coat(void)
{
    return 0;
}
double TBCsystem::a_sub(void)
{
    return 0;
}



labels::labels(const Name name_):name(name_){}

enum labels::Name labels::getName(void)
{
  return name;
}



}