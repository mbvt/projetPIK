# include "main.h"


struct S_GSQL *conn;

/*----------------------------------MAIN---------------------------------------
 *---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

  //struct S_GSQL *conn = NULL;
  //conn->smysql = connect_db(conn->smysql);

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

void on_Game_clicked()//struct user *user, struct S_MYSQL *smysql)
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
  printf("Nom    : %s\n", na);
  printf("Prénom : %s\n", fa);
  printf("Age    : %s ans\n", aa);

  char *n = (char *)na;
  char *f = (char *)fa;
  int a = (int)aa;


  status = (age > 16)?  1 :  2;

  if(!exist_user(n, f, smysql))
  {
    int id_user = 0;
    user->firstname = f;
    printf("%s\n", user->firstname);
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
      printf("User correctly inserted :\n");
      printf("ID : %d\nFirstname : %s\n", user->id_user, user->firstname);
      printf("Name : %s\nAge : %d\n", user->name, user->age);
      printf("Status : %d\nCategory : %d\n", user->status, user->category);
    }
  }
  else
  {
    printf("User already exists\n");
    user = get_user(n, f, smysql);
  }



  /*
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
  */

  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "TestInsPage");

  g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(key_event), NULL);

  gtk_label_set_text(typed, "");

  gtk_entry_set_text(name, "");
  gtk_entry_set_text(firstname, "");
  gtk_entry_set_text(age, "");

  /*
  gtk_toggle_button_set_active(UCO, FALSE);
  gtk_toggle_button_set_active(UCN, FALSE);
  gtk_toggle_button_set_active(HO, FALSE);
  gtk_toggle_button_set_active(HN, FALSE);
  gtk_toggle_button_set_active(Dalt, FALSE);
  gtk_toggle_button_set_active(Mot, FALSE);
  */
}

void on_gameback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "QcmPage");
}



static gboolean *key_event(GtkWidget *widget, GdkEventKey *event)   {
  char *dst = calloc(20, sizeof(char));
  char *c = gdk_keyval_name(event->keyval);
  strcat(dst, c);
  gtk_label_set_text(typed, dst);
  return FALSE;
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



