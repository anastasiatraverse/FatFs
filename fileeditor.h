#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
class FileEditor;
}

class FileEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileEditor(QWidget *parent = nullptr);
    ~FileEditor();

private:
    Ui::FileEditor *ui;
};

#endif // FILEEDITOR_H
