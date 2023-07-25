package academy.pocu.comp2500.lab10;

import academy.pocu.comp2500.lab10.pocuflix.User;

public class Request {
    private String movieName;

    private User user;

    public Request(String name) {
        this.movieName = name;
    }

    public String getMovieName() {
        return movieName;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj == null || !(obj instanceof Request) || this.hashCode() != obj.hashCode()) {
            return false;
        }

        Request request = (Request) obj;
        boolean result = this.movieName.equals(request.movieName);
        if (result) {
            if (this.user == null) {
                return request.user == null;
            } else {
                return this.user.equals(request.user);
            }
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 17;
        hash = 31 * hash + (this.movieName == null ? 0 : this.movieName.hashCode());
        hash = 31 * hash + (this.user == null ? 0 : this.user.hashCode());

        return hash;
    }
}
