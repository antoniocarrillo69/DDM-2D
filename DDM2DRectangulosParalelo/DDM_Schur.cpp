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
// con este programa. AntonioSi no ha sido así, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


#include <math.h>
#include "DDM_Schur.hpp"
#include "Man_arch.hpp"





// Inicializa los subdominios
void DDM_Schur::inicializaSubdominios(void)
{
   int i;
   ldouble x[4], y[4];

   // Numero de elementos de la particion gruesa
   num_sub = pGe2D->retornaNumeroElementos();
   if (num_sub < 2)
   {
      printf("\n\nError la malla gruesa no es valida\n");
      exit(1);
   }
   num_nodos_elemento = NUMERO_NODOS_ELEMENTO;

   printf("\nNúmero de subdominios %d\n",num_sub);
   // Solicita el arreglo para los subdominios
   funPar00(num_sub);
   //~ subdom = new DDM_SchurSubdominio[num_sub];
   //~ if (!subdom) cm.errorSolicitudMemoria("No hay memoria para los subdominios");

   // Inicializa los subdominios
   num_nodos_interiores = 0;
   ldouble sub[4];
   int par[2];
   par[0] = part.retorna(0);
   par[1] = part.retorna(1);
   for (i = 0; i < num_sub; i++)
   {
      // Retorna las coordenadas del subdominio
      pGe2D->coordenadasElemento(i+1, x, y);
      sub[0] = x[0];
      sub[1] = y[0];
      sub[2] = x[2];
      sub[3] = y[2];
      num_nodos_interiores += funPar01(i,pPr2D,sub,par,eps);
      //~ // Puntero al problema
      //~ subdom[i].punteroProblema(pPr2D);
      //~ // Inicializa el subdominio
      //~ subdom[i].inicializaSubdominio(&subdominio, &part, eps);
      //~ // Actualiza el numero de nodos interiores desconocidos
      //~ num_nodos_interiores += subdom[i].retornaNumeroNodosDesconocidos();
   }
   // Visualiza el numero de nodos interiores desconocidos
   printf("Número total de nodos interiores %d\n",num_nodos_interiores);
}


