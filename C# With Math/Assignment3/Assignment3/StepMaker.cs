using System;
using System.Collections.Generic;

namespace Assignment3
{
    public static class StepMaker
    {
        public static List<int> MakeSteps(int[] steps, INoise noise)
        {
            List<int> result = new List<int>();

            for (int i = 0; i < steps.Length - 1; ++i)
            {
                MakeStepRecursive(result, steps[i], steps[i + 1], 0, noise);
            }
            result.Add(steps[steps.Length - 1]);

            return result;
        }

        public static void MakeStepRecursive(List<int> result, int value1, int value2, int depth, INoise noise)
        {
            bool bIsNeedAddStep = Math.Abs(value2 - value1) > 10;

            if (bIsNeedAddStep == true)
            {
                int percent = 20;

                List<int> newStepValues = new List<int>();
                newStepValues.Add(value1);
                for (int i = 1; i <= 4; ++i)
                {
                    int noiseValue = noise.GetNext(depth);
                    int lerpValue = GetLerp(value1, value2, percent * i) + noiseValue;
                    newStepValues.Add(lerpValue);
                }
                newStepValues.Add(value2);

                for (int i = 0; i < 5; ++i)
                {
                    MakeStepRecursive(result, newStepValues[i], newStepValues[i + 1], depth + 1, noise);
                }
            }
            else
            {
                result.Add(value1);
                return;
            }
        }

        public static int GetLerp(int value1, int value2, int percent)
        {
            float result = ((100 - percent) * value1 + percent * value2);
            result /= 100;
            return (int)result;
        }
    }
}
