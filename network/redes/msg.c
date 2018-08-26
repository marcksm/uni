#include "msg.h"

static char *STRINGconcatenate (char *str1, char *str2) {
  char *path;
  path = malloc(strlen(str1)+strlen(str2)+1);
  strcpy(path, str1);
  strcat(path, str2);
  return path;
}

char *MSGstart () {
  char *msg = "* OK [CAPABILITY IMAP4rev1 LITERAL+ SASL-IR LOGIN-REFERRALS ID ENABLE IDLE AUTH=PLAIN] Dovecot ready.";
  return msg;
}

char *MSGend () {
  char *msg = "* BYE IMAP4rev1 Server logging out.\n OK LOGOUT completed.";
  return msg;
}

char *MSGnamespace () {
  char *msg = "* NAMESPACE ((\"\" \".\")) NIL NIL.";
  return msg;
}

char *MSGid () {
  char *msg = "ID (\"MARCOS_E_RODRIGO\", \"EP1\").";
  return msg;
}

char *MSGnoop (double first, double second) {
  char *msg = malloc (100 * sizeof (char));
  sprintf (msg, "OK NOOP completed (%f + %f secs).", first, second);
  return msg;
}

char *MSGidle (int w) {
  char *msg;
  if (w == 1) { msg = "+ idling";}
  if (w == 2) { msg = "* OK Still here.";}
  if (w == 3) { msg = "OK IDLE completed (0.00 + 0.00 secs)."; }//FALTA PARAMETROS
  return msg;
}

char *MSGlist (char *lista) {
    char *msg = STRINGconcatenate ("* LIST (\\\\HasNoChildren) \".\" ", lista);
    return msg;
}
