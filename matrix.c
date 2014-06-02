/* matrix multiplications using threads
	Sharafat Ali -  MSCS13019
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* matrix size (rows and cols)*/
#define m 3
#define k 2
#define n 3 
 
/* input matrices*/
int A[m][k] = { {8,2}, {4,1}, {2,2} }; // 2X3 matrix
int B[k][n] = { {1,2,3}, {7,2,1} }; // second matrix 3X2

int C[m][n]; //matrix to show result (3X3)
 
void *func_multiply(void * indexArr); //calculates each cell of matrix
 
int main() //
{
    int i,j; // loops
    pthread_t thread_id[m][n];  
    int *val_index;//arry of indexes of values to be multiplied by the function
 
 
  for(i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++)
      {
          val_index = malloc(2 * sizeof(int));
          val_index[0] = i;//assign i and j locations to array to pass to thread
          val_index[1] = j;   
          // printf("IDEXES - > I am passing %d ", val_index[0]);
         //printf("and  %d ", val_index[1]);
            //printf("\n");
          pthread_create(&thread_id[i][j], NULL, *func_multiply, (void *) val_index);
            //free(val_index);
      }
  } 
  int a;
  int b;
  for(a = 0; a < m; a++)
  {
    for(b = 0; b < n; b++)
    {
      pthread_join(thread_id[a][b], NULL);
    }
  }    
      
// display result matrix
  for(i = 0; i < m; i++)
    { 
        printf("\n");// move to new row
        for(j = 0; j < n; j++)
        { 
            printf("%d\t", C[i][j]);// show result
        }
    }
 
  return 0;
}

void *func_multiply(void * indexArr)
{


  int *cellIndex;
  cellIndex = (int *) indexArr; // to integer array
 //printf("THREAD -> I am thread with %d ", cellIndex[0]);
 //printf("and  %d ", cellIndex[1]);
 //printf("\n");
  int x;
  for(x = 0; x < k; x++)
  {
    C[cellIndex[0]][cellIndex[1]] += (A[cellIndex[0]][x] * B[x][cellIndex[1]]);
  }    

  pthread_exit(0);

}
