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


#include "CtrlParametros.hpp"
#include "Man_arch.hpp"
#include <string.h>


const int MAX_LINEA = 1024;


// Inicializa el control de parametro
// @param tam Tamaño máximo del arreglo
void CtrlParametros::inicializa(int tam)
{
   int i;
   Tam = tam;
   Key = new char *[Tam];
   Val = new char *[Tam];
   for (i = 0; i < Tam; i++)
   {
      Key[i] = NULL;
      Val[i] = NULL;
   }
}

// Analiza los parametros y los separa
// @param argc Número de argumentos
// @param args Puntero a los argumentos
void CtrlParametros::analiza(int argc, const char *args[])
{
   int i, j, t;
   char cad[MAX_LINEA];


   for (i = 1; i < argc; i++)
   {
      if (args[i][0] == '-')
      {
         t = strlen(args[i]);
         strcpy(cad,args[i]);
         for (j = 1; j < t; j++) cad[j-1] = cad[j];
         cad[j-1] = 0;

         // Chaca si es lectura de un archivo
         if (strcmp(cad,"file") == 0)
         {
            if (i+1 < argc)
            {
               if (args[i+1][0] != '-')
               {
                  t = strlen(args[i+1]);
                  strcpy(cad,args[i+1]);
                  leeArchivo(cad);
                  i++;
               }
            }
         }
         else
         {
            // Almacena al pareametro y en su caso su valor
            if (i+1 < argc)
            {
               if (args[i+1][0] != '-')
               {
                  insertaRemplaza(cad,args[i+1]);
                  i++;
                  continue;
               }
            }
            insertaRemplaza(cad,"");
         }
      }
   }
}


// Analiza los parametros y los separa
// @param argc Número de argumentos
// @param args Puntero a los argumentos
void CtrlParametros::analiza(int argc, char *args[])
{
   int i, j, t;
   char cad[MAX_LINEA];


   for (i = 1; i < argc; i++)
   {
      if (args[i][0] == '-')
      {
         t = strlen(args[i]);
         strcpy(cad,args[i]);
         for (j = 1; j < t; j++) cad[j-1] = cad[j];
         cad[j-1] = 0;

         // Chaca si es lectura de un archivo
         if (strcmp(cad,"file") == 0)
         {
            if (i+1 < argc)
            {
               if (args[i+1][0] != '-')
               {
                  t = strlen(args[i+1]);
                  strcpy(cad,args[i+1]);
                  leeArchivo(cad);
                  i++;
               }
            }
         }
         else
         {
            // Almacena al pareametro y en su caso su valor
            if (i+1 < argc)
            {
               if (args[i+1][0] != '-')
               {
                  insertaRemplaza(cad,args[i+1]);
                  i++;
                  continue;
               }
            }
            insertaRemplaza(cad,"");
         }
      }
   }
}


// Lee el archivo indicado
// @param arch Archivo a leer para agregar a los parametros
void CtrlParametros::leeArchivo(const char *arch)
{
   char xcad[MAX_LINEA];
   int i;

   Manipulador_archivos *la = new Manipulador_archivos;
   if (!la)
   {
      printf("\nError al leer archivo");
      exit(1);
   }
   la->parametros(arch,LEE_ARCHIVO,MAX_LINEA);
   la->arregloInicializa(30, MAX_LINEA);

   do
   {
      la->leeLinea(xcad);
      if (la->retornaEstado()) break;
      la->eliminaEspaciosInicesarios(xcad);
      if (*xcad == '\0') continue;
      i = la->arregloSeparaElementos(xcad,' ');
      if (i >= 0) insertaRemplaza(la->arregloRetornaElemento(0),la->arregloRetornaElemento(1));
      else insertaRemplaza(la->arregloRetornaElemento(0),"");
   }
   while (!la->retornaEstado());

   delete la;
}

// Inserta una entrada
// @param k Llave a insertar o remplazar
// @param v Valor de la llave
void CtrlParametros::insertaRemplaza(const char *k, const char *v)
{
   if (*k == '\0') return;

   int i, t;
   for (i = 0; i < Tam; i++)
   {
      // Inserta
      if (Key[i] == NULL)
      {
         t = strlen(k);
         Key[i] = new char[t+1];
         strcpy(Key[i],k);

         t = strlen(v);
         Val[i] = new char[t+1];
         strcpy(Val[i],v);
         return;
      }
      // Remplaza
      if (strcmp(Key[i],k) == 0)
      {
         if (Val[i]) delete []Val[i];
         t = strlen(v);
         Val[i] = new char[t+1];
         strcpy(Val[i],v);
         return;
      }
   }
}

// Busca si esta una entrada
// @param k Llave a buscar
// @return Retorna la posición de la llave, -1 en caso de no encontrarla
int CtrlParametros::busca(const char *k)
{
   int i;

   for (i = 0; i < Tam; i++)
   {
      if (Key[i] == NULL) return -1;
      // Busca
      if (strcmp(Key[i],k) == 0) return i+1;
   }
   return -1;
}

// Visualiza el contenido
void CtrlParametros::visualiza(void)
{
   int i;
   printf("\n\nVisualiza la lista de parámetros\n");
   for (i = 0; i < Tam; i++)
   {
      if (Key[i]) printf("\n%2d) %s = %s",i+1,Key[i], Val[i]);
   }
   printf("\n");
}

// Retorna el valor entero de la clave
// @param key Llave
// @param v Valor de la llave (por omisión el valor es cero)
int CtrlParametros::intVal(const char *key, int v)
{
   int i, val = v;

   for (i = 0; i < Tam; i++)
   {
      if (Key[i] == NULL) return val;
      // Busca
      if (strcmp(Key[i],key) == 0)
      {
         val = atoi(Val[i]);
         return val;
      }
   }

   return  val;
}

// Retorna el valor ldouble de la clave
// @param key Llave
// @param v Valor de la llave (por omisión el valor es cero)
ldouble CtrlParametros::doubleVal(const char *key, ldouble v)
{
   ldouble val = v;
   int i;

   for (i = 0; i < Tam; i++)
   {
      if (Key[i] == NULL) return val;
      // Busca
      if (strcmp(Key[i],key) == 0)
      {
         val = atof(Val[i]);
         return val;
      }
   }

   return val;
}

// Retorna el valor cadena de la clave
// @param[out] v Puntero al valor
// @param key Llave
// @param val Valor de la llave (por omisión el valor es una cadena nula)
void CtrlParametros::stringVal(char *v, const char *key, const char *val)
{
   int i, t;

   for (i = 0; i < Tam; i++)
   {
      // No hay mas llaves, copia el valor por omision
      if (Key[i] == NULL)
      {
         t = strlen(val);
         v = new char [t+1];
         strcpy(v,val);
         return;
      }
      // Busca la llave
      if (strcmp(Key[i],key) == 0)
      {
         t = strlen(Val[i]);
         v = new char [t+1];
         strcpy(v,Val[i]);
         return;
      }
   }
}

