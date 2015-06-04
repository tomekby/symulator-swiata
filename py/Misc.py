import abc

# Klasa odpowiedzialna za obsługę IN/OUT
class Controller(object):
    __metaclass__ = abc.ABCMeta

    # Wyświetlenie na planszy
    @abc.abstractclassmethod
    def print(self, xy, text):
        """
        :param xy: (int. int)
        :param text: string
        """

    # Czyszczenie informacji dodatkowych
    @abc.abstractclassmethod
    def clear_info(self):
        pass

    # Wypisywanie informacji
    @abc.abstractclassmethod
    def print_info(self, text):
        """
        :param text: string
        """

    # Wczytywanie znaku (ruchu) człowieka
    @abc.abstractclassmethod
    def read_char(self):
        """
        :return: Directions
        """

    # Resetowanie mapki
    @abc.abstractclassmethod
    def reset_map(self):
        """
        :return: None
        """

    # Mapowanie reprezentacji organizmu na kolor
    def _map_to_color(self, text):
        return {
            'A': '#A3872A',
            'L': '#B84E2E',
            'C': '#66DBED',
            'O': '#C8C8C8',
            'Z': '#0B3B08',
            'W': '#505050',
            'j': '#2314C9',
            'm': '#FF0',
            't': '#0F0',
            'g': '#F00',
        }.get(text, '#000')

# Własne wyjątki
# Nie można stworzyć nowego organizmu
class CantSpawnException(Exception):
    pass

# Nie można wykonać ruchu
class CantMoveException(Exception):
    pass
