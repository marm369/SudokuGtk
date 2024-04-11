#ifndef SUDOKU_SUDOKUINTERFACE_H
#define SUDOKU_SUDOKUINTERFACE_H
#include <gtk/gtk.h>
#include <iostream>
#include "Plan.h"
#include "button.h"
#include "window.h"
#include "sudoku_algo.h"
#include "print_sudoku.h"
#include "sauvegarder_jeu.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

class SudokuInterface {
public:
    GtkWidget* m_mainWindow;
    GtkWidget* m_stack;
    Plan *p = new Plan();
    GtkWidget* dialog;
    sudoku_algo *s = new sudoku_algo();
    struct CallbackData {
        SudokuInterface* self;
        GtkWidget* dialog;
        Plan * pl;
        sudoku_algo * sudo;
    };

    CallbackData* initialiser() {
        CallbackData* data = new CallbackData;
        data->self = this;
        data->dialog = dialog;
        data->pl = p;
        data->sudo = s;
        return data;
    }
    CallbackData* data;
    SudokuInterface() {
        data= initialiser();
        gtk_init(NULL, NULL);
        window *wind = new window(m_mainWindow);
        wind->loadCss("C:\\Users\\minou\\CLionProjects\\Sudoku\\style1.css");
        GtkWidget* fixed1 = gtk_fixed_new();
        button nv_btn= button(TRUE,"Nouveau jeu","nouveauJeuButton",150, 65,fixed1, 300, 510);
        button cont_btn= button(TRUE,"Continuer jeu","continuerJeuButton",130, 65,fixed1, 298, 600);
        g_signal_connect(nv_btn.bttn, "clicked", G_CALLBACK(on_nouveau_jeu_clicked), this);
        g_signal_connect(cont_btn.bttn, "clicked", G_CALLBACK(on_continuer_jeu_clicked), data);
        GtkWidget* image = gtk_image_new_from_file("C:\\Users\\minou\\CLionProjects\\Sudoku\\sudo.png");
        gtk_fixed_put(GTK_FIXED(fixed1), image, 200, 170);
        g_signal_connect(wind->win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        m_stack = gtk_stack_new();
        gtk_stack_set_transition_type(GTK_STACK(m_stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
        gtk_stack_set_transition_duration(GTK_STACK(m_stack), 500);
        // Initialisez l'objet Plan
        GtkWidget * page=p->createGameWidget();
        GtkWidget* fixed2 = gtk_fixed_new();
        gtk_fixed_put(GTK_FIXED(fixed2), page,150, 150);
        gtk_stack_add_named(GTK_STACK(m_stack), fixed1, "page1");

        button b1= button(FALSE,"","home",65, 65,fixed2, 20, 30);
        g_signal_connect(b1.bttn,"clicked",G_CALLBACK(come_back_home),this);

        button b2= button(FALSE,"","solution",65, 65,fixed2, 180, 650);
        g_signal_connect(b2.bttn,"clicked",G_CALLBACK(solve_gtk_sudoku),data);
        button b3= button(FALSE,"","reset",65, 65,fixed2, 300, 650);
        g_signal_connect(b3.bttn,"clicked",G_CALLBACK(reset),data);
        button b4= button(FALSE,"","hint",65, 65,fixed2, 420, 650);
        g_signal_connect(b4.bttn,"clicked",G_CALLBACK(hint_gtk_sudoku),data);
        button b5= button(FALSE,"","check",65, 65,fixed2, 545, 650);
        g_signal_connect(b5.bttn,"clicked",G_CALLBACK(check_gtk_sudoku),data);
        button b6= button(FALSE,"","save",65, 65,fixed2, 680, 30);
        g_signal_connect(b6.bttn,"clicked",G_CALLBACK(save_gtk_sudoku),data);
        gtk_stack_add_named(GTK_STACK(m_stack), fixed2, "page2");

        gtk_container_add(GTK_CONTAINER(wind->win), m_stack);

        gtk_widget_show_all(wind->win);
    }
    void run() {
        gtk_main();
    }
    static gboolean save_gtk_sudoku(GtkWidget* widget,gpointer data) {
        CallbackData* cb_data = static_cast<CallbackData*>(data);
        cb_data->self->load_puzzle(cb_data->sudo->current.puzzle);
        sauvegarder_jeu* s_j= new sauvegarder_jeu();
        s_j->s_a=*cb_data->sudo;
        GtkWidget *dial;
        dial = gtk_file_chooser_dialog_new("Save",GTK_WINDOW(cb_data->self->m_mainWindow),GTK_FILE_CHOOSER_ACTION_SAVE,"_Cancel",GTK_RESPONSE_CANCEL,"_Ok",GTK_RESPONSE_OK,NULL);
        int save_flag = 0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(strcmp(gtk_entry_get_text(GTK_ENTRY(cb_data->self->p->gmatrix[i][j]))," ")!=0){
                    save_flag = 1;
                    break;
                }
            }
            if(save_flag) break;
        }
        if(save_flag){
            gtk_widget_show_all(dial);
            gint resp = gtk_dialog_run(GTK_DIALOG(dial));
            if(resp == GTK_RESPONSE_OK){
                s_j->save_progress(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dial)));
                gtk_widget_destroy(dial);
            }
            else{
                gtk_widget_destroy(dial);
            }
        }
        else cb_data->self->open_dialog("Empty file cannot be saved",2);
        return FALSE;
    }
    static void on_nouveau_jeu_clicked(GtkWidget* widget, gpointer data) {
        SudokuInterface* sudokuInterface = static_cast<SudokuInterface*>(data);
        sudokuInterface->showDifficultyWindow();
    }
    static void on_continuer_jeu_clicked(GtkWidget* widget, gpointer data) {
        GtkWidget *dialog;
        CallbackData* cb_data = static_cast<CallbackData*>(data);
        sauvegarder_jeu* s_j= new sauvegarder_jeu();
        s_j->s_a=*cb_data->sudo;
        dialog = gtk_file_chooser_dialog_new("Choose a File",GTK_WINDOW(cb_data->self->m_mainWindow),GTK_FILE_CHOOSER_ACTION_OPEN,"_Cancel",GTK_RESPONSE_CANCEL,"_Ok",GTK_RESPONSE_OK,NULL);
        gtk_widget_show_all(dialog);
        gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if(resp==GTK_RESPONSE_OK){
            s_j->open_progress(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
            cb_data->sudo->load_gtk_puzzle(cb_data->sudo->current.puzzle,cb_data->sudo->matrix.initiale,cb_data->self->p->gmatrix);
        }
        gtk_stack_set_visible_child_name(GTK_STACK(cb_data->self->m_stack), "page2");
        gtk_widget_destroy(dialog);
    }

    void showDifficultyWindow() {
        dialog = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(dialog), " ");
        gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(m_mainWindow));
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
        gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
        gtk_widget_set_size_request(dialog, 400, 300);
        gtk_widget_set_name(dialog, "dialog1");

        gtk_window_set_decorated(GTK_WINDOW(dialog), FALSE);
        GtkWidget *fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), fixed);
        button facileButton= button(TRUE,"Facile","difficultyButton",130, 50,fixed,130, 40);
        button moyenButton= button(TRUE,"Moyen","difficultyButton",130, 50,fixed,130, 110);
        button difficileButton= button(TRUE,"Difficile","difficultyButton",110, 50,fixed,130, 180);
     //   button expertButton= button(TRUE,"Expert","difficultyButton",130, 50,fixed,130, 220);

        // Connect the button click signal to the member function
        if(!data)  cout<<"dd";
        g_signal_connect(facileButton.bttn, "clicked", G_CALLBACK(this->on_button_clicked),data);
        g_signal_connect(moyenButton.bttn, "clicked", G_CALLBACK(this->on_button_clicked),data);
        g_signal_connect(difficileButton.bttn, "clicked", G_CALLBACK(this->on_button_clicked),data);
     //   g_signal_connect(expertButton.bttn, "clicked", G_CALLBACK(this->on_button_clicked),data);

        gtk_widget_show_all(dialog);
    }
    static void on_button_clicked(GtkWidget* widget , gpointer data)
    {

        CallbackData* cb_data = static_cast<CallbackData*>(data);
        const gchar* button_name;
        if (cb_data->self->m_stack) {
            button_name =gtk_button_get_label(GTK_BUTTON(widget));
            gtk_stack_set_visible_child_name(GTK_STACK(cb_data->self->m_stack), "page2");
            gtk_widget_destroy(GTK_WIDGET(cb_data->self->dialog));
        }

        int k ;
        if(strcmp(button_name , "Facile") == 0)
        {
            k = rand() % 5 + 18;
        }
        else if(strcmp(button_name,"Moyen") == 0)
        {
            k = rand() % 5 + 10;
        }
        else if(strcmp(button_name,"Difficile")==0)
        {
            k=0;
        }
        /*
        else
        {

        }*/
        cb_data->sudo->nullify_sudoku(&cb_data->sudo->matrix);
        cb_data->sudo->diagonal_solve(&cb_data->sudo->matrix);
        cb_data->sudo->solve_sudoku(cb_data->sudo->matrix.solution, 0, 0, 1, N, 1);
        cb_data->sudo->copy_box1_to_box2(cb_data->sudo->matrix.solution,cb_data->sudo->matrix.puzzle);
        cb_data->sudo->generate_puzzle(&cb_data->sudo->matrix);
        cb_data->sudo->fill_k_empty_boxes(&cb_data->sudo->matrix,k);
        cb_data->sudo->copy_box1_to_box2(cb_data->sudo->matrix.puzzle,cb_data->sudo->matrix.initiale);
        cb_data->sudo->load_gpuzzle(cb_data->sudo->matrix.puzzle,cb_data->self->p->gmatrix);
        cb_data->sudo->copy_box1_to_box2(cb_data->sudo->matrix.puzzle,cb_data->sudo->current.puzzle);
    }

    int load_puzzle(int **puzzle){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                const char *data = gtk_entry_get_text(GTK_ENTRY(p->gmatrix[i][j]));
                if(strcmp(data," ")==0){
                    puzzle[i][j] = 0;
                }
                else{
                    puzzle[i][j] = atoi(data);
                }
            }
        }
    }


