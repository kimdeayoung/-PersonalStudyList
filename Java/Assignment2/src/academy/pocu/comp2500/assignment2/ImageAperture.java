package academy.pocu.comp2500.assignment2;

public class ImageAperture extends Aperture {
    private String imagePath;

    public ImageAperture(String imagePath, int x, int y, int width, int height) {
        super(x, y, width, height);
        this.imagePath = imagePath;
    }

    public String getImagePath() {
        return imagePath;
    }
}
