package com.example.lab3;

import java.nio.ByteBuffer;
import java.util.function.Function;

import static com.example.lab3.AlgorithmsUtils.fastExp;
import static com.example.lab3.AlgorithmsUtils.toUnsignedInteger;

public class ElGamalEncryptionUtils {

    public static int calculateY(int p, int g, int x){
        return fastExp(g,x,p);
    }

    public static byte[] encrypt(int p, int g, byte[] M, int Y, int k){
        switch (p < 128 ? 0 : p < 32768 ? 1 : 2) {
            case 0 -> {
                /*
                byte A = (byte)fastExp(g,k,p);
                byte[] C = new byte[M.length * 2];
                int i = 0;
                for(byte b : M){
                    C[i] = A;
                    ++i;
                    //byte B = (byte) ((int)(Math.pow(Y, k) * b) % p);
                    byte B = (byte) (fastExp(Y, k, p) * b % p);
                    C[i] = B;
                    ++i;
                }
                return C;
                */
                byte A = (byte)fastExp(g,k,p);
                byte[] C = new byte[M.length * 2];
                int i = 0;
                for(byte b : M){
                    C[i] = A;
                    ++i;
                    //byte B = (byte) ((int)(Math.pow(Y, k) * b) % p);
                    byte B = (byte) (fastExp(Y, k, p) * AlgorithmsUtils.toUnsignedInt(b) % p);
                    C[i] = B;
                    ++i;
                }
                return C;
            }
            case 1 -> {
                /*
                short A = (short)fastExp(g,k,p);
                byte[] C = new byte[M.length * 4];
                int i = 0;
                for(byte b : M){
                    C[i] = (byte)(A >>> 8);
                    ++i;
                    C[i] = (byte)A;
                    ++i;
                    //short B = (short) ((int)(Math.pow(Y, k) * b) % p);
                    //(Y^k * b) mod p = ( (Y^k mod p) * (b mod p) ) mod p = (Y^k mod p) * b mod p
                    short B = (short) (fastExp(Y, k, p) * b % p);
                    C[i] = (byte)(B >>> 8);
                    ++i;
                    C[i] = (byte)B;
                    ++i;
                }
                return C;
                */
                short A = (short)fastExp(g,k,p);
                byte[] C = new byte[M.length * 4];
                int i = 0;
                for(byte b : M){
                    C[i] = (byte)(A >>> 8);
                    ++i;
                    C[i] = (byte)A;
                    ++i;
                    //short B = (short) ((int)(Math.pow(Y, k) * b) % p);
                    //(Y^k * b) mod p = ( (Y^k mod p) * (b mod p) ) mod p = (Y^k mod p) * b mod p
                    short B = (short) (fastExp(Y, k, p) * toUnsignedInteger(b) % p);
                    C[i] = (byte)(B >>> 8);
                    ++i;
                    C[i] = (byte)B;
                    ++i;
                }
                return C;
            }
            case 2 -> {
                int A = fastExp(g,k,p);
                byte[] C = new byte[M.length * 8];
                int i = 0;
                for(byte b : M){
                    C[i] = (byte)(A >>> 24);
                    ++i;
                    C[i] = (byte)(A >>> 16);
                    ++i;
                    C[i] = (byte)(A >>> 8);
                    ++i;
                    C[i] = (byte)A;
                    ++i;
                    //int B = (int)(Math.pow(Y, k) * b) % p;
                    int B = fastExp(Y, k, p) * toUnsignedInteger(b) % p;
                    C[i] = (byte)(B >>> 24);
                    ++i;
                    C[i] = (byte)(B >>> 16);
                    ++i;
                    C[i] = (byte)(B >>> 8);
                    ++i;
                    C[i] = (byte)B;
                    ++i;
                }
                return C;
            }
        }
        return null;
    }

    public static byte[] decrypt(byte[] C, int p, int X, int numberSize){
        byte[] M = new byte[C.length / (numberSize * 2)];
        ByteBuffer wrapped = ByteBuffer.wrap(C); // big-endian by default
        Function<ByteBuffer, ? extends Number> toNumber;
        switch(numberSize) {
            case 2 -> toNumber = ByteBuffer::getShort;
            case 4 -> toNumber = ByteBuffer::getInt;
            default -> toNumber = ByteBuffer::get;
        }
        //return fastExp(A,p-1-X,p)*B %p;
        for (int i = 0; i < C.length; i += (numberSize * 2)) {
            int A = AlgorithmsUtils.toUnsignedInteger(toNumber.apply(wrapped).intValue());
            int B = AlgorithmsUtils.toUnsignedInteger(toNumber.apply(wrapped).intValue());
            M[i / (numberSize * 2)] = (byte)(fastExp(A, p - 1 - X, p) * B % p);
        }
        return M;
    }
}
