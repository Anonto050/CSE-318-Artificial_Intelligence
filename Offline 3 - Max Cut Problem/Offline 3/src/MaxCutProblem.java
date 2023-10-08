import java.util.*;

public class MaxCutProblem {
    // define macros
    public static final int SET_S = 0;
    public static final int SET_S_BAR = 1;

    //Constructor
    public int numVertices;
    public int numEdges;
    public int[][] graph;
    int maxIterations;
    double alpha;
    int[] solution;

    int iterations_LocalSearch;
    int totalWeight_SemiGreedy;
    int totalWeight_LocalSearch;

    public MaxCutProblem(int numVertices, int numEdges, int[][] graph,int maxIterations, double alpha) {
        this.numVertices = numVertices;
        this.numEdges = numEdges;
        this.graph = graph;
        this.maxIterations = maxIterations;
        this.alpha = alpha;

        // Initialize solution
        solution = new int[numVertices];
    }

    // Getters
    public int getNumVertices() {
        return numVertices;
    }

    public int getNumEdges() {
        return numEdges;
    }

    public int[][] getGraph() {
        return graph;
    }

    //Initial solution
    public int[] initialSolution() {
        // Randomly assign vertices to sets
        for (int i = 0; i < numVertices; i++) {
            solution[i] = (int) (Math.random() * 2);
        }
        return solution;
    }

    public double getAvgWeight_SemiGreedy(){
        return totalWeight_SemiGreedy/maxIterations;
    }

    public double getAvgWeight_LocalSearch(){
        return totalWeight_LocalSearch/maxIterations;
    }

    public double getAvgIterations_LocalSearch(){
        return iterations_LocalSearch/maxIterations;
    }


    // Apply GRASP to MaxCutProblem
    public int[] applyGRASP() {

        iterations_LocalSearch = 0;
        totalWeight_LocalSearch = 0;
        totalWeight_SemiGreedy = 0;

        int[] bestSolution = new int[numVertices];
        bestSolution = initialSolution();

        int bestCutWeight = calculateCutWeight(bestSolution);

        for (int i = 0; i < maxIterations; i++) {
            int[] candidateSolution = new int[numVertices];
            candidateSolution = semiGreedyConstruction(alpha);

            candidateSolution = localSearch(candidateSolution);

            int candidateCutWeight = calculateCutWeight(candidateSolution);

            if (candidateCutWeight > bestCutWeight) {
                bestCutWeight = candidateCutWeight;
                bestSolution = candidateSolution;
            }
        }

        return bestSolution;
    }


    // Semi greedy construction algorithm

