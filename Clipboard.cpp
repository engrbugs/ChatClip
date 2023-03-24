#include <Windows.h>
#include <iostream>
#include "Common.h"

using namespace std;
HWND hWndNextViewer;

bool processed_clipboard_update = false; // Initialize flag to false

string Get_clipboard_text() {
    string text = "";
    // Try opning the clipboard
    if (!OpenClipboard(nullptr))
    {
    }
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData != nullptr)
    {
        char* pszText = static_cast<char*>(GlobalLock(hData));
        if (pszText != nullptr)
        {
            // Save text in a string class instance
            text = pszText;
        }
    }
    // Release the lock
    GlobalUnlock(hData);

    // Release the clipboard
    CloseClipboard();
    return text;
}


void Set_clipboard_text(string str) {
    if (OpenClipboard(nullptr)) {
        EmptyClipboard();
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1);
        if (hMem != nullptr) {
            LPSTR pMem = static_cast<LPSTR>(GlobalLock(hMem));
            if (pMem != nullptr) {
                memcpy(pMem, str.c_str(), str.size() + 1);
                GlobalUnlock(hMem);
                SetClipboardData(CF_TEXT, hMem);
            }
        }
        CloseClipboard();
    }
}

void Check_clipboard_update() {
    HWND hwnd = CreateWindowEx(0, L"STATIC", L"", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
    std::atomic<bool> stop_output_thread(false);

    if (hwnd == NULL) {
        std::cerr << "Error creating message-only window." << std::endl;
        return;
    }

    if (!AddClipboardFormatListener(hwnd)) {
        std::cerr << "Error registering clipboard viewer." << std::endl;
        return;
    }

    MSG msg;
    while (!stop_output_thread && GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_CLIPBOARDUPDATE) {
            if (!processed_clipboard_update) {
                // Clipboard content has changed, do something here
                std::cout << endl << "Clipboard content has changed." << endl;
                Get_clipboard_text();
                Set_clipboard_text("LLLL\nLLLL");
                cout << "main: ";

                processed_clipboard_update = true; // Set flag to true
            }
            else {
                // Skip processing the message
                processed_clipboard_update = false; // Reset flag for next update
            }
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    RemoveClipboardFormatListener(hwnd);
    DestroyWindow(hwnd);
}
