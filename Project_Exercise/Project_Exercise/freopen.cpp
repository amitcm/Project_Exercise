#include <stdio.h>

// stream
// pointer to a FILE object that identifies the stream to be reopened.

//freopen ===== [f]reopen stream with different file or mode

//freopen first tries to close any file already associated with the stream given as third parameter and disassociates it.
//FILE * freopen ( const char * filename, const char * mode, FILE * stream );
//freopen ("myfile-out.txt","w",stdout);
//freopen ("myfile-in.txt","r",stdin);

//fclose (stdout);  // treat stdout as FILE* i.e, a file pointer
//fclose (stdin);