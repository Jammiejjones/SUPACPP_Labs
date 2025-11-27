#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "CustomFunctions.h"



int main(){

//Setting names of the two files we will use
std::string inputfile = "../input2D_float.txt";
std::string inputError = "../error2D_float.txt";


//Asking for input and checking against length of data_input
int user_N;
int lineCount = 0;

//Getting input from terminal for amount of values to calculate
print("How many sets of vectors to output?");
std::cin >> user_N;

//Getting the line counts
lineCount = check_number_lines(inputfile);

//comparing file length vs requested amount of data
if (user_N > lineCount-1){
    print("Asking for more vecotrs than avalible, setting max");
    user_N = lineCount - 1;
}

//setting arrays/matracies/vector(vectors) to use later for data and error
std::vector<std::vector<float>> my_data;
std::vector<std::vector<float>> my_error;

//Getting all data out of the files and into Vector(Vector) matrix's
my_data = get_values_from_datafile(inputfile, user_N);
my_error = get_values_from_datafile(inputError, user_N);

//Printing data using custom Print function
print("Data");
print(my_data);

print("\n");
print("Data errors");
print(my_error);

//running linerar regression and formatting results to a string
std::pair linePair = linearReg(my_data);
std::string linePairStr =  "m: "+ std::to_string(linePair.first) + " c: " + std::to_string(linePair.second);


//Printing, saving Linear Refression and chi square analysis
print("\n");
print("Linear Regression & Chi");
print("m,c,chi");
std::string tempFileName = "output";
saveFuncReturn(tempFileName, linearReg(my_data,my_error));
print(linearReg(my_data,my_error));

//Printing and saving power function for x to the y
print("\n");
print("X to the power Y");
tempFileName = "x to the power y results";
saveFuncReturn(tempFileName, powerABunch(my_data));
print(powerABunch(my_data));

//Printing and saving magnitudes of vectors x,y
print("\n");
print("Magnitude of vector x,y");
tempFileName = "Magnitude of vector x,y";
saveFuncReturn(tempFileName, magnitudeOfVectors(my_data));
print(magnitudeOfVectors(my_data));

//A lil message :)
print("\n");
print("Think this covers the whole assignment, was fun! Thank you!...I skipped the last one because I got busy...sorryyyy!...I got you a dino..");
print("               __\n              / _)      \n     _.----._/ /        \n    /         /         \n __/ (  | (  |          \n/__.-'|_|--|_|          \n");
}