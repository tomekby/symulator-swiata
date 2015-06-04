from World.Animal import Animal


class Sheep(Animal):
    def get_name(self):
        return 'Owca'

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'O'
        self._strength = 4
        self._initiative = 4
