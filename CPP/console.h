/**
* Klasa odpowiedzialna za obs�ug� frontendu w konsoli
* Kompilowany kod jest r�ny w zale�no�ci od docelowego systemu.
* Jest to spowodowane tym, �e Windows i Linux u�ywaj� r�nych
* sposob�w formatowania konsoli (WinAPI/ANSI Escape Codes).
*
* @author     Tomasz Stasiak
* @copyright  (c) 2012/2014 Tomasz Stasiak
*/
#ifndef CONSOLE_H
#define CONSOLE_H

#ifdef _WIN32
#   define _WIN32_WINNT 0x0501
#   include <windows.h>
#endif

#include <iostream>
#include <string>

namespace console {

#ifdef _WIN32
#	include <io.h>
#	include <fcntl.h>
#	include <tchar.h>
#	define _(x) _T(x)
	typedef std::wstring string;
#	define LASTMODE		-1
#	define C80			 3
#	define C4350		 8
#	define FULLSCREEN	 0x8000
	static std::wistream& in  = std::wcin;
	static std::wostream& out = std::wcout;
#else
#   include <cstdio>
#   include <unistd.h>
#	define _(x) x
#	define ARRAYSIZE(x) sizeof(x) / sizeof(x[0])
	typedef std::string string;
	static std::istream& in  = std::cin;
	static std::ostream& out = std::cout;
#endif

	/**
	* Ustawienia
	*/
#ifndef _WIN32
	/// ASCII escape codes u�ywane do formatowania konsoli
	const char ESC = 0x1B; // Escape (musi poprzedza� escape code'y)
	const char RESET = 0x00; // Resetowanie ustawie�
	const char BRIGHT = 0x01; // Jaskrawsze kolory
	const char UNDERLINE = 0x04; // Podkre�lenie
	// Kolory tekstu w konsoli
	enum{ BLACK = 0x1E, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
	// Kolory t�a w konsoli
	enum{ BG_BLACK = 0x28, BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE };
#else
	// Ustawienie kodowania w konsoli windows
	// Hack umo�liwiaj�cy init jeszcze przed main()
	const auto _SET_UNICODE = _setmode(_fileno(stdout), _O_U8TEXT);
#endif

	/**
	* Dane kursora
	*/
	class cursor {
	public:
		cursor() : x(0), y(0) {};
		cursor(unsigned x, unsigned y) : x(x), y(y) {};
#ifdef _WIN32
		COORD coords();
#endif
		const inline bool is_valid() { return (x < 10 && y < 10); }
		unsigned x, y;
	};

#ifdef _WIN32
	/**
	* Struktura skopiowana z szablonu do projektu
	* W sumie nie wszystkie pola s� potrzebne, ale
	* nie chce mi si� sprawdza� co mo�na wyrzuci�
	*/
	struct _Conio2ThreadData {
		int attrib;
		int charCount;
		int charValue;
		int charFlag;
		int ungetCount;
		int ungetBuf[16];
		HANDLE input;
		int _wscroll;
		int width;
		int height;
		int origwidth;
		int origheight;
		int origdepth;
		int lastmode;
		HANDLE output;
		DWORD prevOutputMode;
		DWORD prevInputMode;
	};
	bool _InitConio2(); // Funkcja inicjuj�ca w/w 
	bool _hide_cursor();
	// Hack umo�liwiaj�cy za�adowanie przed main
	// Nie wymaga u�ywania makr do kontroli gdzie l�duje kod
	const auto _INIT_HACK = _InitConio2() && _hide_cursor();
#endif
	class IO {
	public:
		/**
		* G��wna obs�uga konsoli
		*/
		static void cls();
		static void pause();
		static void print(const string &row, const int key_letter = -1);
		static void print(const string &row, const string &keyword);
		static void print(const string &row, const string &keyword, const unsigned letter);
		// Wszystkie znaki maj� by� pokolorowane
		static const unsigned ALL = 0xDEADBEEF;
		static const unsigned ALTERNATIVE = 0xBADDCAFE;
		static void gotoxy(const unsigned x, const unsigned y);
		static void gotoxy(const cursor &pos);
		static string title(const string &title);
		static cursor get_cursor_pos();
		static int getch();
		static int getche();
		static std::pair<unsigned, unsigned> get_size();
		static void clear_line(const unsigned y);
		template<class T> static T read();
	private:
		static bool _HandleKeyEvent(INPUT_RECORD *buf);
		static void _sleep();
		static void _set_style(const unsigned type);
		/// Ilo�� znak�w wypisywanych w ci�gu sekundy
		static const unsigned _FPS = 0;
		/// Typ ustawianych informacji
		static const unsigned _NORMAL_STYLE = 1;
		static const unsigned _INDEX_STYLE = 2;
		static const unsigned _ALTERNATIVE_STYLE = 4;
#ifdef _WIN32
		/// Style: http://msdn.microsoft.com/en-us/library/windows/desktop/ms682088%28v=vs.85%29.aspx#_win32_character_attributes
		// Styl normalnego wypisywanego tekstu
		static const unsigned _NORMAL_TEXT_STYLE = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		// Styl indeksu (zaznaczonej litery), kt�ry trzeba wpisa� aby wybra� element z menu
		static const unsigned _INDEX_TEXT_STYLE = FOREGROUND_RED | FOREGROUND_INTENSITY;
		static const unsigned _ALTERNATIVE_TEXT_STYLE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
#else
		/// Style widoczne wy�ej
		static constexpr unsigned _NORMAL_TEXT_STYLE[] = { RESET, BG_BLACK, BRIGHT, GREEN };
		static constexpr unsigned _INDEX_TEXT_STYLE[] = { RESET, BG_BLACK, UNDERLINE, BRIGHT, RED };
#endif
	};
} // End namespace console

#endif // CONSOLE_H
