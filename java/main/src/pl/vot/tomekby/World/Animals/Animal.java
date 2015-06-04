package pl.vot.tomekby.World.Animals;

import javafx.util.Pair;
import pl.vot.tomekby.World.Misc.NoPlaceToSpawn;
import pl.vot.tomekby.World.Organism;
import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-07.
 */
@SuppressWarnings("unchecked")
abstract public class Animal extends Organism {
    Animal() { super(); last_position = position; }
    Animal(int x, int y) { super(x, y); last_position = position; }
    Animal(int x, int y, World world) { super(x, y, world); last_position = position; }

    @SuppressWarnings("unchecked")
    void move_x(DIRECTIONS d) {
        if(d.equals(DIRECTIONS.LEFT)) {
            for(int i = move_range; i >= 1; --i) {
                if(position.getKey() - i >= 0) {
                    setPosition(new Pair(position.getKey() - i, position.getValue()));
                    break;
                }
            }
        }
        if(d.equals(DIRECTIONS.RIGHT)) {
            for(int i = move_range; i >= 1; --i) {
                if(position.getKey() + i < world.get_N()) {
                    setPosition(new Pair(position.getKey() + i, position.getValue()));
                    break;
                }
            }
        }
    }
    void move_y(DIRECTIONS d) {
        if (d.equals(DIRECTIONS.TOP)) { // Przesunięcie w górę
            for (int i = move_range; i >= 1; --i) {
                if (position.getValue() - i >= 0) {
                    setPosition(new Pair(position.getKey(), position.getValue() - i));
                    break;
                }
            }
        }
        else { // Przesunięcie w dół
            for (int i = move_range; i >= 1; --i) {
                if (position.getValue() + i < world.get_N()) {
                    setPosition(new Pair(position.getKey(), position.getValue() + i));
                    break;
                }
            }
        }
    }
    int move_range = 1;
    public void action() {
        // Przesuniecie zwierzaka
        int r = world.getRand_class().nextInt(4);
        if (r == 0) move_y(DIRECTIONS.TOP);
        else if (r == 1) move_y(DIRECTIONS.BOTTOM);
        else if (r == 2) move_x(DIRECTIONS.LEFT);
        else if (r == 3) move_x(DIRECTIONS.RIGHT);

        super.action();
    }
    public void collision(Organism with) {}
    boolean should_fight(Animal with) { return true; }
    public void collision_default(Organism with) throws NoPlaceToSpawn {
        // Ten sam typ ? rozmnażanie
        if (get_symbol() == with.get_symbol()) {
            // Po lewej jest wolne miejsce
            if (world.is_free(position.getKey() - 1, position.getValue())) spawn_new(position.getKey() - 1, position.getValue());
            // Po prawej jest wolne miejsce
            else if (world.is_free(position.getKey() + 1, position.getValue())) spawn_new(position.getKey() + 1, position.getValue());
            // U góry jest wolne miejsce
            else if (world.is_free(position.getKey(), position.getValue() - 1)) spawn_new(position.getKey(), position.getValue() - 1);
            // Na dole jest wolne miejsce
            else if (world.is_free(position.getKey(), position.getValue() + 1)) spawn_new(position.getKey(), position.getValue() + 1);
            else throw new NoPlaceToSpawn();
            world.add_event(get_name() + " się rozmnaża");
        }
        else {
            // Inne gatunki - będzie walka
            if(with instanceof Animal) {
                // Zwierzęta powinny walczyć
                if (should_fight((Animal) with) && ((Animal) with).should_fight(this)) {
                    fight(with);
                }
                // Niestandardowa akcja kolizji
                else {
                    collision(with);
                    with.collision(this);
                }
            }
            // Nie jest zwierzęciem -> będzie jedzone
            else {
                eat(with);
            }
        }
    }
    public void inc_strength(int s) { strength += s; }
    void go_back() { setPosition(last_position); }
    protected enum DIRECTIONS { TOP, BOTTOM, LEFT, RIGHT }

    protected void eat(Organism p) {
        super.eat(p);
    }
}
