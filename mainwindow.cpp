#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cdia_add_birthdate.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    Refresh();
}

void MainWindow::FillSpread()
{




    CManager_birthday_reminder::vecPerson* pvecPerson = m_manager_birthday_reminder.GetpvecPerson();

    ui->tableWidget->reset();
    ui->tableWidget->setRowCount(pvecPerson->size());

    int irow = 0;

    for(auto& person : *pvecPerson)
    {

        auto pitem_id = new QTableWidgetItem;
        pitem_id->setData(Qt::EditRole, person.iid);

        auto pitem_surname = new QTableWidgetItem;
        pitem_surname->setData(Qt::EditRole, person.strsurname);

        auto pitem_forename = new QTableWidgetItem;
        pitem_forename->setData(Qt::EditRole, person.strforename);

        auto pitem_birthdate = new QTableWidgetItem;
        pitem_birthdate->setData(Qt::EditRole, person.birthdate);

        auto pitem_age = new QTableWidgetItem;
        pitem_age->setData(Qt::EditRole, person.iage);


        ui->tableWidget->setItem(irow, 0, pitem_id);
        ui->tableWidget->setItem(irow, 1, pitem_surname);
        ui->tableWidget->setItem(irow, 2, pitem_forename);
        ui->tableWidget->setItem(irow, 3, pitem_birthdate);
        ui->tableWidget->setItem(irow, 4, pitem_age);

        irow++;
    }
    ui->tableWidget->selectRow(0);
}

void MainWindow::Refresh()
{
    m_manager_birthday_reminder.FillvecPerson();

    FillSpread();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*void MainWindow::on_actionadd_triggered()
{
    CDIA_ADD_BIRTHDATE dlg;

    dlg.exec();

    if(dlg.IsSaved())
    {
        Refresh();
    }
}*/


void MainWindow::on_actionadd_triggered()
{
    CDIA_ADD_BIRTHDATE dlg;

    dlg.setWindowTitle("Add");

    dlg.exec();

    if(dlg.IsSaved() && dlg.IsEdited())
    {
        Refresh();
    }
}


void MainWindow::on_actionEdit_triggered()
{
    CDIA_ADD_BIRTHDATE dlg;


    auto qlist_selected = ui->tableWidget->selectedItems();
    if(qlist_selected.size() > 0)
    {
        int irow = qlist_selected.at(0)->row();

        int ipkpersons = ui->tableWidget->item(irow, 0)->data(Qt::EditRole).toInt();

        dlg.SetPKPersons(ipkpersons);

        dlg.setWindowTitle("Edit");

        dlg.exec();

        if(dlg.IsSaved() && dlg.IsEdited())
        {
            Refresh();
        }

        ui->tableWidget->selectRow(irow);
    }
}


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    on_actionEdit_triggered();
}


void MainWindow::on_actionRefresh_triggered()
{
    Refresh();
}


void MainWindow::on_actionDelete_triggered()
{
    auto qlist_selected = ui->tableWidget->selectedItems();
    if(qlist_selected.size() > 0)
    {
        int irow = qlist_selected.at(0)->row();

        int ipkpersons = ui->tableWidget->item(irow, 0)->data(Qt::EditRole).toInt();

        if (CManager_birthday_reminder::DeletePerson(ipkpersons))
        {
            Refresh();
        }

    ui->tableWidget->selectRow(irow);
    }
}


void MainWindow::on_actionControls_triggered()
{
    QMessageBox msgbox;
    msgbox.setWindowTitle("Controls");
    msgbox.setText("To add new: Return Key\nTo edit: Control Key + Return Key\nTo Refresh: F5 Key\nTo delete: Delete Key\nTo Close: Escape Key");
    msgbox.exec();
}

