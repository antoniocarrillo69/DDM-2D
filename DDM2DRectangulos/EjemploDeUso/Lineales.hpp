//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para definir a los interpoladores lineales para el problema en dos dimensiones     //
// Revisión: 20 de Junio del 2006                                                           //
//                                                                                          //
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


#ifndef __LINEALES_HPP__
#define __LINEALES_HPP__

#define TAMANO_BANDA 9

#include <math.h>
#include <stdlib.h>
#include "Definiciones.hpp"

/// Clase para definir a los interpoladores lineales para el problema en dos dimensiones
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Lineales
{

private:

   /// Coordenadas del elemento en X
   ldouble T_X[4];
   /// Coordenadas del elemento en Y
   ldouble T_Y[4];
   /// Jacobiano de la transformacion
   ldouble J;


public:

   /// Asigna valores de los nodos
   inline void asignarValorNodo(ldouble x[], ldouble y[])
   {
      T_X[0] = x[0];
      T_X[1] = x[1];
      T_X[2] = x[2];
      T_X[3] = x[3];

      T_Y[0] = y[0];
      T_Y[1] = y[1];
      T_Y[2] = y[2];
      T_Y[3] = y[3];
   }

   /// Asigna valores de los nodos
   inline void asignarValorJacobiano(ldouble j)
   {
      J = j;
   }


   /// Interpoladores lineales
   inline ldouble l_n(int f, ldouble E, ldouble N)
   {
      switch (f)
      {
      case 0:
         return l_n1(E,N);
      case 1:
         return l_n2(E,N);
      case 2:
         return l_n3(E,N);
      case 3:
         return l_n4(E,N);
      }
      printf("\nFuncion lineal no existente %d\n",f);
      exit(1);
      return 0.0;
   }



   /// Interpolador lineal
   inline ldouble l_n1(ldouble E, ldouble N)
   {
      return ((1.0/4.0) * (1.0 - E) * (1.0 - N));
   }

   /// Interpolador lineal
   inline ldouble l_n2(ldouble E, ldouble N)
   {
      return ((1.0/4.0) * (1.0 + E) * (1.0 - N));
   }

   /// Interpolador lineal
   inline ldouble l_n3(ldouble E, ldouble N)
   {
      return ((1.0/4.0) * (1.0 + E) * (1.0 + N));
   }

   /// Interpolador lineal
   inline ldouble l_n4(ldouble E, ldouble N)
   {
      return ((1.0/4.0) * (1.0 - E) * (1.0 + N));
   }


   /// Derivada del interpolador lineal
   inline ldouble l_dn1_E(ldouble E, ldouble N)
   {
      return (-(1.0/4.0) * (1.0 - N));
   }

   /// Derivada del interpolador lineal
   inline ldouble l_dn1_N(ldouble E, ldouble N)
   {
      return (-(1.0/4.0) * (1.0 - E));
   }

   /// Derivada del interpolador lineal
   inline ldouble l_dn2_E(ldouble E, ldouble N)
   {
      return ((1.0/4.0) * (1.0 - N));
   }


   /// Derivada del interpolador lineal
   inline ldouble l_dn2_N(ldouble E, ldouble N)
   {
      return (-(1.0/4.0) * (1.0 + E));
   }



   /// Derivada del interpolador lineal
   inline ldouble l_dn3_E(ldouble E, ldouble N)
   {
      return ((1.0/4.0) * (1.0 + N));
   }


   /// Derivada del interpolador lineal
   inline ldouble l_dn3_N(ldouble E, ldouble N)
   {
      return ((1.0/4.0) * (1.0 + E));
   }


   /// Derivada del interpolador lineal
   inline ldouble l_dn4_E(ldouble E, ldouble N)
   {
      return (-(1.0/4.0) * (1.0 + N));
   }

   /// Derivada del interpolador lineal
   inline ldouble l_dn4_N(ldouble E, ldouble N)
   {
      return ((1.0/4.0) * (1.0 - E));
   }



   /// Derivada con respecto al cambio de coordenadas
   inline ldouble l_de_X(ldouble E, ldouble N)
   {
      return (((T_Y[3] - T_Y[0]) / 2.0) * (1.0 / J));
   }


   /// Derivada con respecto al cambio de coordenadas
   inline ldouble l_de_Y(ldouble E, ldouble N)
   {
      return 0.0;   //((T_X[3] - T_X[0]) / 2.0) * (1.0 / J);
   }


   /// Derivada con respecto al cambio de coordenadas
   inline ldouble l_dn_X(ldouble E, ldouble N)
   {
      return 0.0;   //((T_Y[1] - T_Y[0]) / 2.0) * (1.0 / J);
   }


   /// Derivada con respecto al cambio de coordenadas
   inline ldouble l_dn_Y(ldouble E, ldouble N)
   {
      return (((T_X[1] - T_X[0]) / 2.0) * (1.0 / J));
   }




   /// Derivada con respecto al cambio de coordenadas
   inline ldouble dn1_X(ldouble E, ldouble N)
   {
      return (l_dn1_E(E,N)*l_de_X(E,N) + l_dn1_N(E,N)*l_dn_X(E,N));
   }

   /// Derivada con respecto al cambio de coordenadas
   inline ldouble dn1_Y(ldouble E, ldouble N)
   {
      return (l_dn1_E(E,N)*l_de_Y(E,N) + l_dn1_N(E,N)*l_dn_Y(E,N));
   }

   /// Derivada con respecto al cambio de coordenadas
   inline ldouble dn2_X(ldouble E, ldouble N)
   {
      return (l_dn2_E(E,N)*l_de_X(E,N) + l_dn2_N(E,N)*l_dn_X(E,N));
   }

   /// Derivada con respecto al cambio de coordenadas
   inline ldouble dn2_Y(ldouble E, ldouble N)
   {
      return (l_dn2_E(E,N)*l_de_Y(E,N) + l_dn2_N(E,N)*l_dn_Y(E,N));
   }

   /// Derivada con respecto al cambio de coordenadas
   inline ldouble dn3_X(ldouble E, ldouble N)
   {
      return (l_dn3_E(E,N)*l_de_X(E,N) + l_dn3_N(E,N)*l_dn_X(E,N));
   }

   /// Derivada con respecto al cambio de coordenadas
   inline ldouble dn3_Y(ldouble E, ldouble N)
   {
      return (l_dn3_E(E,N)*l_de_Y(E,N) + l_dn3_N(E,N)*l_dn_Y(E,N));
   }

   /// Derivada con respecto al cambio de coordenadas
   inline ldouble dn4_X(ldouble E, ldouble N)
   {
      return (l_dn4_E(E,N)*l_de_X(E,N) + l_dn4_N(E,N)*l_dn_X(E,N));
   }

   /// Derivada con respecto al cambio de coordenadas
   inline ldouble dn4_Y(ldouble E, ldouble N)
   {
      return (l_dn4_E(E,N)*l_de_Y(E,N) + l_dn4_N(E,N)*l_dn_Y(E,N));
   }


};

#endif

