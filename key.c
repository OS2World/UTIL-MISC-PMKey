/* key.c */

#include <os2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "opie_cfg.h"
#include "opie.h"
#include "key.h"


/* BOOL KeyParseChallenge(CString challenge, int &algorithm, int &sequence, CString &seed) */
int KeyParseChallenge(const char *challenge, 
                      int *algorithm, int *sequence, char *seed)
{
    static char s[256];
    static char mesg[64];
    char *t;

    if (*challenge == '\0')
    {
        return 0;
    }

    strcpy(s, challenge);

    /* parse algorithm */
    t = strtok(s, " ");
    if (t == NULL) {
        return 0;
    }
    if (!stricmp(t, "otp-md4") || !stricmp(t, "md4")) {
        *algorithm = 4;
        t = strtok(NULL, " ");
    }
    else if (!stricmp(t, "otp-md5") || !stricmp(t, "md5")) {
        *algorithm = 5;
        t = strtok(NULL, " ");
    }
    else
        *algorithm = -1;

    /* parse sequence number */
    if (t == NULL) {
        return 0;
    }
    *sequence = atoi(t);
    if (*sequence < 1) {
        sprintf(mesg, "seq=%d, t=%s", *sequence, t);
        return 0;
    }
   
    /* parse seed */
    t = strtok(NULL, " ");
    if (t == NULL) {
        return 0;
    }
    strcpy(seed, t);   

    return 1;
}


/* BOOL KeyGenerateResponse(int algorithm, int keynum, CString &seed, CString &password, CString &response) */
int KeyGenerateResponse(int algorithm, int keynum, const char *seed, 
                        const char *password, char *response)
{
    char key[8], buf[33];   

    /* Crunch seed and secret password into starting key normally */
    if (opiekeycrunch((unsigned)algorithm, key, (char *)seed,
                      (char *)password) != 0)
        return 0;

    while (keynum-- != 0)
        opiehash(key, algorithm);

    strcpy(response, opiebtoe(buf, key));

    return 1;
}
