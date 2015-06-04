#include "World.h"

namespace World {

	void World::nextRound() {
		// Wykonywanie akcji organizmów
		std::for_each(organisms.begin(), organisms.end(), [](org_type o) { o->action(); });
		for (size_t i = 0; i < organisms.size(); ++i) {
			for (size_t j = i + 1; j < organisms.size(); ++j) {
				try {
					if (organisms[j]->pos() == organisms[i]->pos() && organisms[i] != organisms[j]) { // Te same koordynaty
						organisms[i]->collision_default(organisms[j].get());
					}
				}
				catch (std::exception &e) { break; }
			}
		}
		// Kasowanie niepotrzebnych organizmów
		remove_pending();
		// Rysowanie świata
		draw_world();
	};

	//template<class T>
	void World::add_organism(Organism* new_org) {
		if (is_free(new_org->pos().first, new_org->pos().second)) {
			new_org->set_world(this);
			to_add.push_back(org_type(new_org));
		}
	}

	// Sprawdzanie, czy określone pole na mapie jest wolne
	bool World::is_free(const size_t x, const size_t y) {
		if (x < 0 || x >= N || y < 0 || y >= N) return false;

		const auto pos = std::make_pair(x, y);
		auto predicate = [&pos](org_type o) { return o->pos() == pos; };
		return std::none_of(organisms.begin(), organisms.end(), predicate) &&
			std::none_of(to_add.begin(), to_add.end(), predicate);
	}

	void World::kill(const Organism &winner, const Organism &looser) {
		add_event(winner.get_name() + _(" zabija ") + looser.get_name());
		to_remove.push_back(looser.get_uid());
	}

	void World::eat(const Organism &a, const Organism &p) {
		add_event(a.get_name() + _(" zjada ") + p.get_name());
		to_remove.push_back(p.get_uid());
	}

	// Kasowanie elementów oznaczonych do usunięcia
	void World::remove_pending() {
		organisms.erase(
			std::remove_if(organisms.begin(), organisms.end(), [this](org_type el) { 
				return std::any_of(to_remove.begin(), to_remove.end(), [&el](size_t r) { return el->get_uid() == r; });
			}), organisms.end());
		// Wyczyszczenie listy do usunięcia
		to_remove.clear();
	}

	void World::add_pending() {
		for (auto &o : to_add) organisms.push_back(o);
		to_add.clear();
	}

	void World::print_instruction(size_t &lineno) {
		console::IO::gotoxy(N + 3, lineno++);
		console::IO::print(_("Klawisze: \n"));
		console::IO::gotoxy(N + 3, lineno++);
		console::IO::print(_("n - następna tura"));
		console::IO::gotoxy(N + 3, lineno++);
		console::IO::print(_("a - aktywacja umiejętności człowieka\n"));
		console::IO::gotoxy(N + 3, lineno++);
		console::IO::print(_("s - zapis symulacji w pliku world.xml"));
		console::IO::gotoxy(N + 3, lineno++);
		console::IO::print(_("o - otwarcie pliku world.xml z zapisem symulacji"));
		console::IO::gotoxy(N + 3, lineno++);
		console::IO::print(_("q - wyjście i zapis symulacji w pliku world.xml"));
		console::IO::gotoxy(N + 3, lineno++);
		console::IO::print(_("←↑↓→ - ruch człowieka po planszy"));
	}

	void World::draw_world() {
		console::IO::cls();
		console::IO::print(_("╔") + console::string(N, _('═')) + _("╗")); // Pierwsza linia
		// Wewnętrzne linie
		for (size_t i = 0; i < N; ++i) {
			console::IO::print(_("║") + console::string(N, _(' ')) + _("║"));
		}
		console::IO::print(_("╚") + console::string(N, _('═')) + _("╝")); // Ostatnia linia

		// Rysowanie organizmów
		draw_organisms();

		size_t lineno = 0;
		// Instrukcja
		print_instruction(lineno);
		// Wypisywanie dziennika dla tej tury
		console::IO::gotoxy(N + 3, lineno += 2);
		console::IO::print(_("Dziennik zdarzeń:"));
		std::for_each(log.begin(), log.end(), [&lineno, this](log_entry &evt) {
			console::IO::gotoxy(N + 3, ++lineno);
			console::IO::print(std::to_wstring(std::get<0>(evt)) + _(". ") + std::get<1>(evt) + _(" (x") + std::to_wstring(std::get<2>(evt)) + _(")"));
		});
		console::IO::gotoxy(0, N + 2);
		log.clear();

		// Dopisanie zespawnowanych
		for (auto v : to_add) organisms.push_back(v);
		to_add.clear();
		std::sort(organisms.begin(), organisms.end());
	}

	// Rysowanie organizmów
	void World::draw_organisms() {
		std::for_each(organisms.begin(), organisms.end(), [](org_type &o) { o->draw(); });
	}

	// Dodawanie zdarzenia do dziennika
	void World::add_event(console::string &msg) {
		auto prev = std::find_if(log.begin(), log.end(), [&msg](log_entry &e) { return std::get<1>(e) == msg; });
		// Nie ma jeszcze
		if (prev == log.end()) {
			auto entry = std::make_tuple(log.size() + 1, msg, 1);
			log.push_back(entry);
		}
		// Był taki wpis, inkrementacja licznika wystąpień
		else ++std::get<2>(*prev);
	}
} // End namespace World 
