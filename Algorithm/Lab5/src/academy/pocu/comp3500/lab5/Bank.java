package academy.pocu.comp3500.lab5;

import javax.crypto.Cipher;
import java.nio.ByteBuffer;
import java.security.KeyFactory;
import java.security.MessageDigest;
import java.security.PublicKey;
import java.security.spec.X509EncodedKeySpec;
import java.io.ByteArrayOutputStream;
import java.util.ArrayList;

public class Bank {
    private ArrayList<String> publicKeys;
    private ArrayList<Long> amounts;

    public Bank(byte[][] pubKeys, final long[] amounts) {
        this.publicKeys = new ArrayList<>();
        this.amounts = new ArrayList<>();
        for (int i = 0; i < pubKeys.length; ++i) {
            this.publicKeys.add(encodeToHexString(pubKeys[i]));
            this.amounts.add(amounts[i]);
        }
    }

    public long getBalance(final byte[] pubKey) {
        int index = findAmountsIndex(pubKey);
        if (index >= 0) {
            return amounts.get(index);
        } else {
            return 0;
        }
    }

    public boolean transfer(final byte[] from, byte[] to, final long amount, final byte[] signature) {
        if (amount <= 0) {
            return false;
        }

        try {
            KeyFactory keyFactory = KeyFactory.getInstance("RSA");
            PublicKey fromPublicKey = keyFactory.generatePublic(new X509EncodedKeySpec(from));

            Cipher cipher = Cipher.getInstance("RSA");
            cipher.init(Cipher.DECRYPT_MODE, fromPublicKey);

            byte[] certification = cipher.doFinal(signature);
            String certificationText = encodeToHexString(certification);

            ByteBuffer buffer = ByteBuffer.allocate(Long.BYTES);
            buffer.putLong(amount);

            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            outputStream.write(from);
            outputStream.write(to);
            outputStream.write(buffer.array());

            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(outputStream.toByteArray());
            byte[] bytes = md.digest();
            String bytesString = encodeToHexString(bytes);

            if (certificationText.equals(bytesString)) {
                long fromBalance = getBalance(from);
                if (fromBalance >= amount) {
                    int toAmountIndex = findAmountsIndex(to);
                    if (toAmountIndex == -1) {
                        toAmountIndex = this.amounts.size();
                        this.publicKeys.add(encodeToHexString(to));
                        this.amounts.add(0L);
                    }

                    long toBalance = this.amounts.get(toAmountIndex) + amount;
                    if (toBalance <= 0) {
                        return false;
                    }
                    this.amounts.set(findAmountsIndex(from), fromBalance - amount);
                    this.amounts.set(toAmountIndex, toBalance);

                    return true;
                }
            }

        } catch (Exception e) {
        }

        return false;
    }

    private int findAmountsIndex(final byte[] pubKey) {
        String publicKey = encodeToHexString(pubKey);
        for (int i = 0; i < publicKeys.size(); ++i) {
            if (publicKeys.get(i).equals(publicKey)) {
                return i;
            }
        }

        return -1;
    }

    private byte[] decodeFromHexString(String hexString) {
        byte[] bytes = new byte[hexString.length() / 2];
        for (int i = 0; i < hexString.length(); i += 2) {
            int firstDigit = Character.digit(hexString.charAt(i), 16);
            int secondDigit = Character.digit(hexString.charAt(i + 1), 16);
            bytes[i / 2] = (byte) ((firstDigit << 4) + secondDigit);
        }
        return bytes;
    }

    private String encodeToHexString(byte[] bytes) {
        StringBuilder result = new StringBuilder();
        for (byte oneByte : bytes) {
            result.append(String.format("%02x", oneByte));
        }
        return result.toString();
    }
}