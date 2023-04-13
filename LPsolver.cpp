#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*
 * Implement the one phase simplex algorithm assuming all variables are non-negative
 * Each LP problem is given by a text file. The file starts with the objective function followed by the constraints
 */

int main()
{
    int numberOfConstraints{0};
    //read input file using input redirection for ease of testing
    string input;
    stringstream s(input);
    while(cin.good())
    {
        getline(cin,input);
        s << input;
        s >> value;
        cout << value << endl;
        //create a vector to hold the values
        //* size of the vector is the number of variables
        //put vector into array that holds all constraints
    }
    //convert the problem into canonical form
    
    //check if problem can be solved using one-phase simplex method
    //* If all right hand sides of the constraints are positive, invoke simplex Algorithm
    //* Otherwise print "can't be solved in one phase, need Two-phase simplex algorithm" then return
    
    //convert the problem from canonical form to standard form and add slack variables
    
    
    return 0;
}
