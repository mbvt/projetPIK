//#ifndef _MAIN_H
//#define _MAIN_H

# include "../main.h"

GtkLabel *nb, *ms, *mt, *mn, *mj;


/*----------------------------------------------------------------------------*
 *-------------------------------- Connexion --------------------------------*/
void on_Connexion_clicked()
{
  gtk_entry_set_text(entry, "");
  gtk_entry_set_text(entryP, "");

  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "ConnPage");
}

void on_connback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MainPage");
}



const char *pp, *nn;
char *f;
char *n;

/*----------------------------------------------------------------------------*
 * --------------------------------Connexion---------------------------------*/
void on_CoEntry_clicked()
{

  struct S_MYSQL *smysql = NULL;
  smysql = connect_db(smysql);
  smysql->table_name = "pik_user";


  pp = gtk_entry_get_text(GTK_ENTRY(entry));
  nn = gtk_entry_get_text(GTK_ENTRY(entryP));

  f = (char *)pp;
  n = (char *)nn;

  if(exist_user(f, n, smysql))
  {
    gtk_label_set_text(testCo, f);
    gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MenuSGPage");

  }

  gtk_label_set_text(errCo, "Nom d'utilisateur non trouvé");
  //gtk_entry_set_text(entry, "");
  //gtk_entry_set_text(entryP, "");

}

/*----------------------------------------------------------------------------*
 *--------------------------------Statistiques-------------------------------*/

void on_statback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MenuSGPage");
}

void on_mSGback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MainPage");
}

void on_stat_clicked()
{
  /*------------------------Tu peux rajouter tes trucs ici-------------------*/
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "StatPage");
  pp = gtk_entry_get_text(GTK_ENTRY(entry));
  nn = gtk_entry_get_text(GTK_ENTRY(entryP));

  f = (char *)pp;
  n = (char *)nn;
  
  struct S_MYSQL *smysql = calloc(1, sizeof(struct S_MYSQL));
  smysql = connect_db(smysql);

  int id_u = get_id_user(smysql, f, n);
  
  int nb_game = get_nb_game(smysql, id_u);
  int b_score = 0;
  double b_time = 0;
  int b_lvl = 0;

if(nb_game != 0)
  {
    b_score = get_top_score(smysql, id_u);
    b_time = get_top_time(smysql, id_u);
    b_lvl = get_top_level(smysql, id_u);
  }

  int id_b_player = get_best_player(smysql);
 
  char **tab_fname = get_f_name(smysql, id_b_player);
  char *f_name = tab_fname[0];
  char *name = tab_fname[1];

  int bp_score = get_sum_score(smysql, id_b_player);

  char *nb1 = int_to_str(nb_game);
  char *ms1 = int_to_str(b_score);
  char *mt1 = int_to_str(b_time);
  char *mn1 = int_to_str(b_lvl);

  gtk_label_set_text(nb, nb1);
  gtk_label_set_text(ms, ms1);
  gtk_label_set_text(mt, mt1);
  gtk_label_set_text(mn, mn1);
  gtk_label_set_text(mj, f_name);
}

void on_menuniveau_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "CatePage");
}


//# endif
