// C++ Code implementation for BFS
#include <iostream> // cout 
#include <queue> // FIFO queue 
#include <array>
#include <map> // dictionary

// debugging output to the screen
#include <conio.h> //
#include <thread>
#include <chrono>

using namespace std;

int step_counter = 0;

// outputing 
const bool verbose_output = false; // To see the expansion or the exploration step by step, amek this variable true
const bool break_output = false; // if true the user must hit the keyboard after each step
const bool slow_output = true; // if true wait_period of time is put between each 2 explorations 
const int wait_period = 500;// wait time between 2 explorations in milliseconds 

// choose the map by definting the corresponding Example. For example if you want Example 3, change Example_# in below to Example_3
#define Example_6 true

// Based on the previous macro, only map is choosen
#ifdef Example_1
const int ROW_SIZE = 4;	
const int COL_SIZE = 4;	
char grid[][COL_SIZE] = {
	{ '1', '0', '1', 'S' },		
	{ '0', '1', '0', '0' },		
	{ '1', '0', '0', '0' },		
	{ 'G', '0', '0', '0' }
};
#elif Example_2
const int ROW_SIZE = 10;
const int COL_SIZE = 10;
char grid[][COL_SIZE] = {
	{ 'S', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', 'G' }
};
#elif Example_3
const int ROW_SIZE = 10;
const int COL_SIZE = 10;
char grid[][COL_SIZE] = {
	{ 'S', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', 'G' }
};
#elif Example_4
const int ROW_SIZE = 10;
const int COL_SIZE = 10;
char grid[][COL_SIZE] = {
	{ 'S', '0', '0', '0', '0', '1', '1', '1', '1', 'G' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' }
};
#elif Example_5
const int ROW_SIZE = 10;
const int COL_SIZE = 5;
char grid[][COL_SIZE] = {
	{ '0', '0', '0', '1', '1' },
	{ '1', '0', 'G', '1', '1' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', 'S', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '1', '1', '0', '0' }
};
#elif Example_6
const int ROW_SIZE = 10;
const int COL_SIZE = 5;
char grid[][COL_SIZE] = {
	{ '1', '0', '0', '0', '1' },
	{ '1', '0', '1', '0', '0' },
	{ '1', 'G', '1', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', 'S', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '1', '1', '0', '0' }
};
#elif Example_7
const int ROW_SIZE = 10;
const int COL_SIZE = 5;
char grid[][COL_SIZE] = {
	{ '1', '0', '0', '0', '1' },
	{ '1', '0', '1', '0', '0' },
	{ '1', '0', '1', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', 'S', '0', 'G', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '1', '1', '0', '0' }
};
#elif Example_8
const int ROW_SIZE = 10;
const int COL_SIZE = 5;
char grid[][COL_SIZE] = {
	{ '1', '0', '0', '0', '1' },
	{ '1', '0', '1', '0', '0' },
	{ '1', 'G', '1', '0', '0' },
	{ '1', '1', '1', '1', '1' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', 'S', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '1', '1', '0', '0' }
};
#endif // choose_map 

// The below function shows the map
void show_map(char input_map[ROW_SIZE][COL_SIZE]) {
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			std::cout << input_map[i][j] << "\t";
		}
		std::cout << endl;
	}

	if(verbose_output){
		cout << endl << "Notations:\n"
			"F: current frontier \t E: previously explored frontier \t S: start node \t G: goal node \n"
			"*: Descovered Node \t 0: free & unexplored node \t 1:obstacle" << endl ;
	}

	if (break_output)
		_getch();

	if (slow_output)
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_period));

}

// Initialize parent array with -1 (-1 means no parent or in otherwords the cell is not explored or descovered by any frontier)
void initialize_parents(int map_size, map<int, int> & parent) {
	for (int i = 0; i < map_size; i++) {
		parent.insert(pair<char, int>(i, -1)); //-1 means no parent
	}
}

// The below is defining the entry of each location in the queue. Each cell is defined by its col, row, id and real distance (real distance = exploration step BTW) 
// from start node
// QItem for current location and distance from start location 
class QItem {
public:
	int row;
	int col;
	int id;
	int dist;
	QItem(int x, int y, int ID,  int w)
		: row(x), col(y), id(ID), dist(w)
	{
	}
};

// Here is the real BFS function 
int BFS(char grid[ROW_SIZE][COL_SIZE], map<int, int> & parent, int & start_node_id, int & goal_node_id)
{
	QItem start(0, 0, 0, 0);

	// To keep track of visited QItems. Marking blocked cells as visited. By this we avoid extra check if cell is barrier or not
	// At the same time when we descover start or goal nodes we use their col and row indices to find ther ids (start_node_id and goal_node_id)
	bool visited[ROW_SIZE][COL_SIZE];
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (grid[i][j] == '1') // if barrier
				visited[i][j] = true; // mark visited
			else
				visited[i][j] = false;

			// Finding start 
			if (grid[i][j] == 'S')
			{
				start.row = i;
				start.col = j;
				start.id = i + ROW_SIZE * j; 			// ID = row_index + row_size * col_index 
				start_node_id = i + ROW_SIZE * j;
			}

			// Finding goal 
			if (grid[i][j] == 'G')
			{
				goal_node_id = i + ROW_SIZE * j;
			}
		}
	}

	// applying BFS on matrix cells starting from start node
	queue<QItem> q;
	q.push(start);
	visited[start.row][start.col] = true;
	while (!q.empty()) {
		QItem p = q.front(); // p is the current Fronteir
		q.pop();

		//  goal found; 
		if (grid[p.row][p.col] == 'G') { 
			return p.dist; // break the loop and return minimum hops = distance in uniform grid
		}

		if (verbose_output && grid[p.row][p.col] != 'S') {
			grid[p.row][p.col] = 'F';

			show_map(grid);
		}

		// moving up 
		if (p.row - 1 >= 0 &&
			visited[p.row - 1][p.col] == false) {
			int id = (p.row - 1) + ROW_SIZE * p.col;
			q.push(QItem(p.row - 1, p.col, id, p.dist + 1));
			parent[id] = p.id;
			visited[p.row - 1][p.col] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output){
				if(grid[p.row - 1][p.col] != 'G')
					grid[p.row - 1][p.col] = '*';
				show_map(grid);
			}
		}

		// moving right 
		if (p.col + 1 < COL_SIZE &&
			visited[p.row][p.col + 1] == false) {
			int id = p.row + ROW_SIZE * (p.col + 1);
			q.push(QItem(p.row, p.col + 1, id, p.dist + 1));
			parent[id] = p.id;
			visited[p.row][p.col + 1] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[p.row][p.col + 1] != 'G')
					grid[p.row][p.col + 1] = '*';
				show_map(grid);
			}
		}

		// moving left 
		if (p.col - 1 >= 0 &&
			visited[p.row][p.col - 1] == false) {
			int id = p.row + ROW_SIZE * (p.col - 1);
			q.push(QItem(p.row, p.col - 1, id, p.dist + 1));
			parent[id] = p.id;
			visited[p.row][p.col - 1] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[p.row][p.col - 1] != 'G')
					grid[p.row][p.col - 1] = '*';
				show_map(grid);
			}
		}

		// moving down 
		if (p.row + 1 < ROW_SIZE &&
			visited[p.row + 1][p.col] == false) { 
			int id = (p.row + 1) + ROW_SIZE * p.col;
			q.push(QItem(p.row + 1, p.col, id, p.dist + 1));
			parent[id] = p.id;
			visited[p.row + 1][p.col] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[p.row + 1][p.col] != 'G')
					grid[p.row + 1][p.col] = '*';
				show_map(grid);
			}
		}

		if (grid[p.row][p.col] == 'F') {
			grid[p.row][p.col] = 'E';

			show_map(grid);
		}

	}

	// In case this line is reached, then that means no route between start and goal. We mark that by min distance = -1
	return -1;
}


