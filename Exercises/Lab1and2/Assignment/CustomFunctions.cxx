#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

//Function to check if file is open or closed
bool isFileOpen(const std::ifstream &file) {
    if (file.is_open()){
        std::cout << "File is open!: " << std::endl;
        return -1;
    }
    else{
        std::cout << "File is closed!: " << std::endl;       }
    return file.is_open();
}

//function to take in matrix and output vector. calculates magnitude of x y vector
std::vector<float> magnitudeOfVectors(const std::vector<std::vector<float>> & matrixOfVectors){
    
    std::vector<float> magnitudes;
    
    //Loop
    for (auto& row : matrixOfVectors){
        float x = row[0];
        float y = row[1];
        float mag = std::sqrt(x*x + y*y);

        magnitudes.push_back(mag);
    }

    
    
    return magnitudes;


}

//function to get values from the data sets as matrix
std::vector<std::vector<float>> get_values_from_datafile(std::string file_name, int fun_user_N) {
    
    std::ifstream file;
    file.open(file_name);

    //Declaring varibles to be used, and resetting 
    int i = 0; //for looping
    file.clear();
    file.seekg(0, std::ios::beg);

    //make matrix to store x,y values
    std::vector<std::vector<float>> matrix;

    //Start of loop to go through each line of data file and get x,y
        while (file) {
            //Skipping the first line, as it it 'x,y'
            if (i == 0){
                std::string str1, str2;
                getline(file, str1, ',') && getline(file, str2);

            }
            //doing this while loop intager is under the requested amount
            if(i < fun_user_N){

                std::string str_num1, str_num2;
                getline(file, str_num1, ',') && getline(file, str_num2);

                float num1 = stof(str_num1);
                float num2 = stof(str_num2);

                matrix.push_back({num1,num2});
                

            }
            //Catch to end the loop when asked amount of values has been retrieved
            if(i==fun_user_N){
                
                file.close();
                return matrix;
            }
            i++;
            
    }
    
}

//function to check the number of lines in the data/error files
int check_number_lines(std::string &file_name){
    //declaring and opening file
    std::ifstream file;
    file.open(file_name);

    //declaring placeholder
    std::string line;
    int lineCount;

    //loop to incriment ove the length of the data file
    while(getline(file, line))
    {
        lineCount++;
    }  

    //close file
    file.close();
    return lineCount ;
}



//Just Linear regression

std::pair<float,float> linearReg(std::vector<std::vector<float>> & dataPoints){
    
    // getting N
    int N = dataPoints.size();
    
    // Setting all sums to 0
    float sumX = 0;
    float sumY = 0;
    float sumXY = 0; 
    float sumXX = 0;

    //looping over values of x,y. Doing all the sums at once
    for (auto& row : dataPoints){
        float x = row[0];
        float y = row[1];
        
        sumX += x;
        sumY += y;
        sumXY += y*x;
        sumXX += x*x;

    }

    //calculating m and c (p and q)
    float p = (N * sumXY - sumX*sumY)/(N*sumXX - sumX*sumX);//gradieent
    float q = (sumXX*sumY - sumXY*sumX)/(N*sumXX - sumX*sumX);//offset



    //return as pair
    return {p,q};
}
  
//CHi function. points, errors, and line equations. Assuming chi^2 will be chi of x + chi of y
float chiSquareMePlz(std::vector<std::vector<float>> & dataPoints,std::vector<std::vector<float>> & errorPoints,std::pair<float, float>& lineConsts){
    
    //getting size of datafile
    int N = dataPoints.size();

    //setting placeholders
    int i = 0;
    float chiX = 0.0;
    float chiY = 0.0;
    while(i<N){
        //Getting datapoints of row i
        std::vector<float> dataRow = dataPoints[i] ;
        float x = dataRow[0];
        float y = dataRow[1];
        
        //getting error points of row i
        std::vector<float> errorRow = errorPoints[i] ;
        float xError = errorRow[0];
        float yError = errorRow[1];
       
        //calculating y =mx +c
        float expectedY = lineConsts.first*x + lineConsts.second;
        //calculating x = (y-c)/m
        float expectedX = (y - lineConsts.second)/lineConsts.first;

        //calculating chi for x and y
        float chiXRow = (x-expectedX)*(x-expectedX)/xError*xError;
        float chiYRow = (y-expectedY)*(y-expectedY)/yError*yError;

        //Adding to sum
        chiX += chiXRow;
        chiY += chiYRow;

        //loop incriment
        i ++;
    }
    //Assuming total chi is chi of Y add chi of X
    float totChi = chiY+chiX;
    return totChi;
}

