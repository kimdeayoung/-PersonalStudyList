package academy.pocu.comp3500.assignment1;

import academy.pocu.comp3500.assignment1.pba.Player;
import academy.pocu.comp3500.assignment1.pba.GameStat;

public final class PocuBasketballAssociation {
    private PocuBasketballAssociation() {
    }

    public static void processGameStats(final GameStat[] gameStats, final Player[] outPlayers) {
        if (gameStats.length < 1) {
            return;
        }

        quickSortGameStatsRecursive(gameStats, 0, gameStats.length - 1);

        int organizeIndex = 0;
        int infoCount = 1;
        String name = gameStats[0].getPlayerName();

        int point = gameStats[0].getPoints();
        int pass = gameStats[0].getNumPasses();
        int assist = gameStats[0].getAssists();
        int goalCount = gameStats[0].getGoals();
        int goalAttemptsCount = gameStats[0].getGoalAttempts();

        for (int i = 1; i < gameStats.length; ++i) {
            GameStat gameStat = gameStats[i];
            if (gameStat.getGame() < 0) {
                continue;
            }

            if (gameStat.getPlayerName().equals(name)) {
                ++infoCount;

                point += gameStat.getPoints();
                pass += gameStat.getNumPasses();
                assist += gameStat.getAssists();
                goalCount += gameStat.getGoals();
                goalAttemptsCount += gameStat.getGoalAttempts();
            } else {
                Player player = outPlayers[organizeIndex++];
                player.setName(gameStats[i - 1].getPlayerName());
                player.setPointsPerGame(point / infoCount);
                player.setAssistsPerGame(assist / infoCount);
                player.setPassesPerGame(pass / infoCount);
                player.setShootingPercentage(100 * goalCount / goalAttemptsCount);

                name = gameStat.getPlayerName();
                point = gameStat.getPoints();
                assist = gameStat.getAssists();
                pass = gameStat.getNumPasses();
                goalCount = gameStat.getGoals();
                goalAttemptsCount = gameStat.getGoalAttempts();
                infoCount = 1;
            }
        }

        Player player = outPlayers[organizeIndex];
        player.setName(gameStats[gameStats.length - 1].getPlayerName());
        player.setPointsPerGame(point / infoCount);
        player.setAssistsPerGame(assist / infoCount);
        player.setPassesPerGame(pass / infoCount);
        player.setShootingPercentage(100 * goalCount / goalAttemptsCount);
    }

    private static void quickSortGameStatsRecursive(final GameStat[] gameStats, int left, int right) {
        if (left >= right) {
            return;
        }

        int leftIndex = left;
        String pivotValue = gameStats[right].getPlayerName();
        for (int i = left; i < right; ++i) {
            if (gameStats[i].getPlayerName().compareTo(pivotValue) < 0) {
                GameStat temp = gameStats[leftIndex];
                gameStats[leftIndex] = gameStats[i];
                gameStats[i] = temp;

                ++leftIndex;
            }
        }

        {
            GameStat temp = gameStats[leftIndex];
            gameStats[leftIndex] = gameStats[right];
            gameStats[right] = temp;
        }

        quickSortGameStatsRecursive(gameStats, left, leftIndex - 1);
        quickSortGameStatsRecursive(gameStats, leftIndex + 1, right);
    }

    public static Player findPlayerPointsPerGame(final Player[] players, int targetPoints) {
        int findIndex = findPlayerPointsPerRecursive(players, targetPoints, 0, players.length - 1);

        int scoreDifference = Math.abs(targetPoints - players[findIndex].getPointsPerGame());
        if (scoreDifference != 0) {
            int highIndex = Math.min(findIndex + 1, players.length - 1);
            int highDiff = Math.abs(targetPoints - players[highIndex].getPointsPerGame());

            int minIndex = Math.max(findIndex - 1, 0);
            int lowDiff = Math.abs(targetPoints - players[minIndex].getPointsPerGame());

            if (highDiff <= lowDiff) {
                findIndex = scoreDifference >= highDiff ? highIndex : findIndex;
            } else {
                findIndex = scoreDifference > lowDiff ? minIndex : findIndex;
            }
        }

        return players[findIndex];
    }

