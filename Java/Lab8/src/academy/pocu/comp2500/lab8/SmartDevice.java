package academy.pocu.comp2500.lab8;

public abstract class SmartDevice {
    protected int tick;
    protected int onDeviceTick;

    protected boolean prevOnState;

    public boolean isOn() {
        return false;
    }

    public void onTick() {
        ++this.tick;
    }

    public int getTicksSinceLastUpdate() {
        boolean onState = isOn();
        if (onState != prevOnState) {
            onDeviceTick = tick;
        }

        prevOnState = onState;

        return tick - onDeviceTick;
    }

    public void registInterface(Planter planter) {
    }
}
