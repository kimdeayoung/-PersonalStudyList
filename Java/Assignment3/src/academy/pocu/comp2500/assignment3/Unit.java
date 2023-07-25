package academy.pocu.comp2500.assignment3;

import java.util.ArrayList;

public abstract class Unit {
    protected final int INTEGERMAX = 2147483647;

    protected IntVector2D position;

    protected int hp;

    protected int ap;

    protected int vision;

    protected BehaviorType behaviorType;

    protected IntVector2D targetPos;

    protected TileType unitTile;
    protected TileType visibleTile;
    protected TileType attackableTile;

    protected int aoe;//areaOfEffect

    protected Unit(IntVector2D position, int vision, TileType unitTile, TileType visibleTile, TileType attackableTile, int aoe, int hp, int ap) {
        this.position = position;
        this.vision = vision;
        this.unitTile = unitTile;
        this.visibleTile = visibleTile;
        this.attackableTile = attackableTile;
        this.aoe = aoe;
        this.hp = hp;
        this.ap = ap;
    }

    public IntVector2D getPosition() {
        return this.position;
    }

    public int getHp() {
        return this.hp;
    }

    public boolean isAlive() {
        return this.hp > 0;
    }

    public int getAp() {
        return ap;
    }

    public int getVision() {
        return vision;
    }

    public BehaviorType getBehaviorType() {
        return behaviorType;
    }

    public IntVector2D getTargetPos() {
        return targetPos;
    }

    public TileType getUnitTile() {
        return unitTile;
    }

    public void setBehaivorTargetInfo(BehaviorType behaviorType, IntVector2D targetPos) {
        this.behaviorType = behaviorType;
        this.targetPos = targetPos.copyTo();
    }

    public int getAoe() {
        return aoe;
    }

    public boolean isAttackableUnit(Unit targetUnit) {
        switch (this.attackableTile) {
            case GROUND:
                switch (targetUnit.unitTile) {
                    case GROUND:
                    case BUILDING:
                    case INVISIBLE_GROUND:
                    case ALL:
                        break;
                    default:
                        return false;
                }
                break;
            case SKY:
                switch (targetUnit.unitTile) {
                    case SKY:
                    case ALL:
                        break;
                    default:
                        return false;
                }
                break;
            case GROUND_AND_SKY:
                switch (targetUnit.unitTile) {
                    case GROUND:
                    case BUILDING:
                    case SKY:
                    case INVISIBLE_GROUND:
                    case ALL:
                        break;
                    default:
                        return false;
                }
                break;
        }

        return true;
    }

    public boolean isVisibleUnit(Unit targetUnit) {
        switch (this.visibleTile) {
            case GROUND:
                switch (targetUnit.unitTile) {
                    case GROUND:
                    case BUILDING:
                    case ALL:
                        break;
                    default:
                        return false;
                }
                break;
            case SKY:
                switch (targetUnit.unitTile) {
                    case SKY:
                    case ALL:
                        break;
                    default:
                        return false;
                }
                break;
            case GROUND_AND_SKY:
                switch (targetUnit.unitTile) {
                    case GROUND:
                    case BUILDING:
                    case SKY:
                    case ALL:
                        break;
                    default:
                        return false;
                }
                break;
            case ALL:
                return true;
        }

        int targetPosX = targetUnit.position.getX();
        int targetPosY = targetUnit.position.getY();

        IntVector2D visionLeftTop = new IntVector2D(position.getX() - vision, position.getY() - vision);
        IntVector2D visionRightBottom = new IntVector2D(position.getX() + vision, position.getY() + vision);

        if (targetPosX >= visionLeftTop.getX() && targetPosX <= visionRightBottom.getX()) {
            if (targetPosY >= visionLeftTop.getY() && targetPosY <= visionRightBottom.getY()) {
                return true;
            }
        }
        return false;
    }

    public boolean isCollidedUnit(Unit targetUnit) {
        switch (targetUnit.unitTile) {
            case GROUND:
            case INVISIBLE_GROUND:
            case BUILDING:
                return this.getPosition().equals(targetUnit.getPosition());
        }
        return false;
    }

