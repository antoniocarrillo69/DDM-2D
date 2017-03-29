//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal mediante CGM                                       //
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



#ifndef __BCGM__
#define __BCGM__

#include "ResuelveSistemaLineal.hpp"
#include "MultOp.hpp"
#include "ProductoPunto.hpp"


/// Clase para resolución del sistema lineal mediante CGM
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class BCGM: public ResuelveSistemaLineal
{


protected:

   // Operador
   MultOp *A;

   /// Producto Punto
   ProductoPunto *prodP;

   /// Número máximo de iteraciones
   int Iter;

   /// Tolerancia
   ldouble Ep;


public:

   /// Constructor de la clase
   /** @param a Puntero a la implementación a la multiplicación de la matriz por el vector
       @param prod Puntero a la implementación del producto punto de dos vectores
       @param iter Máximo número de interaciones
       @param ep Tolerancia mínima */
   BCGM(MultOp &a, ProductoPunto &prod, int iter, ldouble ep) : ResuelveSistemaLineal()
   {
      A = &a;
      prodP = &prod;
      Iter = iter;
      Ep = ep;
   }

   /// Resuelve el sistema lineal
   void resuelve(void);


   /// Resuelve el sistema lineal
   /** @param x Puntero a un vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal */
   void resuelve(Vector *x, Vector *b)
   {
      X = x;
      B = b;
      resuelve();
   }

   /// Establece la tolerancia del metodo
   /** @param eps Tolerancia del metodo */
   void tolerancia(ldouble eps)
   {   
	Ep = eps;
   }

   /// Establece el maximo numero de iteraciones
   /** @param iter Iteraciones del metodo */
   void iteraciones(int iter)
   {   
	Iter = iter;
   }
      
   
};

/**
Esta clase implementa los componentes para la resolución del sistema lineal mediante CGM
@example EjemploResuelveSistemaLineal.cpp */

#endif
