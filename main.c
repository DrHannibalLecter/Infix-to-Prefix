#include <stdio.h>
#include <stdlib.h>

char st[] = "A+B-C*D*E*F";
int f = -1;

struct Node{
    char key;
    struct Node* next;
};
typedef struct Node Node;

Node* temp;

// The queue, front stores the front node of LL and rear stores the last node of LL
struct Queue {
    Node* front;
    Node* rear;
};
typedef struct Queue Queue;



// A utility function to create a new linked list node.
Node* newNode(char ch)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = ch;
    temp->next = NULL;
    return temp;
}

// A utility function to create an empty queue
Queue* createQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// The function to add a char ch to q
void enQueue(Queue* q, char ch)
{
    if(!ch){
        return;
    }
    // Create a new LL node
    Node* temp = newNode(ch);

    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}

// Function to remove a key from given queue q
void deQueue(Queue* q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return;

    // Store previous front and move front one node ahead
    Node* temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

char getChar(FILE** input){
    char ch;
    ch = fgetc(*input);
    if(!(ch == EOF || ch == '\n' || ch == ' ')){
        return ch;
    }
    return 0;
    //f++;
    //return st[f];
}

void push(char ch, Node** stack, Node** last){
    if(!ch){
        return;
    }
    temp=newNode(ch);
    temp->next=*stack;
    *stack=temp;
    if(!(temp->next)){
        *last=temp;
    }
}


char toPre(Queue* q, Node** stack, Node** stacklast, char bool, char* prv, int prvoperand, FILE** input){
    char ch = getChar(input);
    if(!ch){
        return 0;
    }
    if(isOperator(ch)){
        int a = precedence(ch);
        if(prvoperand < a){
            char tp = 0;
            Queue* qtp = createQueue();
            Node* stacktp = NULL;
            Node* stacklasttp = NULL;
            push(ch, &stacktp, &stacklasttp);
            enQueue(qtp, *prv);
            *prv=0;
            toPre(qtp, &stacktp, &stacklasttp, bool, &tp, a, input);
            toPre(qtp, &stacktp, &stacklasttp, bool, &tp, a, input);
            stacklasttp->next = qtp->front;
            q->rear->next=stacktp;
            q->rear=qtp->rear;
            return 1;
        }
        else if(prvoperand == a){
            enQueue(q, *prv);
            *prv=0;
            push(ch,stack, stacklast);
            toPre(q, stack, stacklast, bool, prv, prvoperand, input);
            toPre(q, stack, stacklast, bool, prv, prvoperand, input);
            return 1;
        }
        else{
            enQueue(q, *prv);
            *prv=ch;
            (*stacklast)->next = q->front;
            return 1;
        }
    }
    else if(isOperand(ch)){
        enQueue(q, *prv);
        *prv = ch;
        return 1;
    }
    /*else if(ch=='('){

    }
    else if(bool && (ch==')')){
        return 1;
    }*/
    else{
        return 0;
    }
}


int main(int argc, char* argv[])
{
    FILE* input;
    if(argc>=2){
        input= fopen(argv[1], "r");
    }
    else{
        printf("ERROR");
        return -1;
    }

    printf("%c", getChar(&input));
    //Check if input is empty
    if (!(input)) {
        printf("input can't be opened \n");
    }

    Queue* q = createQueue();
    //head and last will be used for stack
    Node* head = NULL;
    Node* last = NULL;


    char prv = 0;
    char bool = 0;
    /*do{}while(toPre(q, &head, &last, bool, &prv, 1, &input));

    enQueue(q, prv);
    last->next=q->front;

    while(head->next){
        printf("%c", head->key);
        head=head->next;
    }
    printf("%c", head->key);*/
}