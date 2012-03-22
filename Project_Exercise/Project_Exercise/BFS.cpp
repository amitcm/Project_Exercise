#include "stdafx.h"
#include "BFS.h"

typedef pair<int, int> state;

int grid[5][5] = {
					{0, 0, 0, 0, 0},
					{0, 1, 1, 0, 0}, 
					{0, 0, 1, 0, 0},
					{0, 1, 1, 1, 0},
					{0, 0, 0, 0, 0}
				 };

void populate_grid() {
}

bool goal_state_reached(state s) {
	return false;
}

/*
						2 IMPORTANT TIPS


		1. Add extra padded zeros to skip ugly looking bound check if statements

					1 1 0  
					0 1 0
					1 1 1

					becomes

					0 0 0 0 0
					0 1 1 0 0 
					0 0 1 0 0
					0 1 1 1 0
					0 0 0 0 0

		2. When processing moves over a grid in North, South, East and West,
		 Set these moves as X, Y and possibly Z deltas in an array

				 X[4] = {1, 0, -1, 0};
				 Y[4] = {0, 1, 0, -1};

		 Like wise, if we have to all possible moves for problem [topcoder problem "aaaa"]
		 we need to maintain following 4 arrays:
				 R[8] = {1, 0, 0, 0, -1, 0, 0, 0};
				 S[8] = {0, 1, 0, 0, 0, -1, 0, 0};
				 T[8] = {0, 0, 1, 0, 0, 0, -1, 0};
				 U[8] = {1, 0, 0, 1, 0, 0, 0, -1};

		 Potential moves can be 
				r = P.first + X[i]
				c = P.second + Y[i] for the first case

		 Similarly for second,
				r = P.first + R[i]
				s = P.second + S[i]
				t = P.third + T[i]
				u = P.fourth + U[i]

		 So, grid can be accessed and check by grid[r][c] or grid[r][s][t][u]
*/
void enqueue_valid_move(queue< state > &q, state s) {
	int X[4] = {1, 0, -1, 0};
	int Y[4] = {0, 1, 0, -1};
	for(int i = 0; i < 4; ++i) {
		int r = s.first + X[i];
		int c = s.second + Y[i];
		if(grid[r][c] == 1){
			state temp;
			temp.first = r;
			temp.second = c;
			q.push(temp);
		}
	}
}

int SolveUsingBFS(state P ) {
	int count = 0;			// Number of moves or as per requirement
	set< state > visited;
	queue< state > q;

	// Push the first element of the set in queue
	q.push(P);

	// Loop through the nodes (in a connected component, actually)
	while(! q.empty()) {
		// get and pop front element
		state s = q.front();
		q.pop();

		// If this node has been already visited, look for next by continuing in the loop
		if(visited.find(s) != visited.end()) {
			continue;
		}

		// Whether the goal has been achieved. Terminate out of loop and return the required.
		if(goal_state_reached(s))
			return count;

		// Insert the current visited.
		visited.insert(s);

		// Try all possible moves. Add them to our queue.
		enqueue_valid_move(q, s);
	}
	return -1;
}