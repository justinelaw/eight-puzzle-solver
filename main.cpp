#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include "Problem.hpp"
#include "Node.hpp"
using namespace std;


double MisplacedHeuristic(Problem p, Node n){

    double heuristic = 0; 

    for (int i = 0; i < 3; i++ ){
        for (int j = 0; j < 3; j++){
            if (n.state[i][j] != p.goal_state[i][j]){
                if (n.state[i][j] != 0 ){
                     ++heuristic;
                }
               
            }
        }
    }

    return heuristic;


}

pair<int, int> findPositionInGoal(Problem p, int position){

    pair<int,int> goalPair;
    goalPair.first = 0;
    goalPair.second = 0; 

    for (int i = 0; i < 3; i++ ){
        for (int j = 0; j < 3; j++){
            if (p.goal_state[i][j] == position){
                goalPair.first = i;
                goalPair.second = i;
            }
        }
    }
    return goalPair;
}

double EuclideanDistance(Problem p, Node n){
    double heuristic = 0; 

    pair<int, int> nPair;
    pair<int, int> goalPair;

    double x, y;
    double euclidean;


    for (int i = 0; i < 3; i++ ){
        for (int j = 0; j < 3; j++){
            if (n.state[i][j] != p.goal_state[i][j]){
                if(n.state[i][j] != 0){
                    goalPair = findPositionInGoal(p, n.state[i][j]);
                    nPair.first = i;
                    nPair.second = j;

                    x = pow((goalPair.first) - (nPair.first),2);
                    y = pow((goalPair.second) - (nPair.second),2);

                    euclidean = sqrt(x + y);
                    heuristic = heuristic + euclidean;
                }
                
            }
        }
    }

    return heuristic;
}

class Compare
{
public:
    bool operator() (const Node& lhs, const Node& rhs){
        return lhs.g_n + lhs.h_n  >= rhs.g_n + rhs.h_n;
    }
};


void search(Problem p, int input){ //uniform-cost search taking in problem p
    Node initial(p.initial_state);
    Node goal(p.goal_state);
    if (input == 2){
            //misplaced tile heuristic
            double h = MisplacedHeuristic(p, initial);
            initial.set_hn(h);
         }

    else if (input == 3){
        //euclidean
        double h = EuclideanDistance(p, initial);
        initial.set_hn(h);
    }


    priority_queue<Node, vector<Node>, Compare> frontier;
    frontier.push(initial);
    vector<Node> explored;
    

    //int g = 0;


    Node curr = frontier.top();
    int nodesExpanded = 0; 
    while (!frontier.empty()){ //or other condition?)
        //cout << "frontier size: " << frontier.size() << endl;
        //cout << frontier.top() << endl;
        curr = frontier.top(); 
        frontier.pop();
        explored.push_back(curr);

        p.printState(curr.state);


        if (curr == goal){
            cout << endl;
            ++nodesExpanded;
            //cout << endl;
            p.printState(curr.state);
            cout << "Goal!" << endl;
             cout << "Nodes expanded: " << nodesExpanded << endl;
             cout << "The depth of the goal node is: " << curr.g_n << endl;
            return;
        }

        //explored.push_back(curr);

        //expand curr 

        cout << "Expanding state... " << endl;

        vector<Node> currChildren;

        Node c1 = p.move_left(curr);
        Node c2 = p.move_right(curr);
        Node c3 = p.move_up(curr);
        Node c4 = p.move_down(curr);

        currChildren.push_back(c1);
        currChildren.push_back(c2);
        currChildren.push_back(c3);
        currChildren.push_back(c4);

       //cout << "curr g_n :" << curr.g_n << endl;
       double g;

    
        for (int i = 0; i < 4 ; i++){
            //if (currChildren.at(i).state != curr.state){
                if (std::find(explored.begin(), explored.end(), currChildren.at(i)) == explored.end()){
                    curr.children.push_back(&currChildren.at(i));
                    //cout << "curr: " << curr << endl;
                    g = curr.g_n;
                    currChildren.at(i).set_gn(++g);

                    //heuristics, skip input 1, hardcoded h(n) = 0
                    if (input == 2){
                        //misplaced tile heuristic
                        double h = MisplacedHeuristic(p, currChildren.at(i));
                        currChildren.at(i).set_hn(h);
                        
                    }
                    else if (input == 3){
                        //euclidean distance heuristic
                        double h = EuclideanDistance(p, currChildren.at(i));
                        currChildren.at(i).set_hn(h);
                    }


                    frontier.push(currChildren.at(i));
                    //cout << "frontier size: " << frontier.size() << endl;
                }

        }

        // for (int i = 0; i < explored.size(); i++){
        //     cout << "Explored states: " << endl << explored.at(i) << endl;
        // }

    //    '' while(!frontier.empty()){
    //         //cout << frontier.pop() << endl;
    //         //frontier.pop();
    //         cout << "frontier size: " << frontier.size() << endl;
    //     }


        currChildren.resize(0);

        //explored.push_back(curr);
        ++nodesExpanded;
        
        cout << "The best state to expand with g(n) = " << frontier.top().g_n << " and h(n) = " << frontier.top().h_n << " is " << endl;  
       
    }


    cout << "Search failed" << endl;
}


int main(){
    int input; 
    cout << "Welcome to 8 puzzle solver" << endl;
    cout << "Type \"1\" to use a default puzzle or \"2\" to enter your own puzzle." << endl; 

    cin >> input; 
    while ((input != 1) && (input != 2)){
        cout << "Type \"1\" to use a default puzzle or \"2\" to enter your own puzzle." << endl; \
        cin >> input; 
    }

    Problem myPuzzle; 

    if(input == 1){
        int arr[3][3] = {{1, 2, 3}, {4, 8, 0}, {7, 6, 5}}; //hardcoded default puzzle
        cout << "Initial State: " << endl;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                myPuzzle.initial_state[i][j] = arr[i][j];
                cout << myPuzzle.initial_state[i][j] << " ";
            }
            cout << endl;
        }
        //myPuzzle.initial(arr);
    }
    else{
        int arr[3][3];
        cout << "Enter your puzzle, use a zero to represent a puzzle" << endl;
        cout << "Enter the first row, use space or tabs between numbers" << endl;
        int a; //user input
        for (int j = 0; j < 3; j++){ //for a 3x3 matrix/grid A_ij, we get inputs for A_1j for 1 <= j <= 3
            cin >> a;
            arr[0][j] = a;
        }

        cout << "Enter the second row, use space or tabs between numbers" << endl;
        for (int j = 0; j < 3; j++){ //for a 3x3 matrix/grid A_ij, we get inputs for A_2j for 1 <= j <= 3
            cin >> a;
            arr[1][j] = a;
        }

        cout << "Enter the third row, use space or tabs between numbers" << endl;
        for (int j = 0; j < 3; j++){ //for a 3x3 matrix/grid A_ij, we get inputs for A_3j for 1 <= j <= 3
            cin >> a;
            arr[2][j] = a;
        }

        cout << "Initial State: " << endl;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                myPuzzle.initial_state[i][j] = arr[i][j];
                cout << myPuzzle.initial_state[i][j] << " ";
            }
            cout << endl;
        }
        //myPuzzle.initial(arr);
    }

     

    

    cout << "Enter your choice of algorithm: " << endl;
    cout << "1 - Uniform Cost Search" << endl;
    cout << "2 - A* with the Misplaced Tile heuristic" << endl;
    cout << "3 - A* with the Euclidean Distance heuristic" << endl;

    cin >> input;

    search(myPuzzle, input);





    return 0;
}