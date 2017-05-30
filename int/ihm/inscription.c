//#ifndef _MAIN_H
//#define _MAIN_H

# include "../main.h"

//static int cpt = 0;
//static int score = 0;

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

  const char *formatinit = "<span size=\"xx-large\" face=\"Times\">\%s</span>";
  char *markupinit;
  const char *tmpinit = calloc(strlen(formatinit) + 100, sizeof(char));
  
  tmpinit = gtk_label_get_text(typed);
  markupinit = g_markup_printf_escaped(formatinit, tmpinit);
  gtk_label_set_markup(GTK_LABEL(typed), markupinit);


 
  g_signal_connect(MainWindow, "key-release-event", G_CALLBACK(event_Ins), NULL);

  //gtk_entry_set_text(name, "");
  //gtk_entry_set_text(firstname, "");
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


void event_Ins(GtkWidget *widget, GdkEventKey *event)
{
  (void)widget;
  (void)event;
  /* char typed */
  
  const gchar *str_wait = gtk_label_get_text(typed);
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
 	 
  char *text_color_begin, *text_color_end;
  const char *red = "<span size=\"xx-large\" foreground=\"#A80202\" face=\"Times\">\%s</span>";
  const char *green = "<span size=\"xx-large\" foreground=\"#23A802\" face=\"Times\">\%s</span>";
  const char *normal = "<span size=\"xx-large\" face=\"Times\">\%s</span>";

  const char *pp, *nn;
  char *f, *n;
  //char *tmp;
  char *dst;
  while(i < len) 
  {
    //tmp = calloc(strlen(format1) + len + 100, sizeof(char));
    dst = calloc(2*(strlen(green)) + len + 1000, sizeof(char));
 
    ptr_send = strcpy(ptr_send,ptr_char);
   
    res = USB_word(ptr_send, keymap);
    

    if(res == 1)
    {
      char *c = calloc(10,sizeof(char));
      *c = *ptr_char;
      str_typed = strcat(str_typed,c);
      ptr_char ++;
      i ++;
      score ++;
      dst = strncpy(dst, str_wait,i);
      text_color_begin = g_markup_printf_escaped(green, dst);

    }
    else 
    {
      score--;
      dst = strncpy(dst, str_wait,i);
      text_color_begin = g_markup_printf_escaped(red, dst);


    }
    text_color_end = g_markup_printf_escaped(normal, str_wait+i);
    dst = strcat(text_color_begin, text_color_end);
    gtk_label_set_markup(GTK_LABEL(typed), dst);
    
    sprintf(pts, "%d", score);
    gtk_label_set_text(ok, pts);
    
    gtk_label_set_text(saisi1, str_typed);
    
    gtk_stack_set_visible_child_name(GTK_STACK(IHM), "TestInsPage");
  
    while (gtk_events_pending ())
        gtk_main_iteration ();

  
  }

  struct S_MYSQL *smysql = NULL;
  smysql = connect_db(smysql);
  smysql->table_name = "pik_user";

  // calcule du temps 
  clock_gettime(CLOCK_MONOTONIC,&t1);
  double sec = t1.tv_sec - t0.tv_sec ;
  char *ctime = calloc (100,sizeof(char));
  sprintf(pts, "  %d", score);
  sprintf(ctime, "  %f", sec);

 
  /*** TODO  recupération des nom prenoms de l'utilisateur ***/
  pp = gtk_entry_get_text(GTK_ENTRY(entry));
  nn = gtk_entry_get_text(GTK_ENTRY(entryP));
  f = (char *)pp;
  n = (char *)nn;
  printf (" name player : %s",n); 
  printf (" firstname player : %s",f);
 // TODO INSERTION DANS LA BASE

  

  
 //printf("gtk_label_set_text = %s \n", (char *)scores);
  gtk_label_set_text(scores, pts);
  gtk_label_set_text(times, ctime);
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "ScorePage");
 // TODO RECOPIER DANS INSCRIPTION 
}

//# endif
