from Misc import CantMoveException
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
            super(Fox, self)._move_x(Directions.LEFT if d is Directions.RIGHT else Directions.RIGHT)
        elif self._world.is_free((x, y + int(Directions.TOP))):
            super(Fox, self)._move_y(Directions.TOP)
        elif self._world.is_free((x, y - int(Directions.BOTTOM))):
            super(Fox, self)._move_y(Directions.BOTTOM)
        else:
            raise CantMoveException

    # Ruch w pionie
    def _move_y(self, d: Directions):
        x, y = self._position
        if self._world.is_free((x, y + int(d))):
            super(Fox, self)._move_y(d)
        elif self._world.is_free((x, y - int(d))):
            super(Fox, self)._move_y(Directions.BOTTOM if d is Directions.TOP else Directions.TOP)
        elif self._world.is_free((x - int(Directions.LEFT), y)):
            super(Fox, self)._move_x(Directions.LEFT)
        elif self._world.is_free((x + int(Directions.RIGHT), y)):
            super(Fox, self)._move_x(Directions.RIGHT)
        else:
            raise CantMoveException
