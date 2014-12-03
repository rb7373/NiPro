#include "mainwindowtests.h"
#include "ui_mainwindowtests.h"

MainWindowTESTS::MainWindowTESTS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowTESTS)
{
    ui->setupUi(this);

}

MainWindowTESTS::~MainWindowTESTS()
{
    delete ui;
}
