# Bankers Algorithm for deadlock avoidance
Justin Lyogky
CS 33211<br /> 
#### Programming Assignment #2<br /> 
Considering a system with five processes P0 through P4 and three resources of type A,B,C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0, the following snapshot of the system has been taken (input.txt). Implement the Banker's algorithm to answer the following question: Is the system in a safe state and what is the sequence?

# Instructions
Clone the git repository with the following:
```
gh repo clone justinlyo/bankersAlg
```
Once you have cloned the git repository, you should be able to access bankers.cpp, input.txt, and input2.txt. You are able to compile with the following command.
```
g++ bankers.cpp -o bankers
```
Once you have compiled the program, we are able to run it with the following command.
```
./bankers
```
Once it begins running, it will ask a prompt similar to this.
```
Enter file name:
```
We should enter a file name here, for this example we are able to use input.txt or input2.txt.
Assume we were to do input.txt, the following would be outputted.
```
Enter file name: input.txt
Opening file: input.txt
Closing file: input.txt

There is a safe state!  1  3  4  0  2 

Do you want to continue? (y/n):
```
It will output that there is a safe sequence, and it will print out this sequence. It will also allow the user to continue if they wish to try another input file.

# Video Walkthrough

# Explanation
The assignment was to have a banker program that, given an input file consisting of allocation, max, and available resources, will output if there is a safe state or not and will determine a possible sequence of the processes. If there is not a possible sequence then the processes are of an unsafe state, meaning that there will be a deadlock. Therefore it is important for these processes to be in a safe state to avoid deadlocks.

## Overview
Our banker.cpp file is the main programming file. It contains three functions, a `main()`, `bankers_alg()`, and `read_file(std::string fileName)`. The main file will allow the user to input a file name that will be sent over to the `read_file()` function. This `read_file()` function will open the file, read the file, and parse any data to 5 different variables. These variables are allocation, max, available, row, and column. Allocation, max, and available are all vectors, whereas row and column are both integers that will hold the number of rows and columns respectfully. There are also 2 different text files: input.txt and input2.txt. Input.txt contains the example problem given on the assignment, whereas input2.txt contains an example that will yield an unsafe state.

## Main
The `main()` function will allow the user to input a file that should be used to get the data from. The main function will then call the read_file() function and the bankers_alg() function. After it calls these two functions, it will ask the user if it wants to continue. If the user wants to continue it will ask for another file name and repeat the process again until the user says no.

## Reading the File
The `read_file(std::string fileName)` function will read the file that the user inputted and will collect data from it. The input files have to follow a specific format of a row of allocation first, each number being separated by a space and each row being separated by a semicolon. Then when it switches to max or available, there has to be a period in between. We open the file using `file.open(fileName)` and will check if it opened correctly by using `file.is_open()`. Once we confirm the file has sucessfully opened, then we can continue into the parsing. We two variables, ch and currentState. The ch variable will go character by character in the data and will be checked later to determine what should be done with it. The currentState will be the current state we are working on, 0 being allocation, 1 being max, and 2 being available. This currentState will increment everytime a period is encountered. We start the while loop with `while(file >> ch)`, which will go character by character in the text file. We then will have 3 checks for determining what to do with this ch variable. 

Due to ease of understanding the process, we will begin at the last if statement. We check to see if the character is between 0 and 9. 
```
if (int(ch) >= '0' && int(ch) <= '9')
```
If the character is between 0 and 9, then we then check what state it is currently on. If the state is either allocation(0) or max(1), then we will convert this character into an integar by `int(ch) - '0'` and will push it onto the addVector. However, if the current state is available(2), then we will convert eh character into an integar and push it back onto the available variable. We will also increment coulmn here since the number of columns for all three variables will directly relate to the number of columns in the available resources. 
```
if (ch == '.')
```
If the character is a period then we will increment the current state as the period should be between each state in the input file. We also use `continue;` to go to the next iteration.
```
if (ch == ';')
```
If the character is a semicolon, then we have to check what the current state is. If the current state is either allocation(0) or max(1), then we will push back the addVector to each one respectively and clear the addVector. We also increment row in one of these since the number of rows would directly relate to the number of rows in either of these variables. If the current state was available(2), then we would just clear the addVector and break.
Once the end of the file has been reached, then it will exit the while loop and close the file. It will then go back to main.

## Bankers Algorithm


