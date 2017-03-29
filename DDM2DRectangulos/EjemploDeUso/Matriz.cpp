//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices de punto flotante                                    //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.geofisica.unam.mx                                                  //
// Página:   http://www.mmc.geofisica.unam.mx/acl                                           //
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

#include <stdio.h>
#include <math.h>
#include "Matriz.hpp"
#include "Ctrl_vis.hpp"



// Inicializa la matriz como una matriz diagonal con el valor indicado
// @param val Valor
void Matriz::inicializaDiagonal(const ldouble val)
{
   int i, r = Ren >= Col ? Col: Ren;

   for (i = 0; i < r; i++)
   {
      asigna(i,i,val);
   }
}


// Visualiza la matriz
// @param tp (1) Se visualiza el vector de en formato de notación científica, (0) formato notación de punto flotante
void Matriz::visualiza(const int tp)
{
   visualizaInformacion();

   int i, j;
   Ctrl_visualizacion cv;

   if (tp)
   {
      for (i = 0; i < Ren; i++)
      {
         for (j = 0; j < Col; j++)
         {
            cv.visualiza_e(retorna(i,j));
         }
         printf("\n");
      }
   }
   else
   {
      for (i = 0; i < Ren; i++)
      {
         for (j = 0; j < Col; j++)
         {
            cv.visualiza_n(retorna(i,j));
         }
         printf("\n");
      }
   }
   printf("\n");
}


// Convierte el arreglo unidimensional en parte de la matriz en el renglon Ren y de tamaño Tam
// @param a puntero al arreglo
// @param ren Renglon en el cual se insertara el contenido del arreglo
// @param tam Tamaño del arreglo
void Matriz::convierte(ldouble *a, int ren, int tam)
{
#ifdef DEPURAR
   if (ren < 0 || ren > Ren)
   {
      printf("\nError al convertir, el renglon esta fuera del rango\n");
      visualizaInformacion();
      exit(1);
   }
#endif
   int i, r = tam >= Col ? Col: tam;

   for (i = 0; i < r; i++)
   {
      if (a[i] != 0.0) asigna(ren,i,a[i]);
   }
}


// Convierte un arreglo bidimensional de numero de renglones REN y columnas Col 
// @param a puntero al arreglo
// @param ren Renglones
// @param tam Columnas 
void Matriz::convierte(ldouble **a, int ren, int col)
{
#ifdef DEPURAR
   if ((ren < 0 || ren > Ren) && (col < 0 || col > Col))
   {
      printf("\nError al convertir, el arreglo esta fuera de rango\n");
      visualizaInformacion();
      exit(1);
   }
#endif
   int i, j;

   for (i = 0; i < ren; i++)
   {
      for (i = 0; i < ren; i++)
      {
         if (a[i][j] != 0.0) asigna(i,j,a[i][j]);
      }
   }
}

// Convierte el contenido del vector en parte de la matriz en el renglon Ren
// @param ren Renglon en el cual se insertara el contenido del arreglo
// @param a puntero al vector
void Matriz::convierte(int ren, Vector *a)
{
#ifdef DEPURAR
   if (ren < 0 || ren > Ren)
   {
      printf("\nError al convertir, el renglon esta fuera del rango\n");
      visualizaInformacion();
      exit(1);
   }
#endif
   int i;
   for (i = 0; i < Col; i++) asigna(ren,i,a->retorna(i));
}


// Convierte el contenido del arreglo unidimensional que contiene una matriz de Ren x Col a matriz
// @param ren Número de renglones
// @param col Número de columnas
// @param a puntero al arreglo
void Matriz::convierte(int ren, int col, ldouble *a)
{
#ifdef DEPURAR
   if (ren != Ren || col != Col)
   {
      printf("\nError al convertir, las dimensiones no coinciden\n");
      visualizaInformacion();
      exit(1);
   }
#endif
   int i, j;
   ldouble val;
   for (i = 0; i < Ren; i++)
   {
      for ( j = 0; j < Col; j++)
      {
         val = a[i*Col+j];
         if (val != 0.0) asigna(i,j,val);
      }
   }
}


// Retorna todo el contenido de la matriz como un vector
// @param a puntero al vector
void Matriz::retornaVector(Vector *a)
{
#ifdef DEPURAR
   if (a->columnas() != (Ren*Col))
   {
      printf("\nError al retornar la matriz como un vector, las dimensiones no coinciden\n");
      visualizaInformacion();
      exit(1);
   }
#endif
   int i, j;
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++)
      {
         a->asigna(i*Col+j,retorna(i,j));
      }
   }
}


