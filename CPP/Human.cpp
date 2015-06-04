#include "Human.h"
#include "World.h"

namespace World {
	namespace Animals {

		size_t Human::move_range() const {
			if (before_next_bonus != 0 && !bonus_left) return 1;
			else if (bonus_left > 2) return 2;
			return (rand() % 2 + 1);
		}

		void Human::move_x(const int d) {
			const size_t DIRECTION = move_range() * d;
			Animal::move_x(DIRECTION);
		}

		void Human::move_y(const int d) {
			const size_t DIRECTION = move_range() * d;
			Animal::move_y(DIRECTION);
		}

		void Human::action() {
			console::IO::gotoxy(0, world->get_N() + 2);
			console::IO::print(_("Oczekiwanie na ruch..."));

			int ch;
			while ((ch = console::IO::getch()) != 0) {
				// Użyszkodnik chce aktywować a nie było aktywowane
				if (ch == 'a' && bonus_left == 0 && before_next_bonus == 0) bonus_left = 5;
			}
			ch = console::IO::getch();
			if (ch == 0x48) move_y(TOP); // ↑
			else if (ch == 0x50) move_y(BOTTOM); // ↓
			else if (ch == 0x4b) move_x(LEFT); // ←
			else if (ch == 0x4d) move_x(RIGHT); // →

			// Zmniejszenie pozostałych rund bonusu
			if (bonus_left) --bonus_left;
			// Bonus się skończył i nie zaczęło odliczanie do następnego
			if (bonus_left == 0 && before_next_bonus == 0) before_next_bonus = 5;
			// Zmniejszenie ilości rund do możliwości uruchomienia bonusa
			else if (bonus_left == 0 && before_next_bonus != 0) --before_next_bonus;
		}

	}
}