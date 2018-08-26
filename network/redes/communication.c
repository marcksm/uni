#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "communication.h"
#include <string.h>

int cntm = 0;

char *lastidle;

void SENDreset () {
    strcpy (sendbuffer, "");
}

static char *STRINGconcatenate (char *str1, char *str2) {
  char *path;
  path = malloc(strlen(str1)+strlen(str2)+1);
  strcpy(path, str1);
  strcat(path, str2);
  return path;
}

static int cntstrings (char sm[][MAXLINE + 1]) {
    int i = 0;
    while (*sm[i] != 0) i++;
    return i;
}

static int STRINGcontains(char *s, char ch) {
    int n = strlen(s);
    int i;
    for (i = 0; i < n; i++)
        if (s[i] == ch) return 1;
    return 0;
}

void SENDinsertline (char *s) {
    strcat (sendbuffer, s);
    strcat (sendbuffer, "\r\n");
}

void CLIENTauthenticate (char sm[][MAXLINE + 1]) {
  SENDreset ();
  SENDinsertline ("+");
  CLIENTwrite ();
}

void CLIENTlogin (char sm[][MAXLINE + 1]) {
    int id;
    char aux[200];
    id = USERlogin (sm[2], sm[3]);
    //printf ("id=%d", id);
    //printf ("(%s,%s)",sm[2],sm[3]);
    setUSERcurrent (id);
    SENDreset ();
    if (getUSERcurrent () != -1) {
      sprintf (aux, "%s OK - login completed, now in authenticated state", sm[0]);
      SENDinsertline (aux);
      USERinit ();
      MAILnew();
    }
    else
      SENDinsertline ("NO login failure: user name or password rejected");
    CLIENTwrite ();
}

void CLIENTlogout (char sm[][MAXLINE + 1]) {
  SENDreset ();
  SENDinsertline (MSGend());
  CLIENTwrite ();
  USERlogout ();
  exit(0);
}

int CLIENTcurrent () {
  return getUSERcurrent();
}


void CLIENTlist (char sm[][MAXLINE + 1]) {
  if ((strcmp ("\"\"", sm[2]) == 0) && (strcmp ("\"*\"", sm[3]) == 0)) {
    SENDreset ();
    SENDinsertline ("* LIST (\\HasNoChieldren) \".\" INBOX");
    SENDinsertline ("OK List completed.");
    CLIENTwrite ();
    return;
  }
  if ((strcmp ("\"\"", sm[2]) == 0) && (strcmp ("\"INBOX\"", sm[3]) == 0)) {
    SENDreset ();
    SENDinsertline ("* LIST (\\HasNoChieldren) \".\" INBOX");
    SENDinsertline ("OK List completed.");
    CLIENTwrite ();
    return;
  }
  FILE *lists;
  int i = 0;
  char c = 0;
  char *userpath = getUSERpath ();
  char *path = STRINGconcatenate (userpath, "/Maildir/lists");
  lists = fopen (path, "r");
  while (1) {
    char *list  = malloc  (MAXLINE * sizeof (char));
    while ((c = getc(lists)) != '\n' && (c != EOF)) {
      list[i++] = c;
    }
    list[i] = '\0';
    if (strcmp (list, sm[3]) == 0) {
      SENDreset ();
      SENDinsertline (MSGlist(sm[3]));
      CLIENTwrite ();
    }
    else if (c == EOF) {
      SENDreset ();
      SENDinsertline ("NO - list failure: can't list that reference or name");
      CLIENTwrite ();
      free(list);
      break;
    }
    free(list);
    fclose(lists);
  }

}

void CLIENTidle (char sm[][MAXLINE + 1]) {
  SENDreset ();
  SENDinsertline (MSGidle(1));
  CLIENTwrite ();
  strcpy (lastidle, sm[0]);
}

void CLIENTnamespace (char sm[] [MAXLINE+1]) {
  SENDreset();
  SENDinsertline (MSGnamespace());
  CLIENTwrite();
}

void CLIENTid (char sm[] [MAXLINE+1]) {
  SENDreset();
  SENDinsertline (MSGid());
  CLIENTwrite();
}

void CLIENTnoop (char sm[] [MAXLINE+1]) {
  SENDreset();
  SENDinsertline (MSGnoop(0, 0));//TEMPO DE RESPOSTA
  CLIENTwrite();
}

void CLIENTdone (char sm[] [MAXLINE+1]) {
  char buffer[200];
  SENDreset();
  strcpy(buffer, sm[0]);
  strcat(buffer, " ");
  strcat(buffer, MSGidle(3));
  SENDinsertline (buffer);
  CLIENTwrite();
}

