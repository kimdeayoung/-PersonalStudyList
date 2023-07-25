package academy.pocu.comp2500.lab11;

import academy.pocu.comp2500.lab11.pocu.User;
import academy.pocu.comp2500.lab11.pocu.Wallet;

public class SafeWallet extends Wallet {
    public SafeWallet(User user) throws IllegalAccessException {
        super(user);
    }

    @Override
    public boolean deposit(int amount) throws OverflowException {
        int addAmount = getAmount() + amount;
        if (addAmount < 0) {
            throw new OverflowException("");
        }
        return super.deposit(amount);
    }
}
