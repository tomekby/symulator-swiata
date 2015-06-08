from Misc import Controller, CantSpawnException


class World(object):
    def __init__(self, rand_class=None, controller_class=None):
        """
        :type rand_class: random.randint
        :type controller_class: Controller
        :return:
        """
        self._rand = rand_class
        self._controller = controller_class

    # Wykonywanie następnej rundy
    def nextRound(self):
        for o in self._organisms:
            if not o.get_uid() in self._to_remove:
                o.action()
        # Sprawdzanie kolizji
        for i, org in enumerate(self._organisms):
            for j, other in enumerate(self._organisms[i + 1:]):
                if self._organisms[j].pos() == self._organisms[i].pos() and self._organisms[j] != self._organisms[i]:
                    try:
                        self._organisms[i].collision_default(self._organisms[j])
                    except CantSpawnException:
                        print("Nie można utworzyć organizmu")
        # Kasowanie niepotrzebnych + rysowanie świata
        self._remove_pending()
        self.draw_world()

    # Dodawanie nowego organizmu do świata
    def add_organism(self, new_org):
        if self.is_free(new_org.pos()):
            new_org.set_world(self)
            self._to_add.append(new_org)

    # Dodawanie oczekujących zwierząt
    def add_pending(self):
        for o in self._to_add:
            ommit = False
            for o2 in self._organisms:
                if o.pos() == o2.pos():
                    ommit = True
            if not ommit:
                self._organisms.append(o)
        self._to_add.clear()
        # Sortowanie aby zachować odpowiednią kolejność
        self._organisms.sort()

    # Czy dane pole jest puste?
    def is_free(self, pos: tuple):
        x, y = pos
        if x < 0 or x >= self._N or y < 0 or y >= self._N:
            return False

        for o in self._organisms:
            if o.pos() == pos:
                return False
        for o in self._to_add:
            if o.pos() == pos:
                return False
        return True

    # Dodawanie wpisu do dziennika
    def add_event(self, msg):
        self._log.append("%d. %s" % (len(self._log) + 1, msg))

    # Rysowanie świata
    def draw_world(self):
        # Porządki
        self._controller.clear_info()
        self._controller.reset_map()

        self._draw_organisms()
        self._print_instruction()
        self._controller.print_info("Dziennik zdarzeń:")
        for msg in self._log:
            self._controller.print_info(msg)
        self._log.clear()

        self.add_pending()

    # Zabijanie organizmu
    def kill(self, winner, looser):
        self.add_event(winner.get_name() + " zabija " + looser.get_name())
        self._to_remove.append(looser.get_uid())

    # Zjadanie organizmu
    def eat(self, animal, plant):
        self.add_event(animal.get_name() + " zjada " + plant.get_name())
        self._to_remove.append(plant.get_uid())

    # Usuwanie oczekujących organizmów
    def _remove_pending(self):
        for id in self._to_remove:
            for o in self._organisms:
                if o.get_uid() == id:
                    self._organisms.remove(o)
                    break
        self._to_remove.clear()

    # Rysowanie organizmów
    def _draw_organisms(self):
        for o in self._organisms:
            o.draw()

    # Wypisanie instrukcji do gry
    def _print_instruction(self):
        instruction = ["Strzałki - poruszanie człowiekiem", "Spacja - umiejętność specjalna człowieka"]
        for s in instruction:
            self._controller.print_info(s)
        self._controller.print_info("\n")

    # Pobieranie klasy kontrolera
    def get_controller(self) -> Controller:
        return self._controller

    # Ustawianie klasy kontrolera
    def set_controller(self, controller: Controller):
        self._controller = controller

    def getN(self):
        return self._N

    def setN(self, n):
        self._N = n

    # Zmienne
    _organisms = []
    _to_remove = []
    _to_add = []
    _log = []
    _N = 20
    # Klasy używane w dependency injection
    _rand = None
    _controller = None
