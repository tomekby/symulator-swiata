#include "console.h"

namespace console {

#ifdef _WIN32
	/**
	* Pobieranie od razu jako struktura coords
	*
	* @return COORD koordynaty kursora
	*/
	COORD cursor::coords() {
		COORD coord;
		coord.X = this->x; coord.Y = this->y;
		return coord;
	}
	// Struktura konfiguracyjna dla funkcji z udostêpnionego szablonu
	_Conio2ThreadData _thData;

	/**
	* Inicjalizacja kodu z udostêpnionego szablonu
	*/
	bool _InitConio2() {
		_thData.output = GetStdHandle(STD_OUTPUT_HANDLE);
		_thData.input = GetStdHandle(STD_INPUT_HANDLE);
		_thData.ungetCount = _thData.charCount = 0;

		_thData.lastmode = C80;
		SetConsoleMode(_thData.input, ENABLE_PROCESSED_INPUT);

		return true;
	}
#endif

	/**
	* Wczytywanie wartoœci z stdin
	*/
	template<class T> T IO::read() {
		T res;
		in >> res;

		return res;
	}

	// Fix na linkowanie
	template string IO::read<string>();
	template unsigned IO::read<unsigned>();
	template unsigned short IO::read<unsigned short>();
	template short IO::read<short>();
	template int IO::read<int>();

