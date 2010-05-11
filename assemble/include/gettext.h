#ifndef __GETTEXT__
#define __GETTEXT__

#include <libintl.h> 
#include <locale.h>

#define _(string) gettext(string)
#define PROGRAM_NAME _("Systolic array emulator")

#endif

/* EOF */
