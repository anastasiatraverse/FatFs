#ifndef EDIT_LINE_H
#define EDIT_LINE_H

#include <QDialog>

namespace Ui {
class edit_line;
}

class edit_line : public QDialog
{
    Q_OBJECT

public:
    explicit edit_line(QWidget *parent = nullptr);
    ~edit_line();
    void get_line();
    bool find_changes();
    void save_change();
    void convert_to_hex(std::string s);
    std::vector<std::string> get_sector(std::string file,int sector);
    std::vector<std::string> read_before_after(std::string file_name, int k, int j);
    std::string get_edited_line();

private slots:
    void on_pushButton_clicked();

private:
    Ui::edit_line *ui;
};

#endif // EDIT_LINE_H
