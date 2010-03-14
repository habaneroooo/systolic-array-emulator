#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../include/interface.h"

int main(int argc, char *argv[])
{
	/* Initialisation de GTK+ */
	gtk_init (&argc, &argv);
	
	GdkScreen* screen = gdk_screen_get_default ();
	/* Création des sous-fenetres */
	
	/* Creation de la fenetre principale */
	fCreateWindow_main(screen);
	
	/* Lancement de la boucle principale */
	gtk_main ();
	return EXIT_SUCCESS;
}
