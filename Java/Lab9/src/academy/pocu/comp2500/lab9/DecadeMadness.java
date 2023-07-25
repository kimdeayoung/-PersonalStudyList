package academy.pocu.comp2500.lab9;

import java.util.Collection;
import java.util.HashMap;

public class DecadeMadness implements ICalTotalPriceAble {
    public int getTotalPrice(Collection<Book> books) {
        HashMap<Integer, Integer> decadePrice = new HashMap<>();
        HashMap<Integer, Integer> decadeCount = new HashMap<>();

        for (Book book : books) {
            int key = book.getPublishedYear() / 10;
            if (decadePrice.containsKey(key)) {
                int value = decadePrice.get(key) + book.getPrice();
                decadePrice.put(key, value);
            } else {
                decadePrice.put(key, book.getPrice());
            }

            int count = decadeCount.getOrDefault(key, 0);
            decadeCount.put(key, ++count);
        }

        double price = 0;
        for (Integer key : decadePrice.keySet()) {
            double calValue = (double) decadePrice.get(key);
            if (decadeCount.get(key) > 1) {
                calValue *= 0.8;
            }

            price += calValue;
        }

        return (int) price;
    }
}
