#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_set>
#include<string>

using namespace std;

//node class
class Node{
    public:
        int** grid;
        int k;
        int moves;
        pair<int, int> zeroPos;
        Node* prevNode;

        Node(int k,int** grid){
            this->k = k;
            this->moves = 0;
            this->prevNode = NULL;

            this->grid = new int*[k];

            for(int i = 0; i < k; i++){
                this->grid[i] = new int[k];
                for(int j = 0; j < k; j++){
                    this->grid[i][j] = grid[i][j];
                    if(grid[i][j] == 0){
                        this->zeroPos = make_pair(i, j);
                    }
                }
            }
        }

        Node(int** grid, int k, int moves, pair<int, int> zeroPos, Node &prevNode){
            this->grid = grid;
            this->k = k;
            this->moves = moves;
            this->zeroPos = zeroPos;
            this->prevNode = &prevNode;
        }

        //assigns the grid of the current node to the grid of the node passed as parameter
        void assignGrid(Node* node){

            this->k = node->k;
            this->moves = node->moves;
            this->zeroPos = node->zeroPos;
            this->prevNode = node->prevNode;

            this->grid = new int*[k];

            for(int i = 0; i < k; i++){
                this->grid[i] = new int[k];
                for(int j = 0; j < k; j++){
                    this->grid[i][j] = node->grid[i][j];
                }
            }
        }

        //checks if the current node is equal to the node passed as parameter
        bool isEqual(Node* node){
            for(int i = 0; i < k; i++){

                for(int j = 0; j < k; j++){
                    if(this->grid[i][j] != node->grid[i][j]){
                        return false;
                    }
                }
            }
            return true;
        }

        //checks if the current node is equal to the goal node
        bool isGoal(){
            int value = 1;

            for(int i = 0; i < k; i++){
                for(int j = 0; j < k; j++){
                    if(this->grid[i][j] != value){
                        return false;
                    }
                    value++;
                    if(value == k*k)
                        break;
                }
            }

            return true;
        }

        //prints the grid of the current node
        void print_grid(){
            for(int i = 0; i < k; i++){
                for(int j = 0; j < k; j++){

                    cout << this->grid[i][j] << " ";
                }
                cout << endl;
            }
            cout<<endl;
        }

        //returns the grid of the current node
        int** getGrid(){
            return this->grid;
        }

        //returns the number of moves of the current node
        int getMoves(){
            return this->moves;
        }

        //returns the position of the zero in the current node
        pair<int, int> getZeroPos(){
            return this->zeroPos;
        }

        //returns the previous node of the current node
        Node* getPrevNode(){
            return this->prevNode;
        }

        Node* getCurNode(){
            return this;
        }

        //returns the k value of the current node
        int getK(){
            return this->k;
        }

        //calculates the hamming distance of the current node
        int hammingDistance(){
            int distance = 0;
            int value = 1;

            for(int i = 0; i < k; i++){
                for(int j = 0; j < k; j++){
                    if(this->grid[i][j] != value){
                        distance++;
                    }
                    value++;
                }
            }
            return distance;
        }


        //calculates the manhattan distance of the current node
        int manhattanDistance(){
            int distance = 0;
            int value = 1;

            for(int i = 0; i < k; i++){
                for(int j = 0; j < k; j++){
                    if(this->grid[i][j] != value){
                        distance += abs(i - ((this->grid[i][j] - 1) / k)) + abs(j - ((this->grid[i][j] - 1) % k)); // (i-((this->grid[i][j]-1)/k)) is the row of the value in the goal state and (j-((this->grid[i][j]-1)%k)) is the column of the value in the goal state
                    }
                    value++;
                }
            }

            return distance;
        }

        //calculate the hamming distance of the current node and adds it to the number of moves of the current node
        int hammingDistanceWithMoves(){
            return this->hammingDistance() + this->moves;
        }

        //calculate the manhattan distance of the current node and adds it to the number of moves of the current node
        int manhattanDistanceWithMoves(){
            return this->manhattanDistance() + this->moves;
        }

        //return all children of the current node in an array

