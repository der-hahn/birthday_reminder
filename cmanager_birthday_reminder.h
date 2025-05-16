#ifndef CMANAGER_BIRTHDAY_REMINDER_H
#define CMANAGER_BIRTHDAY_REMINDER_H

#include <QtSql/QSqlDatabase>
#include <vector>
#include <QDate>

class CManager_birthday_reminder
{
public:
    CManager_birthday_reminder();
    ~CManager_birthday_reminder();

    typedef struct structpersontag
    {
        int iid = -1;
        QString strsurname = "";
        QString strforename = "";
        QDate birthdate;
        int iage = 0;

    } structperson;

    typedef std::vector<structperson> vecPerson;

    vecPerson* GetpvecPerson(){return &m_vecPerson;}
    void FillvecPerson();

    static structperson GetPersonByID(int ipkpersons);
private:
    QSqlDatabase m_db;
    vecPerson m_vecPerson;
};

#endif // CMANAGER_BIRTHDAY_REMINDER_H
