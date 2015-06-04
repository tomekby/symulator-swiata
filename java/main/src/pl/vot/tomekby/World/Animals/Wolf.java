package pl.vot.tomekby.World.Animals;

import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-08.
 */
final public class Wolf extends Animal {
    public Wolf() { super(); init(); }
    public Wolf(int x, int y) { super(x, y); init(); }
    public Wolf(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Wilk"; }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Wolf(x, y));
    }
    protected void init() {
        SYMBOL = 'W';
        strength = 9;
        initiative = 5;
    }

}
