# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>


char *key_event(GtkWidget *widget, GdkEventKey *event)   {
  char *c = gdk_keyval_name(event->keyval);
  printf("%s\n", c);
  return c;
}





int main(int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *label;
  //char *ptr_char = malloc(50*sizeof(char));

  //char arrays[12];
  //char *ptr_char = arrays;

  gtk_init (&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  label = gtk_label_new("Hello ta mere !!!!");
  gtk_container_add(GTK_CONTAINER(window), label);

  char *c = key_event;
  printf("lettre %s", c);

  g_signal_connect(window, "key-release-event", G_CALLBACK(key_event), NULL);

  //gtk_container_add(GTK_CONTAINER(window), ptr_char);


  gtk_widget_show_all(window);

  gtk_main ();

  return 0;
}




/*
   int main()
   {
//char arrays[12];
char *pointers= malloc(50*sizeof(char));
scanf("%s",pointers);
printf("%s\n",pointers);
return 0;
}
*/
