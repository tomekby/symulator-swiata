from World.Animal import Animal
from World.Organism import Organism


class Turtle(Animal):
    def get_name(self):
        return 'Żółw'

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'Z'
        self._strength = 2
        self._initiative = 1

    # Żółw ma 25% szans na ruch
    def action(self):
        if self._world._rand(0, 4) == 1:
            super(Turtle, self).action()

    # Czy żółw powinien walczyć?
    def should_fight(self, second: Organism):
        return second._strength >= 5

    # Akcja przy kolizji
    def collision(self, second: Organism):
        try:
            second.go_back()
            self._world.add_event("Żółw zmusza do wycofania %s" % second.get_name())
        except AttributeError:
            pass
