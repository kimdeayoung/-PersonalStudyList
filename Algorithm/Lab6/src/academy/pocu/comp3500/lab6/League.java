package academy.pocu.comp3500.lab6;

import academy.pocu.comp3500.lab6.leagueofpocu.Player;

public class League {
    private Node root;
    private int playerCount;

    public League() {
    }

    public League(Player[] players) {
        for (int i = 0; i < players.length; ++i) {
            join(players[i]);
        }
    }

    public Player findMatchOrNull(final Player player) {
        Node playerNode = findPlayerNode(root, player);
        if (playerNode == null) {
            return null;
        }

        Player matchPlayer = null;
        int matchPlayerOffset = Integer.MAX_VALUE;

        {
            Player parentNodePlayer = findMatchPlayerByParentNodesRecursive(root, player, matchPlayer, matchPlayerOffset);
            if (parentNodePlayer != null) {
                matchPlayer = parentNodePlayer;
                matchPlayerOffset = Math.abs(player.getRating() - parentNodePlayer.getRating());
            }
        }

        {
            Player predecessorPlayer = checkSetableMatchPlayer(player, findInorderPredecessor(playerNode), matchPlayer, matchPlayerOffset);
            if (predecessorPlayer != null) {
                matchPlayer = predecessorPlayer;
                matchPlayerOffset = Math.abs(player.getRating() - predecessorPlayer.getRating());
            }
        }

        {
            Player successorPlayer = checkSetableMatchPlayer(player, findInorderSuccessor(playerNode), matchPlayer, matchPlayerOffset);
            if (successorPlayer != null) {
                matchPlayer = successorPlayer;
            }
        }
        return matchPlayer;
    }

    private Player checkSetableMatchPlayer(final Player target, final Node cmpNode, final Player currentMatchPlayer, final int matchPlayerOffset) {
        if (cmpNode == null) {
            return null;
        }

        Player cmpPlayer = cmpNode.getPlayer();
        if (isEqualPlayer(target, cmpPlayer)) {
            return null;
        }

        int offset = Math.abs(target.getRating() - cmpPlayer.getRating());
        if (matchPlayerOffset == offset) {
            return currentMatchPlayer.getRating() > cmpPlayer.getRating() ? null : cmpPlayer;
        } else if (matchPlayerOffset > offset) {
            return cmpPlayer;
        }
        return null;
    }

    public Player[] getTop(final int count) {
        if (root == null) {
            return new Player[0];
        }

        int playersCount = Integer.min(playerCount, count);
        Player[] players = new Player[playersCount];
        IntValue playerIndex = new IntValue(0);
        reverseInorderTraversalRecursive(root, players, playerIndex);

        return players;
    }

    public Player[] getBottom(final int count) {
        if (root == null) {
            return new Player[0];
        }

        int playersCount = Integer.min(playerCount, count);
        Player[] players = new Player[playersCount];
        IntValue playerIndex = new IntValue(0);
        inorderTraversalRecursive(root, players, playerIndex);

        return players;
    }

    private void inorderTraversalRecursive(final Node node, Player[] players, IntValue playerIndex) {
        if (node == null) {
            return;
        }

        inorderTraversalRecursive(node.getLeft(), players, playerIndex);
        int index = playerIndex.getValue();
        if (players.length > index) {
            playerIndex.increase();
            players[index] = node.getPlayer();
        } else {
            return;
        }
        inorderTraversalRecursive(node.getRight(), players, playerIndex);
    }

    private void reverseInorderTraversalRecursive(final Node node, Player[] players, IntValue playerIndex) {
        if (node == null) {
            return;
        }

        reverseInorderTraversalRecursive(node.getRight(), players, playerIndex);
        int index = playerIndex.getValue();
        if (players.length > index) {
            playerIndex.increase();
            players[index] = node.getPlayer();
        } else {
            return;
        }
        reverseInorderTraversalRecursive(node.getLeft(), players, playerIndex);
    }

    public boolean join(final Player player) {
        if (root == null) {
            root = new Node(player, null);
            ++playerCount;
            return true;
        }

        boolean isJoin = joinPlayerNodeRecurisve(root, player);
        if (isJoin) {
            ++playerCount;
        }

        return isJoin;
    }

