package academy.pocu.comp2500.lab10;

import academy.pocu.comp2500.lab10.pocuflix.ResultBase;

public interface IRequestHandler {
    ResultBase handle(Request request);
}
