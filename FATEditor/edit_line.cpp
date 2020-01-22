#include "edit_line.h"
#include "ui_edit_line.h"
#include "fileeditor.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QCloseEvent>
#include <QFile>

int line;
int sector_num;
std::string start;
std::string end;
std::vector<unsigned char> end_vector;

edit_line::edit_line(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_line)
{
    ui->setupUi(this);
    FileEditor fileEditor_win;
    line = fileEditor_win.return_curr_row();
    std::cout<<line<<std::endl;
    get_line();
}

void edit_line::get_line(){
    FileEditor fileEditor_win;
    start= fileEditor_win.return_string_line();
    ui->lineEdit->setText(QString::fromStdString(start));
}


bool edit_line::find_changes(){
    QString qend = ui->lineEdit->text();
    end = qend.toStdString();
    int x = end.compare(start);
    if(x!=0){
        return true;
    }
    else{
        return false;
    }
}

edit_line::~edit_line()
{
    delete ui;
}

void edit_line::convert_to_hex(std::string s){
    unsigned int c;
    std::istringstream hex(s);
    while(hex>>std::hex>>c)end_vector.push_back(c);
}

std::vector<std::string> edit_line::get_sector(std::string file, int sector){
    std::vector<std::string> res;
    std::ifstream file_in(file, std::ios::binary);
    file_in>>std::noskipws;
    file_in.seekg(512*sector);
    for(int i=0;i<512;i++){
       unsigned char x;
       file_in>>x;
       std::stringstream file_read;
       file_read<<std::hex<<static_cast<int>(x);
       if(file_read.str().length()==1) res.push_back("0"+file_read.str());
       else res.push_back(file_read.str());
    }
    return res;
}

std::vector<std::string> edit_line::read_before_after(std::string file_name, int k, int j){
    std::vector<std::string> res;
    std::ifstream file_in(file_name, std::ios::binary);
    file_in>>std::noskipws;
    file_in.seekg(k);
    for(int i=0;i<j;i++){
       unsigned char x;
       file_in>>x;
       std::stringstream file_read;
       file_read<<std::hex<<static_cast<int>(x);
       if(file_read.str().length()==1) res.push_back("0"+file_read.str());
       else res.push_back(file_read.str());
    }
    return res;
}

void edit_line::save_change(){
    FileEditor fileEditor_win;
    int sector = fileEditor_win.get_curr_sector();
    int all_bytes = fileEditor_win.return_all_bytes();
    std::string file = fileEditor_win.get_filename();
    std::vector<std::string> all_sector = get_sector(file, sector);


    if(sector==0){
        convert_to_hex(end);
        std::vector<std::string> read_after = read_before_after(file, 512, all_bytes);
        for(auto el:read_after)convert_to_hex(el);
    }
    else{
        std::vector<std::string> read_before = read_before_after(file, 0, sector);
        for(auto el:read_before)convert_to_hex(el);
        convert_to_hex(end);
        std::vector<std::string> read_after = read_before_after(file, sector, all_bytes);
        for(auto el:read_after)convert_to_hex(el);
    }

    QString file_name = QFileDialog::getSaveFileName(this, "Save file as ...");
    std::ofstream file_out(file_name.toStdString());
    for(auto el:end_vector)
        file_out<<el;
}

void edit_line::on_pushButton_clicked()
{
    bool change = find_changes();
    if(change) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Save?" ,"Do you want save file?", QMessageBox::Discard|QMessageBox::Cancel|QMessageBox::Save);
    }
    hide();
}

std::string edit_line::get_edited_line(){
    return end;
}
