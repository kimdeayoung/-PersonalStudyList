package academy.pocu.comp2500.lab8;

import java.util.ArrayDeque;
import java.util.Queue;

public class Sprinkler extends SmartDevice implements ISprayable {
    private final int SPRAYWATERAMOUNT = 15;
    private Queue<Schedule> schedules;
    private int maintainCount;
    private int scheduleChangeDelayCount;

    public Sprinkler() {
        schedules = new ArrayDeque<>();
    }

    public void registInterface(Planter planter) {
        planter.installSprayable(this);
    }

    public void addSchedule(Schedule schedule) {
        if (schedule.getOnTickCount() > 0) {
            schedules.add(schedule);
        }
    }

    @Override
    public boolean isOn() {
        return maintainCount > 0;
    }

    @Override
    public void onTick() {
        super.onTick();

        maintainCount -= 1;
        scheduleChangeDelayCount -= 1;
        if (maintainCount < 0) {
            maintainCount = 0;
        }
        if (scheduleChangeDelayCount < 0) {
            scheduleChangeDelayCount = 0;
        }

        if (this.schedules.size() > 0) {
            Schedule schedule = this.schedules.peek();

            if (scheduleChangeDelayCount == 0) {
                if (schedule.getOnTickCount() == this.tick) {
                    maintainCount = schedule.getMaintainTickCount();
                    scheduleChangeDelayCount = schedule.getMaintainTickCount();
                } else if (schedule.getOnTickCount() < this.tick) {
                    while (true) {
                        schedule = this.schedules.peek();
                        if (schedule == null) {
                            break;
                        }

                        int scheduleableCount = (schedule.getOnTickCount() + schedule.getMaintainTickCount() - 1) - tick;
                        if (scheduleableCount <= 0) {
                            if (this.schedules.size() > 0) {
                                this.schedules.remove();
                            } else {
                                break;
                            }
                        } else {
                            if (this.tick > schedule.getOnTickCount()) {
                                scheduleChangeDelayCount = scheduleableCount;
                            }
                            break;
                        }
                    }

                } else if (schedule.getOnTickCount() > this.tick) {
                    scheduleChangeDelayCount = schedule.getOnTickCount() - tick;
                }
            }
        }

        boolean onState = isOn();
        if (onState != prevOnState) {
            onDeviceTick = tick;
        }

        prevOnState = onState;
    }

    public int getTicksSinceLastUpdate() {
        return tick - onDeviceTick;
    }

    public void spray(Planter planter) {
        if (isOn()) {
            planter.setWaterAmount(planter.getWaterAmount() + SPRAYWATERAMOUNT);
        }
    }
}
