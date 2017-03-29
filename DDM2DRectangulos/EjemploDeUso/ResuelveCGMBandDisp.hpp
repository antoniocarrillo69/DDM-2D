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



#ifndef __ResuelveCGMBandada__
#define __ResuelveCGMBandada__


#include "ResuelveCGM.hpp"
#include "MatrizBandDisp.hpp"



/// Clase para resolución del sistema lineal mediante CGM
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
    @todo Definir clase de producto interior y poder pasarlo como argumento y user este
*/
class ResuelveCGMBandDisp: public ResuelveCGM
{

public:

   /// Constructor de la clase
   ResuelveCGMBandDisp(void) : ResuelveCGM()
   {
      M = NULL;
      C = NULL;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Constructor de la clase
   /** @param A Puntero a una matriz del tipo MatrizBandDisp */
   ResuelveCGMBandDisp(MatrizBandDisp *A) : ResuelveCGM()
   {
      M = A;
      C = NULL;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Constructor de la clase
   /** @param A Puntero a una matriz del tipo MatrizBandDisp
       @param x Puntero a un Vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal */
   ResuelveCGMBandDisp(MatrizBandDisp *A, Vector *x, Vector *b) : ResuelveCGM(x,b)
   {
      M = A;
      C = NULL;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Constructor de la clase
   /** @param A Puntero a una matriz del tipo MatrizBandDisp
       @param x Puntero a un Vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal
       @param ep Tolerancia del método
       @param it Número máximo de iteraciones */
   ResuelveCGMBandDisp(MatrizBandDisp *A, Vector *x, Vector *b, ldouble ep, int it) : ResuelveCGM(x,b,ep,it)
   {
      M = A;
      C = NULL;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

};

/**
Esta clase implementa los componentes para la resolución del sistema lineal mediante CGM
@example EjemploResuelveSistemaLineal.cpp */

#endif
