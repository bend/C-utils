static GtkWidget *princ_window;
static GtkWidget *window_new;
static GtkWidget *window_add;
static GtkWidget *entry_date;
static GtkWidget *entry_montant;
static GtkWidget *entry_objet;
static GtkWidget *entry;
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>

void consult_all(GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
   GtkWidget *window_consult;//declaration of the widgets
   GtkWidget *button_quit;
   GtkWidget *montant;
   GtkWidget *reste;
   GtkWidget *box1;
   GtkWidget *label_m;
   GtkWidget *label_r;
   window_consult = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   button_quit = gtk_button_new_with_label("Terminer");
   gtk_signal_connect_object(GTK_OBJECT(button_quit),
       "clicked",(GtkSignalFunc)gtk_widget_destroy,GTK_OBJECT(window_consult));

   box1=gtk_table_new( 10,10,TRUE);             //creation of the window

   gtk_container_add(GTK_CONTAINER(window_consult),box1);
   gtk_window_set_default_size(GTK_WINDOW(window_consult),100,100);
   gtk_window_set_title(GTK_WINDOW(window_consult),"montant total");
   gtk_container_set_border_width(GTK_CONTAINER(window_consult),10);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_quit,4,6,8,10);
   gtk_window_set_position(GTK_WINDOW(window_consult),GTK_WIN_POS_CENTER);

//lecture du fichier et affichage a l'ecran

   FILE *fdepense= fopen("montant_depenses.dat","rb");//budget depenses reste
   char dep[99];
   char buff[99];
   char res[99];
   fscanf(fdepense,"%s",&*buff);
   fscanf(fdepense,"%s",&*buff);
   fscanf(fdepense,"%s",&*buff);
   fscanf(fdepense,"%s",&*dep);
   fscanf(fdepense,"%s",&*res);
   fclose(fdepense);

   montant=gtk_label_new(dep);
   reste =gtk_label_new(res);
   label_m = gtk_label_new("Montant total de vos depenses € : ");
   label_r = gtk_label_new("Montant restant de votre budget € : ");

   gtk_table_attach_defaults(GTK_TABLE(box1),label_m,1,5,1,3);
   gtk_table_attach_defaults(GTK_TABLE(box1),label_r, 1,5, 5,7);
   gtk_table_attach_defaults(GTK_TABLE(box1),montant,6,9,1,3);
   gtk_table_attach_defaults(GTK_TABLE(box1),reste, 6,9, 5,7);
   gtk_widget_show_all(window_consult);
}


void consult_gains(GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
}

