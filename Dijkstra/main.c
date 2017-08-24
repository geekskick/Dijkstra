//
//  main.c
//  Dijkstra
//  Resources:
//  http://www.sanfoundry.com/cpp-program-find-shortest-path-between-two-vertices-using-dijkstras-algorithm/
//  http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/**
 The maximum number of neighbours a graph node can have
 */
static const unsigned int		MAX_NEIGHBOURS = 10;

/**
 The column of the output in which the info starts
 */
static const unsigned int		INFO_COL = 60;

typedef struct graph_route_t	graph_route_t;
typedef struct graph_node_t		graph_node_t;
typedef struct queue_node_t		queue_node_t;

/**
 A node in the queue
 */
struct queue_node_t{
	queue_node_t				*next;
	graph_node_t				*node;
};

/**
 A monodirectional joing between two nodes in the graph
 */
struct graph_route_t{
	graph_node_t				*end;
	unsigned int				distance;
};

/**
 A node in the graph
 */
struct graph_node_t{
	graph_route_t				neighbours[MAX_NEIGHBOURS];
	unsigned int				num_neighbours;
	unsigned int				shortest_distance_to_me;
	int							id;
};


//------- Queue functionality ------

/**
 Pop the item from the front of the Queue. Updates the *front to be the new front.

 @param front Pointer to the first queue_node of the queue - updated to be the new front once node removed
 @return Address of the popped node.
 */
queue_node_t*	queue_pop_front		(queue_node_t **front);

/**
 Free a node.

 @param v Mode to free.
 */
void			queue_node_free		(queue_node_t *v	);

/**
 Pop the item in the queue with the shortest distance to it. Will pop the first node if all are of equal distance.

 @param front Pointer to the front of the queue.
 @return The popped node address. NULL if no nodes in the queue.
 */
queue_node_t*	queue_pop_min		(queue_node_t **front);

/**
 Frees the entire Queue

 @param front Pointer to the first node in the queue
 */
void			queue_free			(queue_node_t ** front);

/**
 Dynamically creates a queue node

 @param node Address of the graph node to put in the queue_node
 @return Pointer to HEAP containing the new queue node
 */
queue_node_t*   queue_create_node	(graph_node_t *const node);

/**
 Gets the number of items in the queue

 @param node The address of the first item in the queue
 @return The length of the queue
 */
unsigned int	queue_num_contents	(queue_node_t *const *const node);

/**
 Test if the queue already contains a graph node.

 @param front The address of the front of the queue
 @param node The address of the node to try and find
 @return True if the queue contains it already. Else false.
 */
bool			queue_contains_node	(queue_node_t *const *const front, graph_node_t *const node);

/**
 Test if the queue is empty

 @param front Address of the front of the queue
 @return True if there are no items in the queue.
 */
bool			queue_is_empty		(queue_node_t *const *const front);

/**
 Display the Queue contents in the INFO section of output

 @param front The Address of the first queue node.
 */
void			queue_print			(queue_node_t *const *const front);

/**
 Pop the first item from the queue and update the front

 @param front The address of the first item in the queue
 @return The address of the popped item
 */
queue_node_t*	queue_pop_front		(queue_node_t **const front);

/**
 Push to the back of the queue

 @param front The address of the front of the queue
 @param to_add The graph node to add to the back of the queue
 */
void			queue_push_back		(queue_node_t **const front, graph_node_t *const to_add);

//------- Graph functionality ------

/**
 Create a graph node on the stack. This is effectively a vertex

 @param id The id of the new node.
 @return The new node
 */
graph_node_t	graph_create_node		(const unsigned int id);

/**
 Adds the neighbour to the node.

 @param from The source of the route
 @param to The end point of the route
 @param dist The length of the route
 */
void			graph_add_neighbour		(graph_node_t *const from, graph_node_t *const to, const unsigned int dist);

/**
 Display the graph in the INFO section of the output

 @param nodes The address of the graph array
 @param num_nodes The number of items in the graph.
 */
void			graph_print				(graph_node_t *const *const nodes, const unsigned int num_nodes);

/**
 Performs the Dijkstra Algorithm to find the shortest distance from A to B

 @param nodes The address of the graph array
 @param num_nodes The number of nodes in the graph
 @param src The source city index
 @param dest the destination city array
 @return The shortest distance, of UINT_MAX if no route found.
 */
unsigned int	graph_get_shortest_path	(graph_node_t *const *const nodes, const int num_nodes, const int src, const int dest);

