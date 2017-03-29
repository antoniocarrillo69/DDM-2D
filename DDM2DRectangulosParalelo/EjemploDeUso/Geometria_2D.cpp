//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para generar una geometría en dos dimensiones                                 //
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


#include <math.h>
#include "Geometria_2D.hpp"
#include "Ctrl_vis.hpp"


// Retorna el numero de nodo que tiene coordenadas Coor, si no pertenece -1
// @param x Coordenada X
// @param y Coordenada Y
// @return retorna el numero de nodo o (-1) si no es encontrado
int Geometria_2D::retornaNodoCoord(ldouble x, ldouble y)
{
   int i;
   ldouble x1, y1;

#ifdef DEPURAR
   // Revisa que el nodo solicitado este en el dominio
   if (!coordenadasDentroDominio(x,y)) return -1;
#endif

   for (i = 0; i <  N_N; i++)
   {
      coordenadasNodo(i, x1, y1);
#ifdef __Double__
      if ( fabs(x1 - x) < TOLERANCIA_NODO && fabs(y1 - y) < TOLERANCIA_NODO) return i;
#else
      if ( fabsl(x1 - x) < TOLERANCIA_NODO && fabsl(y1 - y) < TOLERANCIA_NODO) return i;
#endif
   }
   // Nodo no encontrado
   return -1;
}


// Regresa las coordenadas del elemento
// @param el Número de elemento
// @param x Puntero a las coordenada X
// @param y Puntero a las coordenada Y
void Geometria_2D::coordenadasElemento(int el, ldouble *x, ldouble *y)
{
   int i, nd;
   for (i = 0; i < NNE; i++)
   {
      nd = EL->retorna(el-1,i);

      int ix = nd % (Particion.retorna(0) +1);
      while (nd >= ((Particion.retorna(0) +1) *(Particion.retorna(1) +1))) nd -= ((Particion.retorna(0) +1) *(Particion.retorna(1) +1));
      int iy = nd / (Particion.retorna(0) +1);
      x[i] = ND->retorna(0,ix);
      y[i] = ND->retorna(1,iy);
   }
}


// Retorna el numero y nodos adyacentes a un nodo dado
// @param nd Nodo a buscar
// @param nds Puntero a un arreglo de nodos
// @param nnds Número de nodos
int Geometria_2D::retornaNodosAdyacentes(int nd, int *nds, int nnds)
{
   int i, j, k, l, num;
   int nds_el[10];
   int el[10];

//#error usar STL para almacenar los valores (SET)  y ponerla en geometria no en 2D


   // Busca todos los elemento que contienen al nodo buscado
   num = retornaElementosContienenNodo(nd,el,6);
   k = 0;
   // Obtiene los nodos de cada elemento que contienen al nodo dado
   for (i = 0; i < num; i++)
   {
      retornaNodosElemento(el[i],nds_el,7);
      for (j = 0; j < NNE; j++)
      {
         // Almacena los nodos adyacentes evitando la duplicacion
         if (k == 0)
         {
            nds[k] = nds_el[j];
            k++;
         }
         else
         {
            for (l = 0; l < k; l++)
            {
               if (nds[l] == nds_el[j]) break;
            }
            if (l != k) continue;
            nds[k] = nds_el[j];
            k++;
         }
         if (k >= nnds) break;
      }
   }
   return k;
}


// Calcula el tipo de nodo dentro del dominio positivo es desconocido, negativo es conocido (1) Interior , (2) cara, (3) Vertice
void Geometria_2D::calculaTipoNodo(void)
{
   int st, i, sg = 0;
   ldouble x, y;//,ini[3], fin[3];
#ifdef DEPURAR
   if (!TN)
   {
      printf("\nNo ha sido inicializado el arreglo para mantener al tipo de nodo\n");
      exit(1);
   }
#endif
   for (i = 0; i <  N_N; i++)
   {
      if ( retornaNumeracionNodo(i) >= 0) sg = 1;
      else sg = -1;

      coordenadasNodo(i,x,y);
      st = 0;

#ifdef __Double__
      if (fabs(Dominio.retorna(0,0) - x) < TOLERANCIA_NODO) st ++;
      if (fabs(Dominio.retorna(0,1) - y) < TOLERANCIA_NODO) st ++;
      if (fabs(Dominio.retorna(1,0) - x) < TOLERANCIA_NODO) st ++;
      if (fabs(Dominio.retorna(1,1) - y) < TOLERANCIA_NODO) st ++;
#else
      if (fabsl(Dominio.retorna(0,0) - x) < TOLERANCIA_NODO) st ++;
      if (fabsl(Dominio.retorna(0,1) - y) < TOLERANCIA_NODO) st ++;
      if (fabsl(Dominio.retorna(1,0) - x) < TOLERANCIA_NODO) st ++;
      if (fabsl(Dominio.retorna(1,1) - y) < TOLERANCIA_NODO) st ++;
#endif
      switch (st)
      {
      case 1:  // Nodo en una cara
         TN->asigna(i,2*sg);
         break;
      case 2:  // Nodo en un vertice
         TN->asigna(i,3*sg);
         break;
      default: // Nodo interior
         TN->asigna(i,1*sg);
      }
   }
}


