// ChatClip.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <string>

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#include <iostream>
#include <map>
#include <optional>
#include <vector>
#include <thread>

#include <thread>
#include <mutex>

std::mutex io_mutex;


using namespace std;

const map<string, vector<string>> COMMANDS = {
    {"Cover Letter", {"cover", "c"}},
    {"Exit", {"exit", "x"}},
};

const string VER = "0.6b";


void output_thread()
{
    while (true)
    {
        lock_guard<mutex> lock(io_mutex);
        cout << endl << "Output thread is running" << endl;
        cout << "main: ";
        this_thread::sleep_for(chrono::seconds(3)); // Delay for 3 second
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
