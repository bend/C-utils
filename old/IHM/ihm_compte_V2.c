#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

static GtkWidget *princ_window;

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

void new_spent (GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
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
   label_m = gtk_label_new("Montant total de vos depenses : ");
   label_r = gtk_label_new("Montant restant de votre budget : ");

   gtk_table_attach_defaults(GTK_TABLE(box1),label_m,1,5,1,3);
   gtk_table_attach_defaults(GTK_TABLE(box1),label_r, 1,5, 5,7);
   gtk_table_attach_defaults(GTK_TABLE(box1),montant,6,9,1,3);
   gtk_table_attach_defaults(GTK_TABLE(box1),reste, 6,9, 5,7);
   gtk_widget_show_all(window_consult);
}

void consult_descriptif(GtkWidget *widget, GdkEventButton *event ,gpointer data)
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
   gtk_signal_connect_object(GTK_OBJECT(button_quit), "clicked",
      (GtkSignalFunc)gtk_widget_destroy,GTK_OBJECT(window_consult));

   box1=gtk_table_new( 3,2,TRUE);
   gtk_container_add(GTK_CONTAINER(window_consult),box1);
   gtk_table_attach_defaults(GTK_TABLE(box1),button_quit,1,2,0,1);
   gtk_window_set_position(GTK_WINDOW(window_consult),GTK_WIN_POS_CENTER);
   gtk_widget_show_all(window_consult);
}

void new_month (GtkWidget *widget, GdkEventButton *event ,gpointer data)
{
   GtkWidget* pBoite;
   GtkWidget* pEntry;
   
   const char *date;
   pBoite = gtk_dialog_new_with_buttons("Saisie date",
                  GTK_WINDOW(princ_window),
                  GTK_DIALOG_MODAL,
                  GTK_STOCK_OK,GTK_RESPONSE_OK,
                  GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
   pEntry = gtk_entry_new();
   gtk_entry_set_text(GTK_ENTRY(pEntry),
                  "Saisissez la date du mois dernier(mm-aaaa)");
   gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pEntry, TRUE, FALSE,0);
   gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
   switch (gtk_dialog_run(GTK_DIALOG(pBoite)))
   {
      case GTK_RESPONSE_OK:
            date = gtk_entry_get_text(GTK_ENTRY(pEntry));
            break;
      case GTK_RESPONSE_CANCEL:
         goto end;
      case GTK_RESPONSE_NONE:
      default:
            break;
   }
   
   printf("%s\n",date);
   char a[30]={"montant_du_"};
   char c[30]={"descriptif_du_"};
   int i,j;
   i=strlen(date);
   strncat(a,date,i);
   strncat(c,date,i);
   printf("%s\n",a);
   fflush(stdout);


   if (rename("montant_depenses.dat",a)==-1 &&
       rename("descriptif_depenses.dat",c)==-1);
   {

         GtkWidget *perror;
         perror = gtk_message_dialog_new (GTK_WINDOW(pBoite),
         GTK_DIALOG_MODAL,
         GTK_MESSAGE_INFO,
         GTK_BUTTONS_OK,
         "La date entrée est invalide\n"
         "veuillez ressaisir la date (mm-aaaa)");
         gtk_dialog_run(GTK_DIALOG(perror));
         gtk_widget_destroy(perror);
         gtk_widget_destroy(pBoite);
         new_month(widget,event, data);

   }
   FILE *fdescriptif =fopen("descriptif_depenses.dat","wb");
   FILE *fmontant =fopen("montant_depenses.dat","wb");

   GtkWidget* pBoite2;
   GtkWidget* pEntry2;
   
   const char *value;
   pBoite2 = gtk_dialog_new_with_buttons("Saisie montant",
                  GTK_WINDOW(pBoite),
                  GTK_DIALOG_MODAL,
                  GTK_STOCK_OK,GTK_RESPONSE_OK,
                  GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
   pEntry2 = gtk_entry_new();
   gtk_entry_set_text(GTK_ENTRY(pEntry2),
                  "Saisissez le budget du mois");
   gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite2)->vbox), pEntry2, TRUE,
                                                               FALSE,0);
   gtk_widget_show_all(GTK_DIALOG(pBoite2)->vbox);
   switch (gtk_dialog_run(GTK_DIALOG(pBoite2)))
   {
      case GTK_RESPONSE_OK:
            value = gtk_entry_get_text(GTK_ENTRY(pEntry));
            break;
      case GTK_RESPONSE_CANCEL:
            goto end;
      case GTK_RESPONSE_NONE:
      default:
            break;

   }
   fprintf(fmontant,"%d\n",value);
   fclose(fdescriptif);
   fclose(fmontant);
end:
   gtk_widget_destroy(pBoite2);
   gtk_widget_destroy(pBoite);
      
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

   //creation du menu
   pMenuBar = gtk_menu_bar_new();
   pMenu = gtk_menu_new();
   pMenuItem = gtk_menu_item_new_with_label("nouvelle depense");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(new_spent),
                                                 (GtkWidget*)princ_window);
   pMenuItem = gtk_menu_item_new_with_label("Nouveau mois");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(new_month),
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
   pMenuItem = gtk_menu_item_new_with_label("consulter montant depenses");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(consult_all),
                                                 (GtkWidget*)princ_window);
   pMenuItem =gtk_menu_item_new_with_label("consulter descriptif depenses");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate",
                     G_CALLBACK(consult_descriptif),(GtkWidget*)princ_window);
   pMenuItem = gtk_menu_item_new_with_label("Consulter");
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);
   pMenu = gtk_menu_new();
   pMenuItem = gtk_menu_item_new_with_label("a propos de ...");
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
