package academy.pocu.comp2500.lab5;

import java.util.ArrayList;

public class Gladiator extends Barbarian {
    private ArrayList<Move> moves;

    private int maxHp;
    private int maxMoveCount = 4;

    public Gladiator(String name, int hp, int atk, int def) {
        super(name, hp, atk, def);

        this.moves = new ArrayList<>(maxMoveCount);
        this.maxHp = hp;
    }

    public boolean addMove(Move move) {
        if (getMoveOrNull(move.getName()) == null) {
            if (moves.size() < maxMoveCount) {
                moves.add(move);
                return true;
            }
        }
        return false;
    }

    private Move getMoveOrNull(String name) {
        for (Move move : this.moves) {
            if (move.isEqual(name)) {
                return move;
            }
        }
        return null;
    }

    public boolean removeMove(String name) {
        Move move = getMoveOrNull(name);
        return this.moves.remove(move);
    }

    public void attack(String name, Barbarian enemy) {
        if (isAttackAbleEnemy(enemy)) {
            Move move = getMoveOrNull(name);
            if (move != null) {
                if (move.isUseAble()) {
                    double damage = ((double) this.atk / enemy.def * move.getPower()) / 2;
                    if (damage < 1.0) {
                        damage = 1.0;
                    }
                    enemy.hp -= (int) damage;
                    if (enemy.hp < 0) {
                        enemy.hp = 0;
                    }
                    move.useMove();
                }
            }
        }
    }

    public void rest() {
        this.hp += 10;
        if (this.maxHp < this.hp) {
            this.hp = this.maxHp;
        }

        for (Move move : this.moves) {
            move.refillMove();
        }
    }
}
