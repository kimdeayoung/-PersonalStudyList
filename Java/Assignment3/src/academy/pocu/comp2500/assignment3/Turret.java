package academy.pocu.comp2500.assignment3;

import java.util.ArrayList;

public class Turret extends Unit implements IThinkable {
    private final int ATTACKRANGE = 1;

    public Turret(IntVector2D position) {
        super(position, 2, TileType.BUILDING, TileType.SKY, TileType.SKY, 0, 99, 7);
    }

    @Override
    public void onSpawn() {
        SimulationManager.getInstance().registerThinkable(this);
    }

    @Override
    public void onDead() {
        SimulationManager.getInstance().unregisterThinkable(this);
    }

    @Override
    public void behaviorDecision() {
        targetPos = null;
        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);

        this.behaviorType = BehaviorType.NONE;
        if (visibleUnits.size() > 0) {
            initAttackableTarget();
        }
    }

    protected void initAttackableTarget() {
        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);

        Unit registAttackUnit = null;
        ClockwiseDirInfo registDirInfo = null;
        boolean isRegistSamePos = false;

        for (Unit targetUnit : visibleUnits) {
            boolean isRegistAble = false;
            ClockwiseDirInfo attackDir = getAttackDirInfoOrNull(targetUnit.getPosition(), ATTACKRANGE, true);
            boolean isSamePos = this.position.equals(targetUnit.getPosition());

            if (attackDir == null && isSamePos == false) {
                continue;
            }

            if (registAttackUnit == null) {
                isRegistAble = true;
            } else {
                if (registAttackUnit.getHp() > targetUnit.getHp()) {
                    isRegistAble = true;
                } else if (registAttackUnit.getHp() == targetUnit.getHp()) {
                    if (isSamePos) {
                        isRegistAble = true;
                    } else {
                        if (isRegistSamePos == false && attackDir.isHigherClockwise(registDirInfo)) {
                            isRegistAble = true;
                        }
                    }
                }
            }

            if (isRegistAble) {
                registAttackUnit = targetUnit;
                registDirInfo = attackDir;
                isRegistSamePos = this.position.equals(targetUnit.getPosition());
            }
        }

        if (registAttackUnit != null) {
            setBehaivorTargetInfo(BehaviorType.ATTACK, registAttackUnit.getPosition());
        }
    }

    public char getSymbol() {
        return 'U';
    }
}
