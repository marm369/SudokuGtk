
#ifndef SUDOKU_SAUVEGARDER_JEU_H
#define SUDOKU_SAUVEGARDER_JEU_H
#include <iostream>
#include "sudoku_algo.h"
#define N 9
#define M 3
class sauvegarder_jeu{
public:
    sudoku_algo s_a;
void open_progress(char *file_path){
    FILE *pointer = fopen(file_path,"r");

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fscanf(pointer,"%d",(&s_a.matrix.initiale[i][j]));

        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fscanf(pointer,"%d",(&s_a.matrix.puzzle[i][j]));
            s_a.matrix.puzzle[i][j]-=1;
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fscanf(pointer,"%d",&s_a.matrix.solution[i][j]);
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fscanf(pointer,"%d",&s_a.current.puzzle[i][j]);
        }
    }
    fclose(pointer);
}
void save_progress(char *file_path){
    FILE *pointer = fopen(file_path,"w+");
    if(!pointer){
        printf("Couldn't save the progress due to a file error\n");
    }
    else{
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",s_a.matrix.initiale[i][j]);
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",s_a.matrix.puzzle[i][j]+1);
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",s_a.matrix.solution[i][j]);
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",s_a.current.puzzle[i][j]);
            }
        }
        fclose(pointer);
    }

}
};
#endif //SUDOKU_SAUVEGARDER_JEU_H
