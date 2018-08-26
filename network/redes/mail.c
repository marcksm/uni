#include "mail.h"

static char *STRINGconcatenate (char *str1, char *str2) {
  char *path;
  path = malloc(strlen(str1)+strlen(str2)+1);
  strcpy(path, str1);
  strcat(path, str2);
  return path;
}

int getMAILsize(int uid) {
    FILE *f;
    int size;
    char *name = getMAILpath(uid);
    printf ("path %d: %s\n", uid, name);
    f = fopen(name, "r");
    fseek (f, 0, SEEK_END);
    size = ftell (f);
    fclose (f);
    return size;
}

int getMAILlines(int uid) {
    int n = 0;
    char buffer[200];
    char *name = getMAILpath(uid);
    FILE *f;
    f = fopen(name, "r");
    while (fgets(buffer, 200, f) != NULL) n++;
    fclose (f);
    return n;
}

int getMAILqtd () {
  char *user = getUSERpath();
  char *path = STRINGconcatenate(user, "/Maildir/uidlist");
  int qtd = 0;
  char c = 0;
  FILE *uidlist = fopen (path, "r");
  while ((c = fgetc(uidlist))!= '\n');
  c = fgetc(uidlist);
  while ((c = fgetc(uidlist))!= '\n');
  while ((c = fgetc(uidlist))!= EOF) {
    if (c == '\n' ) {qtd++;} //novo email
  }
  return qtd;
}



static int size (int uid) {
  int i = 0;
  while (uid != 0) {
    i++;
    uid = uid / 10;
  }
  return i;
}

static int fpeek(FILE * const fp) {
  const int c = getc(fp);
  return c == EOF ? EOF : ungetc(c, fp);
}

char *MAILuniqname(int uid) {
  char *name = malloc (uid * sizeof (char));
  int i = 0, k = 0;
  while (uid != 0) {
    name[i++] = uid%10 + '0';
    uid = uid / 10;
  }
  name[i] = '\0';
  char *uniq_name = malloc ((i) * sizeof (char));
  i = i -1;
  for (k = 0; k <= i; k++) {
    uniq_name[k] = name[i-k];
  }
  uniq_name[k] = '\0';
  free(name);
  return uniq_name;
}

char *MAILgetname (int uid) {
  char *user = STRINGconcatenate("./", getUSERname(getUSERcurrent()));
  char *path = STRINGconcatenate(user, "/Maildir/uidlist");
  FILE *list = fopen (path, "r");
  char c;
  char *name = MAILuniqname(uid);

  char *fullname;
  int i = 0, siz = size(uid);
  fullname =  malloc ((siz + 6 ) * sizeof (char ));
  strcpy(fullname, name);
  while ((c = fgetc(list))!= EOF) {
    if (fullname[i] == c) {
      i++;
      if (i == (siz) && fpeek(list) == '_') { break; }
    }
    else i = 0;
  }
  if (c == EOF) {
    return NULL;
  }
  while ((c = fgetc(list))!= '\n') {
    fullname[i++] = c;
  }
  fullname[i] = '\0';
  free (name);
  fclose(list);
  return (fullname);
}

void MAILupdate (int uid_i, int seen, int delete, int l) {
  char *params = MAILgetname (uid_i);
  char *aff = malloc ((strlen(params+1)) * sizeof (char));
  strcpy(aff,params);
  char *user = STRINGconcatenate("./", getUSERname(getUSERcurrent()));
  char *path = STRINGconcatenate(user, "/Maildir/uidlist");
  FILE *list = fopen (path, "r+");
  char *uid = MAILuniqname (uid_i);
  char c = 0, b = 0, temp = 0, nextc;
  int i = 0, nl = 0, quit  = 0;
  int uidsize = 0;
  while (uid[i] != '\0') i++;
  uidsize = i;
  i = 0;
  while ((c = fgetc(list)) != EOF) {
    nextc = fpeek(list);
    if (c == '\n') {nl = 1;}
    if (c == '_') { nl = 0;}
    if (c == uid[i]) {
      i++;
      if (i == uidsize && nextc == '_' && nl == 1) {
        quit = 1;
        nl = 0;
      }
      if (nextc == '\n') {i = 0; nl = 1;}
    }
    else i = 0;

    if (quit) break;
  }
  (c = fgetc(list));
  b = seen + '0';

  fputc(b, list);
  (c = fgetc(list));
  b = delete + '0';

  fputc(b, list);
  (c = fgetc(list));
  b = l + '0';

  fputc(b, list);
  (c = fgetc(list));
  (c = fgetc(list));
  fclose(list);
  params = MAILgetname (uid_i);
  char *temps = STRINGconcatenate (user, "/Maildir/cur/");
  char *oldpath = STRINGconcatenate (temps , aff);

  char *newsss= malloc ((strlen(params+1)) * sizeof (char));
  newsss= params;
  char *newpath = STRINGconcatenate (temps , newsss);
  rename (oldpath, newpath);
  free(temps);
  free(newsss);
  free(aff);
}

