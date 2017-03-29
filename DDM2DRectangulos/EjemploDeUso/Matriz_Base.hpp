//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices                                                      //
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



#ifndef __Matriz_Base__
#define __Matriz_Base__


#include "Definiciones.hpp"
#include "Ctrl_vis.hpp"
#include <stdio.h>
#include <stdlib.h>


#define MATRIZ_BANDADA            0
#define MATRIZ_DENSA              1
#define MATRIZ_ENTERA_DENSA       2
#define MATRIZ_DISPERSA           3
#define MATRIZ_BANDADA_COMPACTA   4
#define MATRIZ_DISPERSA_COMPACTA  5
#define MATRIZ_TAMANO_VARIABLE    6
#define MATRIZ_RALA               7


/// Clase base para el trabajar con matrices
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Matriz_Base
{

protected:
   /// Número de columnas
   int Col;
   /// Número de renglones
   int Ren;
   /// Tamaño de la banda (solo si es bandada o dispersa)
   int Ban;
   /// Nombre de la matriz
   char *Nmb;
   /// Indica el tipo de matriz de que se trate
   int Tipo_Matriz;



public:

   /// Constructor de la clase
   Matriz_Base(void)
   {
      Nmb = NULL;
      Ban = 0;
   }

   /// Destructor de la clase
   ~Matriz_Base()
   {
      delete []Nmb;
      Nmb = NULL;
   }

   /// Asigna nombre a la matriz
   /** @param nmb Nombre de la matriz */
   void asignaNombre(const char *nmb);

   /// Retorna el nombre de la matriz
   /** @return Regresa un puntero al nombre de la matriz */
   inline char *nombre(void)
   {
      return Nmb;
   }

   /// Retorna el número de renglones de la matriz
   /** @return Regresa el número de renglones de la matriz */
   inline int renglones(void)
   {
      return Ren;
   }

   /// Retorna el número de columnas de la matriz
   /** @return Regresa el número de columnas de la matriz */
   inline int columnas(void)
   {
      return Col;
   }

   /// Es una matriz cuadrada
   /** @return (1) en caso de ser matriz cuadrada. (0) en caso contrario */
   inline int matrizCuadrada(void)
   {
      return (Col == Ren ? 1: 0);
   }

   /// Revisa si ambas matrices tienen la misma dimensión
   /** @return (1) en caso de que ambas matrices tengan la misma dimensión, (0) en caso contrario*/
   int mismaDimension(Matriz_Base *a)
   {
      if (a->columnas() == Col && a->renglones() == Ren) return 1;
      return 0;
   }

   /// Retorna el tipo de matriz
   /** @return Tipo de matriz MATRIZ_BANDADA, MATRIZ_DENSA, MATRIZ_ENTERA_DENSA, MATRIZ_DISPERSA */
   inline int retornaTipoMatriz(void)
   {
      return Tipo_Matriz;
   }

   /// Visualiza el error de falta de memoria para soportar la matriz
   void faltaMemoria(void)
   {
      printf("\nError no hay memoria para la matriz\n");
      exit(1);
   }

   /// Visualiza información general de la matriz
   void visualizaInformacion(void);

   /// Tamaño de la matriz (aproximado) en Kb
   /** @return Tamaño de la matriz en Kb */
   ldouble tamano(void);

   /// Visualiza el tamaño en memoria de la matriz en Kb
   void visualizaTamano(void);

   /// Retorna el máximo tamaño en todas las columnas que sean distintos de cero
   /** @return Máximo tamaño de columnas ocupadas en la matriz */
   virtual int maximoTamanoColumnaOcupado(void) = 0;

   /// Retorna el número de entradas distintas de cero en la matriz
   /** @return Número de entradas distintas de cero en la matriz */
   virtual int entradasDistintasCero(void) = 0;

   /// Libera la memoria solicitada para la matriz
   virtual void liberaMemoria(void) = 0;


};

#endif
