import java.io.BufferedReader;
import java.io.FileReader;
import java.util.*;
import java.util.stream.Collectors;

public class DecisionTree {
    // Default constructor
    public DecisionTree() {
    }

    // Returns the most common classification in the given examples
    public static String pluralityValue(List<Example> examples, List<String> Class) {
        Map<String, Long> classCounts = examples.stream()
                .collect(Collectors.groupingBy(Example::getClassification, Collectors.counting()));
        return Collections.max(classCounts.entrySet(), Map.Entry.comparingByValue()).getKey();
    }

    // Returns true if all examples have the same classification
    public static boolean allSameClassification(List<Example> examples, List<String> Class) {
        String classification = examples.get(0).getClassification();
        for (Example example : examples) {
            if (!example.getClassification().equals(classification)) {
                return false;
            }
        }
        return true;
    }

    // Calculates the entropy of the given examples
    public static double calculateEntropy(Map<String,Long> classCounts, long numExamples) {
        double entropy = 0;
        for (Long count : classCounts.values()) {
            double probability = (double) count / (double) numExamples;
            entropy -= probability * (Math.log(probability) / Math.log(2));
        }
        return entropy;
    }

    // Calculates the information gain of the given examples and attribute
    public static double calculateInformationGain(List<Example> examples, String attribute){
        // Calculate entropy for parent
        Set<String> attributeValues = examples.stream()
                .map(example -> example.getValues().get(attribute))
                .collect(Collectors.toSet());
        Map<String, Long> classCounts = examples.stream()
                .collect(Collectors.groupingBy(Example::getClassification, Collectors.counting()));
        double entropy = calculateEntropy(classCounts, examples.size());

        // Calculate entropy for children
        double remainder = 0;
        for (String attributeValue : attributeValues) {
            List<Example> subsetExamples = examples.stream()
                    .filter(example -> example.getValues().get(attribute).equals(attributeValue))
                    .collect(Collectors.toList());
            Map<String, Long> subsetClassCounts = subsetExamples.stream()
                    .collect(Collectors.groupingBy(Example::getClassification, Collectors.counting()));
            double subsetEntropy = calculateEntropy(subsetClassCounts, subsetExamples.size());

            // Calculate remainder
            remainder += ((double) subsetExamples.size() / (double) examples.size()) * subsetEntropy;

        }

        // Calculate information gain
        double informationGain = entropy - remainder;
        return informationGain;
    }


    public static Node learnDecisionTree (List<Example> examples, Set<String> attributes, List<String> Class, List<Example> parentExamples,String parentAttributeValue){

        // If examples is empty, return a leaf node with the most common classification in the parent examples
        if (examples.isEmpty()) {
            return new Node("", pluralityValue(parentExamples, Class),parentAttributeValue);
        }
        // If all examples have the same classification, return a leaf node with that classification
        else if (allSameClassification(examples, Class)) {
            return new Node("", examples.get(0).getClassification(),parentAttributeValue);
        }

        // If attributes is empty, return a leaf node with the most common classification
        else if (attributes.isEmpty()) {
            return new Node("", pluralityValue(examples, Class),parentAttributeValue);
        }

        else {

            // Otherwise, choose the attribute with the highest information gain
            String bestAttribute = null;
            double bestInformationGain = 0;
            for (String attribute : attributes) {
                double informationGain = calculateInformationGain(examples, attribute);
                if (informationGain > bestInformationGain) {
                    bestAttribute = attribute;
                    bestInformationGain = informationGain;
                }
            }

            // Create a new internal node with the best attribute
            Node tree = new Node(bestAttribute, "",parentAttributeValue);

            // For each possible value of the best attribute, create a new branch
            //Set<String> attributeValues = examples.get(0).getValues().keySet();


            String finalBestAttribute1 = bestAttribute;
            Set<String> attributeValues = examples.stream()
                    .map(example -> example.getValues().get(finalBestAttribute1))
                    .collect(Collectors.toSet());

            for (String attributeValue : attributeValues) {
                // Create a new subset of examples where the best attribute has the given value
                String finalBestAttribute = bestAttribute;
                List<Example> subsetExamples = examples.stream()
                        .filter(example -> example.getValues().get(finalBestAttribute).equals(attributeValue))
                        .collect(Collectors.toList());

                // Create a new subset of attributes that does not contain the best attribute
                Set<String> subsetAttributes = new HashSet<>(attributes);
                subsetAttributes.remove(bestAttribute);


                // Recursively call learnDecisionTree() on the new subset of examples and attributes
                Node subtree = learnDecisionTree(subsetExamples, subsetAttributes, Class, examples,attributeValue);

                // Add the new branch to the tree
                tree.addChild(attributeValue, subtree);
            }

            return tree;
        }
    }

