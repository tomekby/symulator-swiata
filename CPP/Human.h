#pragma once
#include "Animal.h"

namespace World {
	namespace Animals {

		class Human : public Animal
		{
			friend class XML::Writer;
			friend class XML::Reader;
		public:
			Human() : Animal() { init(); }
			Human(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { init(); }
			~Human() {};
			console::string get_name() const { return _("Człowiek"); }
			void action();
		private:
			void spawn_new(const int x, const int y) {};
			void move_x(const int d);
			void move_y(const int d);
			size_t move_range() const;
			void init() {
				SYMBOL = L'♂';
				strength = 5;
				initiative = 4;
				bonus_left = before_next_bonus = 0;
			}
			size_t bonus_left; // ilość pozostałych rund działania bonusu
			size_t before_next_bonus; // ilość rund do kolejnego wykorzystania bonusa
		};

	}
}