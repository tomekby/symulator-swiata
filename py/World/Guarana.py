from World.Organism import Organism
from World.Plant import Plant


class Guarana(Plant):
    def get_name(self):
        return "Guarana"

    # Specyficzna akcja przy kolizji - zwiększenie siły
    def collision(self, second: Organism):
        try:
            second.inc_strength(3)
        except AttributeError:
            pass

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'g'
        self._strength = 0
