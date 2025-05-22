#include "cdia_add_birthdate.h"
#include "ui_cdia_add_birthdate.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

CDIA_ADD_BIRTHDATE::CDIA_ADD_BIRTHDATE(QWidget *parent, CManager_birthday_reminder* pmanager_birthday_reminder)
    : QDialog(parent)
    , ui(new Ui::CDIA_ADD_BIRTHDATE)
{
    ui->setupUi(this);
    m_bsaved = true;
    m_bedited = false;
    m_ipkpersons = -1;
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
    QString strSQL = "";

    if(m_ipkpersons == -1)
        strSQL = QString("insert into persons values (NULL, '%1', '%2', '%3')").arg(strsurname).arg(strforename).arg(birthdate.toString("yyyy-MM-dd"));
    else
        strSQL = QString("update persons set"
                " SURNAME = '%1',"
                " FORENAME = '%2',"
                " BIRTHDATE = '%3'"
                " where ID = %4").arg(strsurname).arg(strforename).arg(birthdate.toString("yyyy-MM-dd")).arg(m_ipkpersons);

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
    if(!m_bsaved)
    {
        QMessageBox msgbox(this);
        msgbox.setWindowTitle("Warning");
        msgbox.setText("Changes not saved. Save now?");
        msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
        msgbox.setDefaultButton(QMessageBox::Yes);
        int iret = msgbox.exec();

        switch (iret) {
        case QMessageBox::Yes:
            on_pushButton_clicked();
            event->accept();
            break;
        case QMessageBox::Abort:
            event->ignore();
            break;
        case QMessageBox::No:
            break;
            event->accept();
        }
    }
}

void CDIA_ADD_BIRTHDATE::reject()   //if escape was pressed
{
    close();
}


void CDIA_ADD_BIRTHDATE::on_lineEdit_surname_textChanged(const QString &arg1)
{
    m_bsaved = false;
    m_bedited = true;
}


void CDIA_ADD_BIRTHDATE::on_lineEdit_forename_textChanged(const QString &arg1)
{
    m_bsaved = false;
    m_bedited = true;
}


void CDIA_ADD_BIRTHDATE::on_dateEdit_dateChanged(const QDate &date)
{
    m_bsaved = false;
    m_bedited = true;
}

void CDIA_ADD_BIRTHDATE::showEvent(QShowEvent * event)
{

    QDialog::showEvent(event);

    if(m_ipkpersons != -1)
    {
        auto person = CManager_birthday_reminder::GetPersonByID(m_ipkpersons);
        ui->lineEdit_surname->setText(person.strsurname);
        ui->lineEdit_forename->setText(person.strforename);
        ui->dateEdit->setDate(person.birthdate);
        m_bsaved = true;
        m_bedited = false;
    }

}
