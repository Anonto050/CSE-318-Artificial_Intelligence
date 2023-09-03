# Decision Tree Algorithm for Car Evaluation

## Overview
This project implements a decision tree learning algorithm for car evaluation based on the provided dataset. The goal is to build a decision tree classifier to predict the acceptability of cars based on their attributes. The project is implemented in Java.

## Problem Statement
The problem statement and dataset details can be found in the [problem statement PDF](https://github.com/Anonto050/CSE-318-Artificial_Intelligence/blob/main/Offline%204%20-%20Decision%20Tree/CSE318_%20Assignment%204.pdf). In summary, the dataset consists of various attributes related to car evaluation, such as buying price, maintenance cost, number of doors, etc., and the task is to classify cars into four categories: 'unacc' (unacceptable), 'acc' (acceptable), 'good', and 'vgood' (very good).

## Solution Highlights


1. **Data Preprocessing**: The provided dataset is preprocessed to prepare it for building the decision tree. This includes parsing the dataset, handling missing values, and splitting it into training and testing sets.

2. **Node Representation**: The `Node` class is used to represent nodes in the decision tree. Each node contains information about the attribute it represents, the attribute value that leads to it, the classification decision at leaf nodes, and child nodes.

3. **Information Gain**: The algorithm selects the best attribute at each node based on information gain. Information gain measures how much the attribute helps in reducing uncertainty about the classification.

4. **Tree Building**: The decision tree is built recursively. The algorithm selects the attribute with the highest information gain, creates a new node for it, and continues building the tree for each branch.

5. **Classification**: Once the tree is built, it is used to classify new examples by traversing the tree from the root to a leaf node.

6. **Testing and Accuracy Calculation**: The dataset is randomly divided into training (80%) and testing (20%) sets. The decision tree classifier is trained on the training data and tested on the testing data. This process is repeated 20 times to calculate the average test accuracy. The mean accuracy and standard deviation of accuracy are reported.


## Decision Tree Learning Algorithm

The heart of this project is the decision tree learning algorithm. Here's an explanation of how the algorithm works using code segments:

### Node Representation
```java
public class Node {
    private String attribute;
    private String decision;
    private Map<String, Node> children;
    
    // Constructor and methods...
}
```

- The `Node` class represents nodes in the decision tree.
- Each node has:
    - `attribute`: The attribute being considered at this node.
    - `decision`: The classification decision at this node (empty for internal nodes).
    - `children`: Child nodes representing different attribute values.


### Tree Building 

The tree building process is a crucial part of the decision tree learning algorithm. It's responsible for constructing the decision tree that can be used for classification. Here's a step-by-step explanation of how the tree is built:

- **Selecting the Best Attribute**: The first step is to choose the best attribute for the current node. The "best" attribute is the one that provides the most information gain, which helps in making accurate classifications. The algorithm calculates the information gain for each attribute and selects the one with the highest value. This attribute becomes the attribute for the current node.

    ```java
    String bestAttribute = null;
    double bestInformationGain = 0;
    for (String attribute : attributes) {
        double informationGain = calculateInformationGain(examples, attribute);
        if (informationGain > bestInformationGain) {
            bestAttribute = attribute;
            bestInformationGain = informationGain;
        }
    }
    ```

- **Creating an Internal Node**: A new internal node is created with the selected attribute. This internal node will be a decision point in the tree, and its attribute helps in determining which branch to follow.

    ```java
    Node tree = new Node(bestAttribute, "");
    ```

- **Splitting into Branches**: For each possible value of the selected attribute, the algorithm creates a new branch. These branches represent different paths that the decision tree can take based on the attribute's value.

    ```java
    Set<String> attributeValues = examples.stream()
        .map(example -> example.getValues().get(bestAttribute))
        .collect(Collectors.toSet());

    for (String attributeValue : attributeValues) {
        // Create a new branch for each attribute value...
    }
    ```

- **Subset Creation**: For each branch, the algorithm creates a subset of examples that have the same value for the selected attribute. These subsets represent the data that will be considered for further tree building within that branch.

    ```java
    // Create a new subset of examples where the best attribute has the given value
    List<Example> subsetExamples = examples.stream()
        .filter(example -> example.getValues().get(bestAttribute).equals(attributeValue))
        .collect(Collectors.toList());
    ```

- **Recursive Tree Building**: The tree-building process continues recursively for each branch. For each branch, the algorithm considers a subset of examples and a reduced set of attributes (excluding the attribute used at the current node). This recursive process builds subtrees for each branch.

    ```java
    Node subtree = learnDecisionTree(subsetExamples, subsetAttributes, Class, examples);
    ```

- **Adding Branches to the Tree**: Each branch is attached to the current node as a child node. These branches represent different attribute values and the subtrees associated with them.

    ```java
    tree.addChild(attributeValue, subtree);
    ```

- **Return the Current Node**: The current node (with its attribute) represents the decision point based on the selected attribute. The algorithm continues building the tree until all branches have been processed.

    ```java
    return tree;
    ```

This process repeats recursively for each internal node in the tree until all attributes have been used or a stopping condition is met (e.g., a node has only one class left). The resulting decision tree represents a hierarchical set of decisions based on the attributes and their values, leading to a classification decision at the leaf nodes.

By constructing this tree, the algorithm can effectively classify new examples by following the appropriate branches based on their attribute values, ultimately reaching a leaf node with a classification decision.

### Information Gain
```java
public static double importance(String attribute, List<Example> examples) {
    // Calculate information gain for the attribute based on class distribution.
    // More code...
}
```

- The `importance` function calculates information gain for each attribute.
- Information gain measures how much an attribute helps in reducing uncertainty about the classification.

### Classification
```java
public static String classifyExample(Node root, Example example) {
    // Classify a new example by traversing the decision tree.
    // More code...
}
```

- The `classifyExample` function uses the trained decision tree to classify new examples.
- Starting from the root node, it considers the attribute value of the current example and moves to the corresponding child node until it reaches a leaf node containing the classification decision.

---

These code segments represent the core components of the decision tree learning algorithm. The algorithm intelligently selects attributes based on information gain, builds a tree structure, and uses the tree for accurate classification. This approach is fundamental to supervised machine learning and can be applied to various classification tasks, including car evaluation based on attributes.

## Usage
1. Clone the repository.
2. Compile and run the Java program to build the decision tree and perform classification.
3. The program will provide the average test accuracy and standard deviation as output.

## Dependencies
- Java (JDK 8 or later)

## Dataset
The dataset used in this project is provided in the `car_data.txt` file. The attributes and class values can be found in the `car_names.txt` file.

## License
This project is licensed under the [MIT License](LICENSE).

