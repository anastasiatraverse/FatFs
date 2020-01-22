#include "root_dir.h"
#include "ui_root_dir.h"
#include "fileeditor.h"

#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> boot_vector;
std::vector<std::string> root_entr;

root_dir::root_dir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::root_dir)
{
    ui->setupUi(this);
    FileEditor fileEditor_win;
    boot_vector = fileEditor_win.return_boot_info();
    root_entr = fileEditor_win.root_entries();
    std::string label_output;
    for(auto element:root_entr){
        label_output += element;
        label_output += "\n";
    }
    ui->label_entries->setText(QString::fromStdString(label_output));
    display_info();
}

void root_dir::display_info(){

    int start_root_area = 512*std::stoi(boot_vector[2])+512*std::stoi(boot_vector[3]);
    int start_root_sector = std::stoi(boot_vector[2])+std::stoi(boot_vector[6])*std::stoi(boot_vector[3]);
    ui->label_2->setText(QString::fromStdString("Root Directory Start Byte:   "+std::to_string(start_root_area)+"\n"
                                                + "Root Directory Start Sector: "+std::to_string(start_root_sector+1)+"\n"
                                                + "Root Sector Size (in bytes):        "+std::to_string(std::stoi(boot_vector[4]))+"\n"));
}



root_dir::~root_dir()
{
    delete ui;
}

void root_dir::on_description_btn_clicked()
{
    hide();
    about_win = new about(this);
    about_win->show();
}
