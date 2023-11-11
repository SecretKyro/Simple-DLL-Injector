#pragma once
// Ease of use includes
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <ctime>
#include <format>
#include <cstdio>

// Stupid curl shit
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Wldap32.lib")
#include <curl/curl.h>

// Basicly just makes it so you don't have to do std::cout but rather do just cout
using namespace std;

// Ease of use variables
inline string Branding;
inline string UserName; // This is the variable that you will check after the user inserts their username
inline string Password; // This is the variable that you will check after the user inserts their password
inline bool Authed; // If they pass the auth check then this will be true otherwise this will be false
inline string URL = ""; // Replace this with the URL to your dll
inline string DLL_LOCATION = ""; // Replace this with where you want your dll to be saved
inline const char* Window = "grcWindow"; // You can change the window to whatever but this is just an example of what you would do for GTAV