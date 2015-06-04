package pl.vot.tomekby.World;

import org.junit.Before;
import org.junit.Test;
import pl.vot.tomekby.World.Animals.Antelope;
import pl.vot.tomekby.World.Animals.Sheep;
import pl.vot.tomekby.World.Animals.Wolf;
import pl.vot.tomekby.World.Misc.Controller;
import pl.vot.tomekby.World.Misc.NullController;
import pl.vot.tomekby.World.Misc.deterministicRand;
import pl.vot.tomekby.World.Plants.Dandelion;

import static org.junit.Assert.*;

/**
 * Created by Tomasz on 2015-05-10.
 */
public class WorldTest extends junit.framework.TestCase {

    public World world;

    @Before
    public void setUp() throws Exception {
        world = new World();
        Controller c = new NullController();
        world.set_N(20);
        world.setController(c);
        world.setRand_class(new deterministicRand());
        // zwierzęta ruszają się do góry jeśli mogą
        // antylopa nigdy nie ucieka

        world.add_organism(new Dandelion(0, 0));
        world.add_organism(new Wolf(0, 1));
        world.add_organism(new Wolf(0, 2));
        world.add_organism(new Antelope(0, 5));
        world.add_organism(new Sheep(0, 7));
        world.add_pending();
    }

    @Test
    public void testFirstRound() throws Exception {
        world.nextRound();
        assertEquals("wilk je mlecz", 4, world.getOrganisms().size());
        assertEquals("wilk sie przemieszcza", false, world.is_free(0, 1));
        assertEquals("pole gdzie jest antylopa", false, world.is_free(0, 3));
        assertEquals("pole gdzie była antylopa", true, world.is_free(0, 5));
        assertEquals("pole gdzie jest owca", false, world.is_free(0, 6));
        assertEquals("pole gdzie była owca", true, world.is_free(0, 7));
    }

    @Test
    public void testSecondRound() throws Exception {
        world.nextRound(); world.nextRound();
        assertEquals("wilki sie rozmnażają", 5, world.getOrganisms().size());
        assertEquals("antylopa", false, world.is_free(0, 1));
        assertEquals("antylopa wcześniej", true, world.is_free(0, 3));
        assertEquals("owca", false, world.is_free(0, 5));
    }

    @Test
    public void testThirdRound() throws Exception {
        world.nextRound(); world.nextRound(); world.nextRound();
        assertEquals("antylopa ginie, wilki się rozmnażają po raz 2.", 5, world.getOrganisms().size());
    }

}