package pl.vot.tomekby.World;

import javafx.util.Pair;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import pl.vot.tomekby.World.Animals.*;
import pl.vot.tomekby.World.Plants.Belladonna;
import pl.vot.tomekby.World.Plants.Dandelion;
import pl.vot.tomekby.World.Plants.Grass;
import pl.vot.tomekby.World.Plants.Guarana;

import java.util.UUID;

/**
 * Data mapper dla organizmów
 * Implementuje wzorzec architektoniczny Data Mapper
 * Created by Tomasz on 2015-05-10.
 */
public class OrganismMapper implements DataMapper {
    // Wczytywanie stanu z XMLa
    @Override
    public Organism read_xml(Object o) {
        Node node = (Node) o;
        if(node.getNodeType() == Node.ELEMENT_NODE) {
            // Node opisujący organizm
            Element org = (Element) node;
            Organism res = null;
            final int POS_X = Integer.parseInt(org.getAttribute("pos_x")), POS_Y = Integer.parseInt(org.getAttribute("pos_y"));
            switch(org.getAttribute("symbol").charAt(0)) {
                // Zwierzęta
                case 'A': res = new Antelope(POS_X, POS_Y); break;
                case 'L': res = new Fox(POS_X, POS_Y); break;
                case 'C':
                    res = new Human(POS_X, POS_Y);
                    // Dodanie specyficznych rzeczy do człeka
                    String[] attr = {"before_next_bonus", "bonus_left"};
                    for(String s : attr) ((Human) res).setBonus_left(Integer.parseInt(org.getAttribute(s)));
                    break;
                case 'O': res = new Sheep(POS_X, POS_Y); break;
                case 'Ż': res = new Turtle(POS_X, POS_Y); break;
                case 'W': res = new Wolf(POS_X, POS_Y); break;
                // Rośliny
                case 'j': res = new Belladonna(POS_X, POS_Y); break;
                case 'm': res = new Dandelion(POS_X, POS_Y); break;
                case 't': res = new Grass(POS_X, POS_Y); break;
                case 'g': res = new Guarana(POS_X, POS_Y); break;
            }
            // Prawidłowy organizm
            if(res != null) {
                res.strength = Integer.parseInt(org.getAttribute("strength"));
                res.initiative = Integer.parseInt(org.getAttribute("initiative"));
                res.uid = UUID.fromString(org.getAttribute("uid"));
                res.SYMBOL = org.getAttribute("symbol").charAt(0);
                res.last_position = new Pair(Integer.parseInt(org.getAttribute("last-pos_x")), Integer.parseInt(org.getAttribute("last-pos_y")));
                res.creation = Integer.parseInt(org.getAttribute("creation"));

                return res;
            }
        }
        return null;
    }

    // Zapisywanie stanu do XMLa
    @Override
    public String write_xml(Object o) {
        Organism org = (Organism) o;
        String res_xml = "<organism";
        res_xml += " uid=\"" + org.get_uid() + "\"";
        res_xml += " strength=\"" + org.get_strength() + "\"";
        res_xml += " initiative=\"" + org.get_initiative() + "\"";
        res_xml += " creation=\"" + org.creation + "\"";
        res_xml += " symbol=\"" + org.get_symbol() + "\"";
        res_xml += " pos_x=\"" + org.pos().getKey() + "\" pos_y=\"" + org.pos().getValue() + "\"";
        res_xml += " last-pos_x=\"" + org.last_position.getKey() + "\" last-pos_y=\"" + org.last_position.getValue() + "\"";
        // Człowiek jest obsługiwany trochę inaczej
        if(org instanceof Human) {
            Human h = (Human) org;
            res_xml += " bonus_left = \"" + h.getBonus_left() + "\" before_next_bonus=\"" + h.getBefore_next_bonus() + "\"";
        }
        res_xml += "></organism>";

        return res_xml;
    }
}
