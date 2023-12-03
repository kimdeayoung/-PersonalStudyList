package academy.pocu.comp3500.lab8;

import academy.pocu.comp3500.lab8.maze.Point;

import java.util.LinkedList;
import java.util.List;

public final class MazeSolver {
    private static final int[][] MOVE_OFFSET = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    public static List<Point> findPath(final char[][] maze, final Point start) {
        LinkedList<Point> result = new LinkedList<>();
        if (maze[start.getY()][start.getX()] == 'E') {
            result.add(new Point(start.getX(), start.getY()));
            return result;
        }

        boolean[][] visited = new boolean[maze.length][maze[0].length];

        PointNode endPoint = null;
        LinkedList<PointNode> points = new LinkedList<>();
        points.add(new PointNode(start.getX(), start.getY(), null));

        while (!points.isEmpty()) {
            PointNode point = points.removeFirst();

            if (visited[point.getY()][point.getX()]) {
                continue;
            } else if (maze[point.getY()][point.getX()] == 'E') {
                endPoint = point;
                break;
            }

            visited[point.getY()][point.getX()] = true;
            for (int i = 0; i < MOVE_OFFSET.length; ++i) {
                int posX = point.getX() + MOVE_OFFSET[i][0];
                int posY = point.getY() + MOVE_OFFSET[i][1];

                if (posY < 0 || posY >= maze.length || posX < 0 || posX >= maze[0].length) {
                    continue;
                } else if (maze[posY][posX] == 'x') {
                    continue;
                } else if (visited[posY][posX]) {
                    continue;
                }

                points.add(new PointNode(posX, posY, point));
            }
        }

        if (endPoint == null) {
            return result;
        }

        while (endPoint.getPrevNode() != null) {
            result.addFirst(new Point(endPoint.getX(), endPoint.getY()));
            endPoint = endPoint.getPrevNode();
        }
        result.addFirst(new Point(endPoint.getX(), endPoint.getY()));

        return result;
    }
}