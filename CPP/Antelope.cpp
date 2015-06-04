#include "Antelope.h"
#include "World.h"

namespace World {
	namespace Animals {

		void Antelope::move_x(const int d) {
			Animal::move_x(d * 2);
		}

		void Antelope::move_y(const int d) {
			Animal::move_y(d * 2);
		}

		void Antelope::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Antelope(x, y));
		}

		// Kolizja - nie ma walki, jest ew. ucieczka
		void Antelope::collision(Organism* with) {
			// Jeœli nie ucieka, nie ma co robiæ
			if (!ran_away) return;
			// Ucieczka - szukanie wolnego pola
			if (world->is_free(position.first + 1, position.second)) Animal::move_x(1);
			else if (world->is_free(position.first - 1, position.second)) Animal::move_x(-1);
			else if (world->is_free(position.first, position.second + 1)) Animal::move_y(1);
			else if (world->is_free(position.first, position.second - 1)) Animal::move_y(-1);
		}

		// Jeœli nie uciek³a, reaguje na cofniêcie
		void Antelope::go_back() {
			if (!ran_away) Animal::go_back();
		}

	}
}