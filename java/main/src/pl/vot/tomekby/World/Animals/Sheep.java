package pl.vot.tomekby.World.Animals;

import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-08.
 */
final public class Sheep extends Animal {
    public Sheep() { super(); init(); }
    public Sheep(int x, int y) { super(x, y); init(); }
    public Sheep(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Owca"; }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Sheep(x, y));
    }
    protected void init() {
        SYMBOL = 'O';
        strength = 4;
        initiative = 4;
    }

}
