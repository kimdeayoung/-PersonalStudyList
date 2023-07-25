package academy.pocu.comp2500.lab7;

import java.util.ArrayList;

public class ReadingList {
    private String name;
    private ArrayList<Book> books;

    public ReadingList(String name) {
        this.name = name;
        this.books = new ArrayList<>();
    }

    public void add(Book book) {
        this.books.add(book);
    }

    public boolean remove(Book book) {
        return this.books.remove(book);
    }

    @Override
    public String toString() {
        int count = 1;
        StringBuilder builder = new StringBuilder();
        for (Book book : this.books) {
            builder.append(count++);
            builder.append(". ");
            builder.append(book.toString());
            builder.append(System.lineSeparator());
        }

        return builder.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj == null || !(obj instanceof ReadingList) || this.hashCode() != obj.hashCode()) {
            return false;
        }

        ReadingList compareReadingList = (ReadingList) obj;
        if (this.name.equals(compareReadingList.name) == false) {
            return false;
        }

        int index = 0;

        for (Book book : books) {
            if (book.equals(compareReadingList.books.get(index++)) == false) {
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
