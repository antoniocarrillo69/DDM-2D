//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para generar una geometría en dos dimensiones                                 //
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



#ifndef __Geometria_2D__
#define __Geometria_2D__

#include "Geometria.hpp"


/// Clase base para generar una geometria en 2D
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Geometria_2D : public Geometria
{

public:

   /// Constructor de la clase
   Geometria_2D(void)
   {
      Dominio.redimensiona(2,2);
      Particion.redimensiona(2);
   }

   /// Inicializa la geometria
   virtual void inicializa(MatrizDensa *dm, int partx, int party) = 0;

   /// Coordenadas dentro del dominio
   /** @param x Coordenada X
       @param y Coordenada Y
       @return (1) si las coordenadas estan dentro del dominio, (0) en caso contrario  */
   int coordenadasDentroDominio(ldouble x, ldouble y)
   {
      if (x < (Dominio.retorna(0,0) - TOLERANCIA_NODO) || x > (Dominio.retorna(1,0) + TOLERANCIA_NODO) ) return 0;
      if (y < (Dominio.retorna(0,1) - TOLERANCIA_NODO) || y > (Dominio.retorna(1,1) + TOLERANCIA_NODO) ) return 0;
      return 1;
   }


   // Retorna el numero de nodo que tiene coordenadas Coor, si no pertenece -1
   /** @param x Coordenada X
       @param y Coordenada Y
       @return retorna el numero de nodo o (-1) si no es encontrado  */
   int retornaNodoCoord(ldouble x, ldouble y);


   /// Retorna las coordenadas del nodo especificado
   /** @param nd Número de nodo
       @param[out] x Coordenada X
       @param[out] y Coordenada Y */
   inline void coordenadasNodo(int nd, ldouble &x, ldouble &y)
   {
      int ix = nd % (Particion.retorna(0) +1);
      while (nd >= ((Particion.retorna(0) +1) *(Particion.retorna(1) +1))) nd -= ((Particion.retorna(0) +1) *(Particion.retorna(1) +1));
      int iy = nd / (Particion.retorna(0) +1);
      x = ND->retorna(0,ix);
      y = ND->retorna(1,iy);
   }

   //~ /// Establece las coordenadas del nodo
   //~ /** @param nodo Número de nodo
   //~ @param x Coordenada X
   //~ @param y Coordenada Y */
   //~ inline void estableceValorCoordenadas(int nodo, ldouble x, ldouble y)
   //~ {
   //~ ND->asigna(0,nodo,x);
   //~ ND->asigna(1,nodo,y);
   //~ }

   /// Regresa las coordenadas del elemento
   /** @param el Número de elemento
       @param x Puntero a las coordenada X
       @param y Puntero a las coordenada Y */
   void coordenadasElemento(int el, ldouble *x, ldouble *y);

   /// Número máximo de nodos en la frontera
   /** @return Número máximo de nodos en la frontera */
   inline int numeroMaximoNodosFrontera(void)
   {
      return (2 * Particion.retorna(0) + 2 * Particion.retorna(1));
   }

   //~ /// Retrona las coordenadas del dominio
   //~ /** @param ini Puntero a las coordenadas iniciales del dominio
   //~ @param fin Puntero a las coordenadas finales del dominio */
   //~ inline void Coordenadas_dominio(ldouble *ini, ldouble *fin)
   //~ {
   //~ ini[0] = Dominio[0][0];
   //~ ini[1] = Dominio[0][1];
   //~ fin[0] = Dominio[1][0];
   //~ fin[1] = Dominio[1][1];
   //~ }

   //~ /// Regresa los nodos externos en un arreglo ARR y numero ND
   //~ /** @param arr Puntero a un arreglo de nodos
   //~ @param nd Número de nodos */
   //~ void Regresa_Nodos_externos(int *arr, int nd);

   //~ /// Marca los nodos externos con el valor MC
   //~ /** @param mc Valor a usar de marca */
   //~ void Marca_Nodos_Externos(int mc);

   /// Retorna el numero y nodos adyacentes a un nodo dado
   /** @param nd Nodo a buscar
       @param nds Puntero a un arreglo de nodos
       @param nnds Número de nodos */
   int retornaNodosAdyacentes(int nd, int *nds, int nnds);

   /// Calcula el tipo de nodo dentro del dominio positivo es desconocido, negativo es conocido (1) Interior , (2) cara, (3) Vertice
   void calculaTipoNodo(void);

   /// Retorna el número de nodos en vertices
   /** @return Número de nodos en vertices */
   int retornaNumeroNodosVertices(void);

   /// Retorna el número de nodos en caras
   /** @return Número de nodos en caras */
   int retornaNumeroNodosCaras(void);

   /// Retorna el numero de nodo que tiene coordenadas Coor, si no se encuentra -1
   /** @param coor Cordenada a buscar */
   int retornaNodoCoord(ldouble coor);

   /// Retorna la numeración de los nodos
   int retornaNumeracionNodoFrontera(int nodo);

   /// Regresa el valor del área del elemento
   /** @return Area del elemento */
   virtual ldouble areaElemento(int el) = 0;

   /// Visualiza coordenadas del dominio
   void visualizaCoordenadasDominio(void)
   {
#ifdef __Double__
      printf("\nDominio: (%f,%f) a (%f,%f)\n\n",Dominio.retorna(0,0),Dominio.retorna(0,1),Dominio.retorna(1,0),Dominio.retorna(1,1));
#else
      printf("\nDominio: (%Lf,%Lf) a (%Lf,%Lf)\n\n",Dominio.retorna(0,0),Dominio.retorna(0,1),Dominio.retorna(1,0),Dominio.retorna(1,1));
#endif
   }

};

#endif
