package academy.pocu.comp2500.assignment3;

public class Mine extends Unit implements ICollisionEvent {
    protected int touchCount;
    protected int explosionAbleCount;

    public Mine(IntVector2D position, int explosionAbleCount) {
        super(position, 0, TileType.INVISIBLE_GROUND, TileType.NONE, TileType.GROUND, 0, 1, 10);
        this.explosionAbleCount = explosionAbleCount;
        this.behaviorType = BehaviorType.UNIT_SPECIFIC;
    }

    protected Mine(IntVector2D position, int explosionAbleCount, int vision, int aoe, int ap) {
        this(position, explosionAbleCount);
        this.aoe = aoe;
        this.ap = ap;
        this.vision = vision;
    }

    @Override
    public void onSpawn() {
        SimulationManager.getInstance().registerCollisionEventListener(this);
    }

    @Override
    public void onDead() {
        SimulationManager.getInstance().registerCollisionEventListener(this);
    }

    public void collsionEvent() {
        int collsionCount = SimulationManager.getInstance().getCollidedUnits(this).size();
        if (collsionCount > 0) {
            this.touchCount += collsionCount;
            if (this.touchCount >= this.explosionAbleCount) {
                initExplosionMine();
            }
        }
    }

    protected void initExplosionMine() {
        setBehaivorTargetInfo(BehaviorType.ATTACK, this.getPosition());
        this.hp = 0;
    }

    public char getSymbol() {
        return 'N';
    }
}
