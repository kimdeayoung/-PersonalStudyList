package academy.pocu.comp2500.assignment2;

public class Banner extends CustomizableProduct {
    private BannerType bannerType;
    private BannerSizeType bannerSize;

    public Banner(int productId, BannerType bannerType, Color bannerColor, BannerSizeType bannerSize, ShippingOption deliveryMethod, OrientationType bannerOrientation) {
        super(productId, deliveryMethod, bannerOrientation);
        this.bannerType = bannerType;
        this.bannerSize = bannerSize;
        this.color = bannerColor;

        switch (bannerType) {
            case GLOSS:
                this.displayName = "Gloss Banner";
                break;
            case SCRIM:
                this.displayName = "Scrim Banner";
                break;
            case MESH:
                this.displayName = "Mesh Banner";
                break;
        }

        switch (bannerSize) {
            case SIZE_TYPE1:
                this.width = 1000;
                this.height = 500;
                break;
            case SIZE_TYPE2:
                this.width = 1000;
                this.height = 1000;
                break;
            case SIZE_TYPE3:
                this.width = 2000;
                this.height = 500;
                break;
            case SIZE_TYPE4:
                this.width = 3000;
                this.height = 1000;
                break;
        }

        switch (bannerType) {
            case GLOSS:
                switch (bannerSize) {
                    case SIZE_TYPE1:
                        this.price = 5000;
                        break;
                    case SIZE_TYPE2:
                        this.price = 5200;
                        break;
                    case SIZE_TYPE3:
                        this.price = 5300;
                        break;
                    case SIZE_TYPE4:
                        this.price = 6000;
                        break;
                }
                break;
            case SCRIM:
            case MESH:
                switch (bannerSize) {
                    case SIZE_TYPE1:
                        this.price = 5100;
                        break;
                    case SIZE_TYPE2:
                        this.price = 5300;
                        break;
                    case SIZE_TYPE3:
                        this.price = 5400;
                        break;
                    case SIZE_TYPE4:
                        this.price = 6100;
                        break;
                }
                break;
        }
    }

    public BannerType getBannerType() {
        return bannerType;
    }

    public BannerSizeType getBannerSize() {
        return bannerSize;
    }
}
