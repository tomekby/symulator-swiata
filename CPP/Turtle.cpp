#include "Turtle.h"
#include "World.h"

namespace World {
	namespace Animals {

		void Turtle::action() {
			//  25% szans na ruch
			if (rand() % 4 == 2) Animal::action();
		}

		// Zmuszenie przeciwnika do wycofania
		void Turtle::collision(Organism *with) {
			dynamic_cast<Animal*>(with)->go_back();
			world->add_event(_("¯ó³w zmusza do wycofania ") + with->get_name());
		}

		void Turtle::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Turtle(x, y));
		}

	}
}
