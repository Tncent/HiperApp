#include "pipes.h"
#include "ui_pipes.h"
#define G2U QString::fromUtf8
#include<string>
using namespace std;
Pipes::Pipes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pipes)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setAttribute(Qt::WA_NoBackground, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    ui->textEdit_2->setAlignment( Qt::AlignCenter|Qt::AlignBottom|Qt::AlignHCenter );
}

Pipes::~Pipes()
{
    delete ui;
}
TCHAR * CTT(const char * _char) {

    TCHAR tszWord[1024] = { 0 };
#ifdef UNICODE
    MultiByteToWideChar(CP_ACP, 0, _char, -1, tszWord, 1024);
#else
    strcpy(tszWord, szWord);
#endif
}
HANDLE Pipes::StartProcess(LPCTSTR program, LPCTSTR args,std::string ass_dark){
    //LPCTSTR _program = L"C:\\users\\administrator\\desktop\\catogui\\cato.exe -auth.token 7173092E077A467ACFD7";
    //LPCTSTR _args = L"7173092E077A467ACFD7";

    hProcess = NULL;
    PROCESS_INFORMATION processInfo;
    STARTUPINFO startupInfo;
    ::ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    //TCHAR * szPath = { L"C:\\users\\administrator\\desktop\\catogui\\cato.exe " L" -auth.token " L" 7173092E077A467ACFD7" };
    //string c = "C:\\users\\administrator\\desktop\\catogui\\cato.exe  -auth.token  7173092E077A467ACFD7";

    TCHAR * szP = CTT(ass_dark.c_str());
    if (::CreateProcess(program, szP,
        NULL,  // process security
        NULL,  // thread security
        FALSE, // no inheritance
        0,     // no startup flags
        NULL,  // no special environment
        NULL,  // default startup directory
        &startupInfo,
        &processInfo)) {
        hProcess = processInfo.hProcess;
        return hProcess;
    }
}

bool Pipes::FindProcess(std::string strProcessName) {
    DWORD nPid;
    TCHAR tszProcess[64] = { 0 };
    lstrcpy(tszProcess, (LPCWSTR)(strProcessName.c_str()));
    //查找进程
    STARTUPINFO st;
    PROCESS_INFORMATION pi;
    PROCESSENTRY32 ps;
    HANDLE hSnapshot;
    memset(&st, 0, sizeof(STARTUPINFO));
    st.cb = sizeof(STARTUPINFO);
    memset(&ps, 0, sizeof(PROCESSENTRY32));
    ps.dwSize = sizeof(PROCESSENTRY32);
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    // 遍历进程
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;
    if (!Process32First(hSnapshot, &ps))
        return false;
    do {
        if (lstrcmp(ps.szExeFile, tszProcess) == 0) {
            //找到制定的程序
            nPid = ps.th32ProcessID;
            CloseHandle(hSnapshot);
//            printf("找到进程: %s\n", tszProcess);
            return true;
            //getchar();
            //return dwPid;
        }
    } while (Process32Next(hSnapshot, &ps));
    CloseHandle(hSnapshot);
    return false;
}


