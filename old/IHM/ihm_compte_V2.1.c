#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>

static GtkWidget *princ_window;
static GtkWidget *window_new;
static GtkWidget *window_add;
static GtkWidget *entry_date;
static GtkWidget *entry_montant;
static GtkWidget *entry_objet;
static GtkWidget *entry;

gint delete_event( GtkWidget *widget,GdkEvent *event,gpointer data )
{
  gtk_main_quit ();
  return(FALSE);
}

void OnQuitter(GtkWidget* widget, gpointer data)
{
    GtkWidget *pQuestion;

    pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez vous vraiment\n"
        "quitter le programme?");

    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NONE:
        case GTK_RESPONSE_NO:
            gtk_widget_destroy(pQuestion);
            break;
    }
}

void OnAbout(GtkWidget* widget, gpointer data)
{
    GtkWidget *pAbout;

    pAbout = gtk_message_dialog_new (GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
         "Vos compte version 1.0 beta\n"
         "Programme destine a vous aider a faire vos comptes\n"
         "Copyright BEN© 2008\n");

    gtk_dialog_run(GTK_DIALOG(pAbout));

    gtk_widget_destroy(pAbout);
}

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
  
   gtk_entry_set_text(GTK_ENTRY(entry_objet),"Objet");gtk_container_add(
   GTK_CONTAINER(window_add),box);
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
   gtk_widget_show_all(window_add);
}

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
   char dep[6];
   char buff[6];
   char res[6];
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

void consult_gain(GtkWidget *widget, GdkEventButton *event ,gpointer data)
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
   char buff[99];
   char montant[99];
   char objet[99];
   if(i==0)
   {
      while(feof(fdescriptif)==0)
      {
         fscanf(fdescriptif,"%s",&buff);
         i=strcmp(entry_cont,buff);
         if(i==0)
         {
            fscanf(fdescriptif,"%s",&montant);
            fscanf(fdescriptif,"%s",&objet);
            //afficher dans la fenentre;(remplacer les espces par _ ds objet)
         }
      }
   }
   else if(j==0)
   {
      printf("montant\n");
   }
   else if(z==0)
   {
      printf("objet\n");
   }

}

void consult_descriptif(GtkWidget *widget, GdkEventButton *event ,gpointer data)
{

   GtkWidget *window_consult;
   GtkWidget *radio_button_date;
   GtkWidget *radio_button_montant;
   GtkWidget *radio_button_objet;
   GtkWidget *box1;
   GSList *group;
   GtkWidget *label;
   GtkWidget *separator;
   GtkWidget *separator1;
   GtkWidget *label2;
   GtkWidget *button_search;
   GtkWidget *button_quit; 
   window_consult=gtk_window_new(GTK_WINDOW_TOPLEVEL);

   radio_button_date= gtk_radio_button_new_with_label(NULL,"date");
   group =gtk_radio_button_group(GTK_RADIO_BUTTON(radio_button_date));

   radio_button_objet=gtk_radio_button_new_with_label(group,"objet");
   group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio_button_objet));

   radio_button_montant=gtk_radio_button_new_with_label(group, "montant");
   group = gtk_radio_button_group(GTK_RADIO_BUTTON (radio_button_montant));

   entry = gtk_entry_new();
   separator = gtk_hseparator_new ();
   separator1 = gtk_hseparator_new();
   box1 = gtk_table_new(5,5,TRUE);
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
   gtk_table_attach_defaults(GTK_TABLE(box1),button_quit,4,5,4,5);
   gtk_container_set_border_width(GTK_CONTAINER(window_consult),10);
   gtk_window_set_title(GTK_WINDOW(window_consult),"Consultation des depenses");
   gtk_signal_connect_object(GTK_OBJECT(button_quit),
      "clicked",(GtkSignalFunc)gtk_widget_destroy,GTK_OBJECT(window_consult));

   gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_date), TRUE);

   g_signal_connect(G_OBJECT(button_search),"clicked",
                                 G_CALLBACK(radio_check),radio_button_date);

   gtk_widget_show_all(window_consult);
}

