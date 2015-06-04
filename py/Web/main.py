import random
import appier
from World.Grass import Grass
from World.Organism import Organism
from World.World import World
import jsonpickle

# Entry point dla aplikacji webowej
class Main(appier.App):

    def __init__(self):
        super(Main, self).__init__()
        self._world = World(random.randint, self)

    # konwersja na tablicę 2d
    @staticmethod
    def _get(orgs, n):
        """
        :type orgs: list[Organism]
        """
        res = [[None] * n for i in range(n)]
        for org in orgs:
            x, y = org.pos()
            res[x][y] = org
        return res

    # Strona domowa
    @appier.route('/', 'GET')
    def home(self):
        # world = World(random.randint, self)
        self._world.add_organism(Grass((self._world._rand(0, 19), self._world._rand(0, 19))))
        self._world.add_pending()

        return self.template(
            'index.html',
            world_size=range(self._world.getN()),
            organisms=self._get(self._world._organisms, self._world.getN())
        )

    @appier.route('/organisms', 'GET')
    def get_organisms(self):
        return jsonpickle.encode(self._world._organisms)

    _world = World
