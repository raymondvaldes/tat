#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <cmath>
#include <cassert>

#include "thermal/equipment/detector/judsonTeledyneInSB/is_valid_signal.hpp"
#include "load_file_path_from_dialog.h"
#include "thermal/pyrometry/twoColor/calibration/coefficient_is_valid.hpp"
#include "phase_analysis.h"
#include "amplitude_analysis.h"
#include "thermal/equipment/laser/is_valid_frequency.h"

#include "thermal/model/oneLayer2D/generator/disk.hpp"
#include "thermal/plot/phase/model_vs_experiment_phases.hpp"

using namespace units;
using std::string;
using std::to_string;
using thermal::equipment::detector::judsonTeledyneInSB::is_valid_signal;
using thermal::model::oneLayer2D::Conduction_model;
using thermal::model::oneLayer2D::Detector_model;
using thermal::model::Optics;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  working_directory(std::string(
   "/Users/raymondvaldes/Dropbox/investigations/2color/august/poco_graphite/edm-3/phase2") ),
  print_directory( working_directory ),
  set_phase( thermal::pyrometry::twoColor::Set_phase::lambda_2 ),
  conduction_model( Conduction_model::finite_disk ),
  detector_model( Detector_model::center_with_view )
{
  ui->setupUi(this);

  // gcoefficient
  auto const gcoefficient_string = std::to_string( gCoefficient.value() );
  ui->gCoefficient_textbox->setPlaceholderText( gcoefficient_string.data() );

    //setup combo boxes
  ui->comboBox_for_phase->addItem("Default phase", 0);
  ui->comboBox_for_phase->addItem("Lambda 1", 1);
  ui->comboBox_for_phase->addItem("Lambda 2", 2);
  ui->comboBox_for_phase->setCurrentIndex( 2 );


  on_comboBox_currentIndexChanged(1);
  on_comboBox_detector_model_selection_currentIndexChanged(1);
  auto const a = identify_parameters_to_fit();

 // on_comboBox_currentIndexChanged(1);
 // on_comboBox_detector_model_selection_currentIndexChanged(1);

}

MainWindow::~MainWindow()
{
  delete ui;
}

auto MainWindow::check_if_pyrometry_ready() -> bool
{

  auto const input_dc_total_1 = ui->filter_1_dc_total->text();
  auto const input_dc_background_1 = ui->filter_1_dc_background->text();

  auto const input_signal_dc_t_1 = input_dc_total_1.toDouble() * volts ;
  auto const input_signal_dc_b_1 = input_dc_background_1.toDouble() * volts ;

  auto const dc_t_1_valid = is_valid_signal( input_signal_dc_t_1 );
  if( dc_t_1_valid ){
    dc_1_total = input_signal_dc_t_1;
  }
  else{
    ui->filter_1_dc_total->clear();
  }

  auto const dc_b_1_valid = is_valid_signal( input_signal_dc_b_1 );
  if( dc_b_1_valid ){
    dc_1_background = input_signal_dc_b_1;
  }
  else{
    ui->filter_1_dc_background->clear();
  }

  auto const input_dc_t_2 = ui->filter_2_dc_background->text();
  auto const input_signal_dc_t_2 = input_dc_t_2.toDouble() * volts ;
  auto const dc_t_2_valid = is_valid_signal( input_signal_dc_t_2 ) ;
  if( dc_t_2_valid ) {
    dc_2_background = input_signal_dc_t_2;

  }
  else{
    ui->filter_2_dc_background->clear();
  }

  auto const input = ui->filter_2_dc_total->text();
  auto const input_signal = input.toDouble() * volts ;
  auto const dc_b_2_valid = is_valid_signal( input_signal ) ;

  if( dc_b_2_valid ){
    dc_2_total = input_signal;

  }
  else{
    ui->filter_2_dc_total->clear();
  }


  auto const DC_measurements_valid =
      dc_t_1_valid && dc_b_1_valid && dc_t_2_valid && dc_b_2_valid;


  auto const files_are_loaded = meta_data_1 && meta_data_2 ;

  auto files_are_unique = false;
  auto files_are_same_size = false;
  auto files_same_measurements = false;

  auto files_are_valid = false;

  if( files_are_loaded )
  {
    files_are_same_size =
        meta_data_1->size() == meta_data_2->size();
    files_same_measurements =
        meta_data_1->laser_frequencies() == meta_data_2->laser_frequencies();
    files_are_unique =
         meta_data_1->detector_wavelength() != meta_data_2->detector_wavelength();

    files_are_valid =
        files_are_loaded && files_are_unique &&
        files_are_same_size && files_same_measurements;

    if( files_are_valid ) {
      fix_order_of_files( files_are_valid );
    }

  }

  auto const DC_measurements_are_valid = DC_measurements_valid &&
      dc_1_background < dc_1_total &&
      dc_2_background < dc_2_total &&
      dc_1_background.value() > 0 &&
      dc_2_background.value() > 0 ;

  auto const pyrometry_ready = files_are_valid && DC_measurements_are_valid;

  if( pyrometry_ready )
  {
    set_print_directory();
    ui->pyrometry_ready_button->setEnabled( true );
    ui->pyrometry_ready_button->setDown(true);
  }
  else{
    ui->pyrometry_ready_button->setEnabled( false );
  }

  return pyrometry_ready;
}

