#pragma once

std::fstream dataFile("data.txt"); //creating the file where the data will be stored

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