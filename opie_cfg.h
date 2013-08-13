/* opie_cfg.h: Various configuration-type pieces of information for OPIE.
               Or, at least, the common portion of it.

Portions of this software are Copyright 1995 by Randall Atkinson and Dan
McDonald, All Rights Reserved. All Rights under this copyright are assigned
to the U.S. Naval Research Laboratory (NRL). The NRL Copyright Notice and
License Agreement applies to this software.

	History:

        Modified by cmetz for OPIE 2.2. Got rid of ANSIPROTO and ARGS.
                Got rid of TRUE and FALSE definitions. Moved UINT4 to
                opie.h and removed UINT2.
	Modified at NRL for OPIE 2.1. Fixed sigprocmask declaration.
		Gutted for autoconf. Split up for autoconf.
	Written at NRL for OPIE 2.0.
*/

#define VERSION "2.21 Release"
#define DATE    "Saturday, April 27, 1996"

#define unix 0

#define _OPIE           1
#define HAVE_ANSIPROTO  1
#define HAVE_ANSIDECL   1
#define HAVE_VOIDPTR    1
#define HAVE_VOIDRET    1
#define HAVE_VOIDARG    1

/* If the user didn't specify, default to MD5 */
#ifndef MDX
#define MDX 5
#endif	/* MDX */

#ifndef DOUTMPX
#define DOUTMPX 0
#endif	/* DOUTMPX */

#ifndef UTMPX
#if DOUTMPX
#define UTMPX utmpx
#else	/* DOUTMPX */
#define UTMPX utmp
#endif	/* DOUTMPX */
#endif /* UTMPX */

#ifndef _PATH_BSHELL
#define _PATH_BSHELL    "/bin/sh"
#endif

#ifndef _PATH_DEVNULL
#define _PATH_DEVNULL	  "/dev/null"
#endif

#ifndef _PATH_FTPUSERS
#define	_PATH_FTPUSERS	"/etc/ftpusers"
#endif

#ifndef TTYGRPNAME
#define TTYGRPNAME	"tty"	/* name of group to own ttys */
#endif

#ifndef NO_LOGINS_FILE
#define NO_LOGINS_FILE	"/etc/nologin"
#endif

#ifndef QUIET_LOGIN_FILE
#define QUIET_LOGIN_FILE  ".hushlogin"
#endif

#ifndef OPIE_ALWAYS_FILE
#define OPIE_ALWAYS_FILE ".opiealways"
#endif

#ifndef OPIE_LOCK_PREFIX
#define OPIE_LOCK_PREFIX "/tmp/opie-lock."
#endif

#ifndef OPIE_LOCK_TIMEOUT
#define OPIE_LOCK_TIMEOUT (30*60)
#endif

#ifndef KEY_FILE
#define KEY_FILE          "/etc/opiekeys"
#endif

#ifndef MOTD_FILE
#define MOTD_FILE         "/etc/motd"
#endif

#ifndef SECURETTY
#define SECURETTY         "/etc/securetty"
#endif	/* SECURETTY */

#ifndef NBBY
#define NBBY 8	/* Reasonable for modern systems */
#endif	/* NBBY */

#ifndef LOGIN_PATH
#define LOGIN_PATH "/usr/ucb:/bin:/usr/bin"
#endif	/* LOGIN_PATH */

#ifndef DOANONYMOUS
#define DOANONYMOUS 0
#endif	/* DOANONYMOUS */

#if NEED_ATEXIT
#define atexit(x)
#endif	/* NEED_ATEXIT */

#ifndef POINTER
#define POINTER unsigned char *
#endif /* POINTER */