void MainWindow::check_if_ready_to_plot()
{
  auto const pyrometry_ready = check_if_pyrometry_ready() ;

  auto const optics_ready = check_if_optics_are_ready();
  auto const specimen_ready = check_if_ready_to_create_initial_slab();

  auto const everything_ready =
      pyrometry_ready && optics_ready && specimen_ready;

  if( everything_ready )
  {
    set_pushButton();
  }
  else{
    disable_analysis();
  }
}

void MainWindow::fix_order_of_files( bool const files_are_valid )
{
  assert( files_are_valid );

  auto const detector_wavelength_1 = meta_data_1->detector_wavelength();
  auto const detector_wavelength_2 = meta_data_2->detector_wavelength();

  auto const order_is_correct = detector_wavelength_1 < detector_wavelength_2;
  auto const order_is_wrong = !order_is_correct;

  if( order_is_wrong ) {
    auto const temporary_first = meta_data_1;
    auto const temporary_second = meta_data_2;

    meta_data_1 = temporary_second;
    meta_data_2 = temporary_first;

    display_file_1_detector_wavelength( meta_data_1->detector_wavelength() ) ;
    display_file_2_detector_wavelength( meta_data_2->detector_wavelength() ) ;

  }
}


void MainWindow::set_print_directory()
{
  using std::string;

  auto const dir = this->working_directory.parent_path().string();
  auto const print_string = dir + "/" + string("plots") ;
  auto const print_folder =
      filesystem::path(  print_string );

  filesystem::create_directory( print_folder );
  print_directory = print_folder;
}

void MainWindow::set_working_directory( filesystem::path const directory_path )
{
  working_directory = directory_path;
}

void MainWindow::load_lambda1()
{
  auto const fileName =
      qt_utilities::load_file_path_from_dialog( working_directory, tbd_file_filter );

  if( fileName ) {

    try{
      meta_data_1 = gTBC::gMeasure::import_sweep_meta_data( *fileName );
    }
    catch ( const std::domain_error& error){
      std::cerr << error.what() << "\n";
    }

    display_file_1_detector_wavelength( meta_data_1->detector_wavelength() ) ;
    set_working_directory( *fileName );
    check_if_ready_to_plot();
  }

}

void MainWindow::load_lambda2()
{
  auto const fileName =
      qt_utilities::load_file_path_from_dialog( working_directory, tbd_file_filter );

  if( fileName ) {
    set_working_directory( *fileName );

    try{
      meta_data_2 = gTBC::gMeasure::import_sweep_meta_data( *fileName );
      display_file_2_detector_wavelength( meta_data_2->detector_wavelength() ) ;
      check_if_ready_to_plot();
    }
    catch ( const std::domain_error& error){
      std::cerr << error.what() << "\n";
    }
  }



}

