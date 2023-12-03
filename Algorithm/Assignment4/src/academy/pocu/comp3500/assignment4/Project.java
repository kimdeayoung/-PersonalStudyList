package academy.pocu.comp3500.assignment4;

import academy.pocu.comp3500.assignment4.project.Task;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;

public final class Project {
    private final HashMap<String, Task> tasks;

    private final HashMap<String, Task> transposeTasks;

    private final HashMap<String, Integer> taskIndexes;
    private final boolean[] isCycleTask;

    private int[] nodeCapacityDatas; // 노드의 capacity 데이터

    public Project(final Task[] tasks) {
        this.tasks = new HashMap<>(tasks.length);
        this.transposeTasks = new HashMap<>(tasks.length);
        this.taskIndexes = new HashMap<>(tasks.length);
        this.isCycleTask = new boolean[tasks.length];
        this.nodeCapacityDatas = new int[tasks.length + 1];

        int index = 0;
        LinkedList<Task> reverseTask = new LinkedList<>();
        {
            for (Task task : tasks) {
                String title = task.getTitle();
                int estimate = task.getEstimate();

                this.tasks.put(title, task);
                this.transposeTasks.put(title, new Task(title, estimate));
                this.taskIndexes.put(title, index++);
            }
        }

        //init transposeTasks, reverseTask
        {
            boolean[] isVisited = new boolean[tasks.length];//for reverseTask
            for (Task task : tasks) {
                String title = task.getTitle();
                int taskIndex = this.taskIndexes.get(task.getTitle());
                nodeCapacityDatas[taskIndex] = task.getEstimate();

                for (Task predecessor : task.getPredecessors()) {
                    Task transposeTask = transposeTasks.get(title);
                    transposeTasks.get(predecessor.getTitle()).addPredecessor(transposeTask);
                }

                if (!isVisited[taskIndex]) {
                    getReverseTaskRecursive(task, reverseTask, isVisited);
                }
            }
            this.nodeCapacityDatas[this.nodeCapacityDatas.length - 1] = Integer.MAX_VALUE;
        }

        {
            boolean[] isVisited = new boolean[tasks.length];
            ArrayList<Task> scc = new ArrayList<>();

            for (Task task : reverseTask) {
                Task transposeTask = transposeTasks.get(task.getTitle());
                if (isVisited[this.taskIndexes.get(transposeTask.getTitle())]) {
                    continue;
                }

                findCycleTaskDFSRecursive(transposeTask, scc, isVisited);
                if (scc.size() > 1) {
                    for (Task sccTask : scc) {
                        this.isCycleTask[this.taskIndexes.get(sccTask.getTitle())] = true;
                    }
                }

                scc.clear();
            }
        }
    }

    private void getReverseTaskRecursive(final Task task, final LinkedList<Task> reverseTask, final boolean[] isVisited) {
        int taskIndex = this.taskIndexes.get(task.getTitle());
        if (!isVisited[taskIndex]) {
            isVisited[taskIndex] = true;
            for (Task predecessorTask : task.getPredecessors()) {
                getReverseTaskRecursive(predecessorTask, reverseTask, isVisited);
            }

            reverseTask.addFirst(task);
        }
    }

    private void findCycleTaskDFSRecursive(final Task task, ArrayList<Task> scc, final boolean[] isVisited) {
        int taskIndex = this.taskIndexes.get(task.getTitle());
        isVisited[taskIndex] = true;

        for (Task neighborTask : task.getPredecessors()) {
            if (isVisited[this.taskIndexes.get(neighborTask.getTitle())]) {
                continue;
            }

            findCycleTaskDFSRecursive(neighborTask, scc, isVisited);
        }
        scc.add(task);
    }

