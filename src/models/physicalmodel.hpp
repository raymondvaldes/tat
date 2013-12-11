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

    explicit property(const double offset_,const double slope_);
    explicit property(void);

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
    static class property
        loadConfigfromXMLTree(const boost::property_tree::ptree pt);


};

namespace physicalModel
{


class labels
{
public:
  enum class Name: uint8_t
  {
    gammaEff,
    asub,
    E1,
    R1,
    lambda,
    R0
  };

  typedef boost::bimap< enum Name , std::string > NameBiTYPE;
  const NameBiTYPE nameMap =
      boost::assign::list_of < NameBiTYPE::relation >
   ( Name::gammaEff , "gammaEff")
   ( Name::asub     , "asub")
   ( Name::E1       , "E1")
   ( Name::R1       , "R1")
   ( Name::lambda   , "lambda")
   ( Name::R0       , "R0");

  explicit labels(void);
  explicit labels(const enum Name name_);
  Name getName(void);

private:
  enum Name name;
};

struct temperatureScale
{
    double tolerance;
    double referance;
    double base;
    double rear;
    temperatureScale(const double tolerance_,const double referance_,
                     const double base_, const double rear_);
    ~temperatureScale( void );
    static struct temperatureScale loadConfig(const std::string &filename);
    static struct temperatureScale
        loadConfigfromXML( const boost::property_tree::ptree pt );
};

struct radiativeSysProp
{
    double R0;
    double R1;
    double Emit1;
    radiativeSysProp(const double R0_, const double R1_, const double Emit1_);
    static class radiativeSysProp
        loadConfig( const boost::property_tree::ptree pt );
    ~radiativeSysProp( void );
};

class layer
{
public:
    class property kthermal;
    class property psithermal;
    double depth;
    double lambda;
    double c = 1;

    double opticalPenetration(void) const;
    double thermalDiffusivity(void) const;
    double thermalEffusivity(void) const;
    explicit layer( const class property kthermal_,
                    const class property psithermal_,
                    const double depth_, const double lambda_);
    ~layer(void);
    static class layer
      loadConfigfromXMLTree( const boost::property_tree::ptree pt );
};

class TBCsystem
{
public:
    class layer coating;
    class layer substrate;
    struct temperatureScale Temp;
    struct radiativeSysProp optical;
    double radius;
    double Rtc;
    double gamma;
    double a_sub;

    explicit TBCsystem( const class layer coating_,
                        const class layer substrate_,
                        const struct temperatureScale Temp_,
                        const struct radiativeSysProp optical_,
                        const double radius_);
    ~TBCsystem(void);
    static class TBCsystem loadConfig(const boost::property_tree::ptree pt);
    double gammaEval(void) const ;
    double a_subEval(void) const;
    void updateCoat(void); //update coat properties
};

}
#endif // PHYSICALMODEL_HPP
