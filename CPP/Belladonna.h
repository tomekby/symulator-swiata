#pragma once
#include "Plant.h"

namespace World {
	namespace Plants {

		// Wilcze jagody
		class Belladonna : public Plant
		{
		public:
			Belladonna() : Plant() { init(); };
			Belladonna(const int x, const int y, World *const world = nullptr) : Plant(x, y, world) { init(); };
			console::string get_name() const { return _("Wilcze jagody"); }
			void collision(Organism* with);
		private:
			void spawn_new(const int x, const int y);
			void init() {
				strength = 99;
				SYMBOL = 'j';
			}
		};
	}
}