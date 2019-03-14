#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node  *left;;
    struct node  *right;
};

struct node *insert(struct node *head, int data);
void search(struct node * head, int data, int level);
struct node *delete(struct node *head, int key);
int findmin(struct node* head);
struct node *delete_one_node(struct node *head, int key);
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
        if (!(c == 'i' || c =='s' || c == 'd')){
            printf("error");
        }else if ( c == 'i'){
            head = insert(head, num);
        
        }else if (c =='s'){
            search(head,num,1);
        
        }else{
            head = delete(head,num);
        
        }
        

    }// end of while



    freeTree(head);
    return 0;
}// end of main int



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

int findmin(struct node* head){
    struct node* p = head;
 
    while (p->left != NULL)
        p = p->left;
 
    return p->data;;
}

struct node *delete(struct node *head, int key){
    // base case
    if (head == NULL){
        printf("fail\n");
        return head;
    }
    // check to see which way to transverse the tree. 
    if (head->data > key){
        head->left = delete(head->left,key);
    } else if (head->data < key){
        head->right = delete(head->right,key);
    }else{
        
        // found a key
        printf("success\n");
        // check if no children 
        if (head->left == NULL && head->right == NULL){
            return NULL;
         // one child
        }else if(head->left == NULL){
            struct node *t = head->right;
            return t;
        
        }// one child
        else if(head->right == NULL){
            struct node *t = head->left;
            return t;
        }
        
        // 2 children 
        // get min value key 
        int x = 0;
        // go down the right side 
        x = findmin(head->right);
        
        // change value in head
        head->data = x;
        
        // go down and find the value to delete. 
        head->right = delete_one_node(head->right,head->data);
        

    }// end of else
    return head;
}// end of function 

struct node *delete_one_node(struct node *head, int key){
    // base case
    if (head == NULL){
        return head;
    }
    // check to see which way to transverse the tree. 
    if (head->data > key){
        head->left = delete_one_node(head->left,key);
    } else if (head->data < key){
        head->right = delete_one_node(head->right,key);
    }else{
        // found a key
        
        // check if no children 
        if (head->left == NULL && head->right == NULL){
            return NULL;
         // one child
        }else if(head->left == NULL){
            struct node *t = head->right;
            return t;
        
        }// one child
        else if(head->right == NULL){
            struct node *t = head->left;
            return t;
        }
     }
        return head;

}
void freeTree(struct node * curr){
       if (curr != NULL) {
        freeTree(curr->left);
        freeTree(curr->right);

        free(curr);
     }
}






