package academy.pocu.comp2500.lab10;

import academy.pocu.comp2500.lab10.pocuflix.NotFoundResult;
import academy.pocu.comp2500.lab10.pocuflix.OkResult;
import academy.pocu.comp2500.lab10.pocuflix.ResultBase;

import java.time.OffsetDateTime;
import java.time.ZoneOffset;

public class MaintenanceMiddleware implements IRequestHandler {
    private IRequestHandler handler;
    private OffsetDateTime checkStartdateTime;

    public MaintenanceMiddleware(IRequestHandler handler, OffsetDateTime startDateTime) {
        this.handler = handler;
        this.checkStartdateTime = startDateTime;
    }

    @Override
    public ResultBase handle(Request request) {
        OffsetDateTime checkEnddateTime = this.checkStartdateTime.plusHours(1);

        if (OffsetDateTime.now(ZoneOffset.UTC).isBefore(this.checkStartdateTime) || OffsetDateTime.now(ZoneOffset.UTC).isAfter(checkEnddateTime)) {
            return this.handler.handle(request);
        } else {
            return new ServiceUnavailableResult(checkStartdateTime, checkEnddateTime);
        }
    }
}
