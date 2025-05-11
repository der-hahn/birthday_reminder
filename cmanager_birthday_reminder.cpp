#include "cmanager_birthday_reminder.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

CManager_birthday_reminder::CManager_birthday_reminder()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("birthdays.db");
    bool b_ok = m_db.open();
    if(!b_ok)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("Error Opening Database");
        msgbox.setText(m_db.lastError().text());
        msgbox.exec();
    }

    QString strSQL = "create table IF NOT EXISTS persons("
                     " ID INTEGER PRIMARY KEY, "
                     " SURNAME VARCHAR(50), "
                     " FORENAME VARCHAR(50), "
                     " BIRTHDATE DATE)";

    QSqlQuery query;
    b_ok = query.exec(strSQL);
    if(!b_ok)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("Error");
        msgbox.setText("Error Creating Table\n" + query.lastError().text());
        msgbox.exec();
    }
}

CManager_birthday_reminder::~CManager_birthday_reminder()
{
    m_db.close();
}

void CManager_birthday_reminder::FillvecPerson()
{

    m_vecPerson.clear();
    QString strSQL = "select ID, SURNAME, FORENAME, BIRTHDATE, (julianday('now') - julianday(BIRTHDATE))/365 AGE from Persons";

    QSqlQuery query(strSQL);

    bool b_ok = query.exec(strSQL);

    if(!b_ok)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("Error");
        msgbox.setText("Error select from Persons\n" + query.lastError().text());
        msgbox.exec();
    }

    while (query.next()) {
        structperson person;
        person.iid = query.value("ID").toInt();
        person.strsurname = query.value("SURNAME").toString();
        person.strforename = query.value("FORENAME").toString();
        person.birthdate = query.value("BIRTHDATE").toDate();
        person.iage = query.value("AGE").toInt();

        m_vecPerson.push_back(person);
    }
}