    public static List<List<Example>> splitData(List<Example> examples, double splitRatio) {
        // Shuffle examples
        Collections.shuffle(examples);
        int splitIndex = (int) Math.round(examples.size() * splitRatio);
        List<Example> trainingSet = examples.subList(0, splitIndex);
        List<Example> testSet = examples.subList(splitIndex, examples.size());
        return Arrays.asList(trainingSet, testSet);
    }

    // classify each example
    public static String classifyExample(Node currentNode, Example example){

        // Start from the root node attribute. Iterate through the children of the root node and match the value of the root node attribute of example to the value of the child node.
        // Then enter the child node and repeat the process until you reach a leaf node.
        // Return the classification of the leaf node.
        if (currentNode.isLeaf()) {
            return currentNode.getDecision();
        }
        else {
            String attributeValue = example.getValues().get(currentNode.getAttribute());
            //System.out.println("Attribute value: " + attributeValue);
            if(attributeValue == null){
                return currentNode.getDecision();
            }
            Node nextNode = currentNode.getChildren().get(attributeValue);
            if(nextNode == null){
                return currentNode.getDecision();
            }
            //System.out.println("Next node: " + nextNode);
            return classifyExample(nextNode, example);
        }
    }

    public static double testAccuracy(List<Example> testSet, Node root){
        int numCorrect = 0;
        for (Example example : testSet) {
            String predictedClassification = classifyExample(root, example);
            if (predictedClassification.equals(example.getClassification())) {
                numCorrect++;
            }
            //System.out.println("Predicted classification: " + predictedClassification + ", Actual classification: " + example.getClassification());
        }
        return (double) numCorrect / (double) testSet.size();
    }

    public static void main(String[] args) {

        String exampleFilePath = "car_data.txt";
        List<Example> examples = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(exampleFilePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(",");
                Map<String, String> attributeValues = new HashMap<>();
                attributeValues.put("buying", values[0]);
                attributeValues.put("maint", values[1]);
                attributeValues.put("doors", values[2]);
                attributeValues.put("persons", values[3]);
                attributeValues.put("lug_boot", values[4]);
                attributeValues.put("safety", values[5]);
                String classification = values[6];
                Example example = new Example(attributeValues, classification);
                examples.add(example);
            }
            br.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        Set<String> attributes = new HashSet<>(Arrays.asList("buying", "maint", "doors", "persons", "lug_boot", "safety"));
        List<String> Class = Arrays.asList("unacc", "acc", "good", "vgood");

        double splitRatio = 0.8;
        int numTrials = 20;

        List<Double> accuracies = new ArrayList<>();

        for (int i = 0; i < numTrials; i++) {

            List<List<Example>> splitData = splitData(examples, splitRatio);
            List<Example> trainingSet = splitData.get(0);
            List<Example> testSet = splitData.get(1);

            Node root = learnDecisionTree(trainingSet, attributes, Class, trainingSet,"");
            // print out the decision tree
//            System.out.println("Decision tree:");
//            System.out.println(root.toString(0));
            double accuracy = testAccuracy(testSet, root);
            accuracies.add(accuracy);
        }

        double totalAccuracy = 0;
        for (Double accuracy : accuracies) {
            totalAccuracy += accuracy;
        }
        double meanAccuracy = totalAccuracy / numTrials;
        double standardDeviation = 0;
        for (Double accuracy : accuracies) {
            standardDeviation += Math.pow(accuracy - meanAccuracy, 2);
        }
        standardDeviation = Math.sqrt(standardDeviation / numTrials);

        System.out.println("Mean accuracy: " + meanAccuracy);
        System.out.println("Standard deviation: " + standardDeviation);

    }
}
