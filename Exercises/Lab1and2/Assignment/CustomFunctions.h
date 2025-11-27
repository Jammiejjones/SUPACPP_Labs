#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

bool isFileOpen(const std::ifstream &file);
std::vector<float> magnitudeOfVectors(const std::vector<std::vector<float>> & matrixOfVectors);
std::vector<std::vector<float>> get_values_from_datafile(std::string file_name, int fun_user_N) ;
int check_number_lines(std::string &file_name);

std::pair<float,float> linearReg(std::vector<std::vector<float>> & dataPoints);
std::vector<float> linearReg(std::vector<std::vector<float>> & dataPoints,std::vector<std::vector<float>> & errorPoints);
float chiSquareMePlz(std::vector<std::vector<float>> & dataPoints,std::vector<std::vector<float>> & errorPoints,std::pair<float, float>& lineConsts);

void print(const std::vector<float>& vec);


void print(std::string x);
void print(std::pair<float, float>& p);
void print(const std::vector<std::vector<float>> &matrix);
void print(float  x);


float powerUpToFive(const float & x,float & y );
std::vector<float> powerABunch(const std::vector<std::vector<float>> &dataPoints);

void saveFuncReturn(std::string & fileName, std::vector<float> vec);
void saveFuncReturn(std::string& fileName, std::vector<std::vector<float>> &matrix);
void saveFuncReturn(std::string& fileName,std::pair<float, float>& p);
void saveFuncReturn(std::string & fileName, float x);
void saveFuncReturn(std::string & fileName, std::string x);


