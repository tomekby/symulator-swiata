package pl.vot.tomekby.World.Misc;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

/**
 * Kontroler obsługujący map_panel
 * Created by Tomasz on 2015-05-09.
 */
public class PaneController implements Controller {
    public void print(int x, int y, String text) {
        Color box_color = Color.white;
        // Zwierzęta
        if(text.equals("A")) box_color = new Color(163, 135, 42);
        else if(text.equals("L")) box_color = new Color(184, 78, 46);
        else if(text.equals("C")) box_color = new Color(102, 219, 237);
        else if(text.equals("O")) box_color = new Color(200, 200, 200);
        else if(text.equals("Ż")) box_color = new Color(11, 59, 8);
        else if(text.equals("W")) box_color = new Color(80, 80, 80);
        // Rośliny
        else if(text.equals("j")) box_color = new Color(35, 20, 201);
        else if(text.equals("m")) box_color = new Color(255, 255, 0);
        else if(text.equals("t")) box_color = new Color(0, 255, 0);
        else if(text.equals("g")) box_color = new Color(255, 0, 0);

        // Rysowanie czegoś
        Graphics g = map_panel.getGraphics();
        g.setColor(box_color);
        g.fillRect(x * field_width + 1, y * field_width + 1, field_width - 1, field_width - 1);
    }
    public void clear_info() {
        info_count = 0;
        info_panel.removeAll();
        info_panel.updateUI();
    }
    public void print_info(String text) {
        ++info_count;
        int MSG_LIMIT = 30;
        if(info_count < MSG_LIMIT) {
            info_panel.add(new JLabel(text, SwingConstants.LEFT));
        }
        // Jeśli osiągnęliśmy limit komunikatów, więcej nie wyświetlamy
        else if(info_count == MSG_LIMIT) {
            info_panel.add(new JLabel("...", SwingConstants.LEFT));
        }
        info_panel.updateUI();
    }
    public int read_char() {
        // Obsługa wejścia dla użyszkodnika
        // Obejście na event driven app
        JFrame parent = (JFrame) SwingUtilities.getWindowAncestor(map_panel);
        JLabel text = new JLabel("Oczekiwanie na ruch człowieka...", SwingConstants.CENTER);
        dlg = new JDialog(parent);
        text.setFont(new Font(text.getFont().getName(), Font.BOLD, 30));
        dlg.setModal(true);
        dlg.requestFocus();
        dlg.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
        dlg.setUndecorated(true);
        JPanel dlg_panel = new JPanel();
        dlg_panel.add(text);
        dlg.add(dlg_panel);

        dlg.setResizable(false);
        dlg.pack();
        dlg.setLocationRelativeTo(parent);
        Point parent_loc = parent.getLocation(), map_loc = map_panel.getLocation();
        int fix_x = (int) parent_loc.getX() + (int) map_loc.getX(), fix_y = (int) parent_loc.getY() + (int) map_loc.getY();
        dlg.setLocation(fix_x + map_panel.getWidth() / 2 - dlg.getWidth() / 2, fix_y + map_panel.getHeight() / 2 - dlg.getHeight() / 2);

        // Dopiero wciśnięcie strzałki wyłączy okienko
        dlg.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                super.keyPressed(e);
                // Strzałki
                if ((e.getKeyCode() >= 37 && e.getKeyCode() <= 40) || e.getKeyCode() == 32) {
                    ch = e.getKeyCode();
                    dlg.dispose();
                }
            }
        });
        dlg.setBackground(new Color(0, 0, 0, 96));
        dlg_panel.setBackground(new Color(0,0,0,0));
        dlg.setVisible(true);

        return ch;
    }
    public void setMap_panel(JPanel p) {
        map_panel = p;
    }
    public void setInfo_panel(JPanel p) {
        info_panel = p;
    }
    public void setField_width(int w) {
        field_width = w;
    }

    private JPanel map_panel;
    private JPanel info_panel;
    private JDialog dlg;

    private int field_width;
    private int ch = 0;
    private int info_count = 0;
}