void get_a_hint(sudoku *current) {
    CallbackData* cb_data = static_cast<CallbackData*>(data);
    // Liste des positions des cellules vides
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (current->puzzle[i][j] == 0) {
                emptyCells.push_back(std::make_pair(i, j));
            }
        }
    }
    if (emptyCells.empty()) {
        // Aucune cellule vide, pas besoin de hint
        return;
    }
    // Mélanger les positions des cellules vides
    std::random_shuffle(emptyCells.begin(), emptyCells.end());
    // Choisir une position aléatoire parmi les cellules vides mélangées
    int pos = rand() % emptyCells.size();
    int i = emptyCells[pos].first;
    int j = emptyCells[pos].second;
    // Donner l'indice dans la cellule choisie
    char donne[2];
    sprintf(donne, "%d",cb_data->sudo->matrix.solution[i][j]);

    gtk_widget_set_name(cb_data->self->p->gmatrix[i][j], "entr");
    gtk_entry_set_text(GTK_ENTRY(cb_data->self->p->gmatrix[i][j]), donne);

    // Mettre à jour la grille actuelle
    current->puzzle[i][j] =cb_data->sudo->matrix.solution[i][j];
}

void open_dialog(const char *message , int style) {
        GtkWidget *dialog = gtk_message_dialog_new(
                GTK_WINDOW(m_mainWindow),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_NONE,
                "%s", message
        );
        if(style == 1)
        {
            gtk_widget_set_name(dialog, "custom_dialog1");
        }
        else if(style == 2)
        {
            gtk_widget_set_name(dialog, "custom_dialog2");
        }
        else
        {
            gtk_widget_set_name(dialog, "custom_dialog3");
        }

        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    static void come_back_home(GtkWidget* widget ,gpointer data )
    {
        SudokuInterface* cb_data = static_cast<SudokuInterface*>(data);
        const gchar* button_name;
        if (cb_data->m_stack) {
            gtk_stack_set_visible_child_name(GTK_STACK(cb_data->m_stack), "page1");

        }
    }

    static void reset(GtkWidget *widget , gpointer data){
        CallbackData* cb_data = static_cast<CallbackData*>(data);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(cb_data->sudo->matrix.puzzle[i][j]!=0){
                    char data[2];
                    strcpy(data,"0");
                    sprintf(data,"%d",cb_data->sudo->matrix.puzzle[i][j]);
                    gtk_entry_set_text(GTK_ENTRY(cb_data->self->p->gmatrix[i][j]),data);
                }
                else gtk_entry_set_text(GTK_ENTRY(cb_data->self->p->gmatrix[i][j])," ");
            }
        }
    }
    static void solve_gtk_sudoku(GtkWidget *widget,gpointer data){
        CallbackData* cb_data = static_cast<CallbackData*>(data);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                char data[2];
                strcpy(data,"0");
                sprintf(data,"%d",cb_data->sudo->matrix.solution[i][j]);
                gtk_entry_set_text(GTK_ENTRY(cb_data->self->p->gmatrix[i][j]),data);


            }
        }
    }
    static void check_gtk_sudoku(GtkWidget *widget,gpointer data){
        CallbackData* cb_data = static_cast<CallbackData*>(data);
        cb_data->self->load_puzzle(cb_data->sudo->current.puzzle);
        int finished_flag = 1;
        int error_check_flag = 0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(cb_data->sudo->current.puzzle[i][j]==0) finished_flag=0;
                else if(cb_data->sudo->current.puzzle[i][j]!=cb_data->sudo->matrix.solution[i][j]) {
                    error_check_flag=1;
                    break;
                }
            }
            if(error_check_flag) break;
        }
        if(finished_flag){
            cb_data->self->open_dialog("Congratulations!, You have solved the sudoku",1);
            return;
        }
        if(error_check_flag) cb_data->self->open_dialog("Your sudoku is incorrect",2);
        else   cb_data->self->open_dialog("Progress so far is correct",3);
    }
    static void hint_gtk_sudoku(GtkWidget *widget,gpointer data)
    {
        CallbackData* cb_data = static_cast<CallbackData*>(data);
        cb_data->self->load_puzzle(cb_data->sudo->current.puzzle);
        cb_data->self->get_a_hint(&cb_data->sudo->current);
    }
};
#endif //SUDOKU_SUDOKUINTERFACE_H