        vector<Node*> getChildren(){
            vector<Node*> children;
            int i = this->zeroPos.first;
            int j = this->zeroPos.second;

            //move up
            if(i > 0){
                int** grid = new int*[k];
                for(int i = 0; i < k; i++){
                    grid[i] = new int[k];
                    for(int j = 0; j < k; j++){
                        grid[i][j] = this->grid[i][j];
                    }
                }
                grid[i][j] = grid[i-1][j];
                grid[i-1][j] = 0;
                Node* node = new Node(grid, k, this->moves + 1, make_pair(i-1, j), *this);
                children.push_back(node);
                //node->print_grid();
            }

            //move down
            if(i < k-1){
                int** grid = new int*[k];
                for(int i = 0; i < k; i++){
                    grid[i] = new int[k];
                    for(int j = 0; j < k; j++){
                        grid[i][j] = this->grid[i][j];
                    }
                }
                grid[i][j] = grid[i+1][j];
                grid[i+1][j] = 0;
                Node* node = new Node(grid, k, this->moves + 1, make_pair(i+1, j), *this);
                children.push_back(node);
                //node->print_grid();
            }

            //move left
            if(j > 0){
                int** grid = new int*[k];
                for(int i = 0; i < k; i++){
                    grid[i] = new int[k];
                    for(int j = 0; j < k; j++){
                        grid[i][j] = this->grid[i][j];
                    }
                }
                grid[i][j] = grid[i][j-1];
                grid[i][j-1] = 0;
                Node* node = new Node(grid, k, this->moves + 1, make_pair(i, j-1), *this);
                children.push_back(node);
                //node->print_grid();
            }

            //move right
            if(j < k-1){
                int** grid = new int*[k];
                for(int i = 0; i < k; i++){
                    grid[i] = new int[k];
                    for(int j = 0; j < k; j++){
                        grid[i][j] = this->grid[i][j];
                    }
                }
                grid[i][j] = grid[i][j+1];
                grid[i][j+1] = 0;
                Node* node = new Node(grid, k, this->moves + 1, make_pair(i, j+1), *this);
                children.push_back(node);
                //node->print_grid();
            }
            return children;
        }

        //destructor
        ~Node(){
            for(int i = 0; i < k; i++){
                delete[] grid[i];
            }
            delete[] grid;
        }
};


//class for solving the n-puzzle problem

class NPuzzle{
    private:
        int k;

    //hamming node comparator
    struct hammingNodeComparator{
        bool operator()(Node* node1, Node* node2){
            return node1->hammingDistanceWithMoves() > node2->hammingDistanceWithMoves();
        }
    };

    //manhattan node comparator
    struct manhattanNodeComparator{
        bool operator()(Node* node1, Node* node2){
            return node1->manhattanDistanceWithMoves() > node2->manhattanDistanceWithMoves();
        }
    };

    struct nodeComparator{
        bool operator()(Node* node1, Node* node2) const{
            //if all elements of the grid of node1 are equal to the elements of the grid of node2
            if(node1->isEqual(node2)){
                return true;
            }
            else{
                return false;
            }
        }
    };

    //struct for node hash
    struct nodeHash{
        size_t operator()(Node* node) const{
            int32_t hash = 0;
            string str = "";

            for(int i = 0; i < node->getK(); i++){
                for(int j = 0; j < node->getK(); j++){
                    str += to_string(node->getGrid()[i][j]);
                }
            }

            for(int i = 0; i < str.length(); i++){
                hash = hash * 31 + str[i];
            }

            return hash;
        }
    };

    //count the number of inversions in the grid
    int countInversions(Node* node){
        int inversions = 0;
        int* arr = new int[k*k];
        int index = 0;

        for(int i = 0; i < k; i++){
            for(int j = 0; j < k; j++){
                arr[index] = node->getGrid()[i][j];
                index++;
            }
        }

        for(int i = 0; i < k*k; i++){
            for(int j = i+1; j < k*k; j++){
                if(arr[i] != 0 && arr[j] != 0 && arr[i] > arr[j]){
                    inversions++;
                }
            }
        }

        return inversions;
    }

