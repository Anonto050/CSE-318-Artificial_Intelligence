import java.util.Map;

public class Example {
    private Map<String, String> values;
    private String Class;

    public Example(Map<String, String> values, String Class) {
        this.values = values;
        this.Class = Class;
    }

    public Map<String, String> getValues() {
        return values;
    }

    public String getClassification() {
        return Class;
    }

    public void setValues(Map<String, String> values) {
        this.values = values;
    }

    public void setClassification(String Class) {
        this.Class = Class;
    }

    public String toString() {
        return "Example: " + values + " " + Class;
    }
}
