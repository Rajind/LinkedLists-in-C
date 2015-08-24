#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct node {
   int    val;
   struct node* next;
};

int  Member(int value, struct node* head);
int  Insert(int value, struct node** head);
int  Delete(int value, struct node** head);
int  Is_Empty(struct node* head);
void Clear_Memory(struct node** head);

int n = 1000;	//Initial population element count
int m = 10000;	//Total random operations count

//These values must be changed according to each case
float mMember = 0.50;	//Fraction of Member 
float mInsert = 0.25;	//Fraction of Insert
float mDelete = 0.25;	//Fraction of Delete

float operation_choice;	
double start_time, finish_time, time_elapsed;

int main(void) {
	int j=0;
	for(j=0; j < 250; j ++){
	struct node* head = NULL;  
   	int i=0;

	//Inserting elements to linked-list
    for(;i<n;i++){   
        int r = rand()%65536;
        if(!Insert(r,&head)){
            i--;
        }
    }
   
    int member_count=0;	//Member function call count
    int insert_count=0;	//Insert function call count
    int delete_count=0;	//Delete function call count
         
    start_time = clock();    
    for(i=0;i<m;i++){
        operation_choice = (rand()%10000/10000.0); 
        int r = rand()%65536;
        if(operation_choice < mMember){
            Member(r,head);
            member_count++;
        }else if(operation_choice < mMember + mInsert ){
            Insert(r,&head);
            insert_count++;
        }else{           
            Delete(r,&head);
            delete_count++;
        }
    }
    finish_time = clock();
    time_elapsed = (finish_time - start_time)/CLOCKS_PER_SEC;
	//printf("Time Elapsed  = %.10f seconds\n", time_elapsed);	
    printf("%.10f\n", time_elapsed);
     
	Clear_Memory(&head);
	}
	
	
	return 0;
}        
 
 //Member Function
int  Member(int value, struct node* head) {
	struct node* current;

	current = head;
	while(current != NULL && current->val < value)
		current = current->next;

	if(current == NULL || current->val > value) {
		//printf("%d is a member in linked-list\n", value);
		return 0;
	} else {
		//printf("%d is not a member in linked-list\n", value);
		return 1;
	}
}

// Insert function
int Insert(int value, struct node** headp) {
	struct node* current = *headp;
	struct node* previous = NULL;
	struct node* temp;
   
	while(current != NULL && current->val < value) {
		previous = current;
		current = current->next;
	}

	if(current == NULL || current->val > value) {
		temp = malloc(sizeof(struct node));
		temp->val = value;
		temp->next = current;
		if(previous == NULL){
			*headp = temp;
		}else{
			previous->next = temp;
		}
		return 1;
	}else{ 
		//printf("%d is already in the linked-list\n", value);
		return 0;
	}
}

//Delete Function
int Delete(int value, struct node** headp) {
	struct node* current = *headp;
	struct node* previous = NULL;

	while(current != NULL && current->val < value) {
		previous = current;
		current = current->next;
	}
   
	if (current != NULL && current->val == value) {
		if (previous == NULL){
			*headp = current->next;
			free(current);
		}else{ 
			previous->next = current->next;
			free(current);
		}
		return 1;
	}else{
		//printf("%d is not in the linked-list\n", value);
		return 0;
	}
}

//Function to free memory used for linked-list
void Clear_Memory(struct node** headp) {
	struct node* current;
	struct node* next;

	if (Is_Empty(*headp)) return;
	current = *headp; 
	next = current->next;
	while(next != NULL) {
		free(current);
		current = next;
		next = current->next;
	}
	free(current);
	*headp = NULL;
}

//Function to check if linked-list is empty
int  Is_Empty(struct node* head) {
	if (head == NULL){
      return 1;
	}else{
      return 0;
	}
}
