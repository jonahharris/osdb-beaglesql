static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/isql.c,v 0.87.2.1 2000/02/05 06:13:24 magrasjc Exp $";
/*

 isql.c

 Copyright (c) 1997   Robert Klein

 Permission to use, copy, modify and distribute this software and its
 documentation, is hereby granted to educational institutions, their
 faculty, and full-time students, non-commercial research organizations,
 registered charities, and registered not-for-profit and non-profit
 organizations without fee provided that this license agreement and
 copyright information appears in all copies.

 Permission to use this software by any other person or organization 
 is hereby granted for the current version of the software and it's
 documentation provided that this license agreement and copyright
 information appears in all copies.
 
 Commercial redistribution of this software, by itself or as part of
 another application is allowed only under express written permission of
 Robert Klein and may entail licensing fees.
 
 ROBERT KLEIN DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
 INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO 
 EVENT SHALL ROBERT KLEIN BE LIABLE FOR ANY SPECIAL, INDIRECT OR 
 CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF 
 USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR 
 OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR 
 PERFORMANCE OF THIS SOFTWARE.
 
*/
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include "bsql.h"

#define YES 1
#define NO 0

void demo(char *host);
void load_execute_file (char *str);
void exit_nicely (int s);
void signal_catcher(int);

char command[30000];
int s;	        /* socket descriptor, read count*/
struct bresult *res;
long i, j;
int dbset=NO, ret;
struct termios       prev_modes  , our_modes;

/*------------------------------------------------------------------------
 * main - Interactive SQL monitor for Beagle SQL
 *------------------------------------------------------------------------
 */
int
main(argc, argv)
int	argc;
char	*argv[];
{
	char	*host = "localhost";	/* host to use if none supplied	*/
        tzset();
	switch (argc) {
	case 1:
		host = "localhost";
		break;
	case 3:
		BSQLservice = argv[2];
		/* FALL THROUGH */
	case 2:
		host = argv[1];
		break;
	default:
		fprintf(stderr, "usage: demo [host [port]]\n");
		exit(1);
	}
	demo(host);
  
	exit(0);
}

/*------------------------------------------------------------------------
 * demo - Main routine
 *------------------------------------------------------------------------
 */
void demo(char *host)
{
   char newpasswd[5][16],passwd[16];

    int length;
   magic_t magicno=MAKE_MAGIC

   sigset(SIGALRM,signal_catcher);   

   alarm(30);
   tcgetattr(0,&prev_modes);
   memcpy(&our_modes,&prev_modes,sizeof(struct termios));
   our_modes.c_lflag &= ~(ECHO|ECHOE|ECHOK/*|ECHOKE*/);
   our_modes.c_lflag &= ~ICANON;
   our_modes.c_cc[VMIN]  = 1;
   our_modes.c_cc[VTIME] = 0;
   tcsetattr(0,TCSAFLUSH,&our_modes);
   printf ("Enter Beagle Password:");
   fgets(passwd,sizeof(passwd),stdin);
   passwd[strlen(passwd)-1]=0;
   
   tcsetattr(0,TCSAFLUSH, &prev_modes);
   alarm(0);
   fprintf (stdout, "\nConnecting to %s...\n", host);
   s = BSQLConnect (host,passwd,magicno);

   if (s < 0) 
      fprintf (stderr, "Can't Connect to Host\n");
   else {
      for (;;) {
         fprintf (stdout, "\nisql--> ");
         fgets (command, 30000, stdin);
         if (command[0] == ';') 
            continue;
         command[strlen(command)-1] = '\0';
         if (command[0]=='\\') {
            switch (command[1]) {
               case 'q': exit_nicely(s);

               case 'h':
               case '?': fprintf (stdout, "\n\\h or ?           help");
                         fprintf (stdout, "\n\\l [file]         load & execute SQL from file");
                         fprintf (stdout, "\n\\o [dbname]       open database");
                         fprintf (stdout, "\n\\p                change password");
                         fprintf (stdout, "\n\\q                quit");
                         fprintf (stdout, "\n");
                         break;

               case 'l': load_execute_file (command+3);
                         break;

               case 'o': if (command[2]=='i') /* undocumented and dangerous */
                            dbset=YES;  
                         else {
                            ret = BSQLSetCurrentDB (s, command+3);
                            if (!ret)
                               fprintf (stdout, "\nCan't sent current database");
                            else {
                               fprintf (stdout, "\nThe Current Database is '%s'", BSQLGetCurrentDB (s));
                               dbset = YES; 
                            }
                         }
                         break;
                  case 'p':
                        tcgetattr(0,&prev_modes);
                        memcpy(&our_modes,&prev_modes,sizeof(struct termios));
                        our_modes.c_lflag &= ~(ECHO|ECHOE|ECHOK/*|ECHOKE*/);
                        our_modes.c_lflag &= ~ICANON;
                        our_modes.c_cc[VMIN]  = 1;
                        our_modes.c_cc[VTIME] = 0;
                        tcsetattr(0,TCSAFLUSH,&our_modes);
                        if (strcmp(getlogin(),"beagle"))
			{
                            printf ("old password:");
                            fgets(newpasswd[2],16,stdin);
                        }
                        printf ("\nnew password:");

                        fgets(newpasswd[3],16,stdin);
                        printf ("\nnew password confirmation:");
                        fgets(newpasswd[4],16,stdin);

                        tcsetattr(0,TCSAFLUSH, &prev_modes);
                        if (strcmp(newpasswd[3],newpasswd[4])!=0)
                           fprintf (stderr,
                                    "\npassword change confirmation failed.\n");
                        else {
                           BSQLSetPassword(s,0,(char **)newpasswd);
                           printf ("\npassword changed.\n");
                        }
                        strcpy(newpasswd[2],"xxxxxxxx");
                        strcpy(newpasswd[3],"xxxxxxxx");
                        strcpy(newpasswd[4],"xxxxxxxx");
                      break;
               }
            }
            else {

               if (dbset) {
                  res = BSQLQueryDB (s, command);
                  show_select(res);
                  BSQLFreeResult (res);
                  }
               else
                  fprintf (stdout, "\nNo Database selected");
            }
      }
   }
}

