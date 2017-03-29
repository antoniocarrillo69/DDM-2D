//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para generar una geometría                                                    //
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

#include "Geometria.hpp"
#include "Man_arch.hpp"
#include <math.h>
#include <string.h>
#include <set>
#include <map>

using namespace std;

#define MAX_LINEA 1024

/// Regresa true si un elemento es menor que otro, usada para la clase map
struct classcomp
{

   bool operator() (const int x, const int y) const
   {
      if (x < y) return true;
      return false;
   }
};


// Visualiza a los elementos que contienen al nodo ND
// @param nd Número de nodo
void Geometria::visualizaElementosContienenNodo(int nd)
{
   int i, k;
   for (i = 0; i < N_E; i++ )
   {
      for (k = 0; k < NNE; k++)
      {
         if (retornaNumeroNodo(i,k) == nd)
         {
            printf("Elemento: %d\n",i+1);
            break;
         }
      }
   }
}


// Regresa un arreglo EL de los elementos que contienen al nodo ND
// @param nd Número de nodos
// @param[out] el Puntero a un arreglo
// @param nel Tamaño máximo del arreglo
// @return Número de elementos que contienen al nodo
int Geometria::retornaElementosContienenNodo(int nd, int *el, int nel)
{
   if (EE == NULL) generaSoporteNodos();

   int i;
   EE->retorna(nd,el,NMESN);
   for (i = NMESN; i < nel; i++) el[i] = -1;
   for (i = 0; i <NMESN; i++)
   {
      if (el[i] == -1) break;
   }

   return i;
}

// Visualiza a los nodos del elemento NE
// @param ne Número del elemento
void Geometria::visualizaNodosElemento(int ne)
{
   int i;
   printf("Elemento: %#3d\n",ne);
   for (i = 0; i < NNE; i++) printf("%#3d\n",retornaNumeroNodo(ne-1,i));
}


// Regresa el numero de nodos desconocidos
// @return Número de nodos desconocidos
int Geometria::retornaNumeroNodosDesconocidos(void)
{
   int i, j = 0;
   for (i = 0; i <  N_N; i++)
   {
      if ( retornaNumeracionNodo(i) >= 0) j++;
   }
   return j;
}


// Numera nodos, (< 0) conocido, (>=0) desconocido
void Geometria::numeraNodos(void)
{
   int i, j = 0;

   for (i = 0; i <  N_N; i++)
   {
      if ( retornaNumeracionNodo(i) >= 0)
      {
         estableceNumeroNodo(i,j);
         j++;
      }
   }
}



// Retorna en un arreglo los nodos conocidos asi como su numero
// @param nds Puntero a un arreglo para los nodos
// @param[out] nnds Tamaño máximo del arreglo
// @return Número de nodos conocidos
int Geometria::retornaNodosConocidos(int *nds, int nnds)
{
   int i, j = 0;
   for (i = 0; i <  N_N; i++)
   {
      if ( retornaNumeracionNodo(i) < 0)
      {
         nds[j] = i;
         j++;
      }
#ifdef DEPURAR
      if (i >= nnds)
      {
         printf("Error desbordamiento del arreglo\n");
         exit(1);
      }
#endif
   }
   return j;
}


// Retorna el numero de nodos conocidos
// @return Número de nodos conocidos
int Geometria::retornaNumeroNodosConocidos(void)
{
   int i, j = 0;
   for (i = 0; i <  N_N; i++)
   {
      if ( retornaNumeracionNodo(i) < 0) j++;
   }
   return j;
}


