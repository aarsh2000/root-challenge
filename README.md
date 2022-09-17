# Root Challenge

A c++ program that parses driver trips and returns trip details (see sample i/o for more [details](https://gist.github.com/dan-manges/1e1854d0704cb9132b74)).

# How to Run Locally
In order to run the c++ program, you must first compile `main.cpp` (it is important to note that each machine compiles c++ differently, so you must recompile once you clone).
For compilation you can use [clang](https://clang.llvm.org/) or [gcc](https://gcc.gnu.org/), in this case I will show compilation with gcc. Once you have gcc installed, in the root directoy of the repo run,
```
g++ -std=c++17 main.cpp -o run
```
To pass input to `run` you must use stdin,
```
cat INPUT_FILE | ./run 
```
or
```
./run < INPUT_FILE
```
For example,

![alt text](https://i.imgur.com/6sosl5C.png)

## Testing
The tests can be found under the `test/` directory. Note that the testing is done by bash script `runSuite`, where it takes two arguments, a file with names for all the tests, and the compiled program. The file with the names of all the tests contains the base name of the tests, and within that directory there will exist two files with that base name, one with the `.in` extension (reporesenting input), and another with `.out` (representing expected output) (note both are required!),

In this case we have the file with the test names to be `test/suite.txt`, containing tests like basic_test, where `test/basic_test.in` is the input for the program and `test/basic_test.out` is the expected output.

So to run tests,
```
cd test
./runSuite suite.txt ../run
```

For example,
![alt text](https://i.imgur.com/stoLcRB.png)

## How the Program Works
The program first reads each line of input. If a driver command is seen, it gets added to a map (key value pair data structure), where the key is the driver's name, and the value is the struct Driver. If the trip command is seen, we find the driver in the map, and add the trip information to the Driver struct. Once we are done reading input, we itterate through the map and move each Driver into a priority queue, where the key is the total miles traveled, and the value is the Driver struct. Finally, we itterate through the priority queue from the top, and print out the driver's details.

## Features and Optimizations
- Uses smart pointers, which ensures that no memmory is being leaked  (unique_ptrs)
- Uses best practices for Object oriented programming through structs and data abstraction
- Uses map key-value pair data structure to store drivers, so searching for a driver is efficient (search only takes O(log(n)) time, where n is the number of distinct drivers)
- Priority queue sorts when inserting, and since we're inserting n drivers, the time complexity of this algorithm is O(nlog(n))

## Notes and Important Assumptions for Correctness

- Non stable sort used, so users who traveled the same distance might not be sorted in original order (i.e see test `test/no_move.*`)
- Last line is a new line for output (i.e see last lines in`test/*.out`), or else tests will fail
- If a driver that already exists is reintialized (i.e two Driver commands with the same name), nothing happens, the previous driver remains as is (i.e see `test/duplicate_driver.*`)




