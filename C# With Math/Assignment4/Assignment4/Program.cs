﻿using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

namespace Assignment4
{
    public sealed class Program
    {
        public static void Main(string[] args)
        {
            const int ONED_SIGNAL_SIZE = 100;
            const int NOISE_POINTS_COUNT = 50;
            const string IMAGE_FILE_NAME = "earth.png";

            var test = SignalProcessor.GetGaussianFilter1D(0.5);

            #region 1D_GAUSSIAN_FILTER 
            double[] filter1D = SignalProcessor.GetGaussianFilter1D(0.5);

            assertArrayEqual(new double[]
            {
                0.107981933026376,
                0.797884560802865,
                0.107981933026376
            }, filter1D, 0.00001);

            filter1D = SignalProcessor.GetGaussianFilter1D(1);

            assertArrayEqual(new double[]
            {
                0.00443184841193801,
                0.0539909665131881,
                0.241970724519143,
                0.398942280401433,
                0.241970724519143,
                0.0539909665131881,
                0.00443184841193801
            }, filter1D, 0.00001);
            #endregion

            #region CONVOLVE_1D
            double[] signal = new double[] { 10, 50, 60, 10, 20, 40, 30 };
            filter1D = new double[] { 0.15, 0.3, 0.15 };

            double[] result1D = SignalProcessor.Convolve1D(signal, filter1D);

            assertArrayEqual(new double[] { 10.5, 25.5, 27, 15, 13.5, 19.5, 15 }, result1D, double.Epsilon);

            signal = getSampleSignal(ONED_SIGNAL_SIZE, NOISE_POINTS_COUNT);
            filter1D = SignalProcessor.GetGaussianFilter1D(1);
            result1D = SignalProcessor.Convolve1D(signal, filter1D);

            assertArrayEqual(new double[]
            {
                5.18195732093606, 8.71943468032427, 7.18114417455111, 1.30221509410243, -4.48695166631741, -7.51580569923451, -5.64864281142517, 1.72824032425041,
                6.16578067163261, 2.89565052495874, -3.66887098069569, -8.55153602111122, -9.12251408221575, -4.82981313726225, -0.606206343961805, -1.09814041003849,
                -3.87688027767521, -6.02057842200011, -3.44605455980997, 4.66572138848927, 12.106970334405, 13.1241314789191, 4.58362900995097, -4.1082384540118,
                -5.40998976878921, -0.802985516653998, 4.62648503616228, 5.76693179556434, 1.16292259971596, -6.54710685608176, -11.7396777500923, -8.30923595875789,
                0.833851702547281, 4.95322466274176, 1.67343691257021, -3.56125940379414, -6.2871329541262, -4.16408019183405, 1.39914256637364, 5.60543012686628,
                4.46665251338947, -0.966804507399002, -5.56058781341298, -5.06858341821125, -0.162556256679786, 3.95262594995233, 3.47648925619644, -0.442401138506631,
                -4.71503523445149, -4.84074736586553, 0.0659719953866885, 5.79007455987602, 9.58947913803615, 8.01831503348674, 0.132767344076205, -4.90773099773524,
                -3.35723091090915, 0.978494608768805, 4.73396278763368, 3.55247507134618, -1.87589428356562, -5.86149088414549, -4.50681013002347, 0.745401620018681,
                4.41631461470658, 3.56604624426051, 1.10275724333565, -1.22904916549125, -2.65128749094711, 0.0677470706442504, 4.58644760130055, 4.91463299040221,
                0.472451438712229, -3.73610222358059, -3.28925297851971, 1.72698433685436, 5.86317783584669, 6.60405472064588, 3.16265470351418, -2.6944565558917,
                -6.02997839981443, -3.8304296084418, 1.79239471863957, 5.40890763005355, 3.82649960567921, -1.06580609700469, -6.23863273617374, -7.37550566492535,
                -1.34806687930198, 4.99186890967147, 5.43803240336943, 0.616441108343297, -5.10700127862168, -7.41162140513133, -3.84862582941917, 4.3651987600132,
                8.51112885332533, 3.0204321094573, -4.78816515137937, -6.299528630311
            }, result1D, 0.00001);
            #endregion

            #region 2D_GAUSSIAN_FILTER
            double[,] filter2D = SignalProcessor.GetGaussianFilter2D(0.5);

            assertMatrixEqual(new double[3, 3]
            {
                { 0.0116600978601128, 0.0861571172073945, 0.0116600978601128 },
                { 0.0861571172073945, 0.636619772367581, 0.0861571172073945 },
                { 0.0116600978601128, 0.0861571172073945, 0.0116600978601128 }
            }, filter2D, 0.00001);

            filter2D = SignalProcessor.GetGaussianFilter2D(1);

            assertMatrixEqual(new double[7, 7]
            {
                { 1.96412803463974E-05, 0.000239279779200471, 0.00107237757119565, 0.00176805171185202, 0.00107237757119565, 0.000239279779200471, 1.96412803463974E-05 },
                { 0.000239279779200471, 0.00291502446502819, 0.0130642332846849, 0.0215392793018486, 0.0130642332846849, 0.00291502446502819,0.000239279779200471 },
                { 0.00107237757119565, 0.0130642332846849, 0.0585498315243192, 0.0965323526300539, 0.0585498315243192, 0.0130642332846849, 0.00107237757119565 },
                { 0.00176805171185202, 0.0215392793018486, 0.0965323526300539, 0.159154943091895, 0.0965323526300539, 0.0215392793018486, 0.00176805171185202 },
                { 0.00107237757119565, 0.0130642332846849, 0.0585498315243192, 0.0965323526300539, 0.0585498315243192, 0.0130642332846849, 0.00107237757119565 },
                { 0.000239279779200471, 0.00291502446502819, 0.0130642332846849,  0.0215392793018486, 0.0130642332846849, 0.00291502446502819, 0.000239279779200471 },
                { 1.96412803463974E-05, 0.000239279779200471, 0.00107237757119565, 0.00176805171185202, 0.00107237757119565, 0.000239279779200471, 1.96412803463974E-05 }
            }, filter2D, 0.00001);
            #endregion

            #region CONVOLVE_2D
            using (FileStream fs = File.OpenRead(IMAGE_FILE_NAME))
            using (FileStream fs2 = File.OpenRead("earth_shift_left_expected.png"))
            using (Bitmap image = new Bitmap(fs))
            using (Bitmap expected = new Bitmap(fs2))
            using (Bitmap newImage = SignalProcessor.ConvolveImage(image, new double[,] {
                    { 0, 0, 0 },
                    { 1, 0, 0 },
                    { 0, 0, 0 }
                }))
            {
                newImage.Save($"{Path.GetFileNameWithoutExtension(IMAGE_FILE_NAME)}_shift_left.png", ImageFormat.Png);
                assertBitmapEqual(expected, newImage, 0);
            }

            using (FileStream fs = File.OpenRead(IMAGE_FILE_NAME))
            using (FileStream fs2 = File.OpenRead("earth_box_expected.png"))
            using (Bitmap image = new Bitmap(fs))
            using (Bitmap expected = new Bitmap(fs2))
            using (Bitmap newImage = SignalProcessor.ConvolveImage(image, new double[,] {
                    { 1 / 9.0, 1 / 9.0, 1 / 9.0 },
                    { 1 / 9.0, 1 / 9.0, 1 / 9.0 },
                    { 1 / 9.0, 1 / 9.0, 1 / 9.0 }
                }))
            {
                newImage.Save($"{Path.GetFileNameWithoutExtension(IMAGE_FILE_NAME)}_box.png", ImageFormat.Png);
                assertBitmapEqual(expected, newImage, 1);
            }
          
            filter2D = SignalProcessor.GetGaussianFilter2D(1);
          
            using (FileStream fs = File.OpenRead(IMAGE_FILE_NAME))
            using (FileStream fs2 = File.OpenRead("earth_gaussian_expected.png"))
            using (Bitmap image = new Bitmap(fs))
            using (Bitmap expected = new Bitmap(fs2))
            using (Bitmap newImage = SignalProcessor.ConvolveImage(image, filter2D))
            {
                newImage.Save($"{Path.GetFileNameWithoutExtension(IMAGE_FILE_NAME)}_gaussian.png", ImageFormat.Png);
                assertBitmapEqual(expected, newImage, 1);
            }
            #endregion
        }