void load_execute_file (char *filename)
{
   FILE *fp;
   struct termios       prev_modes  , our_modes;

   if ((fp = fopen (filename, "r"))==NULL) {
      fprintf (stdout, "\nCan't open file %s", filename);
      return;
   }
   
   while (fgets (command, 30000, fp) != NULL) {
      if (command[0] == ';') continue;
      command[strlen(command)-1] = '\0';

      fprintf (stdout, command);

      if (command[0]=='\\') {
         switch (command[1]) {
            case 'q': exit_nicely(s);

            case 'h':
            case '?': fprintf (stdout, "\n\\h or \\?          help");
                      fprintf (stdout, "\n\\l [file]         load & execute SQL from file");
                      fprintf (stdout, "\n\\o [dbname]       open database");
                      fprintf (stdout, "\n\\p                change password");
                      fprintf (stdout, "\n\\q                quit");
                      fprintf (stdout, "\n");
                      break;

            case 'l': load_execute_file (command+3);
                      break;

            case 'o': ret = BSQLSetCurrentDB (s, command+3);
                      if (!ret)
                         fprintf (stdout, "\nCan't sent current database");
                      else {
                         fprintf (stdout, "\nThe Current Database is '%s'", BSQLGetCurrentDB (s));
                         dbset = YES; 
                      }
                      break;

         }
      }
      else {

         res = BSQLQueryDB (s, command);
         show_select(res);
         BSQLFreeResult (res);
      }
   }
   fclose (fp);
}

show_select (struct bresult *res) {
   void *valP;
   int   valT;
   long i, j;

   if (res != NULL) {
       fprintf (stdout, " --> '%s'\n", res->errcode);
       if (!res->resultcode) 
           fprintf (stdout, "\nERROR Processing Query");
       else if (!strncasecmp ("select ", command, 7)) {
           fprintf (stdout, "\nDisplaying Results of Select\n\n");
           for (j=0L; j<BSQLnfields(res); j++) {
               fprintf (stdout, "%-20s ", BSQLFieldName (res, j));
           }
           fprintf (stdout, "\n");
           for (j=0L; j<70L; j++) 
               fprintf (stdout, "-");

           for (i=0L; i<BSQLntuples(res); i++) {
               fprintf (stdout, "\n");
               for (j=0L; j<BSQLnfields(res); j++) {
                   valP = BSQLFieldValue (res, i, j);
                   valT = BSQLFieldType (res, j);
                   if (valT == FTYPE_INT||valT==FTYPE_OID) 
                       fprintf (stdout, "%ld ", *(long *)valP);
                   else if (valT == FTYPE_CHAR)
                       fprintf (stdout, "%-20s ", valP);
                  else if (valT == FTYPE_TIME||valT == FTYPE_DATE ||valT == FTYPE_TIMESTAMP) {
                       fprintf (stdout,"%s",valP);
		  }
                   else fprintf (stdout,"unrecognized field type %d",valT);

                   
               }
           }
           fprintf (stdout, "\n\n");
       }
   }
   else
      fprintf (stdout, "\nERROR Communicating with Backend");

}


void exit_nicely (int s)
{
   BSQLDisconnect(s);
   exit (0);
}

void signal_catcher(int the_sig) 
{
    signal(the_sig, signal_catcher);
    if (the_sig == SIGALRM) {
      tcsetattr(0,TCSAFLUSH, &prev_modes); 
      putchar('\n');
       exit(10);
    }
}
