//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal                                                    //
// Revisión: 1 de Junio del 2006                                                            //
//                                                                                          //
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



#ifndef __ResuelveSistemaLineal__
#define __ResuelveSistemaLineal__


#include <stdlib.h>
#include <stdio.h>
#include "Matriz.hpp"

// Método numérico
#define CGM            0
#define FACT_LU        1
#define GAUSSSEIDEL    2
#define INVERSA        3
#define JACOBI         4
#define TRIDIAGONAL    5
#define FACT_CHOLESKI  6


// Nombre del método
static const char Nmb[][50]= {"CGM","Factorización LU","Gauss-Seidel","Inversa","Jacobi","Tridiagonal","Choleski"};

// Requiere matriz del tipo Bandada, Dispersa, Densa
#define REQUIERE_MAT_BAND   0
#define REQUIERE_MAT_DISP   1
#define REQUIERE_MAT_DENS   2


/// Clase para resolución del sistema lineal
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class ResuelveSistemaLineal
{
protected:

   /// Indica si el método numérico modifica la matriz
   bool MetodoModificaMatriz;
   /// Numero de iteraciones en la resolución del sistema lineal
   int NumIteraciones;
   /// Método Numerico
   int MetodoNumerico;
   /// Requiere matriz del tipo Bandada, Dispersa, Densa
   int RequiereMatriz;

   /// Vector solución
   Vector *X;
   /// Vactor lado derecho
   Vector *B;
   /// Matriz
   Matriz *M;

   /// Visualiza el error indicado y termina el programa
   /** @param txt Puntero al mensaje de error */
   void error(const char *txt)
   {
      printf("\nError resolver el sistema Lineal: %s\n\n",txt);
      exit(1);
   }


public:

   /// Resuelve el sistema lineal
   /** @param m Puntero a la matriz del sistema lineal
        @param b Puntero a un vector, lado derecho del sistema lineal
        @param x Puntero a un vector, solución del sistema lineal */
   void inicializa(Matriz *m, Vector *b, Vector *x)
   {
      M = m;
      X = x;
      B = b;
   }

   /// Constructor de la clase
   ResuelveSistemaLineal(void)
   {
      NumIteraciones = 0;
   }

   /// Resuelve el sistema lineal
   virtual void resuelve(void) = 0;

   /// Resuelve el sistema lineal
   /** @param b Puntero a un vector, lado derecho del sistema lineal
       @param x Puntero a un vector, solución del sistema lineal */
   virtual void resuelve(Vector *b, Vector *x) = 0;
   
   
   /// Retorna el número de iteraciones en la resolución del sistema lineal
   /** @return Número de iteraciones */
   int retornaNumeroIteraciones(void)
   {
      return NumIteraciones;
   }

   /// Indica si el método numérico modifica la matriz
   /** @return (true) si el método numérico modifica la matriz, (false) en caso contrario */
   bool elMetodoModificaMatriz(void)
   {
      return MetodoModificaMatriz;
   }

   /// Retorna el método numérico
   /** @return Retorna el método numérico CGM, FACT_LU, GAUSSSEIDEL, INVERSA, JACOBI, TRIDIAGONAL, etc  */
   int retornaMetodoNumerico(void)
   {
      return MetodoNumerico;
   }

   /// Retorna el tipo de matriz que requiere el método
   /** @return Retorna el tipo de matriz Bandada, Dispersa, Densa  */
   int retornaRequiereMatriz(void)
   {
      return RequiereMatriz;
   }

   /// Visualiza la información del método
   void informacionMetodo(void)
   {
      if (MetodoModificaMatriz) printf("\nMétodo %s para resolver el sistema lineal\n",Nmb[MetodoNumerico]);
      else printf("\nMétodo %s, iteraciones para resolver el sistema lineal %d\n",Nmb[MetodoNumerico],NumIteraciones);
   }


};

#endif
