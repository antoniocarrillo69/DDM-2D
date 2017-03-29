//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para visualizar números de distinto tipo                                           //
// Revisión: 6 de Junio del 2006                                                            //
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

#ifndef __Ctrl_vis__
#define __Ctrl_vis__

#include <stdio.h>


/// Clase para visualizar números sobrecargando la funcion
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Ctrl_visualizacion
{

public:
   /// Visualiza un número char
   void visualiza(char v)
   {
      printf(" %+d ",(int)v);
   }

   /// Visualiza un número int
   void visualiza(int v)
   {
      printf(" %+d ",v);
   }

   /// Visualiza un número double con formato %+1.10le
   void visualiza_e(double v)
   {
      printf(" %+1.10le ",v);
   }

   /// Visualiza un número double con formato %+1.10le y cambia de linea
   void visualiza_en(double v)
   {
      printf(" %+1.10le\n",v);
   }

   /// Visualiza un número double con formato %+1.10lf
   void visualiza_n(double v)
   {
      printf(" %+1.10lf ",v);
   }

   /// Visualiza un número double con formato %+1.10lf y cambia de linea
   void visualiza_nn(double v)
   {
      printf(" %+1.10lf\n",v);
   }

   /// Visualiza un número long double con formato %+1.10Le
   void visualiza_e(long double v)
   {
      printf(" %+1.10Le ",v);
   }

   /// Visualiza un número long double con formato %+1.10Le y cambia de linea
   void visualiza_en(long double v)
   {
      printf(" %+1.10Le\n",v);
   }

   /// Visualiza un número long double con formato %+1.10Lf
   void visualiza_n(long double v)
   {
      printf(" %+1.10Lf ",v);
   }

   /// Visualiza un número long double con formato %+1.10Lf y cambia de linea
   void visualiza_nn(long double v)
   {
      printf(" %+1.10Lf\n",v);
   }

};


#endif
