package academy.pocu.comp3500.assignment4;

import academy.pocu.comp3500.assignment4.project.Task;

public class Candidate implements Comparable<Candidate> {
    private final Task task;
    private final int distance;

    public Candidate(final Task task, final int distance) {
        this.task = task;
        this.distance = distance;
    }

    public Task getTask() {
        return this.task;
    }

    public int getDistance() {
        return this.distance;
    }

    @Override
    public int compareTo(Candidate o) {
        return o.distance - this.distance;
    }
}
