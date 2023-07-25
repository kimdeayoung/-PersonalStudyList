package academy.pocu.comp2500.assignment4;

public class Canvas {
    private final char SETABLE_MIN = 32;
    private final char SETABLE_MAX = 126;
    private final char UPPER_MIN = 65;
    private final char UPPER_MAX = 90;
    private final char LOWER_MIN = 97;
    private final char LOWER_MAX = 122;


    private int width;
    private int height;
    private char[] pixels;

    public Canvas(int width, int height) {
        this.width = width;
        this.height = height;
        this.pixels = new char[this.width * this.height];
        clear();
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    private int getPixelIndex(int x, int y) {
        return x + y * this.width;
    }

    private boolean isValidRange(int x, int y) {
        return (x >= 0 && x < this.width) && (y >= 0 && y < this.height);
    }

    private char getPixelCharacter(int x, int y) {
        int pixelIndex = getPixelIndex(x, y);
        return this.pixels[pixelIndex];
    }

    private boolean isSetablePixelCharacter(char character) {
        return character >= SETABLE_MIN && character <= SETABLE_MAX;
    }

    public void drawPixel(int x, int y, char character) {
        if (isValidRange(x, y)) {
            int pixelIndex = getPixelIndex(x, y);
            if (isSetablePixelCharacter(character)) {
                this.pixels[pixelIndex] = character;
            }
        }
    }

    public char getPixel(int x, int y) {
        return this.pixels[getPixelIndex(x, y)];
    }

    public boolean increasePixel(int x, int y) {
        if (isValidRange(x, y)) {
            char character = getPixelCharacter(x, y);
            if (isSetablePixelCharacter(++character)) {
                int pixelIndex = getPixelIndex(x, y);
                this.pixels[pixelIndex] = character;
                return true;
            } else {
                --character;
            }
        }
        return false;
    }

    public boolean decreasePixel(int x, int y) {
        if (isValidRange(x, y)) {
            char character = getPixelCharacter(x, y);
            if (isSetablePixelCharacter(--character)) {
                int pixelIndex = getPixelIndex(x, y);
                this.pixels[pixelIndex] = character;
                return true;
            }
        }
        return false;
    }

    public void toUpper(int x, int y) {
        if (isValidRange(x, y)) {
            char character = getPixelCharacter(x, y);
            if (character >= LOWER_MIN && character <= LOWER_MAX) {
                character -= 32;
                int pixelIndex = getPixelIndex(x, y);
                this.pixels[pixelIndex] = character;
            }
        }
    }

    public void toLower(int x, int y) {
        if (isValidRange(x, y)) {
            char character = getPixelCharacter(x, y);
            if (character >= UPPER_MIN && character <= UPPER_MAX) {
                character += 32;
                int pixelIndex = getPixelIndex(x, y);
                this.pixels[pixelIndex] = character;
            }
        }
    }

    public void fillHorizontalLine(int y, char character) {
        if (y >= 0 && y < this.height) {
            if (isSetablePixelCharacter(character)) {
                for (int i = 0; i < this.width; ++i) {
                    int pixelIndex = getPixelIndex(i, y);
                    this.pixels[pixelIndex] = character;
                }
            }
        }
    }

    public void fillVerticalLine(int x, char character) {
        if (x >= 0 && x < this.width) {
            if (isSetablePixelCharacter(character)) {
                for (int i = 0; i < this.height; ++i) {
                    int pixelIndex = getPixelIndex(x, i);
                    this.pixels[pixelIndex] = character;
                }
            }
        }
    }

    public void clear() {
        for (int y = 0; y < this.height; ++y) {
            for (int x = 0; x < this.width; ++x) {
                this.pixels[getPixelIndex(x, y)] = ' ';
            }
        }
    }

    public String getDrawing() {
        StringBuilder builder = new StringBuilder();
        builder.append('+');
        for (int i = 0; i < this.width; ++i) {
            builder.append('-');
        }
        builder.append('+').append(System.lineSeparator());

        for (int y = 0; y < this.height; ++y) {
            builder.append('|');
            for (int x = 0; x < this.width; ++x) {
                builder.append(getPixel(x, y));
            }
            builder.append('|').append(System.lineSeparator());
        }

        builder.append('+');
        for (int i = 0; i < this.width; ++i) {
            builder.append('-');
        }
        builder.append('+').append(System.lineSeparator());
        return builder.toString();
    }
}
