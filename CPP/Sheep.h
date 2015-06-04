#pragma once
#include "Animal.h"

namespace World {
	namespace Animals {

		class Sheep : public Animal
		{
		public:
			Sheep() : Animal() { init(); }
			Sheep(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { init(); }
			~Sheep() {};
			console::string get_name() const { return _("Owca"); }
		private:
			void spawn_new(const int x, const int y);
			void init() {
				SYMBOL = 'O';
				strength = 4;
				initiative = 4;
			}
		};

	}
}