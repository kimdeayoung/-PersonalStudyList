package academy.pocu.comp2500.assignment2;

public class Product {
    protected int productId;
    protected String displayName;
    protected Color color;

    protected int width;
    protected int height;

    protected int price;

    protected ShippingOption deliveryMethod;

    protected Product(int productId, ShippingOption deliveryMethod) {
        this.productId = productId;
        this.deliveryMethod = deliveryMethod;
    }

    public int getProductId() {
        return productId;
    }

    public String getDisplayName() {
        return this.displayName;
    }

    public Color getColor() {
        return color;
    }

    public int getRed() {
        return color.getRed();
    }

    public int getGreen() {
        return color.getGreen();
    }

    public int getBlue() {
        return color.getBlue();
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int getPrice() {
        return this.price;
    }

    public ShippingOption getDeliveryMethod() {
        return deliveryMethod;
    }

    public void setDeliveryMethod(ShippingOption deliveryMethod) {
        this.deliveryMethod = deliveryMethod;
    }
}
