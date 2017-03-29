//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para integrar una funcion mediante la cuadratura Gauss-Legendre usando de          //
// 2 a 10 puntos                                                                            //
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



#ifndef __GaussQuad__
#define __GaussQuad__

#include "Definiciones.hpp"


/// Clase para integrar una funcion mediante la cuadratura Gauss-Legendre usando de 2 a 10 puntos
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
    @todo Hacer algoritmo para soportar n puntos Gaussianos
*/
class GaussQuad
{
private:
   /// Punto inicial de integracion
   ldouble a;
   /// Punto inicial de integracion
   ldouble b;
   /// Numero de puntos de integracion
   int np;

   /// Puntos en los cuales debera de evalurse la función
   /** @param x Puntero a un arreglo de puntos */
   void puntosCalcular(ldouble *x);

   /// Pesos usados para evualuar la integral
   /** @param w Puntero a un arreglo de pesos */
   void pesosCalcular(ldouble *w);


public:
   /// Constructor de la clase
   /** @param a Extremo inicial del intervalo
       @param b Extremo final del intervalo
       @param n Número de puntos a usar
       @param x Puntero a un arreglo de puntos */
   GaussQuad(ldouble a, ldouble b, int n, ldouble *x);

   /// Constructor de la clase
   /** @param a Extremo inicial del intervalo
       @param b Extremo final del intervalo
       @param n Número de puntos a usar
       @param x Puntero a un arreglo de puntos
       @param w Puntero a un arreglo de pesos */
   GaussQuad(ldouble a, ldouble b, int n, ldouble *x, ldouble *w);

   /// Integra mediante el método Gauss-Legendre
   /** @param f Arreglo de valores de una la evaluacion de una funcion */
   ldouble integra(ldouble f[]);
};

/**
Esta clase implementa los componentes para integrar una funcion mediante la cuadratura Gauss-Legendre usando de 2 a 10 puntos
@example EjemploGaussQuad.cpp */

#endif
