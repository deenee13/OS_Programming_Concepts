#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>



// Function Declaration
void problem1();
void problem2();
void problem3();


/**
 * Showing the functionality of pipe where in we are creating the two child process and then in one
 * one of the child process we are reading the data we entered from the command line argumnt
 * and putting the data inside in the pipe and then in the other child process we are reading the data
 * from the pipe and giving it as a output on command line **/

int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid_a,cpid_b;
    char buf;
    struct timeval current_time;

    // Checking if you have enter right number of arguments
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Creating the child process
    cpid_a = fork();
    if (cpid_a == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /* Child reads from pipe */
    if (cpid_a == 0) 
    {    
        printf("Hello, I am child of (pid:%d)\n", (int) getpid());
        close(pipefd[1]);          /* Close unused write end */
        while (read(pipefd[0], &buf, 1) > 0)
        {
            write(STDOUT_FILENO, &buf, 1);
        }    
        write(STDOUT_FILENO, "\n", 1);
        gettimeofday(&current_time, NULL);
        printf("Time in usec in cpid_a: %d\n",current_time.tv_usec);
        close(pipefd[0]);
        
        _exit(EXIT_SUCCESS);
    } 
    /* Parent writes argv[1] to pipe */
    if(cpid_a > 0) 
    {
        cpid_b = fork();
        if(cpid_b > 0)
        {
            printf("Hello, I am parent of %d and %d (pid:%d)\n",cpid_a,cpid_b, (int)getpid());
            wait(NULL);                /* Wait for child */
            exit(EXIT_SUCCESS);
        }
        else if(cpid_b == 0)
        {
            printf("Hello, I am child of (pid:%d)\n", (int) getpid());
            close(pipefd[0]);          /* Close unused read end */
            write(pipefd[1], argv[1], strlen(argv[1]));
            gettimeofday(&current_time, NULL);
            printf("Time in usec in cpid_b: %d\n",current_time.tv_usec);
            close(pipefd[1]);          /* Reader will see EOF */
            
        }           

    }
}

/*
// Run specific problem at any given time 
int main(int argc, char *argv[])
{


    //problem1();
    //problem1();
    //printf("\n\n");
    //problem2();
}
*/


void problem3()
{
    printf("Hello World (pid:%d)\n", (int) getpid());

    int fd;
    fd = open("f1.txt",O_CREAT);
    int rc = fork();



    // Fork failed exit
    if(rc<0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    // Child new process
    else if (rc == 0)
    {
        int sz;
        sz = write(fd,"Hello\n",strlen("Hello\n"));
        printf("Hello, I am child of (pid:%d) with value of fd:%d and sz: %d\n", (int) getpid(),fd,sz);
    }
    
    // Parent Process
    else
    {
        int sz;
        sz = write(fd,"Hello\n",strlen("Hello\n"));
        printf("Hello, I am parent of %d (pid:%d) with value of fd:%d and sz:%d\n",rc, (int) getpid(),fd,sz);
    }

}


void problem2()
{
    int status;
    printf("Hello World (pid:%d)\n", (int) getpid());
    int rc = fork();

    // Fork failed exit
    if(rc<0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    // Child new process
    else if (rc == 0)
    {
        int rc_wait = waitpid(rc,&status,0);
        printf("Hello, I am child of (pid:%d) rc_wait:%d\n", (int) getpid(), rc_wait);
    }
    else
    {
        
        printf("Hello, I am parent of %d (pid:%d)\n",rc,(int) getpid());
    }
}


/** In the give function it will create two process as Child and Parent where Child is the
 * copy of the parent itself  but as a different program. In simple language it is two different threads
 * where the value of the child process is equal to 0. This feature is used to distinguish between parent and child
 * **/

void problem1()
{
    printf("Hello World (pid:%d)\n", (int) getpid());
    int rc = fork();

    // Fork failed exit
    if(rc<0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    // Child new process
    else if (rc == 0)
    {
        printf("Hello, I am child of (pid:%d)\n", (int) getpid());
    }
    else
    {
        printf("Hello, I am parent of %d (pid:%d)\n",rc, (int) getpid());
    }
}