void MainWindow::display_file_1_detector_wavelength
( thermal::equipment::detector::Peak_wavelength const lambda  )
{

  auto const text = QString::number( lambda.value() * 1.e6, 'f', 3 ) ;
  auto const text_label = text + " " + QString( (QChar)956 )+ "m filter:";

  ui->label_filter_1->setText( text_label );
  ui->label_filter_1->setEnabled(true);
  ui->filter_1_dc_background->setEnabled(true);
  ui->filter_1_dc_total->setEnabled(true);
  ui->label_steady_state_Detector_measurements->setEnabled(true);
}

void MainWindow::display_file_2_detector_wavelength
( thermal::equipment::detector::Peak_wavelength const lambda  )
{
  auto const text = QString::number( lambda.value() * 1.e6, 'f', 3 ) ;
  auto const text_label = text + " " + QString( (QChar)956 )+ "m filter:";

  ui->label_filter_2->setText( text_label );
  ui->label_filter_2->setEnabled(true);
  ui->filter_2_dc_background->setEnabled(true);
  ui->filter_2_dc_total->setEnabled(true);
  ui->label_steady_state_Detector_measurements->setEnabled(true);

}


auto MainWindow::display_steady_state_temperature(
     units::quantity< units::si::temperature > const temperature
) noexcept -> void
{
  auto const t_string = to_string( temperature.value() );
  auto const t_out = "steady state temperature: " + t_string + " K";

  add_to_text_logger( t_out );
}

void MainWindow::disable_analysis()
{
  ui->run_amplitude_analysis->setEnabled( false );
}

void MainWindow::set_pushButton()
{
  ui->run_amplitude_analysis->setEnabled( true );
  ui->run_phase_analysis->setEnabled(true);
}

void MainWindow::reset_pushButton()
{
}





void MainWindow::on_filter_1_dc_total_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_filter_1_dc_background_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_filter_2_dc_total_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_filter_2_dc_background_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_gCoefficient_textbox_editingFinished()
{
  using thermal::pyrometry::twoColor::calibration::coefficient_is_valid;
  using thermal::pyrometry::twoColor::calibration::Coefficient;

  auto const input_text = ui->gCoefficient_textbox->text();
  auto const input_value = input_text.toDouble();
  auto const g = Coefficient( input_value );

  if(  coefficient_is_valid( g ) ) {
    gCoefficient = g;
    ui->gCoefficient_textbox->setEnabled(true);

  }
  else{
    ui->gCoefficient_textbox->clear();
    ui->gCoefficient_textbox->setEnabled(false);
  }

}

void MainWindow::on_comboBox_for_phase_currentIndexChanged(int index)
{
  using thermal::pyrometry::twoColor::Set_phase;

    switch( index )
    {
      case 0:
        set_phase = Set_phase::do_not_adjust;
        break;
      case 1:
        set_phase = Set_phase::lambda_1;
        break;
      case 2:
        set_phase = Set_phase::lambda_2;
        break;
    }
}


void MainWindow::on_pushButton_load_TBD_files_clicked()
{
  load_lambda1();
  load_lambda2();

}

void MainWindow::add_to_text_logger( std::string const & line )
{

  ui->textBrowser->append(QString( line.data() ));
}

void MainWindow::add_to_text_logger( double const value )
{
  auto const line_string = to_string( value ) ;
  add_to_text_logger( line_string );
}

void MainWindow::on_run_amplitude_analysis_clicked()
{
  ui->run_amplitude_analysis->setEnabled(true);

  auto const DC_1 = dc_1_total - dc_1_background;
  auto const DC_2 = dc_2_total - dc_2_background;

  auto const analysis =
      gui_analysis::amplitude_analysis
      ( *meta_data_1, *meta_data_2, DC_1, DC_2, gCoefficient, set_phase );


  auto const surface_temperature_phases =
  analysis.surface_temperature_phases();

  auto const surface_temperature_steady =
  analysis.surface_steady_temperature();

  auto const surface_temperature_amplitudes =
  analysis.surface_temperature_amplitudes();

  analysis.print_temperature_amplitudes( print_directory );
  analysis.print_temperature_phases( print_directory );

  display_steady_state_temperature( surface_temperature_steady );

  std::cout << surface_temperature_steady << "\n";
}

