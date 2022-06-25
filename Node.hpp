#ifndef ___NODE_HPP___
#define ___NODE_HPP___

#include <vector>
#include <iostream>

class Node{
    public:
    int state[3][3];
    Node() {}; //default constructor
    Node(int s[3][3]){
        for (int i = 0; i < 3; i ++){
            for (int j = 0; j < 3; j++){
                state[i][j] = s[i][j];
            }
        }
    }

    //Node* parent;
    std::vector<Node*> children; 

    double g_n = 0; //path cost from initial to node n 
    double h_n = 0;

    void set_gn (int newGn){
        this->g_n = newGn;
    }

    void set_hn (int newHn){
        this->h_n = newHn;
    }

    bool operator== (const Node& rhs) const{
        for (int i = 0; i < 3; i ++){
            for (int j = 0; j < 3; j++){
                if (state[i][j] != rhs.state[i][j]){
                    return false;
                }
            }
        }
        return true; 
    }

    Node& operator= (const Node& rhs) {
        if (*this == rhs){
            return *this;
        }

       for (int i = 0; i < 3; i ++){
            for (int j = 0; j < 3; j++){
                state[i][j] = rhs.state[i][j];
            }
        }

        this->g_n = rhs.g_n;
        this->h_n = rhs.h_n;

        // for(int i = 0; i < this->children.size(); i++){
        //     children.at(i) = rhs.children.at(i);
        // }

        return *this;
    }

    friend std::ostream& operator<< (std::ostream& out, const Node& n){
        for (int i = 0; i < 3; i ++){
            for (int j = 0; j < 3; j++){
                out << n.state[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }


};

#endif
