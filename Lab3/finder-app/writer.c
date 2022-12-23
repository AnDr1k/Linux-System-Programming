#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>

const int arg_size = 2;

int main(int argc, char **argv)
{
    openlog(NULL, 0, LOG_USER);

    if (argc == arg_size + 1)
    {
        char *writefile = argv[1];
        char *writestr = argv[2];

        FILE *file = fopen(writefile, "w");
        if (file != NULL)
        {
            syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

            fprintf(file, "%s", writestr);
            fclose(file);

            return 0;
        }
        else
        {
            syslog(LOG_ERR, "Error attempting to open file %s: %d - %s\n", writefile, errno, strerror(errno));
            
            printf("ERROR: File could not be created.");

            return 1;
        }        
    }
    else
    {
        syslog(LOG_ERR, "Invalid Number of Arguments.");

        printf("ERROR: Invalid Number of Arguments.\n");
        printf("Total number of arguments should be 2.\n");
        printf("The order of the arguments should be:\n");
        printf("\t1) Full path to a file (including filename) on the filesystem.\n");
        printf("\t2) Text string which will be written within the file.\n");

        return 1;
    }
}
