//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con vectores enteros                                              //
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



#ifndef __VectorInt__
#define __VectorInt__

#include "Definiciones.hpp"
#include "Vector_Base.hpp"



/// Clase para el trabajar con vectores con valores enteros
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class VectorInt : public Vector_Base
{
private:

   /// Puntero al contenido del Vector
   int *V;

   /// Solicita la memoria necesaria para contener los valores del vector
   /** @param col Número de columnas del vector
       @param val Valor por omision para inicializar el vector */
   void solicitaMemoria(const int col, const int val);

   /// Libera la memoria solicitada dinamicamente
   /** @param tp Distinto de cero libera toda la memoria */
   void liberaMemoria(int tp)
   {
      delete []V;
      V = NULL;
      if (tp)
      {
         delete []Nmb;
         Nmb = NULL;
      }
   }

public:


   /// Constructor de la clase
   VectorInt(void) : Vector_Base()
   {
      solicitaMemoria(1,0);
      asignaNombre("Sin Nombre");
   }

   /// Constructor de la clase
   /** Genera un Vector a partir de los datos de otro
       @param vec Vector del cual se hara una copia  */
   VectorInt(VectorInt &vec) : Vector_Base()
   {
      solicitaMemoria(vec.columnas(),0);
      asignaNombre(vec.nombre());
      for (int i = 0; i < Col; i++) V[i] = vec.retorna(i);
   }


   /// Constructor de la clase
   /** Genera un Vector del tamaño expecificado por el número de columnas e inicializado por omisión a cero.
       @param col Número de columnas del vector  */
   VectorInt(const int col) : Vector_Base()
   {
      solicitaMemoria(col,0);
      asignaNombre("Sin Nombre");
   }

   /// Constructor de la clase
   /** Genera un Vector del tamaño expecificado por el número de columnas e inicializado por omisión al valor val.
       @param col Número de columnas del vector
       @param val Valor por omisión para inicializar el vector */
   VectorInt(const int col, int val) : Vector_Base()
   {
      solicitaMemoria(col,val);
      asignaNombre("Sin Nombre");
   }

   /// Constructor de la clase
   /** Genera un Vector del tamaño expecificado por el número de columnas e inicializado por omisión al valor val.
       @param col Número de columnas del vector
       @param val Valor por omisión para inicializar el vector
       @param nmb Nombre del vector  */
   VectorInt(const int col, const int val, const char *nmb) : Vector_Base()
   {
      solicitaMemoria(col,val);
      asignaNombre(nmb);
   }

   /// Constructor de la clase
   /** Genera un Vector del tamaño expecificado por el número de columnas e inicializado por omisión a cero.
       @param col Numero de columnas del vector
       @param nmb Nombre del vector  */
   VectorInt(const int col, const char *nmb) : Vector_Base()
   {
      solicitaMemoria(col,0);
      asignaNombre(nmb);
   }

   /// Destructor de la clase
   ~VectorInt()
   {
      liberaMemoria(1);
   }

   /// Redimensiona el tamaño del vector
   /** @param ncol Nuevo número de columnas */
   void redimensiona(int ncol)
   {
      liberaMemoria(0);
      solicitaMemoria(ncol,0);
   }

   /// Inicializa el vector al valor val indicado
   /** @param val Valor por omisión para inicializar el vector */
   void inicializa(const int val);

   /// Retorna el valor de la columna col
   /** @param col Columna
       @return Valor */
   inline int operator [] (size_t col)
   {
      return retorna(col);
   }

   /// Retorna el valor de la columna col
   /** @param col Columna
       @return Valor */
   inline int operator () (size_t col)
   {
      return retorna(col);
   }


#ifdef DEPURAR
   /// Asigna el valor val a la columna col
   /** @param col Columna
       @param val Valor */
   void asigna(const int col, const int val)
   {
      if (col < 0 || col >= Col)
      {
         printf("Error indices desbordados (%d)\n", col);
         visualizaInformacion();
         exit(1);
      }
      V[col] = val;
   }


   /// Retorna el valor de la columna col
   /** @param col Columna
       @return Valor */
   int retorna(const int col)
   {
      if (col < 0 || col >= Col)
      {

         printf("Error indices desbordados (%d)\n", col);
         visualizaInformacion();
         exit(1);
      }
      return V[col];
   }

#else
   /// Asigna el valor val a la columna col
   /** @param col Columna
       @param val Valor */
   inline void asigna(const int col, const int val)
   {
      V[col] = val;
   }

   /// Retorna el valor de la columna col
   /** @param col Columna
       @return Valor */
   inline int retorna(const int col)
   {
      return V[col];
   }
#endif

   /// Copia el contenido del vector al vector a
   /** @param a Puntero a un vector */
   void copia(VectorInt *a);

   /// Visualiza el vector
   /** @param nl (1) Visualiza el vector en forma renglones, (0) en forma de columnas
       @param num (1) Numera las componentes del vector, (0) no lo hace */
   void visualiza(int nl = 0, int num = 0);

   /// Tamaño del vector (aproximado) en Kb
   /** @return tamaño del vector en Kb */
   inline ldouble tamano(void)
   {
      ldouble t = (((unsigned long) sizeof(V) * Col) / 1024.0);
      return t;
   }

   /// Visualiza información general del vector
   inline void visualizaInformacion(void)
   {
      printf("\nVector entero \"%s\" de dimensión: %d \n",Nmb,Col);
   }
};

/**
Esta clase implementa los comportamientos más comunes para el trabajar con vectores de valor entero
@example EjemploVectorInt.cpp */

#endif
