#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iterator>
#include <float.h>

using namespace std;

/*
 * Implement the one phase simplex algorithm assuming all variables are non-negative
 * Each LP problem is given by a text file. The file starts with the objective function followed by the constraints
 */
void basicFeasibleSolution(vector<vector<double>>);
int main()
{
    //declare functions
    bool isOnePhase(vector<vector<double>>);
    vector<vector<double>> rowOperations(vector<vector<double>>);
    
    //read input file 
    ifstream InputFile("onephase feasible input.txt");
    string input;
    double inputAsDouble;
    const vector <double> vect; //Empty vector used to add a new row to the matrix
    vector<vector<double>> matrix; //holds the target equation and the constraints

    if(InputFile.is_open()){
        matrix.push_back(vect);
        //add the target equation to the matrix
        getline(InputFile,input);
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
                InputFile >> input;
                value = stod(input);
                matrix[constraints].push_back(value);
                for(int i = 0; i < matrix[constraints].size(); i++){
                    matrix[constraints][i] *= -1;
                }
                constraints++;
                
            }else if(input == "<="){
                //add the final value to the vector, then update the index
                InputFile >> input;
                value = stod(input);
                matrix[constraints].push_back(value);
                constraints++;

            }else{
                //add empty vector to matrix if previous vector is finished
                if(constraints == matrix.size()){
                    matrix.push_back(vect);
                }
                //convert input to int and add it to the vector
                value = stod(input);
                matrix[constraints].push_back(value);
            } 
        }
        matrix.pop_back(); // gets rid of the extra vector generated at the end of input process

        //adds slack variables to vectors
        //stores right hand values temporarily
        vector<double> rightHandValues; 
        for(int i = 0; i < matrix.size(); i++){
            rightHandValues.push_back(matrix[i][matrix[i].size()-1]);
        }

        //replaces the right hand value with the slack variables
        for(int i = 0; i < rightHandValues.size(); i++){
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

        //re-adds the right hand values
        for(int i = 0; i < rightHandValues.size(); i++){
            matrix[i].push_back(rightHandValues[i]);
        }

        cout << "\nInitial Table:\n";
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size(); j++){
                cout << matrix[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
        
    } else{
        cout << "File not open\n";
    }
    
    //check if problem can be solved using one-phase simplex method
    if(!isOnePhase(matrix)){
        cout << "Can't be solved in one phase, need Two-Phase Simplex Algorithm\n";
        return 0;
    }
    
    //* If all right hand sides of the constraints are positive, invoke simplex Algorithm
    vector<vector<double>> optimizedMatrix;
    

    cout << "One Phase Simplex Algorithm: \n";
    optimizedMatrix = rowOperations(matrix);
    
    for(int i = 0; i < optimizedMatrix.size(); i++){
        for(int j = 0; j < optimizedMatrix[i].size(); j++){
            cout << optimizedMatrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    //Output optimal solution
    printf("\nOptimal solution: \n");
    basicFeasibleSolution(optimizedMatrix);
    //Output Optimal value
    printf("Optimal value: %0.2f\n",matrix[0][matrix[0].size()-1] - optimizedMatrix[0][optimizedMatrix[0].size()-1]);
    InputFile.close();
    return 0;
}

bool isOnePhase(vector<vector<double>> m){
    //return true if all the right hand constraints are positive
    for(int i = 1; i < m.size(); ++i){
        if(m.at(i).back() < 0){
            return false;
        }
    }
    return true;
}

void basicFeasibleSolution(vector<vector<double>> m){
    //given a matrix, find and return the basic feasable solution
    vector<double> bfs;
    int indexOf1 = -1; //-1 indicates that a 1 has not been found
    ////cout << "m.size() = " << m.size() << "\tm[0].size() = " << m[0].size() << endl;
    //check each column to find all 0's and a single 1, make note of where the 1 was located
    for(int i = 0; i < m[0].size()-1;i++){
      for(int j = 0; j < m.size();j++){
        ////cout << "Now checking m[j][i] = " << m[j][i] << "\t";
        if(m[j][i] == 1 && indexOf1 == -1){
          indexOf1 = j;
        }
        else if(m[j][i] != 0){
          bfs.push_back(0);
          break; 
        }
        else if(m[j][i] == 1 && indexOf1 != -1){
          bfs.push_back(0);
          indexOf1 = -1;
          break;
        }
        
      }
      if(indexOf1 != -1){
        //A single 1 was found in a column
        bfs.push_back(m[indexOf1][m[0].size()-1]); ////m[row][column]
      }
      
      indexOf1 = -1;
    }
    cout << "BFS: (";
    for(int i = 0; i < bfs.size();i++){
        cout << bfs[i];
        if(i != bfs.size()-1){
            cout << ", ";
        }
    }
    cout << ")\n";
    
}


vector<vector<double>> rowOperations(vector<vector<double>> m){
    //returns the optimized matrix
    vector<double> bfs;
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
        double largestCoefficient = 0;
        int index = 0; // largest coefficient index
        for(int i = 0; i < m[0].size(); i++){
            if (m[0][i] > largestCoefficient){
                largestCoefficient = m[0][i];
                index = i;
            }
        }
        int constraint = 1;
        //find the bottleneck for the first constraint
        
        int count = 1;
        double bottleneck = DBL_MAX;
        
        //find the bottleneck for that variable
        for(int i = 1; i < m.size(); i++){
            
            if((m[i][m[1].size()-1]/m[i][index]) >=0 && m[i][m[1].size()-1]/m[i][index] < bottleneck){
            
                constraint = i;
                bottleneck = m[i][m[1].size()-1]/m[i][index];
            }
        }
        
        //assign the row operation value,
        //need to assign this because it will get updated in the matrix, but we need the nonupdated value

        //divide the target row by the target variabel, setting the target varaible to 1
        double targetValue = m[constraint][index];
        for(int i = 0; i < m[index].size(); i++){
            m[constraint][i] = m[constraint][i] / targetValue;
        }
        
        //set the other coefficents in row index to 0, and update the row
        for(int i = 0; i < m.size(); i++){
            if(i != constraint){
            //assign the row operation value,
            //also gets updated during the operations
            double rowValue = m[i][index];
            
                for(int j = 0; j < m[i].size(); j++){
                    //cout << m[i][j] << " - " << m[constraint][j] << " * " << rowValue << " / " << m[constraint][index] << endl;
                    if(m[constraint][index] != 0){
                    m[i][j] = m[i][j] - m[constraint][j] * rowValue / m[constraint][index];
                    }
                }
            }
        }
        //m = rowOperations(m);
        
        
        return m;
        
        
    }
    

    
}
