package academy.pocu.comp3500.lab9;

import academy.pocu.comp3500.lab9.data.VideoClip;

public class CodingMan {
    public static int findMinClipsCount(final VideoClip[] clips, int time) {
        if (clips == null || time < 0) {
            return -1;
        }
        quickSortClipRecursive(clips, 0, clips.length - 1);

        int clipCount = 0;
        int endTime = 0;
        int result = Integer.MAX_VALUE;

        for (int i = 0; i < clips.length; ++i) {
            VideoClip firstClip = clips[i];
            if (firstClip.getStartTime() > 0) {
                break;
            }

            clipCount = 1;
            endTime = firstClip.getEndTime();
            if (endTime >= time) {
                return clipCount;
            }

            VideoClip insertionClip = null;

            for (int j = i + 1; j < clips.length; ++j) {
                VideoClip clip = clips[j];

                if (insertionClip == null) {
                    insertionClip = clip;
                    continue;
                }

                if (clip.getStartTime() <= endTime) {
                    insertionClip = insertionClip.getEndTime() > clip.getEndTime() ? insertionClip : clip;
                } else {
                    if (insertionClip.getStartTime() > endTime) {
                        break;
                    }

                    ++clipCount;
                    endTime = insertionClip.getEndTime();
                    if (endTime >= time) {
                        if (result > clipCount) {
                            result = clipCount;
                        }
                        insertionClip = null;
                        break;
                    }

                    insertionClip = clip;
                }
            }

            if (insertionClip != null) {
                if (insertionClip.getStartTime() <= endTime && insertionClip.getEndTime() >= time) {
                    if (result > ++clipCount) {
                        result = clipCount;
                    }
                }
            }
        }

        if (result != Integer.MAX_VALUE) {
            return result;
        }

        return -1;
    }

    private static void quickSortClipRecursive(final VideoClip[] clips, int left, int right) {
        if (left >= right) {
            return;
        }

        int pivotValue = clips[right].getStartTime();
        int leftIndex = left;

        for (int i = left; i < right; ++i) {
            if (clips[i].getStartTime() < pivotValue) {
                VideoClip temp = clips[i];
                clips[i] = clips[leftIndex];
                clips[leftIndex++] = temp;
            } else if (clips[i].getStartTime() == pivotValue) {
                if (clips[i].getEndTime() > clips[right].getEndTime()) {
                    VideoClip temp = clips[i];
                    clips[i] = clips[leftIndex];
                    clips[leftIndex++] = temp;
                }
            }
        }

        {
            VideoClip temp = clips[right];
            clips[right] = clips[leftIndex];
            clips[leftIndex] = temp;
        }

        quickSortClipRecursive(clips, left, leftIndex - 1);
        quickSortClipRecursive(clips, leftIndex + 1, right);
    }
}
