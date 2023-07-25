using System;
using System.Drawing;

namespace Assignment4
{
    public static class SignalProcessor
    {
        public static double[] GetGaussianFilter1D(double sigma)
        {
            int filterSize = (int)(Math.Ceiling(sigma * 6.0));
            if (filterSize % 2 == 0)
            {
                ++filterSize;
            }
            double[] result = new double[filterSize];

            int midIndex = filterSize / 2;
            double standardValue = 1.0 / (sigma * Math.Sqrt(2 * Math.PI));
            result[midIndex] = standardValue;

            for (int i = 1; i <= midIndex; ++i)
            {
                double calculatedoffsetValue = standardValue * Math.Exp(-(i * i) / (2 * sigma * sigma));
                result[midIndex - i] = calculatedoffsetValue;
                result[midIndex + i] = calculatedoffsetValue;
            }

            return result;
        }

        public static double[] Convolve1D(double[] signal, double[] filter)
        {
            double[] result = new double[signal.Length];

            for (int i = 0; i < signal.Length; ++i)
            {
                double convolveValue = 0;

                int midIndex = filter.Length / 2;

                convolveValue += signal[i] * filter[midIndex];
                for (int j = 1; j <= midIndex; ++j)
                {
                    int leftIndex = i - j;
                    if (leftIndex >= 0)
                    {
                        convolveValue += signal[leftIndex] * filter[midIndex + j];
                    }

                    int rightIndex = i + j;
                    if (rightIndex < signal.Length)
                    {
                        convolveValue += signal[rightIndex] * filter[midIndex - j];
                    }
                }

                result[i] = convolveValue;
            }

            return result;
        }

        public static double[,] GetGaussianFilter2D(double sigma)
        {
            int filterSize = (int)(Math.Ceiling(sigma * 6.0));
            if (filterSize % 2 == 0)
            {
                ++filterSize;
            }
            double[,] result = new double[filterSize, filterSize];

            int midIndex = filterSize / 2;
            double standardValue = 1.0 / (2 * Math.PI * sigma * sigma);

            for (int i = 0; i <= midIndex; ++i)
            {
                double value = standardValue * Math.Exp(-((i * i) + (0 * 0)) / (2 * sigma * sigma));
                result[midIndex - i, midIndex] = value;
                result[midIndex + i, midIndex] = value;
                for (int j = 1; j <= midIndex; ++j)
                {
                    value = standardValue * Math.Exp(-((i * i) + (j * j)) / (2 * sigma * sigma));
                    result[midIndex - i, midIndex - j] = value;
                    result[midIndex - i, midIndex + j] = value;

                    result[midIndex + i, midIndex - j] = value;
                    result[midIndex + i, midIndex + j] = value;
                }
            }
            return result;
        }

        public static Bitmap ConvolveImage(Bitmap bitmap, double[,] filter)
        {
            int width = bitmap.Width;
            int height = bitmap.Height;

            Color[,] bitmapColors = new Color[height, width];

            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    bitmapColors[i, j] = bitmap.GetPixel(j, i);
                }
            }

            int filterRank = filter.Rank;
            int[] arrLength = new int[filterRank];
            for (int i = 0; i < filterRank; ++i)
            {
                arrLength[i] = filter.GetLength(i);
            }

            Tuple<int, int> filterLength = new Tuple<int, int>(arrLength[0], arrLength[1]);
            double[,] convolveFillter = new double[filterLength.Item1, filterLength.Item2];

            for (int i = 0; i < filterLength.Item1; ++i)
            {
                for (int j = 0; j < filterLength.Item2; ++j)
                {
                    convolveFillter[filterLength.Item1 - 1 - i, filterLength.Item2 - 1 - j] = filter[i, j];
                }
            }
            Bitmap resultBitmap = new Bitmap(width, height);
            Tuple<int, int> signalValueLength = new Tuple<int, int>(height, width);
            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    resultBitmap.SetPixel(j, i, Convolve(bitmapColors, signalValueLength, convolveFillter, filterLength, new Tuple<int, int>(i, j)));
                }
            }
            return resultBitmap;
        }
        //signalValueLength(y,x),   filterLength(y,x),   pixelIndex(y, x)
        static Color Convolve(Color[,] signalValues, Tuple<int, int> signalValueLength, double[,] filter, Tuple<int, int> filterLength, Tuple<int, int> pixelIndex)
        {
            int standardIndexX = -filterLength.Item2 / 2;
            int standardIndexY = -filterLength.Item1 / 2;

            double calculateR = 0;
            double calculateG = 0;
            double calculateB = 0;

            for (int i = 0; i < filterLength.Item1; ++i)//y
            {
                int indexY = pixelIndex.Item1 + i + standardIndexY;

                if (indexY >= 0 && indexY < signalValueLength.Item1)
                {
                    for (int j = 0; j < filterLength.Item2; ++j)//x
                    {
                        int indexX = pixelIndex.Item2 + j + standardIndexX;

                        if (indexX >= 0 && indexX < signalValueLength.Item2)
                        {
                            Color signalValue = signalValues[indexY, indexX];
                            double filterValue = filter[i, j];

                            calculateR += signalValue.R * filterValue;
                            calculateG += signalValue.G * filterValue;
                            calculateB += signalValue.B * filterValue;
                        }
                    }
                }
            }

            byte resultR = 0;
            if (calculateR > byte.MaxValue)
            {
                calculateR = byte.MaxValue;
            }
            else if (calculateR < byte.MinValue)
            {
                calculateR = byte.MinValue;
            }
            resultR = (byte)Math.Truncate(calculateR);

            byte resultG = 0;
            if (calculateG > byte.MaxValue)
            {
                calculateG = byte.MaxValue;
            }
            else if (calculateG < byte.MinValue)
            {
                calculateG = byte.MinValue;
            }
            resultG = (byte)Math.Truncate(calculateG);

            byte resultB = 0;
            if (calculateB > byte.MaxValue)
            {
                calculateB = byte.MaxValue;
            }
            else if (calculateB < byte.MinValue)
            {
                calculateB = byte.MinValue;
            }
            resultB = (byte)Math.Truncate(calculateB);

            Color midPixelValue = signalValues[pixelIndex.Item1, pixelIndex.Item2];
            Color result = Color.FromArgb(midPixelValue.A, resultR, resultG, resultB);
            return result;
        }
    }
}
