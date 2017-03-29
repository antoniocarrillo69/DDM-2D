//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices dispersas de punto flotante                          //
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
#include "MatrizDispersaComp.hpp"
#include "Ctrl_vis.hpp"



#define EPS 1e-14

// Solicita la memoria necesaria para contener los valores de la matriz
// @param ren Número de renglones de la matriz
// @param col Número de columnas de la matriz
// @param ban Tamaño de la banda
void MatrizDispersaComp::solicitaMemoria(const int ren, const int col, const int ban)
{
   int i;

   // Tamaño de la matriz
   Tipo_Matriz = MATRIZ_DISPERSA_COMPACTA;
   Ren = ren;
   Col = col;
   Ban = ban > col? col : ban;

   // Solicita memoria para el contenido de la matriz
   M = new ldouble *[Ren];
   if (M == NULL) faltaMemoria();
   for (i = 0; i < Ren; i++) M[i] = NULL;


   // Solicita memoria para almacenar la columna dentro de la banda de la matriz
   J = new int *[Ren];
   if (J == NULL) faltaMemoria();
   for (i = 0; i < Ren; i++) J[i] = NULL;

   // Inicializacion de arreglos para compactar
   C_IndDat = new int[Ren];
   if (C_IndDat == NULL) faltaMemoria();
   for (i = 0; i < Ren; i++) C_IndDat[i] = -1;
   C_IndDat[0] = 0;
   C_NumRen = 0;
   Ultimo = -1;
}

// Libera la memoria solicitada para la matriz
void MatrizDispersaComp::liberaMemoria(void)
{
   int i;

   // Libera memoria para el contenido de la matriz
   if (M)
   {
      for (i = 0; i <= C_NumRen; i++)
      {
         delete []M[C_IndDat[i]];
      }
      for (i = 0; i < Ren; i++) M[i] = NULL;
      delete []M;
      M = NULL;
   }
   // Libera memoria para almacenar la columna dentro de la banda de la matriz
   if (J)
   {
      for (i = 0; i < Ren; i++)
      {
         delete []J[i];
         J[i] = NULL;
      }
      delete []J;
      J = NULL;
   }

   // Libera los arreglos usados cuando la matriz se compacta
   delete []C_IndDat;
   C_IndDat = NULL;
}


// Asigna el valor indicado en el renglo y columna solicitado
// @param ren Renglon
// @param col Columna
// @param val Valor
void MatrizDispersaComp::asigna(const int ren, const int col, const ldouble val)
{
#ifdef DEPURAR
   if (ren < 0 || ren >= Ren || col < 0 || col >= Col)
   {
      printf("\nError al asignar, indices desbordados (%d, %d)\n", ren,col);
      visualizaInformacion();
      exit(1);
   }
#endif


   int i, k;

   // Solicita la memoria necesaria para almacenar los datos del renglon
   if (M[ren] == NULL)
   {
      compactaMatriz(Ultimo);
      C_IndDat[C_NumRen] = ren;
      M[ren] = new ldouble[Ban];
      if (M[ren] == NULL) faltaMemoria();
      J[ren] = new int[Ban];
      if (J[ren] == NULL) faltaMemoria();
      for (i = 0; i < Ban; i++)
      {
         M[ren][i] = 0.0;
         J[ren][i] = -1;
      }
   }


   // Asignación de un valor igual a cero dentro de la matriz bandada
   if (val == 0.0)
   {
      // Checar que no existan valores en esa posición, en caso de existir, eliminar este valor
      k = 0;
      while (k < Ban)
      {
         if (J[ren][k] == -1) break;
         // Columna encontrada
         if (J[ren][k] == col)
         {
            // Se reacomodan los valores de la banda
            for (i = k+1; i < Ban; i++)
            {
               M[ren][i-1] = M[ren][i];
               J[ren][i-1] = J[ren][i];
            }
            M[ren][Ban-1] = 0.0;
            J[ren][Ban-1] = -1;
            return;
         }
         // Busca la siguiente columna
         k++;
      }
      return;
   }

   // Asignación de un valor distinto de cero dentro de la matriz bandada
   Ultimo = ren;
   k = 0;
   while (J[ren][k] != -1 && k < Ban)
   {
      // Columna encontrada
      if (J[ren][k] == col)
      {
         // Se cambia el valor
         M[ren][k] = val;
         return;
      }
      // Busca la siguiente columna
      k++;
#ifdef DEPURAR
      if (k >= Ban)
      {
         printf("\nError al asignar, banda desbordada (%d, %d)\n", ren,col);
         visualizaInformacion();
         exit(1);
      }
#endif
   }
   // Se introduce el valor en el primer lugar libre encontrado
   M[ren][k] = val;
   J[ren][k] = col;

}