auto MainWindow::check_if_optics_are_ready() noexcept -> bool
{
  using std::isfinite;
  auto const is_valid = []( auto const v ){ return v > 0 && isfinite(v);  };

  auto const b_value = ui->lineEdit_beam_radius->text().toDouble();
  auto const b_det_value = ui->lineEdit_detector_view_radius->text().toDouble();
  auto const p_value = ui->lineEdit_laser_intensity->text().toDouble();
  auto const m_value = ui->lineEdit_modulation_depth_m->text().toDouble();

  auto const all_parameters_are_valid =
      is_valid( b_value ) &&
      is_valid( p_value ) &&
      is_valid( m_value ) &&
      is_valid( b_det_value );


  if( all_parameters_are_valid ) {
    ui->optics_ready_button->setEnabled( true );
    ui->optics_ready_button->setDown(true);

    auto const beam_radius = quantity< length >( b_value * millimeters );
    auto const view_radius = quantity< length >( b_det_value * millimeters );
    auto const m = quantity< si::dimensionless>(m_value);
    auto const laser_intensity =
        quantity< si::heat_flux>( p_value * si::watts / si::square_meter );

    this->optics = Optics( beam_radius, laser_intensity, view_radius, m);
  }
  else {
    ui->optics_ready_button->setEnabled( false );
    this->optics = optional<Optics>();
  }

  return all_parameters_are_valid;
}


auto MainWindow::check_if_ready_to_create_initial_slab() noexcept -> bool
{
  using std::isfinite;
  using thermal::model::slab::Slab;

  auto const is_valid = []( auto const v ){ return v > 0 && isfinite(v);  };

  auto const L_value = ui->lineEdit_slab_thickness->text().toDouble();
  auto const diff_value = ui->lineEdit_thermal_diffusivity->text().toDouble();
  auto const k_value = ui->lineEdit_thermal_conductivity->text().toDouble();
  auto const R_value = ui->lineEdit_radius_input->text().toDouble();

  auto const all_parameters_are_valid =
      is_valid( L_value ) &&
      is_valid( diff_value )&&
      is_valid( k_value ) &&
      is_valid( R_value );

  if( all_parameters_are_valid ) {
    ui->prepare_initial_slab_button->setEnabled( true );
    ui->prepare_initial_slab_button->setDown(true);

    auto const R = quantity< length > ( R_value * millimeters  );
    auto const L = quantity< length > ( L_value * millimeters  );
    auto const diffusivity =
        quantity<thermal_diffusivity>( diff_value *square_millimeters / second);
    auto const conductivity =
      quantity< thermal_conductivity >( k_value * watts / meter / si::kelvin );

    this->initial_slab = Slab( L, diffusivity, conductivity, R ) ;
  }
  else {
    ui->prepare_initial_slab_button->setEnabled( false );

    auto const empty_slab = optional< Slab >();
    this->initial_slab = empty_slab;
  }

  return all_parameters_are_valid;
}

