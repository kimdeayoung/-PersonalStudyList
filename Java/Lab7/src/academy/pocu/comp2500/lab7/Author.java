package academy.pocu.comp2500.lab7;

public class Author {
    private String firstName;
    private String lastName;

    public Author(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append(this.firstName);
        builder.append(" ");
        builder.append(this.lastName);

        return builder.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj == null || !(obj instanceof Author) || this.hashCode() != obj.hashCode()) {
            return false;
        }

        Author compareAuthoer = (Author) obj;
        return this.toString().equals(compareAuthoer.toString());
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 31 * hash + (this.firstName == null ? 0 : this.firstName.hashCode());
        hash = 31 * hash + (this.lastName == null ? 0 : this.lastName.hashCode());

        return hash;
    }
}