// Conoce los nodos de la frontera interior
void DDM_Schur::conoceFronteraInterior(void)
{
   int i, j, k, l, m, n, xi ,ndfmax, ndpsd;
   ldouble x[num_nodos_elemento], y[num_nodos_elemento], xx[num_nodos_elemento], yy[num_nodos_elemento];
   int xpart = pGe2D->retornaParticion(0);
   int des[] = {-xpart-1, -xpart, -xpart+1, -1, 0, +1, xpart-1, xpart, xpart+1};


   //inicializa variables
   ndpsd = (part[0] * 2) + (part[1] * 2); // Número máximo de nodos de frontera por subdominio
   ndfmax = num_sub * ndpsd;                             // Número máximo de nodos en la frontera

   // Solicita a cada subdominio las coordenadas de la frontera interior y las almacena conjuntamente con el número de subdominio correspondiente
   ldouble **cN = cm.asignaMemoriaLDOUBLE(ndpsd, dimension, "coordenadas de la frontera interior");
   ldouble **coord = cm.asignaMemoriaLDOUBLE(ndfmax, dimension, "coordenadas de la frontera interior");
   int *nsub = cm.asignaMemoriaINT(ndfmax,"datos de nodos frontera interior");

   for (i = 0, l = 0; i < num_sub; i++)
   {
      // Coordenadas de la frontera interior del subdominio
      funPar02(i,cN,ndpsd);
      //~ subdom[i].retornaNodosFronteraSubdominio(cN,ndpsd);
      for (j = 0; j < ndpsd; j++)
      {
         for (k = 0; k < dimension; k++)
         {
            coord[l][k] = cN[j][k];
         }
         nsub[l] = i;
         l++;
      }
   }
   cm.liberaMemoriaLDOUBLE(ndpsd,cN);
   //~ // Visualiza las coordenadas y el subdominio del que se obtubieron
   //~ for (i = 0; i < ndfmax; i++)
   //~ {
   //~ printf("Nodo (%3d) coordenadas [",i);
   //~ for (j = 0; j < dimension; j++)
   //~ {
   //~ printf(" %+lf ", coord[i][j]);
   //~ }
   //~ printf("]");
   //~ printf("   %d\n",nsub[i]);
   //~ }
   //~ printf("\n");

   // Calcula las matrices pues es un proceso independiente del conocer a los nodos de la frontera interior
   for (i = 0; i < num_sub; i++) funPar03(i);
   //for (i = 0; i < num_sub; i++) subdom[i].generaMatrices();


   int rnsd = 0, sw;
   int *ai = cm.asignaMemoriaINT(num_sub*8,"datos de nodos frontera interior"); // Por que a lo mas hay 8 subdominios por cada subdominio que comparten frontera interior
   int *aj = cm.asignaMemoriaINT(num_sub*8,"datos de nodos frontera interior");


   // Busca los subdominios que comparten frontera interior
   for (i = 0; i < num_sub; i++)
   {
      pGe2D->coordenadasElemento(i+1, x, y);
      for (xi = 0; xi < 9; xi++)
      {
         j = i + des[xi];
         if (j < 0 || i == j || j >= num_sub) continue;

         sw = 0;
         pGe2D->coordenadasElemento(j+1, xx, yy);

         for (k = 0; k < num_nodos_elemento; k++)
         {
            for (l = 0; l < 4; l++)
            {
               if (fabs(xx[k] - x[l]) < TOLERANCIA_NODO && fabs(yy[k] - y[l]) < TOLERANCIA_NODO )
               {
                  sw = 1;
                  break;
               }
            }
            if (sw) break;
         }

         // Almacena los subdominios
         if (sw)
         {
            // Revisa si ya existe o no
            if (rnsd)
            {
               for (n = 0; n < rnsd; n++)
               {
                  if ((ai[n] == i && aj[n] == j) || (ai[n] == j && aj[n] == i)) break;
               }
               // No existia, se almacena
               if (n == rnsd)
               {
#ifdef DEPURAR
                  if (rnsd >= num_sub*8) cm.errorSolicitudMemoria("Error desbordamiento del arreglo ai,aj");
#endif
                  ai[rnsd] = i, aj[rnsd] = j;
                  rnsd ++;
               }
            }
            else
            {
               // Por ser el primero solo se almacena
               ai[rnsd] = i, aj[rnsd] = j;
               rnsd ++;
            }
         }
      }
   }
   //~ // Visualiza los subdominios que tienen coordenadas en común
   //~ for (i = 0; i < rnsd; i++)
   //~ {
   //~ printf("\n%d  %d",ai[i],aj[i]);
   //~ }
   //~ printf("\n");


   // Solicita memoria para las coordenadas de los nodos de la frontera interior
   int *pc = cm.asignaMemoriaINT(ndfmax,"datos de nodos frontera interior");
   for (i = 0; i < ndfmax; i++) pc[i] = 0;
   num_nodos_frontera_interior = 0;

   // Busca los nodos que estan en la frontera interior como aquellos que estan compartidos en más de una frontera de los subdominios
   for (i = 0; i < rnsd; i++)
   {
      // Numero de nodos en la frontera por subdominio
      for (m = 0; m < ndpsd; m++)
      {
         if (coord[ndpsd*aj[i]+m][0] == -1000000.0) continue; // && coord[ndpsd*aj[i]+m][1] == -1000000.0) continue;
         // Numero de nodos en la frontera por subdominio
         for (n = 0; n < ndpsd; n++)
         {
            if (coord[ndpsd*ai[i]+n][0] == -1000000.0) continue; // && coord[ndpsd*ai[i]+n][1] == -1000000.0) continue;
            // Revisa si son iguales
#ifdef __Double__
            if (fabs(coord[ndpsd*ai[i]+n][0] - coord[ndpsd*aj[i]+m][0]) > TOLERANCIA_NODO) continue;
            if (fabs(coord[ndpsd*ai[i]+n][1] - coord[ndpsd*aj[i]+m][1]) > TOLERANCIA_NODO) continue;
#else
            if (fabsl(coord[ndpsd*ai[i]+n][0] - coord[ndpsd*aj[i]+m][0]) > TOLERANCIA_NODO) continue;
            if (fabsl(coord[ndpsd*ai[i]+n][1] - coord[ndpsd*aj[i]+m][1]) > TOLERANCIA_NODO) continue;
#endif
            // Almacena los nodos de la frontera interior
            if (num_nodos_frontera_interior == 0)
            {
               // Por ser el primero solo se anexa
               pc[num_nodos_frontera_interior] = ndpsd * ai[i] + n;
               num_nodos_frontera_interior++;
            }
            else
            {
               // Revisa si estan en la lista en caso contrario los anexa
               for (xi = 0; xi < num_nodos_frontera_interior; xi++)
               {
#ifdef __Double__
                  if (fabs(coord[pc[xi]][0]- coord[ndpsd*ai[i]+n][0]) < TOLERANCIA_NODO && fabs(coord[pc[xi]][1] - coord[ndpsd*ai[i]+n][1]) < TOLERANCIA_NODO) break;
#else
                  if (fabsl(coord[pc[xi]][0]- coord[ndpsd*ai[i]+n][0]) < TOLERANCIA_NODO && fabsl(coord[pc[xi]][1] - coord[ndpsd*ai[i]+n][1]) < TOLERANCIA_NODO) break;
#endif
               }
               if (xi == num_nodos_frontera_interior)
               {
#ifdef DEPURAR
                  if (num_nodos_frontera_interior >= ndfmax || n > ndpsd)
                  {
                     printf("\nError desbordamiento en el arreglo de nodos de la frontera interior\n");
                     printf("%d , %d \n",ndfmax,num_nodos_frontera_interior);
                     exit(1);
                  }
#endif
                  pc[num_nodos_frontera_interior] = ndpsd * ai[i] + n;
                  num_nodos_frontera_interior++;
               }
            }
         }
      }
   }
   // Libera memoria
   cm.liberaMemoriaINT(ai);
   cm.liberaMemoriaINT(aj);


   // Solicita memoria para las coordenadas de la frontera interior
   coord_FI = cm.asignaMemoriaLDOUBLE(num_nodos_frontera_interior, dimension, "coordenadas de la frontera interior");
   for (i = 0; i < num_nodos_frontera_interior; i++)
   {
      for (j = 0; j < dimension; j++) coord_FI[i][j] = coord[pc[i]][j];
   }
   cm.liberaMemoriaINT(pc);


   // Solicita memoria para soportar subdominio, numeracion local en el subdominio y multiplicidad
   multiplicidad  = cm.asignaMemoriaINT(num_nodos_frontera_interior, "datos de nodos frontera interior");
   subdominio  = cm.asignaMemoriaINT(num_nodos_frontera_interior, NUMERO_NODOS_ELEMENTO,"datos de nodos frontera interior");
   num_nodo_local  = cm.asignaMemoriaINT(num_nodos_frontera_interior, NUMERO_NODOS_ELEMENTO,"datos de nodos frontera interior");
   for (i = 0; i < num_nodos_frontera_interior; i++)
   {
      multiplicidad[i] = 0;
      for (j = 0; j < NUMERO_NODOS_ELEMENTO; j++)
      {
         subdominio[i][j] = -1;
         num_nodo_local[i][j] = -1;
      }
   }


   // Almacena el subdominio, numeracion local en el subdominio y multiplicidad
   for (i = 0; i < num_nodos_frontera_interior; i++)
   {
      for (j = 0; j < ndfmax; j++)
      {
         if (coord[j][0] == -1000000.0) continue; // && coord[j][1] == -1000000.0) continue;
#ifdef __Double__
         if (fabs(coord[j][0] - coord_FI[i][0]) > TOLERANCIA_NODO) continue;
         if (fabs(coord[j][1] - coord_FI[i][1]) > TOLERANCIA_NODO) continue;
#else
         if (fabsl(coord[j][0] - coord_FI[i][0]) > TOLERANCIA_NODO) continue;
         if (fabsl(coord[j][1] - coord_FI[i][1]) > TOLERANCIA_NODO) continue;
#endif
         subdominio[i][multiplicidad[i]] = nsub[j];
         num_nodo_local[i][multiplicidad[i]] = j % ndpsd;
         multiplicidad[i]++;
      }
   }
   cm.liberaMemoriaINT(nsub);
   cm.liberaMemoriaLDOUBLE(ndfmax,coord);


   printf("Número de nodos en la frontera interior %d\n", num_nodos_frontera_interior);
   //~ // Permite visualizar las coordenadas de la frontera interior, el subdominio al que pertenecen, numeración local y la multiplicidad
   //~ for (i = 0; i < num_nodos_frontera_interior; i++)
   //~ {
   //~ printf("Nodo (%3d) coordenadas [",i);
   //~ for (j = 0; j < dimension; j++)
   //~ {
   //~ printf(" %+lf ", coord_FI[i][j]);
   //~ }
   //~ printf("]");

   //~ printf("    ");
   //~ for (j = 0; j < NUMERO_NODOS_ELEMENTO; j++)
   //~ {
   //~ printf(" %+d",subdominio[i][j]);
   //~ }
   //~ printf("     ");
   //~ for (j = 0; j < NUMERO_NODOS_ELEMENTO; j++)
   //~ {
   //~ printf(" %+d ",num_nodo_local[i][j]);
   //~ }
   //~ printf("     %d\n", multiplicidad[i]);
   //~ }
}


