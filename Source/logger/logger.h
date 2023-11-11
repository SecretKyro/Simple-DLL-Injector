#include "pch.h"
#pragma once
using namespace std;
// Fuck you I am not writing comments for this just don't touch it
// Credit: Pocakking
namespace Loader {
	enum class eLogColor : uint16_t {
		Black = 0,
		DarkBlue = FOREGROUND_BLUE,
		DarkGreen = FOREGROUND_GREEN,
		DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkRed = FOREGROUND_RED,
		DarkMagneta = FOREGROUND_RED | FOREGROUND_BLUE,
		DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
		DarkGray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Gray = FOREGROUND_INTENSITY,
		Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		Cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
		Magneta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		White = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		LightGray = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
		Orange = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		Pink = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		LightBlue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		LightGreen = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		LightCyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		LightRed = FOREGROUND_INTENSITY | FOREGROUND_RED,
		LightMagenta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		LightYellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
	};

	inline eLogColor operator|(eLogColor a, eLogColor b) {
		return static_cast<eLogColor>(static_cast<underlying_type_t<eLogColor>>(a) | static_cast<underlying_type_t<eLogColor>>(b));
	}

	enum class eLogType : uint8_t {
		Info,
		Success,
		Warn,
		Fatal
	};

	class Logger {
	public:
		Logger();
		~Logger();

		template <typename... arguments>
		void DirectSend(eLogColor col, string type, string fmt, arguments... args) {
			string msg{ format("[{}] {}", type, vformat(fmt, make_format_args(args...))) };
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(col));
			m_Console << msg << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(eLogColor::White));
		}
		template <typename... arguments>
		void Send(eLogType type, string fmt, arguments... args) {
			switch (type) {
			case eLogType::Info:
				this->DirectSend<arguments...>(eLogColor::Gray, "Info!", fmt, args...);
				break;
			case eLogType::Success:
				this->DirectSend<arguments...>(eLogColor::LightGreen, "Success!", fmt, args...);
				break;
			case eLogType::Warn:
				this->DirectSend<arguments...>(eLogColor::Orange, "Warning!", fmt, args...);
				break;
			case eLogType::Fatal:
				this->DirectSend<arguments...>(eLogColor::LightRed, "Fatal!", fmt, args...);
				break;
			default:
				break;
			}
		}

	private:
		ofstream m_Console;
		ifstream m_Input;
	};
	inline  unique_ptr<Logger> g_Logger;
}

#define LOG(type, fmt, ...) Loader::g_Logger->Send(Loader::eLogType::type, fmt, __VA_ARGS__)
