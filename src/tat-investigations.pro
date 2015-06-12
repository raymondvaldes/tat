#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T16:48:53
#
#-------------------------------------------------

QT       -= core gui

TARGET = tat-investigations
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14
CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -march=native
QMAKE_CXXFLAGS += -stdlib=libc++

SOURCES += \
    investigations/twoColorPyrometery/oneLayer2D/amplitude_analysis/amplitudes_from_experiment.cpp \
    investigations/twoColorPyrometery/oneLayer2D/complex_temperature_check/complex_temperature_check.cpp \
    investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/avg_phases_at_surface.cpp \
    investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/surface_phases_at_radial_position.cpp \
    investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/surface_phases_with_beam_diameter.cpp \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all/diffusivity_from_phases.cpp \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.cpp \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_diffusivity/diffusivity_from_phases.cpp \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_laser/diffusivity_from_phases.cpp \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/uncertainty_analysis.cpp \
    investigations/twoColorPyrometery/oneLayer2D/temp_sweep/surface_radial_profile.cpp \
    investigations/twoColorPyrometery/plot/normalized_SR_exp_model.cpp \
    investigations/twoColorPyrometery/plot/phase_exp_model.cpp \
    investigations/twoColorPyrometery/plot/steady_surface_temperature.cpp \
    investigations/twoColorPyrometery/plot/transient_surface_amplitudes.cpp \
    investigations/twoColorPyrometery/plot/wave_signals.cpp \
    investigations/twoColorPyrometery/calculateCalibrationCoefficients.cpp \
    investigations/twoColorPyrometery/phase_fitting.cpp \
    investigations/twoColorPyrometery/temperature_prediction.cpp \
    investigations/execute.cpp \
    investigations/main-app.cpp \
    investigations/num_method2014.cpp \
    investigations/sensitivityvaldes2013.cpp \
    investigations/taylor_uncertainty.cpp \
    investigations/twoColorPyrometery.cpp


HEADERS += \
    investigations/twoColorPyrometery/oneLayer2D/amplitude_analysis/amplitudes_from_experiment.h \
    investigations/twoColorPyrometery/oneLayer2D/complex_temperature_check/complex_temperature_check.h \
    investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/avg_phases_at_surface.h \
    investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/surface_phases_at_radial_position.h \
    investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/surface_phases_with_beam_diameter.h \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all/diffusivity_from_phases.h \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.h \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_diffusivity/diffusivity_from_phases.h \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_laser/diffusivity_from_phases.h \
    investigations/twoColorPyrometery/oneLayer2D/phase_analysis/uncertainty_analysis.h \
    investigations/twoColorPyrometery/oneLayer2D/temp_sweep/surface_radial_profile.h \
    investigations/twoColorPyrometery/plot/normalized_SR_exp_model.h \
    investigations/twoColorPyrometery/plot/phase_exp_model.h \
    investigations/twoColorPyrometery/plot/steady_surface_temperature.h \
    investigations/twoColorPyrometery/plot/transient_surface_amplitudes.h \
    investigations/twoColorPyrometery/plot/wave_signals.h \
    investigations/twoColorPyrometery/calculateCalibrationCoefficients.h \
    investigations/twoColorPyrometery/phase_fitting.h \
    investigations/twoColorPyrometery/temperature_prediction.h \
    investigations/execute.h \
    investigations/main-app.h \
    investigations/num_method2014.h \
    investigations/sensitivityvaldes2013.hpp \
    investigations/taylor_uncertainty.h \
    investigations/twoColorPyrometery.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
