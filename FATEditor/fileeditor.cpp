#include "fileeditor.h"
#include "ui_fileeditor.h"
#include "mainwindow.h"
#include "bs_info.h"
#include "jump_to.h"
#include "root_dir.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QCloseEvent>
#include <QFile>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string file;
std::string sector_str;
std::string setted_offset;

int line_ind;
int sector_count=0;
int numSectorFS;
int bytesPerSector;
int all_bytes;
int root_dir_sector;
std::vector<std::string> boot_vect;
std::vector<std::string> all_vect;
std::vector<std::string> changes;


FileEditor::FileEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileEditor){
        MainWindow m;
        QString file_name = m.return_file_name();
        file = file_name.toStdString();
        ui->setupUi(this);

        ui->file_name_label->setText("Disk path: "+file_name);

        read_boot_sector();
        display_numsector();
        setOffset(0, 512);

}


void FileEditor::display_sector(){
    unsigned char x;
    std::vector<std::string> temp_vect;
    ui->hex_list->clear();

    std::ifstream file_in(file, std::ios::binary);
    file_in >> std::noskipws;
    file_in.seekg(bytesPerSector*sector_count);

    for(int i=0;i<bytesPerSector;i++){
       file_in>>x;
       std::stringstream file_read;
       file_read<<std::hex<<static_cast<int>(x);
       if(file_read.str().length()==1) temp_vect.push_back("0"+file_read.str() +" ");
       else temp_vect.push_back(file_read.str()+"");
    }

    for(int i=0;i<512;i+=16){
        std::string temp_str;
        for(int j=i;j<i+16;j++) {
            temp_str+=temp_vect[j];
            temp_str+="    ";
        }
        ui->hex_list->addItem(QString::fromStdString(temp_str));
    }

    sector_str="";
    for(auto el:temp_vect){
        sector_str+= convert_to_string(el);
    }

    ui->ascii_list->clear();

    for(int i=0;i<(int)sector_str.size();i+=16){
        std::string temp_str;
        for(int j=i;j<i+16;j++){
            temp_str+=sector_str[j];
        }
        ui->ascii_list->addItem(QString::fromStdString(temp_str));
    }
    display_numsector();
    setOffset(bytesPerSector*sector_count, bytesPerSector*sector_count+bytesPerSector);
}


void FileEditor::display_numsector(){
    std::string s = "Sector: "+std::to_string(sector_count+1)+"/"+std::to_string(numSectorFS);
    ui->label_sector->setText(QString::fromStdString(s));
}


void FileEditor::read_boot_sector()
{
    unsigned char x;
    std::ifstream file_in(file, std::ios::in|std::ios::binary);
    file_in>>std::noskipws;

    for(int i=0;i<512;i++){
        file_in>>x;
        std::stringstream file_read;
        file_read <<std::hex<<static_cast<int>(x);
        if(file_read.str().length()==1) boot_vect.push_back("0"+file_read.str());
        else boot_vect.push_back(file_read.str());
    }

    bytesPerSector = get_hex_data_to_int2(11,12, boot_vect);
    numSectorFS = get_hex_data_to_int2(19,20, boot_vect);
    all_bytes = bytesPerSector*numSectorFS;
    root_dir_sector = get_hex_data_to_int2(14, 15, boot_vect)+
                      get_hex_data_to_int2(22, 23, boot_vect)*
                      get_hex_data_to_int1(16, boot_vect);

    std::vector<std::string> sector_str_vect;
    for(auto el:boot_vect)sector_str_vect.push_back(convert_to_string(el));

    for(int i=0;i<512;i+=16){
        std::string temp_str;
        for(int j=i;j<i+16;j++) {
            temp_str+=boot_vect[j];
            temp_str+="    ";
        }
        ui->hex_list->addItem(QString::fromStdString(temp_str));
    }

    for(int i=0;i<(int)sector_str_vect.size();i+=16){
        std::string temp_str;
        for(int j=i;j<i+16;j++){
            temp_str+=sector_str_vect[j];
        }
        ui->ascii_list->addItem(QString::fromStdString(temp_str));
    }
}


