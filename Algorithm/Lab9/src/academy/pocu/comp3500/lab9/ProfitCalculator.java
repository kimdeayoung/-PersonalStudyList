package academy.pocu.comp3500.lab9;

import academy.pocu.comp3500.lab9.data.Task;

public class ProfitCalculator {
    public static int findMaxProfit(final Task[] tasks, final int[] skillLevels) {
        if (tasks == null || skillLevels == null) {
            return 0;
        }

        quickSortTaskRecursive(tasks, 0, tasks.length - 1);

        int profit = 0;
        for (int i = 0; i < skillLevels.length; ++i) {
            for (int j = 0; j < tasks.length; ++j) {
                if (tasks[j].getDifficulty() <= skillLevels[i]) {
                    profit += tasks[j].getProfit();
                    break;
                }
            }
        }

        return profit;
    }

    private static void quickSortTaskRecursive(final Task[] tasks, int left, int right) {
        if (left >= right) {
            return;
        }

        int pivotValue = tasks[right].getProfit();
        int leftIndex = left;

        for (int i = left; i < right; ++i) {
            if (tasks[i].getProfit() > pivotValue) {
                Task temp = tasks[i];
                tasks[i] = tasks[leftIndex];
                tasks[leftIndex++] = temp;
            }
        }

        {
            Task temp = tasks[right];
            tasks[right] = tasks[leftIndex];
            tasks[leftIndex] = temp;
        }

        quickSortTaskRecursive(tasks, left, leftIndex - 1);
        quickSortTaskRecursive(tasks, leftIndex + 1, right);
    }
}