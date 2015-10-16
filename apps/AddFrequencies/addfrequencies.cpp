#include <QFile>
#include <QTextStream>
#include <QSvgWidget>

#include "addfrequencies.h"
#include "ui_addfrequencies.h"

AddFrequencies::AddFrequencies(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AddFrequencies)
{
  ui->setupUi(this);
  load_default_frequencies();
}

AddFrequencies::~AddFrequencies()
{
  delete ui;
}

void AddFrequencies::load_default_frequencies()
{
  QFile inputFile(":/default_frequencies.txt");
  inputFile.open(QIODevice::ReadOnly);

  QTextStream in(&inputFile);
  QString line = in.readAll();
  inputFile.close();

  displayText( line );
}


void AddFrequencies::load_default_plot()
{
  QSvgWidget default_plot( ":/default_plot.svg" );


}

void AddFrequencies::on_pushButton_clicked()
{
  auto const line = readText();

  auto const line_with_units = line + " Hz";
  displayText( line_with_units );
}

auto AddFrequencies::readText() -> QString
{
  auto const line = ui->textEdit_2->text();
  return line;
}

void AddFrequencies::displayText( QString const line )
{
  ui->textBrowser->setPlainText( line );
}

void AddFrequencies::on_textEdit_2_returnPressed()
{
    on_pushButton_clicked();
    on_pushButton_toggled();
}

void AddFrequencies::on_pushButton_toggled()
{
    ui->pushButton->animateClick();
}

void AddFrequencies::on_pushButton_2_clicked()
{
  load_default_frequencies();
}

void AddFrequencies::display_a_plot()
{

}


