#ifndef _MAIN_H
#define _MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <gtk/gtk.h>
# include <err.h>
# include <SDL/SDL.h>
# include <time.h>
# include <SDL/SDL_image.h>
# include "user.h"
# include "./usb/USB_Main.h"

extern struct S_GSQL {
  struct S_MYSQL *smysql;
  struct user *user;
} *conn;

char *tmp;
struct timespec t0,t1;

GtkWidget  *Connexion, *Inscription, *MainWindow, *TestInsPage;
GtkWidget  *CoWindow, *InsWindow, *IHM, *CoEntry;
GtkEntry   *entry, *entryP, *entryok, *entryok1, *name, *firstname, *age;
GtkBuilder *builder;
GtkLabel   *testCo, *error_test, *scores, *errCo, *typed;
GtkLabel   *nb, *ms, *mt, *mn, *mj;
GtkLabel   *typed1, *ok1, *ok, *times, *saisi;
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
int compare(char *s1, char *s2);

//void event_Game();
void event_Game(GtkWidget *widget, GdkEventKey *event);
//gboolean *event_Game(GtkWidget *widget, GdkEventKey *event);
gboolean *key_event_Ins(GtkWidget *widget, GdkEventKey *event);

#endif
