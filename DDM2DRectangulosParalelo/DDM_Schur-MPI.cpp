

#include "DDM_Schur-MPI.hpp"


int DDM_Schur_MPI::funPar01(int ind, Problema_2D *pr, ldouble *sub, int *par, ldouble ep)
{
   reparteCargaTrabajo(xnp, st, ind);
   msn[0] = st;
   msn[1] = ind;
   msn[2] = par[0];
   msn[3] = par[1];
   int j;
   ldouble arr[5];
   for (j = 0; j < 4; j++) arr[j] = sub[j];
   arr[4] = ep;
   MPI::COMM_WORLD.Send(&msn, 4, MPI::INT, xnp, 1);
   MPI::COMM_WORLD.Send(&arr, 5, MPI::DOUBLE, xnp, 1);

   MPI::COMM_WORLD.Recv(&msn, 1, MPI::INT, xnp,1);
   return msn[0];
}

void DDM_Schur_MPI::funPar02(int ind, ldouble **cd, int tm)
{
   reparteCargaTrabajo(xnp, st, ind);
   msn[0] = st;
   msn[1] = ind;
   msn[2] = tm;
   MPI::COMM_WORLD.Send(&msn, 3, MPI::INT, xnp, 1);

   ldouble *coord = new ldouble[2*tm];
   MPI::COMM_WORLD.Recv(coord, 2*tm, MPI::DOUBLE, xnp,1);

   int i, j = 0;
   for (i = 0; i < tm; i++)
   {
      cd[i][0] = coord[j];
      j++;
      cd[i][1] = coord[j];
      j++;
   }
   delete []coord;
}

void DDM_Schur_MPI::funPar03(int ind)
{
   reparteCargaTrabajo(xnp, st, ind);
   msn[0] = st;
   msn[1] = ind;
   MPI::COMM_WORLD.Send(&msn, 2, MPI::INT, xnp, 1);
}

void DDM_Schur_MPI::funPar04(int ind, ldouble *val1, ldouble *val2, int tm)
{
   reparteCargaTrabajo(xnp, st, ind);
   msn[0] = st;
   msn[1] = ind;
   msn[2] = tm;
   MPI::COMM_WORLD.Send(&msn, 3, MPI::INT, xnp, 1);
   MPI::COMM_WORLD.Recv(val1, tm, MPI::DOUBLE, xnp,1);
   MPI::COMM_WORLD.Recv(val2, tm, MPI::DOUBLE, xnp,1);
}

void DDM_Schur_MPI::funPar05(int ind, ldouble *val, int tm)
{
   reparteCargaTrabajo(xnp, st, ind);
   msn[0] = st;
   msn[1] = ind;
   msn[2] = tm;
   MPI::COMM_WORLD.Send(&msn, 3, MPI::INT, xnp, 1);
   MPI::COMM_WORLD.Send(val, tm, MPI::DOUBLE, xnp,1);
   MPI::COMM_WORLD.Recv(val, tm, MPI::DOUBLE, xnp,1);
}

void DDM_Schur_MPI::funPar06(int ind, ldouble *val, int tm)
{
   reparteCargaTrabajo(xnp, st, ind);
   msn[0] = st;
   msn[1] = ind;
   if (ind == 0)
   {
      msn[2] = 0;
      int i;
      for (i = 0; i < npu; i++) MPI::COMM_WORLD.Send(&msn, 3, MPI::INT, i+1, 1);
   }
   msn[2] = tm;
   MPI::COMM_WORLD.Send(&msn, 3, MPI::INT, xnp, 1);
   MPI::COMM_WORLD.Send(val, tm, MPI::DOUBLE, xnp,1);
}

