package pl.vot.tomekby.World.Misc;

/**
 * Created by Tomasz on 2015-05-10.
 */
public class NoPlaceToSpawn extends Exception {
    public NoPlaceToSpawn() {
        super("�wiat: "+ "Nie mo�na stworzy� potomka");
    }
}
