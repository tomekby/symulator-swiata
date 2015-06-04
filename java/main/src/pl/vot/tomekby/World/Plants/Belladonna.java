package pl.vot.tomekby.World.Plants;

import pl.vot.tomekby.World.Organism;
import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-07.
 */
final public class Belladonna extends Plant {
    public Belladonna() { super(); init(); }
    public Belladonna(int x, int y) { super(x, y); init(); }
    public Belladonna(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Wilcze jagody"; }
    public void collision(Organism with) {
        // Zabicie zwierzęcia które zjadło roślinę
        kill(with);
    }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Belladonna(x, y));
    }
    protected void init() {
        strength = 99;
        SYMBOL = 'j';
    }
}