//void FileEditor::closeEvent(QCloseEvent *event){
//    event->ignore();
//    QMessageBox::StandardButton reply = QMessageBox::question(this, "Close Confirmation", "Do you want save file?", QMessageBox::Discard| QMessageBox::Cancel|QMessageBox::Save);
//    if(QMessageBox::Discard == reply){
//        event->accept();
//    }else if(QMessageBox::Save == reply){
//        FileEditor::on_save_as_btn_clicked();
//    }
//}


void FileEditor::on_open_file_btn_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a File");
    if(file_name.size() >0){
        ui->statusbar->showMessage(file_name);
        QFile file_in(file_name);
        if(!file_in.open(QIODevice::ReadOnly | QFile::Text)){
            QMessageBox::warning(this, "Warning", "Cannot open file name: "+file_in.errorString());
        }else{
            file = file_name.toStdString();
            read_boot_sector();
        }
    }
    else{
        ui->statusbar->showMessage("No file was choosed");
    }
}


void FileEditor::on_pushButton_clicked()
{
//    QMessageBox::StandardButton reply =  QMessageBox::question(this, "EXIT", "Do you want save file?",QMessageBox::Discard|QMessageBox::Cancel|QMessageBox::Save);
//    if(reply == QMessageBox::Save){
//        ui->statusbar->showMessage("File Should Be saved");
//        FileEditor::on_save_as_btn_clicked();
//    }else if(reply == QMessageBox::Discard){
//        QCoreApplication::quit();
//    }
}


void FileEditor::on_save_as_btn_clicked()
{
//    QString file_name = QFileDialog::getSaveFileName(this, "Save file as ...");
//    QFile file(file_name);
//    if(!file.open(QFile::WriteOnly|QFile::Text)){
//        QMessageBox::warning(this, "Warning", "Cannot save file: "+file.errorString());
//        return;
//    }
//    QTextStream out(&file);
//    QString text = QString::fromStdString("hello world");
//    out<<text;
//    file.close();
}



void FileEditor::on_pushButton_up_clicked()
{
    if(sector_count>0){
        sector_count -=1;
        display_numsector();
        display_sector();
    }
}

void FileEditor::on_pushButton_down_clicked()
{
    if(sector_count<numSectorFS){
        sector_count +=1;
        display_numsector();
        display_sector();
    }
}

void FileEditor::on_pushButton_bs_clicked()
{
    std::cout<<"open bs"<<std::endl;
    bs_win = new bs_info(this);
    bs_win->show();
}

void FileEditor::on_pushButton_close_clicked()
{
    on_pushButton_clicked();
}

void FileEditor::on_jmp_to_btn_clicked()
{
    jump_win = new jump_to(this);
    jump_win->show();
}

void FileEditor::on_pushButton_catalog_clicked()
{
    root_win = new root_dir(this);
    root_win->show();
}

void FileEditor::on_edit_catalog_btn_2_clicked()
{
    line_ind = ui->hex_list->currentRow();
    edit_line_win = new edit_line(this);
    edit_line_win->show();
}


FileEditor::~FileEditor()
{
    delete ui;
}

// RETURN BOOT INFO FUNCTION
std::vector<std::string> FileEditor::return_boot_info(){
    std::vector<std::string> boot_info_vect;
    boot_info_vect.push_back(std::to_string(bytesPerSector));
    boot_info_vect.push_back(std::to_string(get_hex_data_to_int1(13, boot_vect)));//sectors per cluster
    boot_info_vect.push_back(std::to_string(get_hex_data_to_int2(14, 15, boot_vect)));//Size of reserved area
    boot_info_vect.push_back(std::to_string(get_hex_data_to_int1(16, boot_vect)));//number of fats
    boot_info_vect.push_back(std::to_string(get_hex_data_to_int2(17, 18, boot_vect)));//Maximum number of files in the root directory
    boot_info_vect.push_back(std::to_string(numSectorFS));//number of sectors
    boot_info_vect.push_back(std::to_string(get_hex_data_to_int2(22, 23, boot_vect)));//size of each fat
    return boot_info_vect;
}


