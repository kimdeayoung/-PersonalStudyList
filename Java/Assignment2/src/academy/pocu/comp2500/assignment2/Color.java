package academy.pocu.comp2500.assignment2;

import java.util.Locale;

public class Color {
    private int red;
    private int green;
    private int blue;

    public Color(int red, int green, int blue) {
        this.red = getCorrectionColor(red);
        this.green = getCorrectionColor(green);
        this.blue = getCorrectionColor(blue);
    }

    public int getRed() {
        return this.red;
    }

    public int getGreen() {
        return this.green;
    }

    public int getBlue() {
        return this.blue;
    }

    public String getColor() {
        StringBuilder builder = new StringBuilder();
        builder.append("#");
        builder.append(getHexString(this.red));
        builder.append(getHexString(this.green));
        builder.append(getHexString(this.blue));
        return builder.toString();
    }

    private String getHexString(int color) {
        String text = Integer.toHexString(color);
        if (text.length() < 2) {
            StringBuilder builder = new StringBuilder();
            builder.append("0");
            builder.append(text);
            text = builder.toString();
        }
        text = text.toUpperCase();
        return text;
    }

    private int getCorrectionColor(int color) {
        int result = color;
        if (result < 0) {
            result = 0;
        } else if (result > 255) {
            result = 255;
        }
        return result;
    }
}
