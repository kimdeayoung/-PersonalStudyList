package academy.pocu.comp2500.assignment4;

public class ToUpperCommand extends Command implements ICommand {
    private int x;
    private int y;

    private char prevCharacter;

    public ToUpperCommand(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean execute(Canvas canvas) {
        if (isExecuteable() && isValidRange(canvas, x, y)) {
            this.canvas = canvas;
            this.canvasPixels = new char[this.canvas.getWidth() * this.canvas.getHeight()];

            prevCharacter = canvas.getPixel(x, y);
            canvas.toUpper(this.x, this.y);
            updateCanvasPixels();

            this.isExecuted = true;
            return true;
        }

        return false;
    }

    @Override
    public boolean undo() {
        if (isUndoable()) {
            this.canvas.drawPixel(this.x, this.y, prevCharacter);
            isUndo = true;
            updateCanvasPixels();

            return true;
        }

        return false;
    }

    @Override
    public boolean redo() {
        if (isRedoable()) {
            this.canvas.toUpper(this.x, this.y);
            isUndo = false;
            updateCanvasPixels();

            return true;
        }

        return false;
    }
}
