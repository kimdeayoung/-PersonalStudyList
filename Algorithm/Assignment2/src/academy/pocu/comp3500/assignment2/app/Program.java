package academy.pocu.comp3500.assignment2.app;

import academy.pocu.comp3500.assignment2.Indent;
import academy.pocu.comp3500.assignment2.Logger;
import academy.pocu.comp3500.assignment2.datastructure.Sort;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import static academy.pocu.comp3500.assignment2.Logger.log;

public class Program {

    public static void main(String[] args) throws IOException {
        {
            final BufferedWriter writer = new BufferedWriter(new FileWriter("LogFile.log"));
            {
                Logger.log("810 755 266");
                Indent indent = Logger.indent();
                {
                    Logger.log("L: 266");
                    Logger.log("R: 755 810");

                    Indent indent1 = Logger.indent();
                    {
                        Logger.log("L: 755 810");
                        Logger.log("R: ");
                        Logger.log("X: 755 810");
                    }
                    Logger.unindent();

                    Logger.log("X: 266 755 810");
                }
                Logger.unindent();

                Logger.printTo(writer);
                writer.write(System.lineSeparator());
                Logger.printTo(writer, "810");
                writer.write(System.lineSeparator());
                Logger.printTo(writer, "266"); // 이거 지워서도 확인해보세요~
                writer.write(System.lineSeparator());
                Logger.printTo(writer, "755");
            }
        }
    }
}