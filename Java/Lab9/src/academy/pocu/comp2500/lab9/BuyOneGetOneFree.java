package academy.pocu.comp2500.lab9;

import java.util.Collection;
import java.util.HashSet;
import java.util.UUID;

public class BuyOneGetOneFree implements ICalTotalPriceAble {
    private HashSet<UUID> skus;

    public BuyOneGetOneFree(HashSet<UUID> skus) {
        this.skus = skus;
    }

    public int getTotalPrice(Collection<Book> books) {
        int price = 0;

        HashSet<UUID> sameCheckSet = new HashSet<>();

        for (Book book : books) {
            if (sameCheckSet.contains(book.getSku())) {
                sameCheckSet.remove(book.getSku());
            } else {
                price += book.getPrice();
                if (skus.contains(book.getSku())) {
                    sameCheckSet.add(book.getSku());
                }
            }
        }

        return price;
    }
}