void DDM_Schur_MPI::funPar07(int ind, ldouble **cd, ldouble *vl, int tm)
{
   reparteCargaTrabajo(xnp, st, ind);
   msn[0] = 1;
   msn[1] = st;
   msn[2] = ind;
   msn[3] = tm;
   MPI::COMM_WORLD.Send(&msn, 4, MPI::INT, xnp, 1);
   ldouble *coord = new ldouble[2*tm];
   ldouble *val = new ldouble[tm];
   MPI::COMM_WORLD.Recv(coord, 2*tm, MPI::DOUBLE, xnp,1);
   MPI::COMM_WORLD.Recv(val, tm, MPI::DOUBLE, xnp,1);

   int i, j = 0;
   for (i = 0; i < tm; i++)
   {
      vl[i] = val[i];
      cd[i][0] = coord[j];
      j++;
      cd[i][1] = coord[j];
      j++;
   }
   delete []coord;
   delete []val;
}





/// Sobrecarga del la aplicacion maestro
void DDM_Schur_MPI::haz(void)
{
   // Definicion del problema
   pr = new Problema_2DEjemp01();
   if (id == 0)
   {

      // Definicion de la geometria
      ge = new Geometria_2DRectangulos();

      //~ // Definicion del problema
      //~ pr = new Problema_2DEjemp01();
      pr->inicializa(ge,malla_gruesa_x,malla_gruesa_y);

      // Visualiza problema y geomentria
      pr->visualizaProblema();
      //~ ge->visualiza();

      // Descomposición de dominio por medio de Schur
      inicializa(pr, ge, malla_fina_x, malla_fina_y, eps);

      // Resualve por el metodo de descomposicion de dominio de subestructuración
      resuelveDDM();

      // Graba la solucion
      grabaSolucion("Solucion.txt");

      // Visualiza la solucion
      //visualizaSolucion();
      //~ printf("Error encontrado: %lf",error());
      //~ printf("\n\n");
      //~ fflush(stdout);

      // Finalizacion de las tareas
      msn[0] = 0;
      for (int i = 1; i < np; i++) MPI::COMM_WORLD.Send(&msn, 4, MPI::INT, i, 1);
   }
   else
   {
      if (nta) Esclavo();
      else
      {
         int sw =1;
         while (sw)
         {
            MPI::COMM_WORLD.Recv(&msn, 4, MPI::INT, 0,1);
            sw = msn[0];
         }
      }
   }
}


