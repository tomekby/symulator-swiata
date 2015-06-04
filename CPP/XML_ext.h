#pragma once
#include "XML.h"
#include "World.h"
#include "Animals.h"
#include "Plants.h"

/**
 * Specjalizacje dla XML readera/writera umo¿liwiaj¹ce serializacjê obiektów
 * Wzorzec Data-Mapper
 */
namespace XML {
	// Rozszerzenie umo¿liwiaj¹ce zapis organizmu do XMLa
	template<>
	console::string Writer::get_xml(const World::World::org_type &o) {
		console::string s = _("<organism");
		s += _(" uid=\"") + std::to_wstring(o->uid) + _("\"");
		s += _(" strength=\"") + std::to_wstring(o->strength) + _("\"");
		s += _(" initiative=\"") + std::to_wstring(o->initiative) + _("\"");
		s += _(" creation=\"") + std::to_wstring(o->creation.time_since_epoch().count()) + _("\"");
		s += _(" symbol=\"") + std::to_wstring(o->SYMBOL) + _("\"");
		s += _(" pos_x=\"") + std::to_wstring(o->position.first) + _("\" pos_y=\"") + std::to_wstring(o->position.second) + _("\"");
		s += _(" last-pos_x=\"") + std::to_wstring(o->position.first) + _("\" last-pos_y=\"") + std::to_wstring(o->position.second) + _("\"");
		// Cz³owiek jest obs³ugiwany inaczej
		auto human = dynamic_cast<World::Animals::Human*>(o.get());
		if (human != nullptr) {
			s += _(" bonus_left=\"") + std::to_wstring(human->bonus_left) + _("\" before_next_bonus=\"") + std::to_wstring(human->before_next_bonus) + _("\"");
		}
		s += _("></organism>");
		add_xml(s);

		return s;
	}
	// Rozszerzenie umo¿liwiaj¹ce zapis œwiata do XMLa
	template<>
	console::string Writer::get_xml(const World::World &w) {
		add_xml(_("<world size=\"") + std::to_wstring(w.N) + _("\">"));
		for (auto &o : w.organisms) get_xml(o);
		add_xml(console::string(_("</world>")));

		return _content;
	}
	// Inicjalizacja organizmu z XMLa
	template<>
	void Reader::init_from_xml(World::Organism *o, const attribs_t &vals) {
		// Cz³owiek jest obs³ugiwany inaczej
		auto human = dynamic_cast<World::Animals::Human*>(o);
		for (auto &v : vals) {
			if (v.first == _("strength")) o->strength = std::stoul(v.second);
			else if (v.first == _("initiative")) o->initiative = std::stoul(v.second);
			else if (v.first == _("uid")) o->uid = std::stoul(v.second);
			else if (v.first == _("symbol")) o->SYMBOL = std::stoi(v.second);
			else if (v.first == _("last-pos_x")) o->last_position.first = std::stoi(v.second);
			else if (v.first == _("last-pos_y")) o->last_position.second = std::stoi(v.second);
			else if (v.first == _("creation")) {
				auto epoch = std::chrono::time_point<std::chrono::high_resolution_clock>();
				auto since_epoch = std::chrono::milliseconds(std::stoull(v.second));
				o->creation = epoch + since_epoch;
			}
			// Cz³owiek jest obs³ugiwany inaczej
			if (human != nullptr) {
				if (v.first == _("bonus_left")) human->bonus_left = std::stoi(v.second);
				else if (v.first == _("before_next_bonus")) human->before_next_bonus = std::stoi(v.second);
			}
		}
	}
	// Inicjalizacja œwiata z XMLa
	template<>
	void Reader::init_from_xml(World::World *world, const Reader::nodes_t &nodes) {
		namespace Animal = World::Animals;
		namespace Plant = World::Plants;

		// Funkcje pomocnicze do wczytywania
		auto stoi = [](XML::Reader &o, const console::string &s) { return std::stoi(o.attrib(s)); };
		auto pair = [](XML::Reader &o, const console::string &s) { return std::make_pair(s, o.attrib(s)); };

		for (size_t i = 0; i < nodes.second; ++i) {
			auto o = nodes.first[i];
			World::Organism *tmp = nullptr;
			XML::Reader::attribs_t attribs;
			const auto POS_X = stoi(o, _("pos_x")), POS_Y = stoi(o, _("pos_y")), SYMBOL = std::stoi(o.attrib(_("symbol")));
			// Tworzenie obiektu
			if (SYMBOL == 'A') tmp = new Animal::Antelope(POS_X, POS_Y); // Antylopa
			else if (SYMBOL == 'L') tmp = new Animal::Fox(POS_X, POS_Y); // Lis
			else if (SYMBOL == 'O') tmp = new Animal::Sheep(POS_X, POS_Y); // Owca
			else if (SYMBOL == 379) tmp = new Animal::Turtle(POS_X, POS_Y); // ¯ó³w
			else if (SYMBOL == 'W') tmp = new Animal::Wolf(POS_X, POS_Y); // Wilk
			// Roœliny
			else if (SYMBOL == 'g') tmp = new Plant::Guarana(POS_X, POS_Y); // Guarana
			else if (SYMBOL == 't') tmp = new Plant::Grass(POS_X, POS_Y); // Trawa
			else if (SYMBOL == 'd') tmp = new Plant::Dandelion(POS_X, POS_Y); // Mlecz
			else if (SYMBOL == 'j') tmp = new Plant::Belladonna(POS_X, POS_Y); // Mlecz
			// Cz³owiek
			else if (SYMBOL == 9794) {
				tmp = new Animal::Human(POS_X, POS_Y);
				// Specyficzne dla cz³owieka
				for (auto &n : { _("bonus_left"), _("before_next_bonus") }) {
					attribs.push_back(pair(o, n));
				}
			}

			// Coœ by³o
			if (tmp != nullptr) {
				// Dodanie atrybutów
				for (auto &n : { _("strength"), _("initiative"), _("uid"), _("symbol"), _("last-pos_x"), _("last-pos_y"), _("creation") }) {
					attribs.push_back(pair(o, n));
				}
				// Inicjalizacja
				XML::Reader::init_from_xml(tmp, attribs);
				// Zapis do œwiata
				world->add_organism(tmp);
			}
		} // End for
	}
}
