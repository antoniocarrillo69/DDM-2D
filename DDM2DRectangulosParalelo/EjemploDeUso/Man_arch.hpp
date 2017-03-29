//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para manipulación de archivos                                                      //
// Revisión: 3 de Noviembre del 2003                                                        //
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



#ifndef __man_arch_hpp__
#define __man_arch_hpp__

#include <stdio.h>
#include <stdlib.h>
#include "SeparaCadenas.hpp"
#include "Definiciones.hpp"


#define LEE_ARCHIVO       0
#define GRABA_ARCHIVO     1
#define ADICIONA_ARCHIVO  2


/// Clase manipuladora del manipulador de archivos
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Manipulador_archivos: virtual public SeparaCadenas
{
private:

   /// Guarda el modo de apertura del archivo
   unsigned int     MODO:              2;
   /// Variable que indica el Estado del objeto
   int              Estado;
   /// Variable de caracter temporal
   char             car;
   /// Indica la longitud maxima de la cadena a trabajar
   unsigned int     LG_MAX;
   /// Variables temporal
   int              inttmp;
   long             longtmp;
   unsigned int     uinttmp;
   unsigned char    cartmp;
   char             xcad[1000];

   /// Puntero al archivo generado como reporte
   FILE            *ARCHIVO_TRABAJO;
   /// Nombre del archivo a trabajar
   char            *ARCHIVO;
   /// Nombre de la rutina que llama al manipulador de archivos
   char            *RUTINA;
   /// Contiene el delimitador entre lineas
   char            *DELIMITADOR;


public:

   /// Costructor de la clase
   Manipulador_archivos(void);
   /// Destructor de la clase
   ~Manipulador_archivos();

   /// Parametros para el manipulador de archivos
   void parametros(const char *archivo, const int modo, const unsigned int lg_max, const char *rutina = "");

   /// Cierra el acceso al puntero del archivo
   void cerrar(void);

   /// Longitud máxima del texto
   void cambiaLongitudMaximaTexto(const int lg)
   {
      LG_MAX = lg;
   }

   /// Cuenta el numero de caracteres y lineas dentro del archivo si T_P es (1) combierte tabuladores en TABULADOR espacios y no tome en cuenta el caracter 13, si T_P es (0) cuenta la cantidad de caracteres reales
   void longitudArchivo(long &lg_archivo, long &nm_lineas, const int t_p);

   /// Actualiza la longitud máxima de la cadena a trabajar
   unsigned int longitudMaximaLinea(void);

   /// Lee la siguiente linea del archivo, retornando la longitud de la linea
   unsigned int leeLinea(char *cadena);

   /// Graba una cadena como una linea del archivo, retornando la longitud de esta
   unsigned int grabaLinea(const char *cadena);

   /// Graba una cambio de nueva linea
   void grabaNuevaLinea(void);

   /// Se posiciona en la linea indicada por LINEA
   unsigned int buscaLinea(const unsigned int linea);

   /// Lee el numero de caracteres indicados en N_C y los deja en la cadena CADENA, retornando  el numero de caracteres leidos
   unsigned int leeCaracteres(char *cadena, const unsigned int n_c);

   /// Graba una una cadena de caracteres, retornando el numero de caracteres grabados
   unsigned int grabaCaracteres(const char *cadena, const unsigned int n_c);

   /// Lee un entero
   void leeEntero(int &num);

   /// Lee un entero sin signo
   void leeEntero(unsigned int &num);

   /// Lee un carcater sin signo
   void leeCaracter(char &num);

   /// Lee un entero largo
   void leeEnteroLargo(long &num);

   /// Lee un flotante double
   void leeDouble(double &num);

   /// Lee un flotante long double
   void leeLdouble(long double &num);

   /// Graba un entero
   void grabaEntero(const int ent);

   /// Graba un entero sin signo
   void grabaEntero(const unsigned int ent);

   /// Graba un caracter sin signo
   void grabaCaracter(const char car);

   /// Graba un entero largo
   void grabaEnteroLargo(const long ent);

   /// Graba un flotante double
   void grabaDouble(const double num);

   /// Graba un flotante long double
   void grabaLdouble(const long double num);

   /// Debuelve el Estado del manipulador de archivos
   int  retornaEstado(void) const
   {
      return Estado;
   }

   /// Posiciona al indicador del archivo en el inicio de este
   void inicioArchivo(void)
   {
      Estado = 0;
      rewind(ARCHIVO_TRABAJO);
   }



   /// Copia el archivo indicado como fuente al archivo objeto
   int  copiaArchivo(const char *archivo_fuente, const char *archivo_objeto);

   /// Concatena el archivo indicado como fuente al archivo objeto
   int  concatenaArchivo(const char *archivo_fuente, const char *archivo_objeto);

   /// Remueve el archivo especificado en el path, en caso de tener permisos de solo lectura y/o oculto son cambiados a archivo normal. Despues de borra el archivo, si tp es (1) reescribe este para evitar su recuperación.
   int  remueveArchivo(const char *arch, const int tp);

   /// Renombra el archivo indicado como fuente al archivo objeto
   int  renombraArchivo(const char *archivo_fuente, const char *archivo_objeto);

   /// Retorna un nombre de archivo con extención EXT
   void cambiaExtPath(const char *path, const char *ext, char *pathmod);

   /// Retorna un nombre de archivo con extención EXT
   void cambiaExtPath(char *path, const char *ext);

   /// Construye una trayectoria
   void construyeTrayectoria(const char *tray, const char *arch, const char *ext, char *xpath);

   /// Adiciona a una cadena con terminador nulo los caracteres LF y LN
   void construyeTrayectoria(const char *tray, const char *arch, char *xpath);

   /// Adiciona a una cadena con terminador nulo los caracteres LF y LN
   void convierteLinea(char *xcad);

   /// Ajusta el nombre de archivo para visualizacion a la longitud indicada
   void ajustaNombreArchivo(const char *cad, char *xcad, unsigned int lg);



   /// Graba el contenido de los arreglos X vs Y
   void graba(ldouble *x, ldouble *y, int n);

   /// Graba el contenido de los arreglos X vs Y y Z
   void graba(ldouble *x, ldouble *y, ldouble *z, int n);

   /// Graba X vs Y
   void graba(ldouble x, ldouble y);

   /// Graba X vs Y y Z
   void graba(ldouble x, ldouble y, ldouble z);

   /// Graba el punto x con los n valores del vector y en una misma linea
   void graba(ldouble x, ldouble *y, int n);

   /// Interpola num valores con los dados
   void interpolaGraba(ldouble *x, ldouble *y,  int n, int num);

   /// Interpola num valores con los dados
   void interpolaGraba(ldouble x1, ldouble y1, ldouble x2, ldouble y2, int num);

   /// Busca el maximo y el mínimo de los valores del arreglo X
   void buscaMaxMin(ldouble *x, int n, ldouble &min, ldouble &max);

   void error(const char *cad)
   {
      printf("\nError: %s", cad);
      exit(1);
   }

};

#endif


