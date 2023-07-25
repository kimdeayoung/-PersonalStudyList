package academy.pocu.comp2500.assignment3;

public class Destroyer extends Unit implements IThinkable {
    public Destroyer(IntVector2D position) {
        super(position, 0, TileType.ALL, TileType.ALL, TileType.ALL, 100, 2147483647, 214740);
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
        this.behaviorType = BehaviorType.ATTACK;
        this.targetPos = this.position;
    }

    @Override
    public void onAttacked(int damage) {
        this.hp -= 1;
    }

    public char getSymbol() {
        return 'D';
    }
}
