package academy.pocu.comp3500.lab3;

import java.util.ArrayList;

public final class MissionControl {
    private MissionControl() {
    }

    public static int findMaxAltitudeTime(final int[] altitudes) {
        return findMaxAltitudeRecursive(altitudes, 0, altitudes.length - 1);
    }

    private static int findMaxAltitudeRecursive(final int[] altitudes, int left, int right) {
        int index = (left + right) / 2;
        int value = altitudes[index];
        if (left >= right) {
            return index;
        }

        if (value < altitudes[Integer.max(0, index - 1)]) {
            return findMaxAltitudeRecursive(altitudes, left, index - 1);
        } else if (value < altitudes[Integer.min(altitudes.length - 1, index + 1)]) {
            return findMaxAltitudeRecursive(altitudes, index + 1, right);
        } else {
            return index;
        }
    }

    public static ArrayList<Integer> findAltitudeTimes(final int[] altitudes, final int targetAltitude) {
        ArrayList<Integer> result = new ArrayList<>();
        if (altitudes.length == 1) {
            if (altitudes[0] == targetAltitude) {
                result.add(0);
            }
            return result;
        }

        int highValueIndex = findMaxAltitudeTime(altitudes);
        if (highValueIndex == 0) {
            findRightAltitudeTimesRecursive(altitudes, targetAltitude, result, 0, altitudes.length - 1);
        } else if (highValueIndex == altitudes.length - 1) {
            findLeftAltitudeTimesRecursive(altitudes, targetAltitude, result, 0, highValueIndex);
        } else {
            findLeftAltitudeTimesRecursive(altitudes, targetAltitude, result, 0, highValueIndex);
            findRightAltitudeTimesRecursive(altitudes, targetAltitude, result, highValueIndex + 1, altitudes.length - 1);
        }


        return result;
    }

    private static void findLeftAltitudeTimesRecursive(final int[] altitudes, final int targetAltitude, ArrayList<Integer> result, int left, int right) {
        int index = (left + right) / 2;
        int value = altitudes[index];
        if (value == targetAltitude) {
            result.add(index);
            return;
        } else if (left >= right) {
            return;
        }

        if (value > targetAltitude) {
            findLeftAltitudeTimesRecursive(altitudes, targetAltitude, result, left, Integer.max(left, index - 1));
        } else {
            findLeftAltitudeTimesRecursive(altitudes, targetAltitude, result, Integer.min(altitudes.length - 1, index + 1), right);
        }
    }

    private static void findRightAltitudeTimesRecursive(final int[] altitudes, final int targetAltitude, ArrayList<Integer> result, int left, int right) {
        int index = (left + right) / 2;
        int value = altitudes[index];
        if (value == targetAltitude) {
            result.add(index);
            return;
        } else if (left >= right) {
            return;
        }

        if (value < targetAltitude) {
            findRightAltitudeTimesRecursive(altitudes, targetAltitude, result, left, Integer.max(left, index - 1));
        } else {
            findRightAltitudeTimesRecursive(altitudes, targetAltitude, result, Integer.min(altitudes.length - 1, index + 1), right);
        }
    }
}