import abc
from World.Organism import Organism
from enum import Enum

class Directions(Enum):
    TOP = 0
    BOTTOM = 1
    LEFT = 2
    RIGHT = 3
    SPECIAL = 0xDEADBEEF

    def __int__(self):
        print(self.value)
        return {
            0: -1, 1: 1,
            2: -1, 3: 1
        }.get(self.value, 0xDEADBEEF)


class Animal(Organism):
    __metaclass__ = abc.ABCMeta

    def __init__(self, pos=None, world=None):
        super(Animal, self).__init__(pos, world)
        self._last_pos = pos

    # Ruch w płaszczyźnie poziomej
    def _move_x(self, d: Directions):
        x, y = self._position
        if d is Directions.LEFT:
            self._make_move(lambda i: x - i >= 0, lambda i: (x - i, y))
        elif d is Directions.RIGHT:
            self._make_move(lambda i: x + i < self._world.getN(), lambda i: (x + i, y))

    # Ruch w płaszczyźnie pionowej
    def _move_y(self, d: Directions):
        x, y = self._position
        if d is Directions.TOP:
            self._make_move(lambda i: y - i >= 0, lambda i: (x, y - i))
        elif d is Directions.BOTTOM:
            self._make_move(lambda i: y + i < self._world.getN(), lambda i: (x, y + i))

    # Wewnętrzna pętla ustalająca zakres ruchu
    def _make_move(self, pred, mk_tuple):
        """
        :type pred: lambda -> bool
        :type mk_tuple: lambda -> tuple
        """
        for i in range(self._range(), 0, -1):
            if pred(i):
                self._position = mk_tuple(i)
                break

    # Wykonywanie akcji dla organizmu
    def action(self):
        try:
            res = {
                0: lambda: self._move_y(Directions.TOP),
                1: lambda: self._move_y(Directions.BOTTOM),
                2: lambda: self._move_x(Directions.LEFT),
                3: lambda: self._move_x(Directions.RIGHT)
            }
            res[self._world._rand(0, 3)]()
        except NotImplementedError:
            print("Nie można wykonać ruchu")

        super(Animal, self).action()

    # Kolizja z innym organizmem
    def collision(self, second: Organism):
        super(Animal, self).collision(second)

    def should_fight(self, second: Organism):
        return True

    # Domyślna akcja dla kolizji
    def collision_default(self, second: Organism):
        x, y = self._position
        if self.get_symbol() == second.get_symbol():
            if self._world.is_free((x - 1, y)):
                self._spawn_new((x - 1, y))
            elif self._world.is_free((x + 1, y)):
                self._spawn_new((x + 1, y))
            elif self._world.is_free((x, y - 1)):
                self._spawn_new((x, y - 1))
            elif self._world.is_free((x, y + 1)):
                self._spawn_new((x, y + 1))
            else:
                # @todo: własny wyjątek
                raise NotImplementedError
            self._world.add_event(self.get_name() + " się rozmnaża")
        else:
            try:
                if self.should_fight(second) and second.should_fight(self):
                    self._fight(second)
                else:
                    self.collision(second)
                    second.collision(self)
            except AttributeError:
                self._eat(second)

    # Zwiększenie siły
    def inc_strength(self, inc_by):
        self._strength += inc_by

    # Cofanie się
    def go_back(self):
        self._position = self._last_pos

    # Zakres ruchu
    def _range(self):
        return self._move_range

    _move_range = 1
