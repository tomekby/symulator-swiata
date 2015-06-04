package pl.vot.tomekby.World;

import org.junit.Before;
import org.junit.Test;
import pl.vot.tomekby.World.Animals.Antelope;
import pl.vot.tomekby.World.Animals.Sheep;
import pl.vot.tomekby.World.Animals.Turtle;
import pl.vot.tomekby.World.Animals.Wolf;
import pl.vot.tomekby.World.Misc.Controller;
import pl.vot.tomekby.World.Misc.NullController;
import pl.vot.tomekby.World.Misc.deterministicRand;
import pl.vot.tomekby.World.Plants.Belladonna;
import pl.vot.tomekby.World.Plants.Dandelion;
import pl.vot.tomekby.World.Plants.Grass;
import pl.vot.tomekby.World.Plants.Guarana;

import static org.junit.Assert.*;

/**
 * Created by Tomasz on 2015-05-10.
 */
public class WorldTest2 extends junit.framework.TestCase {

    public World world;

    @Before
    public void setUp() throws Exception {
        world = new World();
        Controller c = new NullController();
        world.set_N(20);
        world.setController(c);
        world.setRand_class(new deterministicRand());
        // zwierzęta ruszają się do góry jeśli mogą
    }

    @Test
    public void testAnimalPlantCollision() throws Exception {
        Organism w = new Wolf(0, 0), g = new Grass(0, 1);
        world.add_organism(w);
        world.add_organism(g);
        world.add_pending();

        w.collision_default(g);
        assertEquals("wilk zjada trawę", 1, world.getTo_remove().size());
    }

    @Test
    public void testSameAnimalCollision() throws Exception {
        Organism w1 = new Wolf(0, 0), w2 = new Wolf(0, 1);
        world.add_organism(w1);
        world.add_organism(w2);
        world.add_pending();

        w1.collision_default(w2);
        assertEquals("wilki sie rozmnażają", 1, world.getTo_add().size());
    }

    @Test
    public void testWolfSheepCollision() throws Exception {
        Organism w = new Wolf(0, 0), s = new Sheep(0, 1);
        world.add_organism(w);
        world.add_organism(s);
        world.add_pending();

        w.collision_default(s);
        assertEquals("wilk zjada owcę", 1, world.getTo_remove().size());
    }

    @Test
    public void testTurtleSheepCollision() throws Exception {
        Organism t = new Turtle(0, 0), s = new Sheep(0, 1);
        world.add_organism(t);
        world.add_organism(s);
        world.add_pending();

        t.collision_default(s);
        assertEquals("żółw odpiera owcę", 0, world.getTo_remove().size());
        assertEquals("żółw odpiera owcę", 0, world.getTo_add().size());
    }

    @Test
    public void testBelladonnaSheepCollision() throws Exception {
        Organism b = new Belladonna(0, 0), s = new Sheep(0, 1);
        world.add_organism(b);
        world.add_organism(s);
        world.add_pending();

        s.collision_default(b);
        assertEquals("wilcze jagody zabijają owcę", 2, world.getTo_remove().size());
    }

    @Test
    public void testGuaranaSheepCollision() throws Exception {
        Organism g = new Guarana(0, 0), s = new Sheep(0, 1), t = new Turtle(0, 2);
        world.add_organism(g);
        world.add_organism(s);
        world.add_organism(t);
        world.add_pending();

        s.collision_default(g);
        assertEquals("siła owcy ulega zwiększeniu", 7, s.get_strength());
        s.collision_default(t);
        assertEquals("owca zabija żółwia", 2, world.getTo_remove().size());
    }

}