//UTILS
int FileEditor::get_hex_data_to_int1(int i, std::vector<std::string>v){
    std::string data = "";
    data +=v[i];
    int num = stoi(data, 0, 16);
    return num;
}
int FileEditor::get_hex_data_to_int2(int i, int j, std::vector<std::string> v){
    std::string data = "";
    data+=v[j];
    data+=v[i];
    int num = stoi(data, 0, 16);
    return num;
}
std::string FileEditor::conver_int_hex(int i){
    std::stringstream data_stream;
    data_stream << std::hex << i;
    std::string result(data_stream.str());
    while(result.length()<10)
        result.insert(0, "0");
    return result;
}

std::string FileEditor::convert_to_string(std::string hex){
    int len = hex.length();
    std::string newString;
    for(int i=0; i<len; i+=2)
    {
        std::string byte = hex.substr(i,2);
        char chr = (char) (int)strtol(byte.c_str(), 0, 16);
        newString.push_back(chr);
    }
    if(isprint((unsigned)newString[0])) return newString;
    else return ".";
}


//SETTERS
void FileEditor::setSectorNum(int sector){
    sector_count = sector-1;
    display_sector();
}

void FileEditor::setOffsetNum(std::string offset){
    setted_offset = offset;
}

void FileEditor::setOffset(int i, int j){
    ui->offset_list->clear();
    for(;i<j;i+=16){
        std::string offset = conver_int_hex(i);
        ui->offset_list->addItem(QString::fromStdString(offset));
    }
}

std::string upd_line;
void FileEditor::on_refresh_btn_clicked()
{
    edit_line edit_line_point;
    upd_line = edit_line_point.get_edited_line();
    std::cout<<upd_line<<std::endl;
    display_sector();
}


int FileEditor::return_curr_row(){
    return line_ind+(sector_count*32);
}

int FileEditor::get_curr_sector(){
    return sector_count;
}

int FileEditor::return_all_bytes(){
    return all_bytes;
}

std::string FileEditor::get_filename(){
    return file;
}

std::string FileEditor::return_string_line(){
    unsigned char x;

    std::ifstream file_in(file, std::ios::binary);
    file_in >> std::noskipws;
    file_in.seekg((line_ind+(sector_count)*32)*16);

    std::string temp = "";

    for(int i=0;i<16;i++){
        file_in>>x;
        std::stringstream file_read;
        file_read <<std::hex<<static_cast<int>(x);
        if(file_read.str().length()==1) temp+="0"+file_read.str()+" ";
        else temp+=file_read.str()+" ";
    }

    return temp;
}

std::string FileEditor::file_info(std::vector<std::string> v){
    std::string s;
    std::string filename;
    std::string attr;
    for(int i=0;i<8;i++){
        filename += convert_to_string(v[i]);
    }
    for(int i=9;i<12;i++){
        attr += convert_to_string(v[i]);
    }
    s+=filename;
    s+=".";
    s+=attr;
    return s;
}

std::vector<std::string> FileEditor::root_entries(){
    std::vector<std::string> root_entries_v;
    unsigned char x;
    std::ifstream file_in(file, std::ios::binary);
    file_in >> std::noskipws;
    file_in.seekg(root_dir_sector*512);
    std::vector<std::string> temp;
    for(int i=0;i<512;i++){
        file_in>>x;
        std::stringstream file_read;
        file_read <<std::hex<<static_cast<int>(x);
        if(file_read.str().length()==1) temp.push_back("0"+file_read.str()+" ");
        else temp.push_back(file_read.str()+" ");
    }

    for(int i=0;i<512;i+=32){
        std::vector<std::string> v;
        for(int j=0; j<32;j++){
            v.push_back(temp[j+i]);
            v.push_back(temp[j+i+1]);
        }

        std::string f = file_info(v);
        root_entries_v.push_back(file_info(v));
   }


    return root_entries_v;
}

