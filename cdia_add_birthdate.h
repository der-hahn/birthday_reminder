#ifndef CDIA_ADD_BIRTHDATE_H
#define CDIA_ADD_BIRTHDATE_H

#include <QDialog>
#include "cmanager_birthday_reminder.h"
#include <QCloseEvent>

namespace Ui {
class CDIA_ADD_BIRTHDATE;
}

class CDIA_ADD_BIRTHDATE : public QDialog
{
    Q_OBJECT

public:
    explicit CDIA_ADD_BIRTHDATE(QWidget *parent = nullptr, CManager_birthday_reminder* pmanager_birthday_reminder = NULL);
    ~CDIA_ADD_BIRTHDATE();

    bool IsSaved(){return m_bsaved;}

    void SetPKPersons(int ipkpersons){m_ipkpersons = ipkpersons;}

    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
protected slots:
    void reject();
private slots:
    void on_pushButton_clicked();

    void on_lineEdit_surname_textChanged(const QString &arg1);

    void on_lineEdit_forename_textChanged(const QString &arg1);

    void on_dateEdit_dateChanged(const QDate &date);

private:
    Ui::CDIA_ADD_BIRTHDATE *ui;
    bool m_bsaved;

    int m_ipkpersons;

};

#endif // CDIA_ADD_BIRTHDATE_H
