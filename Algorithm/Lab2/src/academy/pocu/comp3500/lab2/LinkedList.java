package academy.pocu.comp3500.lab2;

import academy.pocu.comp3500.lab2.datastructure.Node;

public final class LinkedList {
    private LinkedList() {

    }

    public static Node append(final Node rootOrNull, final int data) {
        Node newNode = new Node(data);

        if (rootOrNull == null) {
            return newNode;
        } else {
            Node node = rootOrNull;
            while (node.getNextOrNull() != null) {
                node = node.getNextOrNull();
            }
            node.setNext(newNode);

            return rootOrNull;
        }
    }

    public static Node appendBack(final Node node, final int data) {
        Node newNode = new Node(data);

        if (node == null) {
            return newNode;
        } else {
            node.setNext(newNode);
        }
        return newNode;
    }

    public static Node prepend(final Node rootOrNull, final int data) {
        Node newNode = new Node(data);

        if (rootOrNull != null) {
            newNode.setNext(rootOrNull);
        }
        return newNode;
    }

    public static Node insertAt(final Node rootOrNull, final int index, final int data) {
        if (index < 0) {
            return rootOrNull;
        }

        Node node = rootOrNull;
        Node prevNode = null;

        for (int i = 0; i < index; ++i) {
            if (node == null) {
                return rootOrNull;
            }

            prevNode = node;
            node = node.getNextOrNull();
        }

        Node newNode = new Node(data);
        newNode.setNext(node);
        if (prevNode == null) {
            return newNode;
        } else {
            prevNode.setNext(newNode);
            return rootOrNull;
        }
    }

    public static Node removeAt(final Node rootOrNull, final int index) {
        if (rootOrNull == null || index < 0) {
            return rootOrNull;
        }

        Node node = rootOrNull;
        Node prevNode = null;

        for (int i = 0; i < index; ++i) {
            if (node.getNextOrNull() == null) {
                return rootOrNull;
            }

            prevNode = node;
            node = node.getNextOrNull();
        }

        if (prevNode == null) {
            return node.getNextOrNull();
        } else {
            prevNode.setNext(node.getNextOrNull());
            return rootOrNull;
        }
    }

    public static int getIndexOf(final Node rootOrNull, final int data) {
        Node node = rootOrNull;

        int findIndex = 0;
        while (node != null) {
            if (node.getData() == data) {
                return findIndex;
            }
            ++findIndex;
            node = node.getNextOrNull();
        }

        return -1;
    }

    public static Node getOrNull(final Node rootOrNull, final int index) {
        Node node = rootOrNull;

        int findIndex = 0;
        while (node != null) {
            if (findIndex++ == index) {
                return node;
            }
            node = node.getNextOrNull();
        }

        return null;
    }

    public static Node reverse(final Node rootOrNull) {
        if (rootOrNull == null) {
            return null;
        }

        Node node = rootOrNull;
        Node prevNode = null;
        while (node.getNextOrNull() != null) {
            Node swapNextNode = node;
            node = node.getNextOrNull();
            swapNextNode.setNext(prevNode);

            Node nextNode = node.getNextOrNull();
            node.setNext(swapNextNode);
            prevNode = node;

            node = nextNode;
            if (node == null) {
                return prevNode;
            }
        }

        node.setNext(prevNode);
        return node;
    }

    public static Node interleaveOrNull(final Node root0OrNull, final Node root1OrNull) {
        Node root = root0OrNull;
        Node node0 = root0OrNull;
        Node node1 = root1OrNull;

        if (root != null) {
            node0 = root0OrNull.getNextOrNull();
            root0OrNull.setNext(null);
        } else {
            if (root1OrNull == null) {
                return null;
            }
            root = root1OrNull;
            node1 = node1.getNextOrNull();
            root1OrNull.setNext(null);
        }

        Node linkNode = root;
        while (node0 != null || node1 != null) {
            if (node1 != null) {
                linkNode.setNext(node1);
                node1 = node1.getNextOrNull();
                linkNode = linkNode.getNextOrNull();
            }

            if (node0 != null) {
                linkNode.setNext(node0);
                node0 = node0.getNextOrNull();
                linkNode = linkNode.getNextOrNull();
            }
        }
        linkNode.setNext(null);

        return root;
    }
}