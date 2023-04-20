#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

/*
 * Implement the one phase simplex algorithm assuming all variables are non-negative
 * Each LP problem is given by a text file. The file starts with the objective function followed by the constraints
 */

int main()
{
    
    bool isOnePhase(vector<vector<double>>);
    vector<vector<double>> rowOperations(vector<vector<double>>);
    //read input file 
    ifstream InputFile("onephase feasible input.txt");
    string input;
    double inputAsDouble;
    const vector <double> vect; ////stays as an empty vector
    vector<vector<double>> matrix; //holds the target equation and the constraints

    if(InputFile.is_open()){
        matrix.push_back(vect);
        ////cout << "Before Input" << endl;
        //add the target equation to the matrix
        getline(InputFile,input);
        ////cout << input << endl;
        //convert the input line into double values for the vector using a stringstream
        stringstream s(input);
        while(s >> inputAsDouble){
            //loop until target equation is in matrix
            matrix[0].push_back(inputAsDouble);
        }
        matrix[0].push_back(0);

        //add the constraints to the matrix

        int constraints = 1;
        double value = 0;
        while(InputFile){
            InputFile >> input;
            if(input == ">="){
                //add the final value to the vector and multiply every value in the vector by -1
                //then update the index
                
    
            }else if(input == "<="){
                //add the final value to the vector, then update the index
                InputFile >> input;
                value = stod(input);
                matrix[constraints].push_back(value);
                constraints++;

            }else{
                //add empty vector to matrix if previous vector is finished
                ////will result in extra vector being added at the end, don't know how to fix that
                ////matrix will be at size one when target equation is added
                if(constraints == matrix.size()){
                    matrix.push_back(vect);
                }
                //convert input to int and add it to the vector
                value = stoi(input);
                matrix[constraints].push_back(value);
            }

            cout << input << endl;
            ////prints out the last value twice, don't know how to fix that, causes the extra vector
        }
        ////Temporary(maybe permanent lol) fix to the last value being added as an extra matrix
        matrix.pop_back(); // gets rid of the extra vector

        //adds slack variables to vectors
        //stores right hand values temporarily
        vector<int> rhv;
        for(int i = 0; i < matrix.size(); i++){
            rhv.push_back(matrix[i][matrix[i].size()-1]);
        }

        //replaces the rhv with the slack variables
        for(int i = 0; i < rhv.size(); i++){
            if(i == 1){
                matrix[i][matrix[i].size()-1] = 1;
            }else{
                matrix[i][matrix[i].size()-1] = 0;
            }
        }
        //adds the rest of the slack variables
        for(int i = 2; i < matrix.size(); i++){
            for(int j = 0; j < matrix.size(); j++){
                if(i == j){
                    matrix[j].push_back(1);
                }else{
                    matrix[j].push_back(0);
                }
            }
        }

        //re-adds the rhv
        for(int i = 0; i < rhv.size(); i++){
            matrix[i].push_back(rhv[i]);
        }

        cout << "\nMatrix:\n";
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size(); j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Done inputing\n";
    } else{
        cout << "File not open\n";
    }


    cout << "After Input is collected" << endl;
    
    
    //check if problem can be solved using one-phase simplex method
    if(!isOnePhase(matrix)){
        cout << "Can't be solved in one phase, need Two-Phase Simplex Algorithm\n";
        return 0;
    }
    
    //* If all right hand sides of the constraints are positive, invoke simplex Algorithm
    vector<vector<int>> optimizedMatrix;
    //optimizedMatrix = rowOperations(matrix);

    cout << "Optimized Matrix: \n";
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    //Output optimal solution
    
    //Output Optimal value
    printf("Optimal value: %d",matrix.at(0).back() - optimizedMatrix.at(0).back());
    InputFile.close();
    return 0;
}

bool isOnePhase(vector<vector<int>> m){
    //return true if all the right hand constraints are positive
    for(int i = 1; i < m.size(); ++i){
        if(m.at(i).back() < 0){
            return false;
        }
    }
    return true;
}


vector<vector<int>> rowOperations(vector<vector<int>> m){
    //returns the optimized

    //check if target equation is nonpositive
    bool nonpos = true;
    for(int i = 0; i < m[0].size(); i++){
        if(m[0][i] > 0){
            nonpos = false;
        }
    }
    //do row operations or return the matrix
    if(nonpos){
        return m;
    }else{
        //find the largest coefficient in the target equation and mark the index
        int largestCoefficient = 0;
        int index = 0; // largest coefficient index
        for(int i = 0; i < m[0].size(); i++){
            if (m[0][i] > largestCoefficient){
                largestCoefficient = m[0][i];
                index = i;
            }
        }
        int constraint = 1;
        //find the bottleneck for the first constraint
        int bottleneck = m[1][m.size()-1]/m[1][index];
        //find the bottleneck for that variable
        for(int i = 2; i < m.size(); i++){
            if(m[i][m.size()-1]/m[i][index] < bottleneck){
                constraint = i;
            }
        }
        //set the target varaible to 1
        for(int i = 0; i < m[index].size(); i++){
            m[i] /= m[index];
        }
    }

    
}