    public static int findPlayerPointsPerRecursive(final Player[] players, int targetPoints, int leftIndex, int rightIndex) {
        int index = (leftIndex + rightIndex) / 2;
        Player player = players[index];

        if (player.getPointsPerGame() == targetPoints) {
            return index;
        } else if (leftIndex >= rightIndex) {
            return index;
        }

        if (player.getPointsPerGame() < targetPoints) {
            return findPlayerPointsPerRecursive(players, targetPoints, index + 1, rightIndex);
        } else {
            return findPlayerPointsPerRecursive(players, targetPoints, leftIndex, index - 1);
        }
    }

    public static Player findPlayerShootingPercentage(final Player[] players, int targetShootingPercentage) {
        int findIndex = findPlayerShootingPerRecursive(players, targetShootingPercentage, 0, players.length - 1);
        int scoreDifference = Math.abs(targetShootingPercentage - players[findIndex].getShootingPercentage());
        if (scoreDifference != 0) {
            int highIndex = Math.min(findIndex + 1, players.length - 1);
            int highDiff = Math.abs(targetShootingPercentage - players[highIndex].getShootingPercentage());

            int minIndex = Math.max(findIndex - 1, 0);
            int lowDiff = Math.abs(targetShootingPercentage - players[minIndex].getShootingPercentage());

            if (highDiff <= lowDiff) {
                findIndex = scoreDifference >= highDiff ? highIndex : findIndex;
            } else {
                findIndex = scoreDifference > lowDiff ? minIndex : findIndex;
            }
        }

        return players[findIndex];
    }

    public static int findPlayerShootingPerRecursive(final Player[] players, int targetShootingPercentage, int leftIndex, int rightIndex) {
        int index = (leftIndex + rightIndex) / 2;
        Player player = players[index];

        if (player.getShootingPercentage() == targetShootingPercentage) {
            return index;
        } else if (leftIndex >= rightIndex) {
            return index;
        }

        if (player.getShootingPercentage() < targetShootingPercentage) {
            return findPlayerShootingPerRecursive(players, targetShootingPercentage, index + 1, rightIndex);
        } else {
            return findPlayerShootingPerRecursive(players, targetShootingPercentage, leftIndex, index - 1);
        }
    }

    private static void sortAscendingPlayersPassRecursive(final Player[] players, int leftIndex, int rightIndex) {
        if (leftIndex >= rightIndex) {
            return;
        }

        int pivotValue = players[rightIndex].getPassesPerGame();
        int left = leftIndex;
        for (int i = left; i < rightIndex; ++i) {
            if (players[i].getPassesPerGame() < pivotValue) {
                Player temp = players[i];
                players[i] = players[left];
                players[left++] = temp;
            }
        }

        {
            Player temp = players[rightIndex];
            players[rightIndex] = players[left];
            players[left] = temp;
        }
        sortAscendingPlayersPassRecursive(players, leftIndex, left - 1);
        sortAscendingPlayersPassRecursive(players, left + 1, rightIndex);
    }

    private static void sortDescendingPlayersPassRecursive(final Player[] players, int leftIndex, int rightIndex) {
        if (leftIndex >= rightIndex) {
            return;
        }

        int pivotValue = players[rightIndex].getPassesPerGame();
        int left = leftIndex;
        for (int i = left; i < rightIndex; ++i) {
            if (players[i].getPassesPerGame() > pivotValue) {
                Player temp = players[i];
                players[i] = players[left];
                players[left++] = temp;
            }
        }

        {
            Player temp = players[rightIndex];
            players[rightIndex] = players[left];
            players[left] = temp;
        }
        sortDescendingPlayersPassRecursive(players, leftIndex, left - 1);
        sortDescendingPlayersPassRecursive(players, left + 1, rightIndex);
    }

