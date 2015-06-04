package pl.vot.tomekby.World.Plants;

import pl.vot.tomekby.World.Organism;
import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-07.
 */
final public class Dandelion extends Plant {
    public Dandelion() { super(); init(); }
    public Dandelion(int x, int y) { super(x, y); init(); }
    public Dandelion(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Mlecz"; }
    public void action(Organism with) {
        for(int i = 0; i < 3; ++i) super.action();
    }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Dandelion(x, y));
    }
    protected void init() {
        strength = 0;
        SYMBOL = 'm';
    }
}
