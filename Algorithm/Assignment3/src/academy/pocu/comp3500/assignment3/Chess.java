package academy.pocu.comp3500.assignment3;

import java.util.ArrayList;

public class Chess {
    public final static int BOARD_SIZE = 8;

    public final static int LOWERCASE_A = 97;

    public static final int[][] KING_MOVE_OFFSETS = {
            {-1, 1},
            {-1, 0},
            {-1, -1},
            {0, 1},
            {0, -1},
            {1, 1},
            {1, 0},
            {1, -1}
    };

    public static final int[][] KNIGHT_MOVE_OFFSETS = {
            {1, -2},
            {1, 2},
            {2, -1},
            {2, 1},
            {-2, -1},
            {-2, 1},
            {-1, -2},
            {-1, 2}
    };

    public static final int[][] PAWN_MOVE_OFFSETS = {
            {0, 1},
            {0, 2},
            {-1, 1},
            {1, 1},
            {0, -1},
            {0, -2},
            {-1, -1},
            {1, -1}
    };

    public static final int[][] ROOK_MOVE_TYPES = {
            {0, -1},
            {0, 1},
            {-1, 0},
            {1, 0},
    };

    public static final int[][] BISHOP_MOVE_TYPES = {
            {-1, -1},
            {1, -1},
            {-1, 1},
            {1, 1},
    };

    public static final int CHECK_KING_SCORE = 10000;
    public static final int KING_SCORE = 1000;
    public static final int QUUEN_SCORE = 500;
    public static final int ROOK_SCORE = 350;
    public static final int BISHOP_SCORE = 280;
    public static final int KNIGHT_SCORE = 250;
    public static final int PAWN_SCORE = 100;

    static boolean isMoveValid(char[][] board, boolean isWhite, final int fromX, final int fromY, final int toX, final int toY) {
        if (fromX >= BOARD_SIZE || fromX < 0
                || fromY >= BOARD_SIZE || fromY < 0) {
            return false;
        }

        final char symbol = board[fromY][fromX];

        if (symbol == 0) {
            return false;
        }

        if ((isWhite && !Character.isLowerCase(symbol))
                || !isWhite && Character.isLowerCase(symbol)) {
            return false;
        }

        if (toX >= BOARD_SIZE || toX < 0
                || toY >= BOARD_SIZE || toY < 0) {
            return false;
        }

        if (fromX == toX && fromY == toY) {
            return false;
        }

        char symbolInvariant = Character.toLowerCase(symbol);

        switch (symbolInvariant) {
            case 'p':
                return isPawnMoveValid(board, fromX, fromY, toX, toY);

            case 'n':
                return isKnightMoveValid(board, fromX, fromY, toX, toY);

            case 'b':
                return isBishopMoveValid(board, fromX, fromY, toX, toY);

            case 'r':
                return isRookMoveValid(board, fromX, fromY, toX, toY);

            case 'q':
                return isQueenMoveValid(board, fromX, fromY, toX, toY);

            case 'k':
                return isKingMoveValid(board, fromX, fromY, toX, toY);

            default:
                throw new IllegalArgumentException("Unknown piece symbol");
        }
    }

    public static boolean isBishopMoveValid(char[][] board, final int fromX, final int fromY, final int toX, final int toY) {
        char fromPiece = board[fromY][fromX];
        char toPiece = board[toY][toX];

        if (toPiece != 0 && Character.isLowerCase(fromPiece) == Character.isLowerCase(toPiece)) {
            return false;
        }

        if (Math.abs(fromX - toX) != Math.abs(fromY - toY)) {
            return false;
        }

        int xIncrement = fromX < toX ? 1 : -1;
        int yIncrement = fromY < toY ? 1 : -1;

        int x = fromX + xIncrement;
        int y = fromY + yIncrement;

        while (x != toX && y != toY) {
            if (board[y][x] != 0 && x != toX && y != toY) {
                return false;
            }

            x += xIncrement;
            y += yIncrement;
        }

        return true;
    }

    public static boolean isRookMoveValid(char[][] board, final int fromX, final int fromY, final int toX, final int toY) {
        char fromPiece = board[fromY][fromX];
        char toPiece = board[toY][toX];

        if (toPiece != 0 && Character.isLowerCase(fromPiece) == Character.isLowerCase(toPiece)) {
            return false;
        }

        if (fromX == toX) {
            int yIncrement = fromY < toY ? 1 : -1;

            int y = fromY + yIncrement;

            while (y != toY) {
                if (board[y][fromX] != 0) {
                    return false;
                }

                y += yIncrement;
            }

            return true;

        } else if (fromY == toY) {
            int xIncrement = fromX < toX ? 1 : -1;

            int x = fromX + xIncrement;

            while (x != toX) {
                if (board[fromY][x] != 0) {
                    return false;
                }

                x += xIncrement;
            }

            return true;
        }

        return false;
    }

