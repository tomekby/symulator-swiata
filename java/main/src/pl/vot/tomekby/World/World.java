package pl.vot.tomekby.World;
import javafx.util.Pair;
import pl.vot.tomekby.World.Misc.Controller;
import pl.vot.tomekby.World.Misc.NoPlaceToSpawn;

import java.util.Comparator;
import java.util.Random;
import java.util.UUID;
import java.util.Vector;

/**
 * Created by Tomasz on 2015-05-02.
 */
final public class World {
    public World() { setRand_class(new Random()); }
    public void nextRound() {
        // Wykonywanie akcji organizmów
        for(Organism o : getOrganisms()) {
            // Jeśli nie oznaczony do usunięcia
            if(to_remove.indexOf(o.get_uid()) == -1) o.action();
        }
        for (int i = 0; i < getOrganisms().size(); ++i) {
            for (int j = i + 1; j < getOrganisms().size(); ++j) {
                // Te same koordynaty
                try {
                    if (getOrganisms().get(j).pos().equals(getOrganisms().get(i).pos()) && !getOrganisms().get(i).get_uid().equals(getOrganisms().get(j).get_uid())) {
                        getOrganisms().get(i).collision_default(getOrganisms().get(j));
                    }
                } catch(NoPlaceToSpawn e) {
                    System.err.println(e.getMessage());
                }
            }
        }
        // Kasowanie niepotrzebnych organizmów
        remove_pending();
        // Rysowanie świata
        draw_world();
    }
    public void add_organism(Organism new_org) {
        if (is_free((Integer) new_org.pos().getKey(), (Integer) new_org.pos().getValue())) {
            new_org.set_world(this);
            to_add.add(new_org);
        }
    }
    public void add_pending() {
        // Dopisanie zespawnowanych
        for(Organism o : to_add) {
            boolean ommit = false;
            for(Organism o2 : getOrganisms()) if(o.pos().equals(o2.pos())) ommit = true;
            // Jeśli pole jest wolne, dodanie zwierzęcia
            if(!ommit) getOrganisms().add(o);
        }
        to_add.clear();

        // Sortowanie w odpowiedniej kolejności
        getOrganisms().sort(new OrgComp());
    }
    public boolean is_free(int x, int y) {
        if (x < 0 || x >= N || y < 0 || y >= N) return false;

        final Pair pos = new Pair(x, y);
        for(Organism o : getOrganisms()) if(o.pos().equals(pos)) return false;
        for(Organism o : to_add) if(o.pos().equals(pos)) return false;
        return true;
    }
    public int get_N() { return N; }
    public void set_N(int N) { this.N = N; }
    public void add_event(String msg) {
        String entry = (log.size() + 1)+". "+msg;
        log.add(entry);
    }

    public Vector<Organism> getOrganisms() {
        return organisms;
    }

    public Vector<UUID> getTo_remove() {
        return to_remove;
    }

    public Vector<Organism> getTo_add() {
        return to_add;
    }

    // Porównywanie organizmów
    static class OrgComp implements Comparator<Organism> {
        public int compare(Organism o1, Organism o2) {
            if(o1.initiative != o2.initiative) return o2.initiative - o1.initiative;
            else if(o1.creation == o2.creation) return 0;
            return (int)(o1.creation - o2.creation);
        }
    }
    public void draw_world() {
        // Porządki
        controller.clear_info();
        // Czyszczenie mapki
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) controller.print(i, j, "EMPTY");
        }

        // Rysowanie organizmów
        draw_organisms();
        // Wypisywanie instrukcji
        print_instruction();
        // Wypisywanie dziennika zdarzeń
        controller.print_info("Dziennik zdarzeń:");
        for(String msg : log) controller.print_info(msg);
        log.clear();

        // Dopisanie zespawnowanych
        add_pending();
    }

    public void kill(Organism winner, Organism looser) {
        add_event(winner.get_name() + " zabija " + looser.get_name());
        to_remove.add(looser.get_uid());
    }
    public void eat(Organism a, Organism p) {
        add_event(a.get_name() + " zjada " + p.get_name());
        to_remove.add(p.get_uid());
    }
    private void remove_pending() {
        for(UUID id : to_remove) {
            for(Organism o : getOrganisms()) {
                if(o.get_uid().equals(id)) {
                    getOrganisms().remove(o);
                    break;
                }
            }
        }
        // Wyczyszczenie listy do usunięcia
        to_remove.clear();
    }
    private void draw_organisms() {
        for(Organism o : getOrganisms()) o.draw();
    }
    private void print_instruction() {
        String[] instruction = {"Strzałki - poruszanie człowiekiem", "Spacja - umiejętność specjalna człowieka", "Plik z zapisem stanu gry: world.xml"};
        for(String s : instruction) {
            controller.print_info(s);
        }
        controller.print_info("\n");
    }

    private Vector<Organism> organisms = new Vector<Organism>();
    private Vector<UUID> to_remove = new Vector<UUID>(); // UID organizmów do skasowania
    private Vector<Organism> to_add = new Vector<Organism>(); // Lista organizmów do zespawnowania
    private Vector<String> log = new Vector<String>(); // Lista zdarzeń
    private int N = 20;

    private Random rand_class;
    private Controller controller;

    public Random getRand_class() {
        return rand_class;
    }

    public void setRand_class(Random rand_class) {
        this.rand_class = rand_class;
    }

    public Controller getController() {
        return controller;
    }

    public void setController(Controller controller) {
        this.controller = controller;
    }
}
