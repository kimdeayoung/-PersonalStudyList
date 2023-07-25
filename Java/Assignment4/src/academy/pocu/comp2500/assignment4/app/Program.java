package academy.pocu.comp2500.assignment4.app;

import academy.pocu.comp2500.assignment4.Canvas;
import academy.pocu.comp2500.assignment4.ClearCommand;
import academy.pocu.comp2500.assignment4.CommandHistoryManager;
import academy.pocu.comp2500.assignment4.DecreasePixelCommand;
import academy.pocu.comp2500.assignment4.DrawPixelCommand;
import academy.pocu.comp2500.assignment4.FillHorizontalLineCommand;
import academy.pocu.comp2500.assignment4.FillVerticalLineCommand;
import academy.pocu.comp2500.assignment4.ICommand;
import academy.pocu.comp2500.assignment4.IncreasePixelCommand;
import academy.pocu.comp2500.assignment4.OverdrawAnalyzer;
import academy.pocu.comp2500.assignment4.ToLowerCommand;
import academy.pocu.comp2500.assignment4.ToUpperCommand;

import java.util.ArrayList;

public class Program {

    public static void main(String[] args) {
        L14();
    }

    private static void L14() {
        OverdrawAnalyzer analyzer = new OverdrawAnalyzer(6, 6);
        CommandHistoryManager manager = new CommandHistoryManager((Canvas) analyzer);

        ArrayList<ICommand> commands = new ArrayList<>();
        commands.add(new ClearCommand());
        commands.add(new FillVerticalLineCommand(1, '.'));
        commands.add(new IncreasePixelCommand(0, 3));
        commands.add(new ToUpperCommand(1, 0));
        commands.add(new FillHorizontalLineCommand(4, 'X'));
        commands.add(new FillHorizontalLineCommand(4, 'V'));
        commands.add(new FillVerticalLineCommand(4, 't'));
        commands.add(new IncreasePixelCommand(4, 2));
        commands.add(new ToLowerCommand(2, 3));
        commands.add(new IncreasePixelCommand(0, 0));
        commands.add(new FillVerticalLineCommand(2, 'm'));
        commands.add(new ToLowerCommand(0, 4));
        commands.add(new ToLowerCommand(1, 0));
        commands.add(new DrawPixelCommand(3, 1, 'o'));
        commands.add(new FillVerticalLineCommand(2, 'y'));
        commands.add(new FillHorizontalLineCommand(1, 'A'));


        for (int i = 0; i < 8; i++) {
            manager.execute(commands.get(i));
        }

        manager.redo();

        for (int i = 8; i < 10; i++) {
            manager.execute(commands.get(i));
        }

        manager.redo();

        manager.execute(commands.get(10));

        manager.undo();

        for (int i = 11; i < 14; i++) {
            manager.execute(commands.get(i));
        }

        manager.undo();

        for (int i = 14; i < 16; i++) {
            manager.execute(commands.get(i));
        }

        System.out.print(analyzer.getDrawing());
        System.out.println(analyzer.getPixelHistory(2,4));
    }

    private static void L15() {
        OverdrawAnalyzer analyzer = new OverdrawAnalyzer(5, 5);
        CommandHistoryManager manager = new CommandHistoryManager((Canvas) analyzer);

        ArrayList<ICommand> commands = new ArrayList<>();
        commands.add(new ClearCommand());
        commands.add(new FillVerticalLineCommand(1, '.'));
        commands.add(new IncreasePixelCommand(0, 3));
        commands.add(new ToUpperCommand(1, 0));
        commands.add(new FillHorizontalLineCommand(4, 'X'));
        commands.add(new FillHorizontalLineCommand(4, 'V'));
        commands.add(new FillVerticalLineCommand(4, 't'));
        commands.add(new IncreasePixelCommand(4, 2));
        commands.add(new ToLowerCommand(2, 3));
        commands.add(new IncreasePixelCommand(0, 0));
        commands.add(new FillVerticalLineCommand(2, 'm'));
        commands.add(new ToLowerCommand(0, 4));
        commands.add(new ToLowerCommand(1, 0));
        commands.add(new DrawPixelCommand(3, 1, 'o'));
        commands.add(new FillVerticalLineCommand(2, 'y'));
        commands.add(new FillHorizontalLineCommand(1, 'A'));

        for (int i = 0; i < 6; i++) {
            manager.execute(commands.get(i));
        }

        manager.undo();

        for (int i = 6; i < 9; i++) {
            manager.execute(commands.get(i));
        }

        manager.undo();

        for (int i = 9; i < 11; i++) {
            manager.execute(commands.get(i));
        }

        manager.undo();

        for (int i = 11; i < 16; i++) {
            manager.execute(commands.get(i));
        }

        System.out.print(analyzer.getDrawing());
        System.out.println(analyzer.getOverdrawCount());
    }

    public static void L16() {
        OverdrawAnalyzer analyzer = new OverdrawAnalyzer(6, 6);
        CommandHistoryManager manager = new CommandHistoryManager((Canvas) analyzer);

        ArrayList<ICommand> commands = new ArrayList<>();
        commands.add(new DrawPixelCommand(4, 4, 'a'));
        commands.add(new ToLowerCommand(0, 0));
        commands.add(new DrawPixelCommand(2, 4, 'n'));
        commands.add(new ClearCommand());
        commands.add(new DecreasePixelCommand(4, 3));
        commands.add(new ToUpperCommand(3, 0));
        commands.add(new IncreasePixelCommand(3, 0));
        commands.add(new ClearCommand());
        commands.add(new FillVerticalLineCommand(0, 'g'));
        commands.add(new FillVerticalLineCommand(3, 'A'));
        commands.add(new DecreasePixelCommand(2, 0));
        commands.add(new ToLowerCommand(1, 2));
        commands.add(new ClearCommand());
        commands.add(new FillHorizontalLineCommand(1, 'J'));
        commands.add(new ToLowerCommand(4, 1));
        commands.add(new ToUpperCommand(0, 2));

        for (int i = 0; i < 3; i++) {
            manager.execute(commands.get(i));
        }

        manager.redo();

        for (int i = 3; i < 7; i++) {
            manager.execute(commands.get(i));
        }

        manager.redo();

        for (int i = 7; i < 13; i++) {
            manager.execute(commands.get(i));
        }

        manager.redo();

        for (int i = 13; i < 16; i++) {
            manager.execute(commands.get(i));
        }

        manager.undo();

        System.out.print(analyzer.getDrawing());
        System.out.println(analyzer.getOverdrawCount(3,0));
    }
}
