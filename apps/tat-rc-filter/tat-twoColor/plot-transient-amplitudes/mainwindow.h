#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "filesystem/path.h"
#include "thermal/equipment/detector/signal.h"
#include "gTBC/gMeasure/gTBD/import_twoColor_TBD_files.hpp"
#include "gTBC/gMeasure/import_sweep_meta_data.h"
#include "thermal/pyrometry/twoColor/calibration/Coefficient.h"
#include "thermal/equipment/detector/peak_wavelength.h"
#include "gTBC/gMeasure/gTBD/meta_measurement_descriptions.hpp"
#include "optional/optional.h"
#include "thermal/pyrometry/twoColor/set_phase.h"
#include "thermal/model/slab/slab.h"
#include "thermal/equipment/laser/modulation_frequency.h"
#include "thermal/equipment/laser/modulation_cutoff_frequencies.h"
#include "thermal/experimental/observations/slab/slab.hpp"
#include "thermal/model/optics/optics.h"
#include "thermal/model/oneLayer2D/model_selection.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:

  void reset_pushButton();


  void on_filter_1_dc_total_editingFinished();

  void on_filter_2_dc_total_editingFinished();

  void on_filter_1_dc_background_editingFinished();

  void on_filter_2_dc_background_editingFinished();

  void on_gCoefficient_textbox_editingFinished();


  void on_comboBox_for_phase_currentIndexChanged(int index);


  void on_pushButton_load_TBD_files_clicked();

  void on_run_amplitude_analysis_clicked();

  void on_run_phase_analysis_clicked();


  void on_lineEdit_slab_thickness_editingFinished();
  void on_lineEdit_beam_radius_editingFinished();
  void on_lineEdit_detector_view_radius_editingFinished();
  void on_lineEdit_thermal_diffusivity_editingFinished();
  void on_lineEdit_thermal_conductivity_editingFinished();

  void on_pyrometry_ready_button_clicked();

  void on_prepare_initial_slab_button_clicked();

  void on_optics_ready_button_clicked();


  void on_cutoff_frequency_lower_bound_editingFinished();

  void on_cutoff_frequency_upper_bound_editingFinished();

  void on_comboBox_currentIndexChanged(int index);

  void on_comboBox_detector_model_selection_currentIndexChanged(int index);

  void on_lineEdit_radius_input_editingFinished();

  void on_tabWidget_settings_tabBarClicked(int index);

private:
  Ui::MainWindow *ui;
  filesystem::path working_directory;
  filesystem::path print_directory;


  QString tbd_file_filter = QFileDialog::tr("All files (*.tbd)");

  thermal::equipment::detector::Signal dc_1_total = 15 * units::si::volts;
  thermal::equipment::detector::Signal dc_1_background = 15 * units::si::volts;
  thermal::equipment::detector::Signal dc_2_total = 15 * units::si::volts;
  thermal::equipment::detector::Signal dc_2_background = 15 * units::si::volts;

  thermal::pyrometry::twoColor::calibration::Coefficient gCoefficient = 0.776;
  thermal::pyrometry::twoColor::Set_phase set_phase;


  optional< gTBC::gMeasure::meta_measurement_descriptions> meta_data_1;
  optional< gTBC::gMeasure::meta_measurement_descriptions> meta_data_2;
  optional< thermal::model::slab::Slab> initial_slab;
  optional< thermal::model::Optics> optics;

  thermal::equipment::laser::Modulation_cutoff_frequencies modulation_cutoff_frequencies;

  thermal::model::oneLayer2D::Conduction_model conduction_model;
  thermal::model::oneLayer2D::Detector_model detector_model;


  void set_working_directory( filesystem::path const directory_path );

  auto display_steady_state_temperature(
       units::quantity< units::si::temperature > const temperature
  ) noexcept -> void;

  void check_if_ready_to_plot();
  void set_pushButton();
  void disable_analysis();
  void set_print_directory();
  void fix_order_of_files(const bool files_are_valid);
  void load_lambda1();
  void load_lambda2();

  void display_file_1_detector_wavelength
  ( thermal::equipment::detector::Peak_wavelength const lambda  );
  void display_file_2_detector_wavelength
  ( thermal::equipment::detector::Peak_wavelength const lambda  );

  void add_to_text_logger( std::string const & line );
  void add_to_text_logger( double const value );

  auto check_if_ready_to_create_initial_slab() noexcept -> bool;
  auto check_if_optics_are_ready() noexcept -> bool;
  auto check_if_pyrometry_ready() -> bool;
  auto identify_parameters_to_fit()
  noexcept -> thermal::model::oneLayer2D::Parameter_selection;

};


#endif // MAINWINDOW_H
