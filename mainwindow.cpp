#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

QString file_name;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    file_name = QFileDialog::getOpenFileName(this, "Open a File");
    if(file_name.size() >0){
        ui->statusbar->showMessage(file_name);
        QFile file(file_name);
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){
            QMessageBox::warning(this, "Warning", "Cannot open file name: "+file.errorString());
        }else{
            hide();
            window_ed = new FileEditor(this);
            window_ed->show();
        }
    }
    else{
        ui->statusbar->showMessage("No file was choosed");
    }
}

QString MainWindow::return_file_name(){
    return file_name;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