    private HashMap<String, Task> getSchedule(final String task, final boolean isNeedCycleTask) {
        HashMap<String, Task> tasks = new HashMap<>();
        {//task bfs
            Task targetTask = this.tasks.get(task);
            boolean[] isVisited = new boolean[this.tasks.size()];

            LinkedList<Task> taskQueue = new LinkedList<>();
            taskQueue.addLast(targetTask);
            isVisited[this.taskIndexes.get(targetTask.getTitle())] = true;

            while (!taskQueue.isEmpty()) {
                Task queuedTask = taskQueue.removeFirst();
                tasks.put(queuedTask.getTitle(), queuedTask);

                for (Task predecessors : queuedTask.getPredecessors()) {
                    int taskIndex = this.taskIndexes.get(predecessors.getTitle());

                    boolean addAble = isNeedCycleTask ? (!isVisited[taskIndex]) : (!isVisited[taskIndex] && !isCycleTask[taskIndex]);
                    if (addAble) {
                        isVisited[this.taskIndexes.get(predecessors.getTitle())] = true;
                        taskQueue.addLast(predecessors);
                    }
                }
            }
        }
        return tasks;
    }

    public int findTotalManMonths(final String task) {
        //task bfs
        Task targetTask = this.tasks.get(task);
        boolean[] isVisited = new boolean[this.tasks.size()];

        LinkedList<Task> totalManMonthsQueue = new LinkedList<>();
        totalManMonthsQueue.addLast(targetTask);
        isVisited[this.taskIndexes.get(targetTask.getTitle())] = true;

        int manMonth = 0;
        while (!totalManMonthsQueue.isEmpty()) {
            Task queuedTask = totalManMonthsQueue.removeFirst();
            manMonth += queuedTask.getEstimate();

            for (Task predecessors : queuedTask.getPredecessors()) {
                int taskIndex = this.taskIndexes.get(predecessors.getTitle());

                if (!isVisited[taskIndex] && !isCycleTask[taskIndex]) {
                    isVisited[this.taskIndexes.get(predecessors.getTitle())] = true;
                    totalManMonthsQueue.addLast(predecessors);
                }
            }
        }

        return manMonth;
    }

    public int findMinDuration(final String task) {
        HashMap<String, Task> schedule = getSchedule(task, false);

        HashMap<String, String> prevs = new HashMap<>();
        return findmaximumEstimateDijkstra(schedule, task, prevs);
    }

    private int findmaximumEstimateDijkstra(final HashMap<String, Task> tasks, final String from, final HashMap<String, String> prevs) {
        HashMap<String, Integer> maxDists = new HashMap<>();

        //모든 경로의 값을 Integer 최솟값으로 지정
        final int inf = Integer.MIN_VALUE;
        for (Task task : tasks.values()) {
            maxDists.put(task.getTitle(), inf);
        }

        Task startTask = tasks.get(from);

        maxDists.put(from, startTask.getEstimate());
        prevs.put(from, null);

        //내림차순 우선순위 큐
        PriorityQueue<Candidate> open = new PriorityQueue<>();

        Candidate candidate = new Candidate(startTask, startTask.getEstimate());
        open.add(candidate);

        while (!open.isEmpty()) {
            candidate = open.poll();

            Task task = candidate.getTask();

            int maxDist = maxDists.get(task.getTitle());
            int dist = candidate.getDistance();

            //이미 등록된 maxDist보다 작은 경우 업데이트 고려하지 않음
            if (maxDist > dist) {
                continue;
            }

            //task의 주변 경로도 전부 탐색
            for (Task predecessor : task.getPredecessors()) {
                String title = predecessor.getTitle();

                int newEstimate = maxDist + predecessor.getEstimate();
                int nextMaxEstimate = maxDists.get(title);

                //주변 경로 탐색 이후 기존 최대거리보다 크면 업데이트
                if (newEstimate <= nextMaxEstimate) {
                    continue;
                }

                maxDists.put(title, newEstimate);
                prevs.put(title, task.getTitle());

                open.add(new Candidate(predecessor, newEstimate));
            }
        }

        int value = inf;
        for (int estimate : maxDists.values()) {
            if (value < estimate) {
                value = estimate;
            }
        }

        return value;
    }

    public int findMaxBonusCount(final String task) {
        return maximumFlow(task);
    }

    private MaximumFlowEdge findFlowEdgeOrNull(HashMap<String, HashMap<String, MaximumFlowEdge>> flowEdges, String fromTitle, String toTitle) {
        HashMap<String, MaximumFlowEdge> edges = flowEdges.get(fromTitle);
        return edges.get(toTitle);
    }