static int MAILadd (int seen, int delete, int l) {
  char *user = STRINGconcatenate("./", getUSERname(getUSERcurrent()));
  char *path = STRINGconcatenate(user, "/Maildir/uidlist");
  FILE *list = fopen (path, "r+");
  char c = 0, nextc = 0;
  (c = fgetc(list));//N
  char *next = malloc (20 * sizeof (char));
  int i = 0, uid = 0;
  while ((c = fgetc(list)) != '\n') next[i++] = c;
  next[i] = '\0';
  uid = atoi (next);
  uid++;

  char *uid_new = MAILuniqname(uid);
  rewind(list);
  (c = fgetc(list));
  i = 0;
  while (uid_new[i] != '\0') {
    fputc(uid_new[i++], list);
  }
  fputc('\n', list);
  while ((c = fgetc(list)) != EOF) {
    nextc = fpeek(list);
    if (nextc == EOF) break;
  }
  fputs (next, list);
  fputc ('_', list);
  char b = 0;
  b = seen + '0';
  fputc (b, list);
  fputc ('_', list);
  b = delete + '0';
  fputc (b, list);
  fputc ('_', list);
  b = l + '0';
  fputc (b, list);
  fputc ('\n', list);

  fclose(list);
  free (uid_new);
  free(next);
  return uid-1;
}

void MAILnew () {
  DIR *d;
  struct dirent *dir;
  char *newname, *oldname;
  char *pathnew, *pathold;
  char *pathn, *patho;
  char *user = STRINGconcatenate("./", getUSERname(getUSERcurrent()));

  pathnew = STRINGconcatenate(user, "/Maildir/cur/");
  pathold = STRINGconcatenate(user, "/Maildir/new/");

  int uid, ret = 0;
  d = opendir(pathold);
  if (d)
  {
      while ((dir = readdir(d)) != NULL)
      {
          printf("%s\n", dir->d_name);
          oldname = dir->d_name;
          if (oldname[0] != '.'){
              uid = MAILadd (0,0,0);
              printf ("%d", uid);
              newname = MAILgetname (uid);
              printf ("(%s,%s)", newname,oldname);
              pathn = malloc(strlen(newname)+strlen(pathnew)+1);
              strcpy(pathn, pathnew);
              strcat(pathn, newname);
              printf ("\n%s\n", pathn);
              patho = malloc(strlen(oldname)+strlen(pathold)+1);
              strcpy(patho, pathold);
              strcat(patho, oldname);
              printf ("\n%s\n", patho);
              ret = rename (patho, pathn);
              if(ret == 0) {
                printf("File renamed successfully\n");
              }
              else {
                printf("Error: unable to rename the file\n");
              }

          }
      }
      closedir(d);
  }

}

int *MAILstatus (int uid) {
  int *v = malloc (3 * sizeof (int));
  char *nm = malloc (100 * sizeof (char));
  char *name = MAILgetname (uid);
  memset(nm, '\0', sizeof(nm));
  strcpy(nm, name);
  free(name);
  int flag = 0, i = 0;
  printf ("%s", nm);
  while (nm[i] != '\0') {
    if (nm[i] == '_' && flag == 0) {
      v[0] = nm[i+1]-48;
      flag++;
    }
    else if (nm[i] == '_' && flag == 1) {
      v[1] = nm[i+1]-48;
      flag++;
    }
    else if (nm[i] == '_' && flag == 2) {
      v[2] = nm[i+1]-48;
      flag++;
    }
    i++;
  }
  free(nm);
  return v;
}

void toMAILseen (int uid) {
  MAILupdate (uid, 1, 0, 0);
}

void toMAILunseen (int uid) {
  MAILupdate (uid, 0, 0, 0);
}

void toMAILdelete (int uid) {
  MAILupdate (uid, 1, 1, 1);
}

void toMAILundelete (int uid) {
  MAILupdate (uid, 1, 0, 0);
}

int isMAILseen (int uid) {
  int *v = MAILstatus (uid);
  if (v[0] == 1) {
    free (v);
    return 1;
  }
  else {
    free (v);
    return 0;
  }
}

int isMAILunseen (int uid) {
  int *v = MAILstatus (uid);
  if (v[0] == 0) {
    free (v);
    return 1;
  }
  else {
    free (v);
    return 0;
  }
}

int isMAILdelete (int uid) {
  int *v = MAILstatus (uid);
  if (v[1] == 1) {
    free (v);
    return 1;
  }
  else {
    free (v);
    return 0;
  }
}

char *getMAILpath (int uid) {
  char *temp = STRINGconcatenate(getUSERpath (), "/Maildir/cur/");
  char *email_name = MAILgetname (uid);
  char *path = STRINGconcatenate (temp, email_name);
  free(email_name);
  free(temp);
  return path;
}
