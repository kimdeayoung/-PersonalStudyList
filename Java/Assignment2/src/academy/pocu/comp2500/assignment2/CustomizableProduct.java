package academy.pocu.comp2500.assignment2;

import java.util.ArrayList;

public class CustomizableProduct extends Product {
    protected ArrayList<Aperture> apertures;

    protected OrientationType orientation;

    protected CustomizableProduct(int productId, ShippingOption deliveryMethod, OrientationType orientation) {
        super(productId, deliveryMethod);
        this.apertures = new ArrayList<>();
        this.orientation = orientation;
    }

    public ArrayList<Aperture> getApertures() {
        return apertures;
    }

    public void addApertures(Aperture aperture) {
        if (aperture.isAddAbleAperture(this.width, this.height)) {
            this.apertures.add(aperture);
            this.price += 5;
        }
    }

    public OrientationType getOrientation() {
        return orientation;
    }
}
