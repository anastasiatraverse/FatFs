#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <QFileDialog>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QMessageBox>
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

void MainWindow::closeEvent(QCloseEvent *event){
    event->ignore();
    if(QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Exit?", QMessageBox::Yes | QMessageBox::No)){
        event->accept();
    }
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
            ui->statusbar->showMessage(file_name);
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
    QCoreApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_about_btn_clicked()
{
    about_win = new about(this);
    about_win->show();
}


