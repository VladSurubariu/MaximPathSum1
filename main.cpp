#include <iostream>
#include "matrixFunctions.h"

//the function returns the max value by comparing to int numbers
int findMaxValue(int aux1, int aux2){
    if(aux1>aux2)
        return aux1;
    else
        return aux2;
}

//the function returns the sum of the triangle, which can be seen at the top of the triangle
void returnSum(){
    std::cout<<"Ruta de suma maxima este:"<<dataMatrix[0][0];
}

//the function calculates the max sum path of the triangle
void solve(){
    unsigned numberOfMatrixLines=returnMatrixNumberOfLines();

    copyDataToMatrix();

    for(int iIndex=numberOfMatrixLines-2;iIndex>=0;iIndex--){ //starting from the second to last row and going to the first one
        for(int jIndex=0;jIndex<=iIndex;jIndex++){ //starting from the first column of the triangle to the last one
            //we look at the elements adjacent to the one that can be found at iIndex,jIndex coordinates
            //this can be done in our matrix by looking at the element below and the one to the right of the previous one
            int maxAdjacent=findMaxValue(dataMatrix[iIndex+1][jIndex], dataMatrix[iIndex+1][jIndex+1]); //the 2 adjacents are compared and
            //the one with the biggest value will be stored in maxAdjacent variable
            dataMatrix[iIndex][jIndex]=dataMatrix[iIndex][jIndex]+maxAdjacent; //and we modify the element at the coordinates iIndex, jIndex by summing up
            //the value of the biggest adjacent number
        }
    }
    returnSum(); //at the end we return the sum
}

int main() {
    checkData();
    solve();

    return 0;
}
