//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para generar una geometria                                                    //
// Revisión: 1 de Junio del 2006                                                            //
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


#ifndef __Geometria__
#define __Geometria__


// Tolerancia para saber si dos nodos son iguales
#define   TOLERANCIA_NODO 1e-14


// Tipo de nodo
#define CONOCIDO     -1
#define DESCONOCIDO  0

#include "Definiciones.hpp"
#include "MatrizTamanoVariable.hpp"
#include "MatrizDensa.hpp"
#include "MatrizInt.hpp"
#include "VectorInt.hpp"
#include <stdlib.h>



/// Clase base para generar una geometria
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Geometria
{

protected:

   /// Dominio de la geometria
   MatrizDensa Dominio;

   /// Particion del dominio
   VectorInt Particion;

   /// Puntero a una MatrizInt que contiene a los nodos de los elementos
   MatrizInt *EL;

   MatrizTamanoVariable *ND;

   /// Puntero a un VectorInt que contiene a la numeracion de nodos
   VectorInt *NN;

   /// Puntero a un VectorInt que contiene el tipo de nodo
   VectorInt *TN;

   /// Puntero a una MatrizInt que contiene a los elementos que contienen al nodo
   MatrizInt *EE;

   /// Numero de nodos
   int N_N;

   /// Numero de elementos
   int N_E;

   /// Dimension a trabajar
   int DIM;

   /// Numero de nodos por elemento
   int NNE;

   /// Numero máximo de elementos que son soporte de un nodo
   int NMESN;


public:

   /// Constructor de la clase
   Geometria(void)
   {
      EL = NULL;
      ND = NULL;
      NN = NULL;
      TN = NULL;
      EE = NULL;
   }

   /// Destructor de la clase
   ~Geometria()
   {
      delete EL;
      delete ND;
      delete NN;
      delete TN;
      delete EE;
   }

   /// Genera la geometria
   virtual void generaGeometria(void) = 0;

   /// Retorna partición del dominio
   /** @return Partición del dominio */
   inline int retornaParticion(int i)
   {
      return Particion[i];
   }

   /// Regresa el número de nodos en el dominio
   /** @return Número de nodos en el dominio */
   inline int retornaNumeroNodos(void)
   {
      return N_N;
   }

   /// Retorna el numero de elementos en el dominio
   /** @return Número de elementos en el dominio */
   inline int retornaNumeroElementos(void)
   {
      return N_E;
   }

   /// Retorna el número de nodos por elemento
   /** @return Número de nodos por elemento */
   inline int retornaNodosElemento(void)
   {
      return NNE;
   }

   /// Retorna la dimensión de la geometría
   /** @return La dimensión de la geometría */
   inline int retornaDimension(void)
   {
      return DIM;
   }

   /// Retorna la coordenada especificada del nodo
   /** @param nodo Número de nodo
       @param Xi Número de coordenada solicitada
       @return Coordenada especificada */
   inline ldouble retornaValorNodo(int nodo, int Xi)
   {

      if (Xi == 0)       // Coordenada X
      {
         int ix = nodo % (Particion.retorna(0) +1);
         return ND->retorna(Xi,ix);
      }
      else if (Xi == 1)  // Coordenada Y
      {
         while (nodo >= ((Particion.retorna(0) +1) *(Particion.retorna(1) +1))) nodo -= ((Particion.retorna(0) +1) *(Particion.retorna(1) +1));
         int iy = nodo / (Particion.retorna(0) +1);
         return ND->retorna(Xi,iy);
      }
      // Coordenada Z
      int iz = nodo / ((Particion.retorna(0) +1) *(Particion.retorna(1) +1));
      return ND->retorna(Xi,iz);
   }

   /// Retorna la coordenada especificada del nodo
   /** @param nodo Número de nodo
       @param[out] coord Puntero a coordenada */
   inline void retornaValorNodo(int nodo, ldouble *coord)
   {
      for (int i = 0; i < DIM; i++)
      {
         coord[i] = retornaValorNodo(nodo, i);
      }
   }

   //~ /// Establece el valor de la coordenada especificada del nodo
   //~ /** @param nodo Número de nodo
   //~ @param xi Número de coordenada a cambiar
   //~ @param val Valor de la coordenada*/
   //~ inline void estableceValorNodo(int nodo, int xi, ldouble val)
   //~ { ND->asigna(xi,nodo,val); }

   /// Retorna el número de nodo del elemento
   /** @param elemento Número de elemento
       @param nodo Número de nodo dentro del elemento
       @return Número de nodo */
   inline int retornaNumeroNodo(int elemento, int nodo)
   {
      return EL->retorna(elemento,nodo);
   }

   /// Retorna el número de elementos en el soporte de un nodos
   /** @return Número de elementos en el soporte de un nodos */
   inline int numeroElementosSoporteNodo(void)
   {
      return NMESN;
   }

   /// Inicializa la numeración de nodos
   inline void inicializaNumeracionNodos(void)
   {
      NN->inicializa(0);
   }

   /// Retorna la numeracion de los nodos
   /** @return (-1) conocido en caras (-2) conocido en vertices (>=0) desconocido */
   inline int retornaNumeracionNodo(int nodo)
   {
      return NN->retorna(nodo);
   }

   /// Establece la numeracion de los nodos
   /** @param nodo Número de nodo
       @param n Número*/
   inline void estableceNumeroNodo(int nodo, int n)
   {
      NN->asigna(nodo,n);
   }

   /// Visualiza a los elementos que contienen al nodo ND
   /** @param nd Número de nodo */
   void visualizaElementosContienenNodo(int nd);

   /// Regresa un arreglo EL de los elementos que contienen al nodo ND
   /** @param nd Número de nodos
       @param[out] el Puntero a un arreglo
       @param nel Tamaño máximo del arreglo
       @return Número de elementos que contienen al nodo */
   int retornaElementosContienenNodo(int nd, int *el, int nel);

   /// Visualiza a los nodos del elemento NE
   /** @param ne Número del elemento */
   void visualizaNodosElemento(int ne);

   /// Regresa el numero de nodos desconocidos
   /** @return Número de nodos desconocidos */
   int retornaNumeroNodosDesconocidos(void);

   /// Numera nodos, (< 0) conocido, (>=0) desconocido
   void numeraNodos(void);

   /// Retorna en un arreglo los nodos conocidos asi como su numero
   /** @param nds Puntero a un arreglo para los nodos
       @param[out] nnds Tamaño máximo del arreglo
       @return Número de nodos conocidos */
   int retornaNodosConocidos(int *nds, int nnds);

   /// Retorna el numero de nodos conocidos
   /** @return Número de nodos conocidos */
   int retornaNumeroNodosConocidos(void);

   /// Regresa en el arreglo ARR de tamaño NARR los nodos que satisfacen la condicion de tener el valor VAL en la componente IND
   /** @param val Valor a buscar
       @param ind Indice de coordenadas
       @param[out] arr Puntero a un arreglo
       @param narr Tamaño máximo del arreglo
       @return Número de nodos que satisfacen la condición estipulada */
   int regresaNodosSatisfagan(ldouble val, int ind, int *arr, int narr);

   /// Marca con el valor MC a los nodos que satisfacen la condicion de tener el valor VAL en la componente IND
   /** @param val Valor a buscar
       @param ind Indice de coordenadas
       @param mc Marca */
   void marcaNodosSatisfagan(ldouble val, int ind, int mc);

   /// Regresa en el arreglo ARR de tamaño NARR los nodos que satisfacen la condicion de tener el valor VAL en la componente IND excepto aquellos que en la componente IND1 tienen los valores EXC1 y EXC2
   /** @param val Valor a buscar
       @param ind Indice de coordenadas
       @param[out] arr Puntero al arreglo
       @param narr Tamaño máximo del arreglo
       @param ind1 Indice de coordenadas a excluir
       @param exc1 Primer valor a excluir
       @param exc2 Segundo valor a excluir
       @return Número de elementos que satisfacen la condición */
   int regresaNodosSatisfagan(ldouble val, int ind, int *arr, int narr, int ind1, ldouble exc1, ldouble exc2);

   /// Marca con el valor MC a los nodos que satisfacen la condicion de tener el valor VAL en la componente IND excepto aquellos que en la componente IND1 tienen los valores EXC1 y EXC2
   /** @param val Valor a buscar
       @param ind Indice de coordenadas
       @param mc Marca
       @param ind1 Indice de coordenadas a excluir
       @param exc1 Primer valor a excluir
       @param exc2 Segundo valor a excluir */
   void marcaNodosSatisfagan(ldouble val, int ind, int mc, int ind1, ldouble exc1, ldouble exc2);

   /// Marca el nodo nd con el valor mc
   /** @param nd Número de nodo
       @param mc Marca */
   inline void marcaNodo(int nd, int mc)
   {
      estableceNumeroNodo(nd, mc);
      numeraNodos();
   }

   /// Regresa un arreglo ND de los nodos del elemento NE
   /** @param ne Número de elemento
       @param[out] nd Puntero a un arreglo
       @param nnd Tamaño máximo del arreglo */
   void retornaNodosElemento(int ne, int *nd, int nnd)
   {
      EL->retorna(ne-1,nd,NNE);
      for (int i = NNE; i < nnd; i++) nd[i] = -1;
   }

   /// Aviso de error al solicitar memoria
   /** @param cad Cadena con una explicación del error */
   inline void errorSolicitudMemoria(const char *cad)
   {
      printf("\nError falta de memoria en: %s\n",cad);
      exit(1);
   }

   /// Retrona las coordenadas del dominio
   /** @return Coordenadas del dominio */
   MatrizDensa coordenadasDominio(void)
   {
      return Dominio;
   }

   /// Retorna el tipo de nodo dentro del dominio positivo es desconocido, negativo es conocido, (1) Interior , (2) cara, (3) Vertice
   /** @param nd Número de nodo
       @return Positivo es desconocido, negativo es conocido, (1) Interior , (2) cara, (3) Vertice */
   inline int retornaTipoNodo(int nd)
   {
      return TN->retorna(nd);
   }

   /// Visualiza el tipo de nodo dentro del dominio positivo es desconocido, negativo es conocido, (1) Interior, (2) cara, (3) Vertice
   inline void visualizaTipoNodos(void)
   {
      TN->visualiza();
   }


   /// Genera arreglo de soporte de cada nodo
   void generaSoporteNodos(void);

   /// Visualiza el soporte de cada nodo
   void visualizaSoporteNodos(void)
   {
      EE->visualiza();
   }

   /// Libera arreglo de soporte de cada nodo
   inline void liberaSoporteNodos(void)
   {
      delete EE;
      EE = NULL;
   }

   /// Visualiza coordenadas del dominio
   virtual void visualizaCoordenadasDominio(void) = 0;

   /// Visualiza los nodos de los elementos
   void visualizaElementos(void);

   /// Visualiza las coordenadas de los nodos
   void visualizaNodos(void);


   /// Graba la geometria a un archivo
   /** @param arch Puntero al nombre del archivo */
   void grabaGeometria(const char *arch)
   {}

   /// Lee la geometria a un archivo
   /** @param arch Puntero al nombre del archivo */
   void leeGeometria(const char *arch)
   {}


   void visualiza(void)
   {
      visualizaCoordenadasDominio();
      visualizaElementos();
      visualizaNodos();
   }
};

#endif



//~ /// Establece el numero de nodo del elemento
//~ inline void establece_Numero_nodo(int elemento, int nodo, int nd)
//~ {
//~ EL->asigna(elemento,nodo,nd);
//~ }

