package academy.pocu.comp2500.assignment3;

import java.util.ArrayList;

public class Wraith extends Unit implements IThinkable, IMovable {
    private final int ATTACKRANGE = 1;
    private IntVector2D spawnPos;
    private boolean isActiveShiled;
    private int useableShiledCount;

    public Wraith(IntVector2D position) {
        super(position, 4, TileType.SKY, TileType.GROUND_AND_SKY, TileType.GROUND_AND_SKY, 0, 80, 6);
        useableShiledCount = 1;
        spawnPos = this.position.copyTo();
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

    @Override
    public void behaviorDecision() {
        this.targetPos = null;
        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);
        this.isActiveShiled = false;

        this.behaviorType = BehaviorType.NONE;
        if (visibleUnits.size() > 0) {
            initAttackableTarget();
            if (this.behaviorType == BehaviorType.NONE) {
                specifyDirOfMovement();
            }
        } else {
            this.behaviorType = BehaviorType.UNIT_SPECIFIC;
        }
    }

    @Override
    public void specifyDirOfMovement() {
        int lowDistance = INTEGERMAX;
        ClockwiseDirInfo registDirInfo = null;
        Unit registTargetUnit = null;

        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnitsWithTryFilter(this, TileType.SKY);
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

    @Override
    public void moveByTheRules() {
        switch (this.behaviorType) {
            case MOVE:
                moveToTarget(this.targetPos);
                break;
            case UNIT_SPECIFIC:
                if (this.position.equals(this.spawnPos) == false) {
                    moveToTarget(this.spawnPos);
                }
                break;
        }
    }

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
                if (isSamePos == true || attackDir != null) {
                    switch (targetUnit.getUnitTile()) {
                        case SKY:
                            switch (registAttackUnit.getUnitTile()) {
                                case GROUND:
                                case BUILDING:
                                    isRegistAble = true;
                                    break;
                            }
                            break;
                        default:
                            if (registAttackUnit.getUnitTile() == TileType.SKY) {
                                continue;
                            }
                            break;
                    }
                }

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
    public void onAttacked(int damage) {
        if (this.useableShiledCount > 0) {
            this.useableShiledCount -= 1;
            this.isActiveShiled = true;
        }

        if (this.isActiveShiled == false) {
            this.hp -= damage;
        }
    }

    public char getSymbol() {
        return 'W';
    }
}
