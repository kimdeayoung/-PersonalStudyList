package academy.pocu.comp2500.assignment4;

public class IncreasePixelCommand extends Command implements ICommand {
    private int x;
    private int y;

    public IncreasePixelCommand(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean execute(Canvas canvas) {
        if (isExecuteable() && isValidRange(canvas, x, y)) {
            this.canvas = canvas;
            this.canvasPixels = new char[this.canvas.getWidth() * this.canvas.getHeight()];

            this.isExecuted = canvas.increasePixel(this.x, this.y);
            updateCanvasPixels();

            return isExecuted;
        }
        return false;
    }

    @Override
    public boolean undo() {
        if (isUndoable()) {
            this.canvas.decreasePixel(this.x, this.y);
            this.isUndo = true;
            updateCanvasPixels();

            return true;
        }
        return false;
    }

    @Override
    public boolean redo() {
        if (isRedoable()) {
            this.canvas.increasePixel(this.x, this.y);
            isUndo = false;
            updateCanvasPixels();

            return true;
        }
        return false;
    }
}
