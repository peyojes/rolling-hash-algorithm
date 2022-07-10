 # Rolling Hash Algorithm
 
Make a rolling hash based file diffing algorithm. When comparing original and an updated version of an input, it returns a description ("delta") which can be used to upgrade an original version of the file into the new file.
 
 ## Prerequisites
 
 You need :
 - compiler (GCC, MinGW or other),
 - CMake program and on the Linux Make.
 
 ## Build and run on the Linux
 
 Create directory build:
 ````
 mkdir build
 cd build
 ````
 
 and get into this folder.
 
 ````
 cmake ..
 make
````

 ## Running the rdiff program
 
```` 
./rdiff --signature file.txt
````


 ## Running the tests
 
 In the build directory:
 
 ```` 
 ./unit_test
 ````

## License
This project is licensed under the MIT License.
