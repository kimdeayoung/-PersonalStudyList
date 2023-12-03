package academy.pocu.comp3500.lab2;

import academy.pocu.comp3500.lab2.datastructure.Node;

public final class Queue {
    private Node root;
    private Node lastNode;
    private int size;

    public Queue() {

    }

    public void enqueue(final int data) {
        if (root == null) {
            root = LinkedList.append(null, data);
            lastNode = root;
        } else {
            lastNode = LinkedList.appendBack(lastNode, data);
        }
        ++size;
    }

    public int peek() {
        return root.getData();
    }

    public int dequeue() {
        int value = peek();
        root = LinkedList.removeAt(root, 0);
        if (root == null) {
            lastNode = null;
        }
        --size;
        return value;
    }

    public int getSize() {
        return size;
    }
}