    private boolean joinPlayerNodeRecurisve(final Node node, final Player target) {
        Player player = node.getPlayer();
        if (isEqualPlayer(player, target)) {
            return false;
        }

        if (player.getRating() > target.getRating()) {
            if (node.getLeft() == null) {
                node.setLeft(new Node(target, node));
                return true;
            }

            return joinPlayerNodeRecurisve(node.getLeft(), target);
        }

        if (node.getRight() == null) {
            node.setRight(new Node(target, node));
            return true;
        }
        return joinPlayerNodeRecurisve(node.getRight(), target);
    }

    public boolean leave(final Player player) {
        Node playerNode = findPlayerNode(root, player);
        if (playerNode == null) {
            return false;
        }

        Node leftNode = playerNode.getLeft();
        Node rightNode = playerNode.getRight();
        Node parentNode = playerNode.getParent();

        if (leftNode == null && rightNode == null) {
            playerNode.clear();
        } else if ((leftNode != null) && (rightNode != null)) {
            Node successor = findInorderSuccessor(playerNode);

            if (successor == playerNode.getRight()) {
                successor.setParent(parentNode);
                successor.setLeft(playerNode.getLeft());
                leftNode.setParent(successor);
                if (parentNode != null) {
                    parentNode.swapChild(playerNode, successor);
                }
                playerNode.clear();

                if (root == playerNode) {
                    root = successor;
                }
            } else {
                Player temp = playerNode.getPlayer();
                playerNode.setPlayer(successor.getPlayer());
                successor.setPlayer(temp);

                if (successor.getRight() != null) {
                    Node successorParent = successor.getParent();
                    Node successorRight = successor.getRight();

                    successorParent.swapChild(successor, successorRight);
                    successorRight.setParent(successorParent);
                }
                successor.clear();
            }
        } else {
            Node childNode = leftNode == null ? rightNode : leftNode;

            if (childNode.hasChild()) {
                childNode.setParent(parentNode);
                if (parentNode != null) {
                    parentNode.swapChild(playerNode, childNode);
                }
                playerNode.clear();

                if (root == playerNode) {
                    root = childNode;
                }
            } else {
                Player temp = playerNode.getPlayer();
                playerNode.setPlayer(childNode.getPlayer());
                childNode.setPlayer(temp);

                childNode.clear();
            }
        }

        if (--playerCount == 0) {
            root = null;
        }
        return true;
    }

    private Node findPlayerNode(final Node node, final Player target) {
        if (node == null) {
            return null;
        }

        Player player = node.getPlayer();
        if (isEqualPlayer(player, target)) {
            return node;
        }

        if (player.getRating() > target.getRating()) {
            return findPlayerNode(node.getLeft(), target);
        }

        return findPlayerNode(node.getRight(), target);
    }

    private Player findMatchPlayerByParentNodesRecursive(final Node node, final Player target, final Player currentMatchPlayer, final int matchPlayerOffset) {
        if (node == null) {
            return null;
        }

        Player player = node.getPlayer();
        if (isEqualPlayer(player, target)) {
            return currentMatchPlayer;
        }

        Player matchPlayer = checkSetableMatchPlayer(target, node, currentMatchPlayer, matchPlayerOffset);
        int offset = Math.abs(target.getRating() - player.getRating());
        if (matchPlayer == null) {
            matchPlayer = currentMatchPlayer;
            offset = matchPlayerOffset;
        }

        if (player.getRating() > target.getRating()) {
            return findMatchPlayerByParentNodesRecursive(node.getLeft(), target, matchPlayer, offset);
        }

        return findMatchPlayerByParentNodesRecursive(node.getRight(), target, matchPlayer, offset);
    }

    private Node findInorderSuccessor(final Node startNode) {
        if (startNode.getRight() == null) {
            return null;
        }

        return findInorderSuccessorRecursive(startNode.getRight());
    }

    private Node findInorderSuccessorRecursive(final Node node) {
        if (node.getLeft() == null) {
            return node;
        }

        return findInorderSuccessorRecursive(node.getLeft());
    }

    private Node findInorderPredecessor(final Node startNode) {
        if (startNode.getLeft() == null) {
            return null;
        }

        return findInorderPredecessorRecursive(startNode.getLeft());
    }

    private Node findInorderPredecessorRecursive(final Node node) {
        if (node.getRight() == null) {
            return node;
        }

        return findInorderPredecessorRecursive(node.getRight());
    }

    private boolean isEqualPlayer(final Player player1, final Player player2) {
        if (player1.getId() == player2.getId()) {
            if (player1.getRating() == player2.getRating()) {
                return true;
            }
        }
        return false;
    }
}
