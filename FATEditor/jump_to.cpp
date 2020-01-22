#include "jump_to.h"
#include "ui_jump_to.h"
#include "fileeditor.h"

#include <iostream>
#include <string>
#include <QMessageBox>


jump_to::jump_to(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::jump_to)
{
    ui->setupUi(this);
}

jump_to::~jump_to()
{
    delete ui;
}

void jump_to::on_close_btn_clicked()
{
    hide();
}

void jump_to::on_jump_sector_btn_clicked()
{
    std::string sector = ui->line_sector->text().toStdString();
    if(sector.length()==0) QMessageBox::warning(this, "Sector number", "You should number of sector");
    else{
        std::cout<<"[Info] - Jump To Sector: "<< sector<<std::endl;
        FileEditor fileeditor_func;
        //call function from File Editor
        try{
            int sector_num = std::stoi(sector);
            fileeditor_func.setSectorNum(sector_num);
            hide();
        }
        catch (std::invalid_argument const &e){
                QMessageBox::warning(this, "Sector number", "Invalid number of sector");
        }
    }
}

int bootSector_id = 0;
int fatSector_id = 1;
int rootDir_id = 69;

void jump_to::on_jump_bs_btn_clicked()
{
    std::cout<<"[Info] - Jump to Boot Sector"<<std::endl;
    FileEditor fileeditor_func;
    fileeditor_func.setSectorNum(bootSector_id);
    hide();
}

void jump_to::on_jump_fat_btn_clicked()
{
    std::cout<<"[Info] - Jump to FAT Sector"<<std::endl;
    FileEditor fileeditor_func;
    fileeditor_func.setSectorNum(fatSector_id);
    hide();
}

void jump_to::on_jump_rootdir_btn_clicked()
{
    std::cout<<"[Info] - Jump to Root Directory Sector"<<std::endl;
    FileEditor fileeditor_func;
    fileeditor_func.setSectorNum(fatSector_id);
    hide();
}