//------- MAIN ------
int				main					(int argc, const char * argv[]) {
	graph_node_t city	= graph_create_node(1);
	graph_node_t second = graph_create_node(2);
	graph_node_t third	= graph_create_node(3);
	graph_node_t fourth = graph_create_node(4);
	graph_node_t fifth	= graph_create_node(5);
	graph_node_t sixth	= graph_create_node(6);
	
	printf("%*. [INFO] %d is at %p\n", INFO_COL, city.id,	&city  );
	printf("%*. [INFO] %d is at %p\n", INFO_COL, second.id, &second);
	printf("%*. [INFO] %d is at %p\n", INFO_COL, third.id,	&third );
	printf("%*. [INFO] %d is at %p\n", INFO_COL, fourth.id, &fourth);
	printf("%*. [INFO] %d is at %p\n", INFO_COL, fifth.id,	&fifth );
	printf("%*. [INFO] %d is at %p\n", INFO_COL, sixth.id,	&sixth );
	
	graph_add_neighbour(&city,	 &third,  10);
	graph_add_neighbour(&city,	 &second, 7 );
	graph_add_neighbour(&second, &third,  2 );
	graph_add_neighbour(&second, &fifth,  6 );
	graph_add_neighbour(&third,  &fourth, 15);
	graph_add_neighbour(&fifth,  &sixth,  9 );
	graph_add_neighbour(&fifth,  &fourth, 2 );
	graph_add_neighbour(&fourth, &sixth,  1 );
	
	// add a loopback
	graph_add_neighbour(&sixth, &fourth, 1);
	
	// add a wrap around
	graph_add_neighbour(&sixth, &city, 40);
	
	// the graph itself
	graph_node_t *nodes[] = { &city, &second, &third, &fourth, &fifth, &sixth };
	
	graph_print(nodes, sizeof(nodes)/sizeof(nodes[0]));
	
	int src, dst;
	printf("Enter a source and then a destination in the range 1 to %lu\nsource >\t", sizeof(nodes)/sizeof(nodes[0]));
	scanf("%d", &src);
	printf("dest >\t");
	scanf("%d", &dst);
	
	const unsigned int dist = graph_get_shortest_path(nodes, sizeof(nodes)/sizeof(nodes[0]), src-1, dst-1);
	
	if(dist == UINT_MAX) {
		printf("Path from %d to %d is IMPOSSIBLE\n",nodes[src-1]->id, nodes[dst-1]->id );
	}
	else{
		printf("The shortest distance from %d to %d is %u\n",nodes[src-1]->id, nodes[dst-1]->id, dist);
	}
	
	return 0;
}

//--------------------
void			queue_node_free			(queue_node_t*v){
	printf("%*. [INFO] Freeing memory at %p\n",INFO_COL, v); free(v); v = NULL;
}

//--------------------
queue_node_t*	queue_pop_min			(queue_node_t** front){
	if(*front == NULL) {
		return NULL;
	}
	queue_node_t* previous = NULL;
	queue_node_t* min = *front;
	queue_node_t* temp = *front;
	
	// only one item so return pointer to it
	if(temp->next == NULL){ *front = NULL; return min; }
	
	while(temp->next){
		if(temp->next->node->shortest_distance_to_me < min->node->shortest_distance_to_me){
			previous = temp;
			min = temp->next;
		}
		temp = temp->next;
	}
	
	// if previous is NULL then the first item is the shortest
	if(!previous){
		return queue_pop_front(front);
	}
	
	//pop
	previous->next = min->next;
	return min;
}

//--------------------
queue_node_t*	queue_create_node		(graph_node_t * const n){
	queue_node_t * temp = calloc(sizeof(queue_node_t), 1);
	printf("%*. [INFO] All'ing memory at %p\n", INFO_COL, temp);
	temp->next = NULL;
	temp->node = n;
	return temp;
}

//--------------------
unsigned int	queue_num_contents		(queue_node_t* const *const node){
	unsigned int count = 0;
	queue_node_t *temp = *node;
	while(temp){ count++; temp = temp->next; }
	return count;
}

//--------------------
bool			queue_contains_node		(queue_node_t *const *const front, graph_node_t * const node){
	queue_node_t*temp = *front;
	while(temp != NULL) {
		if(temp->node == node){
			return true;
		}
		temp = temp->next;
	}
	return false;
}

//--------------------
bool			queue_is_empty			(queue_node_t *const *const front){
	return *front == NULL;
}

