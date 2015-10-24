#include "load_file_path_from_dialog.h"



namespace qt_utilities{

  auto load_file_path_from_dialog
  ( filesystem::path const dir, QString const file_filter )
  -> optional<filesystem::path>
  {
    auto const parent_widget = nullptr;
    auto const caption = QFileDialog::tr("Open Document");

    auto const selectedFilter = nullptr;
    auto const options = QFileDialog::Options(0);

    auto const directory = QString::fromStdString( dir.string() );

    auto const fileName =
         QFileDialog::getOpenFileName(
          parent_widget,
          caption,
          directory,
          file_filter,
          selectedFilter,
          options);


    auto const fileName_string = fileName.toStdString();

    auto const loaded_file = filesystem::path( fileName_string );

    if( filesystem::is_regular_file( loaded_file ) ){
      return loaded_file;
    }
    else {
      return optional<filesystem::path>();
    }
  }

}
