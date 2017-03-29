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
#include <string.h>
#include <stdlib.h>
#include "Matriz_Base.hpp"
#include "Ctrl_vis.hpp"


/// Tipos de matrices
static char TM[][50]= {"Matriz Bandada","Matriz Densa","Matriz Densa Entera","Matriz Dispersa","Matriz Bandada Compacta","Matriz Dispersa Compacta","Matriz Rala"};


// Asigna nombre a la matriz
// @param nmb Nombre de la matriz
void Matriz_Base::asignaNombre(const char *nmb)
{
   Nmb = new char[strlen(nmb)+2];
   if (!Nmb)
   {
      printf("\nError no hay memoria para el nombre de la matriz\n");
      exit(1);
   }
   strcpy(Nmb, nmb);
}



// Visualiza información general de la matriz
void Matriz_Base::visualizaInformacion(void)
{
   if (Tipo_Matriz == MATRIZ_BANDADA || Tipo_Matriz == MATRIZ_BANDADA_COMPACTA || Tipo_Matriz == MATRIZ_DISPERSA || Tipo_Matriz == MATRIZ_DISPERSA_COMPACTA) printf("\n%s \"%s\" de dimensión: %d x %d y banda %d",TM[Tipo_Matriz],Nmb,Ren,Col,Ban);
   else printf("\n%s \"%s\" de dimensión: %d x %d",TM[Tipo_Matriz],Nmb,Ren,Col);
   printf("\nNúmero de entradas distintas de cero: %d",entradasDistintasCero());
   printf("\nNumero máximo de columnas ocupadas: %d\n\n",maximoTamanoColumnaOcupado());
}


// Tamaño de la matriz (aproximado) en Kb
// @return Tamaño de la matriz en Kb
ldouble Matriz_Base::tamano(void)
{
   ldouble t;
   switch (Tipo_Matriz)
   {
   case 1:
      t = ((long) sizeof(ldouble) * Ren * Col) / 1024.0;
      break;
   case 2:
      t = ((long) sizeof(int) * Ren * Col) / 1024.0;
      break;
   default:
      t = (((long) sizeof(ldouble) * Ren * Ban) +  ((long) sizeof(int) * Ren * Ban)) / 1024.0;
   }
   return t;
}

// Visualiza el tamaño en memoria de la matriz en Kb
void Matriz_Base::visualizaTamano(void)
{
   Ctrl_visualizacion cv;
   printf("\nTamaño:");
   cv.visualiza_n(tamano());
   printf("Kb\n");
}




