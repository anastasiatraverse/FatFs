#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fileeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString return_file_name();

private slots:
    void on_pushButton_clicked();
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    FileEditor *window_ed;
};
#endif // MAINWINDOW_H