        private static void assertBitmapEqual(Bitmap expected, Bitmap actual, int epsilon)
        {
            Debug.Assert(expected.Width == actual.Width);
            Debug.Assert(expected.Height == actual.Height);

            for (int i = 0; i < expected.Width; ++i)
            {
                for (int j = 0; j < expected.Height; ++j)
                {
                    Color expectedColor = expected.GetPixel(i, j);
                    Color color = actual.GetPixel(i, j);

                    Debug.Assert(Math.Abs((int)expectedColor.R - (int)color.R) <= epsilon);
                    Debug.Assert(Math.Abs((int)expectedColor.G - (int)color.G) <= epsilon);
                    Debug.Assert(Math.Abs((int)expectedColor.B - (int)color.B) <= epsilon);
                }
            }
        }

        private static void assertMatrixEqual(double[,] expected, double[,] actual, double epsilon)
        {
            Debug.Assert(expected.GetLength(0) == actual.GetLength(0));
            Debug.Assert(expected.GetLength(1) == actual.GetLength(1));

            for (int i = 0; i < expected.GetLength(0); ++i)
            {
                for (int j = 0; j < expected.GetLength(1); ++j)
                {
                    Debug.Assert(Math.Abs(expected[i, j] - actual[i, j]) <= epsilon);
                }
            }
        }

