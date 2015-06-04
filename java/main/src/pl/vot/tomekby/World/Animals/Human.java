package pl.vot.tomekby.World.Animals;

import pl.vot.tomekby.World.World;

/**
 * Created by Tomasz on 2015-05-08.
 */
final public class Human extends Animal {
    public Human(int x, int y) { super(x, y); init(); }

    public String get_name() { return "Człowiek"; }
    protected void spawn_new(int x, int y) {}
    protected void init() {
        SYMBOL = 'C';
        strength = 5;
        initiative = 4;
        bonus_left = before_next_bonus = 0;
    }

    public void action() {
        // Wybrana strzałka
        int move = world.getController().read_char();
        // Obsługa włączenia umiejętności specjalnej
        if(move == 32) {
            if(bonus_left == 0 && before_next_bonus == 0) bonus_left = 5;
            move = world.getController().read_char();
        }
        // 37 - left // 38 - top // 39 - right // 40 - bottom //
        switch(move) {
            case 37: move_x(DIRECTIONS.LEFT); break;
            case 38: move_y(DIRECTIONS.TOP); break;
            case 39: move_x(DIRECTIONS.RIGHT); break;
            case 40: move_y(DIRECTIONS.BOTTOM); break;
        }
        // Zmniejszenie pozostałych rund bonusu
        if(bonus_left > 0) --bonus_left;
        // Bonus się skończył i nie zaczęło odliczanie do następnego
        if (bonus_left == 0 && before_next_bonus == 0) before_next_bonus = 5;
        // Zmniejszenie ilości rund do możliwości uruchomienia bonusa
        else if (bonus_left == 0 && before_next_bonus > 0) --before_next_bonus;
    }
    protected void move_x(DIRECTIONS d) {
        ability();
        super.move_x(d);
    }
    protected void move_y(DIRECTIONS d) {
        ability();
        super.move_y(d);
    }
    private void ability() {
        if(before_next_bonus != 0 && bonus_left == 0) move_range = 1;
        else if(bonus_left > 2) move_range = 2;
        else move_range = world.getRand_class().nextInt() % 2 + 1;
    }

    private int bonus_left = 0; // ilość pozostałych rund działania bonusu
    private int before_next_bonus = 0; // ilość rund do kolejnego wykorzystania bonusa

    public int getBonus_left() {
        return bonus_left;
    }

    public void setBonus_left(int bonus_left) {
        this.bonus_left = bonus_left;
    }

    public int getBefore_next_bonus() {
        return before_next_bonus;
    }
}
