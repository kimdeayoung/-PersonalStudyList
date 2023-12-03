package academy.pocu.comp3500.lab6;

public class IntValue {
    private int value;
    public IntValue(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public void increase() {
        ++this.value;
    }
}
