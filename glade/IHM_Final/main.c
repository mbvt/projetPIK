# include "main.h"
/*
void on_UCO_clicked();
void on_UCN_clicked();
void on_HO_clicked();
void on_HN_clicked();
void on_Dalt_clicked();
void on_Mot_clicked();
*/


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

  testCo = GTK_LABEL(gtk_builder_get_object(builder, "testCo"));
  errCo  = GTK_LABEL(gtk_builder_get_object(builder, "errCo"));

  name      = GTK_ENTRY(gtk_builder_get_object(builder, "name"));
  firstname = GTK_ENTRY(gtk_builder_get_object(builder, "firstname"));
  age       = GTK_ENTRY(gtk_builder_get_object(builder, "age"));

  g_signal_connect(entry, "activate", G_CALLBACK(on_qcm_clicked), name);
  g_signal_connect(entry, "activate", G_CALLBACK(on_qcm_clicked), firstname);
  g_signal_connect(entry, "activate", G_CALLBACK(on_qcm_clicked), age);

  UCO  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "UCO"));
  UCN  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "UCN"));
  HO   = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "HO"));
  HN   = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "HN"));
  Dalt = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "UCO"));
  Mot  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "UCO"));

  g_signal_connect(entry, "activate", G_CALLBACK(on_Game_clicked), UCO);
  g_signal_connect(entry, "activate", G_CALLBACK(on_Game_clicked), UCN);
  g_signal_connect(entry, "activate", G_CALLBACK(on_Game_clicked), HO);
  g_signal_connect(entry, "activate", G_CALLBACK(on_Game_clicked), HN);
  g_signal_connect(entry, "activate", G_CALLBACK(on_Game_clicked), Dalt);
  g_signal_connect(entry, "activate", G_CALLBACK(on_Game_clicked), Mot);

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
  const char *n = gtk_entry_get_text(GTK_ENTRY(name));
  const char *f = gtk_entry_get_text(GTK_ENTRY(firstname));
  const char *a = gtk_entry_get_text(GTK_ENTRY(age));
  printf("Nom    : %s\n", n);
  printf("Prénom : %s\n", f);
  printf("Age    : %s ans\n", a);

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
  char *te = "Morgan";

  sText = gtk_entry_get_text(GTK_ENTRY(entry));


  if(*sText == *te)
  {
    gtk_label_set_text(testCo, sText);
    printf("Nom d'utilisateur saisi : %s\n", sText);
    gtk_stack_set_visible_child_name(GTK_STACK(IHM), "TestCoPage");
  }

  else
  {
    gtk_label_set_text(errCo, "Nom d'utilisateur non trouvé");
  }

}

void on_Game_clicked()
{
  int ok = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(UCO));
  if(ok == 1)
    printf("Ca marhce");
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "TestInsPage");
}


/*
void on_UCO_clicked()
{
  if(UCO)
    printf("J'ai déjà utilisé un clavier\n");
}

void on_UCN_clicked()
{
  if(UCN)
    printf("Je n'ai pas utilisé un clavier\n");
}
void on_HO_clicked()
{
  if(HO)
    printf("J'ai un Handicape\n");
}
void on_HN_clicked()
{
  if(HN)
    printf("Je n'ai pas d'Hanidcape\n");
}
void on_Dalt_clicked()
{
  if(Dalt)
    printf("Je suis daltonien\n");
}
void on_Mot_clicked()
{
  if(Mot)
    printf("J'ai des problèmes de motricité \n");
}
*/

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

void on_TCPQuit_clicked()
{
  gtk_main_quit();
}

void on_MainWindow_main_destroy()
{
  gtk_main_quit();
}
