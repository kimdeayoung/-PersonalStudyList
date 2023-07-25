using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6
{
    public class Item
    {
        private EType mType;
        private double mWeight;
        private double mVolume;
        private bool mbIsToxicWaste;

        public Item(EType type, double weight, double volume, bool bToxicWaste)
        {
            mType = type;
            mWeight = weight;
            mVolume = volume;
            mbIsToxicWaste = bToxicWaste;
        }

        public EType Type { get => mType; }
        public double Weight { get => mWeight; }
        public double Volume { get => mVolume; }
        public bool IsToxicWaste { get => mbIsToxicWaste; }
    }
}
