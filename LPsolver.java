import java.util.Scanner;
import java.util.Vector;
import java.io.File;
/*
 * Implement the one phase simplex algorithm assuming all variables are non-negative
 * Each LP problem is given by a text file. The file starts with the objective function followed by the constraints
 */
public class LPsolver{

    
    public static void main(String[] args){
        //first line is the maximize function
        //next lines are the constraints
        //* size of the vector is the number of variables
        
        File inputFile = new File("C:\\onephase feasible input.txt");
        Scanner input;
        try{
            input = new Scanner(inputFile);
        }catch(Exception e){
            System.out.println("File not found");
            return;
        }
        
        String values = input.nextLine();
        System.out.println(values);
        //convert the problem into canonical form
    
        //check if problem can be solved using one-phase simplex method
        //* If all right hand sides of the constraints are positive, invoke simplex Algorithm
        //* Otherwise print "can't be solved in one phase, need Two-phase simplex algorithm" then return
    
        //convert the problem from canonical form to standard form and add slack variables

        //use one-phase simplex method to find the optimal solution
    
        input.close();
    }
}