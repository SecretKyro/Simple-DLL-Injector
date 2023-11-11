#include "pch.h"
#include "logger/logger.h"
#include "functions.h"
    using namespace Loader;
int main() {
        g_Logger = std::make_unique<Logger>(); // This creates a new instance of the Logger class

        // I'm just gonna write a simple login system but you can add keyauth, system locker, pastebin, or your own auth this is just an example
        LOG(Info, "Enter your username");
        getline(cin, UserName); // Basicly grabs what the user typed in
        LOG(Info, "Enter your password");
        getline(cin, Password); // Basicly grabs what the user typed in

        Authed = (UserName == "Kyro" || Password == "Kyro");

        if (Authed) { // Basicly just means that they passed your auth check
            LOG(Success, "Welcome {}!", UserName);

            uint32_t PID = GetPID(Window); // This gets the PID of whatever window you put into the variable

            if (PID == 0) { // Just a saftey check to inform you that it failed to get your windows PID
                LOG(Fatal, "Failed to get the window's PID");
                return 1;
            }

            DownloadFile(URL, DLL_LOCATION); // This will download the dll

            if (LoadLibraryInject(PID, DLL_LOCATION.c_str()))
                LOG(Success, "Injected DLL from {} into {}/{}", DLL_LOCATION, Window, PID); // If everything goes fine and you don't break shit this should inject into your process
            else
                LOG(Fatal, "Failed to inject DLL from {} into {}/{}", DLL_LOCATION, Window, PID); // Basicly if something goes wrong it will say this in the log

        }
        else { // This just means that they failed your auth check
            // Here you can call your security protocols
            LOG(Fatal, "Invalid Login");
        }
        // Any cleanup you wanna do before the program closes this is where you will do that
        LOG(Info, "Goodbye!");
        system("pause"); // This pauses the console till the user presses a key on their keyboard
        return 0; // Wow the program executed successfully
}