//Linear Regression plus chi squared as an overflow
std::vector<float> linearReg(std::vector<std::vector<float>> & dataPoints,std::vector<std::vector<float>> & errorPoints){
    
    // getting N
    //Assuming error and data size are the same
    int N = dataPoints.size();
    
    // Setting all sums to 0
    float sumX = 0;
    float sumY = 0;
    float sumXY = 0; 
    float sumXX = 0;

    //looping over values of x,y. Doing all the sums
    for (auto& row : dataPoints){
        float x = row[0];
        float y = row[1];
        
        sumX += x;
        sumY += y;
        sumXY += y*x;
        sumXX += x*x;

    }

    //calculating m and c (p and q)
    float p = (N * sumXY - sumX*sumY)/(N*sumXX - sumX*sumX);//gradieent
    float q = (sumXX*sumY - sumXY*sumX)/(N*sumXX - sumX*sumX);//offset
    std::pair<float,float> lineConsts = {p,q};

    //getting chi from privous function
    float chi = chiSquareMePlz(dataPoints, errorPoints,lineConsts);

    std::vector<float> returnMePlz = {p,q,chi};
    //return as pair
    return returnMePlz;
}



//PRINT FUNCTIONS FOR DIFFERNT TYPES OF VARIBLES
//-------------------------------------------------------------------------------------
void print(std::string x){
    std::cout << x << "\n";;
   
}
void print(float  x){
    std::cout << x << "\n";;
   
}
void print(std::pair<float, float>& p){
    std::cout << p.first << ", " << p.second << "\n";

 }

void print(const std::vector<std::vector<float>> &matrix) {
    for (const auto &row : matrix) {
        std::cout << " --";
        for (const auto &val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

void print(const std::vector<float>& vec) {
    for (const float &val : vec) {
        std::cout << val << ", "; 
    }
    std::cout << "\n";
}
//-------------------------------------------------------------------------------------


//The most ugly of functions to be seen by humanity is situated on the next line, have fun
float powerUpToFive(const float & x,float & y ){
    int roundedY = std::round(y) ;
    
    if (roundedY == 0){
        return(0);
    }
    if (roundedY == 1){
        return(x);
    }
    if (roundedY == 2){
        return(x*x);
    }
    if (roundedY == 3){
        return(x*x*x);
    }
    if (roundedY == 4){
        return(x*x*x*x);
    }
    if (roundedY == 5){
        return(x*x*x*x*x);
    }
    if (roundedY == 6){
        return(x*x*x*x*x*x);
    }
}

std::vector<float> powerABunch(const std::vector<std::vector<float>> &dataPoints){

    std::vector<float> reternVector ; 

    for (auto& row : dataPoints){
        float x = row[0];
        float y = row[1];

        reternVector.push_back(powerUpToFive(x,y));
    }

    return reternVector;
}


//SAVING DIFFERNT TYPES OF VARIBELS TO TXT FILE
//-------------------------------------------------------------------------------------
void saveFuncReturn(std::string & fileName, std::string x){

    fileName = fileName + ".txt";
    std::ofstream outFile(fileName, std::ios::app);
    outFile << x << "\n";
}   
void saveFuncReturn(std::string & fileName, float x){

    fileName = fileName + ".txt";
    std::ofstream outFile(fileName, std::ios::app);
    outFile << x << "\n";

}
void saveFuncReturn(std::string & fileName,std::pair<float, float>& p){

    fileName = fileName + ".txt";
    std::ofstream outFile(fileName, std::ios::app);
    outFile << p.first << ", " << p.second <<"\n";

}

void saveFuncReturn(std::string& fileName, std::vector<std::vector<float>> &matrix){

    fileName = fileName + ".txt";
    std::ofstream outFile(fileName, std::ios::app);

    for (const auto &row : matrix) {
        outFile << " --";
        for (const auto &val : row) {
            outFile << val << " ";
        }
        outFile << "\n";
    }
}

void saveFuncReturn(std::string& fileName, std::vector<float> vec){

    fileName = fileName + ".txt";
    std::ofstream outFile(fileName, std::ios::app);

     for (const float &val : vec) {
        outFile << val << ", "; 
    }
    
    outFile << "\n";
}   
//-------------------------------------------------------------------------------------