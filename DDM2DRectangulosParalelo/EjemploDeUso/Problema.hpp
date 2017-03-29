//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para definir un problema                                                      //
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



#ifndef __Problema__
#define __Problema__

// Tipos de frontera definida
#define DIRICHLET 1
#define NEUMANN   2

// Indica la la frontera incluye a los nodos o no
#define FRONTERA_CON_NODOS 0
#define FRONTERA_SIN_NODOS 1

// Solución análitica disponible
#define SOLUCION_ANALITICA_DISPONIBLE    true
#define SOLUCION_ANALITICA_NO_DISPONIBLE false


#include "Definiciones.hpp"
#include "MatrizDensa.hpp"
#include "VectorInt.hpp"


/// Clase base para definir un problema
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Problema
{

protected:

   /// Dominio del problema
   MatrizDensa Dominio;
   /// Tipo de frontera
   VectorInt TipoFrontera;
   /// Alcance de frontera
   VectorInt Alcance_frontera;
   /// Tiempo
   ldouble T;
   /// Tiempo inicial
   ldouble Ti;
   /// tiempo final
   ldouble Tf;


   /// Solución análitica disponible
   bool Solucion_analitica;
   /// Coeficientes constantes
   bool Coeficientes_constantes;
   /// Matriz simetrica
   bool Matriz_simetrica;
   /// Coeficientes constantes en el tiempo
   bool Coeficientes_constante_en_tiempo;


public:

   /// Constructor de la clase
   Problema(void)
   {
      // Inicialización por omisión
      Coeficientes_constantes = false;
      Matriz_simetrica = false;
      Coeficientes_constante_en_tiempo = false;
      Ti = Tf = T = 0.0;
   }

   /// Retorna el dominio
   void retornaDominio(MatrizDensa *dom)
   {
      Dominio.copia(dom);
   }

   /// Retorna la solucion exacta
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @return Valor de la solución */
   virtual ldouble solucionExacta(ldouble *x) = 0;

   /// Discretizacion de la ecuacion
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @param di Banda solicitada
       @return Valor de la función */
   virtual ldouble f(ldouble *x, int di) = 0;

   /// Lado derecho de la ecuacion
   virtual double ladoDerecho(ldouble *x) = 0;

   /// Valor en la frontera X = X0
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @param fr Número de frontera
       @return Valor en la frontera */
   virtual ldouble condicionesFrontera(ldouble *x, int fr) = 0;

   /// Valor en la frontera X = X0
   /** @param fr Número de frontera
       @return Tipo de frontera DIRICHLET o NEUMANN*/
   int tipoCondicionFrontera(int fr)
   {
      return TipoFrontera.retorna(fr);
   }

   /// Alcance de la frontera
   /** @param fr Número de frontera
       @return Alcance de frontera FRONTERA_CON_NODOS o FRONTERA_SIN_NODOS */
   int retornaAlcanceFrontera(int fr)
   {
      return Alcance_frontera.retorna(fr);
   }

   /// Visualiza la definicion del problema
   virtual void visualizaProblema(void) = 0;

   /// Retorna si hay solicion analitica disponible
   /** @return Retorna SOLUCION_ANALITICA_DISPONIBLE o de lo contrario SOLUCION_ANALITICA_NO_DISPONIBLE */
   inline bool haySolucionAnalitica(void)
   {
      return Solucion_analitica;
   }

   /// Retorna si los coeficientes son constantes en la ecuación
   /** @return Retorna true o de lo contrario false si los coeficientes son constantes en la ecuación */
   inline bool retornaCoeficientesConstantes(void)
   {
      return Coeficientes_constantes;
   }

   /// Retorna el tiempo inicial del problema
   /** @return Tiempo inicial */
   inline bool tiempoInicial(void)
   {
      return Ti;
   }

   /// Retorna el tiempo final del problema
   /** @return Tiempo inicial */
   inline bool tiempoFinal(void)
   {
      return Tf;
   }

   /// Establece el valor del tiempo
   /** @param t Tiempo */
   void estableceTiempo(int t)
   {
      T = t;
   }

};

#endif

