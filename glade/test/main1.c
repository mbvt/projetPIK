# include <stdlib.h>
# include <gtk/gtk.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

//GdkPixbuf *p;
GtkWidget *label;
GtkWidget *Connexion;
GtkWidget *Inscription;
GtkWidget *MainWindow;
GtkWidget *CoWindow;
GtkWidget *InsWindow;
GtkWidget *test;

int p = 0;

//gchar *new;

int main(int argc, char *argv[])
{


  GtkBuilder *builder;

  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "test.glade", NULL);


  MainWindow  = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
  Connexion   = GTK_WIDGET(gtk_builder_get_object(builder, "Connexion"));
  Inscription = GTK_WIDGET(gtk_builder_get_object(builder, "Inscription"));
  test        = GTK_WIDGET(gtk_builder_get_object(builder, "test"));
  gtk_builder_connect_signals(builder, NULL);

  g_object_unref(G_OBJECT(builder));

  gtk_widget_show(MainWindow);
  gtk_main();

  return 0;
}

void on_Connexion_clicked()
{
  if(p == 0)
    gtk_stack_set_visible_child_name(GTK_STACK(test), "page1");
  else
    gtk_stack_set_visible_child_name(GTK_STACK(test), "page0");
}


/*
void on_Connexion_clicked()
{
  GtkBuilder *builderco;

  builderco = gtk_builder_new();
  gtk_builder_add_from_file (builderco, "test.glade", NULL);

  CoWindow = GTK_WIDGET(gtk_builder_get_object(builderco, "ww"));
  gtk_builder_connect_signals(builderco, NULL);

  g_object_unref(G_OBJECT(builderco));

  gtk_widget_show(CoWindow);
  gtk_main();

  gtk_widget_destroy(CoWindow);

}
*/

/*
   void on_Inscription_clicked()
   {
   GtkBuilder *builderins;

   builderins = gtk_builder_new();
   gtk_builder_add_from_file (builderins, "inscription.glade", NULL);

   InsWindow = GTK_WIDGET(gtk_builder_get_object(builderins, "InsWindow"));
   gtk_builder_connect_signals(builderins, NULL);

   g_object_unref(G_OBJECT(builderins));

   gtk_widget_show(InsWindow);
   gtk_main();

   gtk_widget_destroy(InsWindow);
   }
   */



void on_quit_clicked()
{
  gtk_main_quit();
}

/*
   void on_quitconnexion_clicked()
   {
   gtk_main_quit();
   }

   void on_quitinscri_clicked()
   {
   gtk_main_quit();
   }


   void on_quitqcm_clicked()
   {
   gtk_main_quit();
   }
   */

void on_MainWindow_main_destroy()
{
  gtk_main_quit();
}



