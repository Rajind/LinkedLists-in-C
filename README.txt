Implementations of a linked list as a:
a) Serial program
b) Parallel program (based on Pthreads) with one mutex for the entire linked list
c) Parallel program (based on Pthreads) with read-write locks for the entire linked list

How to compile and run the programs: 

*linked_list.c

gcc -o linked_list linked_list.c
./linked_list

*linked_list_one_mutex.c

gcc -g -Wall -o linked_list_one_mutex linked_list_one_mutex.c -lpthread
./linked_list_one_mutex parameter_1

*linked_list_one_rwlock.c

gcc -g -Wall -o linked_list_one_rwlock linked_list_one_rwlock.c -lpthread
./linked_list_one_rwlock parameter_1

---------------------------------------------------
parameter_1 : is the number of threads

For each case:
	float mMember = x;	//Fraction of Member 

	float mInsert = y;	//Fraction of Insert

	float mDelete = z;	//Fraction of Delete

x,y,z valuse must be set in the code. 
For example, for case 1 the values are like this.
	
	float mMember = 0.99;	//Fraction of Member 

	float mInsert = 0.005;	//Fraction of Insert

	float mDelete = 0.005;	//Fraction of Delete
----------------------------------------------------

[https://notebookbft.wordpress.com/2015/08/25/linked-list-with-read-write-locks-for-the-entire-linked-list/](https://notebookbft.wordpress.com/2015/08/25/linked-list-with-read-write-locks-for-the-entire-linked-list/)
[https://notebookbft.wordpress.com/2015/08/24/linkedlists-in-c/](https://notebookbft.wordpress.com/2015/08/24/linkedlists-in-c/)
