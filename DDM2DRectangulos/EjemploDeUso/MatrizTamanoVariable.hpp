//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices de tamaño variable                                   //
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



#ifndef __MatrizTamanoVariable__
#define __MatrizTamanoVariable__


#include "Matriz_Base.hpp"


/// Clase para el trabajar con matrices de tamaño variable
/** @author Antonio Carrillo Ledesma
    @date primavera 2010
    @version 1.0.0
    @bug No hay errores conocidos
*/
class MatrizTamanoVariable : public Matriz_Base
{
private:

   /// Solicita la memoria necesaria para contener los valores de la matriz
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas en cada renglon de la matriz  */
   void solicitaMemoria(const int ren, const int *col);


   /// Puntero a la matriz de datos
   ldouble **M;
   /// Arreglo que contiene el tamaño de los renglones de la matriz
   int *TC;


public:

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas en cada renglon de la matriz */
   MatrizTamanoVariable(const int ren, const int *col)
   {
      solicitaMemoria(ren, col);
      asignaNombre("SinNombre");
   }

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas en cada renglon de la matriz
       @param nmb Nombre de la matriz */
   MatrizTamanoVariable(const int ren, const int *col, const char *nmb)
   {
      solicitaMemoria(ren, col);
      asignaNombre(nmb);
   }

   ~MatrizTamanoVariable()
   {
      liberaMemoria();
   }

   /// Libera la memoria solicitada para la matriz
   void liberaMemoria(void);

   /// Inicializa la matriz al valor indicado
   /** @param val Valor por omisión para inicializar la matriz */
   void inicializa(ldouble val);

#ifdef DEPURAR
   /// Asigna el valor indicado en el renglo y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @param val Valor */
   void asigna(const int ren, const int col, const ldouble val);

   /// Retorna valor almacenado en el renglon y la columna indicada
   /** @param ren Número de renglon
       @param col Número de columna
       @return Valor almacenado en el renglon y la columna indicada  */
   ldouble retorna(const int ren, const int col);
#else
   /// Asigna el valor indicado en el renglo y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @param val Valor */
   void asigna(const int ren, const int col, const ldouble val)
   {
      M[ren][col] = val;
   }

   /// Retorna valor almacenado en el renglon y la columna indicada
   /** @param ren Número de renglon
       @param col Número de columna
       @return Valor almacenado en el renglon y la columna indicada  */
   ldouble retorna(const int ren, const int col)
   {
      return (M[ren][col]);
   }
#endif

   /// Retorna el tamaño del número de columna para dicho renglon
   /** @param ren Número de renglon
       @return Número de columnas del renglon */
   inline int retornaNumeroColumna(int ren)
   {
      return ( TC[ren]);
   }

   /// Copia el contenido de la matriz a la matriz pasada como parámetro
   /** @param a Puntero a una Matriz */
   void copia(MatrizTamanoVariable *a);

   /// Visualiza las matrices internas usadas para soportar a las matrices de tamaño variable
   void visualizaMatricesInternas(void);

   /// Retorna el máximo tamaño en todas las columnas que sean distintos de cero
   /** @return Máximo tamaño de columnas ocupadas en la matriz */
   int maximoTamanoColumnaOcupado(void);

   /// Retorna el número de entradas distintas de cero en la matriz
   /** @return Número de entradas distintas de cero en la matriz */
   int entradasDistintasCero(void);

};


/**
Esta clase implementa los componentes para el trabajar con matrices de Tamaño variable
@example EjemploTamanoVariable.cpp */

#endif
