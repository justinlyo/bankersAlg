#include <iostream>
#include <fstream>
#include <vector>


bool read_file(std::string fileName);
void bankers_alg();

int row    = 0;
int column = 0;

std::vector<std::vector<int>> allocation;
std::vector<std::vector<int>> max;
std::vector<int>              available;


int main(){
    char shouldContinue = 'y';
    while(shouldContinue == 'y'){
        std::string fileName;
        std::cout << "Enter file name: ";
        std::cin  >> fileName;
        if (read_file(fileName)) return -1;

        bankers_alg();

        std::cout << "Do you want to continue? (y/n): ";
        std::cin  >> shouldContinue;
    }
    return 0;
}

// Function that will implement the bankers algorithm using allocation, max, and available. It will determine if there is a sequence or not.
void bankers_alg(){
    int need[row][column];
    int inSequence[row]; // Set all indexes of inSequence to 0(false) 
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            need[i][j] = max.at(i).at(j) - allocation.at(i).at(j);
        }
        inSequence[i] = 0;
    }
    int sequence[row];
    int count = 0;

    // Will determine the sequence of the processes
    for(int limit = 0; limit < row; limit++){
        for(int i = 0; i < row; i++){
            if (inSequence[i] == 1) continue; // Process cannot already be in sequence
            bool canAllocate = true; //Flag to determine if it should be put into sequence
            // For loop will determine if a process has the necessary available resources
            for (int j = 0; j < column; j++){
                // Need has to be greater than available. Otherwise, there is not enough available resources to be allocated.
                if(need[i][j] > available[j]){
                    canAllocate = false;
                    break; // Breaks out as it is unnecessary to check the other indexes
                }
            }
            // Check to see if it can allocate
            if (canAllocate){
                // Will increment necessary components and add onto the available resources
                sequence[count] = i;
                inSequence[i] = 1;
                count++;
                for (int j = 0; j < column; j++){
                    available[j] += allocation.at(i).at(j); // Add the allocated resources onto the available
                }
            }
        }
    }

    // Determines if there is a safe state
    bool isSafe = true;
    for(int i = 0; i < row; i++){
        if (inSequence[i] != 1){
            isSafe = false;
            break;
        }
    }

    // Output whether it is a safe state or not and the sequence if so.
    if(isSafe) {
        std::cout << "There is a safe state! ";
        for(int i = 0; i < row; i++){
            std::cout << " " << sequence[i] << " ";
        }
    } else{
        std::cout << "There is no safe state!";
    }
    std::cout << "\n\n";

    // We are done with the three variables so we clear them.
    allocation.clear();
    max.clear();
    available.clear();
}



// Will open file, read file, and get the data from it
//    return a boolean value depending if there is an error or not
bool read_file(std::string fileName){
    row = 0; column = 0;
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
    while(!file.eof() && file >> ch){
        if (ch == ';'){
            if (currentState == 0){ // Current State set to Allocation
                allocation.push_back(addVector);
                addVector.clear();
                row++;
            } else if(currentState == 1){ // Current State set to Max
                max.push_back(addVector);
                addVector.clear();
            } else if(currentState == 2){ // Current state set to Available
                addVector.clear();
                break;
            }
        } else if(ch == '.'){ // This will increment the currentState
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
    std::cout << "Closing file: " << fileName << "\n\n";
    return false;
}