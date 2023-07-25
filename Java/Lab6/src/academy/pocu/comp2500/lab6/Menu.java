package academy.pocu.comp2500.lab6;

import com.sun.source.tree.AssertTree;

import java.util.ArrayList;

public class Menu {
    protected int price;

    protected int meatCount;
    protected int veggieCount;
    protected int cheeseCount;

    protected int maxMeatCount;
    protected int maxVeggieCount;
    protected int maxCheeseCount;

    protected boolean isCheeseAdded;
    protected boolean isVeggieAdded;

    protected boolean isCheckCheeseAdded;
    protected boolean isCheckVeggieAdded;

    protected ArrayList<Appetizer> appetizers;
    protected ArrayList<Dessert> desserts;

    protected ArrayList<MainCourse> mainCourses;

    protected int maxAppetizerCount;
    protected int maxDessertCount;
    protected int maxMainCourseCount;

    protected Menu(int price, int maxMeatCount, int maxVeggieCount, int maxCheeseCount, boolean isCheckCheeseAdded, boolean isCheckVeggieAdded, int maxAppetizerCount, int maxDessertCount, int maxMainCourseCount) {
        this.price = price;
        this.appetizers = new ArrayList<>();
        this.desserts = new ArrayList<>();
        this.mainCourses = new ArrayList<>();

        this.maxMeatCount = maxMeatCount;
        this.maxVeggieCount = maxVeggieCount;
        this.maxCheeseCount = maxCheeseCount;

        this.isCheckCheeseAdded = isCheckCheeseAdded;
        this.isCheckVeggieAdded = isCheckVeggieAdded;

        this.maxAppetizerCount = maxAppetizerCount;
        this.maxDessertCount = maxDessertCount;
        this.maxMainCourseCount = maxMainCourseCount;
    }

    public int getPrice() {
        return price;
    }

    public boolean isValid() {
        boolean result = meatCount == maxMeatCount &&
                veggieCount == maxVeggieCount &&
                cheeseCount == maxCheeseCount;

        if (isCheckCheeseAdded) {
            result &= isCheeseAdded;
        }

        if (isCheckVeggieAdded) {
            result &= isVeggieAdded;
        }

        result &= appetizers.size() >= this.maxAppetizerCount;
        result &= desserts.size() >= this.maxDessertCount;
        result &= mainCourses.size() >= this.maxMainCourseCount;

        return result;
    }
}
