#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include "Organism.h"
#include "Animal.h"
#include "console.h"
#include <numeric>
#include "XML.h"

namespace World {

	class World
	{
		friend class Organism;
		friend class XML::Writer;
	public:
		typedef std::shared_ptr<Organism> org_type;

		World() { draw_world(); };
		void nextRound();
		void add_organism(Organism* new_org);
		std::shared_ptr<Organism> get_by_pos(const size_t pos);
		std::shared_ptr<Organism> get_by_uid(const size_t uid);
		bool is_free(const size_t x, const size_t y);
		size_t get_N() const { return N; };
		void set_N(const size_t N) { this->N = N; };
		// Template, wiêc l¹duje tu
		template<class T> void random_init(const size_t count = 5) {
			for (size_t i = 0; i < count;) {
				T *tmp = new T(rand() % N, rand() % N); // Mo¿na u¿yæ polimorficznego obiektu, ale skoro u¿ywamy templatów...
				if (is_free(tmp->pos().first, tmp->pos().second)) {
					add_organism(tmp);
					++i;
				}
			}
			// Dodanie oczekuj¹cych
			add_pending();
		}
		void add_event(console::string &msg);
		void draw_world();
		void add_pending();
	private:
		typedef std::tuple<size_t, console::string, size_t> log_entry;

		void kill(const Organism &winner, const Organism &looser);
		void eat(const Organism &a, const Organism &p);
		void remove_pending();
		void draw_organisms();
		void print_instruction(size_t &lineno);

		std::vector<org_type> organisms;
		std::vector<size_t> to_remove; // UID organizmów do skasowania
		std::vector<org_type> to_add; // Lista organizmów do zespawnowania
		std::vector<log_entry> log; // Lista zdarzeñ
		size_t N = 20;
	};

}
