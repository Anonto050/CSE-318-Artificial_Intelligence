# Decision Tree Algorithm for Car Evaluation

## Overview
This project implements a decision tree learning algorithm for car evaluation based on the provided dataset. The goal is to build a decision tree classifier to predict the acceptability of cars based on their attributes. The project is implemented in Java.

## Problem Statement
The problem statement and dataset details can be found in the [problem statement PDF](https://github.com/Anonto050/CSE-318-Artificial_Intelligence/blob/main/Offline%204%20-%20Decision%20Tree/CSE318_%20Assignment%204.pdf). In summary, the dataset consists of various attributes related to car evaluation, such as buying price, maintenance cost, number of doors, etc., and the task is to classify cars into four categories: 'unacc' (unacceptable), 'acc' (acceptable), 'good', and 'vgood' (very good).

## Solution Highlights

### Decision Tree Learning Algorithm
The project implements a decision tree learning algorithm to build a decision tree classifier based on the information gain criterion. Here are the significant parts of the solution:

1. **Data Preprocessing**: The provided dataset is preprocessed to prepare it for building the decision tree. This includes parsing the dataset, handling missing values, and splitting it into training and testing sets.

2. **Node Representation**: The `Node` class is used to represent nodes in the decision tree. Each node contains information about the attribute it represents, the attribute value that leads to it, the classification decision at leaf nodes, and child nodes.

3. **Information Gain**: The algorithm selects the best attribute at each node based on information gain. Information gain measures how much the attribute helps in reducing uncertainty about the classification.

4. **Tree Building**: The decision tree is built recursively. The algorithm selects the attribute with the highest information gain, creates a new node for it, and continues building the tree for each branch.

5. **Classification**: Once the tree is built, it is used to classify new examples by traversing the tree from the root to a leaf node.

6. **Testing and Accuracy Calculation**: The dataset is randomly divided into training (80%) and testing (20%) sets. The decision tree classifier is trained on the training data and tested on the testing data. This process is repeated 20 times to calculate the average test accuracy. The mean accuracy and standard deviation of accuracy are reported.

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

