#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include<float.h>
static GtkWidget *princ_window;
static GtkWidget *window_new;
static GtkWidget *window_add;
static GtkWidget *entry_date;
static GtkWidget *entry_montant;
static GtkWidget *entry_objet;
static GtkWidget *entry;



void save_gain(const char *montant,const char *date, const char *objet)
                            //ecriture des donnes ds le fichier
{
   FILE *fenregistrer = fopen("descriptif_gain.dat","ab");

   fprintf(fenregistrer,"%s\n",date);
   fprintf(fenregistrer,"%s\n",montant);
   fprintf(fenregistrer,"%s\n",objet);
   fclose(fenregistrer);

   FILE *fmontant =fopen("montant_depenses.dat","rb");
//date(2),budget,depenses,reste
   int buff,buff1,budget,reste,depenses;
   fscanf(fmontant,"%d",&buff);
   fscanf(fmontant,"%d",&buff1);
   fscanf(fmontant,"%d",&budget);//printf("%d\n",budget);
   fscanf(fmontant,"%d",&depenses);//printf("%d\n",depenses);
   fscanf(fmontant,"%d",&reste);//printf("%d\n",reste);
   fclose(fmontant);
   int montant2=atoi(montant);
   depenses=depenses-montant2;
   reste=budget-(depenses);
   FILE *fdepenses2= fopen("montant_depenses.dat","wb");

   if(buff<10 && buff1 <10)
      fprintf(fmontant,"0%d 0%d\n",buff,buff1);
   else if(buff<10 && buff1>=10)
      fprintf(fmontant,"0%d %d\n",buff,buff1);
   else if(buff>=10 && buff1>=10)
      fprintf(fmontant,"%d %d\n",buff,buff1);
   else if(buff>=10 && buff1<10)
      fprintf(fmontant,"%d 0%d\n",buff,buff1);

   fprintf(fdepenses2,"%d\n",budget);
   fprintf(fdepenses2,"%d\n",depenses);
   fprintf(fdepenses2,"%d\n",reste);
   fclose(fdepenses2);
   gtk_widget_destroy(window_add);
}

void gain_transit(GtkWidget *widget ,GtkWidget *widget2)
{
   const char *date = gtk_entry_get_text(GTK_ENTRY(entry_date));
   const char *montant = gtk_entry_get_text(GTK_ENTRY(entry_montant));
   const char *objet = gtk_entry_get_text(GTK_ENTRY(entry_objet));
   save_gain(montant,date,objet);
}

void new_gain (GtkWidget *widget, GdkEventButton *event ,gpointer data);

void next_gain(GtkWidget *widget ,GtkWidget *widget2)
{
   const char *date = gtk_entry_get_text(GTK_ENTRY(entry_date));
   const char *montant = gtk_entry_get_text(GTK_ENTRY(entry_montant));
   const char *objet = gtk_entry_get_text(GTK_ENTRY(entry_objet));
   save_gain(montant,date,objet);
   new_gain(window_add,NULL,NULL);
}

