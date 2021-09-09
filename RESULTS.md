# OpenFlights Project Final Result

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Our final build of the project turned out very well and was able to meet all the goals we set beforehand. Our program successfully able to calculate the shortest flight path
between two airports, do a BFS traversal with all the connect Vertices and be able to find the airport with the most connected route to.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Our discovery during the development is the difference between adjacency matrix and adjacency list to build the graph. The adjacency list gives better
running time, only O(ElogV), but adjacency matrix was much easier to implement. We followed the guide to do BFS and Dijkstra for adjacency list, which was obviously will not work with our data structure.
The output of our BFS function was meant to display every airport in ourgraph, however we noticed some were missing. After looking into the problem we discovered that many of the airports in the OpenFlights dataset had no commercical flights to them
. Therefore, we began to clean up the data, and figured there are only 7698 vertices

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Furthermore, before running PageRank algorithm, we expected many airport to have the same numbers of connected routes. In reality, it was only one airport, and that is Frankfurt am Main Airport, with ID 340.
Frankfurt is a large airport in Germany, Europe, with lots of cheap commercial flights. Our finding matchs with the real world scenario where Frankfrut is in the center of Europe, with many connecting flights, and given Europe has many cheap commercial flights, the destination of the result makes sense.

--------------------------------------------------------------------------------------------------------------------------------
BFS result with src_id = 1:
1 -> 
2 -> 
3 -> 
4 -> 
5 -> 
6 -> 
5430 -> 
5436 -> 
5431 -> 
5433 -> ... (the result is cut short, for full result, run the command and open file BFSresult.txt)

shortestPath(Dijkstra) result: 
USER enter first id: 1
USER enter second id: 3
Terminal print:
1->3

USER enter first id: 1
USER enter second id: 10
there are not routes from: 1 to 10

PAGERANK result as airport ID in airports.csv data:
340