    private static void sortPlayersAssistRecursive(final Player[] players, int leftIndex, int rightIndex) {
        if (leftIndex >= rightIndex) {
            return;
        }

        int pivotValue = players[rightIndex].getAssistsPerGame();
        int left = leftIndex;
        for (int i = left; i < rightIndex; ++i) {
            if (players[i].getAssistsPerGame() > pivotValue) {
                Player temp = players[i];
                players[i] = players[left];
                players[left++] = temp;
            }
        }

        {
            Player temp = players[rightIndex];
            players[rightIndex] = players[left];
            players[left] = temp;
        }
        sortPlayersAssistRecursive(players, leftIndex, left - 1);
        sortPlayersAssistRecursive(players, left + 1, rightIndex);
    }

    public static long testManDreamTeam(final Player[] players, int k, final Player[] outPlayers) {
        if (k <= 0) {
            return 0;
        }

        long teamWorkScore = 0;
        int depth = k - 1;

        for (int i = 0; i < players.length - depth; ++i) {
            long result = findDreamTeamRecursive(players, depth, i, 0, Integer.MAX_VALUE, teamWorkScore, outPlayers);
            if (result > teamWorkScore) {
                teamWorkScore = result;
                outPlayers[depth] = players[i];
            }
        }

        return teamWorkScore;
    }

    public static long find3ManDreamTeam(final Player[] players, final Player[] outPlayers, final Player[] scratch) {
        return findDreamTeam(players, 3, outPlayers, scratch);
    }

    public static long findDreamTeam(final Player[] players, int k, final Player[] outPlayers, final Player[] scratch) {
        if (k <= 0) {
            return 0;
        }

        long teamWorkScore = 0;
        sortPlayersAssistRecursive(players, 0, players.length - 1);

        int allPasses = 0;
        for (int i = 0; i < k; ++i) {
            Player player = players[i];

            outPlayers[i] = player;
            scratch[i] = player;
            allPasses += player.getPassesPerGame();
        }
        teamWorkScore = (long) allPasses * outPlayers[k - 1].getAssistsPerGame();

        for (int i = k; i < players.length; ++i) {
            Player player = players[i];
            int minPassIndex = 0;

            for (int j = 1; j < k; ++j) {
                if (scratch[minPassIndex].getPassesPerGame() > scratch[j].getPassesPerGame()) {
                    minPassIndex = j;
                }
            }

            Player minPassPlayer = scratch[minPassIndex];
            if (player.getPassesPerGame() > minPassPlayer.getPassesPerGame()) {
                allPasses += player.getPassesPerGame() - minPassPlayer.getPassesPerGame();
                scratch[minPassIndex] = player;

                long calValue = (long) allPasses * player.getAssistsPerGame();
                if (calValue > teamWorkScore) {
                    teamWorkScore = calValue;
                    for (int j = 0; j < k; ++j) {
                        outPlayers[j] = scratch[j];
                    }
                }
            }
        }

        return teamWorkScore;
    }

    public static long findDreamTeamRecursive(final Player[] players, int depth, int findIndex, int allPasses, int minAssist, long highTeamWorkValue, final Player[] outPlayers) {
        int assist = Integer.min(minAssist, players[findIndex].getAssistsPerGame());
        int pass = allPasses + players[findIndex].getPassesPerGame();

        long value = highTeamWorkValue;
        if (depth == 0) {
            value = (long) pass * assist;
            if (value > highTeamWorkValue) {
                outPlayers[depth] = players[findIndex];
            }
        } else {
            for (int i = findIndex + 1; i < players.length; ++i) {
                long result = findDreamTeamRecursive(players, depth - 1, i, pass, assist, value, outPlayers);
                if (result > value) {
                    value = result;
                    outPlayers[depth] = players[findIndex];
                }
            }
        }

        return value;
    }

    public static int findDreamTeamSize(final Player[] players, final Player[] scratch) {
        sortPlayersAssistRecursive(players, 0, players.length - 1);

        int teamSize = 0;
        long maxDreamTeamScore = 0;
        int allPasses = 0;
        for (int i = 0; i < players.length; ++i) {
            allPasses += players[i].getPassesPerGame();
            long score = (long) allPasses * players[i].getAssistsPerGame();
            if (score > maxDreamTeamScore) {
                maxDreamTeamScore = score;
                teamSize = i + 1;
            }
        }
        return teamSize;
    }
}