void new_gain(GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
   GtkWidget *label_date;
   GtkWidget *label_montant;
   GtkWidget *label_objet;
   GtkWidget *box;
   GtkWidget *button_cancel;
   GtkWidget *button_ok;
   GtkWidget *button_next;
   
   window_add = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   label_date = gtk_label_new("Entrez la date");
   label_montant= gtk_label_new("Entrez le montant");
   label_objet= gtk_label_new("entrez l'objet");
   entry_date = gtk_entry_new();
   entry_montant=gtk_entry_new();
   entry_objet= gtk_entry_new();
   button_cancel = gtk_button_new_with_label("Annuler");
   button_ok = gtk_button_new_with_label ("Valider");
   button_next =gtk_button_new_with_label("Enregistrer un autre gain");
   box= gtk_table_new(2,4, FALSE);
   gtk_signal_connect_object(GTK_OBJECT(button_cancel), "clicked",
      (GtkSignalFunc)gtk_widget_destroy,GTK_OBJECT(window_add));
   gtk_signal_connect_object(GTK_OBJECT(button_next), "clicked",
      (GtkSignalFunc)next_gain,GTK_OBJECT(window_add));
   gtk_signal_connect_object(GTK_OBJECT(button_ok), "clicked",
      (GtkSignalFunc)gain_transit,GTK_OBJECT(window_add));

   gtk_entry_set_text(GTK_ENTRY(entry_date),"Date");
   gtk_entry_set_text(GTK_ENTRY(entry_montant),"Montant");
  
   gtk_entry_set_text(GTK_ENTRY(entry_objet),"Objet");
   gtk_container_add(GTK_CONTAINER(window_add),box);
   gtk_window_set_title(GTK_WINDOW(window_add),"Nouveau gain");
   gtk_window_set_default_size(GTK_WINDOW(window_add),100,100);
   gtk_window_set_position(GTK_WINDOW(window_add),GTK_WIN_POS_CENTER);
   gtk_container_set_border_width(GTK_CONTAINER(window_add),10);

   gtk_table_attach_defaults(GTK_TABLE(box),label_date,0,1,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box),entry_date,1,2,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box),label_montant,0,1,1,2);
   gtk_table_attach_defaults(GTK_TABLE(box),entry_montant,1,2,1,2);
   gtk_table_attach_defaults(GTK_TABLE(box),label_objet,0,1,2,3);
   gtk_table_attach_defaults(GTK_TABLE(box),entry_objet,1,2,2,3);
   gtk_table_attach_defaults(GTK_TABLE(box),button_ok,0,1,3,4);
   gtk_table_attach_defaults(GTK_TABLE(box),button_next,0,1,4,5);
   gtk_table_attach_defaults(GTK_TABLE(box),button_cancel,1,2,3,4);

   gtk_table_set_row_spacing( GTK_TABLE (box),0,10);
   gtk_table_set_row_spacing( GTK_TABLE (box),1,10);
   gtk_table_set_row_spacing( GTK_TABLE (box),2,10);
   gtk_table_set_col_spacing (GTK_TABLE (box),0,5);
   gtk_window_set_resizable (GTK_WINDOW(window_add),FALSE);


   gtk_widget_show_all(window_add);
}

void save(const char *montant,const char *date, const char *objet)
                            //ecriture des donnes ds le fichier
{
   FILE *fenregistrer = fopen("descriptif_depenses.dat","ab");

   fprintf(fenregistrer,"%s\n",date);
   fprintf(fenregistrer,"%s\n",montant);
   fprintf(fenregistrer,"%s\n",objet);
   fclose(fenregistrer);

   FILE *fmontant =fopen("montant_depenses.dat","rb");
//date(2),budget,depenses,reste
   int buff,buff1,budget,reste,depenses;
   fscanf(fmontant,"%d",&buff);
   fscanf(fmontant,"%d",&buff1);
   fscanf(fmontant,"%d",&budget);//printf("%d\n",budget);
   fscanf(fmontant,"%d",&depenses);//printf("%d\n",depenses);
   fscanf(fmontant,"%d",&reste);//printf("%d\n",reste);
   fclose(fmontant);
   int montant2=atoi(montant);
   depenses=depenses+montant2;
   reste=budget-depenses;
   FILE *fdepenses2= fopen("montant_depenses.dat","wb");

   if(buff<10 && buff1 <10)
      fprintf(fmontant,"0%d 0%d\n",buff,buff1);
   else if(buff<10 && buff1>=10)
      fprintf(fmontant,"0%d %d\n",buff,buff1);
   else if(buff>=10 && buff1>=10)
      fprintf(fmontant,"%d %d\n",buff,buff1);
   else if(buff>=10 && buff1<10)
      fprintf(fmontant,"%d 0%d\n",buff,buff1);

   fprintf(fdepenses2,"%d\n",budget);
   fprintf(fdepenses2,"%d\n",depenses);
   fprintf(fdepenses2,"%d\n",reste);
   fclose(fdepenses2);
   gtk_widget_destroy(window_add);
}

