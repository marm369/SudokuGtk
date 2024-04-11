//
// Created by minou on 21/01/2024.
//

#ifndef SUDOKU_PLAN_H
#define SUDOKU_PLAN_H
#include <gtk/gtk.h>

#define N 9
#define M 3

class Plan {
public:
    GtkWidget *gmatrix[N][N];

    GtkWidget* createGameWidget() {
        GtkWidget *hbox, *vbox, *sep;

        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        for (int i = 0; i < N; i++) {
            hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
            for (int j = 0; j < N; j++) {
                gmatrix[i][j] = gtk_entry_new();
                gtk_widget_set_size_request(gmatrix[i][j],50,50);
                gtk_entry_set_max_length(GTK_ENTRY(gmatrix[i][j]), 2);
                gtk_entry_set_width_chars(GTK_ENTRY(gmatrix[i][j]), 2);
                gtk_box_pack_start(GTK_BOX(hbox), gmatrix[i][j], 0, 0, 0);

                // Add vertical separators after every three columns
                if ((j + 1) % M == 0 && j < N - 1) {
                    sep = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
                    gtk_widget_set_name(sep,"sep");
                    gtk_box_pack_start(GTK_BOX(hbox), sep, 0, 0, 1);
                }
            }
            gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 0);

            // Add a horizontal separator after every three rows except for the last row
            if ((i + 1) % M == 0 && i < N - 1) {
                sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
                gtk_widget_set_name(sep,"sep");
                gtk_box_pack_start(GTK_BOX(vbox), sep, 0, 0, 1);
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]), " ");
            }
        }

        return vbox;
    }
    Plan()
    {}


};


#endif //SUDOKU_PLAN_H
