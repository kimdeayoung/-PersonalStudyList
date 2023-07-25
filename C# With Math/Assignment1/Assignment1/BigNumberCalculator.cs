using System;
using System.Collections.Generic;
using System.Text;

namespace Assignment1
{
    public class BigNumberCalculator
    {
        const string BINARY_FIRST_LINE = "0b";
        const string HEX_FIRST_LINE = "0x";

        const int HEX_BIT_COUNT = 4;
        const int CHECK_UNIT = 4;

        int CalBitCount;
        EMode CalMode;

        public BigNumberCalculator(int bitCount, EMode mode)
        {
            CalBitCount = bitCount;
            CalMode = mode;
        }

        public static string ConvertNumToBinary(char num)
        {
            int hexValue = Convert.ToInt32(num);
            int convertValue = 0;

            switch (hexValue)
            {
                case 65:
                    convertValue = 10;
                    break;
                case 66:
                    convertValue = 11;
                    break;
                case 67:
                    convertValue = 12;
                    break;
                case 68:
                    convertValue = 13;
                    break;
                case 69:
                    convertValue = 14;
                    break;
                case 70:
                    convertValue = 15;
                    break;
                default:
                    convertValue = hexValue - '0';
                    break;
            }

            if (convertValue < 0 || convertValue > 15)
            {
                return null;
            }
            else
            {
                StringBuilder stringBuilder = new StringBuilder();

                for (int i = 0; convertValue > 0; ++i)
                {
                    stringBuilder.Insert(0, convertValue % 2);
                    convertValue /= 2;
                }

                while (stringBuilder.Length < 4)
                {
                    stringBuilder.Insert(0, 0);
                }

                return stringBuilder.ToString();
            }
        }

        public static string ConvertBinaryTextToNum(string binaryText)
        {
            int convertValue = 0;
            int[] addAbleValues = { 8, 4, 2, 1 };

            for (int i = binaryText.Length - 1; i >= 0; --i)
            {
                if (binaryText[i] == '1')
                {
                    convertValue += addAbleValues[i];
                }
            }

            if (convertValue >= 10)
            {
                switch (convertValue)
                {
                    case 10:
                        return "A";
                    case 11:
                        return "B";
                    case 12:
                        return "C";
                    case 13:
                        return "D";
                    case 14:
                        return "E";
                    case 15:
                        return "F";
                }
            }
            else
            {
                return convertValue.ToString();
            }

            return null;
        }

