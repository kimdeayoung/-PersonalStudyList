package academy.pocu.comp3500.lab4;

import academy.pocu.comp3500.lab4.pocuhacker.RainbowTable;
import academy.pocu.comp3500.lab4.pocuhacker.User;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.lang.String;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;

public final class Cracker {
    final private User[] userTable;

    private int mdTableIndex;

    public Cracker(User[] userTable, String email, String password) {
        this.userTable = userTable;
        this.mdTableIndex = 2;

        String md2PasswordHash = Base64.getEncoder().encodeToString(getHash(password, "md2"));
        for (int i = 0; i < userTable.length; ++i) {
            if (userTable[i].getPasswordHash().equals(md2PasswordHash)) {
                this.mdTableIndex = 1;
                break;
            }
        }
    }

    public static byte[] getHash(String message, String algorithm) {
        try {
            byte[] buffer = message.getBytes();
            MessageDigest md = MessageDigest.getInstance(algorithm);
            md.update(buffer);

            return md.digest();
        } catch (NoSuchAlgorithmException e) {
        }

        return null;
    }

    public String[] run(final RainbowTable[] rainbowTables) {
        String[] result = new String[userTable.length];

        if (rainbowTables.length <= 0) {
            return result;
        }

        for (int i = 0; i < userTable.length; ++i) {
            String hash = userTable[i].getPasswordHash();

            try {
                Long value = Long.parseLong(hash);
                result[i] = rainbowTables[0].get(hash);
                continue;
            } catch (NumberFormatException e) {
            }

            try {
                byte[] hashBytes = hash.getBytes(StandardCharsets.UTF_8);
                byte[] bytes = Base64.getDecoder().decode(hashBytes);

                int bitSize = bytes.length * 8;
                switch (bitSize) {
                    case 128://MD2, MD5
                        result[i] = rainbowTables[mdTableIndex].get(hash);
                        break;
                    case 160://SHA-1
                        result[i] = rainbowTables[3].get(hash);
                        break;
                    case 256://SHA-256
                        result[i] = rainbowTables[4].get(hash);
                        break;
                }
            } catch (IllegalArgumentException e) {
            }
        }

        return result;
    }
}