void CLIENTselect (char sm[][MAXLINE+1]) {
    int i, n, exists = 0, recent = 0, unseen = 1000, uidnext = -1;
    int *uids = getUSERmails();
    char aux[200];
    n = getMAILqtd();
    SENDreset();
    for (int i = 0; i < n; i++) {
        if (!isMAILdelete (uids[i])) {
            if (isMAILunseen(uids[i])) {
                recent++;
                if (uids[i] < unseen) unseen = uids[i];
            }
            if (uids[i] + 1 > uidnext) uidnext = uids[i] + 1;
            exists++;
        }
    }
    SENDreset();
    SENDinsertline("* FLAGS (\\Answered \\Flagged \\Deleted \\Seen \\Draft)");
    SENDinsertline("* OK [PERMANENTFLAGS (\\Answered \\Flagged \\Deleted \\Seen \\Draft)]");
    sprintf(aux, "* %d EXISTS", exists);
    SENDinsertline(aux);
    sprintf(aux, "* %d RECENT", recent);
    SENDinsertline(aux);
    if (unseen != 1000) {
        sprintf(aux, "* OK [UNSEEN %d]", unseen);
        SENDinsertline(aux);
    }
    SENDinsertline("* OK [UIDVALIDITY 999999]");
    if (uidnext != -1) {
        sprintf(aux, "* OK [UIDNEXT %d]", uidnext);
        SENDinsertline(aux);
    }
    sprintf(aux, "%s OK [READ-WRITE] Select completed.", sm[0]);
    SENDinsertline(aux);
    CLIENTwrite();
}

void CLIENTfetchall (char sm[][MAXLINE + 1]) {
    int i;
    char aux[2000];
    FILE *f;
    int n = getMAILqtd();
    int *uids = getUSERmails();
    SENDreset();

    for (i = n-1; i >= 0; i--) {
        if (!isMAILdelete(uids[i])) {
            int size = getMAILsize(uids[i]) + getMAILlines(uids[i]);
            if (isMAILseen(uids[i])) {
                if (cntstrings(sm) == 22)
                    sprintf(aux, "* %d FETCH (UID %d RFC822.SIZE %d FLAGS (\\Seen) BODY[HEADER.FIELDS (FROM TO CC BCC SUBJECT DATE MESSAGE-ID PRIORITY X-PRIORITY REFERENCES NEWSGROUPS IN-REPLY-TO CONTENT-TYPE REPLY-TO)] {%d}", uids[i], uids[i], size, size);
                else
                    sprintf(aux, "* %d FETCH (UID %d RFC822.SIZE %d FLAGS (\\Seen) BODY[] {%d}", uids[i], uids[i], size, size);
            } else {
                if (cntstrings(sm) == 22)
                    sprintf(aux, "* %d FETCH (UID %d RFC822.SIZE %d FLAGS () BODY[HEADER.FIELDS (FROM TO CC BCC SUBJECT DATE MESSAGE-ID PRIORITY X-PRIORITY REFERENCES NEWSGROUPS IN-REPLY-TO CONTENT-TYPE REPLY-TO)] {%d}", uids[i], uids[i], size, size);
                else
                    sprintf(aux, "* %d FETCH (UID %d RFC822.SIZE %d FLAGS () BODY[] {%d}", uids[i], uids[i], size, size);
            }
            SENDinsertline(aux);
            f = fopen(getMAILpath(uids[i]), "r");
            while (fgets(aux, MAXSIZE, f) != NULL) {
                aux[strlen(aux) - 1] = 0;
                SENDinsertline(aux);
            }
            SENDinsertline(")");
            fclose(f);
        }
    }
    sprintf(aux, "%s OK Fetch completed.", sm[0]);
    SENDinsertline(aux);
    CLIENTwrite();
}

