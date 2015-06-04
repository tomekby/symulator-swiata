package pl.vot.tomekby.World;

import javafx.util.Pair;
import pl.vot.tomekby.World.Misc.NoPlaceToSpawn;

import java.time.Instant;
import java.util.UUID;

/**
 * Created by Tomasz on 2015-05-03.
 */
public abstract class Organism {
    protected Organism(int x, int y, World world) {
        setPosition(new Pair(x, y));
        creation = Instant.now().getEpochSecond();
        uid = UUID.randomUUID();
        this.world = world;
        last_position = new Pair(x, y);
    }
    protected Organism(int x, int y) { this(x, y, new World()); }
    protected Organism() {
        this(0, 0, new World());
    }
    public void set_world(World world) {
        this.world = world;
    }
    public void action() {}
    public void collision(Organism with) {}
    public void collision_default(Organism with) throws NoPlaceToSpawn {}
    public Pair<Integer, Integer> pos() { return position; }

    public void draw() {
        world.getController().print(position.getKey(), position.getValue(), String.valueOf(SYMBOL));
    }
    public int get_initiative() { return initiative; }
    public int get_strength() { return strength; }
    public abstract String get_name();
    public UUID get_uid() { return uid; }
    public char get_symbol() { return SYMBOL; }

    protected void kill(Organism o) {
        world.kill(this, o);
    }
    protected void eat(Organism o) {
        world.eat(this, o);
        // Wywo³anie kolizji aby ew. zmodyfikowaæ ten organizm
        o.collision(this);
    }
    protected void fight(Organism oponent) {
        if (strength > oponent.strength) {
            world.kill(this, oponent);
        }
        else if (strength < oponent.strength) {
            world.kill(oponent, this);
        }
        // Si³a jest równa, decyduj¹ inne czynniki
        else {
            // Zaatakowa³
            if (initiative < oponent.initiative) {
                world.kill(this, oponent);
            }
            // Zosta³ zaatakowany
            else if (initiative > oponent.initiative) {
                world.kill(oponent, this);
            }
            // Ta sama inicjatywa, ten jest m³odszy ? wygrywa
            else if (creation < oponent.creation) {
                world.kill(this, oponent);
            }
            // Ta sama inicjatywa, ten jest starszy ? przegrywa
            else if (creation > oponent.creation) {
                world.kill(oponent, this);
            }
        }
    }
    protected abstract void spawn_new(int x, int y);
    protected void spawn_new(Organism o) {
        world.add_organism(o);
    }
    protected abstract void init();

    protected World world;
    protected int strength;
    protected int initiative;
    protected Pair<Integer, Integer> position;
    UUID uid;
    protected char SYMBOL = '?';
    long creation;
    protected Pair<Integer, Integer> last_position;

    public void setPosition(Pair<Integer, Integer> position) {
        this.position = position;
    }
}
