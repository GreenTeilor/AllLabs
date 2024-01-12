package by.teachmeskills.springbootproject.composite;

import java.util.ArrayList;
import java.util.List;

public class Box implements Component{
    private List<Component> components;
    public Box() {
        components = new ArrayList<>();
    }

    public Box(List<Component> components) {
        this.components = components;
    }

    @Override
    public int getPrice() {
        var wrapper = new Object(){ int result = 0; };
        components.forEach(component -> wrapper.result += component.getPrice());
        return wrapper.result;
    }
    private String convert(Component component, int depth) { //This algorithm is inefficient, because each recursive call method
        // getPrice() called and iterate through all components in lower hierarchy, which can be done by this method itself instead, however,
        // in order to make this method simpler and don't create more variables, it's left this way
        String margin = "\t".repeat(depth);
        var wrapper = new Object(){ StringBuilder result = new StringBuilder(margin); };
        if (component instanceof Box) {
            wrapper.result.append("Box ").append(component.getPrice()).append("\n");
            ((Box)component).components.forEach(c -> wrapper.result.append(convert(c, depth + 1)));
        } else {
            wrapper.result.append("Phone ").append((component).getPrice()).append("\n");
        }
        return wrapper.result.toString();
    }
    @Override
    public String toString() {
        return convert(this, 0);
    }
}
