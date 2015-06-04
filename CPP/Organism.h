#pragma once

#include <cstdlib>
#include <utility>
#include <chrono>
#include <algorithm>
#include <typeinfo>
#include <string>
#include <functional>
#include <memory>
#include <vector>
#include "console.h"
#include "XML.h"

namespace World {

	class World;

	class NoPlaceToSpawn : public std::exception {
	public:
		explicit NoPlaceToSpawn(const char *msg) : msg(msg) {}
		explicit NoPlaceToSpawn(const std::string &msg) : msg(msg) {}
		virtual const char* what() const {
			return msg.c_str();
		}
		virtual const wchar_t* wwhat() const {
			std::wstring m;
			m.assign(msg.begin(), msg.end());
			return m.c_str();
		}
	private:
		std::string msg;
	};

	class Organism
	{
		friend class XML::Writer;
		friend class XML::Reader;
	public:
		Organism() : Organism(0, 0, nullptr) {}
		Organism(const int x, const int y, World *const world = nullptr) : position(std::make_pair(x, y)), creation(chrono_type::now()) {
			uid = std::hash<unsigned>()(rand()) ^ (std::hash<time_t>()(chrono_type::to_time_t(creation)) << 1);
		}
		void set_world(World *const world) {
			this->world = world;
		}
		virtual ~Organism();
		virtual void action();
		virtual void collision(Organism* with) {}
		virtual void collision_default(Organism* with) {}
		std::pair<size_t, size_t> pos();
		friend bool operator==(const Organism &curr, const Organism &other);
		friend bool operator<(std::shared_ptr<Organism> a, std::shared_ptr<Organism> b) {
			if (a->initiative != b->initiative) return a->initiative > b->initiative;
			return a->creation < b->creation;
		}
		void draw();
		size_t get_initiative() const { return initiative; };
		size_t get_strength() const { return strength; };
		virtual console::string get_name() const = 0;
		size_t get_uid() const { return uid; }
		size_t get_symbol() const { return SYMBOL; }
	protected:
		typedef std::chrono::high_resolution_clock chrono_type;
		typedef chrono_type::time_point time_type;

		virtual void kill(const Organism& o);
		virtual void eat(Organism& o);
		virtual void fight(const Organism& oponent);
		virtual void spawn_new(const int x, const int y) = 0;
		virtual void spawn_new(const int x, const int y, Organism *o);
		virtual void init() = 0;

		World *world;
		size_t strength;
		size_t initiative;
		std::pair<int, int> position;
		time_type creation;
		// Unikalne ID obiektu
		size_t uid;
		wchar_t SYMBOL = '?';

		std::pair<int, int> last_position;
	};

} // End namespace World