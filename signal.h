//
// Created by minou on 22/01/2024.
//

#ifndef SUDOKU_SIGNAL_H
#define SUDOKU_SIGNAL_H
#include <gtk/gtk.h>
#define N 9
#define M 3

class signal
{
    void get_a_hint(sudoku *current){
        int count=0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(current->puzzle[i][j]==0) count++;
            }
        }
        if(count==0) return;
        int pos = rand()%count+1;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(current->puzzle[i][j]==0) pos--;
                if(pos==0){
                    char data[2];
                    strcpy(data,"0");
                    sprintf(data,"%d",s->matrix.solution[i][j]);
                    gtk_entry_set_text(GTK_ENTRY(p->gmatrix[i][j]),data);
                    current->puzzle[i][j] = s->matrix.solution[i][j];
                }
            }
        }
    }
    void open_dialog(const char* message) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

};
#endif //SUDOKU_SIGNAL_H