// main function  
int main()
{
	int start_node_id, goal_node_id;
	char input_map[ROW_SIZE][COL_SIZE];

	// copy grid map into input_map 
	memcpy(input_map, grid, sizeof(grid));

	// create parent array where parent[i][j] = parent of node [i][j]
	map<int, int> parent;
	initialize_parents(ROW_SIZE*COL_SIZE, parent);

	// explore the map to find shortest path using BFS
	int min_dist = BFS(input_map, parent, start_node_id, goal_node_id);
	
	// if min_dist > 0, then the goal is reachable from the start node 
	if (min_dist > 0){
		// show the route from start to goal
		std::cout << "min distance in hops to goal is " << min_dist << endl;

		std::cout << "shortest Path: G <- ";
		int parent_node = parent[goal_node_id];

		int row_current = goal_node_id % ROW_SIZE;
		int col_current = (goal_node_id - row_current) / ROW_SIZE;

		int row_parent, col_parent;

		while (parent_node != start_node_id) {

			std::cout << parent_node << " <- ";

			row_parent = parent_node % ROW_SIZE;
			col_parent = (parent_node - row_parent) / ROW_SIZE;

			if (row_parent - row_current == -1) {
				input_map[row_parent][col_parent] = 'v';
			}
			else if (row_parent - row_current == 1) {
				input_map[row_parent][col_parent] = '^';
			}
			else if (col_parent - col_current == -1) {
				input_map[row_parent][col_parent] = '>';
			}
			else if (col_parent - col_current == 1) {
				input_map[row_parent][col_parent] = '<';
			}

			parent_node = parent[parent_node];
			row_current = row_parent;
			col_current = col_parent;
		}
		std::cout << "S" << endl;

		// show map with marked shortest route 
		show_map(input_map);
	}
	else
		cout << "No Route from S to G" << endl;

	return 0;
}