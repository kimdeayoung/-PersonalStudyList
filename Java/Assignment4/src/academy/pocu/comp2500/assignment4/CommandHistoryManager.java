package academy.pocu.comp2500.assignment4;

import java.util.Stack;

public class CommandHistoryManager {
    private Stack<ICommand> commandsStack;
    private Stack<ICommand> redoStack;

    private Canvas canvas;


    public CommandHistoryManager(Canvas canvas) {
        this.canvas = canvas;

        this.commandsStack = new Stack<>();
        this.redoStack = new Stack<>();
    }


    public boolean execute(ICommand command) {
        boolean isExecute = command.execute(this.canvas);
        if (isExecute) {
            commandsStack.push(command);
            this.redoStack.clear();
        }

        return isExecute;
    }

    public boolean canUndo() {
        return commandsStack.size() > 0;
    }

    public boolean canRedo() {
        return redoStack.size() > 0;
    }

    public boolean undo() {
        boolean result = false;
        if (canUndo()) {
            ICommand lastCommand = this.commandsStack.peek();
            result = lastCommand.undo();
            if (result) {
                this.redoStack.push(this.commandsStack.pop());
            }
        }
        return result;
    }

    public boolean redo() {
        boolean result = false;
        if (canRedo()) {
            ICommand lastCommand = this.redoStack.peek();
            result = lastCommand.redo();
            if (result) {
                this.commandsStack.push(this.redoStack.pop());
            }
        }

        return result;
    }
}
