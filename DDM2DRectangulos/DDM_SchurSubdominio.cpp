//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para definir los comportamientos de un subdominio mediante el método de descompo-  //
// sición de dominio de subestructuración Schur                                             //
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




#include "DDM_SchurSubdominio.hpp"
#include "ResuelveFactorizacionLUBandDisp.hpp"
#include "ResuelveCGMBandDisp.hpp"
#include "GaussQuad.hpp"
#include "MatrizBand.hpp"
#include "MatrizBandComp.hpp"
#include "MatrizDispersaComp.hpp"
#include "MatrizDensa.hpp"



// Inicializa el complemento de Schur
void DDM_SchurSubdominio::inicializaComplementoSchur(void)
{
   pBi = new Vector(num_nodos_frontera_interior,"Bi de Genera_SchurComplement");
   pUS = new Vector(num_nodos_frontera_interior,"US de Genera_SchurComplement");
   pSU = new Vector(num_nodos_frontera_interior,"SU de Genera_SchurComplement");

   // Variables usadas en Multiplica_Matriz_Schur
   pxb = new Vector(pAIG->renglones(),"xb de Multiplica Matriz de Schur");
   psx = new Vector(pAIG->renglones(),"sx de Multiplica Matriz de Schur");
   py  = new Vector(pAIG->renglones(),"y de Multiplica Matriz de Schur");
   py1 = new Vector(pAGI->renglones(),"y1 de Multiplica Matriz de Schur");
   py2 = new Vector(pAGG->renglones(),"y2 de Multiplica Matriz de Schur");

   if (!pBi || !pUS || !pSU || !pxb || !psx || !py || !py1 || !py2) cm.errorSolicitudMemoria("No hay memoria para los subdominios");

   // Calculo de la parte derecha del complemento de Schur
   Vector *px = new Vector(pB->columnas(),"x");
   if (!px) cm.errorSolicitudMemoria("No hay memoria para los subdominios");

#ifdef USANDO_FACTORIZACION_LU
   pRSL = new ResuelveFactorizacionLUBandDisp(pAII, px, pB);
   pRSL->resuelve();
#else
   pRSL = new ResuelveCGMBandDisp(pAII, px, pB, eps, 1000);
   pRSL->resuelve();
   //~ printf("Número de iteraciones en CGM (%d) para resolver el lado derecho de Schur Complement\n",RSL->retornaNumeroIteraciones());
#endif

   pAGI->multiplica(px,pBi);

   delete px;
}


// Retorna la solucion del subdominio
void DDM_SchurSubdominio::retornaSolucion(ldouble **coord, ldouble *val)
{
   int i, j;
   ldouble xc[10];
   for (i = 0; i < num_nodos; i++)
   {
      // Coordenadas
      pGe->retornaValorNodo(i, xc);
      for (j = 0; j < dimension; j++) coord[i][j] = xc[j];
      // Valor
      val[i] = pXto->retorna(i);
   }
}


// Retorna error en el subdominio
ldouble DDM_SchurSubdominio::retornaErrorSubdominio(void)
{
   ldouble err = 0.0;

   return err;
}




// Proyeccion de la frontera interior
void DDM_SchurSubdominio::proyeccionFronteraInterior(void)
{
   pAIG->multiplica(pUS,pxb);
   psx->inicializa(0.0);

#ifdef USANDO_FACTORIZACION_LU
   pRSL->resuelve(psx,pxb);
#else
   pRSL->resuelve(psx, pxb);
   //~ printf("Número de iteraciones en CGM (%d) para resolver el complemento de Schur\n",pRSL->retornaNumeroIteraciones());
#endif

   pAGI->multiplica(psx,py1);
   pAGG->multiplica(pUS,py2);
   pSU->resta(py2,py1);
}





