#ifndef ADDFREQUENCIES_H
#define ADDFREQUENCIES_H

#include <QMainWindow>

namespace Ui {
  class AddFrequencies;
}

class AddFrequencies : public QMainWindow
{
  Q_OBJECT

public:
  explicit AddFrequencies(QWidget *parent = 0);
  ~AddFrequencies();

private slots:
  void on_pushButton_clicked();
  void load_default_frequencies();
  void load_default_plot();

  void on_textEdit_2_returnPressed();

  void on_pushButton_toggled();

  void on_pushButton_2_clicked();

  void display_a_plot();

private:
  Ui::AddFrequencies *ui;
  void displayText(  QString const line  );
  auto readText( void ) -> QString;


};

#endif // ADDFREQUENCIES_H
