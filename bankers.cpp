#include <iostream>
#include <fstream>
#include <vector>


bool read_file(std::string fileName);
void bankers_alg();

int row = 0;
int column = 0;
std::vector<std::vector<int>> allocation;
std::vector<std::vector<int>> max;
std::vector<int> available;


int main(){
    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin >> fileName;
    if (read_file(fileName)) return -1;
    bankers_alg();

    return 0;
}


void bankers_alg(){

    // Calculate the need. (Need = max-allocation)
    int need[row][column];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            need[i][j] = max.at(i).at(j) - allocation.at(i).at(j);
        }
    }
}



// Will open file, read file, and get the data from it
//    return a boolean value depending if there is an error or not
bool read_file(std::string fileName){
    std::cout << "Opening file: " << fileName << '\n';
    std::ifstream file;
    file.open(fileName); // Open file
    // If it did not open properly or does not exist then there is an error
    if (!file.is_open()){
        std::cout << "File could not open!\n";
        return true;
    }

    // File has successfully opened
    char ch;
    // 0 = allocate. 1 = max. 2 = available.
    int currentState = 0;
    std::vector<int> addVector;
    while(file >> ch){
        if (ch == ';'){
            if (currentState == 0){ // Current State set to Allocation
                allocation.push_back(addVector);
                addVector.clear();
                row++;
            } else if(currentState == 1){ // Current State set to Max
                max.push_back(addVector);
            } else if(currentState == 2){ // Current state set to Available
                addVector.clear();
                break;
            }
        } else if(ch == '.'){ // This will incremete the currentState
            currentState++;
            continue;
        } else if(int (ch)>= '0' && int(ch) <= '9'){  // Ensures it is a number
            if(currentState == 0 || currentState == 1){ // Happens only for allocation or max
                addVector.push_back(int(ch)-'0');
            } else if(currentState == 2){
                available.push_back(int(ch)-'0');
                column++;
            }
        }
    }
    // Close file and return that there is no error.
    file.close();
    std::cout << "Closing file: " << fileName << '\n';
    return false;
}