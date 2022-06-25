#ifndef ___PROBLEM_HPP___
#define ___PROBLEM_HPP___
#include "Node.hpp"
#include <vector>

class Problem{
    public:
    // int n = 0; //length and width of n by n array
    int initial_state[3][3];
    int goal_state[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    //Node initial(int s[3][3]);
    // int setWidth(int x){
    //     n = x;
    // }

    void printState(int s[3][3]){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                std::cout << s[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    //operators
    Node move_left(Node curr){
        if (can_left(curr.state)){
            int new_state[3][3]; 
            int temp; 
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++ ){
                    if (curr.state[i][j] == 0){
                        new_state[i][j-1] = 0;
                        new_state[i][j] = curr.state[i][j-1];
                    }
                    else if (new_state[i][j] != 0){
                        new_state[i][j] = curr.state[i][j];
                    }
                }
            }
            Node newNode(new_state);
            newNode.set_gn(curr.g_n);
            newNode.set_hn(curr.h_n);
            //*newNode->parent = *curr;
    

            return newNode;
        }
        return curr; //if it cannot shift to the left, it will return curr

    }

  Node move_right(Node curr){
        if (can_right(curr.state)){
            int new_state[3][3]; 
            int temp; 
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++ ){
                    if (curr.state[i][j] == 0){
                        new_state[i][j+1] = 0;
                        new_state[i][j] = curr.state[i][j+1];
                    }
                    else if (new_state[i][j] != 0){
                        new_state[i][j] = curr.state[i][j];
                    }
                }
            }
            Node newNode(new_state);
            newNode.set_gn(curr.g_n);
            newNode.set_hn(curr.h_n);
            //*newNode->parent = *curr;
    

            return newNode;
        }
        return curr;

    }

    Node move_up(Node curr){
        if (can_up(curr.state)){
            int new_state[3][3]; 
            int temp; 
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++ ){
                    if (curr.state[i][j] == 0){
                        new_state[i-1][j] = 0;
                        new_state[i][j] = curr.state[i-1][j];
                    }
                    else if (new_state[i][j] != 0){
                        new_state[i][j] = curr.state[i][j];
                    }
                }
            }
           Node newNode(new_state);
           newNode.set_gn(curr.g_n);
            newNode.set_hn(curr.h_n);
            //*newNode->parent = *curr;
    

            return newNode;
        }
        return curr;

    }

    Node move_down(Node curr){
        if (can_down(curr.state)){
            int new_state[3][3]; 
            int temp; 
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++ ){
                    if (curr.state[i][j] == 0){
                        new_state[i+1][j] = 0;
                        new_state[i][j] = curr.state[i+1][j];
                    }
                    else if (new_state[i][j] != 0) {
                        new_state[i][j] = curr.state[i][j];
                    }
                }
            }
            Node newNode(new_state);
            newNode.set_gn(curr.g_n);
            newNode.set_hn(curr.h_n);
            //*newNode->parent = *curr;
    

            return newNode;
        }
        return curr;

    }


    private:
    //private helper functions for operators
    bool can_left(int state[3][3]){
        for (int i = 0 ; i < 3; i++ ){
            if (state[i][0] == 0){
                return false;
            }
        }
        return true;
    }
    bool can_right(int state[3][3]){
        for (int i = 0 ; i < 3; i++ ){
            if (state[i][2] == 0){
                return false;
            }
        }
        return true;
    }
    bool can_up(int state[3][3]){
        for (int j = 0; j < 3; j++){
            if (state[0][j] == 0){
                return false;
            }
        }
        return true;
    }
    bool can_down(int state[3][3]){
        for (int j = 0; j < 3; j++){
            if (state[2][j] == 0){
                return false;
            }
        }
        return true;
    }

};
#endif