package academy.pocu.comp2500.assignment4;

public class Command {
    private final char SETABLE_MIN = 32;
    private final char SETABLE_MAX = 126;
    protected Canvas canvas;
    protected char[] canvasPixels;

    protected boolean isExecuted;
    protected boolean isUndo;

    protected boolean isExecuteable() {
        return this.canvas == null;
    }

    protected boolean isUndoable() {
        return this.canvas != null && this.isExecuted && this.isUndo == false && !isChangedCanvas();
    }

    protected boolean isRedoable() {
        return this.isUndo && !isChangedCanvas();
    }

    protected void updateCanvasPixels() {
        int width = this.canvas.getWidth();
        int height = this.canvas.getHeight();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                this.canvasPixels[x + y * width] = this.canvas.getPixel(x, y);
            }
        }
    }

    private boolean isChangedCanvas() {
        int width = this.canvas.getWidth();
        int height = this.canvas.getHeight();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (this.canvasPixels[x + y * width] != this.canvas.getPixel(x, y)) {
                    return true;
                }
            }
        }

        return false;
    }

    protected boolean isSetablePixelCharacter(char character) {
        return character >= SETABLE_MIN && character <= SETABLE_MAX;
    }

    protected boolean isValidRange(Canvas canvas, int x, int y) {
        return isValidX(canvas, x) && isValidY(canvas, y);
    }

    protected boolean isValidX(Canvas canvas, int x) {
        int width = canvas.getWidth();
        return x >= 0 && x < width;
    }

    protected boolean isValidY(Canvas canvas, int y) {
        int height = canvas.getHeight();
        return y >= 0 && y < height;
    }
}
