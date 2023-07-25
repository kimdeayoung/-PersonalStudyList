package academy.pocu.comp2500.lab4.app;

import academy.pocu.comp2500.lab4.EvictionPolicy;
import academy.pocu.comp2500.lab4.MemoryCache;

import java.util.ArrayList;

public class Program {

    public static void main(String[] args) {
        TestCode1();
        TestCode2();
    }

    static void TestCode1() {
        {
            MemoryCache memCacheA = MemoryCache.getInstance("A");

            MemoryCache memCacheB = MemoryCache.getInstance("B");
            MemoryCache memCacheC = MemoryCache.getInstance("C");

            assert memCacheA == MemoryCache.getInstance("A");
            assert memCacheB == MemoryCache.getInstance("B");
            assert memCacheC == MemoryCache.getInstance("C");

            MemoryCache.setMaxInstanceCount(3);

            MemoryCache memCacheD = MemoryCache.getInstance("D");

            assert memCacheA != MemoryCache.getInstance("A");
            assert memCacheC == MemoryCache.getInstance("C");
            assert memCacheB != MemoryCache.getInstance("B");
            assert memCacheD != MemoryCache.getInstance("D");
        }

        {
            MemoryCache memCache = MemoryCache.getInstance("A");
            memCache.addEntry("key1", "value1");
            memCache.addEntry("key2", "value2");
            memCache.addEntry("key3", "value3");
            memCache.addEntry("key4", "value4");
            memCache.addEntry("key5", "value5");

            memCache.setMaxEntryCount(3);

            assert memCache.getEntryOrNull("key1") == null;
            assert memCache.getEntryOrNull("key2") == null;
            assert memCache.getEntryOrNull("key3") != null;
            assert memCache.getEntryOrNull("key4") != null;
            assert memCache.getEntryOrNull("key5") != null;

            memCache.addEntry("key6", "value6");

            assert memCache.getEntryOrNull("key3") == null;

            memCache.getEntryOrNull("key4");
            memCache.getEntryOrNull("key5");
            memCache.getEntryOrNull("key4");

            memCache.addEntry("key7", "value7");

            assert memCache.getEntryOrNull("key6") == null;

            memCache.addEntry("key5", "value5_updated");
            memCache.addEntry("key8", "value8");

            assert memCache.getEntryOrNull("key4") == null;

            assert memCache.getEntryOrNull("key5").equals("value5_updated");

            memCache.setEvictionPolicy(EvictionPolicy.FIRST_IN_FIRST_OUT);

            memCache.addEntry("key9", "value9");
            assert memCache.getEntryOrNull("key5") == null;

            memCache.addEntry("key10", "value10");
            assert memCache.getEntryOrNull("key7") == null;

            memCache.setMaxEntryCount(1);

            assert memCache.getEntryOrNull("key8") == null;
            assert memCache.getEntryOrNull("key9") == null;
            assert memCache.getEntryOrNull("key10").equals("value10");

            memCache.setMaxEntryCount(5);
            memCache.setEvictionPolicy(EvictionPolicy.LAST_IN_FIRST_OUT);

            memCache.addEntry("key11", "value11");
            memCache.addEntry("key12", "value12");
            memCache.addEntry("key13", "value13");
            memCache.addEntry("key14", "value14");

            assert memCache.getEntryOrNull("key10") != null;
            assert memCache.getEntryOrNull("key11") != null;
            assert memCache.getEntryOrNull("key12") != null;
            assert memCache.getEntryOrNull("key13") != null;
            assert memCache.getEntryOrNull("key14") != null;

            memCache.addEntry("key15", "value15");

            assert memCache.getEntryOrNull("key14") == null;

            assert memCache.getEntryOrNull("key13") != null;
            assert memCache.getEntryOrNull("key11") != null;
            assert memCache.getEntryOrNull("key12") != null;
            assert memCache.getEntryOrNull("key10") != null;
            assert memCache.getEntryOrNull("key15") != null;

            memCache.setEvictionPolicy(EvictionPolicy.LEAST_RECENTLY_USED);

            memCache.addEntry("key16", "value16");

            assert memCache.getEntryOrNull("key13") == null;
            assert memCache.getEntryOrNull("key10") != null;
            assert memCache.getEntryOrNull("key11") != null;
            assert memCache.getEntryOrNull("key12") != null;
            assert memCache.getEntryOrNull("key15") != null;
            assert memCache.getEntryOrNull("key16") != null;
        }
    }

