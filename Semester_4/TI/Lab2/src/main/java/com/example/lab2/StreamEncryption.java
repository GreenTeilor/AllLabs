package com.example.lab2;

public class StreamEncryption {
    public static byte[] generateKey(int userKey, int tactCount) {
        byte[] result = new byte[tactCount / 8];
        byte highBit = 0;
        byte xorResult = 0;
        for (int i = 0; i < tactCount; ++i) {
            highBit = (byte)((userKey >>> 31) & 1);
            result[i / 8] <<= 1;
            result[i / 8] |= highBit;
            xorResult = (byte)( ((userKey >>> 31) ^
                    (userKey >>> 27) ^
                    (userKey >>> 26) ^
                    userKey) & 1 );
            userKey <<= 1;
            userKey |= xorResult;
        }
        return result;
    }

    public static byte[] transform(byte[] bytesArrayM, byte[] generatedKey) {
        byte[] bytesArrayC = new byte[bytesArrayM.length];
        for (int i = 0; i < bytesArrayC.length; ++i) {
            bytesArrayC[i] = (byte)(bytesArrayM[i] ^ generatedKey[i]);
        }
        return bytesArrayC;
    }
}
