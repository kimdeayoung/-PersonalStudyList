package academy.pocu.comp2500.lab7;

public class Book {
    private String name;
    private Author author;
    private int year;
    private Genre genre;

    public Book(String name, Author author, int year, Genre genre) {
        this.name = name;
        this.author = author;
        this.year = year;
        this.genre = genre;
    }

    public String getName() {
        return name;
    }

    public Author getAuthor() {
        return author;
    }

    public int getYear() {
        return year;
    }

    public Genre getGenre() {
        return genre;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append(this.name);
        builder.append(" [");
        builder.append(this.author.toString());
        builder.append("]");

        return builder.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj == null || !(obj instanceof Book) || this.hashCode() != obj.hashCode()) {
            return false;
        }

        Book compareBook = (Book) obj;
        return this.name.equals(compareBook.name) && this.author.equals(compareBook.author) && this.year == compareBook.year && this.genre == compareBook.genre;
    }

    @Override
    public int hashCode() {
        int hash = 17;
        hash = 31 * hash + (this.name == null ? 0 : this.name.hashCode());
        hash = 31 * hash + this.author.hashCode();
        hash = 31 * hash + this.year;
        hash = 31 * hash + this.genre.hashCode();

        return hash;
    }
}