void CLIENTfetchuid (char sm[][MAXLINE + 1], int uid) {
    int i = uid, j;
    char aux[200];
    FILE *f;
    int n = getMAILqtd();
    int *uids = getUSERmails();
    SENDreset();
    int size = getMAILsize(uid) + getMAILlines(uid);
    /*for (j = 0; j < n; j++)
        if (uid == uids[j])
            i = uids[j];*/
    if (!isMAILdelete(i)) {
        if (isMAILseen(i)) {
            if (cntstrings(sm) == 22)
                sprintf(aux, "* %d FETCH (UID %d RFC822.SIZE %d FLAGS (\\Seen) BODY[HEADER.FIELDS (FROM TO CC BCC SUBJECT DATE MESSAGE-ID PRIORITY X-PRIORITY REFERENCES NEWSGROUPS IN-REPLY-TO CONTENT-TYPE REPLY-TO)] {%d}", i, i, size, size);
            else
                sprintf(aux, "* %d FETCH (UID %d RFC822.SIZE %d FLAGS (\\Seen) BODY[] {%d}", i, i, size, size);
        } else {
            if (cntstrings(sm) == 22)
                sprintf(aux, "* %d FETCH (UID %d RFC822.SIZE %d FLAGS () BODY[HEADER.FIELDS (FROM TO CC BCC SUBJECT DATE MESSAGE-ID PRIORITY X-PRIORITY REFERENCES NEWSGROUPS IN-REPLY-TO CONTENT-TYPE REPLY-TO)] {%d}", i, i, size, size);
            else
                sprintf(aux, "* %d FETCH (UID %d RFC822.SIZE %d FLAGS () BODY[] {%d}", i, i, size, size);
        }
        SENDinsertline(aux);
        f = fopen(getMAILpath(i), "r");
        while (fgets(aux, MAXSIZE, f) != NULL) {
            aux[strlen(aux) - 1] = 0;
            SENDinsertline(aux);
        }
        SENDinsertline(")");
        fclose(f);
    }
    sprintf(aux, "%s OK Fetch completed.", sm[0]);
    SENDinsertline(aux);
    CLIENTwrite();

}



void CLIENTfetch (char sm[][MAXLINE + 1]) {

    if (STRINGcontains(sm[3], ':')) {
        CLIENTfetchall(sm);
    } else {
        int uid = atoi(sm[3]);
        CLIENTfetchuid(sm, uid);
    }
}

void CLIENTdeleted(int uid) {
    printf("DELETED %d\n", uid);
    toMAILdelete(uid);
}

void CLIENTseen(int uid) {
    printf ("SEEN %d\n", uid);
    toMAILseen(uid);
}

void CLIENTunseen(int uid) {
    printf ("UNSEEN %d\n", uid);
    toMAILunseen(uid);
}

void CLIENTflag(char sm[][MAXLINE + 1]) {
    char aux[200];
    int uid = atoi(sm[3]);
    SENDreset();
    if (strcmp(sm[4], "+Flags") == 0) {
        CLIENTseen(uid);
        if (strcmp (sm[5], "(\\Seen)") != 0)
            CLIENTdeleted(uid);

    } else {
        CLIENTunseen(uid);
    }
    sprintf (aux, "%s OK Store completed", sm[0]);
    SENDinsertline(aux);
    CLIENTwrite();
}

void CLIENTrequest (char sm[][MAXLINE + 1]) {
  if (strcmp (sm[1], "authenticate") == 0) {
    CLIENTauthenticate (sm);
  }
  else if (strcmp (sm[1], "login") == 0) {
    CLIENTlogin (sm);
  }
  else if (strcmp (sm[1], "logout") == 0) {
    CLIENTlogout (sm);
  }
  else if (strcmp (sm[1], "list") == 0) {
    CLIENTlist (sm);
  }
  else if (strcmp (sm[1], "IDLE") == 0) {
    CLIENTidle (sm);
  }
  else if (strcmp (sm[1], "namespace") == 0) {
    CLIENTnamespace (sm);
  }
  else if (strcmp (sm[1], "noop") == 0) {
    CLIENTnoop (sm);
  }
  else if (strcmp (sm[1], "ID") == 0) {
    CLIENTid (sm);
  }
  else if (strcmp (sm[1], "DONE") == 0) {
    CLIENTdone (sm);
  }
  else if (strcmp (sm[1], "select") == 0) {
    CLIENTselect(sm);
  }
  else if (strcmp (sm[1], "UID") == 0) {
    CLIENTfetch(sm);
  }
  else if (strcmp(sm[1], "uid") == 0) {
    CLIENTflag(sm);
  }
  else if (strcmp(sm[0], "DONE") == 0) {
    CLIENTdone(sm);
  } else {
    SENDinsertline("-");
    CLIENTwrite();
  }
  if (getUSERcurrent() != -1) {
    MAILnew ();
  }
}


int CLIENTread (char sm [][MAXLINE+1]) {
   char recvline [MAXLINE + 1];
   int n = read (connfd, recvline, MAXLINE);
   recvline[n] = 0;
   printf ("Recebendo: %s Fim_recebe\n", recvline);
   split (recvline, sm);
   cntm++;
   return n;
}


void CLIENTwrite () {
    printf ("Enviando: %s Fim_envia\n", sendbuffer);
    write (connfd, sendbuffer, strlen (sendbuffer));
    SENDreset();
}

void split (char s[], char ss[][MAXLINE + 1]) {
    char *token = strtok (s, " ");
    int cnt = 0;
    while (token != NULL) {
        strcpy (ss[cnt++], token);
        token = strtok (NULL, " ");
    }
    *ss[cnt] = 0;
    ss[cnt - 1][strlen(ss[cnt - 1]) - 2] = 0;
}
