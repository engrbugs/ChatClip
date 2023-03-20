// ChatClip.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include <algorithm>
#include <vector>

#include <map>
#include <optional>
#include <thread>

#include <mutex>

#include <Windows.h>

using namespace std;


const map<string, vector<string>> COMMANDS = {
    {"Cover Letter", {"cover", "c"}},
    {"Exit", {"exit", "x"}},
};

const string VER = "0.6b";


std::mutex io_mutex;
HWND hWndNextViewer;

LRESULT CALLBACK ClipboardViewerProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CLIPBOARDUPDATE:
        // Clipboard content has changed, do something here
        std::cout << "Clipboard content has changed." << std::endl;
        break;
    case WM_CHANGECBCHAIN:
        if ((HWND)wParam == hwnd) {
            // This window is being removed from the chain
            hWndNextViewer = (HWND)lParam;
        }
        else if (hWndNextViewer != NULL) {
            // Forward the message to the next window in the chain
            SendMessage(hWndNextViewer, uMsg, wParam, lParam);
        }
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}


void output_thread()
{
    HWND hwnd = CreateWindowEx(0, L"STATIC", L"", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);

    if (hwnd == NULL) {
        std::cerr << "Error creating message-only window." << std::endl;
        return ;
    }

    if (!AddClipboardFormatListener(hwnd)) {
        std::cerr << "Error registering clipboard viewer." << std::endl;
        return ;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_CLIPBOARDUPDATE) {
            // Clipboard content has changed, do something here
            std::cout << endl << "Clipboard content has changed." << std::endl;
            cout << "main: ";
        }

        if (msg.message == WM_DESTROY) {
            // Unregister the clipboard viewer and destroy the window
            RemoveClipboardFormatListener(hwnd);
            DestroyWindow(hwnd);
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}

int main()
{
    vector<string> triggers;

    cout << "List of commands: " << VER << endl;

    for (auto& x : COMMANDS) {
        cout << x.first << ": [" << x.second[1] << "]" << x.second[0] << endl;
        triggers.push_back(x.second[0]);
        triggers.push_back(x.second[1]);
    }
    string input_str;
    auto& it = *new vector<string>::iterator(triggers.end());

    std::thread t(output_thread);
    while (it == triggers.end()) {
        cout << "main: ";
        if (!getline(cin, input_str)) {
            // handle error or end-of-input
            return 1;
        }
        // process the input_str as needed
        it = find(triggers.begin(), triggers.end(), input_str);
    }
    // do something with it, e.g. print the matched string

    t.detach();
    delete& it;



    return 0;
}

//
//int main()
//{
//    std::thread t(output_thread);
//    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay for 1 second
//
//    while (true)
//    {
//        std::lock_guard<std::mutex> lock(io_mutex);
//        std::cout << "Enter input: ";
//        std::string input;
//        std::cin >> input;
//        std::cout << "You entered: " << input << std::endl;
//        std::this_thread::sleep_for(std::chrono::seconds(3)); // Delay for 1 second
//    }
//
//    return 0;
//}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
