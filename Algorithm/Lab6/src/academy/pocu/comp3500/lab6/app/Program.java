package academy.pocu.comp3500.lab6.app;

import academy.pocu.comp3500.lab6.League;
import academy.pocu.comp3500.lab6.leagueofpocu.Player;

import java.util.*;

public class Program {

    public static void main(String[] args) {
        Test();
        for (int i = 0; i < 16000; ++i) {
            Test_C();
        }
    }

    private static void Test() {
        Player player1 = new Player(1, "player1", 15);
        Player player2 = new Player(2, "player2", 13);
        Player player3 = new Player(3, "player3", 83);
        Player player4 = new Player(4, "player4", 22);
        Player player5 = new Player(5, "player5", 21);
        Player player6 = new Player(6, "player6", 32);
        Player player7 = new Player(7, "player7", 24);
        Player player8 = new Player(8, "player8", 53);

        League league = new League(new Player[]{player1, player2, player3, player4, player5,player6,player7,player8});

        league.findMatchOrNull(player7);
    }

    private static void Test_C() {
        int length = 10;
        Player[] players = new Player[length];

        Random random = new Random();
        HashSet<Integer> usedRanks = new HashSet<>();

        for (int i = 0; i < length; ++i) {
            int rank;
            do {
                rank = random.nextInt(100);
            } while (usedRanks.contains(rank));
            usedRanks.add(rank);
            players[i] = (new Player(i, "player" + i, rank));
        }

        League league = new League(players);
        Player cmpPlayer = players[length / 2];
        Player result = league.findMatchOrNull(cmpPlayer);

        Player matchPlayer = null;
        int offset = Integer.MAX_VALUE;
        for (int i = 0; i < length; ++i) {
            if (cmpPlayer.equals(players[i])) {
                continue;
            }

            int cmpOffset = Math.abs(cmpPlayer.getRating() - players[i].getRating());
            if (offset == cmpOffset){
                if (players[i].getRating() > matchPlayer.getRating()) {
                    matchPlayer = players[i];
                    offset = cmpOffset;
                }
            } else if (offset > cmpOffset) {
                matchPlayer = players[i];
                offset = cmpOffset;
            }
        }

        if (result.equals(matchPlayer) == false) {
            if (result.getRating() != matchPlayer.getRating()) {
                System.out.println("");
            }
        }
        assert(result.getRating() == matchPlayer.getRating());
    }

    private static void Test_G() {
        int length = 5;
        Player[] players = new Player[length];
        boolean[] isAffiliation = new boolean[length];
        int[] orders = new int[length];
        int order = 0;

        Random random = new Random();
        HashSet<Integer> usedRanks = new HashSet<>();

        for (int i = 0; i < length; ++i) {
            isAffiliation[i] = true;
            int rank;
            do {
                rank = random.nextInt(100);
            } while (usedRanks.contains(rank));
            usedRanks.add(rank);
            players[i] = (new Player(i, "player" + i, rank));
        }
        League raw = new League(players);
        League league = new League(players);

        for (int i = 0; i < length * 30; ++i) {
            int index = random.nextInt(players.length);
            boolean leave = league.leave(players[index]);
            if (leave) {
                orders[index] = ++order;
            }
            if (isAffiliation[index] != leave) {
                System.out.println("이곳에 디버그 포인트를 찍어서 디버깅을 하시면 더 편합니다.");
            }
            assert(isAffiliation[index] == leave);
            isAffiliation[index] = false;
        }
    }

    public static void test_G_multiple_2() {

        Player player1 = new Player(1, "player1", 9999);
        Player player2 = new Player(2, "player2", 1);
        Player player3 = new Player(3, "player3", 5555);
        Player player4 = new Player(4, "player4", 200);
        Player player5 = new Player(5, "player5", 100);
        Player player6 = new Player(6, "player6", 5);

        League league = new League(new Player[]{player6, player2, player1, player3, player5, player4});
        //              9999(p1)
        //  100(p5)

        //print_arr(league.getTop(100));

        league.leave(player1);
        //print_arr(league.getTop(100));

        league.leave(player5);
        //print_arr(league.getTop(100));

        league.leave(player2);
        //print_arr(league.getTop(100));

        league.leave(player3);
        //print_arr(league.getTop(100));

        league.leave(player4);
        //print_arr(league.getTop(100));

        league.leave(player6);
        //print_arr(league.getTop(100));

    }

    private static void complexScenarioTest_2() {
        List<Player> players = new ArrayList<>();
        Random random = new Random();
        HashSet<Integer> usedRanks = new HashSet<>();

        for (int i = 1; i <= 50; i++) {
            int id = random.nextInt(1000);
            int rank;
            do {
                rank = random.nextInt(100);
            } while (usedRanks.contains(rank));
            usedRanks.add(rank);
            players.add(new Player(id, "player" + i, rank));
        }

        Collections.shuffle(players);

        League league = new League(players.toArray(new Player[0]));

        Player playerToTest = players.get(0);

        Player closestPlayer = null;
        for (Player player : players) {
            if (player == playerToTest) {
                continue;
            }
            if (closestPlayer == null || Math.abs(player.getRating() - playerToTest.getRating()) < Math.abs(closestPlayer.getRating() - playerToTest.getRating())) {
                closestPlayer = player;
            } else if (Math.abs(player.getRating() - playerToTest.getRating()) == Math.abs(closestPlayer.getRating() - playerToTest.getRating()) && player.getRating() > closestPlayer.getRating()){
                closestPlayer = player;
            }
        }

        Player match = league.findMatchOrNull(playerToTest);

        assert (match.getId() == closestPlayer.getId());
    }
}
