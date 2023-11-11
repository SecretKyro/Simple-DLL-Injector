#include "logger.h"
// Fuck you I am not writing comments for this just don't touch it
namespace Loader {
	Logger::Logger() {
		AllocConsole();
		SetConsoleTitleA(Branding.c_str());
		SetLayeredWindowAttributes(GetConsoleWindow(), NULL, 235, LWA_ALPHA);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
		m_Console.open("CONOUT$");
		m_Input.open("CONIN$");
	}
	Logger::~Logger() {
		FreeConsole();
		m_Console.close();
		m_Input.close();
	}
}