/// Esclavo
void DDM_Schur_MPI::Esclavo(void)
{
   int ind, i, j, k, st, sw;

   // Inicializa los subdominios
   DDM_Schur::funPar00(nta);


   // Recibe los datos para inicializar el subdominio
   for (i = 0; i < nta; i++)
   {
      ldouble arr[5];
      MPI::COMM_WORLD.Recv(&msn, 4, MPI::INT, 0, 1);
      MPI::COMM_WORLD.Recv(&arr, 5, MPI::DOUBLE, 0, 1);
      st = msn[0];
      ind = msn[1];
      int par[2];
      par[0] = msn[2];
      par[1] = msn[3];
      ldouble sub[4], ep;
      for (j = 0; j < 4; j++) sub[j] = arr[j];
      ep = arr[4];
      int nni = DDM_Schur::funPar01(st, pr, sub, par, ep);
      MPI::COMM_WORLD.Send(&nni, 1, MPI::INT, 0, 1);
   }



   // Envia las coordenadas de la frontera interior
   for (i = 0; i < nta; i++)
   {
      MPI::COMM_WORLD.Recv(&msn, 3, MPI::INT, 0, 1);
      st = msn[0];
      ind = msn[1];
      int tam = msn[2];
      ldouble **cN = cm.asignaMemoriaLDOUBLE(tam, 2, "coordenadas de la frontera interior");
      DDM_Schur::funPar02(st,cN,tam);
      ldouble *coord = new ldouble[2*tam];
      j = 0;
      for (k = 0; k < tam; k++)
      {
         coord[j] = cN[k][0];
         j++;
         coord[j] = cN[k][1];
         j++;
      }
      cm.liberaMemoriaLDOUBLE(tam,cN);
      MPI::COMM_WORLD.Send(coord, 2*tam, MPI::DOUBLE, 0, 1);
      delete []coord;
   }



   // Genera las matrices
   for (i = 0; i < nta; i++)
   {
      MPI::COMM_WORLD.Recv(&msn, 2, MPI::INT, 0, 1);
      st = msn[0];
      ind = msn[1];
      DDM_Schur::funPar03(st);
   }


   // Envia el vector de carga
   for (i = 0; i < nta; i++)
   {
      MPI::COMM_WORLD.Recv(&msn, 3, MPI::INT, 0, 1);
      st = msn[0];
      ind = msn[1];
      int tam = msn[2];
      ldouble *pXU  = cm.asignaMemoriaLDOUBLE(tam,"Valores intermedios de la solucion");
      ldouble *pxXU = cm.asignaMemoriaLDOUBLE(tam,"Valores intermedios de la solucion");
      DDM_Schur::funPar04(st,pXU, pxXU, tam);
      MPI::COMM_WORLD.Send(pXU, tam, MPI::DOUBLE, 0, 1);
      MPI::COMM_WORLD.Send(pxXU, tam, MPI::DOUBLE, 0, 1);
      cm.liberaMemoriaLDOUBLE(pXU);
      cm.liberaMemoriaLDOUBLE(pxXU);
   }

   // Iteraciones del CGM
   sw = 1;
   while (sw)
   {
      for (i = 0; i < nta; i++)
      {
         MPI::COMM_WORLD.Recv(&msn, 3, MPI::INT, 0, 1);
         st = msn[0];
         ind = msn[1];
         int tam = msn[2];
         if (tam == 0)
         {
            sw = 0;
            break;
         }
         ldouble *var  = cm.asignaMemoriaLDOUBLE(tam,"Valores intermedios de la solucion");
         MPI::COMM_WORLD.Recv(var, tam, MPI::DOUBLE, 0, 1);
         DDM_Schur::funPar05(st, var, tam);
         MPI::COMM_WORLD.Send(var, tam, MPI::DOUBLE, 0, 1);
         cm.liberaMemoriaLDOUBLE(var);
      }
   }


   // Resuelve nodos interiores
   for (i = 0; i < nta; i++)
   {
      MPI::COMM_WORLD.Recv(&msn, 3, MPI::INT, 0, 1);
      st = msn[0];
      ind = msn[1];
      int tam = msn[2];
      ldouble *var  = cm.asignaMemoriaLDOUBLE(tam,"Valores intermedios de la solucion");
      MPI::COMM_WORLD.Recv(var, tam, MPI::DOUBLE, 0, 1);
      DDM_Schur::funPar06(st, var, tam);
      cm.liberaMemoriaLDOUBLE(var);
   }




   sw = 1;
   while (sw)
   {
      MPI::COMM_WORLD.Recv(&msn, 4, MPI::INT, 0, 1);
      sw = msn[0];
      switch (sw)
      {
      case 1:
      {
         // Envia las coordenadas y la solucion del subdominio
         for (i = 0; i < nta; i++)
         {
            st = msn[1];
            ind = msn[2];
            int tam = msn[3];
            ldouble *val = new ldouble[tam];
            ldouble **cN = cm.asignaMemoriaLDOUBLE(tam, 2, "coordenadas subdominio");
            DDM_Schur::funPar07(st,cN,val,tam);
            ldouble *coord = new ldouble[2*tam];
            j = 0;
            for (k = 0; k < tam; k++)
            {
               coord[j] = cN[k][0];
               j++;
               coord[j] = cN[k][1];
               j++;
            }
            cm.liberaMemoriaLDOUBLE(tam,cN);
            MPI::COMM_WORLD.Send(coord, 2*tam, MPI::DOUBLE, 0, 1);
            MPI::COMM_WORLD.Send(val, tam, MPI::DOUBLE, 0, 1);
            delete []coord;
            delete []val;
         }
         break;
      }
      }
   }
   for (i = 0; i < nta; i++) DDM_Schur::funPar09(i);
}






