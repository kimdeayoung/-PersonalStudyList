package academy.pocu.comp2500.lab10;

import academy.pocu.comp2500.lab10.pocuflix.Movie;
import academy.pocu.comp2500.lab10.pocuflix.NotFoundResult;
import academy.pocu.comp2500.lab10.pocuflix.OkResult;
import academy.pocu.comp2500.lab10.pocuflix.ResultBase;

import java.util.ArrayList;

public class MovieStore implements IRequestHandler {
    private ArrayList<Movie> movies;

    public MovieStore() {
        movies = new ArrayList<>();
    }

    public void add(Movie movie) {
        this.movies.add(movie);
    }

    public boolean remove(int index) {
        if (this.movies.size() > index) {
            Movie movie = this.movies.remove(index);
            return movie != null;
        }
        return false;
    }

    @Override
    public ResultBase handle(Request request) {
        Movie findedMovie = null;
        for (Movie movie : movies) {
            if (movie.getTitle().equals(request.getMovieName())) {
                findedMovie = movie;
                break;
            }
        }

        if (findedMovie == null) {
            return new NotFoundResult();
        } else {
            return new OkResult(findedMovie);
        }
    }
}
