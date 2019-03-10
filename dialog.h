#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QTimer>
#include"windows.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private:
    Ui::Dialog *ui;
    QTimer *getinfotimer;
    bool flag;
    HWND hwnd;
    HANDLE handle;
    DWORD lppid;
    int height;
    int width;
    int number;
private slots:
    void getinfopro();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // DIALOG_H
