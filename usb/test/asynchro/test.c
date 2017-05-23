# include <unistd.h>                                                            
# include <stdlib.h>                                                            
# include <stdio.h>                                                             
# include <errno.h>                                                             
# include <inttypes.h>                                                          
# include <libusb-1.0/libusb.h>                                                 
# include <time.h>                                                              
# include <pthread.h>                                                           
# include <string.h>
# include <errno.h>
# include <sys/types.h>

//VALUE PID  =
/* 1- = error
  0 = fils
  autre = pere
*/

pid_t create_process(void)
{
  pid_t PID;
    
  do{
    PID = fork();
  }while ((PID == -1) && (errno == EAGAIN));
  return PID;
}

void child_process(void)
{
  printf("NOUS SOMMES DANS LE FILS \n"
         " Le PID du fils est %d. \n"
         " Le PPID du fils est %d. \n", (int)getpid(),(int)getppid());
}

void father_process(int child_pid)
{
  printf(" Nous sommes dans le pere ! \n"
         " Le PID du fils est %d.\n"
         " Le PID du pere est %d.\n", (int)child_pid, (int)getpid());
}
int main(void)
{
  pid_t pid = create_process();
  switch (pid)
  {
    case -1:
      perror("fork");
    return EXIT_FAILURE;
    break;
    case 0:
    child_process();
    break;
    default:
    father_process(pid);
    }
    return EXIT_SUCCESS;
 
 return 0;
}

