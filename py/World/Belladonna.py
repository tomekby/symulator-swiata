from World.Plant import Plant


class Belladonna(Plant):
    def get_name(self):
        return "Wilcze jagody"

    # Specyficzna akcja przy kolizji - zabicie organizmu który zjadł
    def collision(self, second):
        self._kill(second)

    # Inicjalizacja
    def _init(self):
        self._SYMBOL = 'j'
        self._strength = 99
