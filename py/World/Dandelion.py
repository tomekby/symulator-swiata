from World.Plant import Plant


class Dandelion(Plant):
    def get_name(self):
        return "Mlecz"

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'm'
        self._strength = 0
