package pl.vot.tomekby.World.Plants;

import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-07.
 */
final public class Grass extends Plant {
    public Grass() { super(); init(); }
    public Grass(int x, int y) { super(x, y); init(); }
    public Grass(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Trawa"; }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Grass(x, y));
    }
    protected void init() {
        strength = 0;
        SYMBOL = 't';
    }
}
