#include "Plant.h"
#include "World.h"

namespace World {
	namespace Plants {
		
		void Plant::action() {
			if(rand() < RAND_MAX/4) { // 25% szans na rozsianie
				std::pair<size_t, size_t> pos = position;
				// Po prawej jest miejsce
				if (world->is_free(position.first + 1, position.second)) ++pos.first;
				// Po lewej jest miejsce
				else if (world->is_free(position.first - 1, position.second)) --pos.first;
				// Poni¿ej jest miejsce
				else if (world->is_free(position.first, position.second + 1)) ++pos.second;
				// U góry jest miejsce
				else if (world->is_free(position.first, position.second - 1)) --pos.second;
				// Zespawnowanie nowej roœliny
				spawn_new(pos.first, pos.second);
			}
		}

	} // End namespace Plants
} // End namespace World