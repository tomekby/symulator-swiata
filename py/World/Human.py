from World.Animal import *


class Human(Animal):
    def get_name(self):
        return 'Człowiek'

    # Nowy organizm tego gatunku
    def _spawn_new(self, xy):
        pass

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'C'
        self._strength = 5
        self._initiative = 4

    # Uwzględnianie działania umiejętności specjalnej
    def _ability(self):
        if self._bonus_left == 0:
            self._move_range = 1
        elif self._bonus_left > 2:
            self._move_range = 2
        else:
            self._move_range = self._world._rand(1, 2)

    # Specjalne poruszanie człowiekiem
    def action(self):
        move = self._world.get_controller().read_char()
        if move is Directions.SPECIAL:
            if self._bonus_left == 0 and self._before_next_bonus == 0:
                self._bonus_left = 5
            move = self._world.get_controller().read_char()

        self._ability()
        if move is Directions.TOP or move is Directions.BOTTOM:
            self._move_y(move)
        elif move is Directions.LEFT or move is Directions.RIGHT:
            self._move_x(move)

        if self._bonus_left == 1:
            self._before_next_bonus = 6
            self._bonus_left = 0
        elif self._bonus_left > 0:
            self._bonus_left -= 1
        elif self._bonus_left == 0 and self._before_next_bonus > 0:
            self._before_next_bonus -= 1

    _bonus_left = 0
    _before_next_bonus = 0
