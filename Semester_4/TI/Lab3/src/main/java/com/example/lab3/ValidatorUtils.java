package com.example.lab3;

public class ValidatorUtils {
    private ValidatorUtils() {

    }

    public static boolean isValidP(int P) {
        return AlgorithmsUtils.isPrime(P, 100) && P > 255 && P < 1000000;
    }

    public static boolean isValidK(int K, int P) {
        return K > 1 && K < P - 1 && AlgorithmsUtils.gcd(K, P - 1) == 1;
    }

    public static boolean isValidX(int X, int P) {
        return X > 1 && X < P - 1;
    }

}
