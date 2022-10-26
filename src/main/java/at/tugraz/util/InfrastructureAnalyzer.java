package at.tugraz.util;

public class InfrastructureAnalyzer {
   private static int localPar = -1;

    static {
        //analyze local node properties
        analyzeLocalMachine();
    }

    public static int getLocalParallelism() {
        return localPar;
    }

    /**
     * Analyzes properties of local machine and JVM.
     */
    private static void analyzeLocalMachine() {
        localPar = Runtime.getRuntime().availableProcessors();
    }
}

