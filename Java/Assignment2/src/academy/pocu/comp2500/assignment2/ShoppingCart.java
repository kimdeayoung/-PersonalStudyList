package academy.pocu.comp2500.assignment2;

import java.util.ArrayList;

public class ShoppingCart {
    ArrayList<Product> products;

    public ShoppingCart() {
        products = new ArrayList<>();
    }

    public ArrayList<Product> getProducts() {
        return products;
    }

    public void addProduct(Product product) {
        this.products.add(product);
    }

    public boolean removeProduct(Product product) {
        return this.products.remove(product);
    }

    public int getTotalPrice() {
        int price = 0;
        for (Product product : this.products) {
            price += product.getPrice();
        }

        return price;
    }
}
