from World.Animal import Directions, Animal
from World.Organism import Organism


class Antelope(Animal):
    def get_name(self):
        return 'Antylopa'

    # Czy antylopa powinna z czymś walczyć
    def should_fight(self, second: Organism):
        self._ran_away = self._world._rand(0, 1) == 1
        return not self._ran_away

    # Akcja dla kolizji
    def collision(self, second: Organism):
        if not self._ran_away:
            return

        x, y = self._position
        self._move_range = 1
        if self._world.is_free((x + 1, y)):
            self._move_x(Directions.RIGHT)
        elif self._world.is_free((x - 1, y)):
            self._move_x(Directions.LEFT)
        elif self._world.is_free((x, y + 1)):
            self._move_x(Directions.BOTTOM)
        elif self._world.is_free((x, y - 1)):
            self._move_x(Directions.TOP)
        self._move_range = 2

    # Powrót jeśli coś wymusiło
    def go_back(self):
        if not self._ran_away:
            super(Antelope, self).go_back()

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'A'
        self._strength = 4
        self._initiative = 4

    _ran_away = False
    _move_range = 2
