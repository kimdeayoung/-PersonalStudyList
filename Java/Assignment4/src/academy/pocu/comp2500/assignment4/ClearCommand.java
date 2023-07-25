package academy.pocu.comp2500.assignment4;

public class ClearCommand extends Command implements ICommand {
    private char[] prevCharacters;

    public ClearCommand() {
    }

    @Override
    public boolean execute(Canvas canvas) {
        if (isExecuteable()) {
            this.canvas = canvas;
            this.prevCharacters = new char[this.canvas.getWidth() * this.canvas.getHeight()];
            this.canvasPixels = new char[this.canvas.getWidth() * this.canvas.getHeight()];

            for (int y = 0; y < this.canvas.getHeight(); ++y) {
                for (int x = 0; x < this.canvas.getWidth(); ++x) {
                    prevCharacters[x + y * this.canvas.getWidth()] = canvas.getPixel(x, y);
                }
            }

            canvas.clear();
            this.isExecuted = true;
            updateCanvasPixels();

            return true;
        }
        return false;
    }

    @Override
    public boolean undo() {
        if (isUndoable()) {
            int width = canvas.getWidth();
            int height = canvas.getHeight();

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    canvas.drawPixel(x, y, this.prevCharacters[x + y * width]);
                }
            }

            isUndo = true;
            updateCanvasPixels();

            return true;
        }

        return false;
    }

    @Override
    public boolean redo() {
        if (isRedoable()) {
            this.canvas.clear();
            isUndo = false;
            updateCanvasPixels();

            return true;
        }
        return false;
    }
}
