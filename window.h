//
// Created by minou on 22/01/2024.
//

#ifndef SUDOKU_WINDOW_H
#define SUDOKU_WINDOW_H
#include <gtk/gtk.h>
class window
{

public:
    GtkWidget*win;
    window(GtkWidget * m_mainWindow){
    m_mainWindow=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(m_mainWindow), "Sudoku Game");
    gtk_container_set_border_width(GTK_CONTAINER(m_mainWindow), 10);
    gtk_window_set_default_size(GTK_WINDOW(m_mainWindow), 800, 800);
    gtk_window_set_position(GTK_WINDOW(m_mainWindow), GTK_WIN_POS_CENTER);
    GdkPixbuf* icon = gdk_pixbuf_new_from_file("C:\\Users\\minou\\CLionProjects\\Sudoku\\icon.png", NULL);
    gtk_window_set_icon(GTK_WINDOW(m_mainWindow), icon);
    gtk_window_set_resizable(GTK_WINDOW(m_mainWindow), FALSE);
    GdkRGBA color;
    gdk_rgba_parse(&color, "#F5F6FA");
    gtk_widget_override_background_color(m_mainWindow, GTK_STATE_FLAG_NORMAL, &color);
    win = m_mainWindow;
    }
    void loadCss(const char* path) {

        GtkCssProvider *css_provider;
        css_provider = gtk_css_provider_new();
        gtk_css_provider_load_from_path(css_provider,  path, NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                                  GTK_STYLE_PROVIDER(css_provider),
                                                  GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
};
#endif //SUDOKU_WINDOW_H
