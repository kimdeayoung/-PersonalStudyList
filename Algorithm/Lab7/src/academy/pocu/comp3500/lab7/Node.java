package academy.pocu.comp3500.lab7;

import java.util.ArrayList;
import java.util.HashMap;

public class Node {
    private char latter;
    private int depth;

    private Node parent;
    private Node[] childs;

    private ArrayList<Integer> childIndexes;

    private ArrayList<String> words;

    private final static int ALPHABET_COUNT = 26;

    public Node() {
        depth = 0;
        this.childs = new Node[ALPHABET_COUNT];
        this.childIndexes = new ArrayList<>(ALPHABET_COUNT);
    }

    public Node(char latter, Node parent, int depth) {
        this.latter = latter;
        this.depth = depth;
        this.parent = parent;
        this.childs = new Node[ALPHABET_COUNT];
        this.childIndexes = new ArrayList<>(ALPHABET_COUNT);
        this.words = new ArrayList<>();
    }

    public char getLatter() {
        return latter;
    }

    public int getDepth() {
        return depth;
    }

    public boolean isAddable(char key) {
        return childs[getIndex(key)] == null;
    }

    public Node getParent() {
        return parent;
    }

    public Node addChild(char latter, int depth) {
        Node node = new Node(latter, this, depth);
        int index = getIndex(latter);
        childs[index] = node;
        childIndexes.add(index);

        return node;
    }

    public Node getChild(char key) {
        return childs[getIndex(key)];
    }

    public Node getChild(int index) {
        return childs[index];
    }

    public ArrayList<Integer> getChildIndexes() {
        return childIndexes;
    }

    private int getIndex(char key) {
        return ((key | 32) - 97);
    }

    public ArrayList<String> getWords() {
        return words;
    }

    public void setWordData(String word) {
        this.words.add(word);
    }
}