void DDM_Schur::resuelveSubdominios(void)
{
   int i, j, k, n, it;
   ldouble alfa, gama, beta, t, s;
   int num_max_iteraciones = 1000;

   printf("\nNúmero de iteraciones en CGM ");


   // Inicializa variables
   pXX    = new Vector(num_nodos_frontera_interior, "Solución");
   pXU    = cm.asignaMemoriaLDOUBLE(num_nodos_frontera_interior,"Valores intermedios de la solucion");
   ldouble *pxXU    = cm.asignaMemoriaLDOUBLE(num_nodos_frontera_interior,"Valores intermedios de la solucion");
   Vector *pBC = new Vector(num_nodos_frontera_interior,"Lado Derecho en CGM BC");
   if (pXU == NULL || pXX == NULL || pxXU == NULL || pBC == NULL) cm.errorSolicitudMemoria("Error no hay memoria datos de nodos frontera interior");

   // Llena el vector b para resolver el schur complement Su=b
   for (i = 0; i < num_sub; i++)
   {
      funPar04(i, pXU, pxXU, num_nodos_frontera_interior);
      for (j = 0; j < num_nodos_frontera_interior; j++)
      {
         for (k = 0; k < num_nodos_elemento; k++)
         {
            if (subdominio[j][k] == i) pBC->asigna(j,pBC->retorna(j) + pXU[num_nodo_local[j][k]] - pxXU[num_nodo_local[j][k]]);
         }
      }
   }
   cm.liberaMemoriaLDOUBLE(pxXU);
//~ pBC->visualiza(1,1,1);


   // Método de CGM para la solución de los nodos interiores sin constrir la matriz
   BCGM::resuelve(pXX, pBC);
   printf("(%d) para resolver los nodos de la frontera interior\n",BCGM::retornaNumeroIteraciones());

   // Visualización de la solución de los nodos de la frontera interior
   //~ printf("Solución de nodos frontera interior\n");
   //~ pXX->visualiza(1,1);


   delete pBC;
}



