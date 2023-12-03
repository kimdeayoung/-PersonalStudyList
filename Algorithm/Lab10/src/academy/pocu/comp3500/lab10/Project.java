package academy.pocu.comp3500.lab10;

import academy.pocu.comp3500.lab10.project.Task;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.HashSet;
import java.util.List;

public class Project {
    public static List<String> findSchedule(final Task[] tasks, final boolean includeMaintenance) {
        HashSet<Task> isVisited = new HashSet<>();
        LinkedList<String> result = new LinkedList<String>();

        HashMap<String, HashSet<String>> taskTitles = new HashMap<>(tasks.length);
        HashMap<String, Task> transposeTaskHash = new HashMap<>(tasks.length);
        {
            for (Task task : tasks) {
                transposeTaskHash.put(task.getTitle(), new Task(task.getTitle(), task.getEstimate()));

                taskTitles.put(task.getTitle(), new HashSet<>());
            }

            for (Task rawTask : tasks) {
                for (Task neighborTask : rawTask.getPredecessors()) {
                    Task task = transposeTaskHash.get(neighborTask.getTitle());
                    Task transposeTask = transposeTaskHash.get(rawTask.getTitle());
                    task.addPredecessor(transposeTask);

                    HashSet<String> set = taskTitles.get(transposeTask.getTitle());
                    set.add(neighborTask.getTitle());
                }
            }
        }


        LinkedList<Task> reverseTask = new LinkedList<>();
        {
            for (Task task : tasks) {
                if (isVisited.contains(task)) {
                    continue;
                }

                getReverseTaskRecursive(task, reverseTask, isVisited);
            }
        }

        {
            isVisited.clear();
            ArrayList<Task> scc = new ArrayList<>();

            for (Task task : reverseTask) {
                Task transposeTask = transposeTaskHash.get(task.getTitle());
                if (isVisited.contains(transposeTask)) {
                    continue;
                }

                findCycleTaskDFSRecursive(transposeTask, scc, isVisited);
                if (scc.size() == 1) {
                    result.addFirst(scc.get(0).getTitle());
                } else {
                    if (includeMaintenance) {
                        includeMaintenance(scc, taskTitles, result);
                    }
                }

                scc.clear();
            }
        }

        return result;
    }

    private static void findCycleTaskDFSRecursive(final Task task, ArrayList<Task> scc, final HashSet<Task> isVisited) {
        if (isVisited.contains(task)) {
            return;
        }

        isVisited.add(task);

        for (Task neighborTask : task.getPredecessors()) {
            if (isVisited.contains(neighborTask)) {
                continue;
            }

            findCycleTaskDFSRecursive(neighborTask, scc, isVisited);
        }
        scc.add(task);
    }

    private static void getReverseTaskRecursive(final Task task, final LinkedList<Task> reverseTask, final HashSet<Task> isVisited) {
        if (!isVisited.contains(task)) {
            isVisited.add(task);
            for (Task predecessorTask : task.getPredecessors()) {
                getReverseTaskRecursive(predecessorTask, reverseTask, isVisited);
            }

            reverseTask.addFirst(task);
        }
    }

    private static void includeMaintenance(ArrayList<Task> scc, HashMap<String, HashSet<String>> taskTitles, LinkedList<String> result) {
        Task dfsStartTask = null;

        for (Task sccTask : scc) {
            HashSet<String> taskTitle = taskTitles.get(sccTask.getTitle());
            for (Task search : scc) {
                taskTitle.remove(search.getTitle());
            }

            if (!taskTitle.isEmpty()) {
                dfsStartTask = sccTask;
                break;
            }
        }

        if (dfsStartTask == null) {
            for (Task sccTask : scc) {
                result.addFirst(sccTask.getTitle());
            }
        } else {
            HashSet<Task> visited = new HashSet<>();
            addResultToPostorderRecursive(dfsStartTask, result, visited);
        }
    }

    private static void addResultToPostorderRecursive(final Task task, final LinkedList<String> result, final HashSet<Task> isVisited) {
        if (!isVisited.contains(task)) {
            isVisited.add(task);
            for (Task predecessorTask : task.getPredecessors()) {
                addResultToPostorderRecursive(predecessorTask, result, isVisited);
            }

            result.addFirst(task.getTitle());
        }
    }
}