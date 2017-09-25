/*
2 comandes
>> p/t entrada
>> quit

De fet vull que sigui per mostrar pas per pas d'una calculadora i/o solucionador de jocs pas a pas
Aixi que realment m'interesa com a llibreria

resultats curiosos amb
8
23
// Segurament altres, pero nomes he fet poques proves
*/
#include <unistd.h>
#include <string.h>

typedef struct GDB_COMMUNICATION mygdb;

struct GDB_COMMUNICATION 
{
	int Rfd;	// File descriptor read
	int Wfd;	// File descriptor write
	pid_t pid;	// Pid for child
};

mygdb initGDB ( char *nameFile )
{
// Tot el que necessito
	mygdb gdbd;	// gdb descriptor
	char *cmd[] = { "gdb", "-q", nameFile, NULL }; // Comanda per obrir el programa desitjat
	int Rfd[2], Wfd[2];

// Nomes inicialitzem
	pipe ( Rfd );
	pipe ( Wfd );
	gdbd.pid = fork ();

	if ( !gdbd.pid )
	{ // Cas del fill, lo de Write i Read, es refereix al pare. Aixi que aqui esta del reves
		dup2	(Wfd[0], 0);
		close	(Wfd[0]); // Nomes poso els close, perque aixi ho indiquen les webs... No se que fa
		dup2	(Rfd[1], 1);
		close	(Rfd[1]);
		execvp	( cmd[0], cmd );
	}
	gdbd.Wfd = Wfd[1];
	gdbd.Rfd = Rfd[0];
return gdbd;
}

int main ( int args, char *arg[] )
{
	mygdb test;
	char buffer [30];

	if ( args != 2 )
	{ // Error for arguments
		write (2, "Nomes una entrada\n", 18);
		return 1;
	}

	test = initGDB ( NULL ); // NULL, perque no volem obrir cap programa

// Primer volem que s'agi inicialitzat el gdb
	read (test.Rfd, buffer, sizeof (buffer));

	//write ( 1, buffer, strlen (buffer)); // Comprovar que llegeix /(gdb) /

// Primera trama, per dir que volem en binary
	write (test.Wfd, "p/t ", 4 );
	write (test.Wfd, arg[1], strlen (arg[1]));
	write (test.Wfd, "\n", 1 );

// Ara toca llegir la seva sortida
	read (test.Rfd, buffer, sizeof (buffer));
// Ja podem tancar el gdb, per evitar molts executables oberts
	write (test.Wfd, "quit\n", 5);

// Ja ho tenim tot, mostrem el resultat per pantalla
	write (1, "Entrat: ", 8);
	write (1, arg[1], strlen(arg[1]));
	write (1, "\nSortida: ", 10);
	write (1, buffer, strlen (buffer));
	write (1, "\nfi\n", 4);
}
