#ifndef LOAD_FILE_PATH_FROM_DIALOG_H
#define LOAD_FILE_PATH_FROM_DIALOG_H


////temp
#include <QFileDialog>
#include <string>
#include "tools/interface/filesystem.hpp"
#include "optional/optional.h"


  namespace qt_utilities{
    auto load_file_path_from_dialog
    ( filesystem::path const dir, QString const file_filter )
    -> optional<filesystem::path>;
}
    /// temp

#endif // LOAD_FILE_PATH_FROM_DIALOG_H
