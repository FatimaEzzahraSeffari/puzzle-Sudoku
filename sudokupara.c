#include <stdio.h>
#include <stdlib.h>    
#include <omp.h> 
//definir la taille du matrice N*N
#define N 12 
/*afficher la matrice */


void print(int arr[N][N])
{
	#pragma omp parallel
	#pragma omp parallel for
     for (int i = 0; i < N; i++)
      {
		#pragma omp parallel for
         for (int j = 0; j < N; j++)
            printf("%d ",arr[i][j]);
         printf("\n");
       }
}


//Vérifie si ce sera légal
// pour assigner num au
// ligne donnée, col
int isSafe(int grid[N][N], int row,
                       int col, int num)
{
	#pragma omp parallel
	#pragma omp parallel for
     
    // Vérifie si nous trouvons le même num
    // dans la ligne similaire, nous retournons 0
    for (int x = 0; x <= 11; x++)
        if (grid[row][x] == num)
            return 0;
 
    // Vérifie si nous trouvons le même num
    // dans la col similaire, nous retournons 0
	#pragma omp parallel for
    for (int x = 0; x <= 11; x++)
        if (grid[x][col] == num)
            return 0;
 
    // Vérifie si nous trouvons le même num dans le
    // matrice 3*3 particulière, on retourne 0
    int startRow = row - row % 3,
                 startCol = col - col % 3;
   #pragma omp parallel for
    for (int i = 0; i < 3; i++)
	#pragma omp parallel for
        for (int j = 0; j < 3; j++)
          
            if (grid[i + startRow][j + startCol] == num)
                return 0;
 
    return 1;
}
 
/* Prend une grille partiellement remplie et tente
pour attribuer des valeurs à tous les emplacements non attribués dans
de manière à répondre aux exigences de
Solution Sudoku (non-duplication entre les lignes,
colonnes et cases) */
int solveSudoku(int grid[N][N], int row, int col)
{
	 #pragma omp parallel
    
    //  nous sommes
    // retourne true pour éviter
   
    if (row == N - 1 && col == N)
        return 1;
 
    // Vérifiez si la valeur de la colonne devient 9 ,
    // nous passons à la ligne suivante et
    // la colonne commence à 0
    if (col == N)
    {
        row++;
        col = 0;
    }
   
    // Vérifie si la position actuelle
    // de la grille contient déjà
    // valeur >0, on itère pour la colonne suivante
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);
   #pragma omp parallel for
    for (int num = 1; num <= N; num++)
    {
        // Vérifiez s'il est sûr de placer
        // le nombre (1-9) dans le
        // ligne donnée ,col -> nous passons à la colonne suivante
        
        if (isSafe(grid, row, col, num)==1)
        {
            /* affectation du num dans le
               courant (ligne, colonne)
               position de la grille
               et en supposant notre numéro assigné
               dans le poste
               est correct     */
            grid[row][col] = num;

           // Vérification de la possibilité suivante avec next
            //  colonne
        
            if (solveSudoku(grid, row, col + 1)==1){
                  return 1;
            }
        }
       
        // Suppression du num attribué,
        // depuis notre hypothèse
        // avait tort, et nous passons au suivant
        // hypothèse avec
        // valeur numérique différente
        grid[row][col] = 0;
    }
    return 0;
}
 
int main()
{
   omp_set_num_threads(4);

double x = omp_get_wtime();
    // 0 signifie cellules non affectées
    int grid[N][N] = { {0,9, 10, 0 ,2, 0, 0, 0, 6, 4, 0, 11},
{1 ,0 ,0 ,5 ,0 ,8 ,0 ,0 ,0 ,0 ,9 ,0 },
{0 ,0, 0, 12, 0 ,0 ,0 ,4 ,0 ,2 ,0 ,0}, 
{2 ,4 ,0 ,0 ,0 ,3 ,0 ,10 ,0 ,0 ,0 ,0},
{0 ,0, 8, 0, 12, 4 ,0 ,0 ,0 ,0 ,2, 0}, 
{11 ,12 ,0 ,0 ,0 ,0 ,0 ,2 ,3 ,0 ,0 ,6}, 
{12 ,0, 0, 8, 7 ,0, 0, 0, 0, 0, 11, 3 },
{0 ,3 ,0 ,0 ,0 ,0 ,1 ,8 ,0 ,6 ,0 ,0 },
{0 ,0 ,0 ,0, 3, 0, 4, 0, 0, 0, 1, 8}, 
{0 ,0, 11 ,0, 10 ,0 ,0 ,0 ,8 ,0 ,0 ,0}, 
{0 ,6 ,0 ,0, 0, 0, 11, 0 ,10, 0, 0, 5}, 
{9 ,0 ,5 ,3 ,0 ,0 ,0 ,1 ,0 ,11 ,0 ,0}};
    if (solveSudoku(grid, 0, 0)==1)
        print(grid);
    else
        printf("No solution exists");
		double y = omp_get_wtime();
       
double z = y - x ;

printf ( "la duree dexecution est s: %f secondes \n " , z ) ;

 
 

 
    
    return 0;
}