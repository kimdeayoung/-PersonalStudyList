package academy.pocu.comp2500.assignment4;

public class FillHorizontalLineCommand extends Command implements ICommand {
    private int y;
    private char fillHorizontalChar;
    private char[] prevCharacters;

    public FillHorizontalLineCommand(int y, char character) {
        this.y = y;
        this.fillHorizontalChar = character;
    }

    @Override
    public boolean execute(Canvas canvas) {
        if (isExecuteable() && isValidY(canvas, y) && isSetablePixelCharacter(this.fillHorizontalChar)) {
            int width = canvas.getWidth();
            this.canvas = canvas;
            this.canvasPixels = new char[this.canvas.getWidth() * this.canvas.getHeight()];

            this.prevCharacters = new char[width];
            for (int i = 0; i < width; ++i) {
                this.prevCharacters[i] = canvas.getPixel(i, this.y);
            }

            canvas.fillHorizontalLine(this.y, this.fillHorizontalChar);
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
            for (int i = 0; i < width; ++i) {
                this.canvas.drawPixel(i, this.y, this.prevCharacters[i]);
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
            canvas.fillHorizontalLine(this.y, this.fillHorizontalChar);
            isUndo = false;
            updateCanvasPixels();

            return true;
        }
        return false;
    }
}
