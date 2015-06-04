package pl.vot.tomekby.World.Animals;

import pl.vot.tomekby.World.Organism;
import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-08.
 */
final public class Antelope extends Animal {
    public Antelope() { super(); init(); }
    public Antelope(int x, int y) { super(x, y); init(); }
    public Antelope(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Antylopa"; }
    public boolean should_fight(Animal with) {
        return !(setRan_away(world.getRand_class().nextInt(2) == 1));
    }
    // Kolizja - nie ma walki, jest ew. ucieczka
    public void collision(Organism with) {
        // Jeśli nie ucieka, idziemy standardowo
        if(!ran_away) return;
        // Ucieczka - szukanie wolnego pola
        move_range = 1;
        if(world.is_free(position.getKey() + 1, position.getValue())) super.move_x(DIRECTIONS.RIGHT);
        else if(world.is_free(position.getKey() - 1, position.getValue())) super.move_x(DIRECTIONS.LEFT);
        else if(world.is_free(position.getKey(), position.getValue() + 1)) super.move_y(DIRECTIONS.BOTTOM);
        else if(world.is_free(position.getKey(), position.getValue() - 1)) super.move_y(DIRECTIONS.TOP);
        move_range = 2;
    }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Antelope(x, y));
    }
    protected void init() {
        SYMBOL = 'A';
        strength = 4;
        initiative = 4;
        setRan_away(false);
        move_range = 2;
    }
    // Jeśli nie uciekła, reaguje na cofnięcie
    public void go_back() { if(!ran_away) super.go_back(); }

    // Czy antylopa uciekła
    private boolean ran_away;

    private boolean setRan_away(boolean ran_away) {
        return this.ran_away = ran_away;
    }
}
