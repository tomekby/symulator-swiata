#pragma once
#include "Animal.h"

namespace World {
	namespace Animals {

		class Wolf : public Animal
		{
		public:
			Wolf() : Animal() { init(); }
			Wolf(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { init(); }
			~Wolf() {};
			console::string get_name() const { return _("Wilk"); }
		private:
			void spawn_new(const int x, const int y);
			void init() {
				SYMBOL = 'W';
				strength = 9;
				initiative = 5;
			}
		};

	}
}