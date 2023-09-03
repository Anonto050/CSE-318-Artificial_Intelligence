import java.util.HashMap;
import java.util.Map;

public class Node {
    private String attribute;
    private String decision;
    private String value;
    private Map<String, Node> children; // Map of attribute values to children

    public Node(){
        this.attribute = "";
        this.decision = "";
        this.value = "";
        this.children = new HashMap<>();
    }

    //For non-leaf nodes
    public Node(String attribute, String decision, String value) {
        this.attribute = attribute;
        this.decision = decision;
        this.value = value;
        this.children = new HashMap<>();
    }

    // For non-leaf nodes
    public Node(String attribute, String decision, String value,Map<String, Node> children) {
        this.attribute = attribute;
        this.decision = decision;
        this.value = value;
        this.children = children;
    }

    public String getAttribute() {
        return attribute;
    }

    public String getDecision() {
        return decision;
    }

    public Map<String, Node> getChildren() {
        return children;
    }

    public String getValue() {
        return value;
    }

    public void setAttribute(String attribute) {
        this.attribute = attribute;
    }

    public void setDecision(String decision) {
        this.decision = decision;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public void setChildren(Map<String, Node> children) {
        this.children = children;
    }

    public void addChild(String attribute, Node child){
        children.put(attribute, child);
    }

    public boolean isLeaf() {
        return children == null;
    }

    public String toString() {
        return "Node: " + attribute + " " + decision + " " + value + " " + children;
    }

    public String toString(int depth) {
        String s = "";
        for (int i = 0; i < depth; i++) {
            s += "  ";
        }
        s += "Node: " + attribute + " " + decision + " " + value + "\n";
        if (children != null) {
            for (Node child : children.values()) {
                s += child.toString(depth + 1);
            }
        }
        return s;
    }

}