        public static bool IsOverThanValue(string binaryText, int compareValue)
        {
            int convertValue = 0;
            int[] addAbleValues = { 8, 4, 2, 1 };

            for (int i = binaryText.Length - 1; i >= 0; --i)
            {
                if (binaryText[i] == '1')
                {
                    convertValue += addAbleValues[i];
                }
            }

            if (convertValue >= compareValue)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static string CalculateAddBinary(string binaryNum1, string binaryNum2)
        {
            string higherNum = binaryNum1;
            if (binaryNum1.Length < binaryNum2.Length)
            {
                higherNum = binaryNum2;
            }

            StringBuilder stringBuilder = new StringBuilder();

            bool bIsNeedCarrying = false;
            for (int i = 0; i < higherNum.Length; ++i)
            {
                int oneNumCount = 0;
                if (bIsNeedCarrying == true)
                {
                    ++oneNumCount;
                    bIsNeedCarrying = false;
                }

                int num1Index = binaryNum1.Length - i - 1;
                if (num1Index >= 0)
                {
                    if (binaryNum1[num1Index] == '1')
                    {
                        ++oneNumCount;
                    }
                }
                int num2Index = binaryNum2.Length - i - 1;
                if (num2Index >= 0)
                {
                    if (binaryNum2[num2Index] == '1')
                    {
                        ++oneNumCount;
                    }
                }

                if (oneNumCount >= 2)
                {
                    bIsNeedCarrying = true;
                }
                stringBuilder.Insert(0, (oneNumCount % 2).ToString());
            }

            if (bIsNeedCarrying == true)
            {
                stringBuilder.Insert(0, '1');
            }

            return stringBuilder.ToString();
        }

        public static string CalculateSubtractBinary(string binaryNum1, string binaryNum2)
        {
            string higherNum = binaryNum1;
            if (binaryNum1.Length < binaryNum2.Length)
            {
                higherNum = binaryNum2;
            }

            StringBuilder stringBuilder = new StringBuilder();

            bool bIsNeedBorrowing = false;
            for (int i = 0; i < higherNum.Length; ++i)
            {
                int oneNumCount = 0;
                if (bIsNeedBorrowing == true)
                {
                    --oneNumCount;
                    bIsNeedBorrowing = false;
                }

                int num1Index = binaryNum1.Length - i - 1;
                if (num1Index >= 0)
                {
                    if (binaryNum1[num1Index] == '1')
                    {
                        ++oneNumCount;
                    }
                }

                int num2Index = binaryNum2.Length - i - 1;
                if (num2Index >= 0)
                {
                    if (binaryNum2[num2Index] == '1')
                    {
                        --oneNumCount;
                    }
                }

                if (oneNumCount < 0)
                {
                    bIsNeedBorrowing = true;
                }

                if (oneNumCount < 0)
                {
                    oneNumCount = -oneNumCount;
                }
                stringBuilder.Insert(0, (oneNumCount % 2).ToString());
            }

            return stringBuilder.ToString();
        }

        public static bool IsVaildBinary(string num)
        {
            if (num.Length <= 0)
            {
                return false;
            }

            int binaryTextIndex = num.IndexOf(BINARY_FIRST_LINE);
            if (binaryTextIndex == 0)
            {
                bool bIsLoopComplete = false;
                for (int i = BINARY_FIRST_LINE.Length; i < num.Length; ++i)
                {
                    switch (num[i])
                    {
                        case '0':
                        case '1':
                            break;
                        default:
                            return false;
                    }

                    bIsLoopComplete = true;
                }
                return bIsLoopComplete;
            }
            else
            {
                return false;
            }
        }

        public static bool IsVaildHex(string num)
        {
            if (num.Length <= 0)
            {
                return false;
            }

            int hexTextIndex = num.IndexOf(HEX_FIRST_LINE);
            if (hexTextIndex == 0)
            {
                bool bIsLoopComplete = false;
                for (int i = HEX_FIRST_LINE.Length; i < num.Length; ++i)
                {
                    string resultText = ConvertNumToBinary(num[i]);
                    if (resultText == null)
                    {
                        return false;
                    }

                    bIsLoopComplete = true;
                }

                if (bIsLoopComplete == true)
                {
                    return true;
                }

                return false;
            }
            else
            {
                return false;
            }
        }

        public static bool IsVaildDecimal(string num)
        {
            if (num.Length <= 0)
            {
                return false;
            }

            char firstChar = num[0];
            bool bIsMinus = firstChar == '-';

            if (firstChar == '0')
            {
                if (num.Length > 1)
                {
                    return false;
                }
            }

            int loopStartCount = 0;
            if (bIsMinus == true)
            {
                loopStartCount = 1;

                if (num.Length > loopStartCount)
                {
                    char value = num[loopStartCount];
                    if (value > (char)48 && value < (char)58)
                    {
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }

            for (int i = loopStartCount; i < num.Length; ++i)
            {
                char value = num[i];
                if (value >= (char)48 && value < (char)58)
                {
                }
                else
                {
                    return false;
                }
            }

            return true;
        }

        public static string GetOnesComplementOrNull(string num)
        {
            if (num == null)
            {
                return null;
            }

            int binaryTextIndex = num.IndexOf(BINARY_FIRST_LINE);

            if (binaryTextIndex <= -1 || binaryTextIndex > 0)
            {
                return null;
            }

            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.EnsureCapacity(num.Length + 1);

            for (int i = BINARY_FIRST_LINE.Length; i < num.Length; ++i)
            {
                switch (num[i])
                {
                    case (char)48:
                        stringBuilder.Append('1');
                        break;
                    case (char)49:
                        stringBuilder.Append('0');
                        break;
                    default:
                        return null;
                }
            }

            if (stringBuilder.Length > 0)
            {
                stringBuilder.Insert(0, BINARY_FIRST_LINE);
                return stringBuilder.ToString();
            }

            return null;
        }

        public static string GetTwosComplementOrNull(string num)
        {
            string onesComplementText = GetOnesComplementOrNull(num);
            if (onesComplementText == null)
            {
                return null;
            }
            else
            {
                StringBuilder stringBuilder = new StringBuilder();
                stringBuilder.EnsureCapacity(num.Length + 1);

                bool bIsConvertComplement = true;
                for (int i = onesComplementText.Length - 1; i >= BINARY_FIRST_LINE.Length; --i)
                {
                    char numText = onesComplementText[i];

                    if (bIsConvertComplement == true)
                    {
                        switch (numText)
                        {
                            case (char)48:
                                stringBuilder.Insert(0, '1');
                                bIsConvertComplement = false;
                                break;
                            case (char)49:
                                stringBuilder.Insert(0, '0');
                                break;
                            default:
                                bIsConvertComplement = false;
                                break;
                        }
                    }
                    else
                    {
                        stringBuilder.Insert(0, numText);
                    }
                }

                stringBuilder.Insert(0, BINARY_FIRST_LINE);
                return stringBuilder.ToString();
            }
        }

        public static string ToBinaryOrNull(string num)
        {
            if (num == null)
            {
                return null;
            }
            if (IsVaildBinary(num) == true)
            {
                return num;
            }
            else if (IsVaildHex(num) == true)
            {
                StringBuilder stringBuilder = new StringBuilder();
                for (int i = HEX_FIRST_LINE.Length; i < num.Length; ++i)
                {
                    string resultText = ConvertNumToBinary(num[i]);
                    stringBuilder.Append(resultText);
                }

                stringBuilder.Insert(0, BINARY_FIRST_LINE);
                return stringBuilder.ToString();
            }
            else if (IsVaildDecimal(num) == true)
            {
                bool bIsMinus = num[0] == '-';
                int loopStartIndex = 0;
                if (bIsMinus == true)
                {
                    loopStartIndex = 1;
                }

                List<char> binaryTexts = new List<char>();
                List<char> convertBinaryTexts = new List<char>();

                for (int i = loopStartIndex; i < num.Length; ++i)
                {
                    string binaryText = ConvertNumToBinary(num[i]);
                    if (binaryText == null)
                    {
                        return null;
                    }

                    for (int j = 0; j < binaryText.Length; ++j)
                    {
                        convertBinaryTexts.Add(binaryText[j]);
                    }
                }

                while (true)
                {
                    int lastIndex = convertBinaryTexts.Count - 1;
                    binaryTexts.Insert(0, convertBinaryTexts[lastIndex]);

                    convertBinaryTexts.RemoveAt(lastIndex);
                    convertBinaryTexts.Insert(0, '0');

                    int overCheckLoopCount = convertBinaryTexts.Count / CHECK_UNIT;

                    for (int j = 0; j < overCheckLoopCount; ++j)
                    {
                        int fluctuatingValueIndex = CHECK_UNIT * j;

                        StringBuilder stringBuilder = new StringBuilder();
                        for (int z = fluctuatingValueIndex; z < fluctuatingValueIndex + CHECK_UNIT; ++z)
                        {
                            stringBuilder.Append(convertBinaryTexts[z]);
                        }

                        string text = stringBuilder.ToString();
                        if (IsOverThanValue(text, 8) == true)
                        {
                            string result = CalculateSubtractBinary(text, "0011");

                            convertBinaryTexts.RemoveRange(fluctuatingValueIndex, result.Length);
                            convertBinaryTexts.InsertRange(fluctuatingValueIndex, result);
                        }
                    }

                    bool bIsloopEnd = true;
                    for (int i = 0; i < convertBinaryTexts.Count; ++i)
                    {
                        if (convertBinaryTexts[i] == '1')
                        {
                            bIsloopEnd = false;
                            break;
                        }
                    }

                    if (bIsloopEnd == true)
                    {
                        break;
                    }
                }

                StringBuilder resultStringBuilder = new StringBuilder();
                for (int i = 0; i < binaryTexts.Count; ++i)
                {
                    resultStringBuilder.Append(binaryTexts[i]);
                }

                if (bIsMinus == true)
                {
                    resultStringBuilder.Insert(0, BINARY_FIRST_LINE);
                    string binaryResult = GetTwosComplementOrNull(resultStringBuilder.ToString());
                    if (binaryResult[BINARY_FIRST_LINE.Length] == '0')
                    {
                        binaryResult = binaryResult.Insert(BINARY_FIRST_LINE.Length, "1");
                    }
                    return binaryResult;
                }
                else
                {
                    if (resultStringBuilder.Length <= 0 || resultStringBuilder[0] == '1')
                    {
                        resultStringBuilder.Insert(0, '0');
                    }
                    resultStringBuilder.Insert(0, BINARY_FIRST_LINE);
                    return resultStringBuilder.ToString();
                }
            }

            return null;
        }

        public static string ToHexOrNull(string num)
        {
            if (num == null)
            {
                return null;
            }
            if (IsVaildHex(num) == true)
            {
                return num;
            }

            string binaryText = ToBinaryOrNull(num);
            if (binaryText == null)
            {
                return null;
            }
            else
            {
                StringBuilder stringBuilder = new StringBuilder();
                StringBuilder convertStringBuilder = new StringBuilder();

                int divideBitCount = (binaryText.Length - BINARY_FIRST_LINE.Length) % HEX_BIT_COUNT;
                bool bIsMinus = false;

                bool bIsNeedCopyBit = true;
                if (divideBitCount != 0)
                {
                    if (binaryText[HEX_FIRST_LINE.Length] == '1')
                    {
                        int loopCount = binaryText.Length;
                        if (loopCount >= HEX_BIT_COUNT + HEX_FIRST_LINE.Length)
                        {
                            loopCount = HEX_BIT_COUNT + HEX_FIRST_LINE.Length;
                        }

                        bIsNeedCopyBit = false;
                        bIsMinus = true;
                        for (int i = HEX_FIRST_LINE.Length; i < loopCount; ++i)
                        {
                            if (binaryText[i] != '1')
                            {
                                bIsNeedCopyBit = true;
                                bIsMinus = false;
                                break;
                            }
                        }
                    }
                }

                if (bIsNeedCopyBit == true)
                {
                    StringBuilder bitCopyBuilder = new StringBuilder();
                    bitCopyBuilder.Append(binaryText);
                    int bitCopyCount = HEX_BIT_COUNT - divideBitCount;
                    if (bitCopyCount < HEX_BIT_COUNT)
                    {
                        for (int i = 0; i < bitCopyCount; ++i)
                        {
                            bitCopyBuilder.Insert(HEX_FIRST_LINE.Length, binaryText[BINARY_FIRST_LINE.Length]);
                        }
                        binaryText = bitCopyBuilder.ToString();
                    }
                }

                for (int i = binaryText.Length - 1; i >= BINARY_FIRST_LINE.Length; --i)
                {
                    convertStringBuilder.Insert(0, binaryText[i]);
                    if (convertStringBuilder.Length >= HEX_BIT_COUNT)
                    {
                        string result = ConvertBinaryTextToNum(convertStringBuilder.ToString());
                        stringBuilder.Insert(0, result);

                        convertStringBuilder.Clear();
                    }
                }

                if (bIsMinus == true)
                {
                    stringBuilder.Insert(0, 'F');
                }
                else
                {
                    int zeroCheckCount = 0;
                    int binaryTextIndex = num.IndexOf(BINARY_FIRST_LINE);
                    if (binaryTextIndex == 0)
                    {
                        zeroCheckCount = HEX_FIRST_LINE.Length;
                    }
                }
                stringBuilder.Insert(0, HEX_FIRST_LINE);
                return stringBuilder.ToString();
            }
        }

        public static string ToDecimalOrNull(string num)
        {
            if (num == null)
            {
                return null;
            }
            if (IsVaildDecimal(num) == true)
            {
                return num;
            }

            string binaryText = ToBinaryOrNull(num);
            if (binaryText == null)
            {
                return null;
            }
            else
            {
                List<char> binaryTexts = new List<char>();
                List<char> convertBinaryTexts = new List<char>();

                bool bIsMinus = false;
                int divideBitCount = (binaryText.Length - BINARY_FIRST_LINE.Length) % HEX_BIT_COUNT;
                if (binaryText[HEX_FIRST_LINE.Length] == '1')
                {
                    bIsMinus = true;
                    binaryText = GetTwosComplementOrNull(binaryText);
                }

                if (bIsMinus == false)
                {
                    StringBuilder bitCopyBuilder = new StringBuilder();
                    bitCopyBuilder.Append(binaryText);
                    int bitCopyCount = HEX_BIT_COUNT - divideBitCount;
                    if (bitCopyCount < HEX_BIT_COUNT)
                    {
                        for (int i = 0; i < bitCopyCount; ++i)
                        {
                            bitCopyBuilder.Insert(HEX_FIRST_LINE.Length, '0');
                        }
                        binaryText = bitCopyBuilder.ToString();
                    }
                }

                for (int i = BINARY_FIRST_LINE.Length; i < binaryText.Length; ++i)
                {
                    binaryTexts.Add(binaryText[i]);

                    int additionalConvertTextCount = CHECK_UNIT - (binaryTexts.Count % CHECK_UNIT);
                    for (int j = 0; j < additionalConvertTextCount; ++j)
                    {
                        convertBinaryTexts.Add('0');
                    }
                    convertBinaryTexts.AddRange(binaryTexts);

                    bool bIsCopyAllConvertText = false;
                    if (i < binaryText.Length - 1)
                    {
                        int overCheckLoopCount = convertBinaryTexts.Count / CHECK_UNIT;

                        for (int j = 0; j < overCheckLoopCount; ++j)
                        {
                            int fluctuatingValueIndex = CHECK_UNIT * j;

                            StringBuilder stringBuilder = new StringBuilder();
                            for (int z = fluctuatingValueIndex; z < fluctuatingValueIndex + CHECK_UNIT; ++z)
                            {
                                stringBuilder.Append(convertBinaryTexts[z]);
                            }

                            string text = stringBuilder.ToString();
                            if (IsOverThanValue(text, 5) == true)
                            {
                                string result = CalculateAddBinary(text, "0011");

                                convertBinaryTexts.RemoveRange(fluctuatingValueIndex, result.Length);
                                convertBinaryTexts.InsertRange(fluctuatingValueIndex, result);

                                if (fluctuatingValueIndex == 0)
                                {
                                    bIsCopyAllConvertText = true;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (additionalConvertTextCount >= CHECK_UNIT)
                        {
                            bIsCopyAllConvertText = false;
                        }
                        else
                        {
                            bIsCopyAllConvertText = true;
                        }
                    }

                    if (bIsCopyAllConvertText == true)
                    {
                        binaryTexts = convertBinaryTexts.GetRange(0, convertBinaryTexts.Count);
                    }
                    else
                    {
                        binaryTexts = convertBinaryTexts.GetRange(additionalConvertTextCount, convertBinaryTexts.Count - additionalConvertTextCount);
                    }

                    convertBinaryTexts.Clear();
                }

                bool bIsZeroOnly = true;
                for (int i = 0; i < binaryTexts.Count; ++i)
                {
                    if (binaryTexts[i] != '0')
                    {
                        bIsZeroOnly = false;
                        break;
                    }
                }
                if (bIsZeroOnly == true)
                {
                    binaryTexts.Clear();
                    for (int i = 0; i < HEX_BIT_COUNT; ++i)
                    {
                        binaryTexts.Add('0');
                    }
                }

                {
                    StringBuilder stringBuilder = new StringBuilder();
                    if (bIsMinus == true)
                    {
                        stringBuilder.Append('-');
                    }

                    int loopCount = binaryTexts.Count / CHECK_UNIT;
                    bool bIsNotZeroStart = false;
                    for (int i = 0; i < loopCount; ++i)
                    {
                        int loopIndex = CHECK_UNIT * i;
                        StringBuilder convertStringBuilder = new StringBuilder();
                        for (int j = loopIndex; j < loopIndex + CHECK_UNIT; ++j)
                        {
                            convertStringBuilder.Append(binaryTexts[j]);
                        }

                        string result = ConvertBinaryTextToNum(convertStringBuilder.ToString());
                        if (bIsNotZeroStart == false)
                        {
                            if (result != "0")
                            {
                                bIsNotZeroStart = true;
                            }
                        }

                        if (bIsNotZeroStart == true || loopCount <= 1)
                        {
                            stringBuilder.Append(result);
                        }
                    }

                    return stringBuilder.ToString();
                }
            }
        }

        public string ConvertingForCalculate(string num)
        {
            string numBinaryText = ToBinaryOrNull(num);
            if (numBinaryText == null)
            {
                return null;
            }
            else if (numBinaryText.Length - BINARY_FIRST_LINE.Length > CalBitCount)
            {
                return null;
            }

            if (IsVaildDecimal(num) == true)
            {
                bool bIsMinus = num[0] == '-';
                if (bIsMinus == true)
                {
                    numBinaryText = GetFillNotEnoughBitCount(numBinaryText, CalBitCount, '1');
                }
                else
                {
                    numBinaryText = GetFillNotEnoughBitCount(numBinaryText, CalBitCount, '0');
                }
            }

            if (IsSameConvertResult(num, numBinaryText) == false)
            {
                return null;
            }

            if (IsVaildBinary(num) == true)
            {
                bool bIsMinus = num[BINARY_FIRST_LINE.Length] == '1';
                if (bIsMinus == true)
                {
                    numBinaryText = GetFillNotEnoughBitCount(numBinaryText, CalBitCount, '1');
                }
                else
                {
                    numBinaryText = GetFillNotEnoughBitCount(numBinaryText, CalBitCount, '0');
                }
            }
            else if (IsVaildHex(num) == true)
            {
                bool bIsMinus = ConvertNumToBinary(num[BINARY_FIRST_LINE.Length])[0] == '1';
                if (bIsMinus == true)
                {
                    numBinaryText = GetFillNotEnoughBitCount(numBinaryText, CalBitCount, '1');
                }
                else
                {
                    numBinaryText = GetFillNotEnoughBitCount(numBinaryText, CalBitCount, '0');
                }
            }

            return numBinaryText;
        }

        public string GetFillNotEnoughBitCount(string binaryText, int needBitCount, char customChar = (char)0)
        {
            if (binaryText.Length - BINARY_FIRST_LINE.Length < needBitCount)
            {
                int addZeroLoopCount = needBitCount - (binaryText.Length - BINARY_FIRST_LINE.Length);
                StringBuilder stringBuilder = new StringBuilder();
                stringBuilder.Append(binaryText);

                int insertIndex = BINARY_FIRST_LINE.Length + 1;
                char fillChar = stringBuilder[BINARY_FIRST_LINE.Length];
                if (customChar != (char)0)
                {
                    insertIndex = BINARY_FIRST_LINE.Length;
                    fillChar = customChar;
                }

                for (int i = 0; i < addZeroLoopCount; ++i)
                {
                    stringBuilder.Insert(insertIndex, fillChar);
                }

                return stringBuilder.ToString();
            }

            return binaryText;
        }

        public bool IsSameConvertResult(string num, string convertResult)
        {
            if (IsVaildBinary(num) == true)
            {
                if (num != ToBinaryOrNull(convertResult))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            else if (IsVaildHex(num) == true)
            {
                if (num != ToHexOrNull(convertResult))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            else if (IsVaildDecimal(num) == true)
            {
                if (num != ToDecimalOrNull(convertResult))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            return false;
        }
        public string AddOrNull(string num1, string num2, out bool bOverflow)
        {
            bOverflow = false;

            bool bIsPositiveNum1 = false;
            string num1BinaryText = ConvertingForCalculate(num1);
            if (num1BinaryText == null)
            {
                return null;
            }
            if (num1BinaryText[BINARY_FIRST_LINE.Length] == '0')
            {
                bIsPositiveNum1 = true;
            }

            bool bIsPositiveNum2 = false;
            string num2BinaryText = ConvertingForCalculate(num2);
            if (num2BinaryText == null)
            {
                return null;
            }
            if (num2BinaryText[BINARY_FIRST_LINE.Length] == '0')
            {
                bIsPositiveNum2 = true;
            }

            string calResult = CalculateAddBinary(num1BinaryText, num2BinaryText);
            calResult = calResult.Remove(0, calResult.Length - CalBitCount);

            bool bIsAllZeroBit = true;
            for (int i = 0; i < calResult.Length; ++i)
            {
                if (calResult[i] == '1')
                {
                    bIsAllZeroBit = false;
                    break;
                }
            }

            bool bResultSignPositive = false;
            if (calResult[0] == '0')
            {
                bResultSignPositive = true;
            }

            if (bIsPositiveNum1 & bIsPositiveNum2)
            {
                bOverflow = !bResultSignPositive;
            }
            else if (bIsPositiveNum1 | bIsPositiveNum2)
            {
            }
            else
            {
                bOverflow = bResultSignPositive;
            }

            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append(BINARY_FIRST_LINE);
            stringBuilder.Append(calResult);
            string result = stringBuilder.ToString();

            switch (CalMode)
            {
                case EMode.Binary:
                    return result;
                case EMode.Decimal:
                    string resultText = ToDecimalOrNull(result);
                    if (bIsAllZeroBit == true)
                    {
                        resultText = "0";
                    }
                    return resultText;
            }

            return null;
        }

        public string SubtractOrNull(string num1, string num2, out bool bOverflow)
        {
            bOverflow = false;

            bool bIsPositiveNum1 = false;
            string num1BinaryText = ConvertingForCalculate(num1);
            if (num1BinaryText == null)
            {
                return null;
            }
            if (num1BinaryText[BINARY_FIRST_LINE.Length] == '0')
            {
                bIsPositiveNum1 = true;
            }

            bool bIsPositiveNum2 = false;
            string num2BinaryText = ConvertingForCalculate(num2);
            if (num2BinaryText == null)
            {
                return null;
            }
            num2BinaryText = GetTwosComplementOrNull(num2BinaryText);
            if (num2BinaryText[BINARY_FIRST_LINE.Length] == '0')
            {
                bIsPositiveNum2 = true;
            }

            string calResult = CalculateAddBinary(num1BinaryText, num2BinaryText);
            calResult = calResult.Remove(0, calResult.Length - CalBitCount);

            bool bIsAllZeroBit = true;
            for (int i = 0; i < calResult.Length; ++i)
            {
                if (calResult[i] == '1')
                {
                    bIsAllZeroBit = false;
                    break;
                }
            }

            bool bResultSignPositive = false;
            if (calResult[0] == '0')
            {
                bResultSignPositive = true;
            }

            if (bIsPositiveNum1 & bIsPositiveNum2)
            {
                bOverflow = !bResultSignPositive;
            }
            else if (bIsPositiveNum1 | bIsPositiveNum2)
            {
            }
            else
            {
                bOverflow = bResultSignPositive;
            }

            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append(BINARY_FIRST_LINE);
            stringBuilder.Append(calResult);
            string result = stringBuilder.ToString();

            switch (CalMode)
            {
                case EMode.Binary:
                    return result;
                case EMode.Decimal:
                    string resultText = ToDecimalOrNull(result);
                    if (bIsAllZeroBit == true)
                    {
                        resultText = "0";
                    }
                    return resultText;
            }

            return null;
        }
    }
}