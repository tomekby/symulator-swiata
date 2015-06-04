import javafx.util.Pair;
import pl.vot.tomekby.World.Animals.*;
import pl.vot.tomekby.World.Misc.Controller;
import pl.vot.tomekby.World.Misc.PaneController;
import pl.vot.tomekby.World.Organism;
import pl.vot.tomekby.World.Plants.Belladonna;
import pl.vot.tomekby.World.Plants.Dandelion;
import pl.vot.tomekby.World.Plants.Grass;
import pl.vot.tomekby.World.Plants.Guarana;
import pl.vot.tomekby.World.World;
import pl.vot.tomekby.World.WorldMapper;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Random;

/**
 * Created by Tomasz on 2015-05-02.
 * Użyte wzorce projektowe/architektoniczne:
 * - Data mapper
 * - MVC
 * - Front controller
 * - Dependency injection
 */
public class main {
    private JPanel panel1;
    private JButton nastepnaRundaButton;
    private JButton zapiszStanButton;
    private JButton wczytajStanButton;
    private JPanel panel2;
    private JPanel panel3;
    private JButton aboutButton;
    private JButton startButton;
    private Controller c;
    private boolean game_started = false;

    public main() {
        // Następna runda
        nastepnaRundaButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if(!game_started) return;

                world.nextRound();
            }
        });
        // Zapisanie stanu
        zapiszStanButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if (!game_started) return;
                // Zapis stanu gry do pliku
                WorldMapper wm = new WorldMapper();
                try {
                    PrintWriter writer = new PrintWriter("world.xml", "UTF-8");
                    writer.print(wm.write_xml(world));
                    writer.close();
                } catch (FileNotFoundException e1) {
                    e1.printStackTrace();
                } catch (UnsupportedEncodingException e1) {
                    e1.printStackTrace();
                }
            }
        });
        // Wczytanie stanu
        wczytajStanButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                world = new WorldMapper().read_xml(world);
                world.setController(c);
                world.add_pending();
                world.draw_world();

                // Włączenie UI
                game_started = true;
                startButton.setVisible(false);
                nastepnaRundaButton.setEnabled(true);
                zapiszStanButton.setEnabled(true);
            }
        });
        // Dodawanie zwierzęcia
        panel2.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if (!game_started) return;

                Point p = e.getPoint();
                // Koordynaty klikniętego pola
                int X = (int) p.getX() / field_width, Y = (int) p.getY() / field_width;
                // Jeśli jest wolne, można dodać coś
                if (world.is_free(X, Y)) {
                    JFrame frame = (JFrame) SwingUtilities.getWindowAncestor(panel2);
                    Object[] options = {"Antylopa", "Lis", "Owca", "Żółw", "Wilk", "Człowiek", "Wilcze jagody", "Mlecz", "Trawa", "Guarana"};
                    String org = (String) JOptionPane.showInputDialog(
                            frame, "Wybierz organizm do dodania:", "Nowy organizm", JOptionPane.PLAIN_MESSAGE, null, options, "Antylopa"
                    );

                    // Użytkownik coś wybrał
                    if (org != null && org.length() > 0) {
                        Organism new_org = null;
                        if (org == "Antylopa") new_org = new Antelope(X, Y);
                        else if (org == "Lis") new_org = new Fox(X, Y);
                        else if (org == "Owca") new_org = new Sheep(X, Y);
                        else if (org == "Żółw") new_org = new Turtle(X, Y);
                        else if (org == "Wilk") new_org = new Wolf(X, Y);
                        else if (org == "Człowiek") new_org = new Human(X, Y);
                            // Rośliny
                        else if (org == "Wilcze jagody") new_org = new Belladonna(X, Y);
                        else if (org == "Mlecz") new_org = new Dandelion(X, Y);
                        else if (org == "Trawa") new_org = new Grass(X, Y);
                        else if (org == "Guarana") new_org = new Guarana(X, Y);

                        // Dodanie organizmu
                        if (new_org != null) {
                            world.add_organism(new_org);
                            world.add_pending();
                            world.draw_world();
                        }
                    }
                }
            }
        });
        // O programie
        aboutButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                String about_info = "<html><h2>O programie</h2>Autor: Tomasz Stasiak<br>Zastosowane wzorce projektowe/architektoniczne:<ul>"
                        + "<li>Data Mapper (serializacja/deserializacja świata)</li>"
                        + "<li>MVC</li>"
                        + "<li>Front controller</li>"
                        + "<li>Dependency injection</li>"
                        + "</ul>Biblioteki:<ul>"
                        + "<li>Swing (GUI)</li>"
                        + "<li>JUnit 4.x (Testy jednostkowe)</li>"
                        + "</ul>"
                        + "Inne: <ul>"
                        + "<li>serializacja następuje do formatu XML</li>"
                        + "<li>dzięki zastosowaniu wzorców MVC i Data Mapper <br>możliwa jest zmiana interfejsu/sposobu zapisu<br>bez modyfikacji klas świata"
                        + "</ul>";

                JOptionPane.showMessageDialog(SwingUtilities.getWindowAncestor(panel1), about_info, "O programie", JOptionPane.PLAIN_MESSAGE);
            }
        });
        startButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                world.draw_world();
                startButton.setVisible(false);
                nastepnaRundaButton.setEnabled(true);
                zapiszStanButton.setEnabled(true);
                game_started = true;
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Tomasz Stasiak 155197");
        frame.setContentPane(new main().panel1);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setResizable(false);
        frame.setVisible(true);
    }

    private <T extends Organism> void initOrganism(Class<T> cls) throws IllegalAccessException, InstantiationException {
        Random rand = new Random();
        for(int i = 0; i < 6;) {
            int x = rand.nextInt(N), y = rand.nextInt(N);
            if(world.is_free(x, y)) {
                T elem = cls.newInstance();
                elem.setPosition(new Pair(x, y));
                world.add_organism(elem);
                ++i;
            }
        }
    }

    private void initOrganisms() {
        try {
            // Zwierzęta
            initOrganism(Antelope.class); // Antylopa
            initOrganism(Fox.class); // Lis
            initOrganism(Sheep.class); // Owca
            initOrganism(Turtle.class); // Żółw
            initOrganism(Wolf.class); // Wilk
            // Rośliny
            initOrganism(Belladonna.class); // Wilcze jagody
            initOrganism(Dandelion.class); // Mlecz
            initOrganism(Grass.class); // Trawa
            initOrganism(Guarana.class); // Guarana
        } catch (IllegalAccessException e) {
        } catch (InstantiationException e) {}
    }

    private void createUIComponents() {
        panel2 = new DrawOnThis();
        panel2.setBackground(new Color(255, 255, 255));
        c = new PaneController();
        c.setField_width(field_width);
        c.setMap_panel(panel2);

        panel3 = new JPanel();
        panel3.setLayout(new BoxLayout(panel3, BoxLayout.PAGE_AXIS));
        panel3.setPreferredSize(new Dimension(240, field_width * N));
        panel3.setFocusable(false);
        c.setInfo_panel(panel3);

        // Init świata
        world = new World();
        world.set_N(N);
        world.setController(c);

        // Inicjalizacja organizmów
        initOrganisms();
        world.add_organism(new Human(10, 10));
        world.add_pending();
    }

    // Kontrolka po której będziem rysować
    class DrawOnThis extends JPanel {
        DrawOnThis() {
            setPreferredSize(new Dimension(N*field_width, N*field_width));
        }
        @Override
        public void paintComponent(Graphics g) {
            super.paintComponent(g);
            for(int i = 0; i < N; ++i) {
                g.drawLine(field_width*(i+1), 0, field_width*(i+1), N*field_width); // Linie pionowe
                g.drawLine(0, field_width*(i+1), N*field_width, field_width*(i+1)); // Linie poziome
            }
        }
    }

    private static int N = 20;
    private static int field_width = 35;
    private World world;
}
