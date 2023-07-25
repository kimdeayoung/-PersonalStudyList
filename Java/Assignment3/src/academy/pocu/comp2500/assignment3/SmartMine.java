package academy.pocu.comp2500.assignment3;

import java.util.ArrayList;

public class SmartMine extends Mine implements IThinkable {
    private int detectedCount;

    public SmartMine(IntVector2D position, int explosionAbleCount, int detectedCount) {
        super(position, explosionAbleCount, 1, 1, 15);
        this.visibleTile = TileType.GROUND;
        this.detectedCount = detectedCount;
    }

    @Override
    public void onSpawn() {
        super.onSpawn();
        SimulationManager.getInstance().registerThinkable(this);
    }

    @Override
    public void onDead() {
        super.onDead();
        SimulationManager.getInstance().unregisterThinkable(this);
    }

    @Override
    public void behaviorDecision() {
        ArrayList<Unit> visibleUnits = SimulationManager.getInstance().getVisibleUnits(this);

        int detectUnitCount = 0;
        for (Unit unit : visibleUnits) {
            switch (unit.unitTile) {
                case GROUND:
                case BUILDING:
                    ++detectUnitCount;
                    break;
            }
        }

        if (detectUnitCount >= detectedCount) {
            initExplosionMine();
        }
    }

    public char getSymbol() {
        return 'A';
    }
}
