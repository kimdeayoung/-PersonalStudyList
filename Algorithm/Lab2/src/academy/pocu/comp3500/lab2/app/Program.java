package academy.pocu.comp3500.lab2.app;

import academy.pocu.comp3500.lab2.LinkedList;
import academy.pocu.comp3500.lab2.datastructure.Node;
import academy.pocu.comp3500.lab2.Queue;
import academy.pocu.comp3500.lab2.Stack;

public class Program {

    public static void main(String[] args) {
        {
            Node root = LinkedList.append(null, 10);

            root = LinkedList.append(root, 11);
            root = LinkedList.append(root, 12);

            assert (root.getData() == 10);

            Node next = root.getNextOrNull();

            assert (next.getData() == 11);

            next = next.getNextOrNull();

            assert (next.getData() == 12);
        }

        {
            Node root = LinkedList.append(null, 10);

            root = LinkedList.prepend(root, 11);

            assert (root.getData() == 11);

            root = LinkedList.prepend(root, 12);

            assert (root.getData() == 12);

            Node next = root.getNextOrNull();

            assert (next.getData() == 11);

            next = next.getNextOrNull();

            assert (next.getData() == 10);
        }

        {
            Node root = LinkedList.append(null, 10);

            root = LinkedList.insertAt(root, 0, 11);

            assert (root.getData() == 11);

            root = LinkedList.insertAt(root, 1, 12);

            assert (root.getData() == 11);

            Node next = root.getNextOrNull();

            assert (next.getData() == 12);

            next = next.getNextOrNull();

            assert (next.getData() == 10);
        }

        {
            Node root = LinkedList.append(null, 10);

            root = LinkedList.append(root, 11);
            root = LinkedList.append(root, 12);
            root = LinkedList.append(root, 13);

            root = LinkedList.removeAt(root, 0);

            assert (root.getData() == 11);

            root = LinkedList.removeAt(root, 1);

            assert (root.getData() == 11);

            Node next = root.getNextOrNull();

            assert (next.getData() == 13);
        }

        {
            Node root = LinkedList.append(null, 10);

            root = LinkedList.append(root, 11);

            int index = LinkedList.getIndexOf(root, 10);

            assert (index == 0);

            index = LinkedList.getIndexOf(root, 11);

            assert (index == 1);
        }

        {
            Node root = LinkedList.append(null, 10);

            root = LinkedList.append(root, 11);

            Node node = LinkedList.getOrNull(root, 0);

            assert (node.getData() == 10);

            node = LinkedList.getOrNull(root, 1);

            assert (node.getData() == 11);
        }

        {
            Node root1 = LinkedList.append(null, 10);

            root1 = LinkedList.append(root1, 11);
            root1 = LinkedList.append(root1, 12);

            Node root2 = LinkedList.append(null, 13);

            root2 = LinkedList.append(root2, 14);
            root2 = LinkedList.append(root2, 15);

            Node newRoot = LinkedList.interleaveOrNull(root1, root2); // newRoot: 10, list: 10 -> 13 -> 11 -> 14 -> 12 -> 15

            assert (newRoot.getData() == 10);

            Node next = newRoot.getNextOrNull();

            assert (next.getData() == 13);

            next = next.getNextOrNull();

            assert (next.getData() == 11);

            next = next.getNextOrNull();

            assert (next.getData() == 14);

            next = next.getNextOrNull();

            assert (next.getData() == 12);

            next = next.getNextOrNull();

            assert (next.getData() == 15);
        }


        {
            Node root = LinkedList.append(null, 10);

            root = LinkedList.append(root, 11);
            root = LinkedList.append(root, 12);
            root = LinkedList.append(root, 13);
            root = LinkedList.append(root, 14);

            root = LinkedList.reverse(root); // root: 14, list: 14 -> 13 -> 12 -> 11 -> 10

            assert (root.getData() == 14);

            Node next = root.getNextOrNull();

            assert (next.getData() == 13);

            next = next.getNextOrNull();

            assert (next.getData() == 12);

            next = next.getNextOrNull();

            assert (next.getData() == 11);

            next = next.getNextOrNull();

            assert (next.getData() == 10);
        }

        {
            Node root = LinkedList.append(null, 12);
            root = LinkedList.append(root, 13);

            root = LinkedList.reverse(root); // root: 13, list: 13 -> 12

            assert (root.getData() == 13);

            Node next = root.getNextOrNull();

            assert (next.getData() == 12);
        }

        {
            Stack stack = new Stack();

            stack.push(20);
            stack.push(21); // stack: 21
            //        20

            int data = stack.pop();

            assert (data == 21);

            data = stack.pop();

            assert (data == 20);
        }

        {
            Stack stack = new Stack();

            stack.push(20); // stack: 20

            assert (stack.peek() == 20);

            stack.push(21); // stack: 21
            //        20

            assert (stack.peek() == 21);
        }

        {
            Stack stack  = new Stack();

            stack.push(20);
            stack.push(21);

            assert (stack.getSize() == 2);
        }

        {
            Queue queue = new Queue();

            queue.enqueue(20);

            assert (queue.peek() == 20);

            queue.enqueue(21);

            assert (queue.peek() == 20);
        }

        {
            Queue queue = new Queue();

            queue.enqueue(20);
            queue.enqueue(21);

            int data = queue.dequeue();

            assert (data == 20);

            data = queue.dequeue();

            assert (data == 21);
        }

        {
            Queue queue = new Queue();

            queue.enqueue(20);
            queue.enqueue(21);

            assert (queue.getSize() == 2);
        }

        testInterleaveEdge2();
        testInterleaveEdge();
        testInvalidInterleave();
    }

    public static void testInterleaveEdge2() {
        Node head1 = LinkedList.append(null, 3);
        Node linked = LinkedList.interleaveOrNull(null, head1);
        assert linked.getData() == 3;

        Node linked2 = LinkedList.interleaveOrNull(head1, null);
        assert linked2.getData() == 3;
    }

    public static void testInterleaveEdge() {
        Node head1 = LinkedList.append(null, 3);
        Node head2 = LinkedList.append(null, 1);
        Node linked = LinkedList.interleaveOrNull(head1, head2);

        head1 = LinkedList.append(null, 3);
        head2 = LinkedList.append(null, 1);
        LinkedList.append(head2, 2);

        linked = LinkedList.interleaveOrNull(head1, head2);

        int[] results = new int[] {3,1,2};
        Node node = linked;
        for (int i : results) {
            assert node.getData() == i;
            node = node.getNextOrNull();
        }

        head1 = LinkedList.append(null, 3);
        head2 = LinkedList.append(null, 1);
        LinkedList.append(head1, 2);

        linked = LinkedList.interleaveOrNull(head1, head2);
    }

    public static void testInvalidInterleave() {
        Node head2 = LinkedList.append(null, 1);
        LinkedList.append(head2, 2);
        LinkedList.append(head2, 3);
        LinkedList.append(head2, 4);
        LinkedList.append(head2, 5);
        LinkedList.append(head2, 6);
        LinkedList.append(head2, 7);
        LinkedList.append(head2, 8);
        LinkedList.append(head2, 9);

        Node linked = LinkedList.interleaveOrNull(null, head2);
        Node node = linked;
        int[] results = new int[]{1,2,3,4,5,6,7,8,9};
        for (int i : results) {
            assert i == node.getData();
            node = node.getNextOrNull();
        }

        Node linked2 = LinkedList.interleaveOrNull(head2, null);
        assert linked2 == head2;
    }

}