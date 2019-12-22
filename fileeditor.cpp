#include "fileeditor.h"
#include "ui_fileeditor.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

//#include "mainwindow.h"

FileEditor::FileEditor(QWidget *parent) : QMainWindow(parent),ui(new Ui::FileEditor)
{
    ui->setupUi(this);
}

FileEditor::~FileEditor()
{
    delete ui;
}
