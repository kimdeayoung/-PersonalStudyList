package academy.pocu.comp2500.lab8;

public class Drainer extends SmartDevice implements IWaterDetectable, IDrainable {
    private final int DRAINWATERAMOUNT = 7;
    private int waterLevel;
    private boolean isActionable;

    public Drainer(int waterLevel) {
        this.waterLevel = waterLevel;
    }

    public void registInterface(Planter planter) {
        planter.installDrainable(this);
        planter.installWaterDetectables(this);
    }

    @Override
    public boolean isOn() {
        return isActionable;
    }

    @Override
    public void onTick() {
        super.onTick();
    }

    public void drain(Planter planter) {
        if (isOn()) {
            planter.setWaterAmount(planter.getWaterAmount() - DRAINWATERAMOUNT);
        }
    }

    public void detect(final int waterLevel) {
        this.isActionable = this.waterLevel <= waterLevel;
    }
}
