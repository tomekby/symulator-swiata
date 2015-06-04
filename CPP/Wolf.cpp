#include "Wolf.h"

namespace World {
	namespace Animals {

		void Wolf::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Wolf(x, y));
		}

	}
}