//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para definir un problema en dos dimensiones                                        //
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



#ifndef __Problema_2DEjemp01__
#define __Problema_2DEjemp01__

#include "Problema_2D.hpp"


/// Clase para definir un problema en dos dimensiones
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Problema_2DEjemp01 : public Problema_2D
{


public:

   /// Constructor de la clase
   Problema_2DEjemp01(void) : Problema_2D()
   {
      // Dominio
      Dominio.asigna(0,0,0.0);
      Dominio.asigna(0,1,0.0);
      Dominio.asigna(1,0,1.0);
      Dominio.asigna(1,1,1.0);

      // Tipo de frontera
      TipoFrontera.asigna(0,DIRICHLET);
      Alcance_frontera.asigna(0,FRONTERA_CON_NODOS);

      TipoFrontera.asigna(1,DIRICHLET);
      Alcance_frontera.asigna(1,FRONTERA_CON_NODOS);

      TipoFrontera.asigna(2,DIRICHLET);
      Alcance_frontera.asigna(2,FRONTERA_CON_NODOS);

      TipoFrontera.asigna(3,DIRICHLET);
      Alcance_frontera.asigna(3,FRONTERA_CON_NODOS);

      Coeficientes_constantes = true;
      Solucion_analitica = SOLUCION_ANALITICA_NO_DISPONIBLE;
   }


   /// Discretizacion de la ecuacion
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @param di Banda solicitada
       @return Valor de la función */
   ldouble f(ldouble *x, int di)
   {
      switch(di)
      {
      case 0:
         return ( (ln.dn1_X(x[0],x[1])*ln.dn1_X(x[0],x[1])) +  (ln.dn1_Y(x[0],x[1])*ln.dn1_Y(x[0],x[1])) + (ln.l_n1(x[0],x[1])*ln.l_n1(x[0],x[1])) );
      case 1:
         return ( (ln.dn2_X(x[0],x[1])*ln.dn1_X(x[0],x[1])) +  (ln.dn2_Y(x[0],x[1])*ln.dn1_Y(x[0],x[1])) + (ln.l_n2(x[0],x[1])*ln.l_n1(x[0],x[1])) );
      case 2:
         return ( (ln.dn3_X(x[0],x[1])*ln.dn1_X(x[0],x[1])) +  (ln.dn3_Y(x[0],x[1])*ln.dn1_Y(x[0],x[1])) + (ln.l_n3(x[0],x[1])*ln.l_n1(x[0],x[1])) );
      case 3:
         return ( (ln.dn4_X(x[0],x[1])*ln.dn1_X(x[0],x[1])) +  (ln.dn4_Y(x[0],x[1])*ln.dn1_Y(x[0],x[1])) + (ln.l_n4(x[0],x[1])*ln.l_n1(x[0],x[1])) );
      case 4:
         return ( (ln.dn1_X(x[0],x[1])*ln.dn2_X(x[0],x[1])) +  (ln.dn1_Y(x[0],x[1])*ln.dn2_Y(x[0],x[1])) + (ln.l_n1(x[0],x[1])*ln.l_n2(x[0],x[1])) );
      case 5:
         return ( (ln.dn2_X(x[0],x[1])*ln.dn2_X(x[0],x[1])) +  (ln.dn2_Y(x[0],x[1])*ln.dn2_Y(x[0],x[1])) + (ln.l_n2(x[0],x[1])*ln.l_n2(x[0],x[1])) );
      case 6:
         return ( (ln.dn3_X(x[0],x[1])*ln.dn2_X(x[0],x[1])) +  (ln.dn3_Y(x[0],x[1])*ln.dn2_Y(x[0],x[1])) + (ln.l_n3(x[0],x[1])*ln.l_n2(x[0],x[1])) );
      case 7:
         return ( (ln.dn4_X(x[0],x[1])*ln.dn2_X(x[0],x[1])) +  (ln.dn4_Y(x[0],x[1])*ln.dn2_Y(x[0],x[1])) + (ln.l_n4(x[0],x[1])*ln.l_n2(x[0],x[1])) );
      case 8:
         return ( (ln.dn1_X(x[0],x[1])*ln.dn3_X(x[0],x[1])) +  (ln.dn1_Y(x[0],x[1])*ln.dn3_Y(x[0],x[1])) + (ln.l_n1(x[0],x[1])*ln.l_n3(x[0],x[1])) );
      case 9:
         return ( (ln.dn2_X(x[0],x[1])*ln.dn3_X(x[0],x[1])) +  (ln.dn2_Y(x[0],x[1])*ln.dn3_Y(x[0],x[1])) + (ln.l_n2(x[0],x[1])*ln.l_n3(x[0],x[1])) );
      case 10:
         return ( (ln.dn3_X(x[0],x[1])*ln.dn3_X(x[0],x[1])) +  (ln.dn3_Y(x[0],x[1])*ln.dn3_Y(x[0],x[1])) + (ln.l_n3(x[0],x[1])*ln.l_n3(x[0],x[1])) );
      case 11:
         return ( (ln.dn4_X(x[0],x[1])*ln.dn3_X(x[0],x[1])) +  (ln.dn4_Y(x[0],x[1])*ln.dn3_Y(x[0],x[1])) + (ln.l_n4(x[0],x[1])*ln.l_n3(x[0],x[1])) );
      case 12:
         return ( (ln.dn1_X(x[0],x[1])*ln.dn4_X(x[0],x[1])) +  (ln.dn1_Y(x[0],x[1])*ln.dn4_Y(x[0],x[1])) + (ln.l_n1(x[0],x[1])*ln.l_n4(x[0],x[1])) );
      case 13:
         return ( (ln.dn2_X(x[0],x[1])*ln.dn4_X(x[0],x[1])) +  (ln.dn2_Y(x[0],x[1])*ln.dn4_Y(x[0],x[1])) + (ln.l_n2(x[0],x[1])*ln.l_n4(x[0],x[1])) );
      case 14:
         return ( (ln.dn3_X(x[0],x[1])*ln.dn4_X(x[0],x[1])) +  (ln.dn3_Y(x[0],x[1])*ln.dn4_Y(x[0],x[1])) + (ln.l_n3(x[0],x[1])*ln.l_n4(x[0],x[1])) );
      case 15:
         return ( (ln.dn4_X(x[0],x[1])*ln.dn4_X(x[0],x[1])) +  (ln.dn4_Y(x[0],x[1])*ln.dn4_Y(x[0],x[1])) + (ln.l_n4(x[0],x[1])*ln.l_n4(x[0],x[1])) );
      }
      printf("\nError en indice de f\n");
      exit(1);
      return 0.0;
   }


   /// Retorna la solucion exacta
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @return Valor de la solución */
   ldouble solucionExacta(ldouble *x)
   {
      return (0.0);
   }

   /// Lado derecho de la ecuacion
   /** @param x Puntero al arreglo de coordenadas
       @return Evaluación del lado derecho */
   ldouble ladoDerecho(ldouble *x)
   {
      return(exp(x[0]*x[1]));
   }


   /// Valor en la frontera
   /** @param x Puntero al arreglo de coordenadas
       @param fr Número de frontera
       @return Valor en la frontera */
   ldouble condicionesFrontera(ldouble *x, int fr)
   {
      if (fr == 0) return 0.0;
      if (fr == 1) return 0.0;
      if (fr == 2) return 0.0;
      if (fr == 3) return 0.0;
      printf("\nError al solicitar valores de la frontera");
      return 0.0;
   }


   /// Visualiza la definicion del problema
   void visualizaProblema(void)
   {
      printf("\n  Resuelve -(Uxx + Uyy)+ U = exp(xy)");
      printf("\n  en  0 < x < 1 y 0 < y < 1");
      printf("\n  u(x,0) = 0   u(x,1) = 0");
      printf("\n  u(0,y) = 0   u(1,y) = 0");
      printf("\n  Solucion: ");
      printf("\n\n");
   }


};

/**
Esta clase implementa los comportamientos para definir un problema en dos dimensiones
@example Ejemplo.cpp */

#endif
