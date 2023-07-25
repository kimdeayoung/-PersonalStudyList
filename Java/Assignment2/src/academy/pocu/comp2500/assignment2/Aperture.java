package academy.pocu.comp2500.assignment2;

public class Aperture {
    protected int x;
    protected int y;

    protected int width;
    protected int height;

    protected Aperture(int x, int y, int width, int height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public boolean isAddAbleAperture(int width, int height) {
        int resultX = this.x + this.width;
        int resultY = this.y + this.height;

        return (resultX > 0) && (resultY > 0) && (resultX <= width) && (resultY <= height);
    }
}
