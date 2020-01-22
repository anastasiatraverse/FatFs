#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include <QMainWindow>
#include "bs_info.h"
#include "root_dir.h"
#include "jump_to.h"
#include "edit_line.h"


namespace Ui {
class FileEditor;
}

class FileEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileEditor(QWidget *parent = nullptr);
    ~FileEditor();
    int return_curr_row();
    int get_curr_sector();
    int return_all_bytes();
    std::string return_string_line();
    std::string get_filename();
    std::vector<std::string> root_entries();
    std::vector<std::string> return_boot_info();
    void read_boot_sector();
    void display_numsector();
    void display_sector();
    void setOffset(int i, int j);
    void setSectorNum(int sector);
    void setOffsetNum(std::string offset);
    std::string file_info(std::vector<std::string> v);


private slots:
    //buttons
    void on_open_file_btn_clicked();
    void on_pushButton_clicked();
    void on_save_as_btn_clicked();
//    void closeEvent(QCloseEvent *event);
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();
    void on_pushButton_bs_clicked();
    void on_pushButton_close_clicked();
    void on_jmp_to_btn_clicked();
    void on_pushButton_catalog_clicked();

    //utils
    int get_hex_data_to_int1(int i, std::vector<std::string>v);
    int get_hex_data_to_int2(int i, int j, std::vector<std::string> v);
    std::string convert_to_string(std::string hex);
    std::string conver_int_hex(int i);
    void on_refresh_btn_clicked();
    void on_edit_catalog_btn_2_clicked();

private:
    Ui::FileEditor *ui;
    bs_info *bs_win;
    root_dir *root_win;
    jump_to *jump_win;
    edit_line *edit_line_win;
};

#endif // FILEEDITOR_H
