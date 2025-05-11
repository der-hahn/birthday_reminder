#ifndef CDIA_ADD_BIRTHDATE_H
#define CDIA_ADD_BIRTHDATE_H

#include <QMainWindow>
#include "cmanager_birthday_reminder.h"

namespace Ui {
class CDIA_ADD_BIRTHDATE;
}

class CDIA_ADD_BIRTHDATE : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDIA_ADD_BIRTHDATE(QWidget *parent = nullptr, CManager_birthday_reminder* pmanager_birthday_reminder = NULL);
    ~CDIA_ADD_BIRTHDATE();
    bool m_bsaved;
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_clicked();

private:
    Ui::CDIA_ADD_BIRTHDATE *ui;
signals:

    void CloseSignal();

};

#endif // CDIA_ADD_BIRTHDATE_H