// Retorna el número de nodos en vertices
// @return Número de nodos en vertices
int Geometria_2D::retornaNumeroNodosVertices(void)
{
   int i, j = 0;
   for (i = 0; i <  N_N; i++)
   {
      if ( retornaNumeracionNodo(i) < 0)
      {
         // Es vertice
         if (TN->retorna(i) == -3) j++;
      }
   }
   return j;
}

// Retorna el número de nodos en caras
// @return Número de nodos en caras
int Geometria_2D::retornaNumeroNodosCaras(void)
{
   int i, j = 0;
   for (i = 0; i <  N_N; i++)
   {
      if ( retornaNumeracionNodo(i) < 0)
      {
         // Es cara
         if (TN->retorna(i) != -3) j++;
      }
   }
   return j;
}




// Retorna la numeracion de los nodos
int Geometria_2D::retornaNumeracionNodoFrontera(int nodo)
{
   int i, j = 0;
   for (i = 0; i <  N_N; i++)
   {
      if ( retornaNumeracionNodo(i) < 0)
      {
         if (j == nodo) return i;
         j++;
      }
   }
   printf("Nodo Frontera %d no encontrado\n",nodo);
   return -1;
}



//~ // Regresa los nodos externos en un arreglo ARR y numero ND
//~ void Geometria_2D::Regresa_Nodos_externos(int *arr, int nd)
//~ {
//~ int i, j = 0;
//~ for (i = 0; i <=  PH; i++) arr[j] = i, j++;
//~ for (i = (PH+1); i < (N_N-PH);i++)
//~ {
//~ if ( (i % (PH + 1)) == 0  || ((i+1) % (PH + 1)) == 0 )
//~ {
//~ //////////////////
//~ // Quitar los repetidos
//~ arr[j] = i;
//~ j++;
//~ //////////////////
//~ }
//~ }
//~ for (i = (N_N-PH); i < N_N;i++) arr[j] = i, j++;
//~ nd = j;
//~ }


//~ // Marca los nodos externos con el valor MC
//~ void Geometria_2D::Marca_Nodos_Externos(int mc)
//~ {
//~ int i;
//~ for (i = 0; i <=  PH; i++) Establece_Numero_Nodo(i,mc);
//~ for (i = (PH+1); i < (N_N-PH);i++)
//~ {
//~ if ( (i % (PH + 1)) == 0  || ((i+1) % (PH + 1)) == 0 ) Establece_Numero_Nodo(i,mc);
//~ }
//~ for (i = (N_N-PH); i < N_N;i++) Establece_Numero_Nodo(i,mc);
//~ }


//~ // Retorna 1 si el nodo xnd es nodo adyacente a nd
//~ int Geometria_2D::Es_nodo_adyacente(int nd, int xnd)
//~ {
//~ int n, i, nds[10];

//~ n = Retorna_Nodos_Adyacentes(nd, nds, 10);
//~ for (i = 0; i < n; i++)
//~ {
//~ if (xnd == nds[i]) return 1;
//~ }
//~ return 0;
//~ }


//~ // Retorna 1 si el nodo xnd es nodo colineal a nd
//~ int Geometria_2D::Es_nodo_colineal(int nd, int xnd)
//~ {
//~ int n, i, nds[10];
//~ ldouble x1, y1, x2, y2;

//~ if (nd == xnd) return 0;

//~ n = Retorna_Nodos_Adyacentes(nd, nds, 10);
//~ for (i = 0; i < n; i++)
//~ {
//~ if (xnd == nds[i]) {
//~ Coordenadas_nodo(nd, x1, y1);
//~ Coordenadas_nodo(xnd, x2, y2);
//~ #ifdef __Double__
//~ if (fabs(x1 - x2) < TOLERANCIA_NODO) return 1;
//~ if (fabs(y1 - y2) < TOLERANCIA_NODO) return 1;
//~ #else
//~ if (fabsl(x1 - x2) < TOLERANCIA_NODO) return 1;
//~ if (fabsl(y2 - y2) < TOLERANCIA_NODO) return 1;
//~ #endif
//~ }
//~ }
//~ return 0;
//~ }












//~ // Area del elemento EL
//~ ldouble Geometria_Rectangulos2D::Area_Elemento(int el)
//~ {
//~ ldouble x[8];
//~ ldouble y[8];

//~ Coordenadas_Elemento(el, x, y);
//~ return ((x[1] - x[0]) * (y[3] - y[0]));
//~ }


//~ /// Genera dominio con soporte extendido
//~ void Geometria_Rectangulos2D::Genera_Dominio_Extendido(ldouble x1, ldouble y1, ldouble x2, ldouble y2, int part_hor, int part_ver, ldouble &ex1, ldouble &ey1, ldouble &ex2, ldouble &ey2)
//~ {
//~ ldouble inch, incv;
//~ inch = (x2 - x1) / (ldouble) part_hor;
//~ incv = (y2 - y1) / (ldouble) part_ver;

//~ ex1 = x1 - inch;
//~ ey1 = y1 - incv;
//~ ex2 = x2 + inch;
//~ ey2 = y2 + incv;

//~ if(ex1 < X1) ex1 = X1;
//~ if(ey1 < Y1) ey1 = Y1;
//~ if(ex2 > X2) ex2 = X2;
//~ if(ey2 > Y2) ey2 = Y2;
//~ }


