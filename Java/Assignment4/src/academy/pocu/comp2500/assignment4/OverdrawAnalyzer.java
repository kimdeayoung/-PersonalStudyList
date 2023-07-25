package academy.pocu.comp2500.assignment4;

import java.util.HashMap;
import java.util.LinkedList;

public class OverdrawAnalyzer extends Canvas {
    private final char SETABLE_MIN = 32;
    private final char SETABLE_MAX = 126;
    private final char UPPER_MIN = 65;
    private final char UPPER_MAX = 90;
    private final char LOWER_MIN = 97;
    private final char LOWER_MAX = 122;
    private HashMap<Integer, LinkedList<Character>> pixelHistorys;
    private char[] pixels;

    public OverdrawAnalyzer(int width, int height) {
        super(width, height);
        pixelHistorys = new HashMap<>();
        pixels = new char[width * height];

        for (int y = 0; y < getHeight(); ++y) {
            for (int x = 0; x < getWidth(); ++x) {
                this.pixels[getPixelIndex(x, y)] = ' ';
            }
        }
    }

    private int getPixelIndex(int x, int y) {
        return x + y * getWidth();
    }

    private boolean isValidRange(int x, int y) {
        return (x >= 0 && x < getWidth()) && (y >= 0 && y < getHeight());
    }

    @Override
    public char getPixel(int x, int y) {
        return this.pixels[getPixelIndex(x, y)];
    }

    private char getPixelCharacter(int x, int y) {
        int pixelIndex = getPixelIndex(x, y);
        return this.pixels[pixelIndex];
    }

    private boolean isSetablePixelCharacter(char character) {
        return character >= SETABLE_MIN && character <= SETABLE_MAX;
    }

    private boolean isUpperCharacter(char character) {
        return character >= UPPER_MIN && character <= UPPER_MAX;
    }

    private boolean isLowerCharacter(char character) {
        return character >= LOWER_MIN && character <= LOWER_MAX;
    }

    @Override
    public void drawPixel(int x, int y, char character) {
        if (isValidRange(x, y)) {
            int pixelIndex = getPixelIndex(x, y);
            if (isSetablePixelCharacter(character)) {
                if (isAddAbleCharacter(x, y, character)) {
                    this.pixels[pixelIndex] = character;
                    addPixelHistory(x, y, character);
                }
            }
        }
    }