// Retorna el número de columna cuando se para en el renglon e indice de la banda
// @param ren Número de renglon
// @param ind Número de indice
// @return Número de columna cuando se para en el renglon e indice de la banda
ldouble MatrizDispersaComp::retorna(const int ren, const int col)
{
#ifdef DEPURAR
   if (ren < 0 || ren >= Ren || col < 0 || col >= Col)
   {
      printf("\nError al recuperar, indices desbordados (%d, %d)\n", ren,col);
      visualizaInformacion();
      visualiza(0);
      visualizaMatricesInternas();
      exit(1);
   }
#endif

   if (M[ren] == NULL) return 0.0;

   int k = 0;
   // Busqueda de la columna
   while (J[ren][k] != -1)
   {
      // Columna encontrada
      if (J[ren][k] == col)
      {
         return (M[ren][k]);
      }
      k++;
      if (k >= Ban) break;
   }

   // Columna no encontrada, se asume que el valor guardado es cero
   return 0.0;
}


// Retorna el número de columnas de la banda para el renglon indicado
// @param ren Número de renglon
// @return Número de columnas de la banda para el renglon solicitado
int MatrizDispersaComp::retornaNumeroColumnasBanda(int ren)
{
#ifdef DEPURAR
   if (ren < 0 || ren >= Ren)
   {
      printf("\nError al buscar el renglon solicitado, indice desbordado %d\n", ren);
      visualizaInformacion();
      exit(1);
   }
#endif

   if (M[ren] == NULL) return 0;
   int k = 0;
   // Retorna el tamaño de la banda
   while (k < Ban)
   {
      if (J[ren][k] != -1) break;
      k++;
   }
   return k;
}



// Copia el contenido de la matriz a la matriz pasada como parámetro
// @param a Puntero a una Matriz
void MatrizDispersaComp::copia(Matriz *a)
{
   int i, k;

   for (i = 0; i < Ren; i++)
   {
      if (M[i] == NULL) continue;
      for (k = 0; k < Ban; k++)
      {
         if (J[i][k] == -1) break;
         a->asigna(i,J[i][k],M[i][k]);
      }
   }
}



//Multiplica la matriz por el escalar pasado como parametro
// @param esc Escalar
void MatrizDispersaComp::multiplica(ldouble esc)
{
   int i, k;

   for (i = 0; i < Ren; i++)
   {
      if (M[i] == NULL) continue;
      for (k = 0; k < Ban; k++)
      {
         if (J[i][k] == -1) break;
         M[i][k] *= esc;
      }
   }
}


