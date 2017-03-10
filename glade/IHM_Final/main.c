# include <stdlib.h>
# include <stdio.h>
# include <gtk/gtk.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>


GtkWidget  *label;
GtkWidget  *Connexion;
GtkWidget  *Inscription;
GtkWidget  *MainWindow;
GtkWidget  *CoWindow;
GtkWidget  *InsWindow;
GtkWidget  *IHM;
GtkWidget  *CoEntry;
GtkEntry   *entry;
GtkBuilder *builder;


void on_Connexion_clicked();
void on_Inscription_clicked();
void on_connback_clicked();
void on_insback_clicked();
void on_qcm_clicked();
void on_CoEntry_clicked();

/*----------------------------------MAIN---------------------------------------
 *---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "IHM_final.glade", NULL);

  MainWindow  = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
  IHM         = GTK_WIDGET(gtk_builder_get_object(builder, "IHM"));
  gtk_builder_connect_signals(builder, NULL);


  entry = GTK_ENTRY(gtk_builder_get_object(builder, "entry"));
  g_signal_connect(entry, "activate", G_CALLBACK(on_CoEntry_clicked), entry);


  g_object_unref (G_OBJECT (builder));
  
  gtk_widget_show(MainWindow);
  gtk_main();

  return 0;
}



/*-----------------------------STACK BUTTON-----------------------------------
 *---------------------------------------------------------------------------*/
void on_Connexion_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "ConnPage");
}

void on_Inscription_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "InscriPage");
}

void on_qcm_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "QcmPage");
}

void on_connback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MainPage");
}

void on_insback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MainPage");
}

void on_qcmback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "InscriPage");
}


void on_CoEntry_clicked()
{
  const char *sText;
  sText = gtk_entry_get_text(GTK_ENTRY(entry));
  printf("Nom d'utilisateur saisi : %s\n", sText);
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "TestCoPage");

}

/*-----------------------------QUIT BUTTON-------------------------------------
 *---------------------------------------------------------------------------*/
void on_quit_clicked()
{
  gtk_main_quit();
}

void on_coquit_clicked()
{
  gtk_main_quit();
}

void on_insquit_clicked()
{
  gtk_main_quit();
}

void on_QcmQuit_clicked()
{
  gtk_main_quit();
}

void on_MainWindow_main_destroy()
{
  gtk_main_quit();
}