void MainWindow::on_run_phase_analysis_clicked()
{
  using namespace thermal::analysis::oneLayer2D::estimate_parameters;
  auto best_fit = optional< phase_analysis::Best_fit>();

  auto const filtered_meta_data =
      meta_data_2->
      filter_using_cutoff_frequencies( modulation_cutoff_frequencies );

  auto const parameters_to_fit = identify_parameters_to_fit();

  if( conduction_model == Conduction_model::infinite_disk &&
      detector_model == Detector_model::center_with_view )
  {
    best_fit = gui_analysis::phase_anaysis(
          *initial_slab, *optics,
      filtered_meta_data.laser_frequencies(),
      filtered_meta_data.measurement_phases()
    );
  }


  else if( conduction_model == Conduction_model::finite_disk &&
      detector_model == Detector_model::center_with_view )
  {
    best_fit = gui_analysis::phase_anaysis_finite_disk(
          *initial_slab, *optics,
      filtered_meta_data.laser_frequencies(),
      filtered_meta_data.measurement_phases(),
      parameters_to_fit
    );
  }

  else if( conduction_model == Conduction_model::finite_disk &&
      detector_model == Detector_model::center_point )
  {
    best_fit = gui_analysis::phase_anaysis_finite_disk_centered_point(
      *initial_slab, *optics,
      filtered_meta_data.laser_frequencies(),
      filtered_meta_data.measurement_phases()    );
  }


  if( best_fit ) {
  using thermal::model::oneLayer2D::generator::Disk;


  auto const slab = best_fit->bulk_slab;
  auto const optics = best_fit->optics;
  auto const model = Disk( conduction_model, detector_model, slab, optics );

  auto const frequencies = meta_data_2->laser_frequencies();
  auto const model_complex_temperatures = model.evaluate( frequencies );

  assert( model_complex_temperatures.size() == frequencies.size() ) ;

  auto const model_phases = model_complex_temperatures.phases();

  assert( !model_phases.empty() );

  auto const experimental_phases = meta_data_2->measurement_phases();

  assert( !experimental_phases.empty() );
  assert( model_phases.size() == experimental_phases.size() );

  assert( model_phases.size() == frequencies.size() );
  assert( experimental_phases.size() == frequencies.size() );

  thermal::plot::phase::model_vs_experiment_phases(
        frequencies, model_phases, experimental_phases );
  }
  else {
    add_to_text_logger( std::string("No fitting algorithm available.") );
  }
}

void MainWindow::on_lineEdit_radius_input_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_lineEdit_slab_thickness_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_lineEdit_beam_radius_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_lineEdit_detector_view_radius_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_lineEdit_thermal_diffusivity_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_lineEdit_thermal_conductivity_editingFinished()
{
  check_if_ready_to_plot();
}

void MainWindow::on_pyrometry_ready_button_clicked()
{
   ui->tabWidget_settings->setCurrentIndex(0);
   ui->pyrometry_ready_button->setDown(true);
}

void MainWindow::on_prepare_initial_slab_button_clicked()
{
  ui->tabWidget_settings->setCurrentIndex(1);
  ui->prepare_initial_slab_button->setDown(true);
}

void MainWindow::on_optics_ready_button_clicked()
{
  ui->tabWidget_settings->setCurrentIndex(2);
  ui->optics_ready_button->setDown(true);
}

void MainWindow::on_cutoff_frequency_lower_bound_editingFinished()
{
  using thermal::equipment::laser::is_valid_frequency;
  using thermal::equipment::laser::Modulation_Frequency;

  auto const v = ui->cutoff_frequency_lower_bound->text().toDouble();
  auto const value_is_finite = is_valid_frequency( v );
  auto const freq = Modulation_Frequency( v * si::hertz );

  auto const value_is_acceptable =
      !modulation_cutoff_frequencies.upper_bound  ||
      freq < *modulation_cutoff_frequencies.upper_bound;

  if( value_is_finite && value_is_acceptable )
  {
     modulation_cutoff_frequencies.lower_bound = freq;
  }
  else
  {
    modulation_cutoff_frequencies.lower_bound = 0 * si::hertz;
    ui->cutoff_frequency_lower_bound->clear();
  }
}

void MainWindow::on_cutoff_frequency_upper_bound_editingFinished()
{
  using thermal::equipment::laser::is_valid_frequency;
  using thermal::equipment::laser::Modulation_Frequency;

  auto const v = ui->cutoff_frequency_upper_bound->text().toDouble();
  auto const value_is_finite = is_valid_frequency( v );
  auto const freq = Modulation_Frequency( v * si::hertz );

  auto const value_is_acceptable =
      freq > modulation_cutoff_frequencies.lower_bound;

  if( value_is_finite && value_is_acceptable )
  {
     modulation_cutoff_frequencies.upper_bound = freq;
  }
  else
  {
    ui->cutoff_frequency_upper_bound->clear();
  }
}


