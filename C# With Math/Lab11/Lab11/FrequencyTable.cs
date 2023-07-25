using System;
using System.Collections.Generic;

namespace Lab11
{
    public static class FrequencyTable
    {
        public static List<Tuple<Tuple<int, int>, int>> GetFrequencyTable(int[] data, int maxBinCount)
        {
            int minValue = int.MaxValue;
            int maxValue = int.MinValue;

            List<int> copyedDatas = new List<int>();
            for (int i = 0; i < data.Length; ++i)
            {
                int value = data[i];
                copyedDatas.Add(value);

                if (value < minValue)
                {
                    minValue = value;
                }
                if (maxValue < value)
                {
                    maxValue = value;
                }
            }

            int intervalRange = (maxValue - minValue) / maxBinCount;
            int calculateBinCount = maxBinCount;

            if (intervalRange <= 0)
            {
                intervalRange = 1;
            }
            else
            {
                while (true)
                {
                    int maxInterval = minValue + intervalRange * maxBinCount;

                    if (maxValue >= maxInterval)
                    {
                        ++intervalRange;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            List<Tuple<Tuple<int, int>, int>> resultTables = new List<Tuple<Tuple<int, int>, int>>();
            for (int i = 0; i < calculateBinCount; ++i)
            {
                int minInterval = minValue + intervalRange * i;
                int maxInterval = minValue + intervalRange * (i + 1);

                int count = 0;
                for (int j = 0; j < copyedDatas.Count;)
                {
                    int value = copyedDatas[j];
                    if (value >= minInterval && value < maxInterval)
                    {
                        ++count;
                        copyedDatas.RemoveAt(j);
                    }
                    else
                    {
                        ++j;
                    }
                }
                resultTables.Add(new Tuple<Tuple<int, int>, int>(new Tuple<int, int>(minInterval, maxInterval), count));

                if (copyedDatas.Count <= 0)
                {
                    break;
                }
            }

            return resultTables;
        }
    }
}