// Resuelve nodos interiores
void DDM_Schur::resuelveNodosInteriores(void)
{
   int i, j, n, k;

   // Pasa la solucion de los nodos frontera interior para resolver los nodos interiores
   for (i = 0; i < num_sub; i++)
   {
      for (n = 0, j = 0; j < num_nodos_frontera_interior; j++)
      {
         for (k = 0; k < num_nodos_elemento; k++)
         {
            if (subdominio[j][k] == i)
            {
               pXU[num_nodo_local[j][k]] = pXX->retorna(j);
               n++;
            }
         }
      }
      funPar06(i, pXU, num_nodos_frontera_interior);
      //~ subdom[i].asignaVectorFronteraInterior(pXU);
      //~ subdom[i].solucionNodosInteriores();
   }
}



// Retorna la solucion del subdominio
int DDM_Schur::retornaSolucion(int sub, ldouble **coord, ldouble *val)
{
   int n = (part[0]+1)*(part[1]+1);
   if (sub >=0 && sub < num_sub) funPar07(sub, coord, val, n);
   // subdom[sub].retornaSolucion(coord, val);
   return n;
}


// Retorna error en el subdominio
ldouble DDM_Schur::retornaErrorSubdominio(int sub)
{
   if (sub >=0 && sub < num_sub) return funPar08(sub);
   // subdom[sub].retornaErrorSubdominio();
   return -1.0;
}



