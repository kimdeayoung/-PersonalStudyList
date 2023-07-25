package academy.pocu.comp2500.lab6;

import java.util.ArrayList;

public class SetMenu extends Menu {
    protected SetMenu(int price, int maxAppetizerCount, int maxDessertCount, int maxMainCourseCount) {
        super(price, 0, 0, 0, false, false, maxAppetizerCount, maxDessertCount, maxMainCourseCount);
    }

    public ArrayList<Appetizer> getAppetizers() {
        return appetizers;
    }

    public ArrayList<Dessert> getDesserts() {
        return desserts;
    }

    public ArrayList<MainCourse> getMainCourses() {
        return mainCourses;
    }
}
