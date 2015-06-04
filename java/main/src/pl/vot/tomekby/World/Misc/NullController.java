package pl.vot.tomekby.World.Misc;

import javax.swing.*;

/**
 * Pusty kontroler niewymagaj¹cy okienka ani nic
 * Created by Tomasz on 2015-05-09.
 */
public class NullController implements Controller {
    public void print(int x, int y, String text) {}
    public void clear_info() {}
    public void print_info(String text) {}
    public int read_char() { return 0; }
    public void setMap_panel(JPanel p) {}
    public void setInfo_panel(JPanel p) {}
    public void setField_width(int w) {}
}
