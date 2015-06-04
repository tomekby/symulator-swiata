#include "Belladonna.h"
#include "World.h"

namespace World {
	namespace Plants {

		void Belladonna::spawn_new(const int x, const int y) {
			Organism::spawn_new(x, y, new Belladonna(x, y));
		}

		// Co� trafi�o w ro�lin�
		void Belladonna::collision(Organism* with) {
			// Zabicie zwierz�cia kt�re zjad�o ro�lin�
			Organism::kill(*with);
		}

	}
}