// Visualiza la solicion del problema
void DDM_Schur::visualizaSolucion(void)
{
   int i, j, k, n, l = (part.retorna(0)+1)*(part.retorna(1)+1);
   ldouble **coord = cm.asignaMemoriaLDOUBLE(l,dimension,"Graba solucion");
   ldouble *valor = cm.asignaMemoriaLDOUBLE(l,"Graba solucion");


   Ctrl_visualizacion cv;

   for (i = 0; i < num_sub; i++)
   {
      printf("\n\nSubdominio [ %3d ]\n",i+1);
      n = retornaSolucion(i, coord, valor);
      for (j = 0; j < n; j++)
      {
         printf(" %#3d: ( ",j+1);
         for (k = 0; k < dimension-1; k++)
         {
            cv.visualiza_e(coord[j][k]);
            printf(", ");
         }
         cv.visualiza_e(coord[j][k]);
         printf(" ) ");
         cv.visualiza_e(valor[j]);
         printf("\n");
      }
      printf("\n");
   }
   cm.liberaMemoriaLDOUBLE(l,coord);
   cm.liberaMemoriaLDOUBLE(valor);
}



// Graba la solución a un archivo
// @param arch Nombre del archivo en el cual se grabara la solucion del problema
void DDM_Schur::grabaSolucion(const char *arch)
{
   Manipulador_archivos *la = new Manipulador_archivos;
   if (!la) cm.errorSolicitudMemoria("Grabar archivo");
   la->parametros(arch,GRABA_ARCHIVO,300);

   int i, j, k, n, l = (part[0]+1)*(part[1]+1);
   ldouble **coord = cm.asignaMemoriaLDOUBLE(l,dimension,"Graba solucion");
   ldouble *valor = cm.asignaMemoriaLDOUBLE(l,"Graba solucion");
   char xcad[300], tmp [300];
   xcad[0] = 0;


   for (i = 0; i < num_sub; i++)
   {
      n = retornaSolucion(i, coord, valor);
      for (j = 0; j < n; j++)
      {
         for (k = 0; k < dimension; k++)
         {
#ifdef __Double__
            sprintf(tmp,"%1.16le ",coord[j][k]);
#else
            sprintf(tmp,"%1.18Le ",coord[j][k]);
#endif
            strcat(xcad, tmp);
         }
#ifdef __Double__
         sprintf(tmp,"%1.16le ",valor[j]);
#else
         sprintf(tmp,"%1.18Le ",valor[j]);
#endif
         strcat(xcad, tmp);
         la->grabaLinea(xcad);
         xcad[0] = 0;
      }
   }
   cm.liberaMemoriaLDOUBLE(l,coord);
   cm.liberaMemoriaLDOUBLE(valor);

   delete la;
}

// Retorna el máximo error de la solución vs la solución análitica
// @return El máximo error encontrado en todo el dominio
ldouble DDM_Schur::error(void)
{
   ldouble max = 0.0, err;
   int i;

   // Ciclo para encontrar el maximo error
   for (i = 0; i < num_sub; i++)
   {
      err = retornaErrorSubdominio(i);
      if (err > max) max = err;
   }

   return max;
}

