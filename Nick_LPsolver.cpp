#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

/*
 * Implement the one phase simplex algorithm assuming all variables are non-negative
 * Each LP problem is given by a text file. The file starts with the objective function followed by the constraints
 */

int main()
{
    int numberOfConstraints{0};
    //read input file 
    ifstream InputFile("onephase feasable input.txt");
    string input;
    const vector <int> vect; ////stays as an empty vector
    vector<vector <int>> matrix;

    if (InputFile.is_open()){
        cout << "Before Input" << endl;
        //add the target equation to the matrix
        getline(InputFile, input);
        cout << input << endl;
        ////don't know how to transfer from line to vector
        ////adding an empty matrix so code works
        matrix.push_back(vect);
        

        //add the constraints to the matrix
        int constraints = 1;
        int value = 0;
        while(InputFile){
            InputFile >> input;
            if(input == ">="){
                //add the final value to the vector and multiply every value in the vector by -1
                //then update the index

            }else if(input == "<="){
                //add the final value to the vector, then update the index
                InputFile >> input;
                value = stoi(input);
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
        cout << "\nMatrix:\n";
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size(); j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Done inputing\n";
    }else{
        cout << "File not open\n";
    }
    
    
    //create a vector to hold the values
    //* size of the vector is the number of variables
    //put vector into array that holds all constraints
    
    cout << "After Input is collected" << endl;
    //convert the problem into canonical form
    
    //check if problem can be solved using one-phase simplex method
    //* If all right hand sides of the constraints are positive, invoke simplex Algorithm
    //* Otherwise print "can't be solved in one phase, need Two-phase simplex algorithm" then return
    
    //convert the problem from canonical form to standard form and add slack variables
    
    InputFile.close();
    return 0;
}