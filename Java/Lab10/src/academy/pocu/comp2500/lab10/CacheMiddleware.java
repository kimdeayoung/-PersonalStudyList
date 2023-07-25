package academy.pocu.comp2500.lab10;

import academy.pocu.comp2500.lab10.pocuflix.OkResult;
import academy.pocu.comp2500.lab10.pocuflix.ResultBase;
import academy.pocu.comp2500.lab10.pocuflix.ResultCode;

import java.util.HashMap;

public class CacheMiddleware implements IRequestHandler {
    private IRequestHandler handler;
    private int expiryCount;

    private HashMap<Request, Integer> cachedData;

    public CacheMiddleware(IRequestHandler handler, int expiryCount) {
        this.handler = handler;
        this.expiryCount = expiryCount;

        this.cachedData = new HashMap<>();
    }

    @Override
    public ResultBase handle(Request request) {
        int leftExpiryCount = cachedData.getOrDefault(request, 0);
        leftExpiryCount -= 1;

        if (leftExpiryCount > 0) {
            cachedData.put(request, leftExpiryCount);
            return new CachedResult(leftExpiryCount);
        } else {
            ResultBase resultBase = handler.handle(request);
            ResultValidator validator = new ResultValidator(resultBase);
            if (validator.isValid(ResultCode.OK)) {
                cachedData.put(request, this.expiryCount);
            }
            return resultBase;
        }
    }
}