// Regresa en el arreglo ARR de tamaño NARR los nodos que satisfacen la condicion de tener el valor VAL en la componente IND
// @param val Valor a buscar
// @param ind Indice de coordenadas
// @param[out] arr Puntero a un arreglo
// @param narr Tamaño máximo del arreglo
// @return Número de nodos que satisfacen la condición estipulada
int Geometria::regresaNodosSatisfagan(ldouble val, int ind, int *arr, int narr)
{
   int i, j = 0;
   ldouble tmp;
   for (i = 0; i <  N_N; i++)
   {
      tmp = retornaValorNodo(i, ind);
#ifdef __Double__
      if (fabs(tmp - val) < TOLERANCIA_NODO)
      {
#else
      if (fabsl(tmp - val) < TOLERANCIA_NODO)
      {
#endif
         arr[j] = i;
         j++;
#ifdef DEPURAR
         if (j > narr)
         {
            printf("Error desbordamiento del arreglo\n");
            break;
         }
#endif
      }
   }
   return j;
}


// Marca con el valor MC a los nodos que satisfacen la condicion de tener el valor VAL en la componente IND
// @param val Valor a buscar
// @param ind Indice de coordenadas
// @param mc Marca
void Geometria::marcaNodosSatisfagan(ldouble val, int ind, int mc)
{
   int i;
   ldouble tmp;
   for (i = 0; i <  N_N; i++)
   {
      tmp = retornaValorNodo(i, ind);
#ifdef __Double__
      if ( fabs(tmp - val) < TOLERANCIA_NODO) estableceNumeroNodo(i, mc);
#else
      if ( fabsl(tmp - val) < TOLERANCIA_NODO) estableceNumeroNodo(i, mc);
#endif
   }
   // Actualiza numeracion de nodos
   numeraNodos();
}


// Regresa en el arreglo ARR de tamaño NARR los nodos que satisfacen la condicion de tener el valor VAL en la componente IND excepto aquellos que en la componente IND1 tienen los valores EXC1 y EXC2
// @param val Valor a buscar
// @param ind Indice de coordenadas
// @param arr Puntero al arreglo
// @param narr Tamaño máximo del arreglo
// @param ind1 Indice de coordenadas a excluir
// @param exc1 Primer valor a excluir
// @param exc2 Segundo valor a excluir
// @return Número de elementos que satisfacen la condición
int Geometria::regresaNodosSatisfagan(ldouble val, int ind, int *arr, int narr, int ind1, ldouble exc1, ldouble exc2)
{
   int i, j = 0;
   ldouble tmp;
   for (i = 0; i <  N_N; i++)
   {
      tmp = retornaValorNodo(i, ind);
#ifdef __Double__
      if (fabs(tmp - val) < TOLERANCIA_NODO)
      {
#else
      if (fabsl(tmp - val) < TOLERANCIA_NODO)
      {
#endif
         tmp = retornaValorNodo(i, ind1);
#ifdef __Double__
         if (fabs(tmp - exc1) < TOLERANCIA_NODO) continue;
         if (fabs(tmp - exc2) < TOLERANCIA_NODO) continue;
#else
         if (fabsl(tmp - exc1) < TOLERANCIA_NODO) continue;
         if (fabsl(tmp - exc2) < TOLERANCIA_NODO) continue;
#endif
         arr[j] = i;
         j++;
         if (j > narr)
         {
            printf("Error desbordamiento del arreglo\n");
            break;
         }
      }
   }
   return j;
}

// Marca con el valor MC a los nodos que satisfacen la condicion de tener el valor VAL en la componente IND excepto aquellos que en la componente IND1 tienen los valores EXC1 y EXC2
// @param val Valor a buscar
// @param ind Indice de coordenadas
// @param mc Marca
// @param ind1 Indice de coordenadas a excluir
// @param exc1 Primer valor a excluir
// @param exc2 Segundo valor a excluir
void Geometria::marcaNodosSatisfagan(ldouble val, int ind, int mc, int ind1, ldouble exc1, ldouble exc2)
{
   int i;
   ldouble tmp;
   for (i = 0; i <  N_N; i++)
   {
      tmp = retornaValorNodo(i, ind);
#ifdef __Double__
      if ( fabs(tmp - val) < TOLERANCIA_NODO)
#else
      if ( fabsl(tmp - val) < TOLERANCIA_NODO)
#endif
      {
         tmp = retornaValorNodo(i, ind1);
#ifdef __Double__
         if (fabs(tmp - exc1) < TOLERANCIA_NODO) continue;
         if (fabs(tmp - exc2) < TOLERANCIA_NODO) continue;
#else
         if (fabsl(tmp - exc1) < TOLERANCIA_NODO) continue;
         if (fabsl(tmp - exc2) < TOLERANCIA_NODO) continue;
#endif
         estableceNumeroNodo(i, mc);
      }
   }
   // Actualiza numeracion de nodos
   numeraNodos();
}


// Genera arreglo de soporte de cada nodo
void Geometria::generaSoporteNodos(void)
{
   if (EE == NULL)
   {
      // Solicita la memoria necesaria
      EE = new MatrizInt(N_N,NMESN,"Soporte de cada nodo", -1);
      if (!EE) errorSolicitudMemoria("Generacion de soporte");

      int in, jn, k;
      typedef set<int> Conjunto;
      typedef multimap<int, Conjunto *,classcomp> ListMultiMap;

      // Lista de contenedores
      ListMultiMap ltest;
      for (in = 0; in < N_N; in++)
      {
         Conjunto *s = new Conjunto;
         ltest.insert(ListMultiMap::value_type(in,s));
//#error hay que liberar la ram solicitada por s
         //~ Conjunto  s;
         //~ ltest.insert(ListMultiMap::value_type(in,&s));
      }

      // Almacena el soporte
      ListMultiMap::iterator j;
      for (in = 0; in < N_E; in++ )
      {
         for (jn = 0; jn < NNE; jn++)
         {
            // Busca en el contenedor
            j=ltest.find(EL->retorna(in,jn));
            // Si lo encuentra agrega el soporte
            if (j != ltest.end()) (*j).second->insert(in + 1);
#ifdef DEPURAR
            else
            {
               printf("Error al generar el soporte");
               exit(1);
            }
#endif
         }
      }

      // Recupera soporte y lo guarda en la matriz
      Conjunto::iterator it;
      for (in = 0; in < N_N; in++ )
      {
         j=ltest.find(in);
         if (j != ltest.end())
         {
            k = 0;
            for ( it=(*j).second->begin() ; it != (*j).second->end(); it++ )
            {
               EE->asigna(in,k,(*it));
               k++;
            }
#ifdef DEPURAR
         }
         else
         {
            printf("Error al generar el soporte");
            exit(1);
#endif
         }
         // Libera la memoria solicitada
         Conjunto *s = (*j).second;
         delete s;
      }
   }
}



// Visualiza los nodos de los elementos
void Geometria::visualizaElementos(void)
{
   int i, j;
   printf("\nNodos de los elementos\n\n");
   for (i = 0; i < N_E; i++ )
   {
      printf("Elemento %#3d ---> Nodos ( ",i+1);
      for (j = 0; j < NNE-1; j++)
      {
         printf("%#3d,",EL->retorna(i,j));
      }
      printf("%#3d )\n",EL->retorna(i,NNE-1));
   }
   printf("\n");
}


// Visualiza las coordenadas de los nodos
void Geometria::visualizaNodos(void)
{
   int i, j;
   Ctrl_visualizacion cv;

   printf("Nodos\n\n");
   for (i = 0; i < N_N; i++ )
   {
      printf("Nodo: %#3d ( %#3d ) ---> Nodo: (",i,NN->retorna(i));
      for (j = 0; j < DIM-1; j++)
      {
         cv.visualiza_e(retornaValorNodo(i,j));
         printf(", ");
      }
      cv.visualiza_e(retornaValorNodo(i,j));
      printf(" )\n");
   }
   printf("\n");
}




/*
// Graba la geometria a un archivo
// @param arch Nombre del archivo
void Geometria::grabaGeometria(const char *arch)
{
   int i, j;
   size_t ii, jj;
   char xcad[MAX_LINEA], tmp[MAX_LINEA];


   Manipulador_archivos *la = new Manipulador_archivos;
   if (!la) errorSolicitudMemoria("Grabar archivo");
   la->parametros(arch,GRABA_ARCHIVO,MAX_LINEA);


   // Dimension 2D
   sprintf(xcad,"%d",DIM);
   la->grabaLinea(xcad);
   // Numero de nodos por elemento
   sprintf(xcad,"%d",NNE);
   la->grabaLinea(xcad);
   // Numero de elementos
   sprintf(xcad,"%d",N_E);
   la->grabaLinea(xcad);
   // Numero de nodos
   sprintf(xcad,"%d",N_N);
   la->grabaLinea(xcad);

   // Dominio
   strcpy(xcad,"");
   for(ii = 0; ii < Dominio.renglones(); ii++)
   {
      for (jj = 0; jj < Dominio.columnas(); jj++)
      {
#ifdef __Double__
         sprintf(tmp,"%1.15le ",Dominio.retorna(ii,jj));
#else
         sprintf(tmp,"%1.15Le ",Dominio.retorna(ii,jj));
#endif
         strcat(xcad,tmp);
      }
   }
   la->grabaLinea(xcad);

   // Particion
   strcpy(xcad,"");
   for(ii = 0; ii < Particion.columnas(); ii++)
   {
      sprintf(tmp,"%d ",Particion.retorna(ii));
      strcat(xcad,tmp);
   }
   la->grabaLinea(xcad);


   // Elementos
   for (i = 0; i < N_E; i ++)
   {
      strcpy(xcad,"");
      for (j = 0; j < NNE; j ++)
      {
         sprintf(tmp,"%d ",EL->retorna(i,j));
         strcat(xcad,tmp);
      }
      la->grabaLinea(xcad);
   }


   // Coordenada de nodo y su tipo
   for (i = 0; i < N_N; i ++)
   {
      strcpy(xcad,"");
      for (j = 0; j < DIM; j ++)
      {
#ifdef __Double__
         sprintf(tmp,"%1.16le ",ND->retorna(i,j));
#else
         sprintf(tmp,"%1.16Le ",ND->retorna(i,j));
#endif
         strcat(xcad,tmp);
      }
      sprintf(tmp,"%d ",(int) NN->retorna(i));
      strcat(xcad,tmp);
      la->grabaLinea(xcad);
   }

   delete la;
}


// Lee la geometria a un archivo
// @param arch Nombre del archivo
void Geometria::leeGeometria(const char *arch)
{
   int i, j, n;
   size_t ii, jj;
   char xcad[MAX_LINEA], *endp;

   Manipulador_archivos *la = new Manipulador_archivos;
   if (!la) errorSolicitudMemoria("Leer archivo");
   la->parametros(arch,LEE_ARCHIVO,MAX_LINEA);

   // Dimension
   la->leeLinea(xcad);
   n  = atoi(xcad);
   if (DIM != n)
   {
      printf("Error, el archivo no corresponde con la geometria solicitada");
      exit(1);
   }

   // Numero de nodos por elemento
   la->leeLinea(xcad);
   n = atoi(xcad);
   if (NNE != n)
   {
      printf("Error, el archivo no corresponde con la geometria solicitada");
      exit(1);
   }

   // Numero de elementos
   la->leeLinea(xcad);
   N_E = atoi(xcad);


   // Numero de nodos
   la->leeLinea(xcad);
   N_N = atoi(xcad);


   EL = new MatrizInt(N_E,NNE,"Nodos que conforman a los elementos",-1);
   if (!EL) errorSolicitudMemoria("Elementos Geometria");
   ND = new MatrizDensa(N_N,DIM,"Coordenadas de Nodos");
   if (!ND) errorSolicitudMemoria("Coordenadas Geometria");
   NN = new VectorInt(N_N,"Numeracion de nodos");
   if (!NN) errorSolicitudMemoria("Nodos Geometria");


   // Dimensiones de la geometria
   la->arregloInicializa(10, MAX_LINEA);
   la->leeLinea(xcad);
   if (la->retornaEstado()) exit(1); // Error en la lectura del archivo
   la->eliminaEspaciosInicesarios(xcad);
   la->arregloSeparaElementos(xcad,' ');
   for(ii = 0; ii < Dominio.renglones(); ii++)
   {
      for (jj = 0; jj < Dominio.columnas(); jj++)
      {
         Dominio.asigna(ii,jj,strtod(la->arregloRetornaElemento(jj), &endp));
      }
   }


   // Partición
   la->leeLinea(xcad);
   if (la->retornaEstado()) exit(1); // Error en la lectura del archivo
   la->eliminaEspaciosInicesarios(xcad);
   la->arregloSeparaElementos(xcad,' ');
   for (ii = 0; ii < Particion.columnas(); ii++)
   {
      Particion.asigna(ii,atoi(la->arregloRetornaElemento(ii)));
   }


   // Lee los elementos
   for (i = 0; i < N_E; i ++)
   {
      la->leeLinea(xcad);
      if (la->retornaEstado()) exit(1); // Error en la lectura del archivo
      la->eliminaEspaciosInicesarios(xcad);
      la->arregloSeparaElementos(xcad,' ');
      for (j = 0; j < NNE; j ++)
      {
         EL->asigna(i,j,atoi(la->arregloRetornaElemento(j)));
      }
   }


   // Lee nodos
   for (i = 0; i < N_N; i ++)
   {
      la->leeLinea(xcad);
      if (la->retornaEstado()) exit(1); // Error en la lectura del archivo
      la->eliminaEspaciosInicesarios(xcad);
      la->arregloSeparaElementos(xcad,' ');
      for (j = 0; j < DIM; j ++)
      {
         ND->asigna(i,j, strtod(la->arregloRetornaElemento(j), &endp));
      }
      NN->asigna(i, atoi(la->arregloRetornaElemento(j)));
   }
   delete la;
}


*/



// Definicion de la estructura para leer una geometria desde un archivo
/*

2                           // Diensión (2D)
4                           // Número de nodos por elementos
2                           // Número de elementos
6                           // Número de nodos
-1.0 -1.0 1.0 1.0           // Dimensiones
1 2                         // Partición horizontal y vertical
0 1 2 3                     // Elementos (en sentido contrario a las manecillas del relog)
3 2 4 5
-1.0 -1.0 0.0 -1            // Nodos x y tipo_nodo
 1.0 -1.0 0.0 -1
 1.0 -0.5 0.0 -1
-1.0 -0.5 0.0 -1
 1.0  1.0 0.0 -1
-1.0  1.0 0.0 -1



*/





