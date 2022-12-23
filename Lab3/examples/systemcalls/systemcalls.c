#include "systemcalls.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
 */
bool do_system(const char *cmd)
{
    return system(cmd) == 0;
}

/**
 * @param count -The numbers of variables passed to the function. The variables are command to execute.
 *   followed by arguments to pass to the command
 *   Since exec() does not perform path expansion, the command to execute needs
 *   to be an absolute path.
 * @param ... - A list of 1 or more arguments after the @param count argument.
 *   The first is always the full path to the command to execute with execv()
 *   The remaining arguments are a list of arguments to pass to the command in execv()
 * @return true if the command @param ... with arguments @param arguments were executed successfully
 *   using the execv() call, false if an error occurred, either in invocation of the
 *   fork, waitpid, or execv() command, or if a non-zero return value was returned
 *   by the command issued in @param arguments with the specified arguments.
 */

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char *command[count + 1];
    int i;
    for (i = 0; i < count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t child_pid = fork();
    
    if (child_pid == -1)
    {
        return false;
    }
    else if (child_pid == 0)
    {
        if (execv(command[0], command) == -1)
        {
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pid_t other_pid;
        int other_status;
                
        do 
        {
            other_pid = waitpid(child_pid, &other_status, WUNTRACED | WCONTINUED);
      
            if (other_pid == -1)
            {
                return false;
            }

            if (WIFEXITED(other_status) && WEXITSTATUS(other_status) == EXIT_FAILURE)
            {
                return false;
            }

        } while (!WIFEXITED(other_status));
    }

    va_end(args);

    return true;
}

/**
 * @param outputfile - The full path to the file to write with command output.
 *   This file will be closed at completion of the function call.
 * All other parameters, see do_exec above
 */
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char *command[count + 1];
    int i;
    for (i = 0; i < count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    int output_fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);

    if (output_fd < 0)
    {
        return false;
    }    

    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        return false;
    }
    else if (child_pid == 0)
    {
        if (dup2(output_fd, 1) < 0)
        {
            return false;
        }

        close(output_fd);     

        if (execv(command[0], command) == -1)
        {
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pid_t other_pid;
        int other_status;
                
        do 
        {
            other_pid = waitpid(child_pid, &other_status, WUNTRACED | WCONTINUED);
      
            if (other_pid == -1)
            {
                return false;
            }

            if (WIFEXITED(other_status) && WEXITSTATUS(other_status) == EXIT_FAILURE)
            {
                return false;
            }

        } while (!WIFEXITED(other_status));
    }

    va_end(args);

    return true;
}
