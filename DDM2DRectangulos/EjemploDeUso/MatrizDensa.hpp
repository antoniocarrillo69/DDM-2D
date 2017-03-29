//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices densas de punto flotante                             //
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



#ifndef __MatrizDensa__
#define __MatrizDensa__

#include "Matriz.hpp"



/// Clase para el trabajar con matrices densas de punto flotante
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class MatrizDensa: public Matriz
{
private:

   /// Puntero a la matriz de datos
   ldouble **M;
   /// Indica el estado de la matriz cuando esta compactada
   int Estado;


   /// Solicita la memoria necesaria para contener los valores de la matriz
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz */
   void solicitaMemoria(const int ren, const int col);



public:

   /// Constructor de la clase
   MatrizDensa(void) : Matriz()
   {
      Estado = 0;
      solicitaMemoria(1, 1);
      asignaNombre("SinNombre");
   }

   /// Constructor de la clase
   /** Genera una matriz a partir de los datos de otra
       @param mat Matriz del cual se hara una copia  */
   MatrizDensa(MatrizDensa &mat) : Matriz()
   {
      solicitaMemoria(mat.renglones(),mat.columnas());
      asignaNombre(mat.nombre());
      int i, j;
      for (i = 0; i < Col; i++)
      {
         for (j = 0; j < Ren; j++) M[i][j] = mat.retorna(i,j);
      }
   }

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz */
   MatrizDensa(const int ren, const int col) : Matriz()
   {
      Estado = 0;
      solicitaMemoria(ren, col);
      asignaNombre("SinNombre");
   }

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param nmb Nombre de la matriz*/
   MatrizDensa(const int ren, const int col, const char *nmb) : Matriz()
   {
      Estado = 0;
      solicitaMemoria(ren, col);
      asignaNombre(nmb);
   }

   /// Destructor de la clase
   ~MatrizDensa()
   {
      liberaMemoria();
   }

   /// Libera la memoria solicitada para la matriz
   void liberaMemoria(void);

   /// Constructor de la clase
   /** @param nren Nuevo número de renglones de la matriz
       @param ncol Nuevo número de columnas de la matriz */
   void redimensiona(int nren, int ncol)
   {
      liberaMemoria();
      solicitaMemoria(nren, ncol);
      inicializa(0.0);
   }

   /// Inicializa la matriz al valor indicado
   /** @param val Valor por omisión para inicializar la matriz */
   void inicializa(const ldouble val);


#ifdef DEPURAR
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
#else
   /// Asigna el valor indicado en el renglo y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @param val Valor */
   inline void asigna(const int ren, const int col, const ldouble val)
   {
      M[ren][col] = val;
   }

   /// Retorna el valor del renglon y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @return Valor */
   inline ldouble retorna(const int ren, const int col)
   {
      return M[ren][col];
   }
#endif


   /// Multiplica la matriz por el escalar pasado como parametro
   /** @param esc Escalar */
   void multiplica(ldouble esc);

   /// Multiplica la matriz A por la matriz B
   /** @param a Puntero a matriz densa
       @param b Puntero a matriz densa  */
   void multiplica(MatrizDensa *a, MatrizDensa *b);

   /// Multiplica la matriz por el vector B dejando el Resultado en R
   /** @param b Puntero a un Vector
       @param r Puntero a un Vector */
   void multiplica(Vector *b, Vector *r);

   /// Retorna el número de columnas de la banda para el renglon indicado
   /** @param ren Número de renglon
       @return Número de columnas de la banda para el renglon solicitado  */
   int retornaNumeroColumnasBanda(int ren)
   {
      printf("\nFuncion no implementada en esta clase %d\n",ren);
      return 0;
   }

   /// Retorna el número de columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Número de columna cuando se para en el renglon e indice de la banda  */
   int retornaNumeroColumna(int ren, int ind)
   {
      printf("\nFuncion no implementada en esta clase: %d %d\n",ren, ind);
      return 0;
   }

   /// Retorna el valor de la columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Valor de la columna cuando se para en el renglon e indice de la banda  */
   inline double retornaValorColumna(int ren, int ind)
   {
      printf("\nFuncion no implementada en esta clase: %d %d\n",ren, ind);
      return 0;
   }

};

/**
Esta clase implementa los componentes para el trabajar con matrices densas de punto flotante
@example EjemploMatrizDensa.cpp */

#endif
