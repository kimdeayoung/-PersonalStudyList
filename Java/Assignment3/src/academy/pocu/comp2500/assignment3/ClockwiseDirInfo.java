package academy.pocu.comp2500.assignment3;

public class ClockwiseDirInfo {
    private boolean isRightDir; // 12~5시 방향까지인지
    private double dirValue;

    public ClockwiseDirInfo(boolean isrightDir, double dirValue) {
        this.isRightDir = isrightDir;
        this.dirValue = dirValue;
    }

    public boolean isRightDir() {
        return isRightDir;
    }

    public double getDirValue() {
        return dirValue;
    }

    public boolean isHigherClockwise(ClockwiseDirInfo compareInfo) {
        if (isRightDir == compareInfo.isRightDir()) {
            if (isRightDir) {
                return this.dirValue > compareInfo.dirValue;
            } else {
                return this.dirValue < compareInfo.dirValue;
            }
        } else {
            return isRightDir;
        }
    }
}
