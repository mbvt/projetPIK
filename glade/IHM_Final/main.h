# include <stdlib.h>
# include <stdio.h>
# include <gtk/gtk.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>


GtkWidget  *Connexion, *Inscription, *MainWindow, *TestInsPage;
GtkWidget  *CoWindow, *InsWindow, *IHM, *CoEntry;
GtkEntry   *entry, *name, *firstname, *age;
GtkToggleButton *UCO, *UCN, *HO, *HN, *Dalt, *Mot;
GtkBuilder *builder;
GtkLabel   *testCo, *errCo;

void on_Connexion_clicked();
void on_Inscription_clicked();
void on_connback_clicked();
void on_insback_clicked();
void on_qcm_clicked();
void on_CoEntry_clicked();
void on_Game_clicked();
char *key_event(GtkWidget *widget, GdkEventKey *event);
