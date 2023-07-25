package academy.pocu.comp2500.lab10;

import academy.pocu.comp2500.lab10.pocuflix.NotFoundResult;
import academy.pocu.comp2500.lab10.pocuflix.ResultBase;
import academy.pocu.comp2500.lab10.pocuflix.User;

import java.util.HashSet;

public class AuthorizationMiddleware implements IRequestHandler {
    private IRequestHandler handler;
    private HashSet<User> users;

    public AuthorizationMiddleware(IRequestHandler handler, HashSet<User> user) {
        this.handler = handler;
        this.users = user;
    }

    @Override
    public ResultBase handle(Request request) {
        if (users.contains(request.getUser())) {
            return this.handler.handle(request);
        } else {
            return new UnauthorizedResult();
        }
    }
}