	/**
	* Funkcja czyszcz¹ca ekran
	*
	* Tworzy ró¿ny kod w zale¿noœci od systemu docelowego (Windows/Linux).
	* Nie u¿ywam 'system("cls")', gdy¿ mo¿e to prowadziæ do problemów zw. z bezpieczeñstwem.
	*
	* @return void
	*/
	void IO::cls() {
#ifdef _WIN32
		// Czyszczenie ekranu na podstawie funkcji z oficjalnej strony Microsoftu
		// U¿ywa WinAPI, kompilowane tylko na Windows
		HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_handle, _NORMAL_TEXT_STYLE); // W razie potrzeby zmiana koloru konsoli na okreœlony
		COORD screen = { 0, 0 };
		DWORD chars_written, con_size;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(console_handle, &csbi);
		con_size = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(console_handle, ' ', con_size, screen, &chars_written);
		GetConsoleScreenBufferInfo(console_handle, &csbi);
		FillConsoleOutputAttribute(console_handle, csbi.wAttributes, con_size, screen, &chars_written);
		SetConsoleCursorPosition(console_handle, screen);
#else
		// Czyszczenie ekranu za pomoc¹ ANSI Escape Codes na podstawie danych znalezionych w internecie
		// U¿ywa ANSI Escape Codes, dzia³a tylko na Linuksie i tylko tam kompilowane
		out << "\033[2J\033[1;1H";
		std::rewind(stdout);
#endif
	}

	/**
	* Zatrzymanie konsoli (u¿ywane do efektu drukowania tekstu).
	*
	* @return void
	*/
	void IO::_sleep() {
		unsigned writing_delay = 0; // Opó¿nienie przy wypisywaniu liter
		if (console::IO::_FPS == 0) return;
		// Jeœli ma byæ jakieœ opó¿nienie, liczenie go na podstawie podanego FPS
		// Ciekawe optymalizacje... Jeœli _FPS == 0 to poni¿szy kod siê nie wykona
		// Ale VS i tak siê czepia, ¿e bêdzie dzielenie przez 0...
		writing_delay = 1000 / (console::IO::_FPS == 0 ? 1 : console::IO::_FPS);
		// Delay tylko przed liter¹/cyfr¹
#ifdef _WIN32
		Sleep(writing_delay);
#else
		out.flush();
		usleep(1000 * writing_delay); // OpóŸnienie mniejsze, bo ustawienie stylów trwa odrobinê wiêcej
#endif
	}

	/**
	* Ustawienie stylu (np. kolor tekstu, podkreœlenie, etc.)
	*
	* @param  const unsigned type typ stylu (np. zwyk³y tekst, zaznaczony)
	* @return void
	*/
	void IO::_set_style(const unsigned type) {
#ifdef _WIN32
		HANDLE console_out = GetStdHandle(STD_OUTPUT_HANDLE);
		if (type == _NORMAL_STYLE) {
			SetConsoleTextAttribute(console_out, _NORMAL_TEXT_STYLE);
		}
		else if (type == _ALTERNATIVE_STYLE) {
			SetConsoleTextAttribute(console_out, _ALTERNATIVE_TEXT_STYLE);
		}
		else {
			SetConsoleTextAttribute(console_out, _INDEX_TEXT_STYLE);
		}
#else
		printf("\e[?25l"); // Ukrycie wskaŸnika kursora
		if (type == _NORMAL_STYLE) {
			for (unsigned j = 0; j < ARRAYSIZE(_NORMAL_TEXT_STYLE); ++j) {
				printf("%c[%dm", ESC, _NORMAL_TEXT_STYLE[j]);
			}
		}
		else {
			for (unsigned j = 0; j < ARRAYSIZE(_INDEX_TEXT_STYLE); ++j) {
				printf("%c[%dm", ESC, _INDEX_TEXT_STYLE[j]);
			}
		}
#endif
	}

	/**
	* Drukowanie wiersza tekstu
	* @todo: flatten
	*
	* Jeœli indeks litery (liczony od 0) nie zostanie podany, nie bêdzie
	* zaznaczonej ¿adnej. Jeœli indeks zostanie podany, wyœwietlona zostanie
	* litera o okreœlonym numerze. Podanie console::ALL powoduje kolorowanie
	* ca³ego wiersza na kolor indeksu.
	*
	* @param  const string &row wiersz do wypisania
	* @param  const unsigned key_letter = -1 litera do zaznaczenia
	* @return void
	*/
	void IO::print(const string &row, const int key_letter) {
		/// Wstêpne ustawienia konsoli - ustawienie atrybutów tekstu niekolorowanego/kolorowanego
		if (key_letter == ALL || key_letter == 0) {
			_set_style(_INDEX_STYLE);
		}
		else if (key_letter == ALTERNATIVE) {
			_set_style(_ALTERNATIVE_STYLE);
		}
		else {
			_set_style(_NORMAL_STYLE);
		}

		/// Drukowanie kolejnych liter tekstu
		for (unsigned i = 0; i < row.length(); ++i)
		{
			if (i == unsigned(key_letter) && key_letter != 0) {
				_set_style(_INDEX_STYLE);
			}
			else if (key_letter == ALTERNATIVE) {
				_set_style(_ALTERNATIVE_STYLE);
			}
			else if (i == unsigned(key_letter + 1)) {
				_set_style(_NORMAL_STYLE);
			}
			_sleep();
			out << row[i];
		} // End for
		out << std::endl;
	}

	/**
	* Alias dla funkcji wyœwietlaj¹cej tekst z pokolorowanym indeksem.
	*
	* Jeœli podany zostanie wyraz to zaznaczona zostanie pierwsza litera.
	*
	* @param  const string &row wiersz do wypisania
	* @param  const string &keyword litera lub wyraz do zaznaczenia
	* @return void
	*/
	void IO::print(const string &row, const string &keyword) {
		const unsigned pos = row.find(keyword);
		if (pos != string::npos) print(row, pos);
		else print(row);
	}

	/**
	* Alias dla funkcji wyœwietlaj¹cej tekst z pokolorowanym indeksem.
	*
	* Jeœli podany zostanie wyraz to zaznaczona zostanie litera tego wyrazu
	* o indeksie podanym jako ostatni argument (liczone od 0).
	*
	* @param  const string &row wiersz do wypisania
	* @param  const string &keyword litera lub wyraz do zaznaczenia
	* @param  const unsigned letter numer litery w wyrazie do zaznaczenia
	* @return void
	*/
	void IO::print(const string &row, const string &keyword, const unsigned letter) {
		const unsigned pos = row.find(keyword);
		if (pos != std::string::npos) print(row, pos + letter);
		else print(row);
	}

	/**
	* Oczekiwanie na u¿yszkodnika aby móg³ zobaczyæ wynik.
	* Nie u¿ywam 'system("pause")', gdy¿ mo¿e to prowadziæ do problemów zw. z bezpieczeñstwem.
	* Poza tym, autorska funkcja pozwala na wiêksz¹ kontrolê nad tym, co i jak jest wypisane.
	*
	* @return void
	*/
	void IO::pause() {
		print(_("\nWciœnij <ENTER> aby kontynuowaæ..."));
		in.sync(); // Kasowanie zbêdnych znaków z bufora
		in.get();  // Oczekiwanie na wciœniêcie klawisza
	}

	/**
	* Funkcja przenosz¹ca kursor na okreœlon¹ pozycjê w oknie konsoli (pozwala wprowadziæ zmiany bez redrawa okna)
	*
	* @param  const unsigned x numer kolumny
	* @param  const unsigned y numer wiersza
	* @return void
	*/
	void IO::gotoxy(const unsigned x, const unsigned y) {
#ifdef _WIN32
		COORD coord;
		coord.X = x; coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
		printf("\e[%d;%dH", x, y);
#endif
	}

	/**
	* Funkcja przenosz¹ca kursor na okreœlon¹ pozycjê w oknie konsoli (pozwala wprowadziæ zmiany bez redrawa okna)
	* Alias dla funkcji gotoxy(x,y)
	*
	* @param  const cursor &pos pozycja kursora
	* @return void
	*/
	void IO::gotoxy(const cursor &pos) {
		gotoxy(pos.x, pos.y);
	}

	/**
	* Pobieranie pozycji kursora w konsoli
	* ! Aktualnie nie dzia³a na Linuksie
	*
	* @return cursor pozycja kursora
	*/
	cursor IO::get_cursor_pos() {
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

		return cursor(info.dwCursorPosition.X, info.dwCursorPosition.Y);
#else
		// @todo: zrobienie tak, ¿eby dzia³a³o na Linuksie
		return cursor();
#endif
	}

	/**
	* Ustawianie tytu³u okna konsoli
	*
	* @param  const string &title tytu³ okna konsoli
	* @return void
	*/
	string IO::title(const string &title) {
		if (title == _("")) return _("Tytu³ konsoli"); // @todo zrobienie gettera (?)

#ifdef _WIN32
		SetConsoleTitleW(title.c_str());
#else
		printf("\033]0;%s\007", title.c_str());
#endif

		return title;
	}


	/**
	* Funkcja skopiowana z szablonu
	*/
	bool IO::_HandleKeyEvent(INPUT_RECORD *buf) {
		int ch;
		ch = (int)(buf->Event.KeyEvent.uChar.AsciiChar) & 255;
		if (ch == 0) ch = 0x8000 + buf->Event.KeyEvent.wVirtualKeyCode;
		if (ch == 0x8010 || ch == 0x8011 || ch == 0x8012 || ch == 0x8014
			|| ch == 0x8090 || ch == 0x8091) return false;
		_thData.charCount = buf->Event.KeyEvent.wRepeatCount;
		_thData.charFlag = ch & 0x8000 ? 1 : 0;
		if (_thData.charFlag) _thData.charCount *= 2;
		switch (ch) {
		case 0x8000 + 33:	ch = 0x8000 + 73; break;
		case 0x8000 + 34:	ch = 0x8000 + 81; break;
		case 0x8000 + 35:	ch = 0x8000 + 79; break;
		case 0x8000 + 36:	ch = 0x8000 + 71; break;
		case 0x8000 + 37:	ch = 0x8000 + 75; break;
		case 0x8000 + 38:	ch = 0x8000 + 72; break;
		case 0x8000 + 39:	ch = 0x8000 + 77; break;
		case 0x8000 + 40:	ch = 0x8000 + 80; break;
		case 0x8000 + 46:	ch = 0x8000 + 83; break;
		case 0x8000 + 112:	ch = 0x8000 + 59; break;
		case 0x8000 + 113:	ch = 0x8000 + 60; break;
		case 0x8000 + 114:	ch = 0x8000 + 61; break;
		case 0x8000 + 115:	ch = 0x8000 + 62; break;
		case 0x8000 + 116:	ch = 0x8000 + 63; break;
		case 0x8000 + 117:	ch = 0x8000 + 64; break;
		case 0x8000 + 118:	ch = 0x8000 + 65; break;
		case 0x8000 + 119:	ch = 0x8000 + 66; break;
		case 0x8000 + 120:	ch = 0x8000 + 67; break;
		case 0x8000 + 121:	ch = 0x8000 + 68; break;
		case 0x8000 + 122:	ch = 0x8000 + 133; break;
		case 0x8000 + 123:	ch = 0x8000 + 134; break;
		};
		_thData.charValue = ch & 0x7fff;
		// TODO: translate proper keys (eg. arrows) to 0, xxx
		return true;
	};

	/**
	* Funkcja skopiowana z szablonu
	*/
	int IO::getch() {
		BOOL rv;
		DWORD n;
		INPUT_RECORD buf;

		if (_thData.ungetCount > 0) {
			_thData.ungetCount--;
			return _thData.ungetBuf[_thData.ungetCount];
		};

		if (_thData.charCount > 0) {
			_thData.charCount--;
			if (_thData.charCount & 1 && _thData.charFlag) return 0;
			else return _thData.charValue;
		};

		while (true) {
			rv = ReadConsoleInput(_thData.input, &buf, 1, &n);
			if (rv == false) continue;
			if (buf.EventType != KEY_EVENT) continue;
			if (buf.Event.KeyEvent.bKeyDown == false) continue;
			if (_HandleKeyEvent(&buf)) break;
		};

		_thData.charCount--;
		if (_thData.charCount & 1 && _thData.charFlag) return 0;
		else return _thData.charValue;
	}

	/**
	* Pobieranie znaku i wypisanie go na konsolê
	*
	* @return pobrany znak
	*/
	int IO::getche() {
		const char ch = getch();
		out << ch;
		return ch;
	}

	/**
	* Wymiary okna konsoli
	*
	* @return  <cols, rows>
	*/
	std::pair<unsigned, unsigned> IO::get_size() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int columns, rows;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		return std::make_pair(columns, rows);
	}

	/**
	* Czyszczenie linii
	*
	* @param y numer linii do wyczyszczenia
	*/
	void IO::clear_line(const unsigned y) {
		const auto size = get_size();
		if (y > size.second) return;

		// Poprzednia pozycja kursora
		const console::cursor TMP = get_cursor_pos();
		// Tworzenie stringa o szerokoœci okna konsoli
		string line;
		line.append(size.first, _(' '));
		// Czyszczenie
		gotoxy(0, y);
		print(line);
		// Powrót
		gotoxy(TMP);
	}

	/**
	* Ukrywanie kursora w konsoli
	*
	* @return true
	*/
	bool _hide_cursor() {
		HANDLE hConsoleOutput;
		CONSOLE_CURSOR_INFO structCursorInfo;
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
		structCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);

		return true;
	}
} // End namespace console