void save_transit(GtkWidget *widget ,GtkWidget *widget2)
{
   const char *date = gtk_entry_get_text(GTK_ENTRY(entry_date));
   const char *montant = gtk_entry_get_text(GTK_ENTRY(entry_montant));
   const char *objet = gtk_entry_get_text(GTK_ENTRY(entry_objet));
   save(montant,date,objet);
}

void new_spent (GtkWidget *widget, GdkEventButton *event ,gpointer data);

void next_save(GtkWidget *widget ,GtkWidget *widget2)
{
   const char *date = gtk_entry_get_text(GTK_ENTRY(entry_date));
   const char *montant = gtk_entry_get_text(GTK_ENTRY(entry_montant));
   const char *objet = gtk_entry_get_text(GTK_ENTRY(entry_objet));
   save(montant,date,objet);
   new_spent(window_add,NULL,NULL);
}

void new_spent (GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
   GtkWidget *label_date;
   GtkWidget *label_montant;
   GtkWidget *label_objet;
   GtkWidget *box;
   GtkWidget *button_cancel;
   GtkWidget *button_ok;
   GtkWidget *button_next;
   
   window_add = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   label_date = gtk_label_new("Entrez la date");
   label_montant= gtk_label_new("Entrez le montant");
   label_objet= gtk_label_new("entrez l'objet");
   entry_date = gtk_entry_new();
   entry_montant=gtk_entry_new();
   entry_objet= gtk_entry_new();
   button_cancel = gtk_button_new_with_label("Annuler");
   button_ok = gtk_button_new_with_label ("Valider");
   button_next =gtk_button_new_with_label("Enregistrer une autre depense");
   box= gtk_table_new(2,4, FALSE);
   gtk_signal_connect_object(GTK_OBJECT(button_cancel), "clicked",
      (GtkSignalFunc)gtk_widget_destroy,GTK_OBJECT(window_add));
   gtk_signal_connect_object(GTK_OBJECT(button_next), "clicked",
      (GtkSignalFunc)next_save,GTK_OBJECT(window_add));
   gtk_signal_connect_object(GTK_OBJECT(button_ok), "clicked",
      (GtkSignalFunc)save_transit,GTK_OBJECT(window_add));

   gtk_entry_set_text(GTK_ENTRY(entry_date),"Date");
   gtk_entry_set_text(GTK_ENTRY(entry_montant),"Montant");
   gtk_entry_set_text(GTK_ENTRY(entry_objet),"Objet");

   gtk_container_add(GTK_CONTAINER(window_add),box);
   gtk_window_set_title(GTK_WINDOW(window_add),"Nouvelle depense");
   gtk_window_set_default_size(GTK_WINDOW(window_add),100,100);
   gtk_window_set_position(GTK_WINDOW(window_add),GTK_WIN_POS_CENTER);
   gtk_container_set_border_width(GTK_CONTAINER(window_add),10);

   gtk_table_attach_defaults(GTK_TABLE(box),label_date,0,1,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box),entry_date,1,2,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box),label_montant,0,1,1,2);
   gtk_table_attach_defaults(GTK_TABLE(box),entry_montant,1,2,1,2);
   gtk_table_attach_defaults(GTK_TABLE(box),label_objet,0,1,2,3);
   gtk_table_attach_defaults(GTK_TABLE(box),entry_objet,1,2,2,3);
   gtk_table_attach_defaults(GTK_TABLE(box),button_ok,0,1,3,4);
   gtk_table_attach_defaults(GTK_TABLE(box),button_next,0,1,4,5);
   gtk_table_attach_defaults(GTK_TABLE(box),button_cancel,1,2,3,4);

   gtk_table_set_row_spacing( GTK_TABLE (box),0,10);
   gtk_table_set_row_spacing( GTK_TABLE (box),1,10);
   gtk_table_set_row_spacing( GTK_TABLE (box),2,10);
   gtk_table_set_col_spacing (GTK_TABLE (box),0,5);
   gtk_window_set_resizable (GTK_WINDOW(window_add),FALSE);


   gtk_widget_show_all(window_add);
}
