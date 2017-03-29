//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para el trabajar con vectores                                                 //
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


#ifndef __Vector_Base__
#define __Vector_Base__


#include <stdlib.h>
#include <string.h>
#include <stdio.h>





///  Clase base para el trabajar con vectores
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Vector_Base
{
protected:

   /// Número de columnas del vector
   int Col;

   /// Nombre del vector
   char *Nmb;



public:


   /// Constructor de la clase
   Vector_Base(void)
   {
      Col = 0;
      Nmb = NULL;
   }

   /// Destructor de la clase
   ~Vector_Base()
   {
      delete []Nmb;
      Nmb = NULL;
   }

   /// Asigna nombre al vector
   /** @param nmb Nombre del vector */
   void asignaNombre(const char *nmb)
   {
      delete []Nmb;
      Nmb = NULL;
      Nmb = new char[strlen(nmb)+2];
#ifdef DEPURAR
      if (!Nmb)
      {
         printf("\nError no hay memoria para el nombre del vector\n");
         exit(1);
      }
#endif
      strcpy(Nmb, nmb);
   }


   /// Retorna el nombre del vector
   /** @return Regresa un puntero al nombre del vector */
   inline char *nombre(void)
   {
      return Nmb;
   }

   /// Retorna el número de columnas del vector
   /** @return Regresa el número de columnas del vector */
   inline int columnas(void)
   {
      return Col;
   }


   /// Visualiza información general del vector
   virtual void visualizaInformacion(void) = 0;

};

#endif
