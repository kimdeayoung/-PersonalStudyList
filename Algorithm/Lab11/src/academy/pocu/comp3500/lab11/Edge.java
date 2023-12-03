package academy.pocu.comp3500.lab11;

import academy.pocu.comp3500.lab11.data.Point;

public final class Edge implements Comparable<Edge> {
    private final Point point1;
    private final Point point2;
    private final double length;

    public Edge(final Point node1,
                final Point node2) {
        this.point1 = node1;
        this.point2 = node2;
        this.length = Math.sqrt(Math.pow(node2.getX() - node1.getX(), 2) + Math.pow(node2.getY() - node1.getY(), 2));
    }

    public Point getPoint1() {
        return this.point1;
    }

    public Point getPoint2() {
        return this.point2;
    }

    public Point getOtherSidePointOrNull(Point node) {
        if (this.point1 == node) {
            return point2;
        } else if (this.point2 == node) {
            return point1;
        }
        return null;
    }

    @Override
    public int compareTo(Edge e) {
        double cmpValue = this.length - e.length;
        return (int) cmpValue;
    }
}