#pragma once
#include "Plant.h"

namespace World {
	namespace Plants {

		class Dandelion : public Plant
		{
		public:
			Dandelion() : Plant() { init(); };
			Dandelion(const int x, const int y, World *const world = nullptr) : Plant(x, y, world) { init(); };
			console::string get_name() const { return _("Mlecz"); }
			void action();
		private:
			void spawn_new(const int x, const int y);
			void init() {
				strength = 0;
				SYMBOL = 'm';
			}
		};
	}
}