import abc
from World.Organism import Organism


class Plant(Organism):
    __metaclass__ = abc.ABCMeta

    def __init__(self, pos=None, world=None):
        super(Plant, self).__init__(pos, world)
        self._initiative = 0

    # Akcja - rozmnażanie rośliny
    def action(self):
        if self._world._rand(0, 3) == 1:
            x, y = self._position
            if self._world.is_free((x + 1, y)):
                x += 1
            elif self._world.is_free((x - 1, y)):
                x -= 1
            elif self._world.is_free((x, y + 1)):
                y += 1
            elif self._world.is_free((x, y - 1)):
                y -= 1
            self._spawn_new((x, y))