    private int maximumFlow(final String sourceTaskTitle) {
        final Task source = this.tasks.get(sourceTaskTitle);

        LinkedList<Task> leafTasks = new LinkedList<>();

        final HashMap<String, HashMap<String, MaximumFlowEdge>> flowEdges = new HashMap<>(this.tasks.size() + 1);
        final HashMap<String, HashMap<String, MaximumFlowEdge>> transposeFlowEdges = new HashMap<>(this.tasks.size() + 1);

        {
            for (Task task : this.tasks.values()) {
                String title = task.getTitle();
                flowEdges.put(title, new HashMap<>());
                transposeFlowEdges.put(title, new HashMap<>());
            }

            boolean[] isVisited = new boolean[this.tasks.size()];

            LinkedList<Task> taskQueue = new LinkedList<>();
            taskQueue.addLast(source);
            isVisited[this.taskIndexes.get(source.getTitle())] = true;

            while (!taskQueue.isEmpty()) {
                Task queuedTask = taskQueue.removeFirst();
                String title = queuedTask.getTitle();

                List<Task> predecessors = queuedTask.getPredecessors();
                if (predecessors.isEmpty()) {
                    leafTasks.add(queuedTask);
                } else {
                    for (Task predecessor : predecessors) {
                        String predecessorTitle = predecessor.getTitle();
                        int taskIndex = this.taskIndexes.get(predecessor.getTitle());

                        flowEdges.get(title).put(predecessorTitle, new MaximumFlowEdge(queuedTask, predecessor));
                        transposeFlowEdges.get(predecessorTitle).put(title, new MaximumFlowEdge(predecessor, queuedTask));

                        if (!isVisited[taskIndex] && !isCycleTask[taskIndex]) {
                            isVisited[this.taskIndexes.get(predecessor.getTitle())] = true;
                            taskQueue.addLast(predecessor);
                        }
                    }
                }
            }
        }

        final String SINK_TASK_TITLE = "TempTask";
        int result = 0;

        Task sinkTask;//최대 유량을 구하기 위한 임시 Task(시작과 목적지를 하나로 합치기 위함)
        {
            sinkTask = new Task(SINK_TASK_TITLE, Integer.MAX_VALUE);//가상의 Task는 용량이 무제한(기존 목적지들의 estimate가 알아서 용량 조절)
            this.taskIndexes.put(SINK_TASK_TITLE, this.taskIndexes.size());

            HashMap<String, MaximumFlowEdge> tempTaskFlowEdges = new HashMap<>();
            transposeFlowEdges.put(sinkTask.getTitle(), tempTaskFlowEdges);
            for (Task leafTask : leafTasks) {
                sinkTask.addPredecessor(leafTask);

                flowEdges.get(leafTask.getTitle()).put(sinkTask.getTitle(), new MaximumFlowEdge(leafTask, sinkTask));
                tempTaskFlowEdges.put(leafTask.getTitle(), new MaximumFlowEdge(sinkTask, leafTask));
            }
        }

        int[] nodeFlowDatas = new int[this.taskIndexes.size()]; //노드의 flow 데이터(노드에 연결된 전체 edge의 flow 관리)
        {
            while (true) {
                LinkedList<TraceFlowEdge> bfsTaskQueue = new LinkedList<>(); //bfs 탐색용 큐
                HashMap<TraceFlowEdge, TraceFlowEdge> traceBFS = new HashMap<>();

                boolean[] isVisited = new boolean[this.taskIndexes.size()];

                //시작점
                bfsTaskQueue.add(new TraceFlowEdge(new MaximumFlowEdge(null, source), false));
                isVisited[this.taskIndexes.get(source.getTitle())] = true;

                TraceFlowEdge sinkEdge = null;
                while (!bfsTaskQueue.isEmpty()) {
                    TraceFlowEdge traceFlowEdge = bfsTaskQueue.removeFirst();
                    MaximumFlowEdge queuedFlowEdge = traceFlowEdge.getEdge();
                    Task queuedTask = queuedFlowEdge.getTo();
                    if (queuedTask.equals(sinkTask)) {
                        sinkEdge = traceFlowEdge;
                        break;
                    }

                    HashMap<String, MaximumFlowEdge> transposeEdges = transposeFlowEdges.get(queuedTask.getTitle());
                    for (MaximumFlowEdge edge : transposeEdges.values()) {
                        int flow = edge.getFlow();
                        int remainFlow = -flow;

                        if (remainFlow <= 0) {
                            continue;
                        }

                        TraceFlowEdge newTransposeFlowEdge = new TraceFlowEdge(edge, false);
                        bfsTaskQueue.addLast(newTransposeFlowEdge);
                        traceBFS.put(newTransposeFlowEdge, traceFlowEdge);
                    }

                    {
                        int taskIndex = this.taskIndexes.get(queuedTask.getTitle());
                        int remainCapacity = nodeCapacityDatas[taskIndex] - nodeFlowDatas[taskIndex];

                        //남은 용량이 없는데 역방향 엣지도 아닌 경우는 bfs계산시 정방향 고려x
                        if (remainCapacity <= 0 && !traceFlowEdge.isTranspose()) {
                            continue;
                        }
                    }

                    for (MaximumFlowEdge edge : flowEdges.get(queuedTask.getTitle()).values()) {
                        int toTaskIndex = this.taskIndexes.get(edge.getTo().getTitle());

                        int flow = edge.getFlow();
                        int remainFlow = nodeCapacityDatas[toTaskIndex] - flow;

                        if (remainFlow <= 0) {
                            continue;
                        }

                        if (!isVisited[toTaskIndex]) {
                            TraceFlowEdge newflowEdge = new TraceFlowEdge(edge, false);
                            bfsTaskQueue.addLast(newflowEdge);
                            traceBFS.put(newflowEdge, traceFlowEdge);
                            isVisited[toTaskIndex] = true;
                        }
                    }
                }

                if (sinkEdge == null) {
                    break;
                }

                int amount = Integer.MAX_VALUE;
                {
                    TraceFlowEdge traceEdge = sinkEdge;
                    MaximumFlowEdge edge = traceEdge.getEdge();
                    Task from = edge.getFrom();

                    while (from != null) {
                        if (traceEdge.isTranspose()) {
                            amount = Integer.min(amount, -edge.getFlow());
                        } else {
                            amount = Integer.min(amount, nodeCapacityDatas[this.taskIndexes.get(edge.getTo().getTitle())] - edge.getFlow());

                            if (!traceBFS.get(traceEdge).isTranspose()) {
                                int taskIndex = this.taskIndexes.get(from.getTitle());
                                amount = Math.min(amount, nodeCapacityDatas[taskIndex] - nodeFlowDatas[taskIndex]);
                            }
                        }

                        traceEdge = traceBFS.get(traceEdge);
                        edge = traceEdge.getEdge();
                        from = edge.getFrom();
                    }
                }

                {
                    TraceFlowEdge traceEdge = sinkEdge;
                    MaximumFlowEdge edge = traceEdge.getEdge();
                    Task from = edge.getFrom();

                    while (from != null) {
                        String fromTitle = from.getTitle();
                        String toTitle = edge.getTo().getTitle();

                        if (traceEdge.isTranspose()) {
                            MaximumFlowEdge transposeFlowEdge = findFlowEdgeOrNull(transposeFlowEdges, fromTitle, toTitle);
                            transposeFlowEdge.additionalFlow(amount);

                            MaximumFlowEdge flowEdge = findFlowEdgeOrNull(flowEdges, toTitle, fromTitle);
                            flowEdge.additionalFlow(-amount);
                        } else {
                            MaximumFlowEdge flowEdge = findFlowEdgeOrNull(flowEdges, fromTitle, toTitle);
                            flowEdge.additionalFlow(amount);

                            MaximumFlowEdge transposeFlowEdge = findFlowEdgeOrNull(transposeFlowEdges, toTitle, fromTitle);
                            transposeFlowEdge.additionalFlow(-amount);

                            int fromIndex = this.taskIndexes.get(fromTitle);
                            int nodeFlow = nodeFlowDatas[fromIndex] + amount;
                            nodeFlowDatas[fromIndex] = Math.min(nodeCapacityDatas[fromIndex], nodeFlow);
                        }

                        traceEdge = traceBFS.get(traceEdge);
                        edge = traceEdge.getEdge();
                        from = edge.getFrom();
                    }

                    result += amount;
                }
            }
        }

        //임시로 만들어둔 데이터 삭제
        {
            this.taskIndexes.remove(sinkTask.getTitle());
        }

        return result;
    }
}