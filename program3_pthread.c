# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
// Thread function 1
void * thread_function1 (void * arg ) {
int thread_id = *(( int *) arg ) ;
printf (" Thread 1 started with ID: %d\n", thread_id ) ;
printf (" Thread 1: Performing task ...\n") ;
// Simulate some work
for(int i = 1; i <= 5; i ++) {
printf (" Thread 1: Step %d/5\n", i ) ;
sleep (1) ;
}
printf (" Thread 1: Task completed . Terminating ...\n") ;
pthread_exit ( NULL ) ;
}
// Thread function 2
void * thread_function2 ( void * arg ) {
int thread_id = *(( int *) arg ) ;
printf (" Thread 2 started with ID: %d\n", thread_id ) ;
printf (" Thread 2: Performing different task ...\n") ;
// Simulate some work
for(int i = 1; i <= 3; i ++) {
printf (" Thread 2: Processing item %d/3\n", i ) ;
sleep (2) ;
}
printf (" Thread 2: Processing completed . Terminating ...\n") ;
pthread_exit ( NULL ) ;
}
int main () {
pthread_t thread1 , thread2 ;
int thread_id1 = 1;
int thread_id2 = 2;
int result ;
printf (" Main thread PID : %d\n", getpid () ) ;
printf (" Creating threads ...\n\n") ;

// Create thread 1
result = pthread_create (& thread1 , NULL , thread_function1 , &
thread_id1 ) ;
if ( result != 0) {
printf (" Error creating thread 1\n") ;
exit (1) ;
}
// Create thread 2
result = pthread_create (& thread2 , NULL , thread_function2 , &
thread_id2 ) ;
if ( result != 0) {
printf (" Error creating thread 2\n") ;
exit (1) ;
}
printf (" Both threads created successfully \n") ;
printf (" Main thread waiting for threads to complete ...\n\n") ;
// Wait for both threads to complete
pthread_join ( thread1 , NULL ) ;
pthread_join ( thread2 , NULL ) ;
printf ("\nBoth threads have terminated \n") ;
printf (" Main thread terminating \n") ;
return 0;
}