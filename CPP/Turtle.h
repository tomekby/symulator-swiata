#pragma once
#include "Animal.h"

namespace World {
	namespace Animals {

		class Turtle : public Animal
		{
		public:
			Turtle() : Animal() { init(); }
			Turtle(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { init(); }
			~Turtle() {};
			void action();
			void colision(const Organism& with);
			console::string get_name() const { return _("¯ó³w"); }
		private:
			bool should_fight(Animal *with) { return with->get_strength() >= 5; }
			void collision(Organism* with);
			void spawn_new(const int x, const int y);
			void init() {
				SYMBOL = L'¯';
				strength = 2;
				initiative = 1;
			}
		};

	}
}