#ifndef EXPEQUIPMENT_HPP_INCLUDED
#define EXPEQUIPMENT_HPP_INCLUDED

namespace expEquipment{



struct Detector
{
    double wavelength;
    double radius;
    Detector(const double wavelength_, const double radius_);
};

class Laser
{
private:
    double area(void) const;
    double IntensityTotal(void) const;
    double IntensitySteady(void) const;
    double IntensityTransient(void) const;
    double offset, amplitude;
    void update(void);
    double l_min, l_max;
    void updateNMeasurements();

public:
    double Qlaser;
    double radius;
    double Is, It;

    size_t L_end;
    double *omegas = nullptr;
    double *l_thermal = nullptr;

    Laser(const double a, const double b, const double c, const double d);
    void updateRadius(const double r);
    void updatePower(const double Qpower);

    double thermalSetup(const double lmin_, const double lmax_,
                      const double L_coat, const double kc, const double psic,
                      const double L_end_);
    void cleanup(void);
};

struct setup
{
    class Laser laser;
    struct Detector detector;
    setup(struct Laser laser_, struct Detector detector_);
};


}


#endif // EXPEQUIPMENT_HPP_INCLUDED

