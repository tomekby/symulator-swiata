package pl.vot.tomekby.World.Plants;

import pl.vot.tomekby.World.Animals.Animal;
import pl.vot.tomekby.World.Organism;
import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-07.
 */
final public class Guarana extends Plant {
    public Guarana() { super(); init(); }
    public Guarana(int x, int y) { super(x, y); init(); }
    public Guarana(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Guarana"; }
    public void collision(Organism with) {
        // Zwiększenie siły o 3
        if(with instanceof Animal) {
            ((Animal) with).inc_strength(3);
        }
    }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Guarana(x, y));
    }
    protected void init() {
        strength = 0;
        SYMBOL = 'g';
    }
}
