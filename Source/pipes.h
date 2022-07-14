#ifndef PIPES_H
#define PIPES_H

#include <QMainWindow>
#include <QDialog>
#include <windows.h>
#include<QFile>
#include<QDir>
#include<QMessageBox>
#include<QDebug>
#include<QPainter>
#include<sstream>
#include<QMouseEvent>
#include<QProcess>
#include<QStyleOption>
#include<QWindow>
#include <TlHelp32.h>
#include<io.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Pipes; }
QT_END_NAMESPACE

class Pipes : public QMainWindow
{
    Q_OBJECT

public:
    Pipes(QWidget *parent = nullptr);
    ~Pipes();
    void paintEvent(QPaintEvent *event);
    HANDLE StartProcess(LPCTSTR program, LPCTSTR args,std::string ass_dark);
    bool FindProcess(std::string strProcessName);
    HANDLE hProcess;
    bool check(std::string filename);


private:
    Ui::Pipes *ui;
    bool m_moving =false;
    QPoint m_lastPos;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_pushButton_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_pushButton_2_clicked();
};
#endif // PIPES_H
