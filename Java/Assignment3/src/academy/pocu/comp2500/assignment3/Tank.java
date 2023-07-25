package academy.pocu.comp2500.assignment3;

import java.util.ArrayList;

public class Tank extends Unit implements IThinkable, IMovable {
    private final int ATTACKRANGE = 2;
    private int moveXDir;

    private boolean isSiegeMode;

    public Tank(IntVector2D position) {
        super(position, 3, TileType.GROUND, TileType.GROUND, TileType.GROUND, 1, 85, 8);
        this.isSiegeMode = false;
        this.moveXDir = 1;
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
        this.behaviorType = BehaviorType.NONE;
        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);

        if (visibleUnits.size() > 0) {
            if (this.isSiegeMode) {
                initAttackableTarget();
            } else {
                this.isSiegeMode = true;
                this.behaviorType = BehaviorType.UNIT_SPECIFIC;
            }
        } else {
            if (this.isSiegeMode) {
                this.isSiegeMode = false;
                this.behaviorType = BehaviorType.UNIT_SPECIFIC;
            } else {
                specifyDirOfMovement();
            }
        }
    }

    @Override
    public void specifyDirOfMovement() {
        int posX = this.position.getX();
        this.behaviorType = BehaviorType.MOVE;
        if (posX <= 0) {
            this.moveXDir = 1;
        } else if (posX >= SimulationManager.getInstance().getWorldSizeX()) {
            this.moveXDir = -1;
        }
    }

    @Override
    public void moveByTheRules() {
        if (behaviorType == BehaviorType.MOVE) {
            this.position.setX(this.position.getX() + this.moveXDir);
        }
    }

    protected void initAttackableTarget() {
        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);

        Unit registAttackUnit = null;
        ClockwiseDirInfo registDirInfo = null;

        for (Unit targetUnit : visibleUnits) {
            boolean isRegistAble = false;
            ClockwiseDirInfo attackDir = getAttackDirInfoOrNull(targetUnit.getPosition(), ATTACKRANGE, false);

            if (attackDir == null) {
                continue;
            }

            if (registAttackUnit == null) {
                isRegistAble = true;
            } else {
                if (registAttackUnit.getHp() > targetUnit.getHp()) {
                    isRegistAble = true;
                } else if (registAttackUnit.getHp() == targetUnit.getHp()) {
                    if (attackDir.isHigherClockwise(registDirInfo)) {
                        isRegistAble = true;
                    }
                }
            }

            if (isRegistAble) {
                registAttackUnit = targetUnit;
                registDirInfo = attackDir;
            }
        }

        if (registAttackUnit != null) {
            setBehaivorTargetInfo(BehaviorType.ATTACK, registAttackUnit.getPosition());
        }
    }

    @Override
    public void onAttacked(int damage) {
        if (isSiegeMode) {
            damage *= 2;
        }

        this.hp -= damage;
    }

    public char getSymbol() {
        return 'T';
    }

    ;
}
