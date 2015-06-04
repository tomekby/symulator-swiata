import random
import uuid
from bs4 import BeautifulSoup
from Mapper.General import General

# Klasa odpowiedzialna za serializację/deserializację do/z XMLa
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


class MapOrganism(General):

    # Zapis do XMLa
    def serialize(self, org):
        res_xml = "<organism"
        res_xml += " strength=\"%d\"" % org._strength
        res_xml += " initiative=\"%d\"" % org._initiative
        res_xml += " creation=\"%d\"" % org._creation
        res_xml += " symbol=\"%s\"" % org._SYMBOL
        res_xml += " pos_x=\"%d\" pos_y=\"%d\"" % org._position
        res_xml += " last-pos_x=\"%d\" last-pos_y=\"%d\"" % org._last_pos
        # Człowiek trochę inaczej
        try:
            res_xml += " bonus_left=\"%d\" before_next_bonus=\"%d\"" % (org._bonus_left, org._before_next_bonus)
        except AttributeError:
            pass
        res_xml += "/>\n"

        return res_xml

    def _type_from_symbol(self, symbol):
        return {
            'A': Antelope,
            'L': Fox,
            'O': Sheep,
            'Z': Turtle,
            'W': Wolf,
            'C': Human,
            'j': Belladonna,
            'm': Dandelion,
            't': Grass,
            'g': Guarana,
        }[symbol]

    # Odczyt z XMLa
    def deserialize(self, org_xml):
        org = BeautifulSoup(org_xml, features="xml").organism

        pos = (int(org.get('pos_x')), int(org.get('pos_y')))
        try:
            res_org = self._type_from_symbol(org.get('symbol'))(pos)
            res_org._strength = int(org.get('strength'))
            res_org._initiative = int(org.get('initiative'))
            res_org._uid = uuid.uuid4()
            res_org._SYMBOL = org.get('symbol')
            res_org._last_pos = (int(org.get('last-pos_x')), int(org.get('last-pos_y')))
            res_org._creation = int(org.get('creation'))
            # Specyficzna deserializacja człowieka
            if isinstance(res_org, Human):
                res_org._bonus_left = int(org.get('bonus_left'))
                res_org._before_next_bonus = int(org.get('before_next_bonus'))
        except AttributeError:
            print("XML file corrupted")
            return None

        return res_org

# Klasa odpowiedzialna za serializację świata do XMLa
class MapWorld(General):

    # Zapis do XMLa
    def serialize(self, world):
        om = MapOrganism()
        res_xml = "<world size=\"%d\">\n" % world.getN()
        for org in world._organisms:
            res_xml += om.serialize(org)
        res_xml += "</world>"

        return res_xml

    # Odczyt z XMLa
    def deserialize(self, world_xml):
        # noinspection PyBroadException
        try:
            world_xml = BeautifulSoup(world_xml, features="xml").world
            res_world = World(random.randint)
            res_world.setN(world_xml.get('size'))
            org_mapper = MapOrganism()
            for org in world_xml.findAll('organism'):
                tmp = org_mapper.deserialize(org)
                if tmp is not None:
                    res_world.add_organism(tmp)
            return res_world
        except:
            print("XML file corrupted")
            return None