    public static boolean isKnightMoveValid(char[][] board, final int fromX, final int fromY, final int toX, final int toY) {
        char fromPiece = board[fromY][fromX];
        char toPiece = board[toY][toX];

        if (toPiece != 0 && Character.isLowerCase(fromPiece) == Character.isLowerCase(toPiece)) {
            return false;
        }

        for (int i = 0; i < KNIGHT_MOVE_OFFSETS.length; ++i) {
            if (fromX + KNIGHT_MOVE_OFFSETS[i][0] == toX && fromY + KNIGHT_MOVE_OFFSETS[i][1] == toY) {
                return true;
            }
        }

        return false;
    }

    public static boolean isQueenMoveValid(char[][] board, final int fromX, final int fromY, final int toX, final int toY) {
        return isBishopMoveValid(board, fromX, fromY, toX, toY) || isRookMoveValid(board, fromX, fromY, toX, toY);
    }

    public static boolean isKingMoveValid(char[][] board, final int fromX, final int fromY, final int toX, final int toY) {
        char fromPiece = board[fromY][fromX];
        char toPiece = board[toY][toX];

        if (toPiece != 0 && Character.isLowerCase(fromPiece) == Character.isLowerCase(toPiece)) {
            return false;
        }

        for (int i = 0; i < KING_MOVE_OFFSETS.length; ++i) {
            if (fromX + KING_MOVE_OFFSETS[i][0] == toX && fromY + KING_MOVE_OFFSETS[i][1] == toY) {
                return true;
            }
        }

        return false;
    }

    public static boolean isPawnMoveValid(char[][] board, final int fromX, final int fromY, final int toX, final int toY) {
        char fromPiece = board[fromY][fromX];
        char toPiece = board[toY][toX];

        boolean isFromPieceWhite = Character.isLowerCase(fromPiece);
        boolean isToPieceWhite = Character.isLowerCase(toPiece);

        if (toPiece != 0 && isFromPieceWhite == isToPieceWhite) {
            return false;
        }

        if (toPiece != 0 && fromX == toX) {
            return false;
        }

        boolean hasMoved = isFromPieceWhite ? fromY != 6 : fromY != 1;

        if (!hasMoved && fromX == toX && Math.abs(toY - fromY) == 2) {
            if (toY > fromY && !isFromPieceWhite && board[toY - 1][toX] == 0) {
                return true;
            }

            return toY < fromY && isFromPieceWhite && board[toY + 1][toX] == 0;
        } else if (fromX == toX && Math.abs(toY - fromY) == 1) {
            if (toY > fromY && !isFromPieceWhite) {
                return true;
            }

            return toY < fromY && isFromPieceWhite;
        } else if (toX == fromX - 1 || toX == fromX + 1) {
            if (toPiece != 0 && isToPieceWhite != isFromPieceWhite) {
                return isFromPieceWhite ? toY == fromY - 1 : toY == fromY + 1;
            }
        }

        return false;
    }

    public static int getChessPieceScore(char[][] board, int x, int y) {
        char ch = Character.toLowerCase(board[y][x]);
        switch (ch) {
            case 'p':
                return PAWN_SCORE;

            case 'n':
                return KNIGHT_SCORE;

            case 'b':
                return BISHOP_SCORE;

            case 'r':
                return ROOK_SCORE;

            case 'q':
                return QUUEN_SCORE;

            case 'k':
                return KING_SCORE;

            default:
                return 0;
        }
    }

    public static int hasWon(final char[][] board, boolean isPlayerWhiteColor) {//1 = player won, -1 = oppenent won
        boolean isWhiteKingAlive = false;
        boolean isBlackKingAlive = false;

        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                char ch = board[y][x];
                if (ch == 'K') {
                    isBlackKingAlive = true;

                    if (isWhiteKingAlive) {
                        return 0;
                    }
                } else if (ch == 'k') {
                    isWhiteKingAlive = true;

                    if (isBlackKingAlive) {
                        return 0;
                    }
                }
            }
        }

        if (isPlayerWhiteColor) {
            return isBlackKingAlive ? -1 : 1;
        } else {
            return isWhiteKingAlive ? -1 : 1;
        }
    }

    public static ChessPieceMove getMaxScoreMove(ArrayList<ChessPieceMove> moves) {
        assert (!moves.isEmpty());

        ChessPieceMove bestPieceMove = moves.get(0);
        for (int i = 1; i < moves.size(); ++i) {
            ChessPieceMove pieceMove = moves.get(i);
            if (pieceMove.getScore() > bestPieceMove.getScore()) {
                bestPieceMove = pieceMove;
            }
        }

        return bestPieceMove;
    }

    public static ChessPieceMove getMinScoreMove(ArrayList<ChessPieceMove> moves) {
        assert (!moves.isEmpty());

        ChessPieceMove worstPieceMove = moves.get(0);
        for (int i = 1; i < moves.size(); ++i) {
            ChessPieceMove pieceMove = moves.get(i);
            if (pieceMove.getScore() < worstPieceMove.getScore()) {
                worstPieceMove = pieceMove;
            }
        }

        return worstPieceMove;
    }

    public static int getBoardScores(char[][] board, boolean isWhite) {
        int score = 0;

        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                char ch = board[y][x];

                if (isWhite && ch >= LOWERCASE_A) {
                    score += getChessPieceScore(board, x, y);
                } else {
                    score -= getChessPieceScore(board, x, y);
                }
            }
        }

        return score;
    }
}
