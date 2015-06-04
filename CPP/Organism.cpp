#include "Organism.h"
#include "World.h"
#include "console.h"

namespace World {

	Organism::~Organism()
	{
	}

	std::pair<size_t, size_t> Organism::pos() {
		return position;
	}

	void Organism::action() {}

	// Walka pomiędzy 2 organizmami
	void Organism::fight(const Organism& oponent) {
		if (strength > oponent.strength) {
			world->kill(*this, oponent);
		}
		else if (strength < oponent.strength) {
			world->kill(oponent, *this);
		}
		// Siła jest równa, decydują inne czynniki
		else {
			// Zaatakował
			if (initiative < oponent.initiative) {
				world->kill(*this, oponent);
			}
			// Został zaatakowany
			else if (initiative > oponent.initiative) {
				world->kill(oponent, *this);
			}
			// Ta sama inicjatywa, ten jest młodszy → wygrywa
			else if (creation < oponent.creation) {
				world->kill(*this, oponent);
			}
			// Ta sama inicjatywa, ten jest starszy → przegrywa
			else if (creation > oponent.creation) {
				world->kill(oponent, *this);
			}
		}
	}

	bool operator==(const Organism &curr, const Organism &other) {
		return curr.uid == other.uid;
	}

	void Organism::draw() {
		console::IO::gotoxy(position.first + 1, position.second + 1);
		console::out << SYMBOL;
	}

	void Organism::spawn_new(const int x, const int y, Organism *o) {
		world->add_organism(o);
	}

	void Organism::kill(const Organism& o) {
		world->kill(*this, o);
	}

	void Organism::eat(Organism& o) {
		world->eat(*this, o);
		// Wywołanie kolizji aby ew. zmodyfikować ten organizm
		o.collision(this);
	}

	// Pobieranie wg. pozycji w wektorze
	std::shared_ptr<Organism> World::get_by_pos(const size_t pos) {
		if (pos >= organisms.size()) throw std::out_of_range("Zbyt wysoki indeks tablicy!");
		auto el = organisms[pos];
		organisms.erase(organisms.begin() + pos);

		return el;
	}

	// Pobieranie wg. UID organizmu
	std::shared_ptr<Organism> World::get_by_uid(const size_t uid) {
		// Szukanie odpowiedniego organizmu
		auto el_it = std::find_if(organisms.begin(), organisms.end(), [&uid](const org_type &o) { return o->get_uid() == uid; });
		auto el = *el_it;
		// Kasowanie
		if (el_it == organisms.end()) throw std::invalid_argument("Nie ma takiego organizmu!");
		organisms.erase(el_it);

		return el;
	}

} // End namespace World