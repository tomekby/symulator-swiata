package pl.vot.tomekby.World;

import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;

/**
 * Data mapper dla świata
 * Implementuje wzorzec architektoniczny Data Mapper
 * Created by Tomasz on 2015-05-10.
 */
public class WorldMapper implements DataMapper {
    @Override
    public World read_xml(Object o) {
        World world = new World();

        File XML = new File("world.xml");
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder;
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(XML);
            doc.getDocumentElement().normalize();

            // Przetwarzanie dokumentu
            world.set_N(Integer.parseInt(doc.getDocumentElement().getAttribute("size")));
            // Organizmy
            NodeList organisms = doc.getElementsByTagName("organism");
            OrganismMapper om = new OrganismMapper();
            for(int i = 0; i < organisms.getLength(); ++i) {
                Organism org = om.read_xml(organisms.item(i));
                if(org != null) world.add_organism(org);
            }
            return world;
        }
        catch (ParserConfigurationException e) {} catch (SAXException e) { e.printStackTrace(); }
        catch (IOException e) { e.printStackTrace(); }

        return null;
    }

    @Override
    public String write_xml(Object o) {
        World w = (World) o;
        OrganismMapper om = new OrganismMapper();

        String res_xml = "<world size=\"" + w.get_N() + "\">";
        for(Organism org : w.getOrganisms()) res_xml += om.write_xml(org);
        res_xml += "</world>";

        return res_xml;
    }
}
