#include "Guarana.h"
#include "World.h"
#include "Animal.h"

namespace World {
	namespace Plants {

		void Guarana::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Guarana(x, y));
		}

		// Co� trafi�o w ro�lin�
		void Guarana::collision(Organism* with) {
			// Zwi�kszenie si�y o 3
			auto a = dynamic_cast<Animals::Animal*>(with);
			if (a != nullptr) a->inc_strength(3);
		}

	}
}