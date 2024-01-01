#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <urlmon.h>
#include <Wininet.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Wininet.lib")

using namespace std;

void setColorAndStyle(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

bool checkInternetConnection() {
    DWORD dwFlag;
    if (!InternetGetConnectedState(&dwFlag, 0)) {
        return false;
    }
    return true;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleTitle("Geometry Dash - NoParticles | by vepexlegit");

    setColorAndStyle(10);
    cout << "/////////////////////////////////" << endl;
    cout << "//     ";
    setColorAndStyle(14);
    cout << "Geometry Dash v2.2";
    setColorAndStyle(10);
    cout << "       //" << endl;
    cout << "/////////////////////////////////" << endl;

    setColorAndStyle(11);
    cout << endl << "Введите путь к игре Geometry Dash: ";
    setColorAndStyle(7);

    string gamePath;
    getline(cin, gamePath);

    string resourcesPath = gamePath + "\\Resources\\";

    DWORD attributes = GetFileAttributes(resourcesPath.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES || !(attributes & FILE_ATTRIBUTE_DIRECTORY)) {
        cout << "Папки Resources нет" << endl;
        return 1;
    }

    if (!checkInternetConnection()) {
        cout << "Нет подключения к интернету" << endl;
        return 1;
    }

    string urls[] = {
        "https://i.ibb.co/m4y1nq9/square.png",
        "https://i.ibb.co/m4y1nq9/streak_01_001.png",
        "https://i.ibb.co/m4y1nq9/streak_02_001.png",
        "https://i.ibb.co/m4y1nq9/streak_03_001.png",
        "https://i.ibb.co/m4y1nq9/streak_04_001.png",
        "https://i.ibb.co/m4y1nq9/streak_05_001.png",
        "https://i.ibb.co/m4y1nq9/streak_06_001.png",
        "https://i.ibb.co/m4y1nq9/streak_07_001.png",
        "https://i.ibb.co/m4y1nq9/streakb_01_001.png",
        "https://i.ibb.co/m4y1nq9/streakDWhite.png"
    };

    for (const string& url : urls) {
        string filename = url.substr(url.find_last_of("/\\") + 1);
        string filePath = resourcesPath + filename;

        HRESULT hr = URLDownloadToFile(NULL, url.c_str(), filePath.c_str(), 0, NULL);
        if (SUCCEEDED(hr)) {
            setColorAndStyle(10);
            cout << "Файл ";
            setColorAndStyle(14);
            cout << filename;
            setColorAndStyle(10);
            cout << " - Успешно изменён!" << endl;
        }
        else {
            setColorAndStyle(12);
            cout << "Не удалось загрузить файл: " << filename << endl;
        }
        setColorAndStyle(7);
    }

    cout << endl;
    setColorAndStyle(10);
    cout << "Успешно!" << endl;
    setColorAndStyle(7);
    Sleep(3000);

    return 0;
}
