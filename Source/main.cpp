#include "pipes.h"

#include <QApplication>
#include <windows.h>
#include<QMessageBox>
bool IsProcessRunAsAdmin()
{
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    BOOL b = AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &AdministratorsGroup);
    if(b)
    {
        CheckTokenMembership(NULL, AdministratorsGroup, &b);
        FreeSid(AdministratorsGroup);
    }
    return b == TRUE;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!IsProcessRunAsAdmin()){
        QMessageBox::warning(NULL,QString::fromUtf8("权限"),QString::fromUtf8("请以管理员权限运行程序"));
    }
    else{
        Pipes w;
        w.show();
        return a.exec();
    }
}
