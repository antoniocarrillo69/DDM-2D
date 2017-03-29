//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para generar una geometría homogénea en dos dimensiones usando rectángulos         //
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



#ifndef __Geometria_2DRectangulos__
#define __Geometria_2DRectangulos__

#define NUMERO_NODOS_ELEMENTO 4


#include "Geometria_2D.hpp"



/// Clase para generar una geometría homogénea en dos dimensiones usando rectángulos
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Geometria_2DRectangulos : public Geometria_2D
{

public:

   /// Constructor de la clase
   /** @param x1 Coordenada X del inicio del dominio
       @param y1 Coordenada Y del inicio del dominio
       @param x2 Coordenada X del fin del dominio
       @param y2 Coordenada Y del fin del dominio
       @param part_hor Partición en X
       @param part_ver Partición en Y */
   Geometria_2DRectangulos(ldouble x1, ldouble y1, ldouble x2, ldouble y2, int part_hor, int part_ver) : Geometria_2D()
   {
      inicializa(x1,y1,x2,y2,part_hor,part_ver);
   }


   /// Constructor de la clase
   /** @param dm Dominio
       @param part_hor Partición en X
       @param part_ver Partición en Y */
   Geometria_2DRectangulos(MatrizDensa *dm, int part_hor, int part_ver) : Geometria_2D()
   {
      inicializa(dm,part_hor,part_ver);
   }

   /// Constructor de la clase
   /** @param arch Nombre del archivo que contiene la geometria */
   Geometria_2DRectangulos(const char *arch) : Geometria_2D()
   {
      // Dimension 1D
      DIM = 2;
      // Numero de nodos por elemento
      NNE = 4;
      // Numero máximo de elementos que son soporte de un nodo
      NMESN = 4;

      leeGeometria(arch);
   }

   /// Constructor de la clase
   Geometria_2DRectangulos(void) : Geometria_2D()
   {
      // Dimension 1D
      DIM = 2;
      // Numero de nodos por elemento
      NNE = 4;
      // Numero máximo de elementos que son soporte de un nodo
      NMESN = 4;
   }

   /// Inicializa los datos de la geometría
   /** @param x1 Coordenada X del inicio del dominio
       @param y1 Coordenada Y del inicio del dominio
       @param x2 Coordenada X del fin del dominio
       @param y2 Coordenada Y del fin del dominio
       @param part_hor Partición en X
       @param part_ver Partición en Y */
   void inicializa(ldouble x1, ldouble y1, ldouble x2, ldouble y2, int part_hor, int part_ver)
   {
      // Dimension 2
      DIM = 2;
      // Numero de nodos por elemento
      NNE = 4;
      // Numero máximo de elementos que son soporte de un nodo
      NMESN = 4;
      // Numero de rectangulos
      N_E = part_hor * part_ver;
      // Numero de nodos
      N_N = (part_hor + 1) * (part_ver +1);
      // Almacena valores
      Dominio.asigna(0,0,x1);
      Dominio.asigna(0,1,y1);
      Dominio.asigna(1,0,x2);
      Dominio.asigna(1,1,y2);

      Particion.asigna(0,part_hor);
      Particion.asigna(1,part_ver);

      generaGeometria();
   }

   /// Inicializa los datos de la geometría
   /** @param dm Dominio
       @param part_hor Partición en X
       @param part_ver Partición en Y */
   void inicializa(MatrizDensa *dm, int part_hor, int part_ver)
   {
      // Dimension 2
      DIM = 2;
      // Numero de nodos por elemento
      NNE = 4;
      // Numero máximo de elementos que son soporte de un nodo
      NMESN = 4;
      // Numero de rectangulos
      N_E = part_hor * part_ver;
      // Numero de nodos
      N_N = (part_hor + 1) * (part_ver +1);
      // Almacena valores
      dm->copia(&Dominio);

      Particion.asigna(0,part_hor);
      Particion.asigna(1,part_ver);

      generaGeometria();
   }

   /// Genera la geometria
   void generaGeometria(void);

   /// Regresa el valor del área del elemento
   /** @return Area del elemento */
   ldouble areaElemento(int el)
   {
      return 0.0;
   }

};

#endif


//~ /// Retorna el numero de nodo del elemento
//~ inline void Retorna_Numero_Nodo(int elemento, int &nd1, int &nd2, int &nd3, int &nd4)
//~ {
//~ nd1 = EL->Retorna(elemento,0);
//~ nd2 = EL->Retorna(elemento,1);
//~ nd3 = EL->Retorna(elemento,2);
//~ nd4 = EL->Retorna(elemento,3);
//~ }
