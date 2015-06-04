#pragma once

#include "Organism.h"
#include "Plant.h"

namespace World {
	namespace Animals {

		class Animal : public Organism
		{
		public:
			Animal() : Organism() { last_position = position; };
			Animal(const int x, const int y, World *const world = nullptr) : Organism(x, y, world) { last_position = position; };
			virtual void action();
			virtual void collision(Organism* with) {};
			void collision_default(Organism* with);
			void inc_strength(size_t s) { strength += s; };
			virtual void go_back();
		protected:
			enum DIRECTIONS { TOP = -1, BOTTOM = 1, LEFT = -1, RIGHT = 1 };

			virtual bool should_fight(Animal *with) { return true; }
			virtual void move_x(const int d);
			virtual void move_y(const int d);
			virtual void eat(Organism *p);
		};

	}
}