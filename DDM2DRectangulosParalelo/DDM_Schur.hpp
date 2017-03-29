//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para definir los métodos del método de descomposición de dominio de subestructura- //
// ción Schur                                                                               //
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


#ifndef __DDM_Schur__
#define __DDM_Schur__


#include "Problema_2D.hpp"
#include "Geometria.hpp"
#include "DDM_SchurSubdominio.hpp"
#include "CtrlMemoria.hpp"
#include "Geometria_2DRectangulos.hpp"
#include "BCGM.hpp"


/// Clase para definir el método descomposición de dominio de subestructuración (Complemento de Schur)
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.0
    @bug No hay errores conocidos
*/
class DDM_Schur: public BCGM, public  MultOp, public ProductoPunto
{

private:


   // Configuración necesaria para el método CGM

   /// Producto punto, para el método de CGM
   inline double productoPunto(Vector *u, Vector *v)
   {
      return u->productoPunto(v);
   }

   /// Multiplica Au=v, para el método de CGM
   inline void multiplica(Vector *u, Vector *v)
   {
      int i, n, k, j;
      v->inicializa(0.0);
      // Calculo del vector mediante la multiplicación de x por matriz de Schur Si de cada subdominio
      for (i = 0; i < num_sub; i++)
      {
         for (n = 0, j = 0; j < num_nodos_frontera_interior; j++)
         {
            for (k = 0; k < num_nodos_elemento; k++)
            {
               if (subdominio[j][k] == i)
               {
                  pXU[num_nodo_local[j][k]] = u->retorna(j);
                  n++;
               }
            }
         }
         funPar05(i, pXU, num_nodos_frontera_interior);

         for (j = 0; j < num_nodos_frontera_interior; j++)
         {
            for (k = 0; k < num_nodos_elemento; k++)
            {
               if (subdominio[j][k] == i) v->asigna(j,v->retorna(j) + pXU[num_nodo_local[j][k]]);
            }
         }
      }
   }

   /// Tamaño del sistema lineal, para el método de CGM
   inline int tamano(void)
   {
      return num_nodos_frontera_interior;
   }



protected:

   /// Puntero a un arreglo de subdominios
   DDM_SchurSubdominio *subdom;
   /// Puntero a la definicion de la geometria
   Geometria_2D       *pGe2D;
   /// Puntero a la definicion del problema
   Problema_2D        *pPr2D;
   /// Objeto para manipular memoria
   CtrlMemoria cm;

   /// Particion
   VectorInt part;
   /// Tolerancia
   ldouble eps;
   /// Número de subdominios en la partición
   int num_sub;
   /// Número de nodos interiores
   int num_nodos_interiores;
   /// Número de nodos de frontera interior
   int num_nodos_frontera_interior;
   /// Dimensión de la descomposicion
   int dimension;

   /// Número de nodos por elemento
   int num_nodos_elemento;
   /// Valores solución de la frontera interior
   Vector  *pXX;
   /// Valores intermedios de la solucion de la frontera interior
   ldouble  *pXU;
   /// Coordenadas de la frontera interior
   ldouble **coord_FI;
   /// Indica el numero de sumdominios que comparten el nodo
   int *multiplicidad;
   /// Indica al subdominio al que pertenece el nodo
   int **subdominio;
   /// Indica el número de nodo local de los nodos de frontera interior del subdominio
   int **num_nodo_local;


   // Comportamientos a paralelizar

   /// Inicializa los subdominios
   virtual void funPar00(int ns)
   {
      subdom = new DDM_SchurSubdominio[ns];
      if (!subdom) cm.errorSolicitudMemoria("No hay memoria para los subdominios");
   }

   /// Recibe los datos para inicializar el subdominio
   virtual int funPar01(int ind, Problema_2D *pr, ldouble *sub, int *par, ldouble ep)
   {
      // Puntero al problema
      subdom[ind].punteroProblema(pr);
      // Inicializa el subdominio
      subdom[ind].inicializaSubdominio(sub, par, ep);
      // Actualiza el numero de nodos interiores desconocidos
      return subdom[ind].retornaNumeroNodosDesconocidos();
   }

   // Envia las coordenadas de la frontera interior
   virtual void funPar02(int ind, ldouble **cd, int tm)
   {
      subdom[ind].retornaNodosFronteraSubdominio(cd,tm);
   }

   // Genera las matrices
   virtual void funPar03(int ind)
   {
      subdom[ind].generaMatrices();
   }

