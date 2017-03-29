//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para generar una geometría en dos dimensiones usando rectángulos                   //
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




#include "Geometria_2DRectangulos.hpp"


// Genera la geometria
void Geometria_2DRectangulos::generaGeometria(void)
{
   EL = new MatrizInt(N_E,NNE,"Nodos que conforman a los elementos",-1);
   if (!EL) errorSolicitudMemoria("Elementos Geometria Rectangulos");
   int col[]= {Particion.retorna(0)+1,Particion.retorna(1)+1};
   ND = new MatrizTamanoVariable(DIM,col,"Coordenadas de Nodos");
   if (!ND) errorSolicitudMemoria("Coordenadas Geometria Rectangulos");
   NN = new VectorInt(N_N,"Numeracion de nodos");
   if (!NN) errorSolicitudMemoria("Nodos Geometria Rectangulos");
   TN = new VectorInt(N_N,"Tipo de nodos");
   if (!TN) errorSolicitudMemoria("Tipo de Nodo Geometria Rectangulos");

   int i, j, n, e;
   // Calcula los tamaños de las particiones horizontales como verticales
   ldouble Ic_H = (Dominio.retorna(1,0) - Dominio.retorna(0,0)) / (double) Particion.retorna(0);
   ldouble Ic_V = (Dominio.retorna(1,1) - Dominio.retorna(0,1)) / (double) Particion.retorna(1);

   for (i = 0; i < Particion.retorna(1); i++)
   {
      ND->asigna(1,i,Dominio.retorna(0,1) + Ic_V * i);
      for (j = 0; j < Particion.retorna(0); j++)
      {
         ND->asigna(0,j,Dominio.retorna(0,0) + Ic_H * j);
         e = (i * Particion.retorna(0)) + j;

         // Rectangulo
         n = (i * (Particion.retorna(0)+1)) + j;
         EL->asigna(e,0,n);

         n =(i * (Particion.retorna(0)+1)) + j + 1;
         EL->asigna(e,1,n);

         n =  ((i + 1) * (Particion.retorna(0)+1)) + j + 1;
         EL->asigna(e,2,n);

         n = ((i + 1) * (Particion.retorna(0)+1)) + j;
         EL->asigna(e,3,n);
      }
      ND->asigna(0,j,Dominio.retorna(0,0) + Ic_H * j);
   }
   ND->asigna(1,i,Dominio.retorna(0,1) + Ic_V * i);
}



