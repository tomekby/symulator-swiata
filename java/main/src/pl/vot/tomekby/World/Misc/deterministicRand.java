package pl.vot.tomekby.World.Misc;

import java.util.Random;

/**
 * Created by Tomasz on 2015-05-08.
 */
public class deterministicRand extends Random {
    public int nextInt(int x) {
        return 0; // Losowo wybrana liczba
    }
}