    @Override
    public boolean increasePixel(int x, int y) {
        if (isValidRange(x, y)) {
            char character = getPixelCharacter(x, y);
            if (isSetablePixelCharacter(++character)) {
                if (isAddAbleCharacter(x, y, character)) {
                    int pixelIndex = getPixelIndex(x, y);
                    this.pixels[pixelIndex] = character;
                    addPixelHistory(x, y, character);
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public boolean decreasePixel(int x, int y) {
        if (isValidRange(x, y)) {
            char character = getPixelCharacter(x, y);
            if (isSetablePixelCharacter(--character)) {
                if (isAddAbleCharacter(x, y, character)) {
                    int pixelIndex = getPixelIndex(x, y);
                    this.pixels[pixelIndex] = character;
                    addPixelHistory(x, y, character);
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public void toUpper(int x, int y) {
        if (isValidRange(x, y)) {
            char character = getPixelCharacter(x, y);
            if (isLowerCharacter(character)) {
                character -= 32;
                if (isAddAbleCharacter(x, y, character)) {
                    int pixelIndex = getPixelIndex(x, y);
                    this.pixels[pixelIndex] = character;
                    addPixelHistory(x, y, character);
                }
            }
        }
    }

    @Override
    public void toLower(int x, int y) {
        if (isValidRange(x, y)) {
            char character = getPixelCharacter(x, y);
            if (isUpperCharacter(character)) {
                character += 32;
                if (isAddAbleCharacter(x, y, character)) {
                    int pixelIndex = getPixelIndex(x, y);
                    this.pixels[pixelIndex] = character;
                    addPixelHistory(x, y, character);
                }
            }
        }
    }

    @Override
    public void fillHorizontalLine(int y, char character) {
        if (y >= 0 && y < getHeight()) {
            if (isSetablePixelCharacter(character)) {
                for (int i = 0; i < getWidth(); ++i) {
                    int pixelIndex = getPixelIndex(i, y);
                    if (isAddAbleCharacter(i, y, character)) {
                        this.pixels[pixelIndex] = character;
                        addPixelHistory(i, y, character);
                    }
                }
            }
        }
    }

    @Override
    public void fillVerticalLine(int x, char character) {
        if (x >= 0 && x < getWidth()) {
            if (isSetablePixelCharacter(character)) {
                for (int i = 0; i < getHeight(); ++i) {
                    int pixelIndex = getPixelIndex(x, i);
                    if (isAddAbleCharacter(x, i, character)) {
                        this.pixels[pixelIndex] = character;
                        addPixelHistory(x, i, character);
                    }
                }
            }
        }
    }

    @Override
    public void clear() {
        if (this.pixels != null) {
            for (int y = 0; y < getHeight(); ++y) {
                for (int x = 0; x < getWidth(); ++x) {
                    if (isAddAbleCharacter(x, y, ' ')) {
                        this.pixels[getPixelIndex(x, y)] = ' ';
                        addPixelHistory(x, y, ' ');
                    }
                }
            }
        }
    }

    @Override
    public String getDrawing() {
        StringBuilder builder = new StringBuilder();
        builder.append('+');
        for (int i = 0; i < getWidth(); ++i) {
            builder.append('-');
        }
        builder.append('+').append(System.lineSeparator());

        for (int y = 0; y < getHeight(); ++y) {
            builder.append('|');
            for (int x = 0; x < getWidth(); ++x) {
                builder.append(getPixel(x, y));
            }
            builder.append('|').append(System.lineSeparator());
        }

        builder.append('+');
        for (int i = 0; i < getWidth(); ++i) {
            builder.append('-');
        }
        builder.append('+').append(System.lineSeparator());
        return builder.toString();
    }

    private boolean isAddAbleCharacter(int x, int y, char character) {
        int index = getPixelIndex(x, y);
        if (pixelHistorys.containsKey(index)) {
            LinkedList<Character> updateHistory = pixelHistorys.getOrDefault(index, new LinkedList<>());
            updateHistory.contains(character);
            if (updateHistory.getLast() == character) {
                return false;
            }
            return true;
        } else {
            return getPixel(x, y) != character;
        }
    }

    private void addPixelHistory(int x, int y, char character) {
        int index = getPixelIndex(x, y);
        if (pixelHistorys.containsKey(index)) {
            LinkedList<Character> updateHistory = pixelHistorys.get(index);
            updateHistory.add(character);
        } else {
            LinkedList<Character> updateHistory = new LinkedList<>();
            updateHistory.add(character);
            pixelHistorys.put(index, updateHistory);
        }
    }

    public LinkedList<Character> getPixelHistory(int x, int y) {
        int index = getPixelIndex(x, y);

        LinkedList<Character> updateHistory = pixelHistorys.getOrDefault(index, new LinkedList<>());
        return updateHistory;
    }

    public int getOverdrawCount() {
        int result = 0;
        for (int y = 0; y < getHeight(); ++y) {
            for (int x = 0; x < getWidth(); ++x) {
                int index = getPixelIndex(x, y);

                LinkedList<Character> updateHistory = pixelHistorys.getOrDefault(index, new LinkedList<>());
                result += updateHistory.size();
            }
        }

        return result;
    }

    public int getOverdrawCount(int x, int y) {
        int index = getPixelIndex(x, y);

        LinkedList<Character> updateHistory = pixelHistorys.getOrDefault(index, new LinkedList<>());
        return updateHistory.size();
    }
}
