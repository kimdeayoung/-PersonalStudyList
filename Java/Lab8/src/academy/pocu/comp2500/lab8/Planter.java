package academy.pocu.comp2500.lab8;

import java.util.ArrayList;

public class Planter {
    private final int WATERCONSUMPTIONPERTICK = 2;
    private int waterAmount;

    //private static final instance = ;
    private ArrayList<SmartDevice> devices;
    private ArrayList<IDrainable> drainables;
    private ArrayList<ISprayable> sprayables;
    private ArrayList<IWaterDetectable> waterDetectables;

    public Planter(int waterAmount) {
        this.waterAmount = waterAmount;
        this.devices = new ArrayList<>();
        this.drainables = new ArrayList<>();
        this.sprayables = new ArrayList<>();
        this.waterDetectables = new ArrayList<>();
    }

    public int getWaterAmount() {
        return waterAmount;
    }

    public void setWaterAmount(int waterAmount) {
        this.waterAmount = waterAmount;
    }

    public void installSmartDevice(SmartDevice device) {
        this.devices.add(device);
        device.registInterface(this);
    }

    public void installDrainable(IDrainable drainable) {
        this.drainables.add(drainable);
    }

    public void installSprayable(ISprayable sprayable) {
        this.sprayables.add(sprayable);
    }

    public void installWaterDetectables(IWaterDetectable waterDetectable) {
        this.waterDetectables.add(waterDetectable);
    }

    public void tick() {
        for (SmartDevice device : this.devices) {
            device.onTick();
        }

        for (IWaterDetectable waterDetectable : this.waterDetectables) {
            waterDetectable.detect(this.waterAmount);
        }

        for (IDrainable drainable : this.drainables) {
            drainable.drain(this);
        }

        for (ISprayable sprayable : this.sprayables) {
            sprayable.spray(this);
        }

        this.waterAmount -= WATERCONSUMPTIONPERTICK;
        if (this.waterAmount < 0) {
            this.waterAmount = 0;
        }
    }
}
