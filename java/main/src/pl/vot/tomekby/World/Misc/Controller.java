package pl.vot.tomekby.World.Misc;

import javax.swing.*;

/**
 * Klasa obsługująca IN/OUT w aplikacji
 * Created by Tomasz on 2015-05-09.
 */
public interface Controller {
    // Wyświetlanie na planszy
    void print(int x, int y, String text);
    // Czyszczenie informacji dodatkowych
    void clear_info();
    // Wyświetlanie informacji dodatkowych
    void print_info(String text);
    // Wczytywanie znaku z wejścia
    int read_char();

    void setMap_panel(JPanel p);
    void setInfo_panel(JPanel p);
    void setField_width(int w);
}
