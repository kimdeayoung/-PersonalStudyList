package academy.pocu.comp2500.lab7;

import java.util.ArrayList;

public class Bookshelf {
    private ArrayList<Book> books;
    private int maxBookCount;

    public Bookshelf(int maxBookCount) {
        this.maxBookCount = maxBookCount;
        this.books = new ArrayList<>(this.maxBookCount);
    }

    public boolean add(Book book) {
        if (books.size() < maxBookCount) {
            return books.add(book);
        }
        return false;
    }

    public boolean remove(Book book) {
        return books.remove(book);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj == null || !(obj instanceof Bookshelf) || this.hashCode() != obj.hashCode()) {
            return false;
        }

        Bookshelf compareBookshelf = (Bookshelf) obj;

        for (Book book : books) {
            boolean isFind = false;
            for (Book compareBook : compareBookshelf.books) {
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
        int hash = super.hashCode();
        hash += 31 * hash + maxBookCount;
        for (Book book : books) {
            hash += 31 * hash + book.hashCode();
        }

        return hash;
    }
}
