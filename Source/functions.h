#pragma once
#include "pch.h"
namespace Loader {
    //Simple curl function to download from URL
    void DownloadFile(const std::string& url, const std::string& path) {
        // curl variables
        CURL* Instance;
        FILE* File;
        CURLcode ResultCode;

        // Initialize curl instance
        Instance = curl_easy_init();

        // Check if the instance was initialized successfully
        if (Instance) {
            // Open the file for writing in binary mode
            File = fopen(path.c_str(), "wb");

            // Set libcurl options
            curl_easy_setopt(Instance, CURLOPT_URL, url.c_str());
            curl_easy_setopt(Instance, CURLOPT_USERAGENT, "Nigga");
            curl_easy_setopt(Instance, CURLOPT_WRITEFUNCTION, fwrite);
            curl_easy_setopt(Instance, CURLOPT_WRITEDATA, File);
            curl_easy_setopt(Instance, CURLOPT_VERBOSE, 1L);

            // Perform the file download
            ResultCode = curl_easy_perform(Instance);

            // Checks for errors and display a message box if there are any
            if (ResultCode != CURLE_OK)
                MessageBoxA(0, curl_easy_strerror(ResultCode), 0, MB_ICONERROR);

            // Clean up curl and close the file
            curl_easy_cleanup(Instance);
            fclose(File);
        }

        // Clean up libcurl global resources
        curl_global_cleanup();
    }

    // Simple dll injector
    bool LoadLibraryInject(DWORD PID, const char* Dll) {
        // Check if the PID is valid
        if (PID == NULL)
            return false;

        // Convert narrow string DLL path to wide string
        wchar_t CustomDLL[MAX_PATH];
        MultiByteToWideChar(CP_ACP, 0, Dll, -1, CustomDLL, MAX_PATH);

        // Open the process with all access rights
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

        // Allocate memory in the process
        LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(CustomDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

        // Write the DLL path to the allocated memory in the process
        if (!WriteProcessMemory(hProcess, allocatedMem, CustomDLL, sizeof(CustomDLL), NULL))
            return FALSE;

        // Create a remote thread in the process to load the DLL
        CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, allocatedMem, 0, 0);

        // Close the handle to the process
        if (hProcess)
            CloseHandle(hProcess);

        // WOW it worked
        return TRUE;
    }

    uint32_t GetPID(const char* WndClass, const char* Wnd = NULL) {
        HWND Window = FindWindowA(WndClass, Wnd); // Tries to find your window
        DWORD PID; // Declares the variable PID
        GetWindowThreadProcessId(Window, &PID); // What actually changes the PID variable to the the PID of your window
        return PID;
    }
}