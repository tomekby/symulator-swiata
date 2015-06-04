#pragma once
#include "Plant.h"

namespace World {
	namespace Plants {

		class Grass : public Plant
		{
		public:
			Grass() : Plant() { init(); };
			Grass(const int x, const int y, World *const world = nullptr) : Plant(x, y, world) { init(); };
			console::string get_name() const { return _("trawa"); }
		private:
			void spawn_new(const int x, const int y);
			void init() {
				strength = 0;
				SYMBOL = 't';
			}
		};
	}
}