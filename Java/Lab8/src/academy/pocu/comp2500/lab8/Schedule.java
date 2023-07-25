package academy.pocu.comp2500.lab8;

public class Schedule {
    private int onTickCount;
    private int maintainTickCount;

    public Schedule(int onTickCount, int maintainTickCount) {
        this.onTickCount = onTickCount;
        this.maintainTickCount = maintainTickCount;
    }

    public int getOnTickCount() {
        return onTickCount;
    }

    public int getMaintainTickCount() {
        return maintainTickCount;
    }
}
