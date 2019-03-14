#include <stdio.h>
#include <stdlib.h>



// create node struct
struct node {
    int data;
    struct node *next;
};

struct node *insert(struct node *head, int x);
struct node *delete(struct node *head, int x);
void printList(struct node *head);
void printNumberNodes(struct node *head);

int main(int args, char **argc){

    struct node *root = NULL;
    //root = insert(root,4);
    //root = insert(root,6);
    //root = insert(root,6);
    //root = insert(root,1);
    //root = insert(root,5);
    //printList(root);
    
    //printf("\n");
    //root = delete(root,1);
    //root = delete(root,7);
    //printList(root);
    
    //printf("\n");
    
    
    

    
    // check to confirm correct inputs
    if (args != 2){
        printf("error, to many inputs\n");
        return 0;
    }

    //open file location
    FILE *fp;
    fp = fopen(argc[1],"r");
    
    // check to make sure file exists
    if (fp == NULL || fp == 0){
        printf("error\n");
        return 0;
    }
    // start reading files
    // init varables to store information
    int num = 0 ;
    char c;
    // varable to check how many lines in file
    int lines =0;
    // go throught the file until no more lines to read
    while( fscanf(fp,"%c\t%d\n",&c,&num) != EOF){
        //printf("%c\t%d\n",c,num);
      
        if ('i' == c){  
            root = insert(root,num);
        }else{
            root = delete(root,num);
        }
        lines = lines + 1;
        
    }
    
    // check if there were any lines in file
    if (lines == 0){
        printf("0\n");
        printf("\n");
        return 0;
    }   
    
    // print number of nodes in the list
    printNumberNodes(root);
    // print list 
    printList(root);
    // print new line per instuctions 
    printf("\n");
    
    return 0;
    
}

struct node *insert(struct node *head, int x){
    // if head is null, meaning first insert
    if (head == NULL){
        // create new node 
        struct node *c =malloc(sizeof(struct node));
        c->next = NULL;
        c->data = x;
        head = c;
        return head;
    }else{
        // create node to transverse 
        struct node *current;
        current = head;
        struct node *ptr;
        ptr = head;
       
        // check if the item should be insterted in to the first link in the list 
        if (current->data > x){
            struct node *c = malloc(sizeof(struct node));
            c->data = x;
            c->next = head;
            head = c;
            return head;
        } 
        
        // transverse the list until you are at the last node but not null
        while (current != NULL){
            // if data is already in list exit out and do nothing
            if (current->data == x){
                return head;
            }
            // check to see if data in list is greater or less then insert data and move pointer
            // if currect data in list is greater then insert then instert num in to list
            if (current->data > x ){
                struct node *c = malloc(sizeof(struct node));
                c->data = x;
                ptr->next = c;
                c->next = current;
                return head;
            }else{
            ptr = current;
            current = current->next;
            }
        }// end of while loop 
        
        if (current == NULL){
            struct node *c = malloc(sizeof(struct node));
            c->data = x;
            c->next = NULL;
            ptr->next = c;
            return head;
        }  
    } // end of else 
} // end of function 

struct node *delete(struct node *head, int x){

    // check to see if its null first
    if( head == NULL){
        return head;
    
    }
    
    // check to see if node is the frist node
    if (head->data == x){
         head = head->next;
         return head;
    }
    
    struct node *current;
    current = head;
    struct node *ptr;
    ptr = head;
    
    // loop through all node look for node to delete
    while (current != NULL){
        if (current->data == x){
            ptr->next = current->next;
            return head;
        }else{
            ptr = current;
            current = current->next;
        }
    }// end of while loop 
    
    return head;



}// end of function

void printNumberNodes(struct node *head){
    struct node *current;
    current = head;
    int x = 0;
    while (current != NULL){
        x = x + 1;
        current = current->next;
    } 
    printf("%d\n",x);


}
void printList(struct node *head){
    struct node *current;
    current = head;
    while (current != NULL){
        printf("%d\t",current->data);
        current = current->next;
    } 

}

