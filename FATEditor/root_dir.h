#ifndef ROOT_DIR_H
#define ROOT_DIR_H

#include <QDialog>
#include "about.h"

namespace Ui {
class root_dir;
}

class root_dir : public QDialog
{
    Q_OBJECT

public:
    explicit root_dir(QWidget *parent = nullptr);
    ~root_dir();
    void display_info();

private slots:
    void on_description_btn_clicked();

private:
    Ui::root_dir *ui;
    about *about_win;
};

#endif // ROOT_DIR_H
