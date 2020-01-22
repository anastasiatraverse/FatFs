#ifndef BS_INFO_H
#define BS_INFO_H

#include <QDialog>
#include "about.h"

namespace Ui {
class bs_info;
}

class bs_info : public QDialog
{
    Q_OBJECT

public:
    explicit bs_info(QWidget *parent = nullptr);
    ~bs_info();

private slots:
    void on_description_dtn_clicked();
    void display_info();

private:
    Ui::bs_info *ui;
    about *about_win;
};

#endif // BS_INFO_H
