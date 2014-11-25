typedef struct n{
  int data;
  struct n *next;
} Node;

void print_list(Node *head);

Node * insert_front(Node *head, int data);

Node * free_list(Node *head);
