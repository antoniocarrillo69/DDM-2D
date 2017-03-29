//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices dispersas de punto flotante                          //
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



#ifndef __MatrizDispersa__
#define __MatrizDispersa__


#include "MatrizBandDisp.hpp"


/// Clase para el trabajar con matrices dispersas de punto flotante basada en el algoritmo Jagged Diagonal Storage (JDS)
/// El algoritmo esta optimizado para hacer producto matriz vector
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
    @todo Hacer comportamiento para cambiar tamaño de banda
    @todo Multiplicación de matrices
*/
class MatrizDispersa : public MatrizBandDisp
{
private:

   /// Solicita la memoria necesaria para contener los valores de la matriz
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param ban Tamaño de la banda  */
   void solicitaMemoria(const int ren, const int col, const int ban);


   /// Puntero a la matriz de datos
   ldouble **M;
   /// Arreglo que contiene los columnas de la matriz
   int **J;


public:

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param ban Tamaño de la banda   */
   MatrizDispersa(const int ren, const int col, const int ban) : MatrizBandDisp()
   {
      solicitaMemoria(ren, col, ban);
      asignaNombre("SinNombre");
   }

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param ban Tamaño de la banda
       @param nmb Nombre de la matriz*/
   MatrizDispersa(const int ren, const int col, const int ban, const char *nmb) : MatrizBandDisp()
   {
      solicitaMemoria(ren, col, ban);
      asignaNombre(nmb);
   }

   ~MatrizDispersa()
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

   /// Retorna el número de columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param col Número de columna
       @return Número de columna cuando se para en el renglon e indice de la banda  */
   ldouble retorna(const int ren, const int col);

   /// Retorna el número de columnas de la banda para el renglon indicado
   /** @param ren Número de renglon
       @return Número de columnas de la banda para el renglon solicitado  */
   int retornaNumeroColumnasBanda(int ren);

   /// Retorna el número de columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Número de columna cuando se para en el renglon e indice de la banda  */
   inline int retornaNumeroColumna(int ren, int ind)
   {
      return (J[ren][ind]);
   }

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
   void multiplica(MatrizDispersa *a, MatrizDispersa *b);

   /// Multiplica la matriz por el vector B dejando el Resultado en R
   /** @param b Puntero a un Vector
       @param r Puntero a un Vector */
   void multiplica(Vector *b, Vector *r);

   /// Visualiza las matrices internas usadas para soportar a las matrices bandadas
   void visualizaMatricesInternas(void);


};


/**
Esta clase implementa los componentes para el trabajar con matrices dispersas de punto flotante
@example EjemploMatrizDispersa.cpp */

#endif
