#include "Animal.h"
#include "World.h"

namespace World {
	namespace Animals {

		// Uwzględnienie ruchu o zasięgu > 1 i wolnych pól
		void Animal::move_x(const int d) {
			if (d < 0) { // Przesunięcie w lewo
				for (int i = -d; i >= 1; --i) {
					if (position.first - i >= 0) {
						position.first -= i;
						break;
					}
				}
			}
			else { // Przesunięcie w prawo
				for (int i = d; i >= 1; --i) {
					if (position.first + i < static_cast<int>(world->get_N())) {
						position.first += i;
						break;
					}
				}
			}
		}

		void Animal::move_y(const int d) {
			if (d < 0) { // Przesunięcie w górę
				for (int i = -d; i >= 1; --i) {
					if (position.second - i >= 0) {
						position.second -= i;
						break;
					}
				}
			}
			else { // Przesunięcie w dół
				for (int i = d; i >= 1; --i) {
					if (position.second + i < static_cast<int>(world->get_N())) {
						position.second += i;
						break;
					}
				}
			}
		}

		void Animal::action()
		{
			// Przesuniecie zwierzaka
			auto r = rand();
			if (r < RAND_MAX / 4) move_y(TOP);
			else if (r >= RAND_MAX / 4 && r < RAND_MAX / 2) move_y(BOTTOM);
			else if (r >= RAND_MAX / 2 && r < RAND_MAX / 4 * 3) move_y(LEFT);
			else if (r >= RAND_MAX / 4 * 3) move_y(RIGHT);

			Organism::action();
		}
		
		// Domyślne zachowanie podczas kolizji
		void Animal::collision_default(Organism* with) {
			// Ten sam typ → rozmnażanie
			if (get_symbol() == with->get_symbol()) {
				// Po lewej jest wolne miejsce
				if (world->is_free(position.first - 1, position.second)) spawn_new(position.first - 1, position.second);
				// Po prawej jest wolne miejsce
				else if (world->is_free(position.first + 1, position.second)) spawn_new(position.first + 1, position.second);
				// U góry jest wolne miejsce
				else if (world->is_free(position.first, position.second - 1)) spawn_new(position.first, position.second - 1);
				// Na dole jest wolne miejsce
				else if (world->is_free(position.first, position.second + 1)) spawn_new(position.first, position.second + 1);
				else throw NoPlaceToSpawn("Nie można stworzyć potomka");
				world->add_event(get_name() + _(" się rozmnaża"));
			}
			else {
				// Inne gatunki - będzie walka
				// Python style - duck typing
				try {
					auto oponent = dynamic_cast<Animal*>(with);
					// Jeśli 2. gatunek to nie zwierzę dynamic cast zwróci nullptr
					if (oponent == nullptr) throw std::bad_cast();

					// Zwierzęta powinny walczyć
					if (should_fight(oponent) && oponent->should_fight(this)) {
						fight(*with);
					}
					// Niestandardowa akcja kolizji
					else {
						collision(with);
						with->collision(this);
					}
				}
				// Nie jest zwierzęciem -> będzie jedzone
				catch (const std::bad_cast &e) {
					eat(with);
				}
			}
		}

		void Animal::eat(Organism *p) {
			Organism::eat(*p);
		}

		void Animal::go_back() {
			position = last_position;
		}
	} // End namespace Animals
} // End namespace World