        private static void assertArrayEqual(double[] expected, double[] actual, double epsilon)
        {
            Debug.Assert(expected.Length == actual.Length);

            for (int i = 0; i < expected.Length; ++i)
            {
                Debug.Assert(Math.Abs(expected[i] - actual[i]) <= epsilon);
            }
        }

        private static double[] getSampleSignal(int size, int noisePointsCount)
        {
            double[] signal = new double[size];

            Random random = new Random(10);

            for (int i = 0; i < signal.Length; ++i)
            {
                signal[i] = 10 * Math.Sin(i);
            }

            for (int i = 0; i < noisePointsCount; ++i)
            {
                int index = random.Next(0, size);
                signal[index] += random.Next(-10, 11);
            }

            return signal;
        }

        private static void printMatrix(double[,] matrix)
        {
            Console.WriteLine("---------------------------------");

            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                for (int j = 0; j < matrix.GetLength(1); j++)
                {
                    Console.Write("{0, -6}, ", matrix[i, j]);
                }

                Console.WriteLine();
            }

            Console.WriteLine("---------------------------------");
        }

        private static void printArray(double[] arry)
        {
            Console.WriteLine("----------------------");

            foreach (double d in arry)
            {
                Console.WriteLine($"{d},");
            }

            Console.WriteLine("----------------------");
        }
    }
}


//using System;
//using System.Drawing;
//
//namespace Assignment4
//{
//    public sealed class Program
//    {
//        public static void Main(string[] args)
//        {
//            Bitmap tempMap = new Bitmap(6, 5);
//
//            Console.WriteLine("입력값");
//            for (int i = 0; i < 5; i++)
//            {
//                for (int j = 0; j < 6; j++)
//                {
//                    Color tempMapColor = Color.FromArgb(i, j, i + j); // 증가하는 반복문 값으로 rgb값을 설정했습니다. 원하신다면 직접 값을 설정하세요
//                    tempMap.SetPixel(j, i, tempMapColor);
//                    Console.Write($"{{{tempMapColor.R:D3},{tempMapColor.G:D3},{tempMapColor.B:D3}}} ");
//                }
//                Console.WriteLine();
//            }
//
//            double[,] tempFilter = { { 0, 1, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };  // 원하는 필터를 사용하세요
//                                                                              // {{0,0,0},{0,1,0},{0,0,0} 값을 그대로 나오게 해주는 필터
//                                                                              // {{0,0,0},{0,0,0},{0,1,0}} 아래로 한 칸 이동
//                                                                              // {{0,1,0},{0,0,0},{0,0,0}} 위로 한 칸 이동
//
//            Console.WriteLine("\n필터");
//            for (int i = 0; i < tempFilter.GetLength(0); i++)
//            {
//                Console.Write("{ ");
//                for (int j = 0; j < tempFilter.GetLength(1); j++)
//                {
//                    Console.Write($"{tempFilter[i, j]}, ");
//                }
//                Console.WriteLine("}");
//            }
//
//            Bitmap result = SignalProcessor.ConvolveImage(tempMap, tempFilter);
//
//            Console.WriteLine("\n출력값");
//            for (int i = 0; i < 5; i++)
//            {
//                for (int j = 0; j < 6; j++)
//                {
//                    Color resultColor = result.GetPixel(j, i);
//                    Console.Write($"{{{resultColor.R:D3},{resultColor.G:D3},{resultColor.B:D3}}} ");
//                }
//                Console.WriteLine();
//            }
//        }
//    }
//}
