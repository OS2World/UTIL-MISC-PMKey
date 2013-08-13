/* hash.c: The opiehash() library function.

Portions of this software are Copyright 1996 by Craig Metz, All Rights
Reserved. The Inner Net Copyright Notice and License Agreement applies to
these portions of the software.

Portions of this software are Copyright 1995 by Randall Atkinson and Dan
McDonald, All Rights Reserved. All Rights under this copyright are assigned
to the U.S. Naval Research Laboratory (NRL). The NRL Copyright Notice and
License Agreement applies to this software.

        History:

	Modified by cmetz for OPIE 2.2. Use FUNCTION declaration et al.
               Renamed MDx functions to prevent conflicts. Changed unsigned
               long to UINT4 for Alpha. Use unified context structure.
        Created at NRL for OPIE 2.2 from opiesubr.c.
*/
#include "opie_cfg.h"

#include <stdio.h>
#include <string.h>

#include "opie.h"

/*
 * The one-way function f(x).
 * Takes 8 bytes and returns 8 bytes in place.
 * The value of "algorithm" determines whether MD4 or MD5 is used,
 * where (algorithm==5) specifies MD5 and (algorithm==4) specifies MD4.
 */
VOIDRET opiehash FUNCTION((x, algorithm), char *x AND unsigned algorithm)
{
  struct opiemdx_ctx ctx;
  UINT4 results[4];

  if (4 == algorithm) {
    opiemd4init(&ctx);
    opiemd4update(&ctx, (unsigned char *) x, 8);
    opiemd4final((unsigned char *) results, &ctx);
  } else {
    opiemd5init(&ctx);
    opiemd5update(&ctx, (unsigned char *) x, 8);
    opiemd5final((unsigned char *) results, &ctx);
  }
  /* Fold 128 to 64 bits */
  results[0] ^= results[2];
  results[1] ^= results[3];

  memcpy(x, (char *)results, 8);
}
