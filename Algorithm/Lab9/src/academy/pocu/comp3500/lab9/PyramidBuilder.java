package academy.pocu.comp3500.lab9;

public class PyramidBuilder {
    public static int findMaxHeight(final int[] widths, int statue) {
        if (widths == null) {
            return 0;
        }

        quickSortRecursive(widths, 0, widths.length - 1);

        int width = statue;
        int stoneCount = 1;

        int calWidth = 0;
        int calStoneCount = 0;

        int stoneUseIndex = 0;

        int result = 0;

        while (stoneUseIndex < widths.length) {
            int newWidth = widths[stoneUseIndex++];
            calWidth += newWidth;
            ++calStoneCount;

            if (width < calWidth && stoneCount < calStoneCount) {
                width = calWidth;
                stoneCount = calStoneCount;

                ++result;
                break;
            }
        }

        calWidth = 0;
        calStoneCount = 0;

        while (stoneUseIndex < widths.length) {
            if (width <= calWidth && stoneCount < calStoneCount) {
                width = calWidth;
                stoneCount = calStoneCount;

                calWidth = 0;
                calStoneCount = 0;

                ++result;
            } else {
                int newWidth = widths[stoneUseIndex++];
                calWidth += newWidth;
                ++calStoneCount;
            }
        }

        if (width <= calWidth && stoneCount < calStoneCount) {
            ++result;
        }

        return result;
    }

    private static void quickSortRecursive(final int[] widths, int left, int right) {
        if (left >= right) {
            return;
        }

        int pivotValue = widths[right];
        int leftIndex = left;

        for (int i = left; i < right; ++i) {
            if (widths[i] < pivotValue) {
                int temp = widths[i];
                widths[i] = widths[leftIndex];
                widths[leftIndex++] = temp;
            }
        }

        {
            int temp = widths[right];
            widths[right] = widths[leftIndex];
            widths[leftIndex] = temp;
        }

        quickSortRecursive(widths, left, leftIndex - 1);
        quickSortRecursive(widths, leftIndex + 1, right);
    }
}