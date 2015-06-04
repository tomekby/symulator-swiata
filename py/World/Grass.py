from World.Plant import Plant


class Grass(Plant):
    def get_name(self):
        return "Trawa"

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 't'
        self._strength = 0
