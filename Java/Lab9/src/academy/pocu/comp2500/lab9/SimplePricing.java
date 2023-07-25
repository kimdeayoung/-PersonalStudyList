package academy.pocu.comp2500.lab9;

import java.util.Collection;

public class SimplePricing implements ICalTotalPriceAble {
    public int getTotalPrice(Collection<Book> books) {
        int totalPrice = 0;

        for (Book book : books) {
            totalPrice += book.getPrice();
        }

        return totalPrice;
    }
}
