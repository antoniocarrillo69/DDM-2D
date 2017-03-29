//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para leer parametros de la linea de comandos                                       //
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


#ifndef __CtrlParametros__
#define __CtrlParametros__

#include "Definiciones.hpp"


/// Clase para leer parametros de la linea de comandos
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class CtrlParametros
{
private:
   /// Puntero a las llaves
   char **Key;
   /// Puntero a los valores
   char **Val;
   /// Tamaño del arreglo
   int Tam;


   /// Inicializa el control de parametros
   /** @param tam Tamaño máximo del arreglo */
   void inicializa(int tam);

   /// Analiza los parametros y los separa
   /** @param argc Número de argumentos
       @param args Puntero a los argumentos */
   void analiza(int argc, const char *args[]);

   /// Analiza los parametros y los separa
   /** @param argc Número de argumentos
       @param args Puntero a los argumentos */
   void analiza(int argc, char *args[]);


   /// Lee el archivo indicado
   /** @param arch Archivo a leer para agregar a los parametros */
   void leeArchivo(const char *arch);


public:

   /// Constructor de la clase
   CtrlParametros(void)
   {
      inicializa(100);
   }

   /// Constructor de la clase
   /** @param argc NÃºmero de argumentos
       @param args Puntero a los argumentos */
   CtrlParametros(int argc, const char *args[])
   {
      inicializa(100);
      analiza(argc, args);
   }

   /// Constructor de la clase
   /** @param argc NÃºmero de argumentos
       @param args Puntero a los argumentos */
   CtrlParametros(int argc, char *args[])
   {
      inicializa(100);
      analiza(argc, args);
   }

   /// Destructor de la clase
   ~CtrlParametros(void)
   {
      int i;
      for (i = 0; i < Tam; i++)
      {
         delete []Key[i];
         delete []Val[i];
      }
      delete []Key;
      delete []Val;
   }

   /// Inserta una entrada
   /** @param k Llave a insertar o remplazar
       @param v Valor de la llave */
   void insertaRemplaza(const char *k, const char *v);

   /// Busca si esta una entrada
   /** @param k Llave a buscar
       @return Retorna la posición de la llave, -1 en caso de no encontrarla */
   int busca(const char *k);

   /// Visualiza el contenido
   void visualiza(void);

   /// Retorna el valor entero de la clave
   /** @param key Llave
       @param v Valor de la llave (por omisión el valor es cero) */
   int intVal(const char *key, int v = 0);

   /// Retorna el valor ldouble de la clave
   /** @param key Llave
       @param v Valor de la llave (por omisiÃ³n el valor es cero) */
   ldouble doubleVal(const char *key, ldouble v = 0.0);

   /// Retorna el valor cadena de la clave
   /** @param[out] v Puntero al valor
       @param key Llave
       @param val Valor de la llave (por omisión el valor es una cadena nula) */
   void stringVal(char *v, const char *key, const char *val = "");


};

/**
Esta clase implementa los componentes para leer parametros de la linea de comandos
@example EjemploCtrlParametros.cpp */

#endif