    //check if the grid is solvable
    bool isSolvable(Node* node){
        int inversions = countInversions(node);
        int i = node->getZeroPos().first;
        int j = node->getZeroPos().second;

        if(k % 2 == 1){
            if(inversions % 2 == 0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if((inversions + i) % 2 == 1){
                return true;
            }
            else{
                return false;
            }
        }
    }

    //print the path from the initial node to the goal node
    void printPath(Node* node){
        if(node == NULL){
            return;
        }
        printPath(node->getPrevNode());
        node->print_grid();
        cout << endl;
    }


    public:

       NPuzzle(int k){
           this->k = k;
           //cout<<k;
       }

     //solve the n-puzzle problem using A* algorithm with hamming distance heuristic

         void solveWithHamming(int** grid){

              cout<<"Solving with Hamming Distance Heuristic"<<endl;
                cout<<endl;
              Node* initialNode = new Node(k, grid);

              //first check if the grid is solvable
                if(!isSolvable(initialNode)){
                    cout<<endl;
                     cout << "This puzzle is not solvable" << endl;
                        cout<<endl;
                     return;
                }
                else{
                        cout<<endl;
                     cout << "This puzzle is solvable" << endl;
                        cout<<endl;
                }

              int explored_nodes = 0; //number of nodes entered into the closed list
              int expanded_nodes = 0; //number of nodes entered into the open list

              priority_queue<Node*, vector<Node*>, hammingNodeComparator> open_list;

              //use hash table to create closed list to reduce time complexity
            
             unordered_set<Node*, nodeHash, nodeComparator> closed_list;

              open_list.push(initialNode);
              expanded_nodes++;

              while(!open_list.empty()){
                Node* node = open_list.top();
                open_list.pop();
                explored_nodes++;

                if(node->isGoal()){
                    cout << "Minimum number of moves: " << node->getMoves() << endl;
                    cout << "Number of nodes expanded: " << expanded_nodes << endl;
                    cout << "Number of nodes explored: " << explored_nodes << endl;
                    cout<<endl;

                    cout << "Steps: " << endl;
                    cout<<endl;
                    printPath(node);
                    return;
                }

                vector<Node*> children = node->getChildren();
                for(int i = 0; i < children.size(); i++){

                        if(closed_list.find(children[i]) == closed_list.end()){
                            open_list.push(children[i]);
                            expanded_nodes++;
                        }
                   
                }
                closed_list.insert(node);
                //node->print_grid();
              }
         }


         //solve the n-puzzle problem using A* algorithm with manhattan distance heuristic

         void solveWithManhattan(int** grid){

                cout<<"Solving with Manhattan Distance Heuristic"<<endl;
                cout<<endl;
                Node* initialNode = new Node(k, grid);

                //first check if the grid is solvable
                if(!isSolvable(initialNode)){
                    cout<<endl;
                     cout << "This puzzle is not solvable" << endl;
                     cout<<endl;
                     return;
                }
                else{
                        cout<<endl;
                     cout << "This puzzle is solvable" << endl;
                     cout<<endl;
                }

                priority_queue<Node*, vector<Node*>, manhattanNodeComparator> open_list;
                
                //use hash table to create closed list to reduce time complexity
                unordered_set<Node*, nodeHash, nodeComparator> closed_list;

                int explored_nodes = 0; //number of nodes entered into the closed list
                int expanded_nodes = 0; //number of nodes entered into the open list

                open_list.push(initialNode);
                expanded_nodes++;


              while(!open_list.empty()){
                Node* node = open_list.top();
                open_list.pop();
                explored_nodes++;

                if(node->isGoal()){
                    cout << "Minimum number of moves: " << node->getMoves() << endl;
                    cout << "Number of nodes expanded: " << expanded_nodes << endl;
                    cout << "Number of nodes explored: " << explored_nodes << endl;
                    cout<<endl;

                    cout << "Steps: " << endl;
                    cout<<endl;
                    printPath(node);
                    return;
                }

                vector<Node*> children = node->getChildren();
                for(int i = 0; i < children.size(); i++){
                            
                            if(closed_list.find(children[i]) == closed_list.end()){
                                open_list.push(children[i]);
                                expanded_nodes++;
                            }
                }
                closed_list.insert(node);
              }
         }

};



int main(){

    int k;
    cin >> k;

    int** nPuzzle_grid;
    nPuzzle_grid = new int*[k];

    for(int i = 0; i < k; i++){
        nPuzzle_grid[i] = new int[k];
        for(int j = 0; j < k; j++){
            cin >> nPuzzle_grid[i][j];
        }

    }

    NPuzzle npzl(k);
    //Node node(k,nPuzzle_grid);

    //node.print_grid();
    npzl.solveWithHamming(nPuzzle_grid);
    npzl.solveWithManhattan(nPuzzle_grid);
}