auto MainWindow::identify_parameters_to_fit()
noexcept -> thermal::model::oneLayer2D::Parameter_selection
{
  //put this in xcode library
  using thermal::model::oneLayer2D::Parameter_selection;

  auto parameter_to_fit = Parameter_selection();
  if( ui->checkBox_estimate_beam_radius->isChecked() )  {
     parameter_to_fit.beam_radius = true;
  }
  if( ui->checkBox_estimate_thermal_conductivity->isChecked() )  {
     parameter_to_fit.thermal_conductivity = true;
  }

  if( ui->checkBox_estimate_thermal_diffusivity->isChecked() )  {
     parameter_to_fit.thermal_diffusivity = true;
  }

  if( ui->checkBox_estimate_specimen_radius->isChecked() )  {
     parameter_to_fit.specimen_radius = true;
  }

  if( ui->checkBox_estimate_detector_offset->isChecked() )  {
     parameter_to_fit.detector_offset = true;
  }

  if( ui->checkBox_estimate_view_radius->isChecked() )  {
     parameter_to_fit.detector_view_radius = true;
  }

  return parameter_to_fit;
}




void MainWindow::on_comboBox_currentIndexChanged(int index)
{
  switch( index )
  {
    case 0: {
        conduction_model = Conduction_model::infinite_disk;
        ui->checkBox_estimate_beam_radius->setEnabled(true);
        ui->checkBox_estimate_thermal_conductivity->setEnabled(false);
        ui->checkBox_estimate_thermal_diffusivity->setEnabled(false);
        ui->checkBox_estimate_specimen_radius->setEnabled(false);

        ui->checkBox_estimate_beam_radius->setChecked(true);
        ui->checkBox_estimate_thermal_conductivity->setChecked(false);
        ui->checkBox_estimate_thermal_diffusivity->setChecked(true);
        ui->checkBox_estimate_specimen_radius->setChecked(false);
        break;
      }
    case 1:
      conduction_model = Conduction_model::finite_disk;
        ui->checkBox_estimate_beam_radius->setEnabled(true);
        ui->checkBox_estimate_thermal_conductivity->setEnabled(false);
        ui->checkBox_estimate_thermal_diffusivity->setEnabled(false);
        ui->checkBox_estimate_specimen_radius->setEnabled(true);

        ui->checkBox_estimate_beam_radius->setChecked(true);
        ui->checkBox_estimate_thermal_conductivity->setChecked(false);
        ui->checkBox_estimate_thermal_diffusivity->setChecked(true);
        ui->checkBox_estimate_specimen_radius->setChecked(true);

      break;
  }
}

void MainWindow::on_comboBox_detector_model_selection_currentIndexChanged(int index)
{
  switch( index )
  {
    case 0: {
        detector_model = Detector_model::center_point;

        ui->checkBox_estimate_detector_offset->setEnabled(false);
        ui->checkBox_estimate_detector_offset->setChecked(false);

        ui->checkBox_estimate_view_radius->setEnabled(false);
        ui->checkBox_estimate_view_radius->setChecked(false);

        break;
      }
    case 1: {
        detector_model = Detector_model::center_with_view;

        ui->checkBox_estimate_detector_offset->setEnabled(false);
        ui->checkBox_estimate_detector_offset->setChecked(false);


        ui->checkBox_estimate_view_radius->setEnabled(true);
        ui->checkBox_estimate_view_radius->setChecked(true);
        break;
      }
    case 2: {
        detector_model = Detector_model::offset_point;

        ui->checkBox_estimate_detector_offset->setEnabled(true);
        ui->checkBox_estimate_detector_offset->setChecked(true);

        ui->checkBox_estimate_view_radius->setEnabled(false);
        ui->checkBox_estimate_view_radius->setChecked(false);

        break;
     }
    case 3: {
        detector_model = Detector_model::offset_with_view;

        ui->checkBox_estimate_detector_offset->setEnabled(true);
        ui->checkBox_estimate_detector_offset->setChecked(true);

        ui->checkBox_estimate_view_radius->setEnabled(true);
        ui->checkBox_estimate_view_radius->setChecked(true);

        break;
      }
  }
}

void MainWindow::on_tabWidget_settings_tabBarClicked(int index)
{
   if( index == 3 ) {
      ui->ready_model_button->setDown(true);
   }
}
