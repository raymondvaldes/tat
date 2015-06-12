cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(valdes-units)

find_package(Boost REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-std=c++14)

add_library(valdes-units shared
    units/si/constants/codata.h
    units/si/constants/thermal.h
    units/si/extension.h
    units/si/predefined.h
    units/si/prefixes.h
    units/si/si.h
    units/systems/si/base.h
    units/cmath.h
    units/operators.h
    units/physical_dimensions.h
    units/quantity.h
    units/scale.h
    units/static_rational.h
    units/conversions.h
    units.h
)

target_link_libraries( valdes-units shared
  ${Boost_FILESYSTEM_LIBRARY}
)