// Solución de los nodos interiores
void DDM_SchurSubdominio::solucionNodosInteriores(void)
{
   int i;

   delete pSU;
   pSU = NULL;

   // Asigan los valores de la frontera interior a la solucion
   for (i = 0; i < num_nodos; i++)
   {
      if (nd_s[i] >= 0) pXto->asigna(i,pUS->retorna(nd_s[i]));
   }
   Vector *pb = new Vector(pB->columnas(),"b de Solucion_via_imversa");
   Vector *pu = new Vector(pB->columnas(),"u de Solucion_via_imversa");
   if (!pb || !pu) cm.errorSolicitudMemoria("Variables para solución via inversa");


   pAIG->multiplica(pUS,pu);

   pb->resta(pB,pu);

   pX->inicializa(0.0);

#ifdef USANDO_FACTORIZACION_LU
   pRSL->resuelve(pX,pb);
#else
   pRSL->resuelve(pX,pb);
   //~ printf("Número de iteraciones en CGM (%d) para resolver los nodos interiores\n",RSL->retornaNumeroIteraciones());
#endif

   delete pu;
   delete pb;
}


// Retorna los nodos de la frontera del subdominio
void DDM_SchurSubdominio::retornaNodosFronteraSubdominio(ldouble **coord, int tam)
{
   ldouble xx , xy;
   int i;


   //  Obtiene las coordenadas del dominio
   MatrizDensa dom(2,2);
   pPr2D->retornaDominio(&dom);
   nd_s = cm.asignaMemoriaINT(num_nodos,"nodos frontera interior");
   for (i = 0; i < num_nodos; i++) nd_s[i] = -1;

   // Almacena las coordenadas de los nodos de la frontera del subdominio que no sean nodos de la frontera del dominio
   num_nodos_frontera_interior = 0;
   for (i = 0; i < num_nodos; i++)
   {
      // Coordenadas del nodos frontera
      if (pGe2D->retornaNumeracionNodo(i) == -1)
      {
         // Obtiene las coordenadas del nodo
         pGe2D->coordenadasNodo(i,xx,xy);

         // Elimina los nodos en la frontera del dominio
#ifdef __Double__
         if (fabs(xx - dom.retorna(0,0)) < TOLERANCIA_NODO) continue;
         if (fabs(xx - dom.retorna(1,0)) < TOLERANCIA_NODO) continue;
         if (fabs(xy - dom.retorna(0,1)) < TOLERANCIA_NODO) continue;
         if (fabs(xy - dom.retorna(1,1)) < TOLERANCIA_NODO) continue;
#else
         if (fabsl(xx - dom.retorna(0,0)) < TOLERANCIA_NODO) continue;
         if (fabsl(xx - dom.retorna(1,0)) < TOLERANCIA_NODO) continue;
         if (fabsl(xy - dom.retorna(0,1)) < TOLERANCIA_NODO) continue;
         if (fabsl(xy - dom.retorna(1,1)) < TOLERANCIA_NODO) continue;
#endif
         // Almacena la coordenada
         coord[num_nodos_frontera_interior][0] = xx;
         coord[num_nodos_frontera_interior][1] = xy;
         // Almacena la numeracion local
         nd_s[i] = num_nodos_frontera_interior;
         num_nodos_frontera_interior++;
#ifdef DEPURAR
         if (num_nodos_frontera_interior > tam)
         {
            printf("Desbordamiento del arreglo coordenadas nodos frontera subdominio\n");
            exit(1);
         }
#endif
      }
   }
   // Coordenadas no asignadas
   for (i = num_nodos_frontera_interior; i < tam; i++) coord[i][0] = coord[i][1] = -1000000.0; // valor de relleno
}