// Suma las matrices A y B
// @param a Puntero a una Matriz
// @param b Puntero a una Matriz
void Matriz::suma(Matriz *a, Matriz *b)
{
#ifdef DEPURAR
   if (a->columnas() != b->columnas() || a->renglones() != b->renglones() )
   {
      printf("Error en dimensión de las matrices para su Suma\n");
      visualizaInformacion();
      a->visualizaInformacion();
      b->visualizaInformacion();
      exit(1);
   }
#endif

   int i, j;
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++) asigna(i,j,a->retorna(i,j) + b->retorna(i,j));
   }
}


// Suma a la matriz el contenido de la matriz pasada como parámetro
// @param a Puntero a una Matriz
void Matriz::suma(Matriz *a)
{
#ifdef DEPURAR
   if (columnas() != a->columnas() || renglones() != a->renglones() )
   {
      printf("Error en dimensión de las matrices para su Suma\n");
      visualizaInformacion();
      a->visualizaInformacion();
      exit(1);
   }
#endif

   int i, j;
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++) asigna(i,j,retorna(i,j) + a->retorna(i,j));
   }
}


// Resta a la matriz A la matriz B
// @param a Puntero a una Matriz
// @param b Puntero a una Matriz
void Matriz::resta(Matriz *a, Matriz *b)
{
#ifdef DEPURAR
   if (a->columnas() != b->columnas() || a->renglones() != b->renglones() )
   {
      printf("Error en dimensión de las matrices para su Resta\n");
      visualizaInformacion();
      a->visualizaInformacion();
      b->visualizaInformacion();
      exit(1);
   }
#endif

   int i, j;
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++) asigna(i,j, a->retorna(i,j) - b->retorna(i,j));
   }
}


// Resta a la matriz el contenido de la matriz padada como parámetro
// @param a Puntero a una Matriz
void Matriz::resta(Matriz *a)
{
#ifdef DEPURAR
   if (columnas() != a->columnas() || renglones() != a->renglones() )
   {
      printf("Error en dimensión de las matrices para su Resta\n");
      visualizaInformacion();
      a->visualizaInformacion();
      exit(1);
   }
#endif

   int i, j;
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++) asigna(i,j,retorna(i,j) - a->retorna(i,j));
   }
}


// Transpone la matriz pasada como parámetro
// @param a Puntero a la matriz
void Matriz::transpuesta(Matriz *a)
{
   int i, j;
   ldouble val;

   // Transpone Matriz
   for (i = 0; i < a->renglones(); i++)
   {
      for (j = 0; j < a->columnas(); j++)
      {
         val = a->retorna(i,j);
         if (val != 0.0) asigna(j,i,val);
      }
   }
}


// Regresa verdadero si las matrices son iguales, cero en caso contrario
// @param a Puntero a la matriz
// @param esp Tolerancia usada en la comparación
// @return (1) si son iguales, (0) en caso contrario
int Matriz::iguales(Matriz *a, ldouble eps)
{
   int i, j;

   // Transpone Matriz cuadrada
   for (i = 0; i < a->renglones(); i++)
   {
      for (j = 0; j < a->columnas(); j++)
      {
#ifdef __Double__
         if (fabs(a->retorna(i,j) - retorna(i,j)) > eps) return 0;
#else
         if (fabsl(a->retorna(i,j) - retorna(i,j)) > eps) return 0;
#endif
      }
   }
   return 1;
}


// Retorna el máximo tamaño en todas las columnas que sean distintos de cero
// @return Máximo tamaño de columnas ocupadas en la matriz
int Matriz::maximoTamanoColumnaOcupado(void)
{
   int i, j, k, max = 0;
   for (i = 0; i < renglones(); i++)
   {
      k = 0;
      for (j = 0; j < columnas(); j++)
      {
         if (retorna(i,j) != 0.0) k ++;
      }
      if (k > max) max = k;
   }
   return max;
}


// Retorna el número de entradas distintas de cero en la matriz
// @return Número de entradas distintas de cero en la matriz
int Matriz::entradasDistintasCero(void)
{
   int i, j, max = 0;
   for (i = 0; i < renglones(); i++)
   {
      for (j = 0; j < columnas(); j++)
      {
         if (retorna(i,j) != 0.0) max ++;
      }
   }
   return max;
}


// Copia el contenido de la matriz a la matriz pasada como parámetro
// @param a Puntero a una Matriz
void Matriz::copia(Matriz *a)
{
   int i, j;
   ldouble m;
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++) 
	   {
		   m = retorna(i,j);
		   if (m) a->asigna(i,j,m);
	   }
   }
}

