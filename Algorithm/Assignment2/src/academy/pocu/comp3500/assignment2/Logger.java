package academy.pocu.comp3500.assignment2;

import java.io.BufferedWriter;
import java.io.IOException;

public final class Logger {
    static Indent rootIndent = new Indent(null, 0, "");
    static Indent currentIndent = rootIndent;

    public static void log(final String text) {
        currentIndent.log(text);
    }

    public static void printTo(final BufferedWriter writer) {
        try {
            rootIndent.printTo(writer);
            writer.flush();
        } catch (IOException e) {
        }
    }

    public static void printTo(final BufferedWriter writer, final String filter) {
        try {
            rootIndent.printTo(writer, filter);
            writer.flush();
        } catch (IOException e) {
        }
    }

    public static void clear() {
        rootIndent.clear();
        currentIndent = rootIndent;
    }

    public static Indent indent() {
        currentIndent = currentIndent.indent();
        return currentIndent;
    }

    public static void unindent() {
        currentIndent = currentIndent.unIndent();
    }
}
