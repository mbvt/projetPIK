# include "main.h"


GtkLabel *typed;


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
  TestInsPage  = GTK_WIDGET(gtk_builder_get_object(builder, "TestInsPage"));

  typed = GTK_LABEL(gtk_builder_get_object(builder, "typed"));

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
  Dalt = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "Dalt"));
  Mot  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "Mot"));

  g_signal_connect(UCO, "activate", G_CALLBACK(on_Game_clicked), UCO);
  g_signal_connect(UCN, "activate", G_CALLBACK(on_Game_clicked), UCN);
  g_signal_connect(HO, "activate", G_CALLBACK(on_Game_clicked), HO);
  g_signal_connect(HN, "activate", G_CALLBACK(on_Game_clicked), HN);
  g_signal_connect(Dalt, "activate", G_CALLBACK(on_Game_clicked), Dalt);
  g_signal_connect(Mot, "activate", G_CALLBACK(on_Game_clicked), Mot);

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

  gtk_entry_set_text(name, "");
  gtk_entry_set_text(firstname, "");
  gtk_entry_set_text(age, "");

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

  //GtkWidget *widget;
  //GdkEventKey *event;

  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(UCO)) )
    printf("J'ai déjà utilisé un clavier\n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(UCN)) )
    printf("Je n'utilise pas souvent de clavier\n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(HO)) )
    printf("Je suis handicapé\n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(HN)) )
    printf("Je n'ai pas d'handicape\n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Dalt)) )
    printf("Je suis daltonien\n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Mot)) )
    printf("J'ai des problèmes de motricité\n");

  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "TestInsPage");

  //char arrays[12];
  //char *pointers= malloc(50*sizeof(char));
  //scanf("%s",pointers);
  //printf("%s\n",pointers);
  //char *c = key_event(GtkWidget *widget, GdkEventKey *event);
  //const gchar c = getchar();
  //printf("%c", c);
  //g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(key_event), NULL);
  //const gchar *c = key_event(GtkWidget *widget, GdkEventKey *event);

  //char *array = malloc(10*sizeof(char));

  gtk_label_set_text(typed, "");
  gtk_container_add(GTK_CONTAINER(MainWindow), GTK_WIDGET(typed));

  gchar *test = calloc(7, sizeof(gchar));
  gchar *tmp = calloc(1, sizeof(gchar));
  gchar *array = "Vincent";

  for(int i = 0; i < 7; i++)
  {
    tmp[0] = array[i];
    strcat(test, tmp);
    printf("%s\n", test);
    gtk_label_set_text(typed, test);
    gtk_container_add(GTK_CONTAINER(TestInsPage), GTK_WIDGET(typed));
    gtk_widget_queue_draw(TestInsPage);
    tmp = calloc(1, sizeof(gchar));
    sleep(2);
  }


  gtk_toggle_button_set_active(UCO, FALSE);
  gtk_toggle_button_set_active(UCN, FALSE);
  gtk_toggle_button_set_active(HO, FALSE);
  gtk_toggle_button_set_active(HN, FALSE);
  gtk_toggle_button_set_active(Dalt, FALSE);
  gtk_toggle_button_set_active(Mot, FALSE);
}

void on_gameback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "QcmPage");
}


/*
char *key_event(GtkWidget *widget, GdkEventKey *event)   {
  char *c = gdk_keyval_name(event->keyval);
  printf("%s\n", c);
  return c;
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

void on_gameQuit_clicked()
{
  gtk_main_quit();
}




