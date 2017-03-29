//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal usando factorizacion LU                            //
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



#ifndef __ResuelveFactorizacionLU__
#define __ResuelveFactorizacionLU__

#include "ResuelveSistemaLineal.hpp"
#include "MatrizBandDisp.hpp"



/// Clase para resolución del sistema lineal usando factorizacion LU
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class ResuelveFactorizacionLU: public ResuelveSistemaLineal
{
protected:

   /// Matriz factorizada
   bool MatrizFactorizada;


public:

   /// Constructor de la clase
   ResuelveFactorizacionLU(void) : ResuelveSistemaLineal()
   {
      X = NULL;
      B = NULL;
      MetodoModificaMatriz = true;
      MetodoNumerico = FACT_LU;
      MatrizFactorizada = false;
   }

   /// Constructor de la clase
   /** @param x Puntero a un Vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal */
   ResuelveFactorizacionLU(Vector *x, Vector *b) : ResuelveSistemaLineal()
   {
      X = x;
      B = b;
      MetodoModificaMatriz = true;
      MetodoNumerico = FACT_LU;
      MatrizFactorizada = false;
   }

   /// Factoriza la matriz A en L y U dejandolas en la misma matriz
   virtual void factoriza(void) = 0;

};

#endif
