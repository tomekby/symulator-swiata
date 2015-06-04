#include "Dandelion.h"

namespace World {
	namespace Plants {

		void Dandelion::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Dandelion(x, y));
		}

		// 3 próby rozsiania
		void Dandelion::action() {
			for (size_t i = 0; i < 3; ++i) Plant::action();
		}

	}
}