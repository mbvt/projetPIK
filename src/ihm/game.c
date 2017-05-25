//#ifndef _MAIN_H
//#define _MAIN_H

# include "../level.h"
# include "../main.h"

static int cpt = 0;
static int score = 0;

/*----------------------------------------------------------------------------*
 *--------------------------------- Game -------------------------------------*/

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

gboolean *key_event_Game(GtkWidget *widget, GdkEventKey *event)
{
  (void)widget;
  char *c = gdk_keyval_name(event->keyval);
  const gchar *cs1 = gtk_entry_get_text(GTK_ENTRY(entryok1));
  const gchar *str = gtk_label_get_text(typed1);

  char *pts = calloc(10, sizeof(char));
  char *cs = (char*)cs1;
  size_t l = strlen(cs);
  char *rep = calloc(l,sizeof(char));
  printf("score = %d\n",score);
  int len = strlen(str);

  rep = strncpy(rep,str,l);
  int b = 0;
  char c2 = c[0];
  char *markup;
  const char *format2 = "<span size=\"xx-large\" foreground=\"#A80202\" face=\"Times\">\%s</span>";
  const char *format1 = "<span size=\"xx-large\" foreground=\"#23A802\" face=\"Times\">\%s</span>";

  if(cpt < len)
  {
    if(c2 !=66)
    {
      b  = compare(rep,cs);
      if (b ==1)
      {
        score++;
        cpt++;

        markup = g_markup_printf_escaped (format1, str);
        gtk_label_set_markup (GTK_LABEL(typed1), markup);
      }
      else
      {
        score--;
        cpt--;

        markup = g_markup_printf_escaped (format2, str);
        gtk_label_set_markup (GTK_LABEL(typed1), markup);
      }
    }
    else
    {
      score--;
      cpt--;
      markup = g_markup_printf_escaped (format2, str);
      gtk_label_set_markup (GTK_LABEL(typed1), markup);
    }
    sprintf(pts, "%d", score);
    gtk_label_set_text(ok1, pts);


  }

  else
  {
    struct S_MYSQL *smysql = NULL;
    smysql = connect_db(smysql);
    smysql->table_name = "pik_user";

    clock_gettime(CLOCK_MONOTONIC,&t1);
    double sec = t1.tv_sec - t0.tv_sec ;
    char *ctime = calloc (10,sizeof(char));
    sprintf(pts, "  %d", score);
    sprintf(ctime, "  %f", sec);

    //printf("Score bien enregistrer id_resultat : %f",sec);
    //int req = insert_res(smysql,1,2,score,sec);
    //printf("Score bien enregistrer id_resultat : %d",req);

    gtk_entry_set_text(entryok1, "");
    cpt= 0;
    score = 0;

    gtk_label_set_text(scores, pts);
    gtk_label_set_text(times, ctime);
    gtk_stack_set_visible_child_name(GTK_STACK(IHM), "ScorePage");

  }

  return FALSE;
}


void on_validercat_clicked()
{

  int tab[3];

  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(D)) )
  {
    tab[0] = 1;
    printf("Débutant\n");
  }
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(I)) )
  {
    tab[0] = 2;
    printf("Intermédiaire \n");
  }
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(E)) )
  {
    tab[0] = 3;
    printf("Expert \n");
  }
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(M1)) )
  {
    tab[1] = 1;
    printf("Monde 1 \n");
  }
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(M2)) )
  {
    tab[1] = 2;
    printf("Monde 2 \n");
  }
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(M3)) )
  {
    tab[1] = 3;
    printf("Monde 3 \n");
  }
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(N1)) )
  {
    tab[2] = 1;
    printf("Niveau 1 \n");
  }
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(N2)) )
  {
    tab[2] = 2;
    printf("Niveau 2 \n");
  }
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(N3)) )
  {
    tab[2] = 3;
    printf("Niveau 3 \n");
  }

  struct S_MYSQL *smysql = NULL;
  smysql = connect_db(smysql);
  smysql->table_name = "pik_user";

  int id_lvl1 = compute_lvl_id(tab);
  char *id_lvl = int_to_str(id_lvl1);
  char *lvl_title = calloc(12, sizeof(char));
  strcat(lvl_title,"./dico/lvl");
  strcat(lvl_title,id_lvl);

  char *lvl_dico = "";
  lvl_dico = load_dico_lvl(lvl_title,id_lvl1, 1, smysql);
  printf("dico %s\n", lvl_dico);

  size_t lentmp = strlen(lvl_dico)-2;
  while (lvl_dico[lentmp] == ' ')
    lentmp--;

  if (lentmp < strlen(lvl_dico)-2 )
    lvl_dico[lentmp] = '\0';

  clock_gettime(CLOCK_MONOTONIC,&t0);

  const char *format = "<span size=\"xx-large\" face=\"Times\">\%s</span>";
  char *markup;
  markup = g_markup_printf_escaped(format, lvl_dico);
  gtk_label_set_markup(GTK_LABEL(typed1), markup);
  //gtk_label_set_text(typed1, lvl_dico);

  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "GamePage");


  g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(key_event_Game), NULL);
}


void on_cateba_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MenuSGPage");
  gtk_label_set_text(errCo, "");
}

void on_gameback1_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "CatePage");
}

void on_mainmenu_clicked()
{
  g_signal_handlers_disconnect_by_func(MainWindow,key_event_Game,NULL);
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MenuSGPage");
  gtk_label_set_text(ok1, "");
  gtk_label_set_text(scores, "");
  gtk_label_set_text(times, "");
  gtk_label_set_text(typed, "");
  gtk_label_set_text(typed1, "");
  gtk_entry_set_text(entryok1, "");
  gtk_entry_set_text(entryok, "");
  score = 0;
  cpt = 0;
}

//# endif
