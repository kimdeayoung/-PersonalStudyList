package academy.pocu.comp3500.assignment3;

public class ChessPieceMove {
    private int fromX;

    private int fromY;
    private int toX;
    private int toY;

    private int score;

    public ChessPieceMove() {
    }

    public void init(final int fromX, final int fromY, final int toX, final int toY) {
        this.fromX = fromX;
        this.fromY = fromY;
        this.toX = toX;
        this.toY = toY;
    }

    public void init(final int fromX, final int fromY, final int toX, final int toY, int score) {
        this.fromX = fromX;
        this.fromY = fromY;
        this.toX = toX;
        this.toY = toY;
        this.score = score;
    }

    public int getFromX() {
        return fromX;
    }

    public int getFromY() {
        return fromY;
    }

    public int getToX() {
        return toX;
    }

    public int getToY() {
        return toY;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }
}
