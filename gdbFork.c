/*
2 comandes
>> p/t entrada
>> quit
*/
#include <unistd.h>
#include <string.h>

int main ( int args, char *arg[] )
{
	int Rfd[2], Wfd[2];
	pid_t pid;
	char buffer [30];
	char *help[] = { "gdb", "-q", NULL };

	pipe ( Rfd );
	pipe ( Wfd );
	pid = fork ();
	if (pid)
	{
	//	read ( fd[1], buffer, sizeof (buffer));
	//	strcpy ( buffer + strlen(buffer), "Aixo he llegit <-\n");
	//	write ( 1, buffer, strlen(buffer) );
		//strcpy ( buffer +4, arg[1] );
		//strcpy ( buffer +4+strlen(arg[1]), "\nquit\n\0" );
	//	strcpy ( buffer, "p/t 10\n" );
	//	write ( fd[1], buffer, strlen(buffer) );
	//	write ( 1, buffer, strlen(buffer) );
	//	read ( fd[1], buffer, sizeof (buffer));
	//	strcpy ( buffer + strlen(buffer), "Aixo he llegit <-\n");
	//	write ( 1, buffer, strlen(buffer) );
	//	read ( fd[1], buffer, sizeof (buffer));
	//	strcpy ( buffer, "quit" );
	//	write ( fd[1], buffer, strlen(buffer) );
		read ( Rfd[0], buffer, sizeof (buffer));
		strcpy ( buffer + strlen(buffer), "Aixo he llegit <-\n");
		write ( 1, buffer, strlen(buffer) );

		strcpy ( buffer, "quit\n" );
		write ( Wfd[1], buffer, strlen(buffer));
		strcpy ( buffer, "Acabat\n" );
		write ( 1, buffer, strlen (buffer));
	} else
	{
		dup2	(Wfd[0], 0);
		close	(Wfd[0]);
		dup2	(Rfd[1], 1);
		close	(Rfd[1]);
		execvp	( help[0], help );
	}
}