// Inicializa el subdominio
void DDM_SchurSubdominio::inicializaSubdominio(ldouble *sub, int *par, ldouble eps)
{
   subdominio.redimensiona(2,2);
   part.redimensiona(2);

   // Subdominio
   subdominio.asigna(0,0,sub[0]);
   subdominio.asigna(0,1,sub[1]);
   subdominio.asigna(1,0,sub[2]);
   subdominio.asigna(1,1,sub[3]);
   // Particion del dominio
   part.asigna(0,par[0]);
   part.asigna(1,par[1]);
   // Toleracia
   this->eps = eps;

   pGe2D = new Geometria_2DRectangulos();
   if (!pGe2D) cm.errorSolicitudMemoria("Solicitud Memoria Geometria");
   pGe = pGe2D;

   // Genera la geometria del problema
   pGe2D->inicializa(&subdominio,part.retorna(0),part.retorna(1));

   // Marca los nodos externos
   pGe2D->marcaNodosSatisfagan(subdominio.retorna(0,0),0,-1);
   pGe2D->marcaNodosSatisfagan(subdominio.retorna(1,0),0,-1);
   pGe2D->marcaNodosSatisfagan(subdominio.retorna(0,1),1,-1);
   pGe2D->marcaNodosSatisfagan(subdominio.retorna(1,1),1,-1);
   // Numera los nodos
   pGe2D->numeraNodos();


   // Regresa el número de nodos
   num_nodos = pGe2D->retornaNumeroNodos();
   // Regresa el número de elementos
   num_elementos = pGe2D->retornaNumeroElementos();
   // Regresa el número de nodos desconocidos
   num_nodos_interiores = pGe2D->retornaNumeroNodosDesconocidos();
   // Regresa el número máximo de nodos en la frontera
   num_maximo_nodos_en_frontera = pGe2D->numeroMaximoNodosFrontera();
   // Dimension del dominio
   dimension = pGe2D->retornaDimension();

   // Vector sulución de los nodos interiores
   pX = new Vector(num_nodos_interiores,"X");
   if (!pX) cm.errorSolicitudMemoria("Valores Desconocidos");

   // Vector solución de todo el subdominio
   pXto  =  new VectorExtendido(num_nodos,pX,"Xto");
   if (!pXto) cm.errorSolicitudMemoria("Xto");

   int i, j = 0;
   for (i = 0; i < num_nodos; i++)
   {
      if (pGe2D->retornaNumeracionNodo(i) < 0) pXto->inicializa(i,0.0);
      else
      {
         pXto->inicializa(i,j);
         j++;
      }
   }


   // Visualiza la información del subdominio
   //~ pGe2D->visualiza();
   pGe2D->visualizaCoordenadasDominio();
   printf("\nNúmero de elementos:        %d",num_elementos);
   printf("\nNúmero de Nodos:            %d",num_nodos);
   printf("\nNúmero de Nodos interiores: %d",num_nodos_interiores);
   printf("\n\n");
}



