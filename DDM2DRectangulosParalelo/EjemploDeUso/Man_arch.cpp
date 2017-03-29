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





#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "Man_arch.hpp"

#ifndef __PROGRAMACION_BORLAND__
#include <unistd.h>
#define MAXPATH   1024
#else
#include <io.h>
#include <string.h>
#define W_OK      06
#define R_OK      04
#endif





#define TABULADOR    8



// Posibles estados del manipulador de archivos
// (0)   Sin errores
// (2)   Fin de archivo
// (80)  No se puede leer el archivo
// (81)  No se puede leer y grabar sobre el archivo
// (97)  Error al abrir
// (98)  Error al leer
// (99)  Error al grabar

// Constructor del manipulador de archivos
Manipulador_archivos::Manipulador_archivos(void)
{
   Estado = 0;
   DELIMITADOR = asignaPuntero(4);
   DELIMITADOR[0] = 13;
   DELIMITADOR[1] = 10;
   DELIMITADOR[2] = 0;
   ARCHIVO = NULL;
   RUTINA = NULL;
   ARCHIVO_TRABAJO = NULL;
}


// Destructor del manipulador de archivos
Manipulador_archivos::~Manipulador_archivos()
{
   // Cierra el archivo de trabajo
   cerrar();
   delete []ARCHIVO;
   ARCHIVO = NULL;
   delete []RUTINA;
   RUTINA = NULL;
   delete []DELIMITADOR;
   DELIMITADOR = NULL;
   Estado = 0;
}

// Cierra el acceso al puntero del archivo
void Manipulador_archivos::cerrar(void)
{
   if (ARCHIVO_TRABAJO)
   {
      fflush(ARCHIVO_TRABAJO);
      fclose(ARCHIVO_TRABAJO);
   }
   ARCHIVO_TRABAJO = NULL;
}


// constructor del manipulador de archivos
void Manipulador_archivos::parametros(const char *archivo, const int modo, const unsigned int lg_max, const char *rutina)
{
   MODO = modo;
   LG_MAX = lg_max;

   ARCHIVO = asignaPuntero(archivo);
   RUTINA  = asignaPuntero(rutina);
   // Establece el tipo de atributo para apertura del archivo
   char ATRIBUTO[10];
   if (MODO == LEE_ARCHIVO)      strcpy(ATRIBUTO,"rb");
   if (MODO == GRABA_ARCHIVO)    strcpy(ATRIBUTO,"wb");
   if (MODO == ADICIONA_ARCHIVO) strcpy(ATRIBUTO,"ab");   // "ab+"
   // Si no encuentra el archivo y el modo es de lectura manda mesage de error
   if (MODO == LEE_ARCHIVO)
   {
      if (access(ARCHIVO,R_OK))
      {
         Estado = 80;
         error("No se puede leer el archivo");
      }
   }
   if (MODO == ADICIONA_ARCHIVO)
   {
      // Revisa si se puede escribir y leer el archivo
      if (access(ARCHIVO,W_OK))
      {
         Estado = 81;
         error("No se puede leer y grabar sobre el archivo");
      }
   }

   if (!Estado)
   {
      // Apertura del archivo
      ARCHIVO_TRABAJO = fopen(ARCHIVO,ATRIBUTO);
      if (!ARCHIVO_TRABAJO)
      {
         Estado = 97;
         error("Error al abrir");
      }
   }
}


// Cuenta el numero de caracteres y lineas dentro del archivo si T_P es (1) combierte tabuladores en TABULADOR espacios y no tome en cuenta el caracter 13, si T_P es (0) cuenta la cantidad de caracteres reales
void Manipulador_archivos::longitudArchivo(long &lg_archivo, long &nm_lineas, const int t_p)
{
   lg_archivo = nm_lineas = 1;
   rewind(ARCHIVO_TRABAJO);
   while (!feof(ARCHIVO_TRABAJO))
   {
      car = (char)fgetc(ARCHIVO_TRABAJO);
      if (feof(ARCHIVO_TRABAJO)) break;
      if (ferror(ARCHIVO_TRABAJO))
      {
         Estado = 98;
         error("Error al leer");
      }
      if (t_p)
      {
         if (car == 13) continue;
         if (car == 9)
         {
            lg_archivo += TABULADOR;
            continue;
         }
      }
      if (car == 10) nm_lineas ++;
      lg_archivo++;
   }
   rewind(ARCHIVO_TRABAJO);
   Estado = 0;
}


