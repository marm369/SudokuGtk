//
// Created by minou on 22/01/2024.
//

#ifndef SUDOKU_CONFLIT_H
#define SUDOKU_CONFLIT_H
#define N 9
#define M 3
class conflit{
public:
    // Vérifie si le nombre 'num' provoque un conflit dans la ligne 'i'.
    int estConflitLigne(int **grille, int ligne, int colonne, int num) {
        for (int c = 0; c < N; ++c) {
            if (c != colonne && grille[ligne][c] == num) {
                return 1;  // Il y a un conflit dans la ligne.
            }
        }
        return 0;  // Pas de conflit dans la ligne.
    }

// Vérifie si le nombre 'num' provoque un conflit dans la colonne 'j'.
    int estConflitColonne(int **grille, int ligne, int colonne, int num) {
        for (int r = 0; r < N; ++r) {
            if (r != ligne && grille[r][colonne] == num) {
                return 1;  // Il y a un conflit dans la colonne.
            }
        }
        return 0;  // Pas de conflit dans la colonne.
    }

// Vérifie si le nombre 'num' provoque un conflit dans la boîte 3x3 correspondante.
    int estConflitBoite(int **grille, int ligne, int colonne, int num) {
        int xOffset[2 * M - 1], yOffset[2 * M - 1];
        for (int i = 0; i < 2 * M - 1; ++i) {
            xOffset[i] = i - M + 1;
            yOffset[i] = i - M + 1;
        }

        int xLimiteInf = M - 1 - ligne % M;        // Limite inférieure en x
        int xLimiteSup = 2 * (M - 1) - ligne % M;  // Limite supérieure en x
        int yLimiteInf = M - 1 - colonne % M;      // Limite inférieure en y
        int yLimiteSup = 2 * (M - 1) - colonne % M;  // Limite supérieure en y

        for (int x = xLimiteInf; x <= xLimiteSup; ++x) {
            int xNouveau = ligne + xOffset[x];
            for (int y = yLimiteInf; y <= yLimiteSup; ++y) {
                int yNouveau = colonne + yOffset[y];
                if (!(xNouveau == ligne && yNouveau == colonne) && grille[xNouveau][yNouveau] == num) {
                    return 1;  // Il y a un conflit dans la boîte.
                }
            }
        }

        return 0;  // Pas de conflit dans la boîte.
    }

// Vérifie si le nombre 'num' provoque un conflit dans la ligne, la colonne ou la boîte.
    int Conflit(int **grille, int ligne, int colonne, int num) {
        return estConflitLigne(grille, ligne, colonne, num) || estConflitColonne(grille, ligne, colonne, num) || estConflitBoite(grille, ligne, colonne, num);
    }
};
#endif //SUDOKU_CONFLIT_H
