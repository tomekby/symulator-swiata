import json
from Mapper.General import General
from Misc import Controller
from World.Organism import Organism


# Klasa odpowiedzialna za serializację/deserializację do/z JSON
class MapOrganism(General):

    # Zapis do JSON
    def serialize(self, org: Organism):
        x, y = org.pos()
        color = Controller.map_to_color(org._SYMBOL)

        return json.dumps((x, y, color))

    # Odczyt z JSON
    def deserialize(self, org):
        # Niepotrzebne więc nieimplementowane
        pass

# Klasa odpowiedzialna za serializację świata do JSON
class MapWorld(General):

    # Zapis do JSON
    def serialize(self, world):
        om = MapOrganism()
        organisms = []
        for org in world._organisms:
            organisms.append(om.serialize(org))

        return json.dumps([world.getN(), organisms])

    # Odczyt z JSONa
    def deserialize(self, world_json):
        # Aktualnie niepotrzebne, więc nieimplementowane
        pass
