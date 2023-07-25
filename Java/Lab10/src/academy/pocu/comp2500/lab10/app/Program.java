package academy.pocu.comp2500.lab10.app;

import academy.pocu.comp2500.lab10.AuthorizationMiddleware;
import academy.pocu.comp2500.lab10.CacheMiddleware;
import academy.pocu.comp2500.lab10.CachedResult;
import academy.pocu.comp2500.lab10.MaintenanceMiddleware;
import academy.pocu.comp2500.lab10.MovieStore;
import academy.pocu.comp2500.lab10.Request;
import academy.pocu.comp2500.lab10.ResultValidator;
import academy.pocu.comp2500.lab10.ServiceUnavailableResult;
import academy.pocu.comp2500.lab10.UnauthorizedResult;
import academy.pocu.comp2500.lab10.pocuflix.Movie;
import academy.pocu.comp2500.lab10.pocuflix.NotFoundResult;
import academy.pocu.comp2500.lab10.pocuflix.OkResult;
import academy.pocu.comp2500.lab10.pocuflix.Rating;
import academy.pocu.comp2500.lab10.pocuflix.ResultBase;
import academy.pocu.comp2500.lab10.pocuflix.ResultCode;
import academy.pocu.comp2500.lab10.pocuflix.User;

import java.time.OffsetDateTime;
import java.time.ZoneOffset;
import java.util.HashSet;
import java.util.concurrent.TimeUnit;

public class Program {

    public static void main(String[] args) {
        MovieStore store = new MovieStore();

        store.add(new Movie("Harry Potter", Rating.PG13, 180));
        store.add(new Movie("The Lord of the Rings", Rating.R, 180));

        Request request;
        ResultBase result;

        // ===========================================
        // 1.MaintenanceMiddleware -> CacheMiddleware
        // ===========================================
        {
            // maintain middleware
            OffsetDateTime now = OffsetDateTime.now(ZoneOffset.UTC);
            OffsetDateTime startDateTime = now.plusSeconds(3);

            MaintenanceMiddleware maintainMiddleware = new MaintenanceMiddleware(store, startDateTime);

            request = new Request("Harry Potter");
            result = maintainMiddleware.handle(request);
            assert (result.getCode() == ResultCode.OK);
            assert (result instanceof OkResult);

            // cached middle ware
            CacheMiddleware cachedMiddleware = new CacheMiddleware(maintainMiddleware, 3);

            request = new Request("Harry Potter");
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.OK);
            assert (result instanceof OkResult);


            request = new Request("Harry Potter");
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.NOT_MODIFIED);
            assert (result instanceof CachedResult);

            CachedResult cachedResult = (CachedResult) result;
            assert (cachedResult.getExpiryCount() == 2);


            sleep(5);

            request = new Request("Harry Potter");
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.NOT_MODIFIED);
            assert (result instanceof CachedResult);

            cachedResult = (CachedResult) result;
            assert (cachedResult.getExpiryCount() == 1);

            request = new Request("Harry Potter");
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.SERVICE_UNAVAILABLE);
            assert (result instanceof ServiceUnavailableResult);

        }

        // ===========================================
        // 2.AuthorizationMiddleware -> CacheMiddleware
        // ===========================================
        {
            // authorization middleware
            HashSet<User> users = new HashSet<>();
            users.add(new User("Jane", "Doe"));

            AuthorizationMiddleware authorizationMiddleware = new AuthorizationMiddleware(store, users);

            request = new Request("Harry Potter");
            request.setUser(new User("Jane", "Doe"));
            result = authorizationMiddleware.handle(request);

            assert (result.getCode() == ResultCode.OK);
            assert (result instanceof OkResult);

            // cached middle ware
            CacheMiddleware cachedMiddleware = new CacheMiddleware(authorizationMiddleware, 3);
            CachedResult cachedResult;

            request = new Request("Harry Potter");
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.UNAUTHORIZED);
            assert (result instanceof UnauthorizedResult);


            request = new Request("Harry Potter");
            request.setUser(new User("Jane", "Doe"));
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.OK);
            assert (result instanceof OkResult);

            request = new Request("Harry Potter");
            request.setUser(new User("Jane", "Doe"));
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.NOT_MODIFIED);
            assert (result instanceof CachedResult);

            cachedResult = (CachedResult) result;
            assert (cachedResult.getExpiryCount() == 2);

            request = new Request("Harry Potter");
            request.setUser(new User("Jane", "Doe"));
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.NOT_MODIFIED);
            assert (result instanceof CachedResult);

            cachedResult = (CachedResult) result;
            assert (cachedResult.getExpiryCount() == 1);
        }

        // ===========================================
        // 3.CacheMiddleware  -> AuthorizationMiddleware
        // ===========================================
        {
            // cached middle ware
            CacheMiddleware cachedMiddleware = new CacheMiddleware(store, 3);
            request = new Request("Harry Potter");
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.OK);
            assert (result instanceof OkResult);

            request = new Request("Harry Potter");
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.NOT_MODIFIED);
            assert (result instanceof CachedResult);

            CachedResult cachedResult = (CachedResult) result;
            assert (cachedResult.getExpiryCount() == 2);

            // authorization middleware
            HashSet<User> users = new HashSet<>();
            users.add(new User("Jane", "Doe"));

            AuthorizationMiddleware authorizationMiddleware = new AuthorizationMiddleware(cachedMiddleware, users);

            request = new Request("Harry Potter");
            request.setUser(new User("Jane", "Doe"));
            result = authorizationMiddleware.handle(request);

            assert (result.getCode() == ResultCode.OK);
            assert (result instanceof OkResult);

            request = new Request("Harry Potter");
            request.setUser(new User("Jane", "Doe"));
            result = authorizationMiddleware.handle(request);

            assert (result.getCode() == ResultCode.NOT_MODIFIED);
            assert (result instanceof CachedResult);

            cachedResult = (CachedResult) result;
            assert (cachedResult.getExpiryCount() == 2);
        }

        // ===========================================
        // 4.CacheMiddleware  -> MaintenanceMiddleware
        // ===========================================
        {
            // cached middle ware
            CacheMiddleware cachedMiddleware = new CacheMiddleware(store, 3);
            request = new Request("Harry Potter");
            result = cachedMiddleware.handle(request);
            assert (result.getCode() == ResultCode.OK);
            assert (result instanceof OkResult);

            // maintain middleware
            OffsetDateTime now = OffsetDateTime.now(ZoneOffset.UTC);
            OffsetDateTime startDateTime = now.plusSeconds(3);

            MaintenanceMiddleware maintainMiddleware = new MaintenanceMiddleware(cachedMiddleware, startDateTime);

            request = new Request("Harry Potter");
            result = maintainMiddleware.handle(request);
            assert (result.getCode() == ResultCode.NOT_MODIFIED);
            assert (result instanceof CachedResult);

            CachedResult cachedResult = (CachedResult) result;
            assert (cachedResult.getExpiryCount() == 2);

            sleep(5);

            request = new Request("Harry Potter");
            result = maintainMiddleware.handle(request);
            assert (result.getCode() == ResultCode.SERVICE_UNAVAILABLE);
            assert (result instanceof ServiceUnavailableResult);
        }

    }

    private static void sleep(int seconds) {
        try {
            TimeUnit.SECONDS.sleep(seconds);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}