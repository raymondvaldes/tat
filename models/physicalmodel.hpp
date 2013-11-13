#ifndef PHYSICALMODEL_HPP
#define PHYSICALMODEL_HPP

class property
{
private:
    static constexpr bool tempDependent = false;
    double Current(const double temperature) const;

    double Projected(const double temperature1, const double temperature2)const;

public:
    double offset;
    double slope;

    property(double offset_, double slope_);
    property(void);

    double Current(const std::vector<std::vector<double>>& T, const size_t n,
                   const size_t j) const;

    double Current(const std::vector<std::vector<double>>& T, const size_t n,
                   const size_t j1, const size_t j2) const;


    double Current(const class Temperature Tprofile, const size_t n,
                   const size_t j) const;

    double Current(const class Temperature Tprofile, const size_t n,
                   const size_t j1, const size_t j2) const;


    double Projected(const std::vector<std::vector<double>>& T,
                               const size_t n, const size_t j) const;

    double Projected(const std::vector<std::vector<double>>& T, const size_t n,
                     const size_t j1, const size_t j2) const;

    double Projectedt(const std::vector<std::vector<double>>& T,
                      const size_t n, const size_t, const size_t j) const;

    double Projected(const class Temperature Tprofile,
                               const size_t n, const size_t j) const;

    double Projected(const class Temperature Tprofile, const size_t n,
                     const size_t j1, const size_t j2) const;

    double Projectedt(const class Temperature Tprofile,
                                const size_t n, const size_t, const size_t j)
                                const;
};

namespace physicalModel
{

struct labels
{
public:
  enum class Name
  {
    gammaEff,
    asub,
    E1,
    R1,
    lambda,
    R0
  };

  enum Name name;

  labels(const enum Name name_);
  Name getName(void);
};

struct layer
{
    struct property kthermal;
    struct property psithermal;
    double depth;
    double lambda;
    double diffusivity;
    double effusivity;
    double c = 1;

    double opticalPenetration(void);
    layer(struct property kthermal_, struct property psithermal_, double depth_,
          double lambda_);
};

struct temperatureScale
{
    double tolerance;
    double referance;
    double base;
    double rear;
    temperatureScale(const double tolerance_,const double referance_,
                     const double base_, const double rear_);
};

struct radiativeSysProp
{
    double R0;
    double R1;
    double Emit1;
    radiativeSysProp(const double R0_, const double R1_, const double Emit1_);
};


struct nonDimensional
{
  double gamma;

};

struct TBCsystem
{
    struct layer coating;
    struct layer substrate;
    struct temperatureScale Temp;
    struct radiativeSysProp optical;
    double radius;
    double gamma;
    double Rtc;

    TBCsystem(struct layer coating_, struct layer substrate_,
              struct temperatureScale Temp_, struct radiativeSysProp optical_,
              double radius_);
};

}
#endif // PHYSICALMODEL_HPP
