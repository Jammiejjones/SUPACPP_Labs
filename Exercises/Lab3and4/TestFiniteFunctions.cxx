#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include "CustomFunctions.h"




int main(){

    std::vector<double> dataFromFile = readVector("./Outputs/data/MysteryData14210.txt");

    FiniteFunction obj1;
    obj1.plotData(dataFromFile,50, true);
    obj1.plotFunction();
    obj1.printInfo();


    FiniteFunction obj2(-10,10,"Norm");
    obj2.plotData(dataFromFile,50, true);
    obj2.plotFunction();
    obj2.printInfo();

    FiniteFunction obj3(-15,15,"Cauchy");
    obj3.plotData(dataFromFile,50, true);
    obj3.plotFunction();
    obj3.printInfo();

    FiniteFunction obj4(-15,15,"Crystal");
    obj4.plotData(dataFromFile,50, true);
    obj4.plotFunction();
    obj4.printInfo();


}





