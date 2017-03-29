
#include "CtrlParametros.hpp"
#include "Problema_2DEjemp01.hpp"
#include "Geometria_2DRectangulos.hpp"
#include "DDM_Schur.hpp"


// Ejemplo para resolver un problema en dos dimensiones mediante el método de descomposición de dominio
int main(int argc, const char *args[])
{

   // Control de parametros pasados de la linea de comandos
   CtrlParametros parm(argc, args);

   int malla_gruesa_x = parm.intVal("nx",3);
   int malla_gruesa_y = parm.intVal("ny",malla_gruesa_x);
   int malla_fina_x   = parm.intVal("mx",malla_gruesa_x);
   int malla_fina_y   = parm.intVal("my",malla_gruesa_x);
   ldouble eps        = parm.doubleVal("eps",1e-5);

   // Definicion de la geometria
   Geometria_2DRectangulos *ge = new Geometria_2DRectangulos();

   // Definicion del problema
   Problema_2DEjemp01 *pr = new Problema_2DEjemp01();
   pr->inicializa(ge,malla_gruesa_x,malla_gruesa_y);

   // Visualiza problema y geomentria
   pr->visualizaProblema();
   //~ ge->visualiza();

   // Descomposición de dominio por medio de Schur
   DDM_Schur ddm;
   ddm.inicializa(pr, ge, malla_fina_x, malla_fina_y, eps);
   ddm.resuelveDDM();
   ddm.grabaSolucion("Solucion.txt");
   //~ ddm.visualizaSolucion();
   printf("Error encontrado: %lf",ddm.error());
   printf("\n\n");

   // Borra la memoiria dinamica
   delete ge;
   delete pr;

   return 0;
}