//--------------------
void			queue_print				(queue_node_t *const *const front){
	printf("%*. [INFO] The queue at %p is:\n", INFO_COL,*front);
	int count = 0;
	queue_node_t *temp = *front;
	while(temp){ printf("%*. [INFO]\t\tQueue[%i].node->id = %-*d\n",INFO_COL, count++, 4, temp->node->id); temp = temp->next; }
}

//--------------------
void			queue_free				(queue_node_t ** front){
	if(*front == NULL){  return; }
	queue_free(&(*front)->next);
	queue_node_free(*front);
}

//--------------------
void			queue_push_back			(queue_node_t **const front, graph_node_t *const to_add){
	queue_node_t* temp = *front;
	// if the first item
	printf("%*. [INFO] Pushing %p to the queue at %p\n", INFO_COL,to_add, *front);
	
	if(temp == NULL) { *front = queue_create_node(to_add); return; }
	
	//find last item
	while(temp->next != NULL) { temp = temp->next; }
	
	//allocate
	temp->next = queue_create_node(to_add);
}

//--------------------
queue_node_t*	queue_pop_front			(queue_node_t **const front){
	printf("%*. [INFO] Popping %p from queue at %p\t", INFO_COL,(*front)->node, *front);
	if(queue_is_empty(front)){ printf(" Queue already empty\n"); return NULL; }
	printf("\n");
	queue_node_t* to_free = *front;
	*front = (*front)->next;
	return to_free;
}

//--------------------
graph_node_t	graph_create_node		(const unsigned int id){
	graph_node_t n;
	n.id = id;
	n.num_neighbours = 0;
	n.shortest_distance_to_me= UINT_MAX;
	return n;
}

//--------------------
void			graph_add_neighbour		(graph_node_t * const from, graph_node_t * const to, const unsigned int dist){
	graph_route_t new_route = { to, dist };
	from->neighbours[(from->num_neighbours)++] = new_route;
}

//--------------------
void			graph_print				(graph_node_t * const * const nodes, const unsigned int num_nodes){
	printf("%*. [INFO] There are %u nodes\n", INFO_COL,num_nodes);
	for(int i = 0; i < num_nodes; i++){
		printf("%*. [INFO]\tShortest [%u]\t%d is at %p\n", INFO_COL,nodes[i]->shortest_distance_to_me, nodes[i]->id, nodes[i]);
		for(int n = 0; n < nodes[i]->num_neighbours; n++){
			printf("%*. [INFO]\t\t%d to %d has weight %d\n",INFO_COL,nodes[i]->id,nodes[i]->neighbours[n].end->id, nodes[i]->neighbours[n].distance);
		}
	}
}

//--------------------
unsigned int	graph_get_shortest_path	(graph_node_t * const * const nodes, const int num_nodes, const int src, const int dest){
	
	// The source has to have the shortest distance marked as 0 before starting
	nodes[src]->shortest_distance_to_me = 0;
	queue_node_t * not_visited = NULL;
	
	// No nodes have been visited at this point so add them all the the queue
	for(int i = 0; i < num_nodes; i++){
		queue_push_back(&not_visited, nodes[i]);
	}
	
	queue_print(&not_visited);
	
	while(!queue_is_empty(&not_visited)){
		
		// Get the item in the not visited collection which has the shortest distance to it.
		// The first time through this will be the source node.
		printf("%*. [INFO] Not visited graph nodes:\n", INFO_COL);
		queue_print(&not_visited);
		queue_node_t* current = queue_pop_min(&not_visited);
		printf("%*. [INFO] Not visited graph nodes after minimum removed:\n", INFO_COL);
		queue_print(&not_visited);
		
		graph_node_t* current_graph = current->node;
		queue_node_free(current);
		
		// Calculate the distance to the neighbours
		printf("%*. [INFO] Calculating distances from %d to it's neighbours\n", INFO_COL,current->node->id);
		for(int n = 0; n < current_graph->num_neighbours;n++){
			const unsigned int distance_to_neighbour = current_graph->shortest_distance_to_me + current_graph->neighbours[n].distance;
			printf("%*. [INFO] \t %d to %d is %u", INFO_COL,current->node->id,current_graph->neighbours[n].end->id, distance_to_neighbour );
			
			//update if it's shorter than currently
			if(distance_to_neighbour < current_graph->neighbours[n].end->shortest_distance_to_me){
				printf(" NEW SHORTEST! ");
				current_graph->neighbours[n].end->shortest_distance_to_me = distance_to_neighbour;
			}
			printf("\n");
			
		}
		
	}
	
	// queue should be empty but just in case try to free it
	queue_free(&not_visited);
	return nodes[dest]->shortest_distance_to_me;
}

