package pl.vot.tomekby.World.Misc;

import javax.swing.*;

/**
 * Klasa obs³uguj¹ca IN/OUT w aplikacji
 * Created by Tomasz on 2015-05-09.
 */
public interface Controller {
    // Wyœwietlanie na planszy
    void print(int x, int y, String text);
    // Czyszczenie informacji dodatkowych
    void clear_info();
    // Wyœwietlanie informacji dodatkowych
    void print_info(String text);
    // Wczytywanie znaku z wejœcia
    int read_char();

    void setMap_panel(JPanel p);
    void setInfo_panel(JPanel p);
    void setField_width(int w);
}
