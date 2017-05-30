# include "../level.h"
# include "../main.h"

static int cpt = 0;
static int score = 0;
static int id_lvl1 = 0;

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

void event_Game(GtkWidget *widget, GdkEventKey *event)
{
  (void)widget;
  (void)event;
  /* char typed */
  
  const gchar *str_wait = gtk_label_get_text(typed1);
  char *ptr_char = (char *)str_wait;
  int score = 0;
  size_t i = 0;
  int res = 0;
  size_t len = strlen(ptr_char);
  char *pts = calloc(100, sizeof(char));
  char *str_typed = calloc(len,sizeof(char));
  char *ptr_send = calloc(len,sizeof(char));

  /* Init keymap */
  struct matrix *keymap;
  keymap = get_keymap("biblio");
  USB_Init_first(keymap);
 	 
  char *markup, *markup1;
  const char *format2 = "<span size=\"xx-large\" foreground=\"#A80202\" face=\"Times\">\%s</span>";
  const char *format1 = "<span size=\"xx-large\" foreground=\"#23A802\" face=\"Times\">\%s</span>";
  const char *format = "<span size=\"xx-large\" face=\"Times\">\%s</span>";

  const char *pp, *nn;
  char *f, *n;
  char *tmp;
  char *dst;

  while(i < len) 
  {
    tmp = calloc(strlen(format1) + len + 10, sizeof(char));
    dst = calloc(strlen(format1) + len + 10, sizeof(char));
 
    ptr_send = strcpy(ptr_send,ptr_char);
   
    res = USB_word(ptr_send, keymap);
    

    if(res == 1)
    {
      char *c = calloc(4,sizeof(char));
      *c = *ptr_char;
      str_typed = strcat(str_typed,c);
      ptr_char ++;
      i ++;
      score ++;
      tmp = strncpy(dst, str_wait,i);
      markup = g_markup_printf_escaped(format1, tmp);

    }
    else 
    {
      score--;
      tmp = strncpy(dst, str_wait,i);
      markup = g_markup_printf_escaped(format2, tmp);


    }
    markup1 = g_markup_printf_escaped(format, str_wait+i);
    dst = strcat(markup, markup1);
    gtk_label_set_markup(GTK_LABEL(typed1), dst);
    
    sprintf(pts, "%d", score);
    gtk_label_set_text(ok1, pts);
    
    gtk_label_set_text(saisi, str_typed);
    
    gtk_stack_set_visible_child_name(GTK_STACK(IHM), "GamePage");
  
    while (gtk_events_pending ())
        gtk_main_iteration ();

  
  }

  struct S_MYSQL *smysql = NULL;
  smysql = connect_db(smysql);
  smysql->table_name = "results";

  clock_gettime(CLOCK_MONOTONIC,&t1);
  double sec = t1.tv_sec - t0.tv_sec ;
  char *ctime = calloc (100,sizeof(char));
  sprintf(pts, "  %d", score);
  sprintf(ctime, "  %f", sec);

 
  pp = gtk_entry_get_text(GTK_ENTRY(entry));
  nn = gtk_entry_get_text(GTK_ENTRY(entryP));
  f = (char *)pp;
  n = (char *)nn;

  int id_u = get_id_user(smysql, n, f);
  int id_insert = insert_res(smysql, score, id_lvl1, sec, id_u);
  if(id_insert < 1)
    printf("Not registred id level number : %d\n", id_lvl1);
  
  int id_best_res = insert_best_res(smysql, id_u);
  if(id_best_res == 0)
    printf("No best result to show\n");
 
  gtk_label_set_text(scores, pts);
  
  gtk_label_set_text(times, ctime);
  
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "ScorePage");
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

  id_lvl1 = compute_lvl_id(tab);
  printf("id_lvl1 = %d", id_lvl1);
  
  char *id_lvl = int_to_str(id_lvl1);
  if(id_lvl1 > 19)
  {
    gtk_label_set_text(err_lvl, "Niveau non disponible");
  }
else
{
  gtk_label_set_text(numlvl, id_lvl);
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

  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "GamePage");

  //event_Game();

  g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(event_Game), NULL);
  //g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(event_Game), NULL);
}
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
  g_signal_handlers_disconnect_by_func(MainWindow,event_Game,NULL);
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
