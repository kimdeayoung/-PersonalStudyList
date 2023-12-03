package academy.pocu.comp3500.assignment4;

import academy.pocu.comp3500.assignment4.project.Task;

public class MaximumFlowEdge {
    private final Task from;
    private final Task to;

    private int flow;//유량

    public MaximumFlowEdge(Task from, Task to) {
        this.from = from;
        this.to = to;
        this.flow = 0;
    }

    public Task getFrom() {
        return from;
    }

    public Task getTo() {
        return to;
    }

    public int getFlow() {
        return flow;
    }

    public void additionalFlow(int flow) {
        this.flow += flow;
    }

    public void clear() {
        this.flow = 0;
    }

    @Override
    public String toString() {
        return "from: " + from.getTitle() + " to: " + to.getTitle() + " flow: " + flow;
    }
}
