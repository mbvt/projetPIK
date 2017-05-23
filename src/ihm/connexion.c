//#ifndef _MAIN_H
//#define _MAIN_H

# include "../main.h"


/*-----------------------------------------------------------------------------
 *------------------------------ Connexion ----------------------------------*/
void on_Connexion_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "ConnPage");
}

void on_connback_clicked()
{
  gtk_stack_set_visible_child_name(GTK_STACK(IHM), "MainPage");
}

/*----------------------------------------------------------------------------*
 * --------------------------------Connexion---------------------------------*/
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
  gtk_entry_set_text(entry, "");
  gtk_entry_set_text(entryP, "");

}

//# endif
