package academy.pocu.comp2500.lab6;

import java.util.ArrayList;

public class Pizza extends Menu {
    protected static final int MAX_MEAT_COUNT = 2;
    protected static final int MAX_VEGGIE_COUNT = 2;
    protected static final int MAX_CHEESE_COUNT = 2;
    protected ArrayList<Topping> toppings;

    protected Pizza(int price, int maxMeatCount, int maxVeggieCount, int maxCheeseCount, boolean isCheckCheeseAdded, boolean isCheckVeggieAdded) {
        super(price, maxMeatCount, maxVeggieCount, maxCheeseCount, isCheckCheeseAdded, isCheckVeggieAdded, 0, 0, 0);
        toppings = new ArrayList<>();
    }

    public ArrayList<Topping> getToppings() {
        return this.toppings;
    }
}
