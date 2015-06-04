from World.Animal import *


class Fox(Animal):
    def get_name(self):
        return 'Lis'

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'L'
        self._strength = 3
        self._initiative = 7

    # Ruch w poziomie
    def _move_x(self, d: Directions):
        x, y = self._position
        if self._world.is_free((x + int(d), y)):
            super(Fox, self)._move_x(d)
        elif self._world.is_free((x - int(d), y)):
            super(Fox, self)._move_x(-d)
        elif self._world.is_free((x, y + int(d))):
            super(Fox, self)._move_y(Directions.TOP)
        elif self._world.is_free((x, y - int(d))):
            super(Fox, self)._move_y(Directions.BOTTOM)
        else:
            raise NotImplementedError

    # Ruch w pionie
    def _move_y(self, d: Directions):
        x, y = self._position
        if self._world.is_free((x, y + d)):
            super(Fox, self)._move_y(d)
        elif self._world.is_free((x, y - d)):
            super(Fox, self)._move_y(-d)
        elif self._world.is_free((x - 1, y)):
            super(Fox, self)._move_x(Directions.LEFT)
        elif self._world.is_free((x + 1, y)):
            super(Fox, self)._move_x(Directions.RIGHT)
        else:
            raise NotImplementedError
