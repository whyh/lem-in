# lem-in
## Graph traversal algorithmic project

An objective was to move the number of ants from the start point to the end point, as effective as possible. Start and end points can include as much ants as needed, and the others just one ant per one turn. Time of the program execution shouldn't exceed `3` seconds (on imac 2017). Using just basic `Libc` functions

## Approach
My first attempt was successful in delivering ants and efficiency, but was a total failure in time execution.     
Short about the algorithm: I've marked all the nodes in the graph depending on how far from the start they were, and then just let ants find their shortest way to the end. Before moving ant to the next room I check all other ants priority on the room. So to the next room will pass just the ant that is best suited for it.     
Second approach was successful in both time and efficiency parameters.      
Short about the algorithm: I've searched for the shortest way, then locked all nodes for the way and searched for the next one, till there were no more possible ways. Then  splited ants according to the each way length, and moved them towards the end node.  

## How to use
Visualisation is made using `SDL2` library, you need to install it first and change `path` to yours in the `makefile`.  
Run `make` and `./lem-in < map.lemin_map`  
To create your own map follow the next syntax     
`number_of_ants`  (specify number of ants)     
##start     
`room_name` `x_coordinate` `y _coordinate`  (create a start room     
##end     
`room_name` `x_coordinate` `y_coordinate`  (create an end room)     
`room_name` `x_coordinate` `y_coordinate`  (create a room)     
`room_name` `x_coordinate` `y_coordinate`  (create a room)     
...  (till you listed all the rooms you want)       
`room_name`-`another_room_name`(link two rooms)       
...  (till you created as much links as you want)       

## Visualisation
Requested output looked quite boring, that's why I decided to create visualisation.
To start lemin with visualisation, use `./lem-in` with option `-v`  
`./lem-in -v < map.lemin_map`
Start and pause visualisation with `space`
![lem-in](../assets/image/lem-in.gif)     
To move graph drag it with the `left mouse button`
![move](../assets/image/move.gif)     
To zoom in and out hold `l-alt` and use `mouse wheel`
![scale](../assets/image/scale.gif)     
Switch `counter` `on` and `off` activates with `button C`
![counter](../assets/image/counter.gif)     
     
