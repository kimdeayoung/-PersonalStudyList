package academy.pocu.comp3500.assignment3;

import academy.pocu.comp3500.assignment3.chess.Move;
import academy.pocu.comp3500.assignment3.chess.PlayerBase;

import java.util.ArrayList;

public class Player extends PlayerBase {

    private ArrayList<ChessPieceMove> movesPool;
    private int movesPoolIndex;

    private ArrayList<char[][]> boardsPool;
    private int boardsPoolIndex;

    private final int MAX_TURN = 3;

    public Player(boolean isWhite, int maxMoveTimeMilliseconds) {
        super(isWhite, maxMoveTimeMilliseconds);

        movesPool = new ArrayList<>(65536);
        boardsPool = new ArrayList<>(8192);

        for (int i = 0; i < 65536; ++i) {
            movesPool.add(new ChessPieceMove());
        }

        for (int i = 0; i < 8192; ++i) {
            boardsPool.add(new char[Chess.BOARD_SIZE][Chess.BOARD_SIZE]);
        }
    }

    @Override
    public Move getNextMove(char[][] board) {
        return getNextMove(board, null);
    }

    @Override
    public Move getNextMove(char[][] board, Move opponentMove) {
        ChessPieceMove pieceMove = getBestNextMoveRecursive(board, isWhite(), true, 1);

        movesPoolIndex = 0;
        boardsPoolIndex = 0;
        return new Move(pieceMove.getFromX(), pieceMove.getFromY(), pieceMove.getToX(), pieceMove.getToY());
    }

    private ChessPieceMove getBestNextMoveRecursive(char[][] board, boolean turnColor, boolean isPlayerTurn, int turnCount) {
        int winResult = Chess.hasWon(board, isWhite());
        if (winResult == 1) {
            ChessPieceMove pieceMove = getOrCreateMove();
            pieceMove.init(-1, -1, -1, -1, Chess.CHECK_KING_SCORE);
            return pieceMove;
        } else if (winResult == -1) {
            ChessPieceMove pieceMove = getOrCreateMove();
            pieceMove.init(-1, -1, -1, -1, -Chess.CHECK_KING_SCORE);
            return pieceMove;
        }

        ArrayList<ChessPieceMove> chessMoves = getAllMove(board, turnColor);
        if (chessMoves.isEmpty()) {
            ChessPieceMove pieceMove = getOrCreateMove();
            pieceMove.init(-1, -1, -1, -1, 0);
            return pieceMove;
        }

        for (ChessPieceMove move : chessMoves) {
            if (turnCount == MAX_TURN) {
                char temp = board[move.getToY()][move.getToX()];
                board[move.getToY()][move.getToX()] = board[move.getFromY()][move.getFromX()];
                board[move.getFromY()][move.getFromX()] = 0;

                move.setScore(Chess.getBoardScores(board, isWhite()));

                board[move.getFromY()][move.getFromX()] = board[move.getToY()][move.getToX()];
                board[move.getToY()][move.getToX()] = temp;
            } else {
                char[][] simulateBoard = getOrCreateBoard(board);
                simulateBoard[move.getToY()][move.getToX()] = board[move.getFromY()][move.getFromX()];
                simulateBoard[move.getFromY()][move.getFromX()] = 0;

                int score = getBestNextMoveRecursive(simulateBoard, !turnColor, !isPlayerTurn, turnCount + 1).getScore();
                move.setScore(score);
            }
        }

        if (isPlayerTurn) {
            return Chess.getMaxScoreMove(chessMoves);
        }
        return Chess.getMinScoreMove(chessMoves);
    }

    private ArrayList<ChessPieceMove> getAllMove(char[][] board, boolean isWhite) {
        ArrayList<ChessPieceMove> allMoves = new ArrayList<>();

        for (int y = 0; y < Chess.BOARD_SIZE; ++y) {
            for (int x = 0; x < Chess.BOARD_SIZE; ++x) {
                char ch = board[y][x];
                if (ch == 0) {
                    continue;
                } else if (isWhite && ch < Chess.LOWERCASE_A) {
                    continue;
                }
                ch = Character.toLowerCase(ch);

                switch (ch) {
                    case 'p':
                        getAllPawnMoves(board, x, y, allMoves, isWhite);
                        break;
                    case 'n':
                        getAllKnightMoves(board, x, y, allMoves, isWhite);
                        break;
                    case 'b':
                        getAllBishopMoves(board, x, y, allMoves, isWhite);
                        break;
                    case 'r':
                        getAllRookMoves(board, x, y, allMoves, isWhite);
                        break;
                    case 'q':
                        getAllQueenMoves(board, x, y, allMoves, isWhite);
                        break;
                    case 'k':
                        getAllKingMoves(board, x, y, allMoves, isWhite);
                        break;
                    default:
                        throw new IllegalArgumentException("Unknown piece symbol");
                }

                if (allMoves.size() == 1 && allMoves.get(0).getScore() == Chess.KING_SCORE) {
                    return allMoves;
                }
            }
        }

        return allMoves;
    }

