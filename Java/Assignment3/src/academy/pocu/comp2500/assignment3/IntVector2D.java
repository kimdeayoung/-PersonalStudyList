package academy.pocu.comp2500.assignment3;

public class IntVector2D {
    private int x;
    private int y;

    public IntVector2D(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return this.x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return this.y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public IntVector2D copyTo() {
        return new IntVector2D(this.x, this.y);
    }

    public IntVector2D sub(IntVector2D vector) {
        return new IntVector2D(this.x - vector.x, this.y - vector.y);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) {
            return true;
        }

        if (obj == null) {
            return false;
        }

        IntVector2D vector2D = (IntVector2D) obj;
        return (this.x == vector2D.x) && (this.y == vector2D.y);
    }

    @Override
    public int hashCode() {
        int hash = 17;
        hash = hash * 31 + this.x;
        hash = hash * 31 + this.y;
        return hash;
    }
}