void Pipes::mousePressEvent(QMouseEvent *event)
{
    //如果是鼠标左键按下
    if(event->button()==Qt::LeftButton)
    {
        m_moving=true; //当前窗口被鼠标单击选中
        m_lastPos=event->globalPos()-pos();//记录下鼠标相对于当前窗口的位置
    }
    return QMainWindow::mouseMoveEvent(event);
}
void Pipes::mouseMoveEvent(QMouseEvent *event)
{
    //当前窗口被选中&&鼠标左键被按下&&鼠标移动的位置大于鼠标一开始选中的位置
    if(m_moving && (event->buttons()&&Qt::LeftButton) &&
    (event->globalPos()-m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-m_lastPos); //窗口移动到参数所给的位置
        m_lastPos=event->globalPos()-pos();//更新移动后鼠标相对于当前窗口的位置
    }
    return QMainWindow::mouseMoveEvent(event);
}
void Pipes::mouseReleaseEvent(QMouseEvent *event)
{
    m_moving=false; //当前鼠标没有按下并且不移动
}
void Pipes::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void Pipes::on_toolButton_clicked() //虚拟网卡
{
//    SECURITY_ATTRIBUTES sa;                //保存设定管道的安全属性
//    HANDLE hRead,hWrite;

//    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
//    sa.lpSecurityDescriptor = NULL;        //安全描述符
//    sa.bInheritHandle = TRUE;              //安全描述的对象能否被新创建的进程继承

//    CreatePipe(&hRead,&hWrite,&sa,0); //创建一个匿名管道

//    STARTUPINFO si;             //用于指定新进程的主窗口特性的一个结构
//    PROCESS_INFORMATION pi;     //构返回有关新进程及其主线程的信息
//    si.cb = sizeof(STARTUPINFO);//包含STARTUPINFO结构中的字节数.如果Microsoft将来扩展该结构,它可用作版本控制手段
//    GetStartupInfo(&si);        //取得进程在启动时被指定的 STARTUPINFO 结构

//    //hWrite为匿名管理写入句柄
//    si.hStdError = hWrite;     //错误输出写入匿名管道
//    si.hStdOutput = hWrite;    //标准输出写入匿名管道
//    //si.hStdInput             //标准输入,这里没用到
////    si.wShowWindow = SW_HIDE;  //隐藏窗口

//    si.dwFlags = STARTF_USESHOWWINDOW | //使用wShowWindow 成员(用于隐藏窗口)
//                 STARTF_USESTDHANDLES;  //使用hStdInput 、hStdOutput和hStdError成员(重定向到匿名管道)
//    CreateProcess(NULL,L"C:\\Users\\Administrator\\Desktop\\guchi.exe"/*"C:\\windows\\system32\\tasklist"*///创建进程
//                       ,NULL,NULL,TRUE,(DWORD)NULL,NULL,NULL,&si,&pi);
//    CloseHandle(hWrite);     //关闭匿名管道写入

//    //char str[40960] = {0};
//    char buffer[40960] = {0}; //用于保存输出信息
//    DWORD bytesRead;
////    printf("################################################################################\n");
//    while (TRUE)
//    {
//        if (!ReadFile(hRead,buffer,4095,&bytesRead,NULL))//读取匿名管道信息
//            break;
//        //strcpy(str,buffer);
//        printf("%s\n",buffer);
//    }
//    //printf("%s\n",str);
//    CloseHandle(hRead);
//    STARTUPINFO si = {sizeof(si)};
//    PROCESS_INFORMATION pi ;
//    TCHAR szCommandLine[] = TEXT("windows-tap\\tap_install.exe install OemVista.inf tap0901") ;
//    CreateProcess(NULL,szCommandLine,NULL,NULL,TRUE,(DWORD)NULL,NULL,NULL,&si,&pi);
//    BOOL fIsRunAsAdmin = FALSE;
//    PSID pAdministratorsGroup = NULL;
//    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
//    AllocateAndInitializeSid(
//            &NtAuthority,
//            2,
//            SECURITY_BUILTIN_DOMAIN_RID,
//            DOMAIN_ALIAS_RID_ADMINS,
//            0, 0, 0, 0, 0, 0,
//            &pAdministratorsGroup);

//    if(CheckTokenMembership(NULL,pAdministratorsGroup,&fIsRunAsAdmin))
//        STARTUPINFO si; //一些必备参数设置
//        memset(&si, 0, sizeof(STARTUPINFO));
//        si.cb = sizeof(STARTUPINFO);
//        si.dwFlags = STARTF_USESHOWWINDOW;
//        si.wShowWindow = SW_HIDE;
//        PROCESS_INFORMATION pi; //必备参数设置结束

//        if (!CreateProcess(NULL,(LPWSTR)L"windows-tap\\tap_install.exe install windows-tap\\OemVista.inf tap0901 && pause",NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)){
//            QMessageBox::warning(this,G2U("启动失败"),G2U("请检查或重启程序"));
//        }
//    StartProcess(L"Hiper.exe",L"","windows-tap\\tap_install.exe install windows-tap\\OemVista.inf tap0901");



        system("start cmd /C windows-tap\\tap_install.exe install windows-tap\\OemVista.inf tap0901");

//    else QMessageBox::information(this,G2U("权限"),G2U("如需安装虚拟驱动，请使本程序处于管理员模式下"));
}