void radio_check(GtkWidget *widget, gpointer data)
{
   const gchar *sLabel;
   GSList *plist = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));
   const char *entry_cont= gtk_entry_get_text(GTK_ENTRY(entry));
   
   while(plist)
   {
      if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(plist->data)))
      {
         sLabel = gtk_button_get_label(GTK_BUTTON(plist->data));
          /* On met la liste a NULL pour sortir de la boucle */
          plist = NULL;
      }
      else
      {
         /* NON -> on passe au bouton suivant */
         plist = g_slist_next(plist);
      }
   }
   FILE *fdescriptif =fopen("descriptif_depenses.dat","rb");
   int i=strcmp(sLabel,"date");
   int j=strcmp(sLabel,"montant");
   int z=strcmp(sLabel,"objet");
   char date[99];
   char montant[99];
   char objet[99];
   if(i==0)
   {
      while(feof(fdescriptif)==0)//while !feof
      {
         fscanf(fdescriptif,"%s",&date);
         if(strcmp(sLabel,date)==0)
         {
            fscanf(fdescriptif,"%s",&montant);
            fscanf(fdescriptif,"%s",&objet);
         }
      }
   }
   else if(j==0)
   {
      while(feof(fdescriptif)==0)
      {
         fscanf(fdescriptif,"%s",&date);
         fscanf(fdescriptif,"%s",&montant);
         if(strcmp(sLabel,date)==0)
         {
            
         } 

      }
   }
}
void consult_depenses(GtkWidget *widget, GdkEventButton *event ,gpointer data)
{

   GtkWidget *window_consult;
   GtkWidget *radio_button_date;
   GtkWidget *radio_button_montant;
   GtkWidget *radio_button_objet;
   GtkWidget *box1;
   GtkWidget *box2;
   GSList *group;
   GtkWidget *scrolled;
   GtkWidget *label;
   GtkWidget *separator;
   GtkWidget *separator1;
   GtkWidget *label2;
   GtkWidget *button_search;
   GtkWidget *button_quit;
   GtkWidget *textview;
   window_consult=gtk_window_new(GTK_WINDOW_TOPLEVEL);
   textview = gtk_text_view_new();
   box2 = gtk_table_new(1,1,TRUE);
   radio_button_date= gtk_radio_button_new_with_label(NULL,"date");
   group =gtk_radio_button_group(GTK_RADIO_BUTTON(radio_button_date));

   radio_button_objet=gtk_radio_button_new_with_label(group,"objet");
   group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio_button_objet));

   radio_button_montant=gtk_radio_button_new_with_label(group, "montant");
   group = gtk_radio_button_group(GTK_RADIO_BUTTON (radio_button_montant));
   scrolled=gtk_scrolled_window_new(NULL,NULL);
   gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled),box2);
   entry = gtk_entry_new();
   separator = gtk_hseparator_new ();
   separator1 = gtk_hseparator_new();
   box1 = gtk_table_new(5,6,FALSE);
   label= gtk_label_new("Choisissez le type\nde recherche");
   label2= gtk_label_new("recherche");  
   gtk_container_add(GTK_CONTAINER(window_consult),box1);
   button_search=gtk_button_new_with_label("Rechercher");
   button_quit = gtk_button_new_with_label("terminer");
   gtk_table_attach_defaults(GTK_TABLE(box1),label,0,2,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box1),radio_button_date,2,3,0,1);

   gtk_table_attach_defaults(GTK_TABLE(box1),radio_button_objet,3,4,0,1);
   radio_button_montant= gtk_radio_button_new_with_label(group, "montant");
   group = gtk_radio_button_group(GTK_RADIO_BUTTON (radio_button_montant));
   gtk_table_attach_defaults(GTK_TABLE(box1),radio_button_montant,4,5,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box1),separator,0,5,1,2);
   gtk_table_attach_defaults(GTK_TABLE(box1),label2,0,2,2,3);
   gtk_table_attach_defaults(GTK_TABLE(box1),entry,2,4,2,3);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_search,4,5,2,3);
   gtk_table_attach_defaults(GTK_TABLE(box1),separator1,0,5,3,4);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_quit,4,5,5,6);
   gtk_table_attach_defaults(GTK_TABLE(box1),scrolled,0,5,4,5);
   gtk_table_attach_defaults(GTK_TABLE(box2),textview,0,1,0,1);
   gtk_container_set_border_width(GTK_CONTAINER(window_consult),10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),0,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),1,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),2,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),3,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),4,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),5,10);
   gtk_table_set_col_spacing (GTK_TABLE (box1),0,5);
   gtk_table_set_col_spacing (GTK_TABLE (box1),2,5);
   gtk_table_set_col_spacing (GTK_TABLE (box1),3,5);
   gtk_table_set_col_spacing (GTK_TABLE (box1),4,5);

   gtk_window_set_position(GTK_WINDOW(window_consult),GTK_WIN_POS_CENTER);
   gtk_window_set_title(GTK_WINDOW(window_consult),"Consultation des depenses");
   gtk_signal_connect_object(GTK_OBJECT(button_quit),
      "clicked",(GtkSignalFunc)gtk_widget_destroy,GTK_OBJECT(window_consult));

   gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_date), TRUE);

   g_signal_connect(G_OBJECT(button_search),"clicked",
                                 G_CALLBACK(radio_check),radio_button_date);

   gtk_window_set_resizable (GTK_WINDOW(window_consult),FALSE);

   gtk_widget_show_all(window_consult);
}