// Genera el vector de carga
void DDM_SchurSubdominio::generaVectorCarga(void)
{
   int i, j, l, m, n;
   ldouble x;
   ldouble TX[NUMERO_NODOS_ELEMENTO], TY[NUMERO_NODOS_ELEMENTO], J, pmx, pmy;
   ldouble cd[7], cd1[7];

   int nd[10];



   // Variables para integración
   ldouble itg;
   ldouble *PX = new ldouble[num_puntos_cuadratura];
   ldouble *WX = new ldouble[num_puntos_cuadratura];
   if (!PX || !WX) cm.errorSolicitudMemoria("Genera vector de carga");

   GaussQuad integ(-1.0,1.0,num_puntos_cuadratura,PX,WX);


   // Solicita memoria para los diferentes vectores y matrices necesarios para el método
   pXA   =  new MatrizDensa(pGe2D->retornaNodosElemento(),pGe2D->retornaNodosElemento(),"Matriz Temporal para Generar Matriz de Rigidez");
   if (!pXA) cm.errorSolicitudMemoria("Matriz Temporal para Generar Matriz de Rigidez");

   ldouble *pXM = new ldouble[num_nodos];
   if (!pXM) cm.errorSolicitudMemoria("Genera vector de carga");

   // Vector sulución de los nodos interiores
   pB = new Vector(num_nodos_interiores,"Vector de carga local");
   if (!pB) cm.errorSolicitudMemoria("Vector de carga local");

   // Vector solución de todo el subdominio
   pBA  =  new VectorExtendido(num_nodos,pB,"Vector de carga");
   if (!pBA) cm.errorSolicitudMemoria("Vector de carga");

   for (i = 0, j = 0; i < num_nodos; i++)
   {
      if (pGe2D->retornaNumeracionNodo(i) < 0) pBA->inicializa(i,0.0);
      else
      {
         pBA->inicializa(i,j);
         j++;
      }
   }

   // Nodos interiores
   for (i = 0; i < num_elementos; i++)
   {
      // Recupera la referencia del nodo global con respecto al nodo local
      pGe2D->retornaNodosElemento(i+1, nd, pGe2D->retornaNodosElemento());
      // Obtiene las coordenadas del elemento
      pGe2D->coordenadasElemento(i+1, TX, TY);
      pPr2D->asignarValorNodo(TX,TY);

      pmx = TX[0] + (TX[1] - TX[0])/2.0;
      pmy = TY[0] + (TY[3] - TY[0])/2.0;

      // Jacobiano de la transformación
#ifdef __Double__
      J = fabs( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#else
      J = fabsl( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#endif
      pPr2D->asignarValorJacobiano(J);


      // Llenado del vector local usando el lado derecho de la ecuacion mediante un cambio del intervalo de integracion
      for (j = 0; j < pGe2D->retornaNodosElemento(); j++)
      {
         // Calculo de la integral numerica
         itg = 0.0;
         for (m = 0; m < num_puntos_cuadratura; m++)
         {
            cd[0] = (((TX[1] - TX[0]) / 2.0) * PX[m] + ((TX[1] + TX[0])/2.0));
            for (n = 0; n < num_puntos_cuadratura; n++)
            {
               cd[1] = (((TY[3] - TY[0]) / 2.0) * PX[n] + ((TY[3] + TY[0])/2.0));
               itg += WX[m] * WX[n] * pPr2D->ladoDerecho(cd) * pPr2D->l_n(j,PX[m],PX[n]) * J;
            }
         }
         x = pBA->retorna(nd[j]) + itg;
         if (x) pBA->asigna(nd[j],x);
      }

      if (pGe2D->retornaNumeracionNodo(i) >= 0) continue;

      for (l = 0; l < num_nodos; l++) pXM[l] = 0.0;

      // Genera matriz de carga local a partir de la integracion sobre cada elemento
      for (j = 0; j < pGe2D->retornaNodosElemento(); j++)
      {
         for (l = 0; l < pGe2D->retornaNodosElemento(); l++)
         {
            // Calculo de la integral numerica
            itg = 0.0;
            for (m = 0; m < num_puntos_cuadratura; m++)
            {
               for (n = 0; n < num_puntos_cuadratura; n++)
               {
                  cd1[0] = PX[m];
                  cd1[1] = PX[n];
                  itg += (WX[m] * WX[n] * pPr2D->f(cd1,j*pGe2D->retornaNodosElemento()+l)) * J;
               }
            }
            pXA->asigna(j,l,itg);
            x = pXM[nd[l]] + pXA->retorna(j,l);
            pXM[nd[l]] = x;
         }
         x =  pBA->retorna(i) - pXM[j] * pXto->retorna(j);
         if (x) pBA->asigna(i,x);
      }

   }

#ifdef DEPURAR
   if (visualiza)
   {
      pBA->visualiza(1,1);
   }
#endif

   delete []pXM;
   delete []PX;
   delete []WX;
}


// Genera la matriz de interiores-interiores o matriz de carga
void DDM_SchurSubdominio::generaMatriz_AII(void)
{
   int i, j, l, m, n, k, p, q, sw;
   ldouble TX[NUMERO_NODOS_ELEMENTO], TY[NUMERO_NODOS_ELEMENTO], J;
   ldouble cd1[7];

   ldouble  tp;
   int nd[10], el[10], num;



   // Variables para integración
   ldouble itg;
   ldouble *PX = new ldouble[num_puntos_cuadratura];
   ldouble *WX = new ldouble[num_puntos_cuadratura];
   if (!PX || !WX) cm.errorSolicitudMemoria("Genera matriz AII");

   GaussQuad integ(-1.0,1.0,num_puntos_cuadratura,PX,WX);


// Solicita memoria para la matriz de carga
#ifdef USANDO_FACTORIZACION_LU
   pAII = new MatrizBand(pGe2D->retornaNumeroNodosDesconocidos(),pGe2D->retornaNumeroNodosDesconocidos(),TAMANO_BANDA*2+1,"Matriz de Rigidez");
#else
   if (pPr2D->retornaCoeficientesConstantes())
   {
      pAII = new MatrizBandComp(pGe2D->retornaNumeroNodosDesconocidos(),pGe2D->retornaNumeroNodosDesconocidos(),TAMANO_BANDA,"Matriz de Rigidez");
   }
   else
   {
      pAII = new MatrizBand(pGe2D->retornaNumeroNodosDesconocidos(),pGe2D->retornaNumeroNodosDesconocidos(),TAMANO_BANDA,"Matriz de Rigidez");
   }
#endif
   if (!pAII) cm.errorSolicitudMemoria("Genera matriz AII");

   // Llena la matriz de carga de nodos interiores AII
   sw = 0;
   for (i = 0; i < num_nodos; i++)
   {
      // Descarta a los nodos que no estan en frontera interior
      if (pGe2D->retornaNumeracionNodo(i) < 0) continue;

      // Busca todos los elemento que contienen al nodo buscado
      num = pGe2D->retornaElementosContienenNodo(i,el,pGe2D->numeroElementosSoporteNodo());
      // realiza las integraciones sobre cada elemento que contiene al nodo
      for (k = 0; k < num; k++)
      {
         // Recupera la referencia del nodo global con respecto al nodo local
         pGe2D->retornaNodosElemento(el[k], nd, pGe2D->retornaNodosElemento());
         // Obtiene las coordenadas del elemento
         pGe2D->coordenadasElemento(el[k], TX, TY);
         pPr2D->asignarValorNodo(TX,TY);

         // Jacobiano de la transformación
#ifdef __Double__
         J = fabs( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#else
         J = fabsl( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#endif
         pPr2D->asignarValorJacobiano(J);

         // Ciclo para calcular la matriz local correspondiente al nodo local J,L
         for (j = 0; j < pGe2D->retornaNodosElemento(); j++)
         {
            // Si los coeficientes de la ecuación son constantes solo calcula una sola ves
            if (sw == 0 || (sw > 0 && !pPr2D->retornaCoeficientesConstantes()))
            {
               for (l = 0; l < pGe2D->retornaNodosElemento(); l++)
               {
                  // Calculo de la integral numerica
                  itg = 0.0;
                  for (m = 0; m < num_puntos_cuadratura; m++)
                  {
                     for (n = 0; n < num_puntos_cuadratura; n++)
                     {
                        cd1[0] = PX[m];
                        cd1[1] = PX[n];
                        itg += (WX[m] * WX[n] * pPr2D->f(cd1,j*pGe2D->retornaNodosElemento()+l)) * J;
                     }
                  }
                  pXA->asigna(j,l,itg);
               }
               sw = 1;
#ifdef DEPURAR
               if (visualiza)
               {
                  // Matriz de carga local
                  pXA->visualiza(0);
               }
#endif
            }
            //~ // Llena la matriz AII
            m = pGe2D->retornaNumeracionNodo(nd[j]);
            if (m < 0) continue;
            n = pGe2D->retornaNumeracionNodo(i);
            for (l = 0; l < pGe2D->retornaNodosElemento(); l++)
            {
               if (nd[l] == nd[j]) p = l;
               if (nd[l] == i) q = l;
            }
            tp = pAII->retorna(n,m) + pXA->retorna(p,q);
            if (tp) pAII->asigna(n,m,tp);
         }
      }
   }

   // Visualiza la matriz de carga
#ifdef DEPURAR
   if (visualiza)
   {
      pAII->visualiza(0);
   }
#endif
   delete []PX;
   delete []WX;

}



// Genera la matriz de interiores-frontera interior
void DDM_SchurSubdominio::generaMatriz_AGI(void)
{
   int i, j, l, n , m, k, p, q, sw;
   int el[10], nd[10], num;
   ldouble TX[NUMERO_NODOS_ELEMENTO], TY[NUMERO_NODOS_ELEMENTO], J;
   ldouble itg, tp;
   ldouble cd1[7];

   // Variables para integración
   ldouble *PX = new ldouble[num_puntos_cuadratura];
   ldouble *WX = new ldouble[num_puntos_cuadratura];
   if (!PX || !WX) cm.errorSolicitudMemoria("Genera matriz AGI");
   GaussQuad integ(-1.0,1.0,num_puntos_cuadratura,PX,WX);

   // Solicita espacio para la matriz
   if (pPr2D->retornaCoeficientesConstantes())
   {
      pAGI = new MatrizDispersaComp(num_nodos_frontera_interior,pGe2D->retornaNumeroNodosDesconocidos(),4,"AGI");
   }
   else
   {
      pAGI = new MatrizDispersa(num_nodos_frontera_interior,pGe2D->retornaNumeroNodosDesconocidos(),4,"AGI");
   }
   if (!pAGI) cm.errorSolicitudMemoria("AGI");


   // Llena la matriz AGI
   sw = 0;
   for (i = 0; i < num_nodos; i++)
   {
      // Descarta a los nodos que no estan en frontera interior
      if (nd_s[i] < 0) continue;
      // Busca todos los elemento que contienen al nodo buscado
      num = pGe2D->retornaElementosContienenNodo(i,el,pGe2D->numeroElementosSoporteNodo());
      for (k = 0; k < num; k++)
      {
         // Recupera la referencia del nodo global con respecto al nodo local
         pGe2D->retornaNodosElemento(el[k], nd, pGe2D->retornaNodosElemento());
         // Obtiene las coordenadas del elemento
         pGe2D->coordenadasElemento(el[k], TX, TY);
         pPr2D->asignarValorNodo(TX,TY);

         // Jacobiano de la transformación
#ifdef __Double__
         J = fabs( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#else
         J = fabsl( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#endif
         pPr2D->asignarValorJacobiano(J);

         // Ciclo para calcular la matriz local correspondiente al nodo local J,L
         for (j = 0; j < pGe2D->retornaNodosElemento(); j++)
         {
            // Si los coeficientes de la ecuación son constantes solo calcula una sola ves
            if (sw == 0 || (sw > 0 && !pPr2D->retornaCoeficientesConstantes()))
            {
               for (l = 0; l < pGe2D->retornaNodosElemento(); l++)
               {
                  // Calculo de la integral numerica
                  itg = 0.0;
                  for (m = 0; m < num_puntos_cuadratura; m++)
                  {
                     for (n = 0; n < num_puntos_cuadratura; n++)
                     {
                        cd1[0] = PX[m];
                        cd1[1] = PX[n];
                        itg += (WX[m] * WX[n] * pPr2D->f(cd1,j*pGe2D->retornaNodosElemento()+l)) * J;
                     }
                  }
                  pXA->asigna(j,l,itg);
               }
               sw = 1;
#ifdef DEPURAR
               if (visualiza)
               {
                  // Matriz de carga local
                  pXA->visualiza(0);
               }
#endif
            }
            // Llena la matriz MIS
            m = pGe2D->retornaNumeracionNodo(nd[j]);
            if (m < 0) continue;
            n = nd_s[i];
            for (l = 0; l < pGe2D->retornaNodosElemento(); l++)
            {
               if (nd[l] == nd[j]) p = l;
               if (nd[l] == i) q = l;
            }
            tp = pAGI->retorna(n,m) + pXA->retorna(p,q);
            if (tp) pAGI->asigna(n,m,tp);
         }
      }
   }

   // Visualiza la matriz de carga
#ifdef DEPURAR
   if (visualiza)
   {
      pAGI->visualiza(0);
   }
#endif

   // Libera memoria
   delete []PX;
   delete []WX;

}

// Genera la matriz de frontera interior-interiores
void DDM_SchurSubdominio::generaMatriz_AIG(void)
{

   int i, j;
   ldouble tp;

   // Solicita espacio para la matriz
   if (pPr2D->retornaCoeficientesConstantes())
   {
      pAIG = new MatrizDispersaComp(pGe2D->retornaNumeroNodosDesconocidos(),num_nodos_frontera_interior,8,"AIG");
   }
   else
   {
      pAIG = new MatrizDispersa(pGe2D->retornaNumeroNodosDesconocidos(),num_nodos_frontera_interior,8,"AIG");
   }
   if (!pAIG) cm.errorSolicitudMemoria("AIG");


   for (i = 0; i < pGe2D->retornaNumeroNodosDesconocidos(); i++)
   {
      for (j = 0; j < num_nodos_frontera_interior; j++)
      {
         tp = pAGI->retorna(j,i);
         if (tp) pAIG->asigna(i,j,tp);
      }
   }

   // Visualiza la matriz de carga
#ifdef DEPURAR
   if (visualiza)
   {
      pAIG->visualiza(0);
   }
#endif
}


// Genrea la matriz de frontera interior-frontera interior
void DDM_SchurSubdominio::generaMatriz_AGG(void)
{

   int i, j, l, n , m, k, p, q, sw;
   int el[10], nd[10], num;
   ldouble TX[NUMERO_NODOS_ELEMENTO], TY[NUMERO_NODOS_ELEMENTO], J;
   ldouble itg, tp;
   ldouble cd1[7];

//~ for (i = 0; i < num_nodos; i++)
//~ {
   //~ printf("\n  %d: %d  %d",i, nd_s[i], pGe2D->retornaNumeracionNodo(i));
//~ }
//~ printf("\n");

   // Variables para integración
   ldouble *PX = new ldouble[num_puntos_cuadratura];
   ldouble *WX = new ldouble[num_puntos_cuadratura];
   if (!PX || !WX) cm.errorSolicitudMemoria("Genera matriz AGG");
   GaussQuad integ(-1.0,1.0,num_puntos_cuadratura,PX,WX);

   // Solicita espacio para la matriz
   if (pPr2D->retornaCoeficientesConstantes())
   {
      pAGG = new MatrizDispersaComp(num_nodos_frontera_interior,num_nodos_frontera_interior,5,"AGG");
   }
   else
   {
      pAGG = new MatrizDispersa(num_nodos_frontera_interior,num_nodos_frontera_interior,5,"AGG");
   }
   if (!pAGG) cm.errorSolicitudMemoria("AGG");

   // Llena la matriz AGG
   sw = 0;
   for (i = 0; i < num_nodos; i++)
   {
      // Descarta a los nodos que no estan en frontera interior
      if (nd_s[i] < 0) continue;
      // Busca todos los elemento que contienen al nodo buscado
      num = pGe2D->retornaElementosContienenNodo(i,el,pGe2D->numeroElementosSoporteNodo());
      // realiza las integraciones sobre cada elemento que contiene al nodo
      for (k = 0; k < num; k++)
      {
         // Recupera la referencia del nodo global con respecto al nodo local
         pGe2D->retornaNodosElemento(el[k], nd, pGe2D->retornaNodosElemento());
         // Obtiene las coordenadas del elemento
         pGe2D->coordenadasElemento(el[k], TX, TY);
         pPr2D->asignarValorNodo(TX,TY);

         // Jacobiano de la transformación
#ifdef __Double__
         J = fabs( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#else
         J = fabsl( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#endif
         pPr2D->asignarValorJacobiano(J);

         // Ciclo para calcular la matriz local correspondiente al nodo local J,L
         for (j = 0; j < pGe2D->retornaNodosElemento(); j++)
         {
            // Si los coeficientes de la ecuación son constantes solo calcula una sola ves
            if (sw == 0 || (sw > 0 && !pPr2D->retornaCoeficientesConstantes()))
            {
               for (l = 0; l < pGe2D->retornaNodosElemento(); l++)
               {
                  // Calculo de la integral numerica
                  itg = 0.0;
                  for (m = 0; m < num_puntos_cuadratura; m++)
                  {
                     for (n = 0; n < num_puntos_cuadratura; n++)
                     {
                        cd1[0] = PX[m];
                        cd1[1] = PX[n];
                        itg += (WX[m] * WX[n] * pPr2D->f(cd1,j*pGe2D->retornaNodosElemento()+l)) * J;
                     }
                  }
                  pXA->asigna(j,l,itg);
               }
               sw = 1;
#ifdef DEPURAR
               if (visualiza)
               {
                  // Matriz de carga local
                  pXA->visualiza(0);
               }
#endif

            }
            // Llena la matriz AGG
            m = nd_s[nd[j]];
            if (m < 0) continue;
            n = nd_s[i];
            for (l = 0; l < pGe2D->retornaNodosElemento(); l++)
            {
               if (nd[l] == nd[j]) p = l;
               if (nd[l] == i) q = l;
            }
            tp = pAGG->retorna(n,m) + pXA->retorna(p,q);
            if (tp) pAGG->asigna(n,m, tp);
         }
      }
   }

   // Visualiza la matriz de carga
#ifdef DEPURAR
   if (visualiza)
   {
      pAGG->visualiza(0);
   }
#endif

   // Libera memoria
   delete []PX;
   delete []WX;
}



