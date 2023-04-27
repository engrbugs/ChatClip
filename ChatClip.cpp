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

#include "Common.h"
#include "Filenames.h"
#include "Constant.h"


using namespace std;

// global variables
std::atomic<bool> stop_output_thread(false);

// clipBoards_indes is zero-indexed.
int clipBoards_index = 0;
vector<string> clipBoards;
vector<string> prompt_Lines;
vector<int> before_Locs;

void output_thread()
{
    Check_clipboard_update();
}

int main()
{
    //initialize clipBoards
    //vector<string> clipBoards;
    //for (int i = 0; i <= STACK_OF_CLIPBOARDS; i++) {
    //    clipBoards.push_back("");
    //}
    // 
    //clipboard monitoring thread boolean
 


    
    cout << "List of commands: " << VER << endl;
    for (int i = 1; i <= 9; ++i) {
        string str = "";

        // read for [Files] category 
        str = read_ini_string(ExePath() + FILES_TO_READ, "Files", to_string(i), "");
        if (!str.empty())
        {
            prompt_Lines.push_back(read_Text_file(ExePath() + "\\" + str));

        }
        // read for [Before] category 
        str = read_ini_string(ExePath() + FILES_TO_READ, "Before", to_string(i), "");
        if (!str.empty())
        {
            //  minus 1 because i'm using zero-indexed but my ini file is in one-based
            before_Locs.push_back(stoi(str)-1);
            clipBoards.push_back("");
        }
    }

    vector<string> triggers;
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
    // Stop the clipboard monitoring thread
    stop_output_thread = true;

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
