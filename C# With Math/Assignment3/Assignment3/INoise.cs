using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment3
{
    public interface INoise
    {
        int GetNext(int level);
    }

    public sealed class ZeroNoise : INoise
    {
        public int GetNext(int level)
        {
            return 0;
        }
    }

    public sealed class ConstantNoise : INoise
    {
        public int GetNext(int level)
        {
            return 1;
        }
    }

    public sealed class LevelNoise : INoise
    {
        public int GetNext(int level)
        {
            return level;
        }
    }

    public sealed class SineNoise : INoise
    {
        private const double BASE_SAMPLING_WIDTH = Math.PI / 4;
        private double mX = -BASE_SAMPLING_WIDTH;

        public int GetNext(int level)
        {
            mX += BASE_SAMPLING_WIDTH / Math.Pow(2, level);
            return (int)(5 * Math.Sin(mX));
        }
    }

    public sealed class CosineNoise : INoise
    {
        private const double BASE_SAMPLING_WIDTH = Math.PI / 4;
        private double mX = -BASE_SAMPLING_WIDTH;

        public int GetNext(int level)
        {
            mX += BASE_SAMPLING_WIDTH / Math.Pow(2, level);
            return (int)(5 * Math.Cos(mX));
        }
    }
}
