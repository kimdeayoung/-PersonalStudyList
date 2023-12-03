package academy.pocu.comp3500.lab7;

import java.util.ArrayList;
import java.util.Stack;

public class Decryptor {
    private Node root;

    private final static int ALPHABET_COUNT = 26;

    public Decryptor(final String[] codeWords) {
        this.root = new Node();

        if (codeWords == null) {
            return;
        }

        for (String word : codeWords) {
            if (word.isEmpty()) {
                continue;
            }
            Node node = root;

            for (int i = 0; i < word.length(); ++i) {
                char ch = (char) (word.charAt(i) | 32);
                if (node.isAddable(ch)) {
                    node = node.addChild(ch, (i + 1));
                } else {
                    node = node.getChild(ch);
                }
            }

            node.setWordData(word.toLowerCase());
        }
    }

    public String[] findCandidates(final String word) {
        if (word == null || word.isEmpty()) {
            return new String[]{};
        }

        ArrayList<String> result = new ArrayList<>();
        Stack<Node> restoreStack = new Stack<>();

        int[] wordCount = new int[ALPHABET_COUNT];
        int wordLength = word.length();
        for (int i = 0; i < wordLength; ++i) {
            ++wordCount[getWordsCountIndex(word.charAt(i))];
        }

        Stack<Node> stack = new Stack<>();
        pushDFSStack(stack, root, wordCount);

        while (!stack.isEmpty()) {
            Node node = stack.pop();

            if (!restoreStack.isEmpty()) {
                while (node.getParent() != restoreStack.peek()) {
                    Node restoreNode = restoreStack.pop();
                    ++wordCount[getWordsCountIndex(restoreNode.getLatter())];
                    ++wordLength;

                    if (restoreStack.isEmpty()) {
                        break;
                    }
                }
            }

            restoreStack.push(node);
            --wordCount[getWordsCountIndex(node.getLatter())];
            --wordLength;

            boolean needPushDFSStack = true;
            if (node.getDepth() == word.length()) {
                if (wordLength == 0) {
                    result.addAll(node.getWords());
                }
                needPushDFSStack = false;
            }

            if (needPushDFSStack) {
                pushDFSStack(stack, node, wordCount);
            }
        }

        String[] candidates = new String[result.size()];
        for (int i = 0; i < result.size(); ++i) {
            candidates[i] = result.get(i);
        }
        return candidates;
    }

    private void pushDFSStack(Stack<Node> stack, Node node, int[] wordCount) {
        ArrayList<Integer> childIndexes = node.getChildIndexes();

        for (int i = 0; i < childIndexes.size(); ++i) {
            Node child = node.getChild(childIndexes.get(i));

            if (wordCount[getWordsCountIndex(child.getLatter())] > 0) {
                stack.push(child);
            }
        }
    }

    private int getWordsCountIndex(char key) {
        return ((key | 32) - 97);
    }
}