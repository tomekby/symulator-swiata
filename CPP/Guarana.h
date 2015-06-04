#pragma once
#include "Plant.h"

namespace World {
	namespace Plants {

		class Guarana : public Plant
		{
		public:
			Guarana() : Plant() { init(); };
			Guarana(const int x, const int y, World *const world = nullptr) : Plant(x, y, world) { init(); };
			console::string get_name() const { return _("Guarana"); }
			void collision(Organism* with);
		private:
			void spawn_new(const int x, const int y);
			void init() {
				strength = 0;
				SYMBOL = 'g';
			}
		};
	}
}