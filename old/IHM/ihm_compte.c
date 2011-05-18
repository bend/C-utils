#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

gint delete_event( GtkWidget *widget,GdkEvent *event,gpointer data )
{
  gtk_main_quit ();
  return(FALSE);
}


void consultation(GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
   GtkWidget *window_consult;//declaration of the widgets
   GtkWidget *button_quit;
   GtkWidget *montant;
   GtkWidget *date;
   GtkWidget *objet;
   GtkWidget *box1;
   GtkWidget *reste;
   window_consult = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   button_quit = gtk_button_new_with_label("Terminer");
   gtk_signal_connect_object(GTK_OBJECT(button_quit),
      "clicked",(GtkSignalFunc)gtk_widget_destroy,GTK_OBJECT(window_consult));
   box1=gtk_table_new( 3,2,TRUE);
   gtk_container_add(GTK_CONTAINER(window_consult),box1);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_quit,1,2,0,1);
   gtk_widget_show_all(window_consult);
}





int main(int argc,char *argv[])
{
   gtk_init(&argc,&argv);//initialization

   GtkWidget *princ_window;//declaration of the widgets
   GtkWidget *button_quit;
   GtkWidget *button_consu;
   GtkWidget *button_save;
   GtkWidget *button_new;
   GtkWidget *box1;

   princ_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//creation of the widgets
   button_quit =gtk_button_new_with_label("Quit");
   button_consu = gtk_button_new_with_label("consultation");
   button_save = gtk_button_new_with_label("enregistrement d'une depense");
   button_new = gtk_button_new_with_label("nouveau mois");

   gtk_signal_connect (GTK_OBJECT (button_quit), "clicked", //creating signals
                    GTK_SIGNAL_FUNC (delete_event),NULL);
   g_signal_connect(G_OBJECT(princ_window),"delete-event",
                           G_CALLBACK(gtk_main_quit),NULL);
   g_signal_connect(G_OBJECT(button_consu),"clicked",GTK_SIGNAL_FUNC(
   consultation),NULL);

         GtkWidget *fen;
         fen=gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_signal_connect_object(GTK_OBJECT(button_save), "clicked",
            (GtkSignalFunc)gtk_widget_show,GTK_OBJECT(fen));


   /*g_signal_connect(G_OBJECT(button_save),"button_press_event",
                           GTK_SIGNAL_FUNC(enregistrement),
                                                  NULL ) ;
   g_signal_connect(G_OBJECT(button_new),"button_press_event",
                           GTK_SIGNAL_FUNC(nouveau_mois),
                                                  NULL );*/
   gtk_container_set_border_width(GTK_CONTAINER(princ_window),10);
   box1=gtk_table_new( 3,2,TRUE);
   gtk_container_add(GTK_CONTAINER(princ_window),box1);
   gtk_table_set_row_spacing( GTK_TABLE (box1),0,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),1,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),2,10);
   gtk_table_set_col_spacing (GTK_TABLE (box1),0,5);


   gtk_window_set_title(GTK_WINDOW(princ_window),"Que voulez vous?");
   gtk_window_set_position(GTK_WINDOW(princ_window),GTK_WIN_POS_CENTER);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_consu,0,1,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_new,1,2,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_save,0,2,1,2);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_quit,0,2,2,3);

   gtk_widget_show_all(princ_window);
   gtk_main();

return EXIT_SUCCESS;
}

