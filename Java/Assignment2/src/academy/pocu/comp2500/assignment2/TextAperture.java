package academy.pocu.comp2500.assignment2;

public class TextAperture extends Aperture {
    private String text;

    public TextAperture(String text, int x, int y, int width, int height) {
        super(x, y, width, height);
        this.text = text;
    }

    public String getText() {
        return text;
    }
}
