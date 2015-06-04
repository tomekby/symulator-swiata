import abc
from functools import total_ordering
import time
import uuid

from World.World import World

@total_ordering
class Organism(object):
    __metaclass__ = abc.ABCMeta

    def __init__(self, pos=None, world=None):
        if pos is None:
            pos = (0, 0)
        if world is None:
            world = World
        self._world = world
        self._position = pos
        self._creation = time.time()
        self._uid = uuid.uuid4()
        self._last_pos = pos

        self._init()

    # Ustawianie świata
    def set_world(self, world):
        self._world = world

    # Wykonywanie akcji
    def action(self):
        pass

    # Szczególna akcja dla kolizji
    def collision(self, second):
        pass

    # Domyślna akcja kolizji
    def collision_default(self, second):
        pass

    # Pozycja na świecie
    def pos(self):
        return self._position

    # "Rysowanie" organizmu
    def draw(self):
        self._world.get_controller().print(self._position, self._SYMBOL)

    # Getter dla inicjatywy
    def get_initiative(self):
        return self._initiative

    # Getter dla siły
    def get_strength(self):
        return self._strength

    # Getter dla nazwy
    @abc.abstractclassmethod
    def get_name(self):
        """
        :return: Czytelna nazwa zwierzęcia
        """

    # Getter dla id
    def get_uid(self):
        return self._uid

    # Getter dla symbolu
    def get_symbol(self):
        return self._SYMBOL

    def _kill(self, o):
        self._world.kill(self, o)

    def _eat(self, o):
        """
        :type o: Organism
        """
        self._world.eat(self, o)
        o.collision(self)

    def _fight(self, opponent):
        """
        :type opponent: Organism
        """
        if self._strength > opponent._strength:
            self._world.kill(self, opponent)
        elif self._strength < opponent._strength:
            self._world.kill(opponent, self)
        else:
            # wygrywa atakujący
            if self._initiative < opponent._initiative:
                self._world.kill(self, opponent)
            elif self._initiative > opponent._initiative:
                self._world.kill(opponent, self)
            # wygrywa młodszy
            elif self._creation < opponent._creation:
                self._world.kill(self, opponent)
            elif self._creation > opponent._creation:
                self._world.kill(opponent, self)

    def _spawn_new(self, xy):
        self._world.add_organism(type(self)(xy, self._world))

    @abc.abstractclassmethod
    def _init(self):
        """
        Ręczna inicjalizacja klasy
        """

    # Operator porównania ==
    def __eq__(self, other):
        """
        :type other: Organism
        :return: True jeśli ten sam obiekt
        """
        try:
            return self._uid == other._uid
        except AttributeError:
            return False

    # Porównanie
    def __lt__(self, other):
        """
        :type other: Organism
        :return: True jeśli self < other
        """
        if self._initiative != other._initiative:
            return self._initiative > other._initiative
        return self._creation < other._creation

    _world = World
    _strength = 0
    _initiative = 0
    _position = (0, 0)
    _uid = 0
    _SYMBOL = '?'
    _creation = 0
    _last_pos = ()
