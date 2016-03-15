Division of Labor:

In the first week, Lucy and Jessica outlined and coded a naive version, and then outlined
an iterative approach to minimax of two plays. This iterative approach was feasible only 
because minimax was looking two plays in the future. Lucy implemented the iterative minimax.

In the second week, Jessica resolved the inconsistent segfaults caused by forgetting to
consider edge cases in the first iterative approach. Next, Jessica and Lucy outlined in 
pseudocode a recursive approach to minimax to allow for more than two plays in the future. 
After implementing and debugging it together, they began to play around with parameters to 
beat other players and optimize.

Improvements made to AI:

-- Increasing depth of minimax to look further in the future

-- One of the functions we're using generate a list of all possible moves from the current board
    state by checking every square. One way to decreasing the number of calculations is to only
    iterate over the unoccupied squares or squares that are adjacent to current pieces. We tried  
    implementing only unoccupied squares by storing unoccupied squares in a set and removing
    them whever they become occupied. This failed to work. 

-- Alpha-beta pruning to filter out undesireable paths, reducing the amount of recursive
   calculations.