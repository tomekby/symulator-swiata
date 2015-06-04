#include "Grass.h"

namespace World {
	namespace Plants {

		void Grass::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Grass(x, y));
		}

	}
}
