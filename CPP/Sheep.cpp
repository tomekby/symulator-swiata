#include "Sheep.h"

namespace World {
	namespace Animals {

		void Sheep::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Sheep(x, y));
		}

	}
}