package at.tugraz.util;

public class OptimizerUtils {

    public static final double PARALLEL_CP_WRITE_PARALLELISM_MULTIPLIER = 1.0;

    public static int getParallelWriteParallelism() {
        double dop = InfrastructureAnalyzer.getLocalParallelism() * PARALLEL_CP_WRITE_PARALLELISM_MULTIPLIER;
        return (int) Math.round(dop);
    }
}
