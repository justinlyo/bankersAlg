# Bankers Algorithm
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
[![Watch the video](https://img.youtube.com/vi/eWcMR05BSUE/maxresdefault.jpg)](https://youtu.be/eWcMR05BSUE) 
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
The `bankers_alg()` is in charge of preforming the bankers algorithm given that allocation, max, and available are all set. 
We first need to calculate the NEED since it is needed in calculating if there is a deadlock. This is done by the following code
```
for(int i = 0; i < row; i++){
   for(int j = 0; j < column; j++){
      need[i][j] = max.at(i).at(j) - allocation.at(i).at(j);
   }
   inSequence[i] = 0;
}
```
We set need to the same row size and column size as before. Need is calculate by max subtracted with allocation. So, as seen above, we do this by using a nested for loop to iterate through all the values of max and allocation, subtract them, and place them into the need matrix. It also sets the inSequence variable, which will act as an index holder, and if set to 1, then it means that that index is in the safe state. Therefore, we can conclude that if all the values are set to 1, then there exists a safe state. We can also use this to check if a process is already in the sequence to avoid duplicates. Once it does this, it will continue onto the next part of the bankers algorithm, which is to determine the sequence if there is one. There will be three for loops inside of each other. The basic schema of the code is given below.
```
for(int limit = 0; limit < row; limit++){
  for(int i = 0; i < row; i++){...
    for(int j = 0; j < column; j++){...}}}
```
The first for loop is the limit of times it should itereate through each process. This is the max amount of times it takes until we cover all the possibilities. The second for loop is to iterate through all the rows. The third for loop is to iterate through all the columns. 

We have four main variables that will be used in the for loop. 
```
int inSequence[row];
int sequence[row];
...
(in the for loops)
bool canAllocate = true;
```
The first main variable would be the inSequence variable that was mentioned earlier. It will be initialized to all zeros and the process number will directly correspond to the indexes of the inSequence array. This means that if an index is changed to 1, then it will signify that the process is in the sequence. We then have the sequence array that will hold the sequence of execution for the processes. There is also the need variable, which will hold the needed resources for each process. The last variable is canAllocate, which is a flag to determine if the current process should be put into sequence.


The first thing we do is check if the process is already in the sequence. We use `if(inSequence[i] == 1) continue;` to check this. If the current index, which directly relates to the process number, is set to 1, then the process is already in the sequence and cannot be added again. We do not want duplicates so it will continue onto the next loop iteration. Otherwise, it will continue to with the code to the following for loop, which is the iterator that checks the columns. We set canAllocate beforehand to true as a flag that it can be put into the sequence. In the for loop we check if the current process' need is greater than the available resources with the following code.
```
if(need[i][j] > available[j]){
  canAllocate = false;
  break;
}
```
This code will check to see if the process' needed resources are greater than the available resources. The i indicates the current row and j indicates the current column. If so, then it will set the canAllocate to false and break out. Outside of this for loop, we use `if(canAllocate)` to check to see if we are able to allocate the resources to this process. If we can allocate then it will do many things. First, it will add the process number to the end of the sequence. We will then adjust the inSequence index i to 1 as it will show that the process number is already in the sequence. Lastly, we will add the resources of the process to the total available resources. We do this with the following code.
```
for(int j = 0; j < column; j++){
  available[j] += allocation.at(i).at(j);
}
```
We are adding the processes allocated resources to the total available resources since the process is able to be completed, meaning that the resources originially allocated to the process are now released. Therefore it will be added to the total amount of the current available resources. Once added, the for loop for the row will continue onto the next row until every row and column has been checked, and until the limit is reached for the outer loop.

Now, with all of this information in the variables, we are able to determine if there is a safe state and what the sequence is if there is a safe state. We will check if there is a safe state with the following code.
```
bool isSafe = true;
for(int i = 0; i < row; i++){
  if(inSequence[i] != 1){
    isSafe = false;
    break;
  }
}
```
This code will have a isSafe variable that will act as a flag to determine if the processes are in a safe state. It will check all the values in inSequence and if one of them is not a 1, then that means that there is a process that is not in the sequence, therefore causing it to be in an unsafe state. This will set the isSafe flag to false and break out. We will then need to output if there is a safe state and what it is or if there is no safe state. We simply do this by checking if isSafe is true. If it is true then we will print out that there is a safe state and use the following for loop to print out each position in the sequence.
```
for(int i = 0; i < row; i++){
  std::cout << " " << sequence[i] << " ";
  }
```
This will print out the sequence that the processes are able to run in a safe state. If the isSafe variable is false then we will print out that there is no safe state. 


## Wrapping up
At the end of the bankers algorithm, we clean up the vectors by clearing them. We do that by the following code.
```
allocation.clear();
max.clear();
available.clear();
```
Once the bankers algorithm completes, it will return back to the main function. Here, we will ask the user if they would like to continue. If they would then it will ask them to for another file to input and test. If they would not like to continue then it will stop the program.

# Conclusion
The bankers algorithm is an algorithm that will avoid deadlocks and figure out a possible sequence that the processes need to run in order to not run into any problems. It will compare each of the processes needs (Max - Allocation) and compare this to the available resources. If there are enough available resources, then the process is added to the sequence and its resources are now added to the total available resources. If there are not enough resources then it will continue to the next process and check if there are enough available resources to fill its needs. It will continue doing this until a sequence is found or if there is no possible sequence. 
