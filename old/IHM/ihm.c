#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void fenetre_suivante(GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
   gtk_main_quit();
   GtkWidget *window2=NULL;
   window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   
   gtk_widget_show(window2);
   gtk_main();

}

void texte(GtkWidget *widget, GtkWidget entry)
{

   gchar *entry_text;
   entry_text=gtk_entry_get_text(GTK_ENTRY(entry1));
   printf("le text entre est : %s\n",entry_text);
}

int main(int argc, char *argv[])
{
   GtkWidget *window = NULL;
   GtkWidget *button1 =NULL;
   GtkWidget *button2 =NULL;
   GtkWidget *button3 =NULL;
   GtkWidget *box1 =NULL;
   GtkWidget *entry1=NULL;
   gtk_init(&argc,&argv);
   window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
   button1=gtk_button_new_with_label("quitter");
   button2=gtk_button_new_with_label("hehe");
   button3=gtk_button_new_with_label("lol");
   entry1=gtk_entry_new();
   g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(gtk_main_quit),
                                                                        NULL);

   g_signal_connect(G_OBJECT(button1),"button_press_event",
                           GTK_SIGNAL_FUNC(fenetre_suivante),
                                                  NULL ) ;
   g_signal_connect(GTK_OBJECT(entry1), "activate",
   GTK_SIGNAL_FUNC(texte),entry1);

   box1=gtk_table_new( 2,2,TRUE);
   gtk_container_add(GTK_CONTAINER(window),box1);
   gtk_table_attach_defaults(GTK_TABLE(box1),button1,0,1,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box1),button2,2,3,0,1);
   gtk_entry_set_text(GTK_ENTRY (entry1),"tapez le text ici");
   gtk_table_attach_defaults(GTK_TABLE(box1),entry1,0,2,1,2);
   gtk_window_set_title(GTK_WINDOW(window),"fenetre de test");
   gtk_window_set_default_size(GTK_WINDOW(window),640,480);
   gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
   gtk_window_set_deletable(GTK_WINDOW(window),TRUE);
   gtk_container_set_border_width(GTK_CONTAINER(window),10);
   gtk_container_add (GTK_CONTAINER(window), button1);
   gtk_widget_show_all(window);
   gtk_main();






return EXIT_SUCCESS;
}
