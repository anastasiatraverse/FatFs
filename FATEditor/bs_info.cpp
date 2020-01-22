#include "bs_info.h"
#include "ui_bs_info.h"
#include "fileeditor.h"

#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> boot_info;

bs_info::bs_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bs_info)
{
    FileEditor file_edit;
    boot_info = file_edit.return_boot_info();
    ui->setupUi(this);
    display_info();
}

bs_info::~bs_info()
{
    delete ui;
}

void bs_info::on_description_dtn_clicked()
{
    hide();
    about_win = new about(this);
    about_win -> show();
}

void bs_info::display_info(){
    ui->info->setText(QString::fromStdString("Bytes Per Sector:                               "+boot_info[0]+"\n"+
                                             "Sector Per Cluster:                             "+boot_info[1]+"\n"+
                                              "Size of reserved area:                         "+boot_info[2]+"\n"+
                                              "Number of FATs:                                "+boot_info[3]+"\n"+
                                              "Maximum number of files in the root directory: "+boot_info[4]+"\n"+
                                              "Number of sectors:                             "+boot_info[5]+"\n"+
                                              "Size of each FAT:                              "+boot_info[6]+"\n"));
}
