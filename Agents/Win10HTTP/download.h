#include <windows.h>
#include <iostream>
#include <string.h>
#include <wininet.h>
#include <fstream>

#pragma comment (lib, "wininet.lib")    

using namespace std;

bool downloadFile(const char* url, const char* filePath) {
    HINTERNET hInternet = InternetOpenA("DownloadFile", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "Error al abrir la sesión de Internet" << std::endl;
        return false;
    }

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        std::cerr << "Error al abrir la URL" << std::endl;
        InternetCloseHandle(hInternet);
        return false;
    }

    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error al crear el archivo local" << std::endl;
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return false;
    }

    DWORD bytesRead = 0;
    CHAR buffer[4096];

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        file.write(buffer, bytesRead);
    }

    file.close();
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return true;
}
    