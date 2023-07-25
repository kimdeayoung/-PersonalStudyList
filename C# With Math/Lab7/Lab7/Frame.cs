using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7
{
    public class Frame
    {
        private EFeatureFlags mFeatureFlags;
        private uint mId;
        private string mName;

        public EFeatureFlags Features { get => mFeatureFlags; }
        public uint ID { get => mId; }
        public string Name { get => mName; }

        public Frame(uint id, string name)
        {
            mFeatureFlags = EFeatureFlags.Default;
            mId = id;
            mName = name;
        }

        public void ToggleFeatures(EFeatureFlags features)
        {
            mFeatureFlags ^= features;
        }

        public void TurnOnFeatures(EFeatureFlags features)
        {
            mFeatureFlags |= features;
        }

        public void TurnOffFeatures(EFeatureFlags features)
        {
            mFeatureFlags &= ~features;
        }

        public string GetIntersectKey()
        {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append(mId);
            stringBuilder.Append(",");
            stringBuilder.Append(mName);

            return stringBuilder.ToString();
        }
    }
}
