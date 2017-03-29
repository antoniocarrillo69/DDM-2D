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


#ifndef __ResuelveCGM__
#define __ResuelveCGM__

#include "BCGM.hpp"


/// Clase para resolución del sistema lineal mediante CGM standard
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class ResuelveCGM: public BCGM, public  MultOp, public ProductoPunto
{

protected:

   /// Producto punto
   inline double productoPunto(Vector *u, Vector *v)
   {
      return u->productoPunto(v);
   }

   /// Multiplica Au=v
   inline void multiplica(Vector *u, Vector *v)
   {
      M->multiplica(u,v);
   }

   /// Tamaño
   inline int tamano(void)
   {
      return M->renglones();
   }


   /// Precondicionador
   Matriz *C;


public:

   /// Constructor de la clase
   ResuelveCGM(void) : BCGM(*(MultOp*) this, *(ProductoPunto*) this, 1000, 1e-5)
   {
      X = NULL;
      B = NULL;
      MetodoModificaMatriz = false;
      MetodoNumerico = CGM;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Constructor de la clase
   /** @param x Puntero a un Vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal */
   ResuelveCGM(Vector *x, Vector *b) : BCGM(*(MultOp*) this, *(ProductoPunto*) this, 1000, 1e-5)
   {
      X = x;
      B = b;
      MetodoModificaMatriz = false;
      MetodoNumerico = CGM;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Constructor de la clase
   /** @param x Puntero a un Vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal
       @param ep Tolerancia del método
       @param it Número máximo de iteraciones */
   ResuelveCGM(Vector *x, Vector *b, ldouble ep, int it) : BCGM(*(MultOp*) this, *(ProductoPunto*) this, 1000, 1e-5)
   {
      X = x;
      B = b;
      MetodoModificaMatriz = false;
      MetodoNumerico = CGM;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Configura al método numérico
   /** @param ep Tolerancia del método
       @param it Número máximo de iteraciones */
   inline void configuraMetodo(ldouble ep, int it)
   {
      Ep = ep;
      Iter = it;
   }
};

#endif



