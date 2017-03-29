//////////////////////////////////////////////////////////////////////////////////////////////
// Clase con multiples comportamientos para manipular memoria                               //
//                                                                                          //
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



#ifndef __CtrlMemoria__
#define __CtrlMemoria__

#include <stdlib.h>
#include <stdio.h>
#include "Definiciones.hpp"



/// Clase con multiples comportamientos para manipular memoria
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.0
    @bug No hay errores conocidos
*/
class CtrlMemoria
{

public:

   /// Visualiza el error indicado por falta de memoria
   /** @param cad Puntero a la cadena de error */
   void errorSolicitudMemoria(const char *cad)
   {
      printf("\nError no hay memoria: %s\n",cad);
      exit(1);
   }

   /// Asigna memoria para un arreglo INT
   /** @param n Número de columnas
       @param cad Puntero a la cadena de error
       @return Puntero a un arreglo int */
   int *asignaMemoriaINT(int n, const char *cad)
   {
      int *var = new int[n];
      if (!var) errorSolicitudMemoria(cad);
      return var;
   }

   /// Libera memoria de un arreglo INT
   /** @param var Puntero al arreglo */
   void liberaMemoriaINT(int *var)
   {
      if (var) delete []var;
      var = NULL;
   }

   /// Asigna memoria para un arreglo ldouble
   /** @param n Número de columnas
       @param cad Puntero a la cadena de error
       @return Puntero a un arreglo ldouble */
   ldouble *asignaMemoriaLDOUBLE(int n, const char *cad)
   {
      ldouble *var = new ldouble[n];
      if (!var) errorSolicitudMemoria(cad);
      return var;
   }

   /// Libera memoria de un arreglo ldouble
   /** @param var Puntero al arreglo */
   void liberaMemoriaLDOUBLE(ldouble *var)
   {
      if (var) delete []var;
      var = NULL;
   }

   /// Asigna memoria para una matriz int
   /** @param n Número de renglones
       @param m Número de columnas
       @param cad Puntero a la cadena de error
       @return Puntero a la matriz int */
   int **asignaMemoriaINT(int n, int m, const char *cad)
   {
      int **var = new int*[n];
      if (!var) errorSolicitudMemoria(cad);
      int i;
      for (i = 0; i < n; i++)
      {
         var[i] = new int[m];
         if (!var[i]) errorSolicitudMemoria(cad);
      }
      return var;
   }

   /// Libera memoria de una matriz int
   /** @param n Número de renglones
       @param var Puntero a la matriz int */
   void liberaMemoriaINT(int n, int **var)
   {
      int i;
      if (var)
      {
         for (i = 0; i < n; i++)
         {
            delete []var[i];
            var[i] = NULL;
         }
         delete []var;
         var = NULL;
      }
   }

   /// Asigna memoria para una matriz ldouble
   /** @param n Número de renglones
       @param m Número de columnas
       @param cad Puntero a la cadena de error
       @return Puntero a la matriz ldouble */
   ldouble **asignaMemoriaLDOUBLE(int n, int m, const char *cad)
   {
      ldouble **var = new ldouble*[n];
      if (!var) errorSolicitudMemoria(cad);
      int i;
      for (i = 0; i < n; i++)
      {
         var[i] = new ldouble[m];
         if (!var[i]) errorSolicitudMemoria(cad);
      }
      return var;
   }

   /// Libera memoria de una matriz ldouble
   /** @param n Número de renglones
       @param var Puntero a la matriz ldouble */
   void liberaMemoriaLDOUBLE(int n, ldouble **var)
   {
      int i;
      if (var)
      {
         for (i = 0; i < n; i++)
         {
            delete []var[i];
            var[i] = NULL;
         }
         delete []var;
         var = NULL;
      }
   }


};


#endif


