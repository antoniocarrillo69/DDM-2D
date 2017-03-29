//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para definir el Esquema Maestro-Esclavo                                       //
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


#ifndef __Esquema_ME__
#define __Esquema_ME__


#define SUBDOMINIOS_CONTIGUOS


#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>


/// Clase base para definir el Esquema Maestro-Esclavo en MPI
/** Clase base para definir el Esquema Maestro-Esclavo para
    programar en paralelo mediante el paso de mensajes usando
    MPI, donde el primer procesador (id = 0) es el nodo mestro
    y el resto son los nodos esclavos. Las tareas se pueden repartir
    de manara que subdominios contiguos queden en un mismo
    nodo esclavo o queden en distinto nodo esclavo.
*/
/** @author Antonio Carrillo Ledesma
    @date primavera 2010
    @version 1.0.0
    @bug No hay errores conocidos
*/
class Esquema_ME
{

protected:

   /// Identificador
   int id;
   /// Número de procesadores
   int np;
   /// Número de tareas por nodo esclavo
   int *ta;
   /// Número de nodos esclavos a utilizar (los que tienen carga)
   int npu;


public:

   /// Constructor de la clase
   /** @param id Identificador
       @param np Número de procesadores */
   Esquema_ME(int id, int np)
   {
      this->id = id;
      this->np = np;
      ta = NULL;
   }

   /// Destructor de la clase
   ~Esquema_ME()
   {
      if (ta) delete []ta;
   }

   /// Genera el reparto de carga
   /** @param n Número de trabajos */
   void generaRepartoCarga(int n)
   {
      int i, j;

      // Ajusta el número de procesadores a usar
      if (n >= (np-1)) npu = np - 1;
      else npu = n;

      // Arreglo para soportar el reparto de carga por cada esclavo
      ta = new int [npu];
      for (i = 0; i < npu; i++) ta[i] = 0;

      // Reparto de carga
      j = 0, i = 0;
      while (i < n)
      {
         ta[j] ++;
         i++;
         j++;
         if (j >= npu) j = 0;
      }

      // Visualiza la carga
      for (i = 0; i < npu; i++) printf("\nId = %d  ==> TAREAS = %d ",i+1,ta[i]);
      printf("\n\nNumero de procesadores esclavos a usar = %d\n\n",npu);
      fflush(stdout);

      // Avisa a cada esclavo la cantidad de tareas a soportar
      for (i = 1; i<= npu; i++)  MPI::COMM_WORLD.Send(&ta[i-1], 1, MPI::INT, i, 1);
      j=0;
      for (i = (npu + 1); i < np; i++) MPI::COMM_WORLD.Send(&j, 1, MPI::INT, i, 1);
   }


#ifdef SUBDOMINIOS_CONTIGUOS
   // El reparto de carga se hace de forma que nodos contiguos queden en un mismo nodo esclavo
   /// Reparte la carga de trabajo entre los nodos esclavos
   /** @param np Numero de procesador esclavo
       @param st  Indice de tarea dentro del nodo esclavo
       @param tarea Tarea la cual debe ser repartida   */
   inline void reparteCargaTrabajo(int &np, int &ind, int tarea)
   {
      int i = 0;
      // Indica el número de tarea dentro del esclavo
      ind = tarea;
      while (ind >= ta[i])
      {
         ind -= ta[i];
         i++;
      }
      // Indica el número de esclavo en el que estará la tarea
      np = i+1;
   }

#else

   /// Reparte la carga de trabajo entre los nodos esclavos
   // El reparto de carga entre los nodos esclavos, si hay mas tareas que procesadores se asignaran mas de una tarea a cada esclavo, el reparto no necesariamente es homogeneo
   /** @param np Numero de procesador esclavo
       @param st  Indice de tarea dentro del nodo esclavo
       @param tarea Tarea la cual debe ser repartida   */
   inline void reparteCargaTrabajo(int &np, int &ind, int tarea)
   {
      // Indica el número de esclavo en el que estará la tarea
      np = (tarea % npu) + 1;
      // Indica el número de tarea dentro del esclavo
      ind = tarea / npu;
   }
#endif

   /// Retorna el numero de procesadores a usar por el esquema M-E
   /** @return  Número de procesadores a usar dentro del esquema Maestro-Esclavo */
   int numeroProcesadoresUsar(void)
   {
      return npu;
   }

};

#endif


