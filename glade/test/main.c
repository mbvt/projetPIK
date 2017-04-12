# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>

static int key_event(GtkWidget *widget, GdkEventKey *event)
{
  g_printerr("%s\n", gdk_keyval_name (event->keyval));
  return event->keyval;
  //return FALSE;
}

int main(int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *label;

  gtk_init (&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(window, "key-release-event", G_CALLBACK(key_event), NULL);

  printf("%d", key_event);

  label = gtk_label_new("");
  gtk_container_add(GTK_CONTAINER(window), label);


  gtk_widget_show (window);

  gtk_main ();

  return 0;
}
