//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con vectores de punto flotante                                    //
//                                                                                          //
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


#include <stdlib.h>
#include <string.h>
#include "VectorExtendido.hpp"
#include "Ctrl_vis.hpp"




// Solicita la memoria necesaria para contener los valores del vector extendido
void VectorExtendido::solicitaMemoria(void)
{
   V2 = new Vector(TE,"Vector Extendido");
   if (!V2)
   {
      visualizaInformacion();
      exit(1);
   }

   Ind = new int [Col];
   if (!Ind)
   {
      visualizaInformacion();
      exit(1);
   }

   for (int i = 0; i < Col; i++) Ind[i] = -1;
}




// Inicializa la columna del vector extendido con el valor
// @param col Columna
// @param val Valor
void VectorExtendido::inicializa(const int col, const ldouble val)
{
#ifdef DEPURAR
   if (col < 0 || col >= Col)
   {
      visualizaInformacion();
      printf("Error en inicializa, indice desbordado (%d)\n",col);
      exit(1);
   }
#endif

   Ind[col] = TO + Num;
   V2->asigna(Num,val);
   Num++;
}

// Inicializa la columna del vector extendido con el indice del vector original
// @param col Columna
// @param ind Indice del vector original
void VectorExtendido::inicializa(const int col, const int ind)
{
#ifdef DEPURAR
   if (col < 0 || col >= Col)
   {
      visualizaInformacion();
      printf("Error en inicializa, indice desbordado (%d)\n",col);
      exit(1);
   }
   if (ind < 0 || ind >= TO)
   {
      visualizaInformacion();
      printf("Error indice desbordado vector original(%d)\n",col);
      exit(1);
   }

#endif
   Ind[col] = ind;
}




// Asigna el valor val a la columna col
// @param col Columna
// @param val Valor
void VectorExtendido::asigna(const int col, ldouble val)
{
#ifdef DEPURAR
   if (col < 0 || col >= Col)
   {
      visualizaInformacion();
      printf("Error al asignar, indice desbordado (%d)\n", col);
      exit(1);
   }

   if (Ind[col] == -1)
   {
      visualizaInformacion();
      printf("Error al asignar, indice no asignado (%d)\n", col);
      exit(1);
   }
#endif
   if (Ind[col]-TO >= 0) V2->asigna(Ind[col]-TO,val);
   else V1->asigna(Ind[col],val);
}


// Retorna el valor de la columna col
// @param col Columna
// @return Valor
ldouble VectorExtendido::retorna(const int col)
{
#ifdef DEPURAR
   if (col < 0 || col >= Col)
   {
      visualizaInformacion();
      printf("Error al retornar, indice desbordado (%d)\n", col);
      exit(1);
   }

   if (Ind[col] == -1)
   {
      visualizaInformacion();
      printf("Error al retornar, indice no asignado (%d)\n", col);
      exit(1);
   }
#endif

   if (Ind[col] >= TO) return V2->retorna(Ind[col]-TO);
   if (V1) return V1->retorna(Ind[col]);
   return 0.0;
}



// Visualiza el vector
// @param tp (1) Se visualiza el vector de en formato de notación científica, (0) formato notación de punto flotante
// @param nl (1) Visualiza el vector en forma renglones, (0) en forma de columnas
// @param num (1) Numera las componentes del vector, (0) no lo hace
void VectorExtendido::visualiza(const int tp, int nl, int num)
{
   int i;
   Ctrl_visualizacion cv;

   visualizaInformacion();
   if (tp)
   {
      for (i = 0; i < Col; i++)
      {
         // Visualiza el numero de elemento
         if (num) printf("%d: ",i);
         // Visualiza el elemenento
         cv.visualiza_e(retorna(i));
         // Cambia de linea
         if (nl) printf("\n");
      }
   }
   else
   {
      for (i = 0; i < Col; i++)
      {
         // Visualiza el numero de elemento
         if (num) printf("%d: ",i);
         // Visualiza el elemenento
         cv.visualiza_n(retorna(i));
         // Cambia de linea
         if (nl) printf("\n");
      }
   }
   printf("\n");
}



// Copia el contenido del vector al vector a
// @param a Puntero a un vector
void VectorExtendido::copia(Vector *a)
{
#ifdef DEPURAR
   if (columnas() != a->columnas())
   {
      printf("Error en dimensión de los vectores al copiar\n");
      visualizaInformacion();
      a->visualizaInformacion();
      exit(1);
   }
#endif
   int i;
   for (i = 0; i < Col; i++) a->asigna(i,retorna(i));
}

