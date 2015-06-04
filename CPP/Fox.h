#pragma once
#include "Animal.h"

namespace World {
	namespace Animals {

		class Fox : public Animal
		{
		public:
			Fox() : Animal() { init(); }
			Fox(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { init(); }
			~Fox() {};
			console::string get_name() const { return _("Lis"); }
		private:
			void move_x(const int d);
			void move_y(const int d);
			void spawn_new(const int x, const int y);
			void init() {
				SYMBOL = 'L';
				strength = 3;
				initiative = 7;
			}
		};

	}
}