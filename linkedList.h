#define PASSONBUS 0
#define IDLEPASS 1
#define ALLDEST 2
#define TARGETLIST 3





// Define the structure for the node in the linked list
typedef struct cell
{
    int coordinates[2];
    int cellData[4];
    //one-hot encoded array where 0 is false, and 1 is true.
    //[0]: 1 if open, 0 if not.
    //[1]: 1 if construction, 0 if not.
    //[2]: 1 if passenger, 0 if not.
    //[3]: 1 if destination, 0 if not.
    struct cell* passenger;
    struct cell* destination;
    struct cell* parent;
    int f_cost;
    int g_cost;
    int h_cost;
} Cell;

typedef struct Node {
    Cell* cell;
    struct Node* next;
    int key;
} Node;

// Define the structure for the linked list itself
typedef struct LinkedList {
    Node* head;
    int count;
} LinkedList;

// Function prototypes
LinkedList* createLinkedList();
void addNode(LinkedList* list, Cell* data);
int deleteNode(LinkedList* list, Node* data);
Node* findNode(LinkedList* list, Cell* cell);
void displayList(LinkedList* list);
void destroyList(LinkedList* list);

