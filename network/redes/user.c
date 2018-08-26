#include "user.h"

char *user_logged = NULL;

struct stat st = {0};

int user_id = -1;

struct stat getst() {
  return st;
}

static char *STRINGconcatenate (char *str1, char *str2) {
  char *path;
  path = malloc(strlen(str1)+strlen(str2)+1);
  strcpy(path, str1);
  strcat(path, str2);
  return path;
}

static char *STRINGremovequote (char *s) {
    int i;
    int n = strlen (s);
    char *new = malloc ((n - 1) * sizeof(char));
    for (i = 1; i < n - 1; i++)
        new[i - 1] = s[i];
    new[i -1] = 0;
    return new;
}

int *getUSERmails () {
  int *v = malloc ((getMAILqtd() + 1) * sizeof (int));
  char *temp;
  DIR *d;
  int i =0;
  struct dirent *dir;
  char *newname, *oldname;
  char *pathnew, *pathold;
  char *pathn, *patho;
  char *user = getUSERpath ();

  pathnew = STRINGconcatenate(user, "/Maildir/cur/");
  pathold = STRINGconcatenate(user, "/Maildir/cur/");
  int k = 0;
  int uid, ret = 0;
  d = opendir(pathold);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      oldname = dir->d_name;
      if (oldname[0] != '.'){
        temp = malloc ((strlen(oldname) + 1) * sizeof (char));
        for (k = 0; oldname[k] != '_'; k++) {
          temp[k] = oldname[k];
        }
        temp[k] = '\0';
        printf ("[%s]",temp);
        v[i] = atoi(temp);
        i++;
      }
    }
  }
  return v;
}

static void USERname () {
  user_logged = getUSERname (getUSERcurrent());
}

static int fpeek(FILE * const fp) {
  const int c = getc(fp);
  return c == EOF ? EOF : ungetc(c, fp);
}

char *getUSERname (int us_id) {
  if (us_id == -1) return NULL;
  FILE *users = fopen ("users", "r");
  int i = 0, id = 0, end = 0;
  char c = 0, nextc = 0, *username;
  username = malloc (2000 * sizeof (char));
  us_id = user_id;
  while ((c = fgetc(users)) != EOF) {
    nextc = fpeek (users);
    if (id == us_id) {
      end = 1;
      username[i++] = c;
    }
    if (c == ' ' && end == 1) break;
    if (c == '\n') id++;
  }
  username[i] = '\0';
  return username;
}

void USERinit () {
  FILE *subscribe, *uidlist;
  char *user = user_logged;//USERname()
  char *path = STRINGconcatenate ("./",user);
  char *ls, *uidls, *maildir, *folder;
  if (stat(path, &st) == -1) {
      mkdir(path, 0700);
      maildir = STRINGconcatenate (path, "/Maildir/");
      mkdir(maildir, 0700);
      ls = STRINGconcatenate (path, "/Maildir/lists");
      subscribe = fopen(ls, "w");
      fprintf (subscribe, "INBOX\nInbox\n");
      fclose (subscribe);
      uidls = STRINGconcatenate (path, "/Maildir/uidlist");
      uidlist = fopen(uidls, "w");
      fprintf (uidlist, "N1\n");
      fprintf (uidlist, "         ");
      fprintf (uidlist, "         ");
      fprintf (uidlist, "         ");
      fprintf (uidlist, "         ");
      fprintf (uidlist, "         \n");
      fclose (uidlist);
      folder = STRINGconcatenate(maildir, "/new/");
      mkdir(folder, 0700);
      folder = STRINGconcatenate(maildir, "/tmp/");
      mkdir(folder, 0700);
      folder = STRINGconcatenate(maildir, "/cur/");
      mkdir(folder, 0700);
      free (folder);
      free(ls);
      free(uidls);

  }
  free(path);
}

void USERlogout (){
  user_id = -1;
}

int USERlogin(char *username, char *password) {
  FILE *users = fopen ("users", "r");
  int i = 0, user = 0, pass = 0, id = 0;
  char c = 0, nextc = 0;
  username = STRINGremovequote(username);
  password = STRINGremovequote(password);
  while ((c = fgetc(users)) != EOF) {
    nextc = fpeek (users);
    if (user == 0 && username[i] == c) {
      i++;
      if (i == strlen(username) && nextc == ' ') {
        user = 1;
        i = 0;
      }
    }
    else if (user == 0) i = 0;
    else if (user == 1 && password[i] == c) {
      i++;
      if (i == strlen(password) && (nextc == '\r' || nextc == '\n')) {
        pass = 1;
        i = 0;
      }
    }
    else if (pass == 0) i = 0;
    if (pass) break;
    if (!pass && c == '\n') {user = 0; pass = 0;id++;}
  }
  fclose (users);
  if (pass) {
    user_id = id;
    USERname();
    return id;
  }
  else {
    user_id = -1;
    USERname();
    return -1;
  }
}

int getUSERcurrent () {
  return user_id;
}

void setUSERcurrent (int id) {
  user_id = id;
}


char *getUSERpath () {
  int id;
  id = getUSERcurrent ();
  char *path = STRINGconcatenate ("./", getUSERname (id));
  return path;
}
