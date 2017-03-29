//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para separar subcadenas dentro de una cadena                                       //
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




#ifndef __SEPARACADENAS_HPP__
#define __SEPARACADENAS_HPP__

#include "Cadenas.hpp"


/// Clase para separar subcadenas dentro de una cadena
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class SeparaCadenas : public Cadenas
{
private:
   // Varables usadas para separar una cadena en sus componentes indicados por un separador dado
   bool             Arreglo_inicializado;
   char           **Arreglo;
   int              Arreglo_num_columnas_maximas;
   int              Arreglo_num_columnas_encontradas;
   int              Arreglo_tamano_columna;



public:
   /// Constructor de la clase
   SeparaCadenas(void)
   {
      Arreglo = NULL;
      Arreglo_inicializado = false;
   }
   /// Destructor de la clase
   ~SeparaCadenas()
   {
      arregloLibera();
   }

   /// Libera la memoria ocupada por el arreglo
   void             arregloLibera(void);
   /// Inicializa el arreglo de trabajo
   void             arregloInicializa(const int num_col_max, const int tam);
   /// Separar una cadena en sus componentes indicados por un separador dado retornado el numero de elementos encontrado
   int              arregloSeparaElementos(const char *xcad, const char sep);
   /// Retorna los componentes de una cadena indicados por un separador dado
   char            *arregloRetornaElemento(const int in);


};

#endif



