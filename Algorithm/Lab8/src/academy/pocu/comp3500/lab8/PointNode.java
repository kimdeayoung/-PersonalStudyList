package academy.pocu.comp3500.lab8;

public class PointNode {
    private final int x;
    private final int y;
    private final PointNode prevNode;

    public PointNode(final int x, final int y, final PointNode prevNode) {
        this.x = x;
        this.y = y;
        this.prevNode = prevNode;
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    public PointNode getPrevNode() {
        return prevNode;
    }
}
