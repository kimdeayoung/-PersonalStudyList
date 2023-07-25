package academy.pocu.comp2500.assignment2;

public class Calendar extends Product {
    private CalenderType calenderType;

    public Calendar(int productId, CalenderType calendarType, ShippingOption deliveryMethod) {
        super(productId, deliveryMethod);
        this.calenderType = calendarType;
        this.color = new Color(255, 255, 255);

        switch (calendarType) {
            case WALL_CALENDER:
                this.displayName = "Wall Calendar";
                this.width = 400;
                this.height = 400;
                this.price = 1000;
                break;
            case DESK_CALENDER:
                this.displayName = "Desk Calendar";
                this.width = 200;
                this.height = 150;
                this.price = 1000;
                break;
            case MAGNET_CALENDER:
                this.displayName = "Magnet Calendar";
                this.width = 100;
                this.height = 200;
                this.price = 1500;
                break;
        }
    }

    public CalenderType getCalenderType() {
        return calenderType;
    }
}
