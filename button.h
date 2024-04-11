//
// Created by minou on 22/01/2024.
//

#ifndef SUDOKU_BUTTON_H
#define SUDOKU_BUTTON_H
#include <gtk/gtk.h>
class button
{
public:
    GtkWidget * bttn;
    button(bool k ,const char * label, const char* nom, gint width, gint height, GtkWidget *fixed, int x, int y) {
        if(k)
        {
            bttn=gtk_button_new_with_label(label);
        }
        else
        {
            bttn = gtk_button_new();
        }
        gtk_widget_set_name(GTK_WIDGET(bttn),nom);
        gtk_widget_set_size_request(GTK_WIDGET(bttn), width, height);
        gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(bttn), x, y);
        gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(bttn)), "circular");
    }

};
#endif //SUDOKU_BUTTON_H
