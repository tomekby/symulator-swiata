#include "Belladonna.h"
#include "World.h"

namespace World {
	namespace Plants {

		void Belladonna::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Belladonna(x, y));
		}

		// Coœ trafi³o w roœlinê
		void Belladonna::collision(Organism* with) {
			// Zabicie zwierzêcia które zjad³o roœlinê
			Organism::kill(*with);
		}

	}
}