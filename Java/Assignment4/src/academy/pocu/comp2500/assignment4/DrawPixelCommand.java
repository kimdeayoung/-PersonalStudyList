package academy.pocu.comp2500.assignment4;

public class DrawPixelCommand extends Command implements ICommand {
    private int x;
    private int y;
    private char excuteCharacter;

    private char prevCharacter;

    public DrawPixelCommand(int x, int y, char character) {
        this.x = x;
        this.y = y;
        this.excuteCharacter = character;
    }

    @Override
    public boolean execute(Canvas canvas) {
        if (isExecuteable() && isValidRange(canvas, x, y) && isSetablePixelCharacter(this.excuteCharacter)) {
            this.canvas = canvas;
            this.prevCharacter = canvas.getPixel(x, y);
            this.canvasPixels = new char[this.canvas.getWidth() * this.canvas.getHeight()];

            canvas.drawPixel(this.x, this.y, this.excuteCharacter);
            this.isExecuted = true;
            updateCanvasPixels();

            return true;
        }

        return false;
    }

    @Override
    public boolean undo() {
        if (isUndoable()) {
            this.canvas.drawPixel(this.x, this.y, this.prevCharacter);

            this.isUndo = true;
            updateCanvasPixels();

            return true;
        }
        return false;
    }

    @Override
    public boolean redo() {
        if (isRedoable()) {
            this.canvas.drawPixel(this.x, this.y, this.excuteCharacter);

            this.isUndo = false;
            updateCanvasPixels();

            return true;
        }
        return false;
    }
}
