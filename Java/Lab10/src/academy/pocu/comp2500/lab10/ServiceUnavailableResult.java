package academy.pocu.comp2500.lab10;

import academy.pocu.comp2500.lab10.pocuflix.ResultBase;
import academy.pocu.comp2500.lab10.pocuflix.ResultCode;

import java.time.OffsetDateTime;

public class ServiceUnavailableResult extends ResultBase {
    private OffsetDateTime checkStartdateTime;
    private OffsetDateTime checkEnddateTime;

    public ServiceUnavailableResult(OffsetDateTime startDate, OffsetDateTime endDate) {
        super(ResultCode.SERVICE_UNAVAILABLE);
        this.checkStartdateTime = startDate;
        this.checkEnddateTime = endDate;
    }

    public OffsetDateTime getStartDateTime() {
        return checkStartdateTime;
    }

    public OffsetDateTime getEndDateTime() {
        return checkEnddateTime;
    }
}
