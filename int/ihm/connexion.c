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
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "StatPage");
  pp = gtk_entry_get_text(GTK_ENTRY(entry));
  nn = gtk_entry_get_text(GTK_ENTRY(entryP));

  f = (char *)pp;
  n = (char *)nn;

  printf("ca marche1 : %s\n", f);
  printf("ca marche2 : %s\n", n);
}

void on_menuniveau_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "CatePage");
}


//# endif
