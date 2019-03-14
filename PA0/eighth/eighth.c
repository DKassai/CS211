#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node  *left;;
    struct node  *right;
};

struct node *insert(struct node *head, int data);
void search(struct node * head, int data, int level);
void freeTree(struct node * curr);

int main(int args, char** argv){
   
    // check to confirm correct inputs
    if (args != 2){
        printf("error\n");
        return 0;
    }

    //open file location
    FILE *fp;
    fp = fopen(argv[1],"r");
    
    // check to make sure file exists
    if (fp == NULL || fp == 0){
        printf("error\n");
        return 0;
    }


    int num = 0 ;
    char c;
    struct node *head;
    head =NULL;
    while( fscanf(fp,"%c\t%d\n",&c,&num) != EOF){
        //printf("%c\t%d\n",c,num);

        // check for correct input
        if (!(c == 'i' || c =='s')){
            printf("error");
        }else if ( c == 'i'){
            head = insert(head, num);
        
        }else{
            search(head,num,1);
        
        }
        

    }// end of while



    freeTree(head);
    return 0;
}// end of main int


void freeTree(struct node * curr){
       if (curr != NULL) {
        freeTree(curr->left);
        freeTree(curr->right);

        free(curr);
     }
}

struct node *insert(struct node *head, int data){
    // create the new node and set both left and right to NULL
    struct node *new_node = malloc(sizeof(struct node));
    new_node-> left = NULL;
    new_node-> right = NULL;
    new_node-> data = data;
    
    // check to see if head is null 
    if (head  == NULL){
        printf("inserted 1\n");
        return new_node;
    }

    // create pointer to transverse tree
    struct node *p = head;
    
    // keep track of the height of the tree
    int sum = 1; 
    
    // find where to insert new node
    while (p != NULL){
        //check to see if currect node has the same data 
        if (p->data == data){
            printf("duplicate\n");
            free(new_node);
            return head;
        }
        // if the number insterting is smaller then the currect node check left
        if (p->data > data){
            // if the left node is NULL insert new node there
            if (p->left == NULL){
                p->left = new_node;
                sum++;
                printf("inserted %d\n",sum);
                sum = 0;
                return head; 
            }else{
                // move to the next node
                sum++;
                p = p->left;
            }
            // else that means the node inserting is bigger then current node so go left
        }else{
             // if the right node is NULL insert new node there
             
            if (p->right == NULL){
                p->right = new_node;
                sum++;
                printf("inserted %d\n", sum);
                sum = 0;
                return head; 
            }else{
                // move to the next node
                sum++;
                p = p->right;
            }
        }
    }// end of while loop 
}// end of struct 


void search(struct node * head, int data,int level){
    struct node *p = head;
    if (p == NULL){
        printf("absent\n");
    }else if (p->data == data){
        printf("present %d\n", level);
    }else if(p->data > data){
        level++;
        search(p->left, data, level);
    }else{
        level++;
        search(p->right,data,level);
    }
}

