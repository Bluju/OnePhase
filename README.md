# OnePhase
Linear Programming - One Phase Project
Programming assignment for CS 30900

Write a program to implement the one phase simplex algorithm in Java.
(1) Assume all variables have the non-negativity constraints.
(2) Input: each LP problem is given by a text file. The file starts with the objective function, followed by the constraints
(3) Output: The program should print out the initial table and the table after each pivot. If the problem is infeasable or unbounded, the program should print out an appropriate message. 
(4) After reading the input file, the program should do the following:
  a. Convert the problem into canonical form. This includes converting inequalities with ">=" to inequalities with "<=" and adding slack variables.
  b. If all the right hand sides of the constraints from a. are positive, invoke the Simplex Algorithm.
  c. Otherwise print out a message: "Can't be solved in one phase, need Two-Phase Simplex Algorithm", then return.
  
Submit the source code, test input files, test output text file or screen shot. 
