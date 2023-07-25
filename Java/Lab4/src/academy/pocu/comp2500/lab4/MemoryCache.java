package academy.pocu.comp2500.lab4;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.Map;

public class MemoryCache {
    private static HashMap<String, MemoryCache> instance = new HashMap<>();
    private static LinkedHashSet<String> cashEditAt = new LinkedHashSet<>();

    private static int maxInstanceCount = -1;

    private String type;

    private EvictionPolicy evictionPolicy;

    private HashMap<String, String> entry;
    private LinkedList<String> entryCreateAt;
    private LinkedHashSet<String> entryEditAt;

    private int maxEntryCount;

    private MemoryCache(String type) {
        this.type = type;
        this.evictionPolicy = EvictionPolicy.LEAST_RECENTLY_USED;
        this.entry = new HashMap<>();
        this.entryCreateAt = new LinkedList<>();
        this.entryEditAt = new LinkedHashSet<>();
        this.maxEntryCount = -1;
    }

    public static MemoryCache getInstance(String key) {
        MemoryCache cache = instance.getOrDefault(key, null);
        if (cache == null) {
            cache = new MemoryCache(key);
            instance.put(key, cache);
        }
        editCashData(cache.type);

        if (maxInstanceCount != -1) {
            if (instance.size() > maxInstanceCount) {
                removeInstanceByLRU();
            }
        }

        return cache;
    }

    public static void clear() {
        instance.clear();
        cashEditAt.clear();
    }

    public static void setMaxInstanceCount(int count) {
        maxInstanceCount = count;

        if (maxInstanceCount != -1) {
            if (instance.size() > maxInstanceCount) {
                removeInstanceByLRU();
            }
        }
    }

    private static void removeInstanceByLRU() {
        int removeCount = cashEditAt.size() - maxInstanceCount;

        for (int i = 0; i < removeCount; ++i) {
            String key = cashEditAt.iterator().next();

            instance.remove(key);
            cashEditAt.remove(key);
        }
    }

    private static void editCashData(String key) {
        cashEditAt.remove(key);
        cashEditAt.add(key);
    }

    public void setEvictionPolicy(EvictionPolicy evictionPolicy) {
        this.evictionPolicy = evictionPolicy;

        editCashData(type);
    }

    public void addEntry(String key, String value) {
        if (this.entry.containsKey(key) == false) {
            if (this.maxEntryCount != -1) {
                if (this.entry.size() >= this.maxEntryCount) {
                    removeEntry();
                }
            }
            this.entryCreateAt.add(key);
        }

        this.entry.put(key, value);
        this.entryEditAt.remove(key);
        this.entryEditAt.add(key);

        editCashData(type);
    }

    public String getEntryOrNull(String key) {
        String result = this.entry.getOrDefault(key, null);
        if (result != null) {
            this.entryEditAt.remove(key);
            this.entryEditAt.add(key);
        }

        editCashData(type);
        return result;
    }

    public void setMaxEntryCount(int count) {
        this.maxEntryCount = count;

        if (this.maxEntryCount != -1) {
            if (this.entry.size() > this.maxEntryCount) {
                removeEntry();
            }
        }
        editCashData(type);
    }

    private void removeEntry() {
        int removeCount = this.entry.size() - this.maxEntryCount;
        if (removeCount <= 0) {
            removeCount = 1;
        }

        switch (evictionPolicy) {
            case FIRST_IN_FIRST_OUT:
                for (int i = 0; i < removeCount; ++i) {
                    String key = this.entryCreateAt.removeFirst();
                    removeEntryData(key);
                }
                break;
            case LAST_IN_FIRST_OUT:
                for (int i = 0; i < removeCount; ++i) {
                    String key = this.entryCreateAt.removeLast();
                    removeEntryData(key);
                }
                break;
            case LEAST_RECENTLY_USED:
                for (int i = 0; i < removeCount; ++i) {
                    String key = this.entryEditAt.iterator().next();
                    removeEntryData(key);
                    this.entryCreateAt.remove(key);
                }
                break;
        }
    }

    private void removeEntryData(String key) {
        this.entry.remove(key);
        this.entryEditAt.remove(key);
    }
}
