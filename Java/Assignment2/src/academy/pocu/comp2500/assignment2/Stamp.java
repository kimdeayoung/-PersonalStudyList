package academy.pocu.comp2500.assignment2;

public class Stamp extends Product {
    private StampType stampType;
    private StampSizeType stampSize;
    private String text;

    public Stamp(int productId, StampType stampType, StampSizeType stampSize, ShippingOption deliveryMethod, String text) {
        super(productId, deliveryMethod);
        this.stampType = stampType;
        this.stampSize = stampSize;
        this.displayName = "Stamp";
        this.text = text;

        switch (stampType) {
            case RED_STAMP:
                this.color = new Color(255, 0, 0);
                break;
            case GREEN_STAMP:
                this.color = new Color(0, 80, 0);
                break;
            case BLUE_STAMP:
                this.color = new Color(0, 0, 255);
                break;
        }

        switch (stampSize) {
            case SIZE_TYPE1:
                this.width = 40;
                this.height = 30;
                this.price = 2300;
                break;
            case SIZE_TYPE2:
                this.width = 50;
                this.height = 20;
                this.price = 2300;
                break;
            case SIZE_TYPE3:
                this.width = 70;
                this.height = 40;
                this.price = 2600;
                break;
        }
    }

    public StampType getStampType() {
        return stampType;
    }

    public StampSizeType getStampSize() {
        return stampSize;
    }

    public String getText() {
        return text;
    }
}
