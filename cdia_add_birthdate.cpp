#include "cdia_add_birthdate.h"
#include "ui_cdia_add_birthdate.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

CDIA_ADD_BIRTHDATE::CDIA_ADD_BIRTHDATE(QWidget *parent, CManager_birthday_reminder* pmanager_birthday_reminder)
    : QMainWindow(parent)
    , ui(new Ui::CDIA_ADD_BIRTHDATE)
{
    ui->setupUi(this);
    m_bsaved = false;
}

CDIA_ADD_BIRTHDATE::~CDIA_ADD_BIRTHDATE()
{
    delete ui;
}

void CDIA_ADD_BIRTHDATE::on_pushButton_clicked()
{
    QString strsurname = ui->lineEdit_surname->text();
    QString strforename = ui->lineEdit_forename->text();
    QDate birthdate = ui->dateEdit->date();

    QString strSQL = QString("insert into persons values (NULL, '%1', '%2', '%3')").arg(strsurname).arg(strforename).arg(birthdate.toString("yyyy-MM-dd"));
    QSqlQuery query;
    if(!query.exec(strSQL))
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("Error");
        msgbox.setText("Error Inserting Data into Table 'Persons'\n" + query.lastError().text());
        msgbox.exec();
        return;
    }

    m_bsaved = true;
}

void CDIA_ADD_BIRTHDATE::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);

    emit CloseSignal();
}

