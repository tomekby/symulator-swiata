#pragma once
#include "Animal.h"

namespace World {
	namespace Animals {

		class Antelope : public Animal
		{
		public:
			Antelope() : Animal() { init(); }
			Antelope(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { init(); }
			~Antelope() {};
			console::string get_name() const { return _("Antylopa"); }
			void go_back();
		private:
			enum DIRECTIONS { TOP = -2, BOTTOM = 2, LEFT = -2, RIGHT = 2 };

			// 50% szans na ucieczkê
			bool should_fight(Animal *with) { return !(ran_away = (rand() < RAND_MAX / 2)); }
			void collision(Organism* with);
			void spawn_new(const int x, const int y);
			void move_x(const int d);
			void move_y(const int d);
			void init() {
				SYMBOL = 'A';
				strength = 4;
				initiative = 4;
				ran_away = false;
			}

			bool ran_away;
		};

	}
}