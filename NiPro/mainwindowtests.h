#ifndef MAINWINDOWTESTS_H
#define MAINWINDOWTESTS_H

#include <QMainWindow>

namespace Ui {
class MainWindowTESTS;
}

class MainWindowTESTS : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindowTESTS(QWidget *parent = 0);
    ~MainWindowTESTS();
    
private:
    Ui::MainWindowTESTS *ui;
};

#endif // MAINWINDOWTESTS_H
