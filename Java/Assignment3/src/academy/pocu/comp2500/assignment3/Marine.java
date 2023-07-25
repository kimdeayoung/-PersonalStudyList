package academy.pocu.comp2500.assignment3;

import java.util.ArrayList;

public class Marine extends Unit implements IThinkable, IMovable {
    private final int ATTACKRANGE = 1;

    public Marine(IntVector2D position) {
        super(position, 2, TileType.GROUND, TileType.GROUND_AND_SKY, TileType.GROUND_AND_SKY, 0, 35, 6);
    }

    @Override
    public void onSpawn() {
        SimulationManager.getInstance().registerThinkable(this);
        SimulationManager.getInstance().registerMovable(this);
    }

    @Override
    public void onDead() {
        SimulationManager.getInstance().unregisterThinkable(this);
        SimulationManager.getInstance().unregisterMovable(this);
    }

    public void behaviorDecision() {
        targetPos = null;
        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);

        behaviorType = BehaviorType.NONE;
        if (visibleUnits.size() > 0) {
            initAttackableTarget();
            if (behaviorType == BehaviorType.NONE) {
                specifyDirOfMovement();
            }
        }
    }

    public void specifyDirOfMovement() {
        int lowDistance = INTEGERMAX;
        ClockwiseDirInfo registDirInfo = null;
        Unit registTargetUnit = null;

        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);
        for (Unit targetUnit : visibleUnits) {
            boolean isRegistAble = false;
            int distance = getManhattanDistance(targetUnit);
            ClockwiseDirInfo clockwiseDir = getClockwiseDir(targetUnit.getPosition());

            if (lowDistance > distance) {
                isRegistAble = true;
            } else if (lowDistance == distance) {
                if (registTargetUnit.getHp() > targetUnit.getHp()) {
                    isRegistAble = true;
                } else if (registTargetUnit.getHp() == targetUnit.getHp()) {
                    if (clockwiseDir.isHigherClockwise(registDirInfo)) {
                        isRegistAble = true;
                    }
                }
            }

            if (isRegistAble) {
                registTargetUnit = targetUnit;
                lowDistance = distance;
                registDirInfo = clockwiseDir;
            }
        }

        if (registTargetUnit != null) {
            setBehaivorTargetInfo(BehaviorType.MOVE, registTargetUnit.getPosition());
        }
    }

    public void moveByTheRules() {
        if (behaviorType == BehaviorType.MOVE) {
            moveToTarget(this.targetPos);
        }
    }

    @Override
    protected void initAttackableTarget() {
        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);

        Unit registAttackUnit = null;
        ClockwiseDirInfo registDirInfo = null;
        boolean isRegistSamePos = false;

        for (Unit targetUnit : visibleUnits) {
            boolean isRegistAble = false;
            boolean isSamePos = this.position.equals(targetUnit.getPosition());
            ClockwiseDirInfo attackDir = null;

            if (isSamePos == false) {
                attackDir = getAttackDirInfoOrNull(targetUnit.getPosition(), ATTACKRANGE, false);
                if (attackDir == null) {
                    continue;
                }
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

    @Override
    public char getSymbol() {
        return 'M';
    }
}