// Retorna la longitud máxima de la linea contenida en el archivo
unsigned int Manipulador_archivos::longitudMaximaLinea(void)
{

   unsigned int longtmp = 0, lg_max = 0;
   rewind(ARCHIVO_TRABAJO);

   while (!feof(ARCHIVO_TRABAJO))
   {
      car = (char)fgetc(ARCHIVO_TRABAJO);
      if (feof(ARCHIVO_TRABAJO)) break;
      if (ferror(ARCHIVO_TRABAJO))
      {
         Estado = 98;
         error("Error al leer");
      }
      if (car == 13) continue;
      if (car == 9)
      {
         longtmp += TABULADOR;
         continue;
      }
      if (car == 10)
      {
         if (longtmp >= lg_max) lg_max = longtmp;
         longtmp = 0;
         continue;
      };
      longtmp++;
   }
   rewind(ARCHIVO_TRABAJO);
   Estado = 0;
   return lg_max;
}



// Lee la siguiente linea del archivo, retornando la longitud de la linea
unsigned int Manipulador_archivos::leeLinea(char *cadena)
{
   unsigned int longtmp = 0;
   while (!feof(ARCHIVO_TRABAJO))
   {
      car = (char)fgetc(ARCHIVO_TRABAJO);
      if (feof(ARCHIVO_TRABAJO))
      {
         Estado = 2;  // Fin de archivo
         break;
      }
      if (ferror(ARCHIVO_TRABAJO))
      {
         Estado = 98;
         error("Error al leer");
      }
      if (car == 13) continue;
      if (car == 10 || longtmp >= LG_MAX) break;
      if (car == 9)
      {
         if (longtmp + TABULADOR < LG_MAX)
         {
            for (int i = 0; i < TABULADOR; i++) *cadena = 32, cadena++;
            longtmp += TABULADOR;
            continue;
         }
         else break;
      }
      *cadena = car, cadena++, longtmp++;
   }
   *cadena = 0;
   return longtmp;
}


