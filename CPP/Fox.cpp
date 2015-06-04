#include "Fox.h"
#include "World.h"

namespace World {
	namespace Animals {

		void Fox::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Fox(x, y));
		}

		void Fox::move_x(const int d) {
			// Tam gdzie mia³ siê ruszyæ jest wolne miejsce
			if (world->is_free(position.first + d, position.second)) Animal::move_x(d);
			// Z drugiej strony jest miejsce
			else if (world->is_free(position.first - d, position.second)) Animal::move_x(d == LEFT ? RIGHT : LEFT);
			// U góry/na dole jest miejsce
			else if (world->is_free(position.first, position.second + TOP)) Animal::move_y(TOP);
			else if (world->is_free(position.first, position.second + BOTTOM)) Animal::move_y(BOTTOM);
		}

		void Fox::move_y(const int d) {
			// Tam gdzie mia³ siê ruszyæ jest wolne miejsce
			if (world->is_free(position.first, position.second + d)) Animal::move_y(d);
			// Z drugiej strony jest miejsce
			else if (world->is_free(position.first, position.second - d)) Animal::move_y(d == TOP ? BOTTOM : TOP);
			// U góry/na dole jest miejsce
			else if (world->is_free(position.first, position.second + LEFT)) Animal::move_x(LEFT);
			else if (world->is_free(position.first, position.second + RIGHT)) Animal::move_x(RIGHT);
		}

	}
}