    static void TestCode2() {
        int maxN = 100000;
        int count = 70000;
        int step = 100000;

        System.out.printf("===================================\n");
        System.out.printf("Time complexity test(MAX N: %d)\n", maxN);
        System.out.printf("===================================\n");
        ArrayList<String> strings = new ArrayList<>(maxN);
        for (int i = 0; i < maxN; i++) {
            strings.add(Integer.toString(i));
        }

        // initialization for instance test
        MemoryCache.clear();
        MemoryCache.setMaxInstanceCount(count);

        // test getInstance()
        System.out.printf("\ngetInstance() test\n");
        for (int n = 0; n < maxN; n += step) {
            System.out.printf("%6d ~ %6d: ", n, n + step - 1);

            long start = System.currentTimeMillis();
            for (int i = n; i < n + step; i++) {
                MemoryCache.getInstance(strings.get(i));
            }
            long end = System.currentTimeMillis();

            System.out.printf("%dms\n", end - start);
        }

        // initialization for entry test
        MemoryCache.clear();
        MemoryCache.setMaxInstanceCount(3);

        MemoryCache memCacheFifo = MemoryCache.getInstance("FIFO");
        MemoryCache memCacheFilo = MemoryCache.getInstance("FILO");
        MemoryCache memCacheLru = MemoryCache.getInstance("LRU");

        memCacheFifo.setEvictionPolicy(EvictionPolicy.FIRST_IN_FIRST_OUT);
        memCacheFilo.setEvictionPolicy(EvictionPolicy.LAST_IN_FIRST_OUT);
        memCacheLru.setEvictionPolicy(EvictionPolicy.LEAST_RECENTLY_USED);

        memCacheFifo.setMaxEntryCount(count);
        memCacheFilo.setMaxEntryCount(count);
        memCacheLru.setMaxEntryCount(count);

        // test addEntry()
        System.out.printf("\naddEntry() test [FIFO / FILO / LRU]\n");
        for (int n = 0; n < maxN; n += step) {
            System.out.printf("%6d ~ %6d: ", n, n + step - 1);

            long startFifo = System.currentTimeMillis();
            for (int i = n; i < n + step; i++) {
                memCacheFifo.addEntry(strings.get(i), strings.get(i));
            }
            long endFifo = System.currentTimeMillis();

            long startFilo = System.currentTimeMillis();
            for (int i = n; i < n + step; i++) {
                memCacheFilo.addEntry(strings.get(i), strings.get(i));
            }
            long endFilo = System.currentTimeMillis();

            long startLru = System.currentTimeMillis();
            for (int i = n; i < n + step; i++) {
                memCacheLru.addEntry(strings.get(i), strings.get(i));
            }
            long endLru = System.currentTimeMillis();

            System.out.printf("%dms / %dms / %dms\n", endFifo - startFifo, endFilo - startFilo, endLru - startLru);
        }

        // test getEntryOrNull()
        System.out.printf("\ngetEntryOrNull() test [FIFO / FILO / LRU]\n");
        for (int n = 0; n < maxN; n += step) {
            System.out.printf("%6d ~ %6d: ", n, n + step - 1);

            long startFifo = System.currentTimeMillis();
            for (int i = n; i < n + step; i++) {
                memCacheFifo.getEntryOrNull(strings.get(i));
            }
            long endFifo = System.currentTimeMillis();

            long startFilo = System.currentTimeMillis();
            for (int i = n; i < n + step; i++) {
                memCacheFilo.getEntryOrNull(strings.get(i));
            }
            long endFilo = System.currentTimeMillis();

            long startLru = System.currentTimeMillis();
            for (int i = n; i < n + step; i++) {
                memCacheLru.getEntryOrNull(strings.get(i));
            }
            long endLru = System.currentTimeMillis();

            System.out.printf("%dms / %dms / %dms\n", endFifo - startFifo, endFilo - startFilo, endLru - startLru);
        }
    }


}