    public int calculateCutWeight(int[] bestSolution) {
        int cutWeight = 0;
        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                if ( graph[i][j] != 0 && bestSolution[i] != bestSolution[j]) {
                    cutWeight += graph[i][j];
                }
            }
        }
        return cutWeight;
    }

    public double calculateGreedyValue(int v, Set<Integer> X, Set<Integer> Y, int[][] edgeWeights) {
        // consider v in set X and sum weights of edges between v and vertices in Y
        double sigma = 0;

        for(int u : Y){
            sigma += edgeWeights[u][v];
        }

        return sigma;
    }

    public int[] semiGreedyConstruction(double alpha){
        int candidateSolution[] = new int[numVertices];
        Arrays.fill(candidateSolution, -1);

        Set<Integer> X = new HashSet<Integer>();
        Set<Integer> Y = new HashSet<Integer>();
        Random rand = new Random();

        int[][] edgeWeights = new int[numVertices][numVertices];
        // copy graph to edgeWeights
        for(int i = 0; i < numVertices; i++){
            for(int j = 0; j < numVertices; j++){
                edgeWeights[i][j] = graph[i][j];
            }
        }

        double w_min = Integer.MAX_VALUE;
        double w_max = Integer.MIN_VALUE;
        double cutoff = 0;

        // Find w_min and w_max

        // Arrays.stream -> returns a stream of elements from the array
        // flatMapToInt -> converts the stream of elements to IntStream
        // min() -> returns the minimum element in the stream
        // getAsInt() -> returns the minimum element as an int
        w_min = Arrays.stream(edgeWeights).flatMapToInt(Arrays::stream).min().getAsInt();
        w_max = Arrays.stream(edgeWeights).flatMapToInt(Arrays::stream).max().getAsInt();

        // Calculate cutoff
        cutoff = w_min + alpha * (w_max - w_min);

        // Construct RCL_e which contains edges with weight >= cutoff
        List<Map.Entry<Integer, Integer>> RCL_e = new ArrayList<Map.Entry<Integer, Integer>>();

        // Iterate through all vertices
        for(int i = 0; i < numVertices; i++){
            for(int j = i+1; j < numVertices; j++){
                if(edgeWeights[i][j] >= cutoff){
                    Map.Entry<Integer, Integer> pair = new AbstractMap.SimpleEntry<Integer, Integer>(i, j);
                    RCL_e.add(pair);
                }
            }
        }

        // Select random edge from RCL_e
        Map.Entry<Integer, Integer> randomEdge = RCL_e.get(rand.nextInt(RCL_e.size()));

        // Add vertices from random edge to X and Y
        X.add(randomEdge.getKey());
        Y.add(randomEdge.getValue());

        // Enter while loop

        while(X.size() + Y.size() < numVertices){
            Set<Integer> unAssignedVertices = new HashSet<Integer>();
            for(int i = 0; i < numVertices; i++){
                if(!X.contains(i) && !Y.contains(i)){
                    unAssignedVertices.add(i);
                }
            }

            // Iterate through all unassigned vertices and store the lowest greedy value for X and Y
            double minGreedyValueX = Integer.MAX_VALUE;
            double minGreedyValueY = Integer.MAX_VALUE;
            double maxGreedyValueX = Integer.MIN_VALUE;
            double maxGreedyValueY = Integer.MIN_VALUE;

            for(int v : unAssignedVertices){
                double greedyValueX = calculateGreedyValue(v, X, Y, edgeWeights);
                double greedyValueY = calculateGreedyValue(v, Y, X, edgeWeights);

                if(greedyValueX < minGreedyValueX){
                    minGreedyValueX = greedyValueX;
                }

                if(greedyValueY < minGreedyValueY){
                    minGreedyValueY = greedyValueY;
                }

                if(greedyValueX > maxGreedyValueX){
                    maxGreedyValueX = greedyValueX;
                }

                if(greedyValueY > maxGreedyValueY){
                    maxGreedyValueY = greedyValueY;
                }
            }

            // Calculate cutoff
            w_min = Math.min(minGreedyValueX, minGreedyValueY);
            w_max = Math.max(maxGreedyValueX, maxGreedyValueY);

            cutoff = w_min + alpha * (w_max - w_min);

            List<Integer> RCL_v = new ArrayList<Integer>(); // Restricted candidate list

            // Iterate through all unassigned vertices and add vertices with greedy value >= cutoff to RCL_v
            for(int v : unAssignedVertices){
                double greedyValueX = calculateGreedyValue(v, X, Y, edgeWeights);
                double greedyValueY = calculateGreedyValue(v, Y, X, edgeWeights);

                if(Math.max(greedyValueX, greedyValueY) >= cutoff){
                    RCL_v.add(v);
                }
            }

            // Select random vertex from RCL_v
            int randomVertex = RCL_v.get(rand.nextInt(RCL_v.size()));

            // Add random vertex to X or Y
            double sigmaX = calculateGreedyValue(randomVertex, X, Y, edgeWeights);
            double sigmaY = calculateGreedyValue(randomVertex, Y, X, edgeWeights);

            if(sigmaX>sigmaY){
                X.add(randomVertex);
            }else{
                Y.add(randomVertex);
            }
        }

        // Assign vertices to sets
        for(int v : X){
            candidateSolution[v] = SET_S;
        }

        for(int v : Y){
            candidateSolution[v] = SET_S_BAR;
        }

        totalWeight_SemiGreedy += calculateCutWeight(candidateSolution);

        return candidateSolution;
    }

    // Local search algorithm

    // Calculate delta
    public double calculateDelta(int v, Set<Integer> X, Set<Integer> Y, int[] candidateSolution) {
        double delta = 0;

        for(int i = 0; i < numVertices; i++){
            if(i != v){
                // if i is in Y and v is in X, add weight of edge between i and v to delta
                if(Y.contains(i)){
                    delta += graph[i][v];
                }
                // if i and v are in the same set, subtract weight of edge between i and v from delta
                else if(X.contains(i)){
                    delta -= graph[i][v];
                }
            }
        }

        return delta;
    }

    public int[] localSearch(int[] candidateSolution) {
        int count = 0;

        // construct S, S_bar set from candidateSolution
        Set<Integer> S = new HashSet<Integer>();
        Set<Integer> S_bar = new HashSet<Integer>();

        for(int i = 0; i < numVertices; i++){
            if(candidateSolution[i] == SET_S){
                S.add(i);
            }else{
                S_bar.add(i);
            }
        }

        boolean changed = true;
        while (changed) {
            changed = false;
            count++;

            for(int i = 0; i < numVertices; i++){
                if(changed){
                    break;
                }
                if(candidateSolution[i] == SET_S){
                    double delta = 0;
                    delta = calculateDelta(i, S, S_bar, candidateSolution);

                    if(delta < 0){
                        candidateSolution[i] = SET_S_BAR;
                        S.remove(i);
                        S_bar.add(i);
                        changed = true;
                    }
                }

                else if(candidateSolution[i] == SET_S_BAR){
                    double delta = 0;
                    delta = calculateDelta(i, S_bar, S, candidateSolution);

                    if(delta < 0){
                        candidateSolution[i] = SET_S;
                        S.add(i);
                        S_bar.remove(i);
                        changed = true;
                    }
                }
            }
        }

        totalWeight_LocalSearch += calculateCutWeight(candidateSolution);
        iterations_LocalSearch += count;
        return candidateSolution;
    }
}
