package academy.pocu.comp2500.assignment4;

public class FillVerticalLineCommand extends Command implements ICommand {
    private int x;
    private char fillVerticalChar;
    private char[] prevCharacters;

    public FillVerticalLineCommand(int x, char character) {
        this.x = x;
        this.fillVerticalChar = character;
    }

    @Override
    public boolean execute(Canvas canvas) {
        if (isExecuteable() && isValidX(canvas, x) && isSetablePixelCharacter(this.fillVerticalChar)) {
            int height = canvas.getHeight();
            this.canvas = canvas;
            this.canvasPixels = new char[this.canvas.getWidth() * this.canvas.getHeight()];

            this.prevCharacters = new char[height];
            for (int i = 0; i < height; ++i) {
                this.prevCharacters[i] = canvas.getPixel(this.x, i);
            }

            canvas.fillVerticalLine(this.x, this.fillVerticalChar);
            this.isExecuted = true;
            updateCanvasPixels();

            return true;
        }
        return false;
    }

    @Override
    public boolean undo() {
        if (isUndoable()) {
            int height = canvas.getHeight();
            for (int i = 0; i < height; ++i) {
                this.canvas.drawPixel(this.x, i, this.prevCharacters[i]);
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
            canvas.fillVerticalLine(this.x, this.fillVerticalChar);
            isUndo = false;
            updateCanvasPixels();

            return true;
        }
        return false;
    }
}
