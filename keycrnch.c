/* keycrunch.c: The opiekeycrunch() library function.

Portions of this software are Copyright 1996 by Craig Metz, All Rights
Reserved. The Inner Net Copyright Notice and License Agreement applies to
these portions of the software.

Portions of this software are Copyright 1995 by Randall Atkinson and Dan
McDonald, All Rights Reserved. All Rights under this copyright are assigned
to the U.S. Naval Research Laboratory (NRL). The NRL Copyright Notice and
License Agreement applies to this software.

        History:

	Modified by cmetz for OPIE 2.2. Use FUNCTION declaration et al.
               Renamed MDx functions to prevent conflicts. Use unified 
               context structure. Added changes to comply with OTP
               spec: enforce sixteen char seed length limit, make seed
               case insensitive by crunching as lower case. Don't allow
               spaces in seed (shouldn't get here anyway). Check for
               NULL arguments.
        Created at NRL for OPIE 2.2 from opiesubr.c.
*/
#include "opie_cfg.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	/* ANSI C standard library */

#include "opie.h"

/* Crunch a key:
 * concatenate the seed and the password, run through MD4 or MD5 and
 * collapse to 64 bits. This is defined as the user's starting key.
 */
int opiekeycrunch FUNCTION((algorithm, result, seed, passwd), unsigned algorithm AND char *result AND char *seed AND char *passwd)
{
  char *buf;
  struct opiemdx_ctx ctx;
  UINT4 results[4];
  unsigned int buflen;

/* NOTE - we need to bound seed and password before this point.
   "any length" can bite us... */
  if (!seed || !seed[0] || !passwd || !result)
    return 1;

  if ((buflen = strlen(seed)) > OPIE_SEED_MAX) 
    return 1;

  {
  int i;

  for (i = 0; seed[i]; i++)
    if ((seed[i] >= 'A') && (seed[i] <= 'Z'))
      seed[i] += 'a' - 'A';
    else
      if (seed[i] == ' ')
        return 1;
  } 

  buflen += strlen(passwd);
  if ((buf = malloc(buflen + 1)) == NULL)
    return -1;

  strcpy(buf, seed);
  strcat(buf, passwd);

  /* Crunch the key through MD[45] */
  if (4 == algorithm) {
    opiemd4init(&ctx);
    opiemd4update(&ctx, (unsigned char *) buf, buflen);
    opiemd4final((unsigned char *) results, &ctx);
  } else {
    opiemd5init(&ctx);
    opiemd5update(&ctx, (unsigned char *) buf, buflen);
    opiemd5final((unsigned char *) results, &ctx);
  }
  free(buf);

  results[0] ^= results[2];
  results[1] ^= results[3];

  memcpy(result, (char *) results, 8);
  return 0;
}
