package academy.pocu.comp3500.assignment2;

import academy.pocu.comp3500.assignment2.datastructure.ArrayList;

import java.io.BufferedWriter;
import java.io.IOException;

public final class Indent {
    private final ArrayList<String> logs;
    private final ArrayList<Integer> nextLevelIndentsLogIndexes;

    private Indent prevLevelIndent;
    private ArrayList<Indent> nextLevelIndents;

    private int indentCount;
    private String indentSpace;

    public Indent(Indent prevLevelIndent, int indentCount, String indentSpace) {
        this.logs = new ArrayList<>();
        this.nextLevelIndentsLogIndexes = new ArrayList<>();

        this.prevLevelIndent = prevLevelIndent;
        this.nextLevelIndents = new ArrayList<>();

        this.indentCount = indentCount;
        this.indentSpace = indentSpace;
    }

    public void log(final String text) {
        logs.add(text);
    }

    private int getNextLevelIndentsLogIndex(int nextLevelIndex) {
        if (nextLevelIndentsLogIndexes.getSize() > nextLevelIndex) {
            return nextLevelIndentsLogIndexes.get(nextLevelIndex);
        } else {
            return -1;
        }
    }

    private void writeLogText(final BufferedWriter writer, final String log) {
        try {
            writer.write(indentSpace);
            writer.write(log);
            writer.write(System.lineSeparator());
        } catch (IOException ignored) {
        }
    }

    public void printTo(final BufferedWriter writer) {
        int nextLevelIndex = 0;
        int logIndex = getNextLevelIndentsLogIndex(nextLevelIndex);

        while (logIndex == 0) {
            nextLevelIndents.get(nextLevelIndex++).printTo(writer);
            logIndex = getNextLevelIndentsLogIndex(nextLevelIndex);
        }

        for (int i = 0; i < logs.getSize(); ++i) {
            writeLogText(writer, logs.get(i));
            while (logIndex == i + 1) {
                nextLevelIndents.get(nextLevelIndex++).printTo(writer);
                logIndex = getNextLevelIndentsLogIndex(nextLevelIndex);
            }
        }
    }

    public void printTo(final BufferedWriter writer, final String filter) {
        if (filter == null || filter.isEmpty()) {
            return;
        }

        int nextLevelIndex = 0;
        int logIndex = getNextLevelIndentsLogIndex(nextLevelIndex);

        while (logIndex == 0) {
            nextLevelIndents.get(nextLevelIndex++).printTo(writer, filter);
            logIndex = getNextLevelIndentsLogIndex(nextLevelIndex);
        }

        for (int i = 0; i < logs.getSize(); ++i) {
            String logText = logs.get(i);
            boolean isPrintAble = logText.contains(filter);

            if (isPrintAble) {
                writeLogText(writer, logText);
                while (logIndex == i + 1) {
                    nextLevelIndents.get(nextLevelIndex++).printTo(writer, filter);
                    logIndex = getNextLevelIndentsLogIndex(nextLevelIndex);
                }
            } else {
                while (logIndex == i + 1) {
                    logIndex = getNextLevelIndentsLogIndex(++nextLevelIndex);
                }
            }
        }
    }

    public Indent indent() {
        Indent nextLevelIndent = new Indent(this, indentCount + 1, indentSpace + "  ");
        this.nextLevelIndents.add(nextLevelIndent);
        this.nextLevelIndentsLogIndexes.add(logs.getSize());

        return nextLevelIndent;
    }

    public Indent unIndent() {
        if (prevLevelIndent == null) {
            return this;
        } else {
            return prevLevelIndent;
        }
    }

    public void clear() {
        for (int i = 0; i < nextLevelIndents.getSize(); ++i) {
            nextLevelIndents.get(i).clear();
        }

        logs.clear();
        nextLevelIndentsLogIndexes.clear();

        prevLevelIndent = null;
        nextLevelIndents.clear();
        indentCount = 0;
    }

    public void discard() {
        for (int i = 0; i < nextLevelIndents.getSize(); ++i) {
            nextLevelIndents.get(i).discard();
        }

        logs.clear();
        nextLevelIndentsLogIndexes.clear();
        nextLevelIndents.clear();
        indentCount = 0;
    }
}