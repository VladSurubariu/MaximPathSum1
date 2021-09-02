#include <iostream>
#include <fstream>

std::fstream dataFile("data.txt"); //creating the file where the data will be stored
int dataMatrix[150][150]; //creating the matrix where the data will be stored

//the function deletes all content in a file
void deleteFileContent(){
    std::fstream newDataFile; //initialising the same file, but with another name variable
    newDataFile.open("data.txt", std::ofstream::out | std::ofstream::trunc); //opening the file for writing with the truncate-option
    newDataFile.close();
}

//the function reads the elements for a new set of data
void readElements(unsigned numberOfLines){
    int numberOfElements, elementValue;

    std::cout<<"Introduceti, pe rand, fiecare linie a triunghiului:"<<std::endl;

    for(unsigned index=0;index<numberOfLines;index++){
        numberOfElements=0;
        while(numberOfElements<=index){ //for each line of the triangle we only read as many elements as the index of the column
            numberOfElements++;
            std::cin>>elementValue;
            dataFile<<elementValue<<" "; //after reading the value for each individual item, it is stored in the file "data.txt"
        }
        dataFile<<std::endl;
    }
}

//the function is called when the user wants to use another set of data
void setNewData(){
    deleteFileContent(); //the first step in changing the set of data is to delete the old content

    unsigned numberOfLines;
    std::cout<<"Introduceti numarul de linii pentru noul triunghi:"<<std::endl;
    std::cin>>numberOfLines;
    dataFile<<numberOfLines<<std::endl; //the number of lines that form the triangle is stored on the first line of the data file

    readElements(numberOfLines); //the next elements for the data are read
}

//the function is the first one called and asks the user if he wants to change the data set
void checkData(){
    std::string userAnswer;

    std::cout<<"Doriti sa schimbati setul de date? Tastati 1 pentru da si 0 pentru nu:"<<std::endl;
    std::cin>>userAnswer;

    if(userAnswer=="1"){ //if the user answer is 1 the function setNewData() is created
        setNewData();
    }
    else if(userAnswer!="0"){ //if the user answer is not 1 or 0 it will be considered invalid and the function will be called again
        std::cout<<"Invalid."<<std::endl;
        checkData();
    }
    //if the user answer in 0 the function will not do anything because it means that the user doesn't want to change the data set
}

//the function returns to the beginning of the "data.txt" file so that the number of lines can be read again
void readFileFromStart(){
    dataFile.clear(); //the eof and fail flags have been set so we have to clear them with the clear function
    dataFile.seekg(0); //and we seek the posion 0 to go to the first element in the file
}

//the function returns the number of lines that compose the triangle by reading the first number in the file
int returnMatrixNumberOfLines(){
    unsigned numberOfLines;
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
