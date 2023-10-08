import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {

        int[] input = { 20, 21, 25, 26, 27, 28, 29, 30 }; //
        int[] knownBestSolutions = {0, 0, 0, 0, 0, 0, 0, 0}; //

        //Write outputs to csv file
        String outputFileName = "output.csv";

        try (FileWriter writer = new FileWriter(outputFileName,true)) {

            for (int i = 0; i < input.length; i++) {
                String fileName = "set1/g" + input[i] + ".rud";
                File file = new File(fileName);
                Scanner sc = new Scanner(file);

                int numVertices = sc.nextInt();
                int numEdges = sc.nextInt();
                // Create 2D array of weights
                int[][] graph = new int[numVertices][numVertices];

                //Initialize 2D array of weights to 0
                for (int j = 0; j < numVertices; j++) {
                    for (int k = 0; k < numVertices; k++) {
                        graph[j][k] = 0;
                    }
                }

                // Fill 2D array of weights with weights from input file
                for (int j = 0; j < numEdges; j++) {
                    int vertex1 = sc.nextInt();
                    int vertex2 = sc.nextInt();
                    int weight = sc.nextInt();
                    graph[vertex1-1][vertex2-1] = weight;
                    graph[vertex2-1][vertex1-1] = weight;
                }

                // Close scanner
                sc.close();

                double[] alphaValues = { 0.5, 0.6, 0.7, 0.8, 0.9 };
                Random random = new Random();
                int randomIndex = random.nextInt(alphaValues.length);
                double alpha = alphaValues[randomIndex];

                int maxIterations = 10;

                double randomizedBestValue = 0;
                double greedyBestValue = 0;
                double semiGreedyBestValue = 0;
                double localSearchBestValue = 0;
                double graspBestValue = 0;
                double localSearchIterations = 0;

                // Create new MaxCutProblem object
                MaxCutProblem maxCutProblem = new MaxCutProblem(numVertices, numEdges, graph, maxIterations, alpha);
                int[] solution = new int[numVertices];
                double bestValue = 0;

                // Run Simple Randomized Algorithm maxIterations times and write results to csv file
                for (int j = 0; j < maxIterations; j++) {
                    solution = maxCutProblem.semiGreedyConstruction(0);
                    randomizedBestValue += maxCutProblem.calculateCutWeight(solution);
                }
                randomizedBestValue = randomizedBestValue / maxIterations;

                // Run Simple Greedy Algorithm maxIterations times and write results to csv file
                for (int j = 0; j < maxIterations; j++) {
                    solution = maxCutProblem.semiGreedyConstruction(1);
                    greedyBestValue += maxCutProblem.calculateCutWeight(solution);
                }
                greedyBestValue = greedyBestValue / maxIterations;

                // Run Grasp Algorithm maxIterations times and write results to csv file
                solution = maxCutProblem.applyGRASP();
                graspBestValue = maxCutProblem.calculateCutWeight(solution);

                semiGreedyBestValue = maxCutProblem.getAvgWeight_SemiGreedy();
                localSearchBestValue = maxCutProblem.getAvgWeight_LocalSearch();
                localSearchIterations = maxCutProblem.getAvgIterations_LocalSearch();

                System.out.println("G" + input[i] + " done.");
                // Write results to csv file
                String input_file = "G" + input[i];
                writer.append(input_file + "," + numVertices + "," + numEdges + "," + randomizedBestValue + "," + greedyBestValue + "," + semiGreedyBestValue + "," + localSearchIterations + "," + localSearchBestValue + "," + maxIterations + "," + graspBestValue + ","  + knownBestSolutions[i] + "\n");
                System.out.println(input_file + "," + numVertices + "," + numEdges + "," + randomizedBestValue + "," + greedyBestValue + "," + semiGreedyBestValue + "," + localSearchIterations + "," + localSearchBestValue + "," + maxIterations + "," + graspBestValue + ","  + knownBestSolutions[i] + "\n");
            }

            //System.out.println("CSV file created successfully.");
        } catch (IOException e) {
            System.out.println("An error occurred while writing the CSV file.");
            e.printStackTrace();
        }
    }
}