package academy.pocu.comp2500.assignment3;

import java.util.ArrayList;
import java.util.Iterator;

public final class SimulationManager {
    private static SimulationManager instance;

    private int worldSizeX;
    private int worldSizeY;

    private ArrayList<Unit> units;

    private ArrayList<IThinkable> thinkableUnits;

    private ArrayList<IMovable> movableUnits;

    private ArrayList<ICollisionEvent> collisionEvents;

    private SimulationManager() {
        this.units = new ArrayList<>();
        this.thinkableUnits = new ArrayList<>();
        this.movableUnits = new ArrayList<>();
        this.collisionEvents = new ArrayList<>();

        this.worldSizeX = 15;
        this.worldSizeY = 7;
    }

    public static SimulationManager getInstance() {
        if (instance == null) {
            instance = new SimulationManager();
        }

        return instance;
    }

    public int getWorldSizeX() {
        return worldSizeX;
    }

    public int getWorldSizeY() {
        return worldSizeY;
    }

    public ArrayList<Unit> getUnits() {
        return units;
    }

    public void spawn(Unit unit) {
        this.units.add(unit);
        unit.onSpawn();
    }

    public ArrayList<Unit> getVisibleUnits(Unit unit) {
        ArrayList<Unit> visibleUnits = new ArrayList<>();

        for (Unit findUnit : units) {
            if (findUnit.equals(unit) == false) {
                if (unit.isVisibleUnit(findUnit)) {
                    visibleUnits.add(findUnit);
                }
            }
        }
        return visibleUnits;
    }

    public ArrayList<Unit> getVisibleUnitsWithTryFilter(Unit unit, TileType tileFilter) {
        ArrayList<Unit> visibleUnits = getVisibleUnits(unit);
        ArrayList<Unit> filteredVisibleUnits = new ArrayList<>();

        for (Unit findUnit : visibleUnits) {
            if (findUnit.getUnitTile() == tileFilter) {
                filteredVisibleUnits.add(findUnit);
            }
        }

        if (filteredVisibleUnits.size() > 0) {
            return filteredVisibleUnits;
        } else {
            return visibleUnits;
        }
    }

    public ArrayList<Unit> getCollidedUnits(Unit unit) {
        ArrayList<Unit> collidedUnits = new ArrayList<>();

        for (Unit findUnit : units) {
            if (findUnit.equals(unit) == false) {
                if (unit.isCollidedUnit(findUnit)) {
                    collidedUnits.add(findUnit);
                }
            }
        }
        return collidedUnits;
    }

    public void registerThinkable(IThinkable thinkable) {
        this.thinkableUnits.add(thinkable);
    }

    public boolean unregisterThinkable(IThinkable thinkable) {
        return this.thinkableUnits.remove(thinkable);
    }

    public void registerMovable(IMovable movable) {
        this.movableUnits.add(movable);
    }

    public boolean unregisterMovable(IMovable movable) {
        return this.movableUnits.remove(movable);
    }

    public void registerCollisionEventListener(ICollisionEvent listener) {
        this.collisionEvents.add(listener);
    }

    public boolean unregisterCollisionEventListener(ICollisionEvent listener) {
        return this.collisionEvents.remove(listener);
    }

    public void update() {
        for (IThinkable thinkableObj : thinkableUnits) {
            thinkableObj.behaviorDecision();
        }

        for (IMovable movableObj : movableUnits) {
            movableObj.moveByTheRules();
        }

        for (ICollisionEvent event : collisionEvents) {
            event.collsionEvent();
        }

        for (Unit unit : units) {
            if (unit.getBehaviorType() == BehaviorType.ATTACK) {
                AttackIntent attackIntent = unit.attack();

                for (Unit attackTarget : units) {
                    if (unit.equals(attackTarget) == false && unit.isAttackableUnit(attackTarget)) {
                        int damage = attackIntent.getDamage(attackTarget.getPosition());
                        if (damage != -1) {
                            attackTarget.onAttacked(damage);
                        }
                    }
                }
            }
        }

        Iterator<Unit> unitIter = this.units.iterator();
        while (unitIter.hasNext()) {
            Unit unit = unitIter.next();
            if (unit.isAlive() == false) {
                unit.onDead();
                unitIter.remove();
            }
        }
    }
}