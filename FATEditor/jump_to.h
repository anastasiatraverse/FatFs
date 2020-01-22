#ifndef JUMP_TO_H
#define JUMP_TO_H

#include <QDialog>

namespace Ui {
class jump_to;
}

class jump_to : public QDialog
{
    Q_OBJECT

public:
    explicit jump_to(QWidget *parent = nullptr);
    ~jump_to();

private slots:
    void on_close_btn_clicked();

    void on_jump_sector_btn_clicked();

    void on_jump_bs_btn_clicked();

    void on_jump_fat_btn_clicked();

    void on_jump_rootdir_btn_clicked();

private:
    Ui::jump_to *ui;
};

#endif // JUMP_TO_H
