package academy.pocu.comp3500.lab5;

import java.math.BigInteger;

public class KeyGenerator {

    public static boolean isPrime(final BigInteger number) {
        int[] checkValues = {2, 3};

        for (int i = 0; i < checkValues.length; ++i) {
            if (!millerAlgorithm(number, checkValues[i])) {
                return false;
            }
        }

        return true;
    }

    private static boolean millerAlgorithm(BigInteger number, int k) {
        BigInteger zero = new BigInteger("0");
        BigInteger one = new BigInteger("1");
        BigInteger two = new BigInteger("2");

        if (number.compareTo(two) == -1) {
            return false;
        }

        BigInteger bigIntegerK = new BigInteger(Integer.toString(k));
        if (bigIntegerK.remainder(number).compareTo(zero) == 0) { // k % number == 0
            return true;
        }

        BigInteger n = number.subtract(one);
        BigInteger val = number.subtract(one);
        while (true) {
            BigInteger calValue = bigIntegerK.modPow(val, number);
            if (calValue.compareTo(n) == 0) { // (calvalue == n - 1)
                return true;
            } else if (val.remainder(two).compareTo(one) == 0) { // (val % 2) == 1
                return (calValue.compareTo(one) == 0) || (calValue.compareTo(n) == 0); // (calValue == 1) || (calValue == (number - 1))
            }
            val = val.divide(two); // val /= 2
        }
    }
}