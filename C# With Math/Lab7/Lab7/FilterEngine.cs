using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7
{
    public static class FilterEngine
    {
        public static List<Frame> FilterFrames(List<Frame> frames, EFeatureFlags features)
        {
            List<Frame> result = new List<Frame>();
            for (int i = 0; i < frames.Count; ++i)
            {
                EFeatureFlags featureFlags = frames[i].Features & features;

                if (featureFlags != EFeatureFlags.Default)
                {
                    result.Add(frames[i]);
                }
            }

            return result;
        }

        public static List<Frame> FilterOutFrames(List<Frame> frames, EFeatureFlags features)
        {
            List<Frame> result = new List<Frame>();
            for (int i = 0; i < frames.Count; ++i)
            {
                EFeatureFlags featureFlags = frames[i].Features & features;

                if (featureFlags == EFeatureFlags.Default)
                {
                    result.Add(frames[i]);
                }
            }

            return result;
        }

        public static List<Frame> Intersect(List<Frame> frames1, List<Frame> frames2)
        {
            List<Frame> result = new List<Frame>();

            List<Frame> copyedFrames = new List<Frame>();
            for (int i = 0; i < frames2.Count; ++i)
            {
                copyedFrames.Add(frames2[i]);
            }

            for (int i = 0; i < frames1.Count; ++i)
            {
                string frame1IntersectKey = frames1[i].GetIntersectKey();
                bool bIsAdded = false;
                for (int j = 0; j < copyedFrames.Count;)
                {
                    bool bIsNeedRemoved = false;
                    if (frame1IntersectKey.Equals(copyedFrames[j].GetIntersectKey()) == true)
                    {
                        if (bIsAdded == false)
                        {
                            result.Add(frames1[i]);
                            bIsAdded = true;
                        }

                        bIsNeedRemoved = true;
                    }

                    if (bIsNeedRemoved == true)
                    {
                        copyedFrames.RemoveAt(j);
                    }
                    else
                    {
                        ++j;
                    }
                }
            }

            return result;
        }

        public static List<int> GetSortKeys(List<Frame> frames, List<EFeatureFlags> features)
        {
            List<int> result = new List<int>();
            List<int> additionalSortValues = new List<int>();

            foreach (int i in Enum.GetValues(typeof(EFeatureFlags)))
            {
                additionalSortValues.Insert(0, i);
            }

            for (int i = 0; i < frames.Count; ++i)
            {
                result.Add(0);
            }

            for (int i = 0; i < features.Count; ++i)
            {
                EFeatureFlags featureFlags = features[i];

                for (int j = 0; j < frames.Count; ++j)
                {
                    EFeatureFlags compareResult = frames[j].Features & featureFlags;
                    if (compareResult == featureFlags)
                    {
                        result[j] += additionalSortValues[i];
                    }
                }
            }

            return result;
        }
    }
}
