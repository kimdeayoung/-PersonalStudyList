using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab8
{
    public class Matrix
    {
        public static int DotProduct(int[] v1, int[] v2)
        {
            int result = 0;

            for (int i = 0; i < v1.Length; ++i)
            {
                result += v1[i] * v2[i];
            }
            return result;
        }

        public static Tuple<int, int> GetMatrixLengthOrNull(int[,] matrix)//<int>(row, column)
        {
            int length = matrix.Rank;

            int[] matLength = new int[length];
            for (int i = 0; i < length; ++i)
            {
                matLength[i] = matrix.GetLength(i);
            }

            if (matLength.Length > 1)
            {
                return new Tuple<int, int>(matLength[0], matLength[1]);
            }
            else
            {
                return null;
            }
        }

        public static int[,] Transpose(int[,] matrix)
        {
            Tuple<int, int> matLength = GetMatrixLengthOrNull(matrix);
            int[,] result = new int[matLength.Item2, matLength.Item1];

            for (int i = 0; i < matLength.Item1; ++i)
            {
                for (int j = 0; j < matLength.Item2; ++j)
                {
                    result[j, i] = matrix[i, j];
                }
            }

            return result;
        }

        public static int[,] GetIdentityMatrix(int size)
        {
            int[,] result = new int[size, size];

            for (int i = 0; i < size; ++i)
            {
                result[i, i] = 1;
            }

            return result;
        }

        public static int[] GetRowOrNull(int[,] matrix, int row)
        {
            Tuple<int, int> matLength = GetMatrixLengthOrNull(matrix);

            if (matLength.Item1 > row)
            {
                int[] result = new int[matLength.Item2];

                for (int i = 0; i < matLength.Item2; ++i)
                {
                    result[i] = matrix[row, i];
                }

                return result;
            }

            return null;
        }

        public static int[] GetColumnOrNull(int[,] matrix, int col)
        {
            Tuple<int, int> matLength = GetMatrixLengthOrNull(matrix);

            if (matLength.Item2 > col)
            {
                int[] result = new int[matLength.Item1];

                for (int i = 0; i < matLength.Item1; ++i)
                {
                    result[i] = matrix[i, col];
                }

                return result;
            }

            return null;
        }

        public static int[] MultiplyMatrixVectorOrNull(int[,] matrix, int[] vector)
        {
            Tuple<int, int> matLength = GetMatrixLengthOrNull(matrix);

            if (matLength.Item2 == vector.Length)
            {
                int[] result = new int[matLength.Item1];
                
                for (int i = 0; i < matLength.Item1; ++i)
                {
                    int[] rows = GetRowOrNull(matrix, i);
                    if (rows != null)
                    {
                        result[i] = DotProduct(rows, vector);
                    }
                }

                return result;
            }
            return null;
        }

        public static int[] MultiplyVectorMatrixOrNull(int[] vector, int[,] matrix)
        {
            Tuple<int, int> matLength = GetMatrixLengthOrNull(matrix);

            if (matLength.Item1 == vector.Length)
            {
                int[] result = new int[matLength.Item2];

                for (int i = 0; i < matLength.Item2; ++i)
                {
                    int[] columns = GetColumnOrNull(matrix, i);
                    if (columns != null)
                    {
                        result[i] = DotProduct(columns, vector);
                    }
                }

                return result;
            }

            return null;
        }

        public static int[,] MultiplyOrNull(int[,] multiplicandMatrix, int[,] multiplierMatrix)
        {
            Tuple<int, int> multiplierLength = GetMatrixLengthOrNull(multiplierMatrix);//연산 행렬
            Tuple<int, int> multiplicandLength = GetMatrixLengthOrNull(multiplicandMatrix);//피연산 행렬

            bool bIsCalAble = false;
            if (multiplierLength.Item1 == multiplicandLength.Item2)
            {
                bIsCalAble = true;
            }

            if (bIsCalAble == true)
            {
                int[,] result = new int[multiplicandLength.Item1, multiplierLength.Item2];

                for (int i = 0; i < multiplicandLength.Item1; ++i)
                {
                    int[] rows = GetRowOrNull(multiplicandMatrix, i);

                    for (int j = 0; j < multiplierLength.Item2; ++j)
                    {
                        int[] columns = GetColumnOrNull(multiplierMatrix, j);
                        result[i, j] = DotProduct(rows, columns);
                    }
                }

                return result;
            }

            return null;
        }
    }
}
