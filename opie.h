/* opie.h: Data structures and values for the OPIE authentication
	system that a program might need.

Portions of this software are Copyright 1996 by Craig Metz, All Rights
Reserved. The Inner Net Copyright Notice and License Agreement applies to
these portions of the software.

Portions of this software are Copyright 1995 by Randall Atkinson and Dan
McDonald, All Rights Reserved. All Rights under this copyright are assigned
to the U.S. Naval Research Laboratory (NRL). The NRL Copyright Notice and
License Agreement applies to this software.

	History:

	Modified by cmetz for OPIE 2.2. Re-did prototypes. Added FUNCTION
                definition et al. Multiple-include protection. Added struct
		utsname fake. Got rid of gethostname() cruft. Moved UINT4
                here. Provide for *seek whence values. Move MDx context here
                and unify. Re-did prototypes.
	Modified at NRL for OPIE 2.0.
	Written at Bellcore for the S/Key Version 1 software distribution
		(skey.h).
*/
#ifndef _OPIE_H
#define _OPIE_H

#if _OPIE

#if HAVE_VOIDPTR
#define PTR void *
#else /* HAVE_VOIDPTR */
#define PTR char *
#endif /* HAVE_VOIDPTR */

#if HAVE_VOIDRET
#define VOIDRET void
#else /* HAVE_VOIDRET */
#define VOIDRET
#endif /* HAVE_VOIDRET */

#if HAVE_VOIDARG
#define NOARGS void
#else /* HAVE_VOIDARG */
#define NOARGS
#endif /* HAVE_VOIDARG */

#if HAVE_ANSIDECL
#define FUNCTION(arglist, args) (args)
#define AND ,
#else /* HAVE_ANSIDECL */
#define FUNCTION(arglist, args) arglist args;
#define AND ;
#endif /* HAVE_ANSIDECL */

#define FUNCTION_NOARGS ()

#ifndef __P
#if HAVE_ANSIPROTO
#define __P(x) x
#else /* HAVE_ANSIPROTO */
#define __P(x) ()
#endif /* HAVE_ANSIPROTO */
#endif /* __P */

#ifndef HAVE_SYS_UTSNAME_H
struct utsname {
	char nodename[65];
	};
#endif /* HAVE_SYS_UTSNAME_H */

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 1024
#endif /* MAXHOSTNAMELEN */

#else /* _OPIE */
#ifdef __STDC__
#define VOIDRET void
#else /* __STDC__ */
#define VOIDRET
#endif /* __STDC__ */
#endif /* _OPIE */

#ifndef __P
#ifdef __ARGS
#define __P __ARGS
#else /* __ARGS */
#ifdef __STDC__
#define __P(x) (x)
#else /* __STDC__ */
#define __P(x) ()
#endif /* __STDC__ */
#endif /* __ARGS */
#endif /* __P */

/* Server library's internal state block.
   Code outside libopie.a should treat this as an opaque data block and
   should not ever manipulate this structure in any way. Its format is
   subject to change in future versions of OPIE.
*/
struct opie {
  void *keyfile;
  char buf[256];
  char *logname;
  int n;
  char *seed;
  char *val;
  long recstart;	/* needed so reread of buffer is efficient */
};

/* Minimum length of a secret password */
#ifndef OPIE_PASS_MIN
#define OPIE_PASS_MIN 10
#endif	/* OPIE_PASS_MIN */

/* Maximum length of a secret password */
#ifndef OPIE_PASS_MAX
#define OPIE_PASS_MAX 127
#endif	/* OPIE_PASS_MAX */

/* Minimum length of a seed */
#ifndef OPIE_SEED_MIN
#define OPIE_SEED_MIN 5
#endif	/* OPIE_SEED_MIN */

/* Maximum length of a seed */
#ifndef OPIE_SEED_MAX
#define OPIE_SEED_MAX 16
#endif	/* OPIE_SEED_MAX */

/* Maximum length of a challenge (otp-md? 9999 seed) */
#ifndef OPIE_CHALLENGE_MAX
#define OPIE_CHALLENGE_MAX (7+1+4+1+OPIE_SEED_MAX)
#endif	/* OPIE_CHALLENGE_MAX */

/* Maximum length of a response (six words up to four chars each w/spaces) */
#ifndef OPIE_RESPONSE_MAX
#define OPIE_RESPONSE_MAX (6*4+5)
#endif	/* OPIE_RESPONSE_MAX */

/* Maximum length of a principal (read: user name) */
#ifndef OPIE_PRINCIPAL_MAX
#define OPIE_PRINCIPAL_MAX 32
#endif	/* OPIE_PRINCIPAL_MAX */

#ifndef __alpha
#define UINT4 unsigned long
#else   /* __alpha */
#define UINT4 unsigned int 
#endif  /* __alpha */

struct opiemdx_ctx {
	UINT4 state[4];
	UINT4 count[2];
	unsigned char buffer[64];
};

#ifndef SEEK_SET
#define SEEK_SET 0
#endif /* SEEK_SET */

#ifndef SEEK_END
#define SEEK_END 2
#endif /* SEEK_END */

int  opieaccessfile __P((char *));
int  rdnets __P((long));
int  isaddr __P((register char *));
int  opiealways __P((char *));
int  opieatob8 __P((char *,char *));
VOIDRET  opiebackspace __P((char *));
int  opiebtoa8 __P((char *,char *));
char * opiebtoe __P((char *,char *));
int  opieetob __P((char *,char *));
int  opiechallenge __P((struct opie *,char *,char *));
int  opiegenerator __P((char *,char *,char *));
int  opiegetsequence __P((struct opie *));
VOIDRET  opiehash __P((char *,unsigned));
int  opiehtoi __P((register char));
int  opiekeycrunch __P((unsigned,char *,char *,char *));
int  opielock __P((char *));
int  opielookup __P((struct opie *,char *));
VOIDRET  opiemd4init __P((struct opiemdx_ctx *));
VOIDRET  opiemd4update __P((struct opiemdx_ctx *,unsigned char *,unsigned int));
VOIDRET  opiemd4final __P((unsigned char *,struct opiemdx_ctx *));
VOIDRET  opiemd5init __P((struct opiemdx_ctx *));
VOIDRET  opiemd5update __P((struct opiemdx_ctx *,unsigned char *,unsigned int));
VOIDRET  opiemd5final __P((unsigned char *,struct opiemdx_ctx *));
int  opiepasscheck __P((char *));
VOIDRET  opierandomchallenge __P((char *));
char * opieskipspace __P((register char *));
VOIDRET  opiestripcrlf __P((char *));
int  opieverify __P((struct opie *,char *));

#endif /* _OPIE_H */
