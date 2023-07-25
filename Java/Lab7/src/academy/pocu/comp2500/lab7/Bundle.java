package academy.pocu.comp2500.lab7;

import java.util.HashSet;

public class Bundle {
    private final short MAXBOOKCOUNT = 4;
    private String name;
    private HashSet<Book> books;

    public Bundle(String name) {
        this.name = name;
        this.books = new HashSet<>();
    }

    public boolean add(Book book) {
        return books.add(book);
    }

    public boolean remove(Book book) {
        return books.remove(book);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj == null || !(obj instanceof Bundle) || this.hashCode() != obj.hashCode()) {
            return false;
        }

        Bundle compareBundle = (Bundle) obj;
        if (this.name.equals(compareBundle.name) == false) {
            return false;
        }

        for (Book book : books) {
            boolean isFind = false;
            for (Book compareBook : compareBundle.books) {
                if (book.equals(compareBook)) {
                    isFind = true;
                    break;
                }
            }

            if (isFind == false) {
                return false;
            }
        }
        return true;
    }

    @Override
    public int hashCode() {
        int hash = this.name.hashCode();
        for (Book book : books) {
            hash += 31 * hash + book.hashCode();
        }

        return hash;
    }
}
