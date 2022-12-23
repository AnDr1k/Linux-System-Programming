#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int 
main( int argc, char ** argv )
{
  const char * writefile;
  const char * writestr;
  int fd;
  int len;
  int err;

  openlog( NULL, 0, LOG_USER );
  if ( argc != 3 ) {
    syslog( LOG_ERR, "Usage: %s <file> <string>", argv[0] );
    return 1;
  }
  writefile = argv[1];
  writestr  = argv[2];

  fd = open( writefile, O_RDWR | O_CREAT | O_TRUNC );
  if ( fd == -1 ) {
    err = errno;
    syslog( LOG_ERR, "Failed to open file %s - error %s", writefile, strerror( err ) );
    return 1;
  }
  if ( fchmod( fd, S_IRUSR | S_IWUSR | S_IRGRP ) == -1 ) {
    err = errno;
    syslog( LOG_ERR, "Failed to chmod file %s - error %s", writefile, strerror( err ) );
  }

  // NOTE echo adds a carriage return - write does not 
  len = strlen( writestr );
  if ( write( fd, (const void *)writestr, len ) != len || write( fd, (const void *)"\n", 1) != 1 ) {
    err = errno;
    syslog( LOG_ERR, "Failed to write string %s - error %s", writestr, strerror( err ) );
    return 1;
  }
  if ( close(fd) == -1 ) {
    err = errno;
    syslog( LOG_ERR, "Failed to close file %s - error %s", writefile, strerror( err ) );
    return 1;
  }
  return 0; 

}  
