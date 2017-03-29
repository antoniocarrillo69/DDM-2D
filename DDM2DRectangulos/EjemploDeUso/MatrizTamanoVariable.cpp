//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices de tamaño variable                                   //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.igeofcu.unam.mx                                                    //
// Página:   http://www.mmc.igeofcu.unam.mx/acl                                             //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los términos de la Licencia Pública General de GNU según es                         //
// publicada por la Free Software Foundation, bien de la versión 2 de                       //
// dicha Licencia o bien (según su elección) de cualquier versión                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea útil, pero SIN                   //
// NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la                        //
// Licencia Pública General de GNU para más detalles.                                       //
//                                                                                          //
// Debería haber recibido una copia de la Licencia Pública General junto                    //
// con este programa. Si no ha sido así, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////



#include <stdlib.h>
#include <math.h>
#include "MatrizTamanoVariable.hpp"
#include "Ctrl_vis.hpp"




// Solicita la memoria necesaria para contener los valores de la matriz
// @param ren Número de renglones de la matriz
// @param col Número de columnas de la matriz
// @param ban Tamaño de la banda
void MatrizTamanoVariable::solicitaMemoria(const int ren, const int *col)
{
#ifdef DEPURAR
   if (ren < 0)
   {
      printf("\nError al definir Matriz de Tamaño Variable");
      exit(1);
   }
   for (int i = 0; i < ren; i++)
   {
      if (col[i] < 0)
      {
         printf("\nError en el tamaño de las columnas al definir Matriz de Tamaño Variable");
         exit(1);
      }
   }
#endif

   int i;

   // Tamaño de la matriz
   Tipo_Matriz = MATRIZ_TAMANO_VARIABLE;
   Ren = ren;
   Col = -1;

   // Solicita memoria para almacenar el tamaño de la columna por cada renglon
   TC = new int[Ren];
   if (TC == NULL) faltaMemoria();
   for (i = 0; i < Ren; i++) TC[i] = col[i];


   // Solicita memoria para el contenido de la matriz
   M = new ldouble *[Ren];
   if (M == NULL) faltaMemoria();
   for (i = 0; i < Ren; i++)
   {
      M[i] = new ldouble[TC[i]];
      if (M[i] == NULL) faltaMemoria();
   }
   inicializa(0.0);
}


// Inicializa la matriz al valor indicado
// @param val Valor por omisión para inicializar la matriz */
void MatrizTamanoVariable::inicializa(ldouble val)
{
   int i, j;
   for (i = 0; i < Ren; i++)
      for (j = 0; j < TC[i]; j++) M[i][j] = val;
}



// Libera la memoria solicitada para la matriz
void MatrizTamanoVariable::liberaMemoria(void)
{
   int i;

   // Libera memoria para el contenido de la matriz
   for (i = 0; i < Ren; i++)
   {
      delete []M[i];
      M[i] = NULL;
   }
   delete []M;
   M = NULL;

   delete []TC;
   TC = NULL;
}

#ifdef DEPURAR

// Asigna el valor indicado en el renglo y columna solicitado
// @param ren Renglon
// @param col Columna
// @param val Valor
void MatrizTamanoVariable::asigna(const int ren, const int col, const ldouble val)
{
   if (ren < 0 || ren >= Ren || col < 0 || col >= TC[ren])
   {
      printf("\nError al asignar, indices desbordados (%d, %d)\n", ren,col);
      visualizaInformacion();
      exit(1);
   }
   M[ren][col] = val;
}



// Retorna el número de columna cuando se para en el renglon e indice de la banda
// @param ren Número de renglon
// @param ind Número de indice
// @return Número de columna cuando se para en el renglon e indice de la banda
ldouble MatrizTamanoVariable::retorna(const int ren, const int col)
{
   if (ren < 0 || ren >= Ren || col < 0 || col >= TC[ren])
   {
      printf("\nError al recuperar, indices desbordados (%d, %d)\n", ren,col);
      visualizaInformacion();
      visualizaMatricesInternas();
      exit(1);
   }
   return (M[ren][col]);
}
#endif




// Copia el contenido de la matriz a la matriz pasada como parámetro
// @param a Puntero a una Matriz
void MatrizTamanoVariable::copia(MatrizTamanoVariable *a)
{
   int i, k;

   for (i = 0; i < Ren; i++)
   {
      for (k = 0; k < TC[i]; k++)
      {
         a->asigna(i,k,M[i][k]);
      }
   }
}





/// Visualiza las matrices internas usadas para soportar a las matrices bandadas
void MatrizTamanoVariable::visualizaMatricesInternas(void)
{
   int i, j;
   Ctrl_visualizacion cv;

   visualizaInformacion();

   // Visualiza la matriz de datos
   printf("\n\nMatriz de Datos\n");
   for (i = 0; i < renglones(); i++)
   {
      for (j = 0; j < TC[i]; j++)
      {
         cv.visualiza_e(M[i][j]);
      }
      printf("\n");
   }

   // Visualiza la matriz de indices
   printf("\n\nNumero de Columnas\n");
   for (i = 0; i < renglones(); i++)
   {
      cv.visualiza(TC[i]);
      printf("\n");
   }
}



// Retorna el máximo tamaño en todas las columnas que sean distintos de cero
// @return Máximo tamaño de columnas ocupadas en la matriz
int MatrizTamanoVariable::maximoTamanoColumnaOcupado(void)
{
   int i, j, k, max = 0;
   for (i = 0; i < renglones(); i++)
   {
      k = 0;
      for (j = 0; j < TC[i]; j++)
      {
         if (retorna(i,j) != 0.0) k ++;
      }
      if (k > max) max = k;
   }
   return max;
}


// Retorna el número de entradas distintas de cero en la matriz
// @return Número de entradas distintas de cero en la matriz
int MatrizTamanoVariable::entradasDistintasCero(void)
{
   int i, j, max = 0;
   for (i = 0; i < renglones(); i++)
   {
      for (j = 0; j < TC[i]; j++)
      {
         if (retorna(i,j) != 0.0) max ++;
      }
   }
   return max;
}