   // Envia el vector de carga
   virtual void funPar04(int ind, ldouble *val1, ldouble *val2, int tm)
   {
      subdom[ind].contenidoVectorCarga(val1);
      subdom[ind].contenidoVectorSchur(val2);
   }

   // Proyeccion
   virtual void funPar05(int ind, ldouble *val, int tm)
   {
      subdom[ind].asignaVectorFronteraInterior(val);
      subdom[ind].proyeccionFronteraInterior();
      subdom[ind].retornaVectorFronteraInterior(val);
   }

   // Resuelve nodos interiores
   virtual void funPar06(int ind, ldouble *val, int tm)
   {
      subdom[ind].asignaVectorFronteraInterior(val);
      subdom[ind].solucionNodosInteriores();
   }

   // Retorna la solucion del subdominio
   virtual void funPar07(int ind, ldouble **cd, ldouble *vl, int tm)
   {
      subdom[ind].retornaSolucion(cd, vl);
   }

   virtual ldouble funPar08(int ind)
   {
      return subdom[ind].retornaErrorSubdominio();
   }

   virtual void funPar09(int ind)
   {
      subdom[ind].liberaMemoria();
   }

   /// Inicializa los subdominios
   void inicializaSubdominios(void);

   /// Conoce los nodos de la frontera interior
   void conoceFronteraInterior(void);

   /// Resuelve subdominios
   void resuelveSubdominios(void);

   /// Resuelve nodos interiores
   void resuelveNodosInteriores(void);


public:

   DDM_Schur(void) : BCGM(*(MultOp*) this, *(ProductoPunto*) this, 1000, 1e-5)
   {
      subdom = NULL;
      pXX = NULL;
      pXU = NULL;
      coord_FI = NULL;
      multiplicidad = NULL;
      subdominio = NULL;
      num_nodo_local = NULL;
      num_sub = 0;
   }

   /// Destructor de la clase
   ~DDM_Schur(void)
   {
      if (subdom)
      {
         int i;
         for (i = 0; i < num_sub; i++) funPar09(i);
         delete []subdom;
         subdom = NULL;
      }
      if (pXX) delete pXX;
      if (pXU) cm.liberaMemoriaLDOUBLE(pXU);
      if (coord_FI) cm.liberaMemoriaLDOUBLE(num_nodos_frontera_interior,coord_FI);
      if (multiplicidad) cm.liberaMemoriaINT(multiplicidad);
      if (subdominio) cm.liberaMemoriaINT(num_nodos_frontera_interior,subdominio);
      if (num_nodo_local) cm.liberaMemoriaINT(num_nodos_frontera_interior,num_nodo_local);
   }

   /// Constructor de la clase
   void inicializa(Problema_2D *pr, Geometria_2DRectangulos *ge, int mx, int my, double eps=1e-5)
   {
      if (mx < 2 || my < 2)
      {
         printf("\n\nError no se esta haciendo una descomposción fina valida (%d x %d)\n",mx,my);
         exit(1);
      }

      pPr2D = pr;
      pGe2D = ge;

      dimension = pGe2D->retornaDimension();
      part.redimensiona(dimension);
      part.asigna(0,mx);
      part.asigna(1,my);

      this->eps = eps;
   }


   /// Resuelve mediante el método de descomposición de dominio
   void resuelveDDM(void)
   {
      // Inicializa subdominios
      inicializaSubdominios();
      // Conoce la frontera interior
      conoceFronteraInterior();
      // Resuelve subdominios
      resuelveSubdominios();
      // Resuelve nodos interiore
      resuelveNodosInteriores();
   }

   /// Retorna la solución de cada punto de la discretización del subdominio
   /** @param sub Número del subdominio
       @param coord Coordenada
       @param val Valor
       @return Número de coordenadas y valores regresados */
   int retornaSolucion(int sub, ldouble **coord, ldouble *val);

   /// Retorna el máximo error de la solución vs la solución análitica en el subdominio
   /** @param sub Número del subdominio
       @return El máximo error encontrado en todo el dominio*/
   ldouble retornaErrorSubdominio(int sub);

   /// Visualiza la solicion del problema
   void visualizaSolucion(void);

   /// Graba la solución a un archivo
   /** @param arch Nombre del archivo en el cual se grabara la solucion del problema */
   void grabaSolucion(const char *arch);

   /// Retorna el máximo error de la solución vs la solución análitica
   /** @return El máximo error encontrado en todo el dominio */
   ldouble error(void);


};

#endif
