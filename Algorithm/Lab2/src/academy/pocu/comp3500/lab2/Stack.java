package academy.pocu.comp3500.lab2;

import academy.pocu.comp3500.lab2.datastructure.Node;

public final class Stack {
    private Node root;
    private int size;

    public Stack() {
    }
    public void push(final int data) {
        if (root == null) {
            root = LinkedList.append(null, data);
        } else {
            root = LinkedList.prepend(root, data);
        }
        ++size;
    }

    public int peek() {
        return root.getData();
    }

    public int pop() {
        int value = peek();
        root = LinkedList.removeAt(root, 0);
        --size;
        return value;
    }

    public int getSize() {
        return size;
    }
}