#pragma once
#include "Organism.h"

namespace World {
	namespace Plants {

		class Plant : public Organism
		{
		public:
			Plant() : Organism() { initiative = 0; };
			Plant(const int x, const int y, World *const world = nullptr) : Organism(x, y, world) { initiative = 0; };
			virtual void action();
			virtual void collision(Organism* with) {};
		};

	}
}