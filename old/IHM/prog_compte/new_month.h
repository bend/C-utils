static GtkWidget *EntryBudget;
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>

void budget (GtkWidget *window, GtkWidget *button)
{
   FILE *fmontant = fopen("montant_depenses.dat","rb");
   char m[3];
   char y[3];
   char a[30]={"montant_du_"};
   char c[30]={"descriptif_du_"};
   char d[30]={"gain_du_"};
   if(fmontant)
   {
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
   }
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
   const char *montant = gtk_entry_get_text(GTK_ENTRY(EntryBudget));
   fprintf(fmontant,"%s\n",montant);//budget depense reste
   fprintf(fmontant,"0\n");
   fprintf(fmontant,"%s\n",montant);

   fclose(fdescriptif);
   fclose(fmontant);
   fclose(fgain);
   gtk_widget_destroy(window);
}

void new_month (GtkWidget *widget)
{
   GtkWidget *WindowBudget;
   GtkWidget *BoxBudget;
   GtkWidget *LabelBudget;
   GtkWidget *ButtonOk;
   GtkWidget *LabelMois;
   WindowBudget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   EntryBudget = gtk_entry_new();
   LabelBudget = gtk_label_new("Entrez le budget mensuel € ");
   LabelMois =gtk_label_new("Un nouveau mois a commencé");
   BoxBudget = gtk_table_new(2,3,FALSE);
   ButtonOk = gtk_button_new_with_label("Valider");
   gtk_container_add(GTK_CONTAINER(WindowBudget),BoxBudget);
   gtk_table_attach_defaults(GTK_TABLE(BoxBudget),LabelMois,0,2,0,1);
   gtk_table_attach_defaults(GTK_TABLE(BoxBudget),LabelBudget,0,1,1,2);
   gtk_table_attach_defaults(GTK_TABLE(BoxBudget),EntryBudget,1,2,1,2);
   gtk_table_attach_defaults(GTK_TABLE(BoxBudget),ButtonOk,1,2,2,3);
   gtk_table_set_row_spacing( GTK_TABLE (BoxBudget),0,10);
   gtk_table_set_row_spacing( GTK_TABLE (BoxBudget),1,10);
   gtk_table_set_row_spacing( GTK_TABLE (BoxBudget),2,10);
   gtk_table_set_col_spacing (GTK_TABLE (BoxBudget),0,5);
   gtk_table_set_col_spacing (GTK_TABLE (BoxBudget),1,5);
   gtk_table_set_col_spacing (GTK_TABLE (BoxBudget),2,5);
   gtk_window_set_resizable(GTK_WINDOW(WindowBudget),FALSE);
   gtk_window_set_title(GTK_WINDOW(WindowBudget),"Nouveau gain");
   gtk_window_set_default_size(GTK_WINDOW(WindowBudget),100,100);
   gtk_window_set_position(GTK_WINDOW(WindowBudget),GTK_WIN_POS_CENTER);
   gtk_container_set_border_width(GTK_CONTAINER(WindowBudget),10);
   gtk_entry_set_text(GTK_ENTRY(EntryBudget),"Budget");

   gtk_signal_connect_object(GTK_OBJECT(ButtonOk), "clicked",
      (GtkSignalFunc)budget,GTK_WINDOW(WindowBudget));

   gtk_widget_show_all(WindowBudget);

}


