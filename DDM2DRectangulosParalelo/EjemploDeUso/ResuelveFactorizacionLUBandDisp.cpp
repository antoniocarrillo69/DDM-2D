//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal usando factorizacion LU                            //
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


#include "ResuelveFactorizacionLUBandDisp.hpp"


// Factoriza la matriz A en L y U dejandolas en la misma matriz
void ResuelveFactorizacionLUBandDisp::factoriza(void)
{
#ifdef DEPURAR
   if (!M->matrizCuadrada())
   {
      printf("\nError al factorizar por LU, matriz no cuadrada\n\n");
      exit(1);
   }
#endif

   int i, j, k, ind, xcol, ind1, xcol1;
   ldouble m;


   for (i = 0; i < M->renglones(); i++)
   {
#ifdef DEPURAR
      if (M->retorna(i,i) == 0.0)
      {
         printf("\nError al factorizar el sistema en LU\n");
         exit(1);
      }
#endif
      xcol1 = M->retornaNumeroColumnasBanda(i);
      for (ind1 = 0; ind1 < xcol1; ind1++)
      {
         j = M->retornaNumeroColumna(i,ind1);
         if (j < i+1) continue;

         m = M->retornaValorColumna(i,ind1) / M->retorna(i,i);
         M->asigna(j, i, m);

         xcol = M->retornaNumeroColumnasBanda(i);
         for (ind = 0; ind < xcol; ind++)
         {
            k = M->retornaNumeroColumna(i,ind);
            if (k < i+1) continue;
            M->asigna(j, k, M->retorna(j,k) - m * M->retornaValorColumna(i,ind) );
         }
      }
   }
   MatrizFactorizada = true;
}


// Resuelve el sistema lineal
void ResuelveFactorizacionLUBandDisp::resuelve(void)
{
   if (!MatrizFactorizada) factoriza();

   int i, j, n, ind, xcol;
   ldouble t;
   n = M->renglones();

   Vector *y = new Vector(n);

   // Resuelve el sistema LY=B, dados L y B
   y->asigna(0,  B->retorna(0) / M->retorna(0,0) );
   for (i = 0; i < n; i++)
   {
      t = B->retorna(i);

      xcol = M->retornaNumeroColumnasBanda(i);
      for (ind = 0; ind < xcol ; ind++)
      {
         j = M->retornaNumeroColumna(i,ind);
         if (j >= i) continue;
         t -= M->retornaValorColumna(i,ind) * y->retorna(j);
      }
      y->asigna(i, t);
   }

   // Resuelve el sistema UX=Y, dados U  y Y
   X->asigna(n - 1, y->retorna(n - 1) / M->retorna(n - 1, n-1) );
   for (i = (n - 2); i >= 0; i--)
   {
      t = y->retorna(i);

      xcol = M->retornaNumeroColumnasBanda(i);
      for (ind = 0; ind < xcol; ind++)
      {
         j = M->retornaNumeroColumna(i,ind);
         if (j <= i || j > (n-1)) continue;
         t -= M->retornaValorColumna(i,ind) * X->retorna(j);
      }

      X->asigna(i, t / M->retorna(i,i) );
   }

   delete y;
}
