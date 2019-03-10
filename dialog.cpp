#include "dialog.h"
#include "ui_dialog.h"
#include<QDebug>
#define rlong 16

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    getinfotimer=new QTimer(this);
    ui->pushButton->setEnabled(false);
    hwnd=FindWindow(L"扫雷",nullptr);
    GetWindowThreadProcessId(hwnd, &lppid);
    handle=OpenProcess( PROCESS_ALL_ACCESS, false,lppid);
    qDebug()<<handle;

    getinfotimer->start(500);
    connect(getinfotimer,SIGNAL(timeout()),this,SLOT(getinfopro()));
}
void Dialog::getinfopro()
{
    if(handle) ui->pushButton->setEnabled(true);
    ReadProcessMemory(handle,(LPVOID)0x10056A8,&height,4,NULL);
    ReadProcessMemory(handle,(LPVOID)0x10056AC,&width,4,NULL);
    ReadProcessMemory(handle,(LPVOID)0x1005194,&number,4,NULL);
    ui->label_4->setText(QString::number(height,10));
    ui->label_5->setText(QString::number(width,10));
    ui->label_6->setText(QString::number(number,10));
}
Dialog::~Dialog()
{
    CloseHandle(handle);
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    BYTE map[32*height];
    RECT rect;
    GetWindowRect(hwnd,&rect);
    //0x1005340+0x20*numer  map
    ReadProcessMemory(handle,(LPVOID)0x1005340+0x20,&map,32*height,NULL);
    SetCursorPos(rect.left+20,rect.top+110);
    mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
    Sleep(10);
    mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
    for(int i=0;i<height;i++)
    {
        for(int count=0;count<=width;count++)
        {
            if(!ui->checkBox->isChecked())
            {
            if(map[0x20*i+count]!=0x8f)
            {
               qDebug()<<QString::number(i,10)+','+QString::number(count,10);
               SetCursorPos(rect.left+20+(count-1)*rlong,rect.top+110+i*rlong);
               //Sleep(10);
               mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
               Sleep(1);
               mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
            }
            }
            else
            {
                if(map[0x20*i+count]==0x8f)
                {
                qDebug()<<QString::number(i,10)+','+QString::number(count,10);
                SetCursorPos(rect.left+20+(count-1)*rlong,rect.top+110+i*rlong);
                //Sleep(10);
                mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
                Sleep(1);
                mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
                }
            }

        }
    }
}
void Dialog::on_pushButton_2_clicked()
{
    hwnd=FindWindow(L"扫雷",nullptr);
    GetWindowThreadProcessId(hwnd, &lppid);
    handle=OpenProcess( PROCESS_ALL_ACCESS, false,lppid);
}
