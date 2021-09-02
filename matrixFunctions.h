#pragma once
#include "fileFunctions.h"

int dataMatrix[150][150]; //creating the matrix where the data will be stored

//the function returns the number of lines that compose the triangle by reading the first number in the file
int returnMatrixNumberOfLines(){
    int numberOfLines;
    readFileFromStart(); //the file is set to be readen from the start
    dataFile>>numberOfLines; //the number of lines that compose the triangle is read
    return numberOfLines; //and it is returned
}

//the function copies the data that can be found in the file and stores it in dataMatrix[][]
void copyDataToMatrix(){
    unsigned numberOfMatrixLines=returnMatrixNumberOfLines();

    for(int iIndex=0;iIndex<numberOfMatrixLines;iIndex++){ //the index for rows
        for(int jIndex=0; jIndex<numberOfMatrixLines;jIndex++){ //the index for columns
            if(jIndex<=iIndex){ //since on every line of the triangle the max number of elements is the index of the row jIndex has to always be <=iIndex
                dataFile>>dataMatrix[iIndex][jIndex];
            }
            else{ //every element that doesnt compose the triangle will have the value 0
                dataMatrix[iIndex][jIndex]=0;
            }
        }
    }
}

//the function prints the dataMatrix[][]
void writeMatrix(){
    unsigned numberOfMatrixLines=returnMatrixNumberOfLines();
    for(int iIndex=0;iIndex<numberOfMatrixLines;iIndex++){
        for(int jIndex=0; jIndex<numberOfMatrixLines;jIndex++){
            std::cout<<dataMatrix[iIndex][jIndex]<<" ";
        }
        std::cout<<std::endl;
    }
}