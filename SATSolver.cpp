#include <iostream>
#include<vector>
#include <unordered_map>
using namespace std;

// variables:
//      variables in the SAT solver are defined using a vector 
//      each index represents a variable
//          - they are all initialized to 0 for false
//          - setting them to 1 means setting the variable at index i to true

// clauses: 
//      clauses are stored as a map of indices that locate each variable within the clause 
//      if the value at the index is true (1), the variable is taken as is 
//      if the value at the index if false (0), the variable is negated 


class SATInstance{
public:
    vector<int> variables;
    vector<unordered_map<int, int>> clauses;
    int numVars = 0;


    SATInstance(){
        // blank
    }

    void setupInstance(int numVars_) {
        numVars = numVars_;
        variables = vector<int>(numVars, 0);
    }

    void addClause(unordered_map<int, int> clause) {
        clauses.push_back(clause);
    }

    void setVariableTrue(int index) {
        variables[index] = 1;
    }

    void setVariableFalse(int index) {
        variables[index] = 0;

    }

    int clauseSatisfied(unordered_map<int, int> clause){
        for(auto pairs : clause){
            int variable = pairs.first;
            int requiredState = pairs.second;
            int truthValue = variables[variable];
            if(truthValue == requiredState) {
                return 1;
            }
        }
        return 0;
    }

    int solved(){
        for(auto clause: clauses){
            if(!clauseSatisfied(clause)){
                return false;
            }
        }
        return true;
    }

    void printResults(){
        if (solved()){
            for (int i = 0; i<variables.size(); i++){
                cout << "variable " << i << " has value: " << variables[i] << endl;
            }
        } else {
            cout << "no solution found!";
        }
    }



};

class SATSolver{

public:

    SATSolver(){
        //blank
    }

    int bruteForceDFS(SATInstance& instance, int variable){
        if(instance.solved()){
            return 1;
        }
        if(variable == instance.variables.size()){
            return 0;
        }
        instance.setVariableTrue(variable);
        int solvedWhenTrue = bruteForceDFS(instance, variable + 1);
        if(solvedWhenTrue){
            return 1;
        }
        instance.setVariableFalse(variable);
        int solvedWhenFalse = bruteForceDFS(instance, variable + 1);
        return solvedWhenFalse;

        


    }


    int solve(SATInstance& instance){
        // we will try to implement recursive dfs approach (BF)
        int solved = bruteForceDFS(instance, 0);

        return solved;
    }
    
};


int main(){
    SATSolver solver;
    SATInstance instance;
    instance.setupInstance(8);
        // Clause 1: ~x0 ∨ ~x1 ∨ ~x2
    unordered_map<int, int> clause1 = {{0, 0}, {1, 0}, {2, 0}};

    // Clause 2: ¬x0 ∨ ~x3
    unordered_map<int, int> clause2 = {{0, 0}, {3, 0}};

    // Clause 3: x1 ∨ ¬x3 ∨ x4
    unordered_map<int, int> clause3 = {{1, 1}, {3, 0}, {4, 1}};

    // Clause 4: ¬x1 ∨ x5
    unordered_map<int, int> clause4 = {{1, 0}, {5, 1}};

    // Clause 5: x2 ∨ ~x5 ∨ x6
    unordered_map<int, int> clause5 = {{2, 1}, {5, 0}, {6, 1}};

    // Clause 6: ¬x4 ∨ ¬x5 ∨ x7
    unordered_map<int, int> clause6 = {{4, 0}, {5, 0}, {7, 1}};

    // Clause 7: x6 ∨ x7
    unordered_map<int, int> clause7 = {{6, 1}, {7, 1}};

    // Clause 8: x0 ∨ x2 ∨ x4 ∨ x6
    unordered_map<int, int> clause8 = {{0, 1}, {2, 1}, {4, 1}, {6, 1}};

    // Add the clauses to the instance
    instance.addClause(clause1);
    instance.addClause(clause2);
    instance.addClause(clause3);
    instance.addClause(clause4);
    instance.addClause(clause5);
    instance.addClause(clause6);
    instance.addClause(clause7);
    instance.addClause(clause8);
    cout << solver.solve(instance) << endl;
    instance.printResults();

}