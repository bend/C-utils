#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include "new_month.h"
#include "consult.h"
#include "save.h"


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

int main(int argc,char *argv[])
{
   gtk_init(&argc,&argv);//initialization
   GtkWidget *princ_window;//declaration of the widgets
   GtkWidget *box1;
   GtkWidget *pMenuBar;
   GtkWidget *pMenu;
   GtkWidget *pMenuItem;
   GtkWidget *pImage;
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
                   G_CALLBACK(consult_depenses),(GtkWidget*)princ_window);

   pMenuItem =gtk_menu_item_new_with_label("Consulter descriptif gains");
   gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
   g_signal_connect(G_OBJECT(pMenuItem), "activate",
                   G_CALLBACK(consult_gains),(GtkWidget*)princ_window);


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
   box1=gtk_table_new( 10,5,FALSE);
   gtk_container_add(GTK_CONTAINER(princ_window),box1);
   gtk_table_set_row_spacing( GTK_TABLE (box1),0,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),1,10);
   gtk_table_set_row_spacing( GTK_TABLE (box1),2,10);
   gtk_table_set_col_spacing (GTK_TABLE (box1),0,5);
   pImage = gtk_image_new_from_file("./pic.png");
   gtk_table_attach_defaults(GTK_TABLE(box1), pMenuBar,0,10,0,1);
   gtk_table_attach_defaults(GTK_TABLE(box1), pImage, 0,10,1,5);
   gtk_window_set_title(GTK_WINDOW(princ_window),"Que voulez vous?");
   gtk_window_set_position(GTK_WINDOW(princ_window),GTK_WIN_POS_CENTER);
   gtk_window_set_resizable (GTK_WINDOW(princ_window),FALSE);
   gtk_window_set_default_size(GTK_WINDOW(princ_window),640,480);

   gtk_widget_show_all(princ_window);

   //if the year of the file is smaller than the actual year or if the year is
   //equal and the month is smaller than the actual month then goto create new_
   //month. this program will rename the old file with the date written in it
   //will create a new file named "descriptif_depenses.dat" and
   //"montant_depenses.dat". than the program will ask the given budget of the
   //month and will write it into the file on the second line; the first line
   // is the date of the month.same if the file doesen't exist;
   int month;
   int year;
   FILE *fmontant=fopen("montant_depenses.dat","rb");
   if(!fmontant)
      {
      new_month(princ_window);
      }
   else if(fmontant)
   {
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
      {
         new_month(princ_window);
      }
   }
   gtk_main();

   return EXIT_SUCCESS;
}
