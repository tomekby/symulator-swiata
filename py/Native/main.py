import random
from PySide import QtCore, QtGui
from PySide.QtCore import Qt, QObject, SIGNAL, SLOT
from Mapper.XML import MapWorld
from Misc import Controller
from World.Animal import Directions
from World.Antelope import Antelope
from World.Belladonna import Belladonna
from World.Dandelion import Dandelion
from World.Fox import Fox
from World.Grass import Grass
from World.Guarana import Guarana
from World.Human import Human
from World.Sheep import Sheep
from World.Turtle import Turtle
from World.Wolf import Wolf
from World.World import World


class HumanMoveWnd(QtGui.QDialog):
    def __init__(self, parent=None):
        super(HumanMoveWnd, self).__init__(parent)

        self._parent = parent
        self.setFixedSize(500, 70)
        self.setWindowFlags(QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint | QtCore.Qt.Popup)
        self.setWindowOpacity(0.8)
        self.setStyleSheet("background-color: rgb(50, 50, 50);")
        self.setModal(True)

        # Layout
        vbox = QtGui.QVBoxLayout(self)
        vbox.setAlignment(Qt.AlignHCenter)
        label_font = QtGui.QFont("Arial", 20, QtGui.QFont.Bold)
        label = QtGui.QLabel("Oczekiwanie na ruch człowieka...")
        label.setFont(label_font)
        vbox.addWidget(label)
        self.setLayout(vbox)

    # Po pokazaniu okienka ustawienie focusa
    def showEvent(self, evt):
        self.activateWindow()
        self.setFocus()

        super(HumanMoveWnd, self).showEvent(evt)

    # Blokowanie zamknięcia na esc
    def keyPressEvent(self, evt):
        if evt.key() != Qt.Key_Escape:
            super(HumanMoveWnd, self).keyPressEvent(evt)

    # Obsługa ruchu człowieka
    def keyReleaseEvent(self, e):
        try:
            res_key = {
                Qt.Key_Space: Directions.SPECIAL,
                Qt.Key_Left: Directions.LEFT,
                Qt.Key_Right: Directions.RIGHT,
                Qt.Key_Up: Directions.TOP,
                Qt.Key_Down: Directions.BOTTOM
            }[e.key()]

            self._parent._res_key = res_key
            self.close()
        except KeyError:
            pass

    # Wyłączenie alt-f4
    def closeEvent(self, evt):
        evt.setAccepted(not evt.spontaneous())

# Widget po którym rysujemy - plansza gry
class GameBoard(QtGui.QWidget):
    def __init__(self, parent=None, start_x=0, start_y=0):
        super(GameBoard, self).__init__(parent)

        w, h = 600 + start_x, 600 + start_y
        self._start_x, self._start_y = start_x, start_y
        self.setFixedSize(w, h)

    # Redraw
    def paintEvent(self, e):
        qp = QtGui.QPainter()
        qp.begin(self)
        self.draw(qp)
        qp.end()

        self._should_redraw = False

    # Funkcja odpowiedzialna za odrysowanie planszy
    def draw(self, qp):
        qp.setBrush(QtGui.QColor("#fff"))
        for i in range(20):
            for j in range(20):
                qp.drawRect(self._start_x + 29*i, self._start_y + 29*j, 29, 29)

        for point in self._draw_at:
            x, y, color = point
            qp.setBrush(color)
            qp.drawRect(self._start_x + 29*x, self._start_y + 29*y, 29, 29)

    # Funkcja kolejkująca coś do narysowania
    def draw_at(self, x, y, color):
        self._draw_at.append((x, y, color))

    _draw_at = []
    _should_redraw = False

