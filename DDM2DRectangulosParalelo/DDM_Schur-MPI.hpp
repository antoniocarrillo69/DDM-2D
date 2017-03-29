//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para definir el Esquema Maestro-Esclavo del método de descomposición de dominio de //
// subestructuración (Complemento de Schur)                                                 //
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


#ifndef __DDM_Schur_MPI__
#define __DDM_Schur_MPI__


#include "Esquema_ME.hpp"
#include "DDM_Schur.hpp"
#include "Problema_2DEjemp01.hpp"
#include "Geometria_2DRectangulos.hpp"
#include <time.h>



/// Clase para definir el Esquema Maestro-Esclavo del método de descomposición de dominio de subestructuración (Complemento de Schur)
/** Clase para definir el Esquema Maestro-Esclavo para programar
    en paralelo mediante el paso de mensajes usando MPI, donde
    el primer procesador (id = 0) es el nodo mestro y el resto
    son los nodos esclavos. Las tareas se reparten de una a una
    entre los nodos esclavos, si hay mas tareas que procesadores
    se asignaran mas de una tarea a cada esclavo, el reparto no
    necesariamente es homogeneo.
*/
/** @author Antonio Carrillo Ledesma
    @date primavera 2010
    @version 1.0.0
    @bug No hay errores conocidos
*/
class DDM_Schur_MPI: public DDM_Schur, public Esquema_ME
{
protected:

   /// Tiempo inicial
   time_t t1;
   /// Tiempo final
   time_t t2;
   /// Número de tareas por nodo esclavo
   int nta;
   /// Número de esclavo en el que estará la tarea
   int xnp;
   /// Número de tarea dentro del esclavo
   int st;
   /// Arreglo para enviar y/o recibir mensajes
   int msn[10];


private:

   /// Definicion de la geometria
   Geometria_2DRectangulos *ge;
   /// Definicion del problema
   Problema_2DEjemp01 *pr;
   /// Tamaño de la malla gruesa en X
   int malla_gruesa_x;
   /// Tamaño de la malla gruesa en Y
   int malla_gruesa_y;
   /// Tamaño de la malla fina en X
   int malla_fina_x;
   /// Tamaño de la malla fina en Y
   int malla_fina_y;
   /// Tolerancia para finalizar el método
   ldouble eps;


   /// Sobrecarga de los comportamientos a paralelizar
   void funPar00(int ns)
   {  }

   int funPar01(int ind, Problema_2D *pr, ldouble *sub, int *par, ldouble ep);

   void funPar02(int ind, ldouble **cd, int tm);

   void funPar03(int ind);

   void funPar04(int ind, ldouble *val1, ldouble *val2, int tm);

   void funPar05(int ind, ldouble *val, int tm);

   void funPar06(int ind, ldouble *val, int tm);

   void funPar07(int ind, ldouble **cd, ldouble *vl, int tm);

   ldouble funPar08(int ind)
   {      }

   void funPar09(int ind)
   {      }


public:

   /// Constructor de la clase
   DDM_Schur_MPI(int id, int np, int nx, int ny, int mx, int my, ldouble ep) : Esquema_ME(id, np), DDM_Schur()
   {
      // Controlador del esquema M-E
      if (id == 0)
      {
         time(&t1);
         printf("\nMaestro ID=%d\n",id);
         fflush(stdout);

         malla_gruesa_x = nx;
         malla_gruesa_y = ny;
         malla_fina_x = mx;
         malla_fina_y = my;
         eps = ep;

         // manda el numero de tareas que deben hacer nodo esclavo
         generaRepartoCarga(malla_gruesa_x*malla_gruesa_y);
      }
      else
      {
         // Numero de tareas a soportar
         MPI::COMM_WORLD.Recv(&nta, 1, MPI::INT, 0, 1);
         printf("\nEsclavo ID=%d  Tareas = %d\n",id,nta);
         fflush(stdout);
      }
   }


   /// Destructor de la clase
   ~DDM_Schur_MPI()
   {
      // Borra la memoiria dinamica
      delete pr;
      if (id == 0) // Maestro
      {
         delete ge;

         time(&t2);
         printf("\nTiempo C?lculo: %f\n",difftime(t2,t1));
         fflush(stdout);
      }
   }


   /// Sobrecarga de la aplicacion maestro
   void haz(void);

   /// Esclavo
   void Esclavo(void);

};


#endif


