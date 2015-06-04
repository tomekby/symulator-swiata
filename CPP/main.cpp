#include "console.h"
#ifdef _DEBUG // Dostajemy OutputDebugString umożliwiające pisanie do debuggera
#	include <..\um\debugapi.h>
#else
#	define OutputDebugString(x)
#endif

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <memory>
#include <fstream>
#include "World.h"
#include "Animals.h"
#include "Plants.h"
#include "XML.h"
#include "XML_ext.h"

int main() {
	namespace Animal = World::Animals;
	namespace Plant  = World::Plants;

	srand( static_cast<unsigned>(time(nullptr)) );
	console::IO::title(_("Tomasz Stasiak 155197"));
	console::IO::cls(); // Czyszczenie ekranu jakby coś było wcześniej uruchamiane itp.

	World::World world;
	// Zwierzęta
	world.random_init<Animal::Wolf>(); // Wilki
	world.random_init<Animal::Sheep>(); // Owce
	world.random_init<Animal::Fox>(); // Lisy
	world.random_init<Animal::Turtle>(); // Żółwie
	world.random_init<Animal::Antelope>(); // Żółwie
	// Rośliny
	world.random_init<Plant::Grass>(); // Trawa
	world.random_init<Plant::Dandelion>(); // Mlecz
	world.random_init<Plant::Guarana>(); // Guarana
	world.random_init<Plant::Belladonna>(); // Wilcze jagody
	// Człowiek na koniec
	world.random_init<Animal::Human>(1); // Człek
	world.draw_world();
	 
	//// Transfer pomiędzy obiektami
	//World::World world2;
	//world2.add_organism(world.get_by_pos(0).get());
	
	char c = 0;
	// Główna pętla "gry"
	do {
		if (c == 'n') world.nextRound();
		// Zapis stanu "gry"
		else if (c == 's') {
			// Dodanie info
			world.add_event(console::string(_("Zapis stanu symulacji")));
			XML::Writer w(_("world.xml"));
			w.get_xml(world);
			w.save();
		}
		// Wczytywanie z XMLa
		else if (c == 'o') {
			XML::Reader file(_("world.xml"));
			file = file.get_node(_("world"));
			// Reset świata
			world = World::World();
			world.set_N( std::stoi(file.attrib(_("size"))) ); // Wielkość świata
			// Inicjalizacja z XMLa
			XML::Reader::init_from_xml(&world, file.get_nodes(_("organism")));

			// Dodanie info
			world.add_event(console::string(_("Wczytanie stanu symulacji")));
			// Start + narysowanie
			world.add_pending();
			world.draw_world();
		}
	} while ((c = console::IO::getch()) != 'q');

	// Zapis XMLa (automatycznie, w destruktorze)
	XML::Writer w(_("world.xml"));
	w.get_xml(world);

	return 0;
}