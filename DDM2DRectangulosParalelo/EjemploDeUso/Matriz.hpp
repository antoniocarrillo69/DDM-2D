//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para el trabajar con matrices de punto flotante                               //
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



#ifndef __Matriz__
#define __Matriz__

#include "Matriz_Base.hpp"
#include "Vector.hpp"


/// Clase base para el trabajar con matrices de punto flotante
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Matriz: public Matriz_Base
{

public:

   /// Constructor de la clase
   Matriz(void) : Matriz_Base()
   {}

   /// Retorna el valor del renglon y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @return Valor */
   inline ldouble operator() (size_t ren, size_t col)
   {
      return retorna(ren,col);
   }

   /// Asigna el valor indicado en el renglon y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @param val Valor */
   virtual void asigna(const int ren, const int col, const ldouble val) = 0;

   /// Retorna el valor del renglon y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @return Valor */
   virtual ldouble retorna(const int ren, const int col) = 0;

   /// Retorna el contenido del renglon de la matriz en el arreglo
   /** @param r Renglon
       @param[out] arr Arreglo de tipo ldouble
       @param tam Tamaño del arreglo */
   inline void retornaRenglon(int r, ldouble *arr, int tam)
   {
      int i, t = Col < tam ? Col : tam;
      for (i = 0; i < t; i++) arr[i] = retorna(r,i);
   }

   /// Inicializa la matriz con el valor indicado
   /** @param val Valor */
   virtual void inicializa(const ldouble val) = 0;

   /// Inicializa la matriz como una matriz diagonal con el valor indicado
   /** @param val Valor */
   void inicializaDiagonal(const ldouble val);

   /// Visualiza la matriz
   /** @param tp (1) Se visualiza el vector de en formato de notación científica, (0) formato notación de punto flotante */
   void visualiza(const int tp);

   /// Convierte el arreglo unidimensional en parte de la matriz en el renglon Ren y de tamaño Tam
   /** @param a puntero al arreglo
       @param ren Renglon en el cual se insertara el contenido del arreglo
       @param tam Tamaño del arreglo  */
   void convierte(ldouble *a, int ren, int tam);

   /// Convierte un arreglo bidimensional de numero de renglones REN y columnas Col 
   /** @param a puntero al arreglo
       @param ren Renglones
       @param col Columnas  */
   void convierte(ldouble **a, int ren, int col);
   
   /// Convierte el contenido del vector en parte de la matriz en el renglon Ren
   /** @param ren Renglon en el cual se insertara el contenido del arreglo
       @param a puntero al vector */
   void convierte(int ren, Vector *a);

   /// Convierte el contenido del arreglo unidimensional que contiene una matriz de Ren x Col a matriz
   /** @param ren Número de renglones
       @param col Número de columnas
       @param a puntero al arreglo */
   void convierte(int ren, int col, ldouble *a);

   /// Retorna todo el contenido de la matriz como un vector
   /** @param a puntero al vector */
   void retornaVector(Vector *a);

   /// Copia el contenido de la matriz a la matriz pasada como parámetro
   /** @param a Puntero a una Matriz */
   virtual void copia(Matriz *a);

   /// Suma las matrices A y B
   /** @param a Puntero a una Matriz
       @param b Puntero a una Matriz */
   void suma(Matriz *a, Matriz *b);

   /// Suma a la matriz el contenido de la matriz pasada como parámetro
   /** @param a Puntero a una Matriz */
   void suma(Matriz *a);

   /// Resta a la matriz A la matriz B
   /** @param a Puntero a una Matriz
       @param b Puntero a una Matriz */
   void resta(Matriz *a, Matriz *b);

   /// Resta a la matriz el contenido de la matriz padada como parámetro
   /** @param a Puntero a una Matriz */
   void resta(Matriz *a);

   /// Multiplica la matriz por el escalar pasado como parametro
   /** @param esc Escalar */
   virtual void multiplica(ldouble esc) = 0;

   /// Multiplica la matriz por el vector B dejando el Resultado en R
   /** @param b Puntero a un Vector
       @param r Puntero a un Vector */
   virtual void multiplica(Vector *b, Vector *r) = 0;

   /// Transpone la matriz pasada como parámetro
   /** @param a Puntero a la matriz */
   void transpuesta(Matriz *a);

   /// Regresa verdadero si las matrices son iguales, cero en caso contrario
   /** @param a Puntero a la matriz
       @param eps Tolerancia usada en la comparación
       @return (1) si son iguales, (0) en caso contrario */
   int iguales(Matriz *a, ldouble eps = 1e-14);

   /// Retorna el máximo tamaño en todas las columnas que sean distintos de cero
   /** @return Máximo tamaño de columnas ocupadas en la matriz */
   int  maximoTamanoColumnaOcupado(void);

   /// Retorna el número de entradas distintas de cero en la matriz
   /** @return Número de entradas distintas de cero en la matriz */
   int  entradasDistintasCero(void);

   /// Retorna el número de columnas de la banda para el renglon indicado
   /** @param ren Número de renglon
       @return Número de columnas de la banda para el renglon solicitado  */
   virtual int retornaNumeroColumnasBanda(int ren) = 0;

   /// Retorna el número de columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Número de columna cuando se para en el renglon e indice de la banda  */
   virtual int retornaNumeroColumna(int ren, int ind) = 0;


   /// Retorna el valor de la columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Valor de la columna cuando se para en el renglon e indice de la banda  */
   virtual double retornaValorColumna(int ren, int ind) = 0;

};

#endif
