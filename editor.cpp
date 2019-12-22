#include "editor.h"
#include "ui_editor.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

#include "mainwindow.h"



Editor::Editor(QWidget *parent) : QDialog(parent), ui(new Ui::Editor)
{
    ui->setupUi(this);

    MainWindow m;
    QString file_name = m.return_file_name();
    ui->label->setText(file_name);
    read_file(file_name);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_pushButton_clicked()
{
    QMessageBox::information(this, "Button click", "Button 'EDIT' was clicked");
}

void Editor::read_file(QString file_name){
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Unable to open File", "File not open");
    }else{
        QTextStream file_in(&file);
        QString text = file_in.readAll();
        ui->textBrowser->setText(text);
        file.close();
    }
}

void Editor::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Button click", "Button 'OPEN' was clicked");
}

void Editor::on_pushButton_3_clicked()
{
    QMessageBox::information(this, "Button click", "Button 'CHECK' was clicked");
}

void Editor::on_pushButton_8_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }else{
        QTextStream file_out(&file);
        QString text = ui->textBrowser->toPlainText();
        file_out<< text;
        file.close();
    }
}
