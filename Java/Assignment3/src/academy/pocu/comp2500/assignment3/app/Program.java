package academy.pocu.comp2500.assignment3.app;

import academy.pocu.comp2500.assignment3.App;
import academy.pocu.comp2500.assignment3.Destroyer;
import academy.pocu.comp2500.assignment3.SimulationManager;
import academy.pocu.comp2500.assignment3.IntVector2D;
import academy.pocu.comp2500.assignment3.Marine;
import academy.pocu.comp2500.assignment3.Mine;
import academy.pocu.comp2500.assignment3.SmartMine;
import academy.pocu.comp2500.assignment3.Tank;
import academy.pocu.comp2500.assignment3.TileType;
import academy.pocu.comp2500.assignment3.Turret;
import academy.pocu.comp2500.assignment3.Unit;
import academy.pocu.comp2500.assignment3.Wraith;
import academy.pocu.comp2500.assignment3.registry.Registry;
import com.sun.tools.javac.Main;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Program {

    public static void main(String[] args) {
        SimulationManager simulationManager = SimulationManager.getInstance();

        ArrayList<Unit> units = Test01();

        for (Unit unit : units) {
            simulationManager.spawn(unit);
        }

        SimulationVisualizer visualizer = new SimulationVisualizer(units);
        for (int i = 0; i < 10; ++i) {
            clearConsole();
            visualizer.visualize(i, simulationManager.getUnits());
            simulationManager.update();
            continueOnEnter();
        }
    }

    public static void continueOnEnter() {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("Press enter to continue");
            reader.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void clearConsole() {
        try {
            new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static ArrayList<Unit> Test00() {
        Unit u0 = new Marine(new IntVector2D(2, 1));
        Unit u1 = new Turret(new IntVector2D(0, 2));
        Unit u2 = new Wraith(new IntVector2D(3,0));
        Unit u3 = new Mine(new IntVector2D(4,0),4);
        Unit u4 = new Marine(new IntVector2D(4,3));
        Unit u5 = new Turret(new IntVector2D(5,0));
        Unit u6 = new Tank(new IntVector2D(4,1));
        Unit u7 = new Wraith(new IntVector2D(0, 2));
        Unit u8 = new SmartMine(new IntVector2D(0,3), 3,3);
        Unit u9 = new Wraith(new IntVector2D(3,0));
        Unit u10 = new Mine(new IntVector2D(2,0),4);
        Unit u11 = new Wraith(new IntVector2D(2,3));
        Unit u12 = new Tank(new IntVector2D(5,3));
        Unit u13 = new Wraith(new IntVector2D(0,1));
        Unit u14 = new SmartMine(new IntVector2D(0, 2),1,3);
        Unit u15 = new Mine(new IntVector2D(2,2),2);

        ArrayList<Unit> units = new ArrayList<>();
        units.add(u0);
        units.add(u1);
        units.add(u2);
        units.add(u3);
        units.add(u4);
        units.add(u5);
        units.add(u6);
        units.add(u7);
        units.add(u8);
        units.add(u9);
        units.add(u10);
        units.add(u11);
        units.add(u12);
        units.add(u13);
        units.add(u14);
        units.add(u15);

        return units;
    }

    public static ArrayList<Unit> Test01() {
        Unit u0 = new Wraith(new IntVector2D(5,3));
        Unit u1 = new Mine(new IntVector2D(3,1),1);
        Unit u2 = new SmartMine(new IntVector2D(5,3), 1,3);
        Unit u3 = new Wraith(new IntVector2D(7,2));
        Unit u4 = new Marine(new IntVector2D(6,1));
        Unit u5 = new Mine(new IntVector2D(1,3),4);
        Unit u6 = new Wraith(new IntVector2D(5,3));
        Unit u7 = new Tank(new IntVector2D(7,2));
        Unit u8 = new Turret(new IntVector2D(5,0));
        Unit u9 = new SmartMine(new IntVector2D(2,2),1,3);
        Unit u10 = new Tank(new IntVector2D(2,0));
        Unit u11 = new Turret(new IntVector2D(6,2));
        Unit u12 = new SmartMine(new IntVector2D(5,2), 4,2);
        Unit u13 = new Marine(new IntVector2D(2,1));
        Unit u14 = new Wraith(new IntVector2D(1,2));
        Unit u15 = new Marine(new IntVector2D(5,0));

        ArrayList<Unit> units = new ArrayList<>();
        units.add(u0);
        units.add(u1);
        units.add(u2);
        units.add(u3);
        units.add(u4);
        units.add(u5);
        units.add(u6);
        units.add(u7);
        units.add(u8);
        units.add(u9);
        units.add(u10);
        units.add(u11);
        units.add(u12);
        units.add(u13);
        units.add(u14);
        units.add(u15);

        return units;
    }
}