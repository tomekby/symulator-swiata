package pl.vot.tomekby.World.Animals;

import pl.vot.tomekby.World.Organism;
import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-08.
 */
final public class Turtle extends Animal {
    public Turtle() { super(); init(); }
    public Turtle(int x, int y) { super(x, y); init(); }
    public Turtle(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Żółw"; }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Turtle(x, y));
    }
    protected void init() {
        SYMBOL = 'Ż';
        strength = 2;
        initiative = 1;
    }

    public void action() {
        // 25% szans na ruch
        if(world.getRand_class().nextInt(4) == 1) super.action();
    }
    protected boolean should_fight(Animal with) {
        return with.get_strength() >= 5;
    }
    public void collision(Organism with) {
        if(with instanceof Animal) {
            ((Animal) with).go_back();
            world.add_event("Żółw zmusza do wycofania "+with.get_name());
        }
    }
}
