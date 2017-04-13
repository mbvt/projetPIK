# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>


/*
gboolean *key_event(GtkWidget *widget, GdkEventKey *event)
{
  char *c = gdk_keyval_name(event->keyval);	
  printf("%s\n", c);
  return FALSE;
}
*/

int main(int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *label;
  char *ptr_char = malloc(50*sizeof(char));

  gtk_init (&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  label = gtk_label_new("Hello ta mere !!!!");
  gtk_container_add(GTK_CONTAINER(window), label);

  //g_signal_connect(window, "key-release-event", G_CALLBACK(key_event), NULL);
  scanf("%s\n", ptr_char);
  printf("lettre saisie : %s\n", ptr_char);
  //gtk_container_add(GTK_CONTAINER(window), ptr_char); 


  gtk_widget_show_all(window);

  gtk_main ();

  return 0;
}
