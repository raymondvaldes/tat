#include "addfrequencies.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  AddFrequencies w;

  w.show();

  return a.exec();
}
