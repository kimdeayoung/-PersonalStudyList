package academy.pocu.comp3500.lab11;

import academy.pocu.comp3500.lab11.data.Point;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

public class BallBoy {
    public static List<Point> findPath(final Point[] points) {
        if (points == null || points.length == 0) {
            LinkedList<Point> result = new LinkedList<>();
            result.add(new Point(0, 0));
            return result;
        }

        Point start = new Point(0, 0);
        Point[] newPoints = new Point[points.length + 1];
        Edge[] edges = new Edge[newPoints.length * (newPoints.length - 1) / 2];

        HashMap<Point, Boolean> isVisited = new HashMap<>();
        {
            newPoints[0] = start;
            isVisited.put(newPoints[0], false);

            int edgeIndex = 0;
            for (int i = 0; i < points.length; ++i) {
                newPoints[i + 1] = points[i];
                isVisited.put(newPoints[i + 1], false);
                for (int j = i; j < points.length; ++j) {
                    edges[edgeIndex++] = new Edge(newPoints[i], points[j]);
                }
            }
        }

        ArrayList<Edge> mst = kruskal(newPoints, edges);
        HashMap<Edge, Integer> entryCounts = new HashMap<>();

        LinkedList<Point> mstDfsResult = new LinkedList<>();
        mstDFSRecursive(mstDfsResult, mst, start, entryCounts);

        LinkedList<Point> result = new LinkedList<>();
        for (Point point : mstDfsResult) {
            if (!isVisited.get(point)) {
                isVisited.put(point, true);
                result.add(point);
            }
        }
        result.add(start);

        return result;
    }

    private static ArrayList<Edge> kruskal(final Point[] points, final Edge[] edges) {
        DisjointSet set = new DisjointSet(points);
        ArrayList<Edge> mst = new ArrayList<>(edges.length);
        Arrays.sort(edges);

        for (Edge edge : edges) {
            Point point1 = edge.getPoint1();
            Point point2 = edge.getPoint2();

            Point root1 = set.find(point1);
            Point root2 = set.find(point2);

            if (!root1.equals(root2)) {
                mst.add(edge);
                set.union(point1, point2);
            }
        }

        return mst;
    }

    private static void mstDFSRecursive(final LinkedList<Point> result, final ArrayList<Edge> mst, final Point point, final HashMap<Edge, Integer> entryCounts) {
        result.add(point);

        for (Edge edge : mst) {
            Point otherSidePoint = edge.getOtherSidePointOrNull(point);

            if (otherSidePoint != null) {
                int entryCount = entryCounts.getOrDefault(edge, 0);
                if (entryCount < 2) {
                    entryCounts.put(edge, ++entryCount);
                    mstDFSRecursive(result, mst, otherSidePoint, entryCounts);
                    result.add(point);
                }
            }
        }
    }
}