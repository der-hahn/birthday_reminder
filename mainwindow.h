#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cmanager_birthday_reminder.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Refresh();
    void FillSpread();

private slots:
    void on_actionadd_triggered();

    void on_actionEdit_triggered();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_actionRefresh_triggered();

    void on_actionDelete_triggered();

    void on_actionControls_triggered();

private:
    Ui::MainWindow *ui;
    CManager_birthday_reminder m_manager_birthday_reminder;

};
#endif // MAINWINDOW_H
