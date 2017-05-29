# include "main.h"

/*----------------------------------MAIN---------------------------------------
 *---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "IHM_final.glade", NULL);

  MainWindow  = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
  IHM         = GTK_WIDGET(gtk_builder_get_object(builder, "IHM"));
  gtk_builder_connect_signals(builder, NULL);
  TestInsPage  = GTK_WIDGET(gtk_builder_get_object(builder, "TestInsPage"));

  typed = GTK_LABEL(gtk_builder_get_object(builder, "typed"));
  ok = GTK_LABEL(gtk_builder_get_object(builder, "ok"));
  typed1 = GTK_LABEL(gtk_builder_get_object(builder, "typed1"));
  ok1 = GTK_LABEL(gtk_builder_get_object(builder, "ok1"));

  entryok1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryok1"));
  entryok = GTK_ENTRY(gtk_builder_get_object(builder, "entryok"));
  entry = GTK_ENTRY(gtk_builder_get_object(builder, "entry"));
  entryP = GTK_ENTRY(gtk_builder_get_object(builder, "entryP"));
  g_signal_connect(entry, "activate", G_CALLBACK(on_CoEntry_clicked), entry);

  testCo = GTK_LABEL(gtk_builder_get_object(builder, "testCo"));
  errCo  = GTK_LABEL(gtk_builder_get_object(builder, "errCo"));
  error_test = GTK_LABEL(gtk_builder_get_object(builder, "error_test"));
  scores = GTK_LABEL(gtk_builder_get_object(builder, "scores"));
  times = GTK_LABEL(gtk_builder_get_object(builder, "times")); 
  saisi = GTK_LABEL(gtk_builder_get_object(builder, "saisi"));
   
  nb = GTK_LABEL(gtk_builder_get_object(builder, "nb"));
  ms = GTK_LABEL(gtk_builder_get_object(builder, "ms"));
  mt = GTK_LABEL(gtk_builder_get_object(builder, "mt"));
  mn = GTK_LABEL(gtk_builder_get_object(builder, "mn"));
  mj = GTK_LABEL(gtk_builder_get_object(builder, "mj"));

  name      = GTK_ENTRY(gtk_builder_get_object(builder, "name"));
  firstname = GTK_ENTRY(gtk_builder_get_object(builder, "firstname"));
  age       = GTK_ENTRY(gtk_builder_get_object(builder, "age"));

  g_signal_connect(entry, "activate", G_CALLBACK(on_qcm_clicked), name);
  g_signal_connect(entry, "activate", G_CALLBACK(on_qcm_clicked), firstname);
  g_signal_connect(entry, "activate", G_CALLBACK(on_qcm_clicked), age);

  UCO  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "UCO"));
  UCN  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "UCN"));
  HO   = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "HO"));
  HN   = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "HN"));
  Dalt = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "Dalt"));
  Mot  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "Mot"));

  g_signal_connect(UCO , "activate", G_CALLBACK(on_Game_clicked), UCO);
  g_signal_connect(UCN , "activate", G_CALLBACK(on_Game_clicked), UCN);
  g_signal_connect(HO  , "activate", G_CALLBACK(on_Game_clicked), HO);
  g_signal_connect(HN  , "activate", G_CALLBACK(on_Game_clicked), HN);
  g_signal_connect(Dalt, "activate", G_CALLBACK(on_Game_clicked), Dalt);
  g_signal_connect(Mot , "activate", G_CALLBACK(on_Game_clicked), Mot);


  D  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "D"));
  I  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "I"));
  E  = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "E"));
  M1 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "M1"));
  M2 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "M2"));
  M3 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "M3"));
  N1 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "N1"));
  N2 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "N2"));
  N3 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "N3"));


  g_signal_connect(D , "activate", G_CALLBACK(on_validercat_clicked), D);
  g_signal_connect(I , "activate", G_CALLBACK(on_validercat_clicked), I);
  g_signal_connect(E , "activate", G_CALLBACK(on_validercat_clicked), E);
  g_signal_connect(M1, "activate", G_CALLBACK(on_validercat_clicked), M1);
  g_signal_connect(M2, "activate", G_CALLBACK(on_validercat_clicked), M2);
  g_signal_connect(M3, "activate", G_CALLBACK(on_validercat_clicked), M3);
  g_signal_connect(N1, "activate", G_CALLBACK(on_validercat_clicked), N1);
  g_signal_connect(N2, "activate", G_CALLBACK(on_validercat_clicked), N2);
  g_signal_connect(N3, "activate", G_CALLBACK(on_validercat_clicked), N3);


  g_object_unref (G_OBJECT (builder));

  gtk_widget_show(MainWindow);
  gtk_main();

  return 0;
}

