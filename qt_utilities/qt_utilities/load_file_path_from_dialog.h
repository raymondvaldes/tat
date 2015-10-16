#ifndef QT_UTILITIES_H
#define QT_UTILITIES_H

#include <QFileDialog>
#include <string>
#include "tools/interface/filesystem.hpp"
#include "optional/optional.h"

namespace qt_utilities{

auto load_file_path_from_dialog
( filesystem::path const directory, QString const file_filter )
-> optional<filesystem::path>;

}

#endif // QT_UTILITIES_H