# Entry point dla aplikacji natywnej (PySide)
class Main(QtGui.QWidget, Controller):
    def __init__(self):
        super(Main, self).__init__()

        self._world = World(random.randint, self)
        self._world.setN(20)
        # Dodawanie organizmów
        org_types = [Antelope, Fox, Sheep, Turtle, Wolf, Belladonna, Dandelion, Grass, Guarana]
        for org_type in org_types:
            self._init_org(10, org_type, random.randint)
        self._world.add_organism(Human((10, 10)))
        self._world.add_pending()

        # GUI
        # To okno
        self._menu_bar_h = 20
        x, y, w, h = 300, 50, 870, 600 + self._menu_bar_h
        self.setGeometry(x, y, w, h)
        self.setFixedSize(w, h)
        self.setWindowTitle("Tomasz Stasiak 155197")
        hbox = QtGui.QHBoxLayout(self)
        menu_bar = QtGui.QMenuBar(self)
        menu_bar.setGeometry(0, 0, w, self._menu_bar_h)

        # Akcje w menu
        self._game_start = menu_bar.addAction("Start gry")
        self._next_round = menu_bar.addAction("Następna runda")
        self._next_round.setVisible(False)
        save_game = menu_bar.addAction("Zapisz stan")
        load_game = menu_bar.addAction("Wczytaj stan")

        # Bindowanie kontrolek do akcji
        # Start gry
        QObject.connect(self._game_start, SIGNAL("triggered()"), self, SLOT("start_game()"))
        QObject.connect(self._next_round, SIGNAL("triggered()"), lambda: self._world.nextRound())
        QObject.connect(save_game, SIGNAL("triggered()"), self, SLOT("save_game()"))
        QObject.connect(load_game, SIGNAL("triggered()"), self, SLOT("load_game()"))

        # Insze kontrolki
        # Plansza gry
        self._game_board = GameBoard(self, 0, self._menu_bar_h)

        # Panel informaacyjny
        info_widget = QtGui.QWidget()
        self._info_panel = QtGui.QVBoxLayout(info_widget)
        self._info_panel.setAlignment(Qt.AlignTop)
        info_widget.setLayout(self._info_panel)

        # Dodanie ww. paneli
        hbox.addWidget(self._game_board)
        hbox.addWidget(info_widget)

        self.setLayout(hbox)

    # Przycisk startu gry
    def start_game(self):
        self._world.draw_world()
        # Ukrycie tego przycisku
        self._next_round.setVisible(True)
        self._game_start.setVisible(False)

    # Zapis stanu gry
    def save_game(self):
        world_mapper = MapWorld()
        try:
            with open('world.xml', 'w+') as file:
                file.write(world_mapper.serialize(self._world))
        except (OSError, IOError):
            print("Nie można zapisać pliku")

    # Wczytywanie stanu gry
    def load_game(self):
        try:
            with open('world.xml', 'r') as file:
                map_world = MapWorld()
                tmp = map_world.deserialize(file.read())
                if tmp is not None:
                    tmp._controller = self
                    self._world = tmp
                    self.start_game()
        except (OSError, IOError):
            print("Nie można wczytać pliku")

    # Losowa inicjalizacja organizmami
    def _init_org(self, count, org_type, rand):
        for i in range(count):
            x, y = rand(0, self._world.getN()), rand(0, self._world.getN())
            if self._world.is_free((x, y)):
                new_org = org_type((x, y))
                self._world.add_organism(new_org)

    # Metody kontrolera
    def reset_map(self):
        self._game_board._should_redraw = True
        self._game_board._draw_at.clear()

    # Wypisywanie informacji
    def print_info(self, text):
        self._info_panel.addWidget(QtGui.QLabel(text))

    # Czyszczenie informacji
    def clear_info(self):
        for i in reversed(range(self._info_panel.count())):
            self._info_panel.itemAt(i).widget().deleteLater()

    # Wypisanie czegoś
    def print(self, xy, text):
        x, y = xy
        self._game_board.draw_at(x, y, QtGui.QColor(self._map_to_color(text)))
        self._game_board.update()

    # Wczytywanie znaku/komendy etc.
    def read_char(self):
        wnd = HumanMoveWnd(self)
        wnd.exec_()
        return self._res_key

    def show_and_raise(self):
        self.show()
        self.raise_()

    _game_board = GameBoard
    _info_panel = QtGui.QVBoxLayout
    _res_key = 0xDEADC0DE
    _world = World
