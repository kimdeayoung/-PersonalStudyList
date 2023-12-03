package academy.pocu.comp3500.assignment1.app;

import academy.pocu.comp3500.assignment1.PocuBasketballAssociation;
import academy.pocu.comp3500.assignment1.pba.Player;
import academy.pocu.comp3500.assignment1.pba.GameStat;

import java.util.Arrays;
import java.util.Random;

public class Program {

    public static void main(String[] args) {
        {
            testDreamTeam();
        }
    }

    private static void testDreamTeam() {
        {
            {
                {
                    Player[] players = new Player[] {
                            new Player("Player 1", -1, 99999999, 2, -1),
                            new Player("Player 2", -1, 99999999, 1, -1),
                            new Player("Player 3", -1, 100, 0, -1),
                            new Player("Player 4", -1, 2, 102, -1),
                            new Player("Player 5", -1, 1, 296, -1),
                    };

                    Player[] outPlayers = new Player[3];
                    Player[] scratch = new Player[3];

                    long maxTeamwork = PocuBasketballAssociation.find3ManDreamTeam(players, outPlayers, scratch);
                    assert maxTeamwork == 400;
                }

                {
                    Player[] players = new Player[] {
                            new Player("Player 2", 5, 2, 14, 50),
                            new Player("Player 6", 15, 2, 5, 40),
                            new Player("Player 5", 11, 2, 11, 54),
                            new Player("Player 4", 10, 2, 51, 88),
                            new Player("Player 7", 16, 2, 5, 77),
                            new Player("Player 1", 1, 2, 2, 22),
                            new Player("Player 3", 7, 2, 8, 66)
                    };

                    Player[] outPlayers = new Player[3];
                    Player[] scratch = new Player[3];

                    long maxTeamwork = PocuBasketballAssociation.find3ManDreamTeam(players, outPlayers, scratch);

                    assert (maxTeamwork == 152);

                    Player player = getPlayerOrNull(outPlayers, "Player 4");
                    assert (player != null);

                    player = getPlayerOrNull(outPlayers, "Player 2");
                    assert (player != null);

                    player = getPlayerOrNull(outPlayers, "Player 5");
                    assert (player != null);
                }

                {
                    Player[] players = new Player[]{
                            new Player("player0", 91, 77, 92, 7),
                            new Player("player1", 87, 49, 53, 97),
                            new Player("player2", 91, 41, 89, 10),
                            new Player("player3", 39, 9, 81, 63),
                            new Player("player4", 2, 77, 43, 41),
                            new Player("player5", 46, 39, 59, 53),
                            new Player("player6", 51, 33, 70, 73),
                            new Player("player7", 32, 64, 62, 73),
                            new Player("player8", 61, 84, 81, 24),
                            new Player("player9", 96, 97, 7, 40),
                            new Player("player10", 17, 0, 91, 58),
                            new Player("player11", 43, 36, 86, 48),
                            new Player("player12", 65, 37, 68, 5),
                            new Player("player13", 68, 81, 41, 96),
                            new Player("player14", 33, 100, 21, 44),
                            new Player("player15", 40, 0, 92, 9),
                    };

                    final int TEAM_SIZE = 8;

                    Player[] outPlayers = new Player[TEAM_SIZE];
                    Player[] scratch = new Player[TEAM_SIZE];

                    long teamTest = PocuBasketballAssociation.testManDreamTeam(players, TEAM_SIZE, outPlayers);
                    long maxTeamwork = PocuBasketballAssociation.findDreamTeam(players, TEAM_SIZE, outPlayers, scratch);

                    assert (maxTeamwork == 21240);
                }
            }

            for (int test = 0; test < 5000; ++test) {
                int length = 10;
                int k = 4;
                Player[] players = new Player[length];
                Player[] outPlayers = new Player[k];
                Player[] scratch = new Player[k];
                Player[] expectedOutPlayers = new Player[k];

                Random random = new Random();
                for (int i = 0; i < length; i++) {
                    players[i] = new Player("Player" + i, 0, random.nextInt(100), random.nextInt(100), 0);
                }


                long team = PocuBasketballAssociation.findDreamTeam(players, k, outPlayers, scratch);
                long checkValue = PocuBasketballAssociation.testManDreamTeam(players, k, expectedOutPlayers);

                if (team != checkValue) {
                    for (int i = 0; i < players.length; ++i) {
                        Player player = players[i];
                        boolean outPlayer = false;
                        boolean expected = false;
                        for (int j = 0; j < k; ++j) {
                            outPlayer |= outPlayers[j].getName().equals(player.getName());
                            expected |= expectedOutPlayers[j].getName().equals(player.getName());
                        }

                        System.out.print(player.getAssistsPerGame() + " " + player.getPassesPerGame());
                        if (outPlayer) {
                            System.out.print(" x ");
                        }
                        if (expected) {
                            System.out.print(" o ");
                        }
                        System.out.println("");
                    }
                    System.out.println("");
                }

                for (int i = 0; i < k; ++i) {
                    players[i] = null;
                    expectedOutPlayers[i] = null;
                }
            }
        }

        {
            Player[] players = new Player[]{
                    new Player("Player 2", 5, 100, 1, 50),
                    new Player("Player 6", 15, 100, 1, 40),
                    new Player("Player 5", 11, 100, 1, 54),
                    new Player("Player 4", 10, 1, 50, 88),
                    new Player("Player 7", 16, 1, 60, 77),
                    new Player("Player 1", 1, 1, 70, 22),
                    new Player("Player 3", 7, 1, 80, 66)
            };

            Player[] outPlayers = new Player[3];
            Player[] scratch = new Player[3];

            long maxTeamwork = PocuBasketballAssociation.find3ManDreamTeam(players, outPlayers, scratch);

            assert (maxTeamwork == 300);

            Player player = getPlayerOrNull(outPlayers, "Player 2");
            assert (player != null);

            player = getPlayerOrNull(outPlayers, "Player 6");
            assert (player != null);

            player = getPlayerOrNull(outPlayers, "Player 5");
            assert (player != null);
        }
    }

    private static Player getPlayerOrNull(final Player[] players, final String id) {
        for (int i = 0; i < players.length; ++i) {
            if (players[i] == null) {
                return null;
            }

            if (players[i].getName().equals(id)) {
                return players[i];
            }
        }
        return null;
    }
}