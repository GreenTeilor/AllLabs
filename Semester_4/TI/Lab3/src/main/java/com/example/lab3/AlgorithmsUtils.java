package com.example.lab3;

import java.util.ArrayList;
import java.util.List;

public class AlgorithmsUtils {
    public static int gcd(int a, int b) {
        while (a != b) {
            if (a > b) {
                a -= b;
            } else {
                b -= a;
            }
        }
        return a;
    }

    //Calculate a^z mod p
    public static int fastExp(int a, int z, int p) {
        long a1 = a;
        long z1 = z;
        long x = 1;
        while (z1 != 0) {
            while (z1 % 2 == 0) {
                z1 /= 2;
                //a1 = (a1 * a1) % p;
                a1 = (a1 % p) * a1 % p;
            }
            z1--;
            //x = (x * a1) % p;
            x = (x % p) * a1 % p;
        }
        return (int)x;
    }

    //Is n prime
    public static boolean isPrime(int n, int iterationsCount) {
        if (n <= 1 || n == 4) return false;
        if (n <= 3) return true;
        while (iterationsCount > 0) {
            //int randValue = 2 + (int) (Math.random() % (n - 4));
            int randValue = (int) (Math.random() * (n - 1) + 1);
            // Fermat's little theorem
            if (fastExp(randValue, n - 1, n) != 1)
                return false;
            iterationsCount--;
        }
        return true;
    }

    public static List<Integer> findPrimeFactors(int number) {
        List<Integer> resultList = new ArrayList<>();
        for (int i = 2; i * i <= number; ++i) {
            if (number % i == 0) {
                resultList.add(i);
                while (number % i == 0) {
                    number /= i;
                }
            }
        }
        if (number != 1) {
            resultList.add(number);
        }
        return resultList;
    }

    public static List<Integer> findRoots(int p) {
        List<Integer> simple = findPrimeFactors(p - 1);
        List<Integer> res = new ArrayList<>();
        boolean flag;
        for (int g = 2; g < p; g++) {
            flag = true;
            for (int j = 0; j < simple.size(); j++) {
                if (fastExp(g, (p - 1) / simple.get(j), p) == 1) {
                    flag = false;
                } else {
                    if ((j == simple.size() - 1) && (flag)) {
                        res.add(g);
                    }
                }
            }
        }
        return res;
    }

    public static int toUnsignedInt(byte x) {
        return ((int) x) & 0xff;
    }

    public static <T extends Number> Integer toUnsignedInteger(T x) {
        if (x instanceof Byte) {
            return (x.intValue()) & 0xff;
        } else if (x instanceof Short) {
            return (x.intValue()) & 0xffff;
        } else {
            return x.intValue();
        }
    }
}
