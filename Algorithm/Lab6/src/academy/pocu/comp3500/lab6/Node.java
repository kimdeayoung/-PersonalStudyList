package academy.pocu.comp3500.lab6;

import academy.pocu.comp3500.lab6.leagueofpocu.Player;

public class Node {
    private Player player;

    private Node parent;
    private Node left;
    private Node right;

    public Node(Player player, Node parent) {
        this.player = player;
        this.parent = parent;
        this.left = null;
        this.right = null;
    }

    public Player getPlayer() {
        return player;
    }

    public void setPlayer(Player player) {
        this.player = player;
    }

    public Node getParent() {
        return parent;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public Node getLeft() {
        return left;
    }

    public void setLeft(Node left) {
        this.left = left;
    }

    public Node getRight() {
        return right;
    }

    public void setRight(Node right) {
        this.right = right;
    }

    public void swapChild(Node existingNode, Node newNode) {
        if (existingNode.equals(this.left)) {
            this.left = newNode;
        } else if (existingNode.equals(this.right)) {
            this.right = newNode;
        }
    }

    public boolean hasChild() {
        return this.left != null || this.right != null;
    }

    public void clear() {
        this.player = null;
        if (this.parent != null) {
            this.parent.swapChild(this, null);
            this.parent = null;
        }
        this.left = null;
        this.right = null;
    }
}
