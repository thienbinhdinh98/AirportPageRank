# tbdinh2-mrosad4-haoenli2-lz15

## CODE LOCATION
* The major code are **graph.cpp vertex.cpp edge.cpp and airportData.cpp**
All of the major code are located in the root folder of the project

* The data files are located in the sub-folder, called **data**
* The test cases are located in the **tests-unit.cpp**, which locates in the **test** folder

* The result of BFS and Dijkstra can be found in **BFSresult.txt**
* The result of Dijkstra(shortestPath) will be displayed in the terminal
* The result of Pagerank is only one line, which can be see by running the code, will be displayed in the terminal.

## Instruction to run the code
We can run the code using make:
* **make flight** to run the main.cpp, which will ask you to end starting airport id and destionation airport id, which can be found the airports.csv
The starting airport id will also be used to run BFS.
And in the terminal, at the end of the build, you can see the result of PageRank.

## Testing
* **make test** to run the test suite
* To use with other smaller dataset that is smaller than ours, the users just need to change the file path, important information about vertices and edges and the ASSERTION REQUIREMENT. Please put all other data in data folder.

To change the file path follow these instructions:

* EXAMPLE: std::string dataFile = "tests/../data/**airports.csv**";
we can change it to:
* std::string dataFile = "tests/../data/**airports-test.csv**";


