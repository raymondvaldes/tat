#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>

using std::cout;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_display_frequencies_textChanged()
{
  auto const display_this = "hi raymond!";
}

void MainWindow::on_actionCreateFrequencyObject_triggered()
{
  cout << "hello, now I am triggering object..\n";
}

void MainWindow::on_pushButton_clicked()
{

}
