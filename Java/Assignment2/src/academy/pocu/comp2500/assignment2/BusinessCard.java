package academy.pocu.comp2500.assignment2;

public class BusinessCard extends CustomizableProduct {
    private PaperMaterial paperMaterial;
    private BusinessCardColorType cardColor;
    private BusinessCardSideType sideType;

    public BusinessCard(int productId, PaperMaterial paperMaterial, BusinessCardColorType cardColor, ShippingOption deliveryMethod, OrientationType cardOrientation, BusinessCardSideType businessCardSides) {
        super(productId, deliveryMethod, cardOrientation);
        this.paperMaterial = paperMaterial;
        this.cardColor = cardColor;
        this.width = 90;
        this.height = 50;
        this.sideType = businessCardSides;

        switch (paperMaterial) {
            case LINEN:
                this.displayName = "Linen Business Card";
                this.price = 110;
                break;
            case LAID:
                this.displayName = "Laid Business Card";
                this.price = 120;
                break;
            case SMOOTH:
                this.displayName = "Smooth Business Card";
                this.price = 100;
                break;
        }
        if (this.sideType == BusinessCardSideType.DOUBLE_SIDE) {
            this.price += 30;
        }

        switch (cardColor) {
            case GRAY:
                this.color = new Color(230, 230, 230);
                break;
            case IVORY:
                this.color = new Color(255, 255, 240);
                break;
            case WHITE:
                this.color = new Color(255, 255, 255);
                break;
        }
    }

    public PaperMaterial getPaperMaterial() {
        return paperMaterial;
    }

    public BusinessCardColorType getCardColor() {
        return cardColor;
    }

    public BusinessCardSideType getSideType() {
        return sideType;
    }
}
