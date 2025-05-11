#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cdia_add_birthdate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Refresh();
}

void MainWindow::FillSpread()
{

    ui->tableWidget->reset();
    ui->tableWidget->setRowCount(0);

    CManager_birthday_reminder::vecPerson* pvecPerson = m_manager_birthday_reminder.GetpvecPerson();
    int irow = 0;

    for(auto& person : *pvecPerson)
    {
        ui->tableWidget->setRowCount( ui->tableWidget->rowCount() + 1);

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

void MainWindow::on_actionHinzufuegen_triggered()
{
    CDIA_ADD_BIRTHDATE* pdlg = new CDIA_ADD_BIRTHDATE(this);

    connect(pdlg, &CDIA_ADD_BIRTHDATE::CloseSignal, [this, pdlg](){
        if(pdlg->m_bsaved)
        {
            this->Refresh();
        }
    });

    pdlg->show();
}

