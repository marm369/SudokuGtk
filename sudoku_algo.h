//
// Created by minou on 22/01/2024.
//

#ifndef SUDOKU_SUDOKU_ALGO_H
#define SUDOKU_SUDOKU_ALGO_H

#include "conflit.h"
#include <iostream>

#define N 9
typedef struct {
    int **puzzle;
    int **solution;
    int **initiale;
}sudoku;
class sudoku_algo
{
public:
    sudoku matrix,current;
    void init_sudoku(sudoku& s)
    {
        s.puzzle = new int*[N];
        s.solution = new int*[N];
        s.initiale = new int*[N];
        for (int i = 0; i < N; ++i)
        {
            s.puzzle[i] = new int[N];
            s.solution[i] = new int[N];
            s.initiale[i] = new int[N];
            for (int j = 0; j < N; ++j)
            {
                s.puzzle[i][j] = 0;
                s.solution[i][j] = 0;
                s.initiale[i][j] = 0;
            }
        }
    }
   sudoku_algo()
   {
       init_sudoku(current);
       init_sudoku(matrix);
   }
    void nullify_sudoku(sudoku *matrix)
    {

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                matrix->puzzle[i][j] = 0;
                matrix->solution[i][j] = 0;
                matrix->initiale[i][j] = 0;
            }
        }
    }
    void fill_k_empty_boxes(sudoku *matrix,int k)
    {
    int total_empty_boxes=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix->puzzle[i][j]==0) total_empty_boxes++;
        }
    }
    while(k--){
        int number = rand()%total_empty_boxes +1;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(matrix->puzzle[i][j]==0) number--;
                if(number==0){
                    matrix->puzzle[i][j] = matrix->solution[i][j];
                    goto out;
                }
            }
        }
        out:
        total_empty_boxes--;
    }
  }
    int select_random_number(int numvisited[N+1],int no_of_num_left){
        int n=no_of_num_left;
        int num = (rand()%n) +1;
        int count=0;
        for(int i=1;i<=N;i++){
            if(numvisited[i]==1){
                count++;
            }
            if(count==num){
                num = i;
                break;
            }
        }
        numvisited[num]=0;
        return num;
    }
    void diagonal_solve(sudoku *matrix){
        for(int diag =0;diag<N;diag+=M){
            int numvisited[N+1];
            int cellvisited[N+1];
            for(int i=0;i<=N;i++){
                numvisited[i] = cellvisited[i] = 1;
            }
            for(int emptyboxes=N;emptyboxes>=1;emptyboxes--){
                int cell = select_random_number(cellvisited,emptyboxes);
                int num = select_random_number(numvisited,emptyboxes);
                int x = (cell-1)/M;
                int y = (cell-1)%M;
                matrix->solution[diag+x][diag+y] = num;
            }
        }
    }
    void copy_box1_to_box2(int **box1,int **box2){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                box2[i][j]=box1[i][j];
            }
        }
    }
    void generate_puzzle(sudoku *matrix){
        int visited[N*N+1];
        for(int i=0;i<=N*N;i++){
            visited[i]=1;
        }
        puzzle_generator(matrix,visited,N*N);
    }
    void puzzle_generator(sudoku *matrix,int visited[N*N+1],int steps){
        if(steps==0) return ;
        int index = select_random_grid(visited,steps);
        int x = (index-1)/N;
        int y = (index-1)%N;
        int store = matrix->puzzle[x][y];
        matrix->puzzle[x][y] = 0;
        if(!unique_solution(matrix->puzzle)){
            matrix->puzzle[x][y]=store;
        }
        puzzle_generator(matrix,visited,steps-1);
    }
    int unique_solution(int **box){
        sudoku tempbox;
        init(&tempbox);
        copy_box1_to_box2(box,tempbox.puzzle);
        copy_box1_to_box2(box,tempbox.solution);
        solve_sudoku(tempbox.puzzle,0,0,1,N,1);
        solve_sudoku(tempbox.solution,0,0,N,1,-1);
        if(is_box1_equal_to_box2(tempbox.puzzle,tempbox.solution)) return 1;
        else return 0;
    }
    void init(sudoku *matrix){
        matrix->puzzle = (int**) malloc(sizeof(int*)*N);
        for(int i=0;i<N;i++){
            matrix->puzzle[i] = (int*) malloc(sizeof(int)*N);
            for(int j=0;j<N;j++){
                matrix->puzzle[i][j]=0;
            }
        }
        matrix->solution = (int**) malloc(sizeof(int*)*N);
        for(int i=0;i<N;i++){
            matrix->solution[i] = (int*) malloc(sizeof(int)*N);
            for(int j=0;j<N;j++){
                matrix->solution[i][j]=0;
            }
        }
    }
    int is_box1_equal_to_box2(int **box1,int **box2){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(box1[i][j]!=box2[i][j]) return 0;
            }
        }
        return 1;
    }
    int select_random_grid(int visited[N*N+1],int no_of_grids_left){
        int n=no_of_grids_left;
        int number = (rand() % n) + 1;
        int count1=0,index;
        for(int it=1;it<=N*N;it++){
            if(visited[it]==1){
                count1++;
            }
            if(count1==number){
                index =it;
                break;
            }
        }
        visited[index] = 0;
        return index;
    }
    int solve_sudoku(int **solution,int i,int j,int S,int E,int T){
        if(i==N)  return 1;
        if(j==N)  return solve_sudoku(solution,i+1,0,S,E,T);
        if(solution[i][j]!=0) return solve_sudoku(solution,i,j+1,S,E,T);
        for(int num = S;num != E + T;num = num + T){
            conflit c ;
            if(!c.Conflit(solution,i,j,num)){
                solution[i][j]=num;
                if(solve_sudoku(solution,i,j+1,S,E,T)){
                    return 1;
                }
                solution[i][j]=0;
            }
        }
        return 0;
    }


    int load_gpuzzle(int **puzzle,GtkWidget*gmatrix[N][N]){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(puzzle[i][j]!=0)
                {
                    char data[2];
                    strcpy(data,"0");
                    sprintf(data,"%d",puzzle[i][j]);
                    gtk_widget_set_name(gmatrix[i][j], "entry-style1");
                    gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]),data);
                }
                else
                {
                    gtk_widget_set_name(gmatrix[i][j], "entry-style2");
                    gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j])," ");
                }
            }
        }
    }
    int load_gtk_puzzle(int **puzzle, int **init, GtkWidget *gmatrix[N][N]) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                std::cout << puzzle[i][j];

                if(puzzle[i][j] != 0)
                {
                    char data[2];
                    strcpy(data, "0");
                    sprintf(data, "%d", puzzle[i][j]);
                    if(puzzle[i][j] == init[i][j]) {
                        gtk_widget_set_name(gmatrix[i][j], "entry-style1");
                    } else {
                        gtk_widget_set_name(gmatrix[i][j], "entry-style2");
                    }
                    gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]), data);
                } else {
                    gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]), " ");
                    gtk_widget_set_name(gmatrix[i][j], "entry-style2");
                }
            }
        }
    }

};

#endif //SUDOKU_SUDOKU_ALGO_H
