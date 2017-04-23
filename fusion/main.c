# include "main.h"


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
  entryP = GTK_ENTRY(gtk_builder_get_object(builder, "entryP"));
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

  g_signal_connect(UCO , "activate", G_CALLBACK(on_Game_clicked), UCO);
  g_signal_connect(UCN , "activate", G_CALLBACK(on_Game_clicked), UCN);
  g_signal_connect(HO  , "activate", G_CALLBACK(on_Game_clicked), HO);
  g_signal_connect(HN  , "activate", G_CALLBACK(on_Game_clicked), HN);
  g_signal_connect(Dalt, "activate", G_CALLBACK(on_Game_clicked), Dalt);
  g_signal_connect(Mot , "activate", G_CALLBACK(on_Game_clicked), Mot);


  D  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "D"));
  I  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "I"));
  E  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "E"));
  M1 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "M1"));
  M2 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "M2"));
  M3 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "M3"));
  N1 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "N1"));
  N2 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "N2"));
  N3 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "N3"));


  g_signal_connect(D , "activate", G_CALLBACK(on_validercat_clicked), D);
  g_signal_connect(I , "activate", G_CALLBACK(on_validercat_clicked), I);
  g_signal_connect(E , "activate", G_CALLBACK(on_validercat_clicked), E);
  g_signal_connect(M1, "activate", G_CALLBACK(on_validercat_clicked), M1);
  g_signal_connect(M2, "activate", G_CALLBACK(on_validercat_clicked), M2);
  g_signal_connect(M3, "activate", G_CALLBACK(on_validercat_clicked), M3);
  g_signal_connect(N1, "activate", G_CALLBACK(on_validercat_clicked), N1);
  g_signal_connect(N2, "activate", G_CALLBACK(on_validercat_clicked), N2);
  g_signal_connect(N3, "activate", G_CALLBACK(on_validercat_clicked), N3);


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

  struct S_MYSQL *smysql = NULL;
  smysql = connect_db(smysql);
  smysql->table_name = "pik_user";

  const char *pp, *nn;
  pp = gtk_entry_get_text(GTK_ENTRY(entry));
  nn = gtk_entry_get_text(GTK_ENTRY(entryP));

  char *f = (char *)pp;
  char *n = (char *)nn;


  if(exist_user(f, n, smysql))
  {
    gtk_label_set_text(testCo, f);
    gtk_stack_set_visible_child_name(GTK_STACK(IHM), "CatePage");
  }

  gtk_label_set_text(errCo, "Nom d'utilisateur non trouvé");
}

void on_Game_clicked()
{

  struct S_MYSQL *smysql = NULL;
  smysql = connect_db(smysql);
  smysql->table_name = "pik_user";

  struct user *user = calloc(1,sizeof(struct user));
  user = calloc(1, sizeof(struct user));


  int category = 1;
  int status;


  const char *na = gtk_entry_get_text(GTK_ENTRY(name));
  const char *fa = gtk_entry_get_text(GTK_ENTRY(firstname));
  const char *aa = gtk_entry_get_text(GTK_ENTRY(age));

  char *n = (char *)na;
  char *f = (char *)fa;
  int a = (int)atoi(aa);

  status = (a > 16)?  1 :  2;

  if(!exist_user(n, f, smysql))
  {
    int id_user = 0;
    user->firstname = f;
    user->name = n;
    user->age = a;
    user->status = status;
    user->category = category;

    if ((id_user = insert_user(user, smysql)) == 0)
    {
      err(1, "error while inserting user");
    }
    else
    {
      user = get_user(user->name, user->firstname, smysql);
    }
  }
  else
  {
    printf("User already exists\n");
    user = get_user(n, f, smysql);
  }


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

const char *tmp;

static gboolean *key_event()//GtkWidget *widget, GdkEventKey *event)
{
  //char *c = gdk_keyval_name(event->keyval);
  //printf("%s\n", c);
  size_t cpt = 0;
  const char *c = gtk_entry_get_text(GTK_ENTRY(entryok));
  const gchar *str = gtk_label_get_text(typed);
  tmp = gtk_entry_get_text(GTK_ENTRY(entryok));
  size_t l = strlen(c);
  size_t le = strlen(tmp);
  size_t len = strlen(str);
  char *pts = calloc(10, sizeof(char));
  if(cpt < len)
  {
    for(size_t j = 0; j < le; j++)
    {
      if(tmp[j] != c[j])
        cpt--;
    }
    for(size_t i = 0; i < l; i++)
    {
      if(str[i] == c[i])
        cpt++;
      else if(str[i] != c[i])
        cpt--;
    }
  }

  sprintf(pts, "%zu", cpt);
  gtk_label_set_text(ok, pts);
  return FALSE;
}
void on_validercat_clicked()
{
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(D)) )
    printf("Débutant\n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(I)) )
    printf("Intermédiaire \n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(E)) )
    printf("Expert \n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(M1)) )
    printf("Monde 1 \n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(M2)) )
    printf("Monde 2 \n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(M3)) )
    printf("Monde 3 \n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(N1)) )
    printf("Niveau 1 \n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(N2)) )
    printf("Niveau 2 \n");
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(N3)) )
    printf("Niveau 3 \n");

  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "GamePage");

  g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(key_event), NULL);
}


void on_cateba_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MainPage");
}

void on_gameback1_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "CatePage");
}



/*-----------------------------QUIT BUTTON-------------------------------------
 *---------------------------------------------------------------------------*/

void on_quit_clicked(){ gtk_main_quit(); }

void on_coquit_clicked(){ gtk_main_quit(); }

void on_insquit_clicked(){ gtk_main_quit(); }

void on_QcmQuit_clicked(){ gtk_main_quit(); }

void on_TCPQuit_clicked(){ gtk_main_quit(); }

void on_MainWindow_main_destroy(){ gtk_main_quit(); }

void on_gameQuit_clicked(){ gtk_main_quit(); }

void on_catequi_clicked(){ gtk_main_quit(); }

void on_gameQuit1_clicked(){ gtk_main_quit(); }
