import json
import random
import appier
from Misc import Controller
from World.Antelope import Antelope
from World.Belladonna import Belladonna
from World.Dandelion import Dandelion
from World.Fox import Fox
from World.Grass import Grass
from World.Guarana import Guarana
from World.Human import Human
from World.Organism import Organism
from World.Sheep import Sheep
from World.Turtle import Turtle
from World.Wolf import Wolf
from World.World import World

# Entry point dla aplikacji webowej
class Main(appier.App, Controller):

    def __init__(self):
        super(Main, self).__init__()
        self._world = World(random.randint, self)
        self._world.setN(20)

        # Dodawanie organizmów
        # self._world.add_organism(Human((10, 10)))
        org_types = [Antelope, Fox, Sheep, Turtle, Wolf, Belladonna, Dandelion, Grass, Guarana]
        for org_type in org_types:
            self._init_org(10, org_type, random.randint)
        self._world.add_pending()

    # Losowa inicjalizacja organizmami
    def _init_org(self, count, org_type, rand):
        for i in range(count):
            x, y = rand(0, self._world.getN()), rand(0, self._world.getN())
            if self._world.is_free((x, y)):
                new_org = org_type((x, y))
                self._world.add_organism(new_org)

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
        return self.template(
            'index.html',
            world_size=range(self._world.getN()),
            organisms=self._get(self._world._organisms, self._world.getN())
        )

    @appier.route('/human-color', 'GET')
    def human_color(self):
        h = Human(0, 0)
        return self.map_to_color(h._SYMBOL)

    @appier.route('/organisms', 'GET')
    def get_organisms(self):
        organisms = []
        for org in self._printed:
            organisms.append(json.dumps(org))
        return json.dumps(organisms)

    @appier.route('/log', 'GET')
    def get_log(self):
        res = json.dumps(self._log)
        self._log.clear()

        return res

    @appier.route('/next-round', 'GET')
    def next_round(self):
        self._world.nextRound()

    # Wyświetlenie na planszy
    def print(self, xy, text):
        x, y = xy
        self._printed.append((x, y, self.map_to_color(text)))

    # Czyszczenie informacji dodatkowych
    def clear_info(self):
        pass

    # Wypisywanie informacji
    def print_info(self, text):
        self._log.append(text)

    # Wczytywanie znaku (ruchu) człowieka
    def read_char(self):
        pass

    # Resetowanie mapki -> nieużywane
    def reset_map(self):
        pass

    _printed = []
    _world = World
    _log = []
