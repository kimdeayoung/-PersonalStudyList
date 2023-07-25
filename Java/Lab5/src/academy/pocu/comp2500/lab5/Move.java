package academy.pocu.comp2500.lab5;

public class Move {
    private String name;

    private int power;
    private int useAbleMaxPower;
    private int maxPower;


    public Move(String name, int power, int maxPower) {
        this.name = name;
        this.power = power;
        this.useAbleMaxPower = maxPower;
        this.maxPower = maxPower;
    }

    public String getName() {
        return name;
    }

    public int getPower() {
        return power;
    }

    public boolean isUseAble() {
        return this.useAbleMaxPower > 0;
    }

    public boolean isEqual(String name) {
        return this.name.equals(name);
    }

    public void useMove() {
        if (this.useAbleMaxPower > 0) {
            this.useAbleMaxPower -= 1;
        }
    }

    public void refillMove() {
        if (this.maxPower > this.useAbleMaxPower) {
            this.useAbleMaxPower += 1;
        }
    }
}
