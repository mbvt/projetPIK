# include <stdlib.h>
# include <stdio.h>
# include <gtk/gtk.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "user.h"


extern struct S_GSQL {
  struct S_MYSQL *smysql;
  struct user *user;
} *conn;


GtkWidget  *Connexion, *Inscription, *MainWindow, *TestInsPage;
GtkWidget  *CoWindow, *InsWindow, *IHM, *CoEntry;
GtkEntry   *entry, *entryP, *entryok, *name, *firstname, *age;
GtkBuilder *builder;
GtkLabel   *testCo, *errCo, *typed, *ok;
GtkToggleButton *UCO, *UCN, *HO, *HN, *Dalt, *Mot;
GtkToggleButton *D, *I, *E, *M1, *M2, *M3, *N1, *N2, *N3;
GSList *group1, *group2, *group3;

void on_Connexion_clicked();
void on_Inscription_clicked();
void on_connback_clicked();
void on_insback_clicked();
void on_qcm_clicked();
void on_CoEntry_clicked();
void on_Game_clicked();
void on_validercat_clicked();
static gboolean *key_event();//GtkWidget *widget, GdkEventKey *event);
