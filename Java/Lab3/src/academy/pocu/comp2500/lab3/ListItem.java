package academy.pocu.comp2500.lab3;

import java.util.ArrayList;

public class ListItem {
    private String text;
    private ArrayList<ListItem> sublistItems;
    private char bulletStyle;

    private int recursiveDepth;

    public ListItem(String text) {
        this(text, '*');
    }

    public ListItem(String text, char bulletStyle) {
        this.text = text;
        sublistItems = new ArrayList<>();
        this.bulletStyle = bulletStyle;
    }

    public String getText() {
        return this.text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public char getBulletStyle() {
        return this.bulletStyle;
    }

    public void addSublistItem(ListItem sublistItem) {
        this.sublistItems.add(sublistItem);
    }

    public void removeSublistItem(int index) {
        this.sublistItems.remove(index);
    }

    public ListItem getSublistItem(int index) {
        return this.sublistItems.get(index);
    }

    public void setBulletStyle(char bulletStyle) {
        this.bulletStyle = bulletStyle;
    }

    public String toString() {
        StringBuilder strBuilder = new StringBuilder();
        strBuilder.append(getBulletStyle());
        strBuilder.append(" ");
        strBuilder.append(getText());
        strBuilder.append(System.lineSeparator());

        for (ListItem listItem : this.sublistItems) {
            listItem.recursiveDepth = this.recursiveDepth + 1;

            for (int i = 0; i < listItem.recursiveDepth; ++i) {
                strBuilder.append("    ");
            }

            strBuilder.append(listItem.toString());
        }

        return strBuilder.toString();
    }
}
