#include <iostream>
#include <fstream>

std::fstream dataFile("data.txt");
unsigned dataMatrix[50][50];

void deleteFileContent(){
    std::fstream newDataFile;
    newDataFile.open("data.txt", std::ofstream::out | std::ofstream::trunc);
    newDataFile.close();
}

void readElements(unsigned numberOfLines){
    unsigned numberOfElements, elementValue;

    std::cout<<"Introduceti, pe rand, fiecare linie a triunghiului:"<<std::endl;

    for(unsigned index=0;index<numberOfLines;index++){
        numberOfElements=0;
        while(numberOfElements<=index){
            numberOfElements++;
            std::cin>>elementValue;
            dataFile<<elementValue<<" ";
        }
        dataFile<<std::endl;
    }
}

void setNewData(){
    deleteFileContent();

    unsigned numberOfLines;
    std::cout<<"Introduceti numarul de linii pentru noul triunghi:"<<std::endl;
    std::cin>>numberOfLines;
    dataFile<<numberOfLines<<std::endl;

    readElements(numberOfLines);
}

void checkData(){
    std::string userAnswer;

    std::cout<<"Doriti sa schimbati setul de date? Tastati 1 pentru da si 0 pentru nu:"<<std::endl;
    std::cin>>userAnswer;

    if(userAnswer=="1"){
        setNewData();
    }
    else if(userAnswer!="0"){
        std::cout<<"Invalid."<<std::endl;
        checkData();
    }
}

void readFileFromStart(){
    dataFile.clear();
    dataFile.seekg(0);
}

unsigned returnMatrixNumberOfLines(){
    unsigned numberOfLines;
    readFileFromStart();
    dataFile>>numberOfLines;
    return numberOfLines;
}

void copyDataToMatrix(){
    unsigned numberOfMatrixLines=returnMatrixNumberOfLines();

    for(int iIndex=0;iIndex<numberOfMatrixLines;iIndex++){
        for(int jIndex=0; jIndex<numberOfMatrixLines;jIndex++){
            if(jIndex<=iIndex){
                dataFile>>dataMatrix[iIndex][jIndex];
            }
            else{
                dataMatrix[iIndex][jIndex]=0;
            }
        }
    }
}

void writeMatrix(){
    unsigned numberOfMatrixLines=returnMatrixNumberOfLines();
    for(int iIndex=0;iIndex<numberOfMatrixLines;iIndex++){
        for(int jIndex=0; jIndex<numberOfMatrixLines;jIndex++){
            std::cout<<dataMatrix[iIndex][jIndex]<<" ";
        }
        std::cout<<std::endl;
    }
}

unsigned findMaxValue(unsigned aux1, unsigned aux2){
    if(aux1>aux2)
        return aux1;
    else
        return aux2;
}

void returnSum(){
    std::cout<<"Ruta de suma maxima este:"<<dataMatrix[0][0];
}

void solve(){
    unsigned numberOfMatrixLines=returnMatrixNumberOfLines();
    copyDataToMatrix();

    for(int iIndex=numberOfMatrixLines-2;iIndex>=0;iIndex--){
        for(int jIndex=0;jIndex<=iIndex;jIndex++){
            unsigned maxAdjacent=findMaxValue(dataMatrix[iIndex+1][jIndex], dataMatrix[iIndex+1][jIndex+1]);
            dataMatrix[iIndex][jIndex]=dataMatrix[iIndex][jIndex]+maxAdjacent;
        }
    }
    returnSum();
}

int main() {
    checkData();
    solve();
    return 0;
}
