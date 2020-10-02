# lem-in
## Graph traversal algorithmic project

Moves `N` ants from a "start" graph node to the "finish" graph node, in the least amount of turns. Points, other than start and end, are constrained to contain a single ant at once


Executes in less than 3 seconds


Used just 3 standard C library functions
```c
ssize_t read(int fd, void *buf, size_t count);
void    *malloc(size_t size);
void    free(void *ptr);
```

## Approach
Used modified Dijkstra's algorithm with custom made ant distribution system

## How to use
Visualised with `SDL2` library. Install it and change the path in `makefile` accordingly

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
     
