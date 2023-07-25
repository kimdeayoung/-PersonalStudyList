package academy.pocu.comp2500.lab5;

public class Knight extends Gladiator {
    private Pet pet;

    public Knight(String name, int hp, int atk, int def) {
        super(name, hp, atk, def);
    }

    public void setPet(Pet petOrNull) {
        this.pet = petOrNull;
    }

    public void attackTogether(Barbarian enemy) {
        if (pet != null) {
            if (isAttackAbleEnemy(enemy)) {
                double damage = ((double) this.atk + pet.getAtk() - enemy.def) / 2;
                if (damage < 1.0) {
                    damage = 1.0;
                }
                enemy.hp -= (int) damage;
                if (enemy.hp < 0) {
                    enemy.hp = 0;
                }
            }
        }
    }
}
