//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con vectores de punto flotante                                    //
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


#ifndef __Vector__
#define __Vector__

#include "Definiciones.hpp"
#include "Vector_Base.hpp"





///  Clase para el trabajar con vectores de punto flotante
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Vector: public Vector_Base
{
protected:


   /// Puntero al contenido del Vector
   ldouble *V;

   /// Solicita la memoria necesaria para contener los valores del vector
   /** @param col Número de columnas del vector
       @param val Valor por omision para inicializar el vector */
   void solicitaMemoria(const int col, const ldouble val);


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
   Vector(void) : Vector_Base()
   {
      solicitaMemoria(1,0);
      asignaNombre("Sin Nombre");
   }

   /// Constructor de la clase
   /** Genera un Vector a partir de los datos de otro
       @param vec Vector del cual se hara una copia  */
   Vector(Vector &vec) : Vector_Base()
   {
      solicitaMemoria(vec.columnas(),0);
      asignaNombre(vec.nombre());
      for (int i = 0; i < Col; i++) V[i] = vec.retorna(i);
   }

   /// Constructor de la clase
   /** Genera un Vector del tamaño expecificado por el número de columnas e inicializado por omisión a cero.
      @param col Número de columnas del vector  */
   Vector(const int col) : Vector_Base()
   {
      solicitaMemoria(col,0.0);
      asignaNombre(" ");
   }

   /// Constructor de la clase
   /** Genera un Vector del tamaño expecificado por el número de columnas e inicializado por omisión al valor val.
      @param col Número de columnas del vector
      @param val Valor por omisión para inicializar el vector */
   Vector(const int col, const ldouble val)  : Vector_Base()
   {
      solicitaMemoria(col, val);
      asignaNombre(" ");
   }

   /// Constructor de la clase
   /** Genera un Vector del tamaño expecificado por el número de columnas e inicializado por omisión al valor val.
      @param col Número de columnas del vector
      @param val Valor por omisión para inicializar el vector
      @param nmb Nombre del vector */
   Vector(const int col, const ldouble val, const char *nmb)  : Vector_Base()
   {
      solicitaMemoria(col, val);
      asignaNombre(nmb);
   }

   /// Constructor de la clase
   /** Genera un Vector del tamaño expecificado por el número de columnas e inicializado por omisión a cero.
       @param col Numero de columnas del vector
       @param nmb Nombre del vector  */
   Vector(const int col, const char *nmb) : Vector_Base()
   {
      solicitaMemoria(col,0.0);
      asignaNombre(nmb);
   }

   /// Destructor de la clase
   ~Vector()
   {
      liberaMemoria(1);
   }

   /// Redimensiona el tamaño del vector
   /** @param ncol Nuevo número de columnas */
   void redimensiona(int ncol)
   {
      liberaMemoria(0);
      solicitaMemoria(ncol,0.0);
   }


   /// Inicializa el vector al valor val indicado
   /** @param val Valor por omisión para inicializar el vector */
   void inicializa(const ldouble val);


   /// Retorna el valor de la columna col
   /** @param col Columna
       @return Valor */
   inline ldouble operator [] (size_t col)
   {
      return retorna(col);
   }

   /// Retorna el valor de la columna col
   /** @param col Columna
       @return Valor */
   inline ldouble operator () (size_t col)
   {
      return retorna(col);
   }


#ifdef DEPURAR
   /// Asigna el valor val a la columna col
   /** @param col Columna
       @param val Valor */
   inline void asigna(const int col, const ldouble val)
   {
      if (col < 0 || col >= Col)
      {
         visualizaInformacion();
         printf("Error indice desbordado (%d)\n",col);
         exit(1);
      }
      V[col] = val;
   }


   /// Retorna el valor de la columna col
   /** @param col Columna
       @return Valor */
   inline ldouble retorna(const int col)
   {
      if (col < 0 || col >= Col)
      {
         visualizaInformacion();
         printf("Error indice desbordado (%d)\n", col);
         exit(1);
      }
      return V[col];
   }

#else
   /// Asigna el valor val a la columna col
   /** @param col Columna
       @param val Valor */
   inline void asigna(const int col, const ldouble val)
   {
      V[col] = val;
   }


   /// Retorna el valor de la columna col
   /** @param col Columna
       @return Valor */
   inline ldouble retorna(const int col)
   {
      return V[col];
   }
#endif

   /// Visualiza el vector
   /** @param tp (1) Se visualiza el vector de en formato de notación científica, (0) formato notación de punto flotante
       @param nl (1) Visualiza el vector en forma renglones, (0) en forma de columnas
       @param num (1) Numera las componentes del vector, (0) no lo hace */
   void visualiza(const int tp, int nl = 0, int num = 0);

   /// Copia el contenido del vector al vector a
   /** @param a Puntero a un vector */
   void copia(Vector *a);

   /// Convierte el contenido del arreglo a de tamaño tam a vector
   /** @param a Arreglo de tipo ldouble
       @param tam Tamaño del arreglo */
   void convierte(ldouble *a, int tam);

   /// Suma los vectores a y b
   /** @param a Puntero a un vector
       @param b Puntero a un vector */
   void suma(Vector *a, Vector *b);

   /// Suma al vector a
   /** @param a Puntero a un vector */
   void suma(Vector *a);

   /// Resta los vectores a menos b
   /** @param a Puntero a un vector
       @param b Puntero a un vector */
   void resta(Vector *a, Vector *b);

   /// Resta el vector a
   /** @param a Puntero a un vector */
   void resta(Vector *a);

   /// Multiplica el vector por el escalar esc
   /** @param esc Valor escalar */
   void multiplica(ldouble esc);

   /// Calcula la norma infinito
   /** @return Valor del la norma infinita */
   ldouble normaInf(void);

   /// Calcula el producto punto
   /** @return Valor del producto punto */
   ldouble productoPunto(void);

   /// Calcula el producto punto
   /** @param a Puntero a un vector
       @return Valor del producto punto */
   ldouble productoPunto(Vector *a);

   /// Es el vector cero
   /** @return (1) si es el vector cero, (0)en caso contrario */
   int esVectorCero(void);

   /// Es el vector en todas sus componentes más pequeño que eps
   /** @param eps Tolerancia
       @return (1) si todas las componentes son más pequeñas que eps, (0) en caso contrario */
   int esCadaEntradaMasPequeno(double eps);

   /// Tamaño del vector (aproximado) en Kb
   /** @return Tamaño del vector en Kb */
   inline ldouble tamano(void)
   {
      ldouble t = (((long) sizeof(V) * Col) / 1024.0);
      return t;
   }

   /// Visualiza información general del vector
   inline void visualizaInformacion(void)
   {
      printf("\nVector \"%s\" de dimensión: %d \n",Nmb,Col);
   }

};

/**
Esta clase implementa los comportamientos más comunes para el trabajar con vectores de punto flotante
@example EjemploVector.cpp */

#endif
