from World.Animal import Animal


class Wolf(Animal):
    def get_name(self):
        return 'Wilk'

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'W'
        self._strength = 9
        self._initiative = 5