    private void getAllPawnMoves(char[][] board, int startX, int startY, ArrayList<ChessPieceMove> moves, boolean isWhite) {
        int pawnHalfMoveOffset = Chess.PAWN_MOVE_OFFSETS.length / 2;

        int loopStartIndex = 0;
        int loopEndIndex = pawnHalfMoveOffset;
        if (isWhite) {
            loopStartIndex = pawnHalfMoveOffset;
            loopEndIndex = Chess.PAWN_MOVE_OFFSETS.length;
        }

        for (int i = loopStartIndex; i < loopEndIndex; ++i) {
            int toPosX = startX + Chess.PAWN_MOVE_OFFSETS[i][0];
            int toPosY = startY + Chess.PAWN_MOVE_OFFSETS[i][1];

            if (Chess.isMoveValid(board, isWhite, startX, startY, toPosX, toPosY)) {
                ChessPieceMove pieceMove = getOrCreateMove();
                pieceMove.init(startX, startY, toPosX, toPosY);

                if (Chess.getChessPieceScore(board, toPosX, toPosY) == Chess.KING_SCORE) {
                    moves.clear();
                    moves.add(pieceMove);
                    return;
                }

                moves.add(pieceMove);
            }
        }

    }

    private void getAllKnightMoves(char[][] board, int startX, int startY, ArrayList<ChessPieceMove> moves, boolean isWhite) {
        for (int i = 0; i < Chess.KNIGHT_MOVE_OFFSETS.length; ++i) {
            int toPosX = startX + Chess.KNIGHT_MOVE_OFFSETS[i][0];
            int toPosY = startY + Chess.KNIGHT_MOVE_OFFSETS[i][1];
            if (Chess.isMoveValid(board, isWhite, startX, startY, toPosX, toPosY)) {
                ChessPieceMove pieceMove = getOrCreateMove();
                pieceMove.init(startX, startY, toPosX, toPosY);

                if (Chess.getChessPieceScore(board, toPosX, toPosY) == Chess.KING_SCORE) {
                    moves.clear();
                    moves.add(pieceMove);
                    return;
                }

                moves.add(pieceMove);
            }
        }
    }

    private void getAllQueenMoves(char[][] board, int startX, int startY, ArrayList<ChessPieceMove> moves, boolean isWhite) {
        getAllRookMoves(board, startX, startY, moves, isWhite);
        if (moves.size() == 1 && moves.get(0).getScore() == Chess.KING_SCORE) {
            return;
        }
        getAllBishopMoves(board, startX, startY, moves, isWhite);
    }

    private void getAllRookMoves(char[][] board, int startX, int startY, ArrayList<ChessPieceMove> moves, boolean isWhite) {
        for (int i = 0; i < Chess.ROOK_MOVE_TYPES.length; ++i) {
            for (int j = 1; j <= Chess.BOARD_SIZE; ++j) {
                int toPosX = startX + Chess.ROOK_MOVE_TYPES[i][0] * j;
                int toPosY = startY + Chess.ROOK_MOVE_TYPES[i][1] * j;

                if (Chess.isMoveValid(board, isWhite, startX, startY, toPosX, toPosY)) {
                    int score = Chess.getChessPieceScore(board, toPosX, toPosY);
                    ChessPieceMove pieceMove = getOrCreateMove();
                    pieceMove.init(startX, startY, toPosX, toPosY);
                    if (score == Chess.KING_SCORE) {
                        moves.clear();
                        moves.add(pieceMove);
                        return;
                    }
                    moves.add(pieceMove);
                    if (score > 0) {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
    }

    private void getAllKingMoves(char[][] board, int startX, int startY, ArrayList<ChessPieceMove> moves, boolean isWhite) {
        for (int i = 0; i < Chess.KING_MOVE_OFFSETS.length; ++i) {
            int toPosX = startX + Chess.KING_MOVE_OFFSETS[i][0];
            int toPosY = startY + Chess.KING_MOVE_OFFSETS[i][1];

            if (Chess.isMoveValid(board, isWhite, startX, startY, toPosX, toPosY)) {
                int score = Chess.getChessPieceScore(board, toPosX, toPosY);
                ChessPieceMove pieceMove = getOrCreateMove();
                pieceMove.init(startX, startY, toPosX, toPosY);
                if (score == Chess.KING_SCORE) {
                    moves.clear();
                    moves.add(pieceMove);
                    return;
                }
                moves.add(pieceMove);
            }
        }
    }

    private void getAllBishopMoves(char[][] board, int startX, int startY, ArrayList<ChessPieceMove> moves, boolean isWhite) {
        for (int i = 0; i < Chess.BISHOP_MOVE_TYPES.length; ++i) {
            for (int j = 1; j <= Chess.BOARD_SIZE; ++j) {
                int toPosX = startX + Chess.BISHOP_MOVE_TYPES[i][0] * j;
                int toPosY = startY + Chess.BISHOP_MOVE_TYPES[i][1] * j;

                if (Chess.isMoveValid(board, isWhite, startX, startY, toPosX, toPosY)) {
                    int score = Chess.getChessPieceScore(board, toPosX, toPosY);
                    ChessPieceMove pieceMove = getOrCreateMove();
                    pieceMove.init(startX, startY, toPosX, toPosY);
                    if (score == Chess.KING_SCORE) {
                        moves.clear();
                        moves.add(pieceMove);
                        return;
                    }
                    moves.add(pieceMove);
                    if (score > 0) {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
    }

    private ChessPieceMove getOrCreateMove() {
        if (movesPool.size() <= movesPoolIndex) {
            movesPool.add(new ChessPieceMove());
        }

        return movesPool.get(movesPoolIndex++);
    }

    private char[][] getOrCreateBoard(char[][] rawData) {
        if (boardsPool.size() <= boardsPoolIndex) {
            boardsPool.add(new char[Chess.BOARD_SIZE][Chess.BOARD_SIZE]);
        }

        char[][] board = boardsPool.get(boardsPoolIndex++);
        for (int y = 0; y < Chess.BOARD_SIZE; ++y) {
            for (int x = 0; x < Chess.BOARD_SIZE; ++x) {
                board[y][x] = rawData[y][x];
            }
        }

        return board;
    }
}