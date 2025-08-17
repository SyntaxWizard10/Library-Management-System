#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//LINKED LIST (Book List)
typedef struct book
{
    int id;
    char title[50];
    struct book *next;
} book;
book*head=NULL; 
void add(int id, char title[])
{
    book*newbook = (book*)malloc(sizeof(book));
    newbook->id = id;
    strcpy (newbook->title, title);
    newbook->next = head;
    head = newbook;
    printf ("Book added:%d-%s\n", id, title);
}
void displaybooks()
{
    book *temp=head;
    if(!temp)
    {
        printf ("No books in library.\n");
        return;
    }
    printf ("\nLibrary Books:\n");
    while(temp)
    {
        printf ("ID:%d,Title:%s\n", temp->id, temp->title);
        temp=temp->next;
    }
}
//Queue (Borrowers)
typedef struct dequeue
{
    char name[50];
    struct dequeue *next;
} dequeue;
dequeue *front = NULL, *rear = NULL;
void enqueue(char name[])
{
    dequeue*newnode =(dequeue*)malloc(sizeof(dequeue));
    strcpy (newnode->name, name);
    newnode->next = NULL;
    if (!rear)
        front=rear=newnode;
    else
    {
        rear->next = newnode;
        rear = newnode;
    }
    printf ("Borrower added:%s\n", name);
}
void displayqueue()
{
    dequeue*temp = front;
    if(!temp)
    {
        printf ("No borrower\n");
        return;
    }
    printf ("\nBorrower:\n");
    while(temp)
    {
        printf ("%s\n", temp->name);
        temp=temp->next;
    }
}
//Stack(Returned Books)
typedef struct node
{
    char title[50];
    struct node *next;
} node;
node *top = NULL;
void push(char title[])
{
    node*newnode =(node*)malloc(sizeof(node));
    strcpy (newnode->title, title);
    newnode->next = top;
    top = newnode;
    printf ("Book returned: %s\n", title);
}
void displaystack()
{
    node *temp = top;
    if(!temp)
    {
        printf ("No returned books.\n");
        return;
    }
    printf ("\nRecently Returned Books:\n");
    while(temp)
    {
        printf ("%s\n", temp->title);
        temp=temp->next;
    }
}
//Binary Search Tree(Book Search)
typedef struct bst
{
    int id;
    char title[50];
    struct bst *left, *right;
} bst;
bst *root = NULL;
bst *insert(bst *node, int id, char title[])
{
    if(!node)
    {
        bst *newnode = (bst *)malloc(sizeof(bst));
        newnode->id = id;
        strcpy (newnode->title, title);
        newnode->left = newnode->right = NULL;
        return newnode;
    }
    if(id<node->id)
        node->left = insert(node->left, id, title);
    else if(id > node->id)
        node->right = insert(node->right, id, title);
    return node;
}
void searchbook (bst *node, int id)
{
    if(!node)
    {
        printf ("Book not found.\n");
        return;
    }
    if(id==node->id)
    {
        printf ("Book Found: %d - %s\n", node->id, node->title);
        return;
    }
    if(id < node->id)
        searchbook (node->left, id);
    else
        searchbook (node->right, id);
}
int main()
{
    int choice, id;
    char title[50], name[50];
    while (1)
    {
        printf ("\n------Library Menu------\n");
        printf ("1. Add Book\n2. View Books\n3. Add Borrower\n4. View borrower\n");
        printf ("5. Return Book\n6. View Returned Books\n7. Search Book by ID\n8. Exit\n");
        printf ("Enter choice: ");
        scanf ("%d", &choice);
        getchar (); 
        switch(choice)
        {
        case 1:
            printf ("Enter Book ID: ");
            scanf ("%d", &id);
            getchar ();
            printf ("Enter Book Title: ");
            fgets (title, sizeof(title), stdin);
            title [strcspn(title, "\n")]=0;
            add(id, title);
            root = insert(root, id, title);
            break;
        case 2:
            displaybooks();
            break;
        case 3:
            printf ("Enter Borrower Name: ");
            fgets (name, sizeof(name), stdin);
            name [strcspn(name, "\n")] = 0;
            enqueue(name);
            break;
        case 4:
            displayqueue();
            break;
        case 5:
            printf ("Enter Returned Book Title: ");
            fgets (title, sizeof(title), stdin);
            title [strcspn(title, "\n")] = 0;
            push(title);
            break;
        case 6:
            displaystack();
            break;
        case 7:
            printf ("Enter Book ID to Search: ");
            scanf ("%d", &id);
            searchbook(root, id);
            break;
        case 8:
            exit(0);
        default:
            printf ("Invalid choice!\n");
        }
    }
    return 0;
}
