#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

  void on_display_frequencies_textChanged();

  void on_actionCreateFrequencyObject_triggered();

  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
