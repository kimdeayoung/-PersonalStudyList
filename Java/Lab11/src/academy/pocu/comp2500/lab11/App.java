package academy.pocu.comp2500.lab11;

import academy.pocu.comp2500.lab11.pocu.PermanentlyClosedException;
import academy.pocu.comp2500.lab11.pocu.Product;
import academy.pocu.comp2500.lab11.pocu.ProductNotFoundException;
import academy.pocu.comp2500.lab11.pocu.User;
import academy.pocu.comp2500.lab11.pocu.Wallet;
import academy.pocu.comp2500.lab11.pocu.Warehouse;
import academy.pocu.comp2500.lab11.pocu.WarehouseType;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;

public class App {
    private int selectWarehouse;
    private SafeWallet wallet;
    private Warehouse warehouse;

    public App() {
    }

    public void run(BufferedReader in, PrintStream out, PrintStream err) {
        if (wallet == null) {
            try {
                StringBuilder builder = new StringBuilder();
                builder.append("WAREHOUSE: ").append("Choose your warehouse!");
                out.println(builder.toString());
                builder.setLength(0);

                int index = 1;
                for (WarehouseType type : WarehouseType.values()) {
                    builder.append(index++).append(". ").append(type.toString()).append(System.lineSeparator());
                }

                out.println(builder.toString());

                String userInputText = null;
                userInputText = in.readLine();

                if (userInputText.equals("exit")) {
                    return;
                }

                selectWarehouse = Integer.parseInt(userInputText);

            } catch (IOException ioException) {
                reRun(in, out, err);
                return;
            } catch (NumberFormatException numberFormatException) {
                reRun(in, out, err);
                return;
            }

            if (selectWarehouse <= 0 || selectWarehouse > WarehouseType.values().length) {
                reRun(in, out, err);
                return;
            }
            warehouse = new Warehouse(WarehouseType.values()[this.selectWarehouse - 1]);

            User user = new User();
            try {
                wallet = new SafeWallet(user);
            } catch (IllegalAccessException illegalAccessException) {
                err.println("AUTH_ERROR");
                return;
            }
        }

        int productPrice = 0;
        try {
            StringBuilder builder = new StringBuilder();
            builder.append("BALANCE:").append(this.wallet.getAmount());
            out.println(builder.toString());
            builder.setLength(0);

            builder.append("PRODUCT_LIST: ").append("Choose the product you want to buy!");
            int index = 1;
            builder.append(System.lineSeparator());
            ArrayList<Product> products = warehouse.getProducts();
            for (int i = 0; i < products.size(); ++i) {
                Product product = products.get(i);
                builder.append(index++).append(". ").append(product.getName()).append('\t').append('\t').append(product.getPrice()).append(System.lineSeparator());
            }

            out.println(builder.toString());

            String userInputText = null;
            userInputText = in.readLine();

            if (userInputText.equals("exit")) {
                return;
            }
            int selectProduct = Integer.parseInt(userInputText);
            if (selectProduct <= 0 || selectProduct > products.size()) {
                reRun(in, out, err);
                return;
            }

            selectProduct -= 1;
            productPrice = products.get(selectProduct).getPrice();
            if (wallet.getAmount() >= productPrice) {
                if (wallet.withdraw(productPrice)) {
                    warehouse.removeProduct(products.get(selectProduct).getId());
                }
            }
        } catch (IOException ioException) {
            reRun(in, out, err);
            return;
        } catch (NumberFormatException numberFormatException) {
            reRun(in, out, err);
            return;
        } catch (ProductNotFoundException productNotFoundException) {
            wallet.deposit(productPrice);
            reRun(in, out, err);
            return;
        }

        reRun(in, out, err);
        return;
    }

    private void reRun(BufferedReader in, PrintStream out, PrintStream err) {
        run(in, out, err);
    }
}
