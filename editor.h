#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>

namespace Ui {
class Editor;
}

class Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

private slots:
    void on_pushButton_clicked();
    void read_file(QString file_name);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();

private:
    Ui::Editor *ui;
};

#endif // EDITOR_H