void budget (GtkWidget *window, GtkWidget *entry)
{
   FILE *fmontant = fopen("montant_depenses.dat","rb");
   char m[3];
   char y[3];
   char a[30]={"montant_du_"};
   char c[30]={"descriptif_du_"};
   char d[30]={"gain_du-"};
   if(!fmontant)
      printf("error while opening the files");
   fscanf(fmontant,"%s",&m);
   fscanf(fmontant,"%s",&y);
   strncat(a,m,2);
   strncat(a,"_",1);
   strncat(a,y,2);
   strncat(c,m,2);
   strncat(c,"_",1);
   strncat(c,y,2);
   strncat(d,m,2);
   strncat(d,"_",1);
   strncat(d,y,2);
   fclose(fmontant);
   if (rename("montant_depenses.dat",a) !=0||
       rename("descriptif_depenses.dat",c)!=0||
       rename("descriptif_gain.dat",d)!=0)
         printf("error while renaming files\n");
   FILE *fdescriptif =fopen("descriptif_depenses.dat","wb");
   fmontant =fopen("montant_depenses.dat","wb");
   FILE *fgain = fopen("descriptif_gain.dat","wb");
   struct tm *tb;
      time_t t;
      tb = localtime(&t);
      time(&t);
      ctime(&t);
      int month_act= tb->tm_mon;
      int year_act = tb->tm_year;
      month_act = month_act+1;
      year_act = year_act-100;

   if(month_act<10 && year_act <10)
      fprintf(fmontant,"0%d 0%d\n",month_act,year_act);
   else if(month_act<10 && year_act>=10)
      fprintf(fmontant,"0%d %d\n",month_act,year_act);
   else if(month_act>=10 && year_act>=10)
      fprintf(fmontant,"%d %d\n",month_act,year_act);
   else if(month_act>=10 && year_act<10)
      fprintf(fmontant,"%d 0%d\n",month_act,year_act);
   const char *montant = gtk_entry_get_text(GTK_ENTRY(entry));
   fprintf(fmontant,"%s\n",montant);

   fclose(fdescriptif);
   fclose(fmontant);
   fclose(fgain);
   gtk_widget_destroy(window_new);
}

void new_month (GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
   GtkWidget *label1;
   GtkWidget *label2;
   GtkWidget *box1;
   GtkWidget *button_ok;

   window_new = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   label1 = gtk_label_new("Un nouveau mois a commencé");
   label2 = gtk_label_new("Saisissez le Budget du mois");
   button_ok = gtk_button_new_with_label("Valider");
   entry_montant = gtk_entry_new();
   gtk_entry_set_text(GTK_ENTRY(entry_montant),"Budget mensuel");
   gtk_signal_connect(GTK_OBJECT(button_ok), "clicked",
                     GTK_SIGNAL_FUNC(budget),entry_montant);

   box1 = gtk_table_new(3,3,FALSE);
   gtk_container_add(GTK_CONTAINER(window_new),box1);
   gtk_window_set_title(GTK_WINDOW(window_new),"Budget mensuel");
   gtk_window_set_default_size(GTK_WINDOW(window_new),10,10);
   gtk_window_set_position(GTK_WINDOW(window_new),GTK_WIN_POS_CENTER);
   gtk_container_set_border_width(GTK_CONTAINER(window_new),10);

   gtk_table_attach_defaults(GTK_TABLE(box1),label1,0,3,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box1),label2,0,1,1,2);
   gtk_table_attach_defaults(GTK_TABLE(box1),entry_montant,2,3,1,2);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_ok,1,2,2,3);
   gtk_table_set_row_spacing( GTK_TABLE (box1),0,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),1,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),2,10);
   gtk_table_set_col_spacing (GTK_TABLE (box1),0,5);
   gtk_widget_show_all(window_new);

}

