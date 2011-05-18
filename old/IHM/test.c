#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>



void enter_callback( GtkWidget *widget,
                     GtkWidget *entry )
{
  gchar *entry_text;
  entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
  printf("Entry contents: %s\n", entry_text);
}


int main(int argc, char *argv[])
{
   gtk_init(&argc,&argv);
   GtkWidget *window = NULL;
   window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
   GtkWidget *entry= NULL;
   GtkWidget *box1= NULL;
   entry=gtk_entry_new();

   g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(gtk_main_quit),
                                                                        NULL);
   g_signal_connect(GTK_OBJECT(entry), "activate",

   GTK_SIGNAL_FUNC(enter_callback),entry);
   box1=gtk_table_new( 2,2,TRUE);
   gtk_container_add(GTK_CONTAINER(window),box1);
   gtk_table_attach_defaults(GTK_TABLE(box1),entry,0,2,1,2);

   gtk_widget_show_all(window);
   gtk_main();
   return EXIT_SUCCESS;
}

