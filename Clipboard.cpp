#include <Windows.h>
#include <iostream>
#include <string>

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
void create_a_Prompt()
{
    string prompt = "";
    int index_for_clipBoards = 0;
    for (int i = 0; i <= prompt_Lines.size() - 1; i++)
    {
        bool exists = std::find(before_Locs.begin(), before_Locs.end(), i) != before_Locs.end();
        if (exists)
        {
            prompt += clipBoards[index_for_clipBoards];
            index_for_clipBoards += 1;
        }
        prompt += prompt_Lines[i];
    }
    Set_clipboard_text(prompt);
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

                // clipBoards_indes is zero-indexed.
                clipBoards[clipBoards_index] = Get_clipboard_text();
                if (clipBoards_index >= clipBoards.size() - 1)
                    clipBoards_index = 0;
                else
                    clipBoards_index += 1;
                // zero-indexed
                
                create_a_Prompt();
                //Set_clipboard_text("LLLL\nLLLL");
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

// this will be dirty: this file is meant for clipboards commands only, for future usage.

