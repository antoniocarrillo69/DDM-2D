//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para trabajar con matrices bandadas y dispersas                               //
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



#ifndef __MatrizBandDisp__
#define __MatrizBandDisp__


#include "Matriz.hpp"


/// Clase base para trabajar con matrices bandadas y dispersas
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class MatrizBandDisp : public Matriz
{
private:

   /// Solicita la memoria necesaria para contener los valores de la matriz
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param ban Tamaño de la banda  */
   virtual void solicitaMemoria(const int ren, const int col, const int ban) = 0;


public:

   /// Constructor de la clase
   MatrizBandDisp(void) : Matriz()
   {
   }


   /// Retorna el tamaño de la banda
   /** @return Tamaño de la banda */
   inline int tamanoBanda(void)
   {
      return Ban;
   }


   /// Multiplica la matriz por el escalar pasado como parametro
   /** @param esc Escalar */
   virtual void multiplica(ldouble esc) = 0;


   /// Multiplica la matriz por el vector B dejando el Resultado en R
   /** @param b Puntero a un Vector
       @param r Puntero a un Vector */
   virtual void multiplica(Vector *b, Vector *r) = 0;


   /// Visualiza las matrices internas usadas para soportar a las matrices bandadas
   virtual void visualizaMatricesInternas(void) = 0;

};


/**
Esta clase implementa los componentes para el trabajar con matrices dispersas de punto flotante
@example EjemploMatrizDispersa.cpp */

#endif
