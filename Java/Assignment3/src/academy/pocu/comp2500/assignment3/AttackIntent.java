package academy.pocu.comp2500.assignment3;

public class AttackIntent {
    private IntVector2D attackPosition;
    private int damage;
    private Unit attacker;

    public AttackIntent(Unit attacker) {
        this.attacker = attacker;
    }

    public IntVector2D getAttackPosition() {
        return this.attacker.getTargetPos();
    }

    public int getDamage(IntVector2D targetUnitPos) {
        if (this.attacker.getTargetPos().equals(targetUnitPos)) {
            return this.attacker.getAp();
        }

        int targetPosX = this.attacker.getTargetPos().getX();
        int targetPosY = this.attacker.getTargetPos().getY();

        int offsetX = Math.abs(this.attacker.getTargetPos().getX() - targetUnitPos.getX());
        int offsetY = Math.abs(this.attacker.getTargetPos().getY() - targetUnitPos.getY());

        int attackerAoe = this.attacker.getAoe();
        if (offsetX <= attackerAoe && offsetY <= attackerAoe) {
            double damage = this.attacker.getAp() * (1.0 - (double) Math.max(offsetX, offsetY) / (attackerAoe + 1));
            return (int) damage;
        }

        return -1;
    }

    public Unit getAttacker() {
        return attacker;
    }
}