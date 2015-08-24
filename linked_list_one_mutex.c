#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

//Maximum key value
const int MAX_KEY = 65536;

//Maximum thread count
const int MAX_THREADS = 1024;

struct node {
   int    val;
   struct node* next;
};

// Shared variables
struct      node* head = NULL;  

int n = 1000;	//Initial population element count
int m = 10000;	//Total random operations count

//These values must be changed according to each case
float mMember = 0.50;	//Fraction of Member 
float mInsert = 0.25;	//Fraction of Insert
float mDelete = 0.25;	//Fraction of Delete

int thread_count = 1;	//Thread Count

double start_time, finish_time, time_elapsed;

int member_count=0;	//Member function call count
int insert_count=0;	//Insert function call count
int delete_count=0;	//Delete function call count

pthread_mutex_t mutex;
pthread_mutex_t count_mutex;

int Member(int value);
int Insert(int value);
int Delete(int value);
void Clear_Memory(void);
int Is_Empty(void);

void* Thread_Function(void* rank);

int main(int argc, char* argv[]) {

	if (argc != 2){ 
		fprintf(stderr, "please provide a command line argument for thread count less than %d\n", MAX_THREADS);
   		exit(0);
	}

	thread_count = strtol(argv[1], NULL, 10);  
   	if (thread_count <= 0 || thread_count > MAX_THREADS){ 
		fprintf(stderr, "please provide a command line argument for thread count less than %d\n", MAX_THREADS);
   		exit(0);
	}
	
	int i=0;
	//Inserting elements to linked-list
    for(;i<n;i++){   
        int r = rand()%65536;
        if(!Insert(r)){
            i--;
        }
    }
 
	pthread_t* thread_handles;

	thread_handles = malloc(thread_count*sizeof(pthread_t));
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&count_mutex, NULL);

	start_time = clock();
	for (i = 0; i < thread_count; i++)
		pthread_create(&thread_handles[i], NULL, Thread_Function, (void*) i);

	for (i = 0; i < thread_count; i++)
		pthread_join(thread_handles[i], NULL);
   
	finish_time = clock();
	time_elapsed = (finish_time - start_time)/CLOCKS_PER_SEC;
    //printf("Time Elapsed  = %.10f seconds\n", time_elapsed);
	printf("%.10f\n", time_elapsed);
    
	Clear_Memory();
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&count_mutex);
	free(thread_handles);
	return 0;
}

//Member Function
int  Member(int value) {
   struct node* temp;

   temp = head;
   while (temp != NULL && temp->val < value)
      temp = temp->next;

   if (temp == NULL || temp->val > value) {
	  //printf("%d is a member in linked-list\n", value);	
      return 0;
   } else {
      //printf("%d is a member in linked-list\n", value);
      return 1;
   }
}

// Insert function
int Insert(int value) {
   struct node* current = head;
   struct node* previous = NULL;
   struct node* temp;
   int return_value = 1;
   
   while (current != NULL && current->val < value) {
      previous = current;
      current = current->next;
   }

   if (current == NULL || current->val > value) {
	  temp = malloc(sizeof(struct node));
      temp->val = value;
      temp->next = current;
      if (previous == NULL)
         head = temp;
      else
         previous->next = temp;
   } else {
      return_value = 0;
   }

   return return_value;
}

//Delete Function
int Delete(int value) {
   struct node* current = head;
   struct node* previous = NULL;
   int return_value = 1;

   while (current != NULL && current->val < value) {
      previous = current;
      current = current->next;
   }
   
   if (current != NULL && current->val == value) {
      if (previous == NULL) {
         head = current->next;
         free(current);
      } else { 
         previous->next = current->next;
         free(current);
      }
   } else {
      return_value = 0;
	  //printf("%d is not in the linked-list\n", value);
   }
   return return_value;
}

//Function to free memory used for linked-list
void Clear_Memory(void) {
   struct node* current;
   struct node* next;

   if (Is_Empty()) return;
   current = head; 
   next = current->next;
   while (next != NULL) {
      free(current);
      current = next;
      next = current->next;
   }
   free(current);
}

//Function to check if linked-list is empty
int  Is_Empty(void) {
   if (head == NULL)
      return 1;
   else
      return 0;
}

void* Thread_Function(void* rank) {
	int i, val;
	
	int my_member=0;
	int my_insert=0;
	int my_delete=0;
	
	int ops_per_thread = m/thread_count;

	for (i = 0; i < ops_per_thread; i++) {
		float operation_choice = (rand()%10000/10000.0);
		val = rand()%MAX_KEY;
	  
		if (operation_choice < mMember) {
			pthread_mutex_lock(&mutex);
			Member(val);
			pthread_mutex_unlock(&mutex);
			my_member++;
		} else if (operation_choice < mMember + mInsert) {
			pthread_mutex_lock(&mutex);
			Insert(val);
			pthread_mutex_unlock(&mutex);
			my_insert++;
		} else {
			pthread_mutex_lock(&mutex);
			Delete(val);
			pthread_mutex_unlock(&mutex);
			my_delete++;
		}
	}

	pthread_mutex_lock(&count_mutex);
	member_count += my_member;
	insert_count += my_insert;
	delete_count += my_delete;
	pthread_mutex_unlock(&count_mutex);
	return NULL;
}

