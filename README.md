# tspweekone
Homework: Travelling Salesperson Part One



Notes:
I tried to implement a default input for total_path_distance but it was easier to just let it accept an empty permutation_t and treat that as "use your current order".
The shortest.gif file may not connect the first and last points in the chain.
This lack of connection is only visual as part of the plot - the distance that line would take up is taken into account by the total_path_distance function.
I did my best to keep each file that tsp interacts with open for as little time as possible, for safety.
I used the -O3 flag in the makefile to make it run faster in realtime. This does not affect its relative performance in terms of big-O notation.
