package pl.vot.tomekby.World.Animals;

import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-08.
 */
final public class Fox extends Animal {
    public Fox() { super(); init(); }
    public Fox(int x, int y) { super(x, y); init(); }
    public Fox(int x, int y, World world) { super(x, y, world); init(); }

    public String get_name() { return "Lis"; }
    protected void spawn_new(int x, int y) {
        super.spawn_new(new Fox(x, y));
    }
    protected void init() {
        SYMBOL = 'L';
        strength = 3;
        initiative = 7;
    }

    protected void move_x(DIRECTIONS d) {
        int tmp = d.equals(DIRECTIONS.LEFT) ? -1 : 1;
        // Tam gdzie miał się ruszyć jest wolne miejsce
        if (world.is_free(position.getKey() + tmp, position.getValue())) super.move_x(d);
        // Z drugiej strony jest miejsce
        else if (world.is_free(position.getKey() - tmp, position.getValue())) super.move_x(d == DIRECTIONS.LEFT ? DIRECTIONS.RIGHT : DIRECTIONS.LEFT);
        // U góry/na dole jest miejsce
        else if (world.is_free(position.getKey(), position.getValue() - 1)) super.move_y(DIRECTIONS.TOP);
        else if (world.is_free(position.getKey(), position.getValue() + 1)) super.move_y(DIRECTIONS.BOTTOM);
    }
    protected void move_y(DIRECTIONS d) {
        int tmp = d.equals(DIRECTIONS.TOP) ? -1 : 1;
        // Tam gdzie miał się ruszyć jest wolne miejsce
        if (world.is_free(position.getKey(), position.getValue() + tmp)) super.move_x(d);
        // Z drugiej strony jest miejsce
        else if (world.is_free(position.getKey(), position.getValue() - tmp)) super.move_x(d == DIRECTIONS.TOP ? DIRECTIONS.BOTTOM : DIRECTIONS.TOP);
        // U góry/na dole jest miejsce
        else if (world.is_free(position.getKey() - 1, position.getValue())) super.move_y(DIRECTIONS.LEFT);
        else if (world.is_free(position.getKey() + 1, position.getValue())) super.move_y(DIRECTIONS.RIGHT);
    }
}