#include <QInputDialog>
void Pipes::on_toolButton_2_clicked() // system("") 2 createprocess(null,"")
{
    if(!FindProcess("Hiper.exe")){
        system("start cmd /C taskkill /f /im Hiper.exe");
        bool ret=false;
        QString PassWord = QInputDialog::getText(this,G2U("凭证"),G2U("在这里输入你的凭证"),QLineEdit::Password,NULL,&ret);
        if(ret && !PassWord.isEmpty()){
            string CmdLine="start cmd /C Hiper v -t ";
            CmdLine.insert(CmdLine.length(),PassWord.toStdString());


    //        STARTUPINFO si; //一些必备参数设置
    //        memset(&si, 0, sizeof(STARTUPINFO));
    //        si.cb = sizeof(STARTUPINFO);
    //        si.dwFlags = STARTF_USESHOWWINDOW;
    //        si.wShowWindow = SW_HIDE;
    //        PROCESS_INFORMATION pi; //必备参数设置结束

    //        if (!CreateProcess(NULL,(LPWSTR)QString::fromStdString(CmdLine).utf16(),NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)){
    //            QMessageBox::warning(this,G2U("启动失败"),G2U("请检查或重启程序"));
    //        }

            system(CmdLine.c_str());
        }
    }
    else{
        if(QMessageBox::information(this,G2U("运行中"),G2U("当前已运行一个Hiper\n是否重新启动?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
            system("start cmd /C taskkill /f /im Hiper.exe");
            bool ret=false;
            QString PassWord = QInputDialog::getText(this,G2U("凭证"),G2U("在这里输入你的凭证"),QLineEdit::Password,NULL,&ret);
            if(ret && !PassWord.isEmpty()){
                string CmdLine="start cmd /C Hiper v -t ";
                CmdLine.insert(CmdLine.length(),PassWord.toStdString());
                system(CmdLine.c_str());
            }
        }
    }
}


void Pipes::on_pushButton_clicked()
{
    if(QMessageBox::warning(this,QString::fromUtf8("提示"),QString::fromUtf8("真的要退出吗?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
        system("start cmd /C taskkill /f /im Hiper.exe");
        this->close();
    }
}


void Pipes::on_toolButton_3_clicked()
{
   bool HiperActive = FindProcess("Hiper.exe");
   if(!HiperActive && QMessageBox::information(this,G2U("提示"),G2U("此选项将使你在线30分钟，结束需要重新启动"),QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes){
       system("start cmd /C taskkill /f /im Hiper.exe");
       STARTUPINFO si; //一些必备参数设置
       memset(&si, 0, sizeof(STARTUPINFO));
       si.cb = sizeof(STARTUPINFO);
       si.dwFlags = STARTF_USESHOWWINDOW;
       si.wShowWindow = SW_HIDE;
       PROCESS_INFORMATION pi; //必备参数设置结束

//       if (!CreateProcess(NULL,(LPWSTR)L"Hiper v",NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)){
//           QMessageBox::warning(this,G2U("启动失败"),G2U("请检查或重启程序"));
//       }
       system("start cmd /C Hiper v");
   }
   else if(HiperActive &&QMessageBox::information(this,G2U("运行中"),G2U("当前已运行一个Hiper\n是否重新启动?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
        system("start cmd /C taskkill /f /im Hiper.exe");
        system("start cmd /C Hiper v");
   }
}

#include<QDesktopServices>
void Pipes::on_toolButton_4_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://mcer.cn/shop")));
}


void Pipes::on_toolButton_5_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://mcer.cn/463.html")));
}


void Pipes::on_pushButton_2_clicked()
{
    if(QMessageBox::information(this,G2U("运行"),G2U("此举动将关闭正在运行的Hiper\n您会断开与社区的联系"),QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
        system("start cmd /C taskkill /f /im Hiper.exe");
    }
}

