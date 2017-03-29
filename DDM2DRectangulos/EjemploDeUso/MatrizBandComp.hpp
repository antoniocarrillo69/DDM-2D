//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices bandadas de punto flotante                           //
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



#ifndef __MatrizBandComp__
#define __MatrizBandComp__



#include "MatrizBandDisp.hpp"


/// Clase para el trabajar con matrices bandadas de punto flotante basada en el algoritmo Compressed Diagonal Storage (CDS) que pueden ser compactada, pero soporta matrices con todos los valores distintos.
/// El algoritmo esta optimizado para hacer el producto matriz vector.
/// El algoritmo de compactación presupone que se llenara la matriz renglon por renglon de manara consecutiva, no asi las columnas dentro del renglon.
/// El algoritmo de compactación sólo guarda los renglones distintos de la matriz.
/// Si la matriz tiene ciertas propiedades es posible usar otros algoritmo de compactación (matrices tridiagonales con coeficientes constantes solo guardar los 3 valores distintos).
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
    @todo Multiplicación de matrices
*/
class MatrizBandComp : public MatrizBandDisp
{
private:

   /// Solicita la memoria necesaria para contener los valores de la matriz
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param ban Tamaño de la banda  */
   void solicitaMemoria(const int ren, const int col, const int ban);


   /// Compacta el renglon de la matriz liberando el espacio no usado (usar cuando ya no se desee modificar la matriz)
   /** @param ren Renglon a compactar */
   void compactaMatriz(int ren);


   /// Puntero a la matriz de datos
   ldouble **M;
   /// Arreglo que contiene los columnas de la matriz
   int *J;
   /// Indice al nuevo renglon de datos
   int *C_IndDat;
   /// Matriz compactada
   bool Compactada;
   /// Número de renglones distintos
   int C_NumRen;
   /// Ultimo renglon actualizado
   int Ultimo;


public:

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param ban Tamaño de la banda   */
   MatrizBandComp(const int ren, const int col, const int ban) : MatrizBandDisp()
   {
      solicitaMemoria(ren, col, ban);
      asignaNombre("SinNombre");
   }

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param ban Tamaño de la banda
       @param nmb Nombre de la matriz */
   MatrizBandComp(const int ren, const int col, const int ban, const char *nmb) : MatrizBandDisp()
   {
      solicitaMemoria(ren, col, ban);
      asignaNombre(nmb);
   }

   /// Destructor de la clase
   ~MatrizBandComp()
   {
      liberaMemoria();
   }


   /// Libera la memoria solicitada para la matriz
   void liberaMemoria(void);

   /// Inicializa la matriz al valor indicado
   /** @param val Valor por omisión para inicializar la matriz */
   void inicializa(ldouble val)
   {
      printf("\nFuncion no implementada en esta clase\n");
   }

   /// Asigna el valor indicado en el renglo y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @param val Valor */
   void asigna(const int ren, const int col, const ldouble val);

   /// Retorna el valor del renglon y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @return Valor */
   ldouble retorna(const int ren, const int col);

   /// Retorna el número de columnas de la banda para el renglon indicado
   /** @param ren Número de renglon
       @return Número de columnas de la banda para el renglon solicitado  */
   int retornaNumeroColumnasBanda(int ren);

   /// Retorna el número de columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Número de columna cuando se para en el renglon e indice de la banda  */
   int retornaNumeroColumna(int ren, int ind);

   /// Retorna el valor de la columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Valor de la columna cuando se para en el renglon e indice de la banda  */
   inline double retornaValorColumna(int ren, int ind)
   {
      return (M[ren][ind]);
   }

   /// Multiplica la matriz por el escalar pasado como parametro
   /** @param esc Escalar */
   void multiplica(ldouble esc);

   /// Multiplica la matriz A por la matriz B
   /** @param a Puntero a matriz densa
       @param b Puntero a matriz densa  */
   void multiplica(MatrizBandComp *a, MatrizBandComp *b);

   /// Multiplica la matriz por el vector B dejando el Resultado en R
   /** @param b Puntero a un Vector
       @param r Puntero a un Vector */
   void multiplica(Vector *b, Vector *r);

   /// Visualiza las matrices internas usadas para soportar a las matrices bandadas
   void visualizaMatricesInternas(void);


};


/**
Esta clase implementa los componentes para el trabajar con matrices bandadas de punto flotante que puede ser compactada
@example EjemploMatrizBandComp.cpp */

#endif
