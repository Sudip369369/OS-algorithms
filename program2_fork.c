# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
int main () {
pid_t pid ;
printf (" Before fork () - Current PID : %d\n", getpid () ) ;
pid = fork () ;
if ( pid == 0) {
// Child process
printf ("\n- - - CHILD PROCESS - - -\n") ;
printf (" Child Process PID : %d\n", getpid () ) ;
printf (" Child ’s Parent PID : %d\n", getppid () ) ;
printf (" fork () returned : %d\n", pid ) ;
}
else if ( pid > 0) {
// Parent process
printf ("\n- - - PARENT PROCESS - - -\n") ;
printf (" Parent Process PID : %d\n", getpid () ) ;
printf (" Child Process PID : %d\n", pid ) ;
printf (" fork () returned : %d\n", pid ) ;
// Wait for child to complete
wait ( NULL ) ;
printf (" Child process completed \n") ;
}
else {
// Fork failed
printf (" Fork failed !\n") ;
return 1;
}
printf (" Process %d terminating \n", getpid () ) ;
return 0;
}