int main(int argc,char *argv[])
{
   gtk_init(&argc,&argv);//initialization
   GtkWidget *princ_window;//declaration of the widgets
   GtkWidget *box1;
   GtkWidget *pMenuBar;
   GtkWidget *pMenu;
   GtkWidget *pMenuItem;
   princ_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//creation of the widgets
   g_signal_connect(G_OBJECT(princ_window),"delete-event",
                           G_CALLBACK(gtk_main_quit),NULL);

   /**creation du menu **/
   pMenuBar = gtk_menu_bar_new();
   pMenu = gtk_menu_new();
   pMenuItem = gtk_menu_item_new_with_label("Nouvelle depense");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(new_spent),
                                                 (GtkWidget*)princ_window);
   pMenuItem = gtk_menu_item_new_with_label("Nouveau gain");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(new_gain),
                                                 (GtkWidget*)princ_window);
   pMenuItem = gtk_menu_item_new_with_label("Quitter");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter),
                                                 (GtkWidget*)princ_window);

   pMenuItem = gtk_menu_item_new_with_label("Fichier");
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

    /** Second sous-menu **/
   pMenu = gtk_menu_new();
   pMenuItem = gtk_menu_item_new_with_label("Consulter montant depenses");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(consult_all),
                                                 (GtkWidget*)princ_window);

   pMenuItem =gtk_menu_item_new_with_label("Consulter descriptif depenses");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate",
                   G_CALLBACK(consult_descriptif),(GtkWidget*)princ_window);

   pMenuItem =gtk_menu_item_new_with_label("Consulter descriptif gains");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate",
                   G_CALLBACK(consult_gain),(GtkWidget*)princ_window);


   pMenuItem = gtk_menu_item_new_with_label("Consulter");
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);
   pMenu = gtk_menu_new();

   pMenuItem = gtk_menu_item_new_with_label("A propos de ...");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu),pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate",
   G_CALLBACK(OnAbout), (GtkWidget*) princ_window);

   pMenuItem = gtk_menu_item_new_with_label("?");
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

   gtk_container_set_border_width(GTK_CONTAINER(princ_window),10);
   box1=gtk_table_new( 10,10,TRUE);
   gtk_window_set_default_size(GTK_WINDOW(princ_window),320,200);
   gtk_container_add(GTK_CONTAINER(princ_window),box1);
   gtk_table_set_row_spacing( GTK_TABLE (box1),0,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),1,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),2,10);
   gtk_table_set_col_spacing (GTK_TABLE (box1),0,5);

   gtk_table_attach_defaults(GTK_TABLE(box1), pMenuBar,0,10,0,1);
   gtk_window_set_title(GTK_WINDOW(princ_window),"Que voulez vous?");
   gtk_window_set_position(GTK_WINDOW(princ_window),GTK_WIN_POS_CENTER);
   gtk_widget_show_all(princ_window);

   // if the year of the file is smaller than the actual year or if the year is
   // equal and the month is smaller than the actual month then goto create new_
   // month. this program will rename the old file with the date written in it
   // will create a new file named "descriptif_depenses.dat" and
   // "montant_depenses.dat". than the program will ask the given budget of the
   //    month and will write it into the file on the second line; the first
   //line
   // is the date of the month.same if the file doesen't exist;
   int month;
   int year;
   FILE *fmontant=fopen("montant_depenses.dat","rb");
   if(!fmontant)
      {
      new_month(princ_window,NULL,NULL);
      }
   fscanf(fmontant,"%d",&month);
   fscanf(fmontant,"%d",&year);
   fclose(fmontant);

   struct tm *tb;
   time_t t;
   tb = localtime(&t);
   time(&t);
   ctime(&t);
   int month_act= tb->tm_mon;
   int year_act = tb->tm_year;
   month_act = month_act+1;
   year_act = year_act-100;
   if(year_act > year || (year_act == year && month_act>month))
      new_month(princ_window,NULL,NULL);
   gtk_main();

return EXIT_SUCCESS;
}