    protected ClockwiseDirInfo getAttackDirInfoOrNull(IntVector2D targetUnitPos, int attackRange, boolean isDiagonalAttackable) {
        int unitPosX = position.getX();
        int unitPosY = position.getY();

        int targetUnitPosX = targetUnitPos.getX();
        int targetUnitPosY = targetUnitPos.getY();

        boolean isCalculateable = false;
        boolean isAttackXAxis = true;

        if (unitPosY - attackRange == targetUnitPosY) {
            isCalculateable = true;
            isAttackXAxis = false;
        } else if (unitPosX + attackRange == targetUnitPosX) {
            isCalculateable = true;
        } else if (unitPosY + attackRange == targetUnitPosY) {
            isCalculateable = true;
            isAttackXAxis = false;
        } else if (unitPosX - attackRange == targetUnitPosX) {
            isCalculateable = true;
        }

        if (isCalculateable) {
            isCalculateable = false;
            if (isAttackXAxis) {
                if (isDiagonalAttackable) {
                    if (unitPosY - attackRange <= targetUnitPosY && unitPosY + attackRange >= targetUnitPosY) {
                        isCalculateable = true;
                    }
                } else {
                    if (unitPosY - attackRange < targetUnitPosY && unitPosY + attackRange > targetUnitPosY) {
                        isCalculateable = true;
                    }
                }
            } else {
                if (isDiagonalAttackable) {
                    if (unitPosX - attackRange <= targetUnitPosX && unitPosX + attackRange >= targetUnitPosX) {
                        isCalculateable = true;
                    }
                } else {
                    if (unitPosX - attackRange < targetUnitPosX && unitPosX + attackRange > targetUnitPosX) {
                        isCalculateable = true;
                    }
                }
            }
        }

        if (isCalculateable) {
            ClockwiseDirInfo dirInfo = getClockwiseDir(targetUnitPos);
            return dirInfo;
        }
        return null;
    }

    public ClockwiseDirInfo getClockwiseDir(IntVector2D targetUnitPos) {
        IntVector2D standardPivot = new IntVector2D(0, -1);
        double pivotLength = Math.sqrt((standardPivot.getX() * standardPivot.getX() + (standardPivot.getY() * standardPivot.getY())));
        double normalizePivotX = (double) standardPivot.getX() / pivotLength;
        double normalizePivotY = (double) standardPivot.getY() / pivotLength;

        IntVector2D targetUnitPivot = new IntVector2D(targetUnitPos.getX() - this.position.getX(), targetUnitPos.getY() - this.position.getY());
        double targetUnitLength = Math.sqrt((targetUnitPivot.getX() * targetUnitPivot.getX() + (targetUnitPivot.getY() * targetUnitPivot.getY())));
        double normalizetargetUnitX = (double) targetUnitPivot.getX() / targetUnitLength;
        double normalizetargetUnitY = (double) targetUnitPivot.getY() / targetUnitLength;

        boolean isRightDir = false;
        if ((this.position.getX() == targetUnitPos.getX()) && (this.position.getY() > targetUnitPos.getY())) {
            isRightDir = true;
        } else if (this.position.getX() < targetUnitPos.getX()) {
            isRightDir = true;
        }

        ClockwiseDirInfo result = new ClockwiseDirInfo(isRightDir, (normalizePivotX * normalizetargetUnitX) + (normalizePivotY * normalizetargetUnitY));
        return result;
    }

    public int getManhattanDistance(Unit targetUnit) {
        return Math.abs(position.getX() - targetUnit.getPosition().getX()) + Math.abs(position.getY() - targetUnit.getPosition().getY());
    }

    protected void moveToTarget(IntVector2D targetPos) {
        int posX = this.position.getX();
        int posY = this.position.getY();

        int targetPosX = targetPos.getX();
        int targetPosY = targetPos.getY();

        if (posY != targetPosY) {
            int offsetY = posY - targetPosY;
            offsetY /= Math.abs(offsetY);
            this.position.setY(posY - offsetY);
        } else {
            int offsetX = posX - targetPosX;
            offsetX /= Math.abs(offsetX);
            this.position.setX(posX - offsetX);
        }
    }

    protected void initAttackableTarget() {
    }

    // 공격 의도개체 반환
    public AttackIntent attack() {
        AttackIntent attackIntent = new AttackIntent(this);
        return attackIntent;
    }

    //유닛에 피해치 적용
    public void onAttacked(int damage) {
        this.hp -= damage;
    }

    public void onSpawn() {
    }

    public void onDead() {
    }

    public char getSymbol() {
        return ' ';
    }
}