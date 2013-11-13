#include "../Header.h"

namespace expEquipment{

Detector::Detector(const double wavelength_, const double radius_)
    :wavelength(wavelength_), radius(radius_)
{}

Laser::Laser(const double a, const double b, const double c, const double d):
             offset(c), amplitude(d), Qlaser(a), radius(b)
{
    update();
}

void Laser::update(void)
{
    Is = IntensitySteady();
    It = IntensityTransient();
}

void Laser::updateRadius(const double r)
{
    radius = r;
    update();
}

void Laser::updatePower(const double Qpower)
{
    Qlaser = Qpower;
    update();
}

double Laser::area(void) const
{
    return M_PI_2 * radius * radius;
}

double Laser::IntensityTotal(void) const
{
    return Qlaser / area();
}

double Laser::IntensitySteady(void) const
{
    return IntensityTotal() * offset;
}

double Laser::IntensityTransient(void) const
{
    return IntensitySteady() * amplitude;
}

void Laser::updateNMeasurements()
{
    if(l_thermal)
    {
        delete [] l_thermal;
        delete [] omegas;
    }

    omegas      = new double[L_end];
    l_thermal   = new double[L_end];
}

double Laser::thermalSetup(const double lmin_, const double lmax_,
                           const double L_coat, const double kc,
                           const double psic, const double L_end_)
{
    l_min = lmin_;
    l_max = lmax_;
    /* I need to create a function that determines the number of measurements
    necessary to satisfy L_end_ which is the minimum  number of measurements per
    decade. Once I determine the number of measurements I need then I can use
    the ::rangelog10 function to populate the range.*/

    constexpr size_t box = 7;
    const double rangeLim[box] = {1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3};

    /*check to verify inputs*/
    if(l_min < rangeLim[0] || l_max > rangeLim[box-1])
    {
        std::cout << "error in Laser::thermalSetup" << "\n";
        exit(-1);
    }

    double rangeFills[box-1] = {0};
    for(size_t i = 0; i < box-1 ; ++i)
    {
        if( l_min >= rangeLim[i+1]  || l_max <= rangeLim[i])
        {
            rangeFills[i] = 0;
        }
        else if( l_min <= rangeLim[i] && l_max >= rangeLim[i+1])
        {
            rangeFills[i] = 1;
        }
        else
        {
            double start = 0;
            if(l_min <= rangeLim[i])
            {
                start = 0;
            }
            else if( l_min < rangeLim[i+1] )
            {
                start = ::percentilelog10(rangeLim[i], rangeLim[i+1], l_min);
            }

            double end1 = 1;
            if(l_max >= rangeLim[i+1])
            {
                end1 = 1;
            }
            else if( l_max < rangeLim[i+1] )
            {
                end1 = ::percentilelog10(rangeLim[i], rangeLim[i+1], l_max);
            }

            rangeFills[i] = end1 - start;
        }
    }

    double sum = 0;
    for(size_t i = 0; i < box-1 ; ++i)
    {
        sum += rangeFills[i];
    }

    if( sum > 1)
    {
        L_end = L_end_;
        L_end *=sum;
    }
    else if(sum <= 1)
    {
        L_end = L_end_;
    }

    updateNMeasurements();
    ::range1og10(l_min, l_max, L_end, l_thermal);

    for (size_t i=0; i < L_end; ++i )
    {
        omegas[i] = ::omega(L_coat, l_thermal[i], kc, psic);
    }

    return L_end;
}


Laser::~Laser()
{
  delete [] l_thermal;
  delete [] omegas;
}


setup::setup(struct Laser laser_, struct Detector detector_)
    : laser(laser_), detector(detector_) {}



}