// Graba una cadena como una linea del archivo, retornando la longitud de esta
unsigned int Manipulador_archivos::grabaLinea(const char *cadena)
{
   size_t inttmp, longtmp = 0;
   inttmp = strlen(cadena);
   if (inttmp) longtmp = fwrite(cadena,1,inttmp,ARCHIVO_TRABAJO);
   fwrite(DELIMITADOR,1,2,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
   return longtmp;
}

// Graba una cambio de nueva linea
void Manipulador_archivos::grabaNuevaLinea(void)
{
   fwrite(DELIMITADOR,1,2,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
}


// Busca un numero de linea determinado en el archivo
unsigned int Manipulador_archivos::buscaLinea(const unsigned int linea)
{
   unsigned int longtmp = 1;
   rewind(ARCHIVO_TRABAJO);
   if (linea < 2) return 1;
   while (!feof(ARCHIVO_TRABAJO))
   {
      car =(char)fgetc(ARCHIVO_TRABAJO);
      if (ferror(ARCHIVO_TRABAJO))
      {
         Estado = 98;
         error("Error al leer");
      }
      if (car == 10)
      {
         if (longtmp >= linea) break;
         else longtmp++;
      }
   }
   if (feof(ARCHIVO_TRABAJO)) Estado = 2;  // Fin de archivo
   return longtmp;
}




// Lee el numero de caracteres indicados en N_C y los deja en la cadena CADENA, retornando  el numero de caracteres leidos
unsigned int Manipulador_archivos::leeCaracteres(char *cadena, const unsigned int n_c)
{
   unsigned int longtmp = fread(cadena,1,(unsigned int) n_c,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 98;
      error("Error al leer");
   }
   if (feof(ARCHIVO_TRABAJO)) Estado = 2;  // Fin de archivo
   return longtmp;
}


// Graba una una cadena de caracteres, retornando el numero de caracteres grabados
unsigned int Manipulador_archivos::grabaCaracteres(const char *cadena, const unsigned int n_c)
{
   unsigned int longtmp = fwrite(cadena,1,n_c,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
   return longtmp;
}


// Lee un entero
void Manipulador_archivos::leeEntero(int &num)
{
   fread(&inttmp,sizeof(inttmp),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 98;
      error("Error al leer");
   }
   if (feof(ARCHIVO_TRABAJO)) Estado = 2;  // Fin de archivo
   num = inttmp;
}

// Lee un entero sin signo
void Manipulador_archivos::leeEntero(unsigned int &num)
{
   fread(&uinttmp,sizeof(uinttmp),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 98;
      error("Error al leer");
   }
   if (feof(ARCHIVO_TRABAJO)) Estado = 2;  // Fin de archivo
   num = uinttmp;
}

// Lee un caracter sin signo
void Manipulador_archivos::leeCaracter(char &car)
{
   fread(&cartmp,1,1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 98;
      error("Error al leer");
   }
   if (feof(ARCHIVO_TRABAJO)) Estado = 2;  // Fin de archivo
   car = cartmp;
}


// Lee un entero largo
void Manipulador_archivos::leeEnteroLargo(long &num)
{
   fread(&longtmp,sizeof(longtmp),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 98;
      error("Error al leer");
   }
   if (feof(ARCHIVO_TRABAJO)) Estado = 2;  // Fin de archivo
   num = longtmp;
}

// Lee un flotante double
void Manipulador_archivos::leeDouble(double &num)
{
   fread(&num,sizeof(num),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 98;
      error("Error al leer");
   }
   if (feof(ARCHIVO_TRABAJO)) Estado = 2;  // Fin de archivo
}


// Lee un flotante double
void Manipulador_archivos::leeLdouble(long double &num)
{
   fread(&num,sizeof(num),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 98;
      error("Error al leer");
   }
   if (feof(ARCHIVO_TRABAJO)) Estado = 2;  // Fin de archivo
}




// Graba un entero
void Manipulador_archivos::grabaEntero(const int ent)
{
   fwrite(&ent,sizeof(ent),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
}

// Graba un entero largo
void Manipulador_archivos::grabaEnteroLargo(const long ent)
{
   fwrite(&ent,sizeof(ent),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
}


// Graba un entero sin signo
void Manipulador_archivos::grabaEntero(const unsigned int ent)
{
   fwrite(&ent,sizeof(ent),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
}

// Graba caracter sin signo
void Manipulador_archivos::grabaCaracter(const char car)
{
   fwrite(&car,1,1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
}

// Graba un flotante double
void Manipulador_archivos::grabaDouble(const double num)
{
   fwrite(&num,sizeof(num),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
}

// Graba un flotante long double
void Manipulador_archivos::grabaLdouble(const long double num)
{
   fwrite(&num,sizeof(num),1,ARCHIVO_TRABAJO);
   if (ferror(ARCHIVO_TRABAJO))
   {
      Estado = 99;
      error("Error al grabar");
   }
}

#define LG_BUFF 10240
// Copia el archivo indicado como fuente al archivo objeto
// Retornando (0) Termino satisfactoriamente
//            (1) Error apertura de archivo fuente
//            (2) Error apertura de archivo objeto
int Manipulador_archivos::copiaArchivo(const char *archivo_fuente, const char *archivo_objeto)
{
   unsigned int lg;
   Manipulador_archivos Arc_lect;
   Arc_lect.parametros(archivo_fuente,LEE_ARCHIVO,LG_BUFF,"COPIA ARCHIVO");
   if (Arc_lect.retornaEstado())
   {
      error("Error apertura de archivo fuente");
      return 1;
   }

   Manipulador_archivos Arc_grab;
   Arc_grab.parametros(archivo_objeto,GRABA_ARCHIVO,LG_BUFF,"COPIA ARCHIVO");
   if (Arc_grab.retornaEstado())
   {
      error("Error apertura de archivo objeto");
      return 2;
   }

   char *buff = asignaPuntero(LG_BUFF+3);
   while (Arc_lect.retornaEstado() != 2)
   {
      lg = Arc_lect.leeCaracteres(buff,LG_BUFF);
      Arc_grab.grabaCaracteres(buff,lg);
   }
   delete []buff;
   return 0; // Termino satisfactoriamente
}


// Concatena el archivo indicado como fuente al archivo objeto
// Retornando (0) Termino satisfactoriamente
//            (1) Error apertura de archivo fuente
//            (2) Error apertura de archivo objeto
int Manipulador_archivos::concatenaArchivo(const char *archivo_fuente, const char *archivo_objeto)
{
   unsigned int lg;
   Manipulador_archivos Arc_lect;
   Arc_lect.parametros(archivo_fuente,LEE_ARCHIVO,LG_BUFF,"CONCATENA ARCHIVO");
   if (Arc_lect.retornaEstado())
   {
      error("Error apertura de archivo fuente");
      return 1;
   }

   Manipulador_archivos Arc_grab;
   Arc_grab.parametros(archivo_objeto,ADICIONA_ARCHIVO,LG_BUFF,"CONCATENA ARCHIVO");
   if (Arc_grab.retornaEstado())
   {
      error("Error apertura de archivo objeto");
      return 2;
   }


   char *buff = asignaPuntero(LG_BUFF+3);
   while (Arc_lect.retornaEstado() != 2)
   {
      lg = Arc_lect.leeCaracteres(buff,LG_BUFF);
      Arc_grab.grabaCaracteres(buff,lg);
   }
   delete []buff;
   return 0; // Termino satisfactoriamente
}

// Remueve el archivo especificado en el path, en caso de tener permisos de solo lectura es cambiado a archivo normal. Despues de borra el archivo, si tp es distinto de cero reescribe este para evitar su recuperación.
// Retornando (0) Termino satisfactoriamente
//            (1) No existe el archivo
//            (2) No se puede borrar el archivo
int Manipulador_archivos::remueveArchivo(const char *arch, const int tp)
{
   int st = 0;

   // Reescribe el archivo para evitar su recuperación
   if (tp)
   {
      char msg[] = "Error no se puede borrar el archivo:";
      int handle = creat(arch,O_CREAT);
      if (handle >= 0)
      {
         write(handle,msg,strlen(msg));
         close(handle);
      }
   }
   // Revisa si existe el archivo
   if (!access(arch,R_OK))
   {
      // Revisa si tiene permiso para ser borrado
      if (access(arch,W_OK)) chmod(arch, S_IWRITE);
      // Borra el archivo
      if (unlink(arch)) st = 2; // no se puede borrar el archivo
   }
   else st = 1; // No existe el archivo
   return st;
}

// Renombra el archivo indicado como fuente al archivo objeto
// Retornando (0) Termino satisfactoriamente
//            (1) No pudo duplicar el archivo
int Manipulador_archivos::renombraArchivo(const char *archivo_fuente, const char *archivo_objeto)
{
   if (!copiaArchivo(archivo_fuente, archivo_objeto))
   {
      if (!remueveArchivo(archivo_fuente, 0)) return 0; // termino correctamente
   }
   return 1; // No pudo duplicar el archivo
}


// Retorna un nombre de archivo con extención EXT
// La extención no incluye el punto
void Manipulador_archivos::cambiaExtPath(const char *path, const char *ext, char *pathmod)
{
   char xpath[MAXPATH];
   int lg = trim(path,xpath) -1;
   while (lg)
   {
      if (xpath[lg] != '.')
      {
         if (xpath[lg] == '\\' || xpath[lg] == ':' || xpath[lg] == '/') lg = 0;
         else lg --;
      }
      else xpath[lg] = 0, lg = 0;
   }
   sprintf(pathmod,"%s.%s",xpath,ext);
}

// Retorna un nombre de archivo con extención EXT
// La extención no incluye el punto
void Manipulador_archivos::cambiaExtPath(char *path, const char *ext)
{
   char xpath[MAXPATH];
   int lg = trim(path,xpath) -1;
   while (lg)
   {
      if (xpath[lg] != 46)
      {
         if (xpath[lg] == 92 || xpath[lg] == 58) lg = 0;
         else lg --;
      }
      else xpath[lg] = 0, lg = 0;
   }
   sprintf(path,"%s.%s",xpath,ext);
}


// Construye una trayectoria
void Manipulador_archivos::construyeTrayectoria(const char *tray, const char *arch, const char *ext, char *xpath)
{
   char tmpPath[MAXPATH+1], tmpArch[MAXPATH+1];

   cambiaExtPath(arch, ext, tmpArch);
   sprintf(tmpPath,"%s\\%s",tray,tmpArch);
   memccpy(xpath,tmpPath,0,MAXPATH);
}

void Manipulador_archivos::construyeTrayectoria(const char *tray, const char *arch, char *xpath)
{
   char tmpPath[MAXPATH+1];

   sprintf(tmpPath,"%s\\%s",tray,arch);
   memccpy(xpath,tmpPath,0,MAXPATH);
}

// Adiciona a una cadena con terminador nulo los caracteres LF y LN
void Manipulador_archivos::convierteLinea(char *xcad)
{
   char del[4];
   del[0] = 13;
   del[1] = 10;
   del[2] = 0;
   strcat(xcad,del);
}

// Ajusta el nombre de archivo para visualizacion a la longitud indicada
void Manipulador_archivos::ajustaNombreArchivo(const char *cad, char *xcad, unsigned int lg)
{
   if (strlen(cad) < lg) memccpy(xcad,cad,0,lg);
   else
   {
//////////////////////////////////////////////////////////////////////////////////////
//#error Falta hacer lo necesario para ajustar la visualización  [Primeros 10 caracteres] [...] [Final del texto]
      memccpy(xcad,cad,0,lg);
//////////////////////////////////////////////////////////////////////////////////////
   }
}



/*
void Remueve_archivos(const char *files, const int tp);
// Remueve los archivos especificados en el path, en caso de tener permisos de solo
// lectura y/o oculto son cambiados a archivo normal. Despues de borra el archivo
// Si tp es (1) reescribe este para evitar su recuperaci¢n.

#include "r_esp.hpp"
#include "r_var.hpp"
#include "nucleo.hpp"


   #include <string.h>
   #include <stdio.h>
   #include <dos.h>
   #include <io.h>
   #include <dir.h>
   #include <sys\stat.h>




void Remueve_archivos(const char *files, const int tp)
{
   unsigned int attr, handle, na = 0, i = 0;
   char arch[MAXPATH];
   na = n_archivos_directorios(files,_A_ARCH);
   for(i = 0; i < na; i++) {
      nombre_archivo_directorio(files,_A_ARCH,!i,arch);
      arch[14] = 0;
      // Revisa los atributos del archivos
      if(_dos_getfileattr(arch,&attr) != 0) {
         // Quita atributo HIDEN
         if(attr & FA_HIDDEN) {
            attr &= ~FA_HIDDEN;
           _dos_setfileattr(arch,attr);
         }
         // Quita atributo de READ ONLY
         if(attr & FA_RDONLY) {
            attr &= ~FA_RDONLY;
           _dos_setfileattr(arch,attr);
         }
         // Reescribe el archivo
         if(tp) {
            handle = creat(arch,S_IREAD | S_IWRITE);
            write(handle,RUTINA,8);
            close(handle);
         }
      }
      // Borra el archivo
//      if(unlink(arch)) NCO->Ctrl_error(7,arch,RUTINA);
      unlink(arch)
   }
}

*/
/*
char *msg = "Error no se puede borrar el archivo:";
int done, handle;
unsigned int attr;
struct ffblk ffblk;
done = findfirst(files,&ffblk,FA_ARCH | FA_HIDDEN | FA_SYSTEM | FA_RDONLY);
while(!done) {
   // Quita atributo HIDEN
   _dos_getfileattr(ffblk.ff_name,&attr);
   if(attr & FA_HIDDEN) {
      attr &= ~FA_HIDDEN;
     _dos_setfileattr(ffblk.ff_name,attr);
   }
   // Quita atributo de READ ONLY
   _dos_getfileattr(ffblk.ff_name,&attr);
   if(attr & FA_RDONLY) {
      attr &= ~FA_RDONLY;
     _dos_setfileattr(ffblk.ff_name,attr);
   }
   if(tp) {
      // Reescribe el archivo
      handle = creat(ffblk.ff_name,S_IREAD | S_IWRITE);
      write(handle,msg,8);
      close(handle);
   }
   // Borra el archivo
   if(unlink(ffblk.ff_name)) ctrl_err(7,ffblk.ff_name,"REMUEVE ARCHIVO");
   done = findnext(&ffblk);
}
*/



// Grafica el contenido de los arreglos X vs Y
void Manipulador_archivos::graba(ldouble *x, ldouble *y, int n)
{
   int i;
   for (i = 0; i < n; i++)
   {
#ifdef __Double__
      sprintf(xcad,"%+10.10lf  %+10.10lf",x[i],y[i]);
#else
      sprintf(xcad,"%+10.10Lf  %+10.10Lf",x[i],y[i]);
#endif
      grabaLinea(xcad);
   }
}

// Grafica el contenido de los arreglos X vs Y y Z
void Manipulador_archivos::graba(ldouble *x, ldouble *y, ldouble *z, int n)
{
   int i;
   for (i = 0; i < n; i++)
   {
#ifdef __Double__
      sprintf(xcad,"%+10.10lf  %+10.10lf  %+10.10lf",x[i],y[i],z[i]);
#else
      sprintf(xcad,"%+10.10Lf  %+10.10Lf  %+10.10Lf",x[i],y[i],z[i]);
#endif
      grabaLinea(xcad);
   }
}


// Grafica X vs Y
void Manipulador_archivos::graba(ldouble x, ldouble y)
{
#ifdef __Double__
   sprintf(xcad,"%+10.10lf  %+10.10lf",x,y);
#else
   sprintf(xcad,"%+10.10Lf  %+10.10Lf",x,y);
#endif

   grabaLinea(xcad);
}


// Grafica X vs Y y Z
void Manipulador_archivos::graba(ldouble x, ldouble y, ldouble z)
{
#ifdef __Double__
   sprintf(xcad,"%+10.10lf  %+10.10lf  %+10.10lf",x,y,z);
#else
   sprintf(xcad,"%+10.10Lf  %+10.10Lf  %+10.10Lf",x,y,z);
#endif
   grabaLinea(xcad);
}


// Graba el punto x con los n valores del vector y en una misma linea
void Manipulador_archivos::graba(ldouble x, ldouble *y, int n)
{
   int i;
   char cad[100];

#ifdef __Double__
   sprintf(xcad,"%+10.10lf  ",x);
#else
   sprintf(xcad,"%+10.10Lf  ",x);
#endif
   for (i = 0; i < n; i++)
   {
#ifdef __Double__
      sprintf(cad,"%+10.10lf  ",y[i]);
#else
      sprintf(cad,"%+10.10Lf  ",y[i]);
#endif
      strcat(xcad,cad);
   }
   grabaLinea(xcad);
}



// Interpola num valores con los dados
void Manipulador_archivos::interpolaGraba(ldouble x1, ldouble y1, ldouble x2, ldouble y2, int num)
{
   ldouble inc = (x2 - x1) / (ldouble) num;
   ldouble x, y;
   int j;

   for (j = 0; j < num; j++)
   {
      x = x1 + inc * j;
      y = y1 * ((x - x2) / (x1 - x2)) + y2 * ((x - x1) / (x2 - x1));
#ifdef __Double__
      sprintf(xcad,"%+10.10lf  %+10.10lf",x,y);
#else
      sprintf(xcad,"%+10.10Lf  %+10.10Lf",x,y);
#endif
      grabaLinea(xcad);
   }
}



// Interpola num valores con los dados
void Manipulador_archivos::interpolaGraba(ldouble *x, ldouble *y, int n, int num)
{
   ldouble inc;
   ldouble xi, yi;

   int i, j;
   for (i = 0; i < n-1; i++)
   {
      inc = (x[i+1] - x[i]) / (ldouble) num;
      for (j = 0; j < num; j++)
      {
         xi = x[i] + inc * j;
         yi = y[i] * ((xi - x[i+1]) / (x[i] - x[i+1])) + y[i+1] * ((xi - x[i]) / (x[i+1] - x[i]));
#ifdef __Double__
         sprintf(xcad,"%+10.10lf  %+10.10lf",xi,yi);
#else
         sprintf(xcad,"%+10.10Lf  %+10.10Lf",xi,yi);
#endif
         grabaLinea(xcad);
      }
   }
#ifdef __Double__
   sprintf(xcad,"%+10.10lf  %+10.10lf",x[i],y[i]);
#else
   sprintf(xcad,"%+10.10Lf  %+10.10Lf",x[i],y[i]);
#endif
   grabaLinea(xcad);
}


// Busca el maximo y el mínimo de los valores del arreglo X
void Manipulador_archivos::buscaMaxMin(ldouble *x, const int n, ldouble &min, ldouble &max)
{
   max = min = x[0];
   for (int i = 0; i < n; i++)
   {
      if (x[i] > max) max = x[i];
      if (x[i] < min) min = x[i];
   }
}


