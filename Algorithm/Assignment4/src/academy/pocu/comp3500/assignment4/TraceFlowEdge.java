package academy.pocu.comp3500.assignment4;

import academy.pocu.comp3500.assignment4.project.Task;

public class TraceFlowEdge {
    private final MaximumFlowEdge edge;
    private final boolean isTranspose;

    public TraceFlowEdge(final MaximumFlowEdge edge, final boolean isTranspose) {
        this.edge = edge;
        this.isTranspose = isTranspose;
    }

    public MaximumFlowEdge getEdge() {
        return edge;
    }

    public boolean isTranspose() {
        return isTranspose;
    }

    @Override
    public String toString() {
        return edge.toString() + ", isTranspose : " + isTranspose;
    }
}
