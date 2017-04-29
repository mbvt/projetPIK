//#ifndef _MAIN_H
//#define _MAIN_H

# include "main.h"

int cpt = 0;
int score = 0;

/*-----------------------------------------------------------------------------
 *------------------------------ Inscription --------------------------------*/

void on_Inscription_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "InscriPage");
}

void on_qcm_clicked()
{

  struct S_MYSQL *smysql = NULL;
  smysql = connect_db(smysql);
  smysql->table_name = "pik_user";

  const char *na = gtk_entry_get_text(GTK_ENTRY(name));
  const char *fa = gtk_entry_get_text(GTK_ENTRY(firstname));

  char *n = (char *)na;
  char *f = (char *)fa;
  char *a = "\0";


  if(exist_user(n, f, smysql))
    gtk_label_set_text(error_test, "Nom déjà existant");
  else if((*n == *a) || (*f == *a))
    gtk_label_set_text(error_test, "Données manquantes");
  else
    gtk_stack_set_visible_child_name(GTK_STACK(IHM), "QcmPage");
}

void on_insback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MainPage");
}

void on_qcmback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "InscriPage");
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
    //gtk_stack_set_visible_child_name(GTK_STACK(IHM), "CatePage");
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

  g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(key_event_Ins), NULL);

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


/*----------------------------------------------------------------------------*
 *----------------------------- Test d'inscription --------------------------*/

static gboolean *key_event_Ins(GtkWidget *widget, GdkEventKey *event)
{
  (void)widget;
  char *c = gdk_keyval_name(event->keyval);
  const gchar *cs1 = gtk_entry_get_text(GTK_ENTRY(entryok));
  const gchar *str = gtk_label_get_text(typed);

  char *pts = calloc(10, sizeof(char));
  char *cs = (char*)cs1;

  size_t l = strlen(cs);
  char *rep = calloc(l,sizeof(char));

  size_t lentmp = 1;
  char *a = " ";

  while (str[strlen(str)-lentmp] == *a)
    lentmp++;
  int len = strlen(str)-lentmp;

  rep = strncpy(rep,str,l);
  int b = 0;
  char c2 = c[0];
  if(cpt < len)
  {
    if(c2 !=66)
    {
      b  = compare(rep,cs);
      if (b ==1)
      {
        score +=1;
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
    sprintf(pts, "%d", score);
    gtk_label_set_text(ok, pts);

  }
  else
  {
    clock_gettime(CLOCK_MONOTONIC,&t1);
    double sec = t1.tv_sec - t0.tv_sec ;
    char *ctime = calloc (10,sizeof(char));
    sprintf(pts, "  %d", score);
    sprintf(ctime, "  %f", sec);

    gtk_label_set_text(scores, pts);
    gtk_label_set_text(times, ctime);
    gtk_stack_set_visible_child_name(GTK_STACK(IHM), "ScorePage");

  }
  return FALSE;
}

//# endif
