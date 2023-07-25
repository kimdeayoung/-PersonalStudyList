package academy.pocu.comp2500.lab5;

public class Barbarian {
    protected String playerName;
    protected int atk;
    protected int def;

    protected int hp;

    public Barbarian(String name, int hp, int atk, int def) {
        this.playerName = name;
        this.hp = hp;
        this.atk = atk;
        this.def = def;
    }

    public int getHp() {
        return hp;
    }

    protected boolean isAttackAbleEnemy(Barbarian enemy) {
        return (this.playerName.equals(enemy.playerName) == false) && isAlive() && enemy.isAlive();
    }

    public void attack(Barbarian enemy) {
        if (isAttackAbleEnemy(enemy)) {
            double damage = ((double) this.atk - enemy.def) / 2;
            if (damage < 1.0) {
                damage = 1.0;
            }
            enemy.hp -= (int) damage;
            if (enemy.hp < 0) {
                enemy.hp = 0;
            }
        }
    }


    public boolean isAlive() {
        return this.hp > 0;
    }
}
