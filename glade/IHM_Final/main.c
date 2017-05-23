# include "main.h"


GtkLabel *typed, *ok;
GtkEntry *entryok;

//extern char dst[1024];
int cpt = 0;
int score = 0;
char *tmp;
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
  ok = GTK_LABEL(gtk_builder_get_object(builder, "ok"));

  entryok = GTK_ENTRY(gtk_builder_get_object(builder, "entryok"));
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
  /*
     const char *n = gtk_entry_get_text(GTK_ENTRY(name));
     const char *f = gtk_entry_get_text(GTK_ENTRY(firstname));
     const char *a = gtk_entry_get_text(GTK_ENTRY(age));
     printf("Nom    : %s\n", n);
     printf("Prénom : %s\n", f);
     printf("Age    : %s ans\n", a);
     */
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "QcmPage");

  /*
     gtk_entry_set_text(name, "");
     gtk_entry_set_text(firstname, "");
     gtk_entry_set_text(age, "");
     */
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

  const char *n = gtk_entry_get_text(GTK_ENTRY(name));
  const char *f = gtk_entry_get_text(GTK_ENTRY(firstname));
  const char *a = gtk_entry_get_text(GTK_ENTRY(age));
  printf("Nom    : %s\n", n);
  printf("Prénom : %s\n", f);
  printf("Age    : %s ans\n", a);

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

  g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(key_event), NULL);

  //gtk_label_set_text(typed, "Bonjour");


  //gtk_label_set_text(typed, "");

  gtk_entry_set_text(name, "");
  gtk_entry_set_text(firstname, "");
  gtk_entry_set_text(age, "");

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

int compare(char *s1, char *s2)
{
  if(strlen(s1) != strlen(s2))
    return 0;

  for (size_t i = 0 ; i< strlen(s1) ; i++)
  {
    if (s1[i] != s2[i])
      return 0;
  }
  return 1;
}

static gboolean *key_event(GtkWidget *widget, GdkEventKey *event)
{
  char *c = gdk_keyval_name(event->keyval);
  const gchar *cs1 = gtk_entry_get_text(GTK_ENTRY(entryok));
  const gchar *str = gtk_label_get_text(typed);

  char *pts = calloc(10, sizeof(char));
  char *cs = (char*)cs1;
  size_t l = strlen(cs);
  char *rep = calloc(l,sizeof(char));

  rep = strncpy(rep,str,l);
  int b = 0;
  int len = strlen(str);
  char c2 = c[0];

  if(cpt < len)
  {
    if(c2 !=66)
    {
      b  = compare(rep,cs);
      if (b ==1)
      {
        score++;
        cpt++;
      }
      else
      {
        score -=1;
        cpt--;
      }
    }
    else
    {
      score--;
      cpt--;
    }
  }

  sprintf(pts, "%d", score);
  gtk_label_set_text(ok, pts);
  return FALSE;
}


/*-----------------------------QUIT BUTTON-------------------------------------
 *---------------------------------------------------------------------------*/
/*
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
*/



