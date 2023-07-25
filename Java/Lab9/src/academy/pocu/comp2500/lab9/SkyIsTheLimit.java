package academy.pocu.comp2500.lab9;

import java.util.Collection;

public class SkyIsTheLimit implements ICalTotalPriceAble {
    private final int CALTOTALPRICEABLECOUNT = 5;
    private int discountAblePrice;

    public SkyIsTheLimit(int price) {
        this.discountAblePrice = price;
    }

    public int getTotalPrice(Collection<Book> books) {
        int totalPrice = 0;
        if (books.size() >= CALTOTALPRICEABLECOUNT) {
            int[] higherPrices = new int[]{0, 0};
            int[] higherindexes = new int[]{0, 0};

            boolean[] isHigher = new boolean[]{false, false};

            int findBookIndex = 0;
            for (Book book : books) {
                totalPrice += book.getPrice();

                isHigher[0] = false;
                isHigher[1] = false;

                for (int i = 0; i < higherPrices.length; ++i) {
                    if (higherPrices[i] < book.getPrice()) {
                        isHigher[i] = true;
                    }
                }

                if (isHigher[0] && isHigher[1]) {
                    if (higherPrices[0] > higherPrices[1]) {
                        higherPrices[1] = book.getPrice();
                        higherindexes[1] = findBookIndex;
                    } else {
                        higherPrices[0] = book.getPrice();
                        higherindexes[0] = findBookIndex;
                    }
                } else {
                    for (int i = 0; i < isHigher.length; ++i) {
                        if (isHigher[i]) {
                            higherPrices[i] = book.getPrice();
                            higherindexes[i] = findBookIndex;
                            break;
                        }
                    }
                }

                findBookIndex++;
            }

            if (totalPrice >= discountAblePrice) {
                double newTotalValue = 0;
                findBookIndex = 0;
                for (Book book : books) {
                    double price = (double) book.getPrice();
                    for (int i = 0; i < higherindexes.length; ++i) {
                        if (findBookIndex == higherindexes[i]) {
                            price *= 0.5;
                            break;
                        }
                    }

                    findBookIndex++;
                    newTotalValue += price;
                }

                return (int) newTotalValue;
            } else {
                return totalPrice;
            }
        } else {
            for (Book book : books) {
                totalPrice += book.getPrice();
            }
            return totalPrice;
        }
    }
}
