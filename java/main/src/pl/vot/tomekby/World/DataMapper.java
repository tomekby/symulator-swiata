package pl.vot.tomekby.World;

import java.util.Objects;

/**
 * Created by Tomasz on 2015-05-10.
 */
interface DataMapper {
    Object read_xml(Object o);
    String write_xml(Object o);
}