// Multiplica la matriz A por la matriz B
// @param a Puntero a matriz densa
// @param b Puntero a matriz densa
void MatrizDispersaComp::multiplica(MatrizDispersaComp *a, MatrizDispersaComp *b)
{
//~ #ifdef DEPURAR
   //~ if (a->Columnas() != b->Renglones())
   //~ {
   //~ printf("\nError en dimensión de las matrices para su multiplicarción\n");
   //~ Visualiza_Informacion();
   //~ a->Visualiza_Informacion();
   //~ b->Visualiza_Informacion();
   //~ exit(1);
   //~ }
//~ #endif

   //~ int i, j, k, ind, xcol;
   //~ ldouble v;

   //~ for (i = 0; i < a->Renglones(); i++)
   //~ {
   //~ for (j = 0; j < b->Columnas(); j++)
   //~ {
   //~ v = 0;
   //~ xcol = a->RetornaNumeroColumnasBanda(i);
   //~ for (ind = 0; ind < xcol; ind++)
   //~ {
   //~ k = a->RetornaNumeroColumna(i,ind);
   //~ v += a->Retorna(i,k) * b->Retorna(k,j);
   //~ }
   //~ Asigna(i,j,v);
   //~ }
   //~ }
}


// Multiplica la matriz por el vector B dejando el Resultado en R
// @param b Puntero a un Vector
// @param r Puntero a un Vector
void MatrizDispersaComp::multiplica(Vector *b, Vector *r)
{
#ifdef DEPURAR
   if (columnas() != b->columnas() || renglones() != r->columnas())
   {
      printf("\nMultiplica Mb=r Error en dimensión\n");
      visualizaInformacion();
      b->visualizaInformacion();
      r->visualizaInformacion();
      exit(1);
   }
#endif


   int i, k;
   ldouble v;

   for (i = 0; i < renglones(); i++)
   {
      if (M[i] == NULL) continue;
      v = 0.0;
      k = 0;
      while (J[i][k] != -1)// && k < Ban)
      {
         v += M[i][k] *  b->retorna(J[i][k]);
         k++;
         if (k >= Ban) break;
      }
      r->asigna(i,v);
   }
}



/// Visualiza las matrices internas usadas para soportar a las matrices bandadas
void MatrizDispersaComp::visualizaMatricesInternas(void)
{
   int i, j;
   Ctrl_visualizacion cv;

   visualizaInformacion();

   printf("\n\nMatriz de Datos\n");
   for (i = 0; i <= C_NumRen; i++)
   {
      if (!M[i]) continue;
      for (j = 0; j < tamanoBanda(); j++)
      {
         cv.visualiza_e(M[C_IndDat[i]][j]);
      }
      printf("\n");
   }

   printf("\n\nMatriz de indices\n");
   for (i = 0; i < renglones(); i++)
   {
      if (!M[i]) continue;
      for (j = 0; j < tamanoBanda(); j++)
      {
         cv.visualiza(J[i][j]);
      }
      printf("\n");
   }

   printf("\n\nArreglos de referencias\n");
   for (j = 0; j < Ren; j++)
   {
      printf("[%d]",j);
      cv.visualiza(C_IndDat[j]);
      printf("\n");
   }

   printf("\n\nMatriz compactada de %d a %d",Ren,C_NumRen+1);
}



// Compacta el renglon de la matriz liberando el espacio no usado (usar cuando ya no se desee modificar la matriz)
// @param ren Renglon a compactar
void MatrizDispersaComp::compactaMatriz(int ren)
{

   if (ren < 0) return;
   if (M[ren] == NULL) return;


   int j, k, sw = 0;

   // Busca si ese renglon ya existe
   for (k = C_NumRen-1; k >= 0 ; k --)
   {
      sw = 1;
      for (j=0; j < Ban; j++)
      {
#ifdef __Double__
         if (fabs(M[C_IndDat[k]][j] - M[ren][j]) > EPS) sw = 0;
#else
         if (fabsl(M[C_IndDat[k]][j] - M[ren][j]) > EPS) sw = 0;
#endif
         if (!sw) break;
      }
      if (sw) break;
   }
   // Compactación
   if (sw)
   {
      // Renglones repetidos
      delete []M[ren];
      M[ren] = M[C_IndDat[k]];
   }
   else
   {
      // Renglones distintos
      C_IndDat[C_NumRen] = ren;
      C_NumRen++;
   }
}


