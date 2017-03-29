//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para manipulación de cadenas                                                       //
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




#ifndef __CADENAS_HPP__
#define __CADENAS_HPP__

#define IZQUIERDA   0
#define CENTRADA    1
#define DERECHA     2


/// Clase para manipulación de cadenas
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Cadenas
{

public:


   /// Asigna un puntero de la longitud de la cadena y que contiene una copia de la cadena CAD
   char            *asignaPuntero(const char *cad);
   /// Asigna un puntero de longitud LG
   char            *asignaPuntero(const unsigned int lg);
   /// Asigna un puntero de la longitud de la cadena CAD
   char            *asignaPunteroSinCopiar(const char *cad);


   /// Elimina espacios inecesario de la cadena CAD1 dejando el resultado en la cadena CAD2
   void             eliminaEspaciosInicesarios(const char *cad1, char *cad2);
   /// Elimina espacios inecesario de la cadena CAD
   void             eliminaEspaciosInicesarios(char *cad);
   /// Borra el contenido de la cadena, respetando la longitud de esta
   void             Borra_cadena(char *cad);
   /// Borra de la cadena CAD el caracter especificado por la posici¢n POS, recorriendo el texto subsiguiente sin alterar su longitud
   void             Borra_caracter(char *cad, const unsigned int pos);
   /// Borra de la cadena CAD el caracter especificado por la posici¢n POS, recorriendo el texto subsiguiente sin alterar su longitud, retornando esta en CADOBJ
   void             Borra_caracter(const char *cad, const unsigned int pos, char *cadobj);
   /// Borra desde el inicio hasta la  posici¢n POS de la cadena, respetando la longitud de esta
   void             Borra_cadena_ini_pos(char *cad, const unsigned int pos);
   /// Borra desde la posici¢n POS hasta el final de la cadena, respetando la longitud de esta
   void             Borra_cadena_pos_fin(char *cad, const unsigned int pos);

   /// Indica la posición POS en que fuen encontrado el caracter CAR en la cadena CAD, retorna 0 si no lo encuentra y 1 si lo encuentra
   int              Busca_caracter(const char *cad, const char car, unsigned int &pos);
   /// Indica la posición en que fue encontrado cualquier caracter de la cadena CARS en la cadena CAD e indicando su posicion en la variable POS, si no fue encontrado, retorna 0, si fue encontrado retorna 1
   int              Busca_caracteres(const char *cad,  const char *cars, unsigned int &pos);
   /// Busca en la cadena CAD los caracteres de la cadena XCAD, indicando la posición donde inicia esta POS, retornando 0 si no la encuentra, y 1 si la encuentra
   int              Busca_cadena(const char *cad, const char *xcad, unsigned int &pos);
   /// Busca en la cadena CAD los caracteres de la cadena XCAD iniciando en la posicion POS_INI, indicando la posici¢n donde inicia esta POS, retornando 0 si no la encuentra, y 1 si la encuentra
   int              Busca_cadena(const char *cad, const char *cbus, const unsigned int pos_ini, unsigned int &pos);
   /// Busca si la cadena CBUS esta al inicio de la cadena CAD, retorna 1 si esta y 0 en caso contrario
   int              Busca_cadena_inicio(const char *cad, const char *cbus, const unsigned int tp);
   /// Busca si la cadena CBUS esta al final de la cadena CAD, retorna 1 si esta y 0 en caso contrario
   int              Busca_cadena_final(const char *cad, const char *cbus, const unsigned int tp);
   /// Busca si la cadena CBUS esta en la cadena CAD (soporta el metacaracter ?), retorna 1 si esta y 0 en caso contrario
   int              Busca_cadena_metacaracteres(const char *cad, const char *cbus, const unsigned int pos_ini, unsigned int &pos);
   /// Busca en una cadena un patron, retornando 1 si lo encontra y 0 en caso contrario
   // ^   Inicio de la cadena
   // $   Fin de la cadena
   // ?   Cualquier caracter
   // *   Cero o mas caracteres
   // +   Uno o mas caracteres
   ////////////////////////////////////////////////
   // Faltan \,[],[-],[^]
   ////////////////////////////////////////////////
   int              Busca_patron(const char *cad, const char *patron);
   /// Remplaza de la cadena CAD la cedena buscada BUS por la cedena REM (todas las ocurrencias), retornando el numero de remplazos
   unsigned int     Busca_remplaza_cadenas(char *cad, const char *bus, const char *rem);
   /// Busca una expresion EXP, dentro de la cadena CAD (expresion es una variable o funcion), la expresion buscada estara delimitada por
   //    Al inicio {}[]()=,.*-/+><?:&|  o el inicio de la cadena
   //    Al final  {}[]()=,.*-/+><?:&| o fin de la cadena
   // retornando la posici¢n donde inicia esta, retorna 1 si la encuentra 0 en caso contrario
   int              Busca_expresion(const char *cad, const char *exp, unsigned int &pos);
   /// Remplaza de la cadena CAD la cedena buscada BUS por la cedena REM (todas las ocurrencias), retornando el numero de remplazos
   unsigned int     Busca_remplaza_expresion(char *exp, const char *bus, const char *rem);


   /// Retorna la posicion donde inicia la palabra anterior en la cadena CAD a partir de la posicion POS hasta el inicio de la cadena, retornando -1 si no se encuentra
   // Si T_P es (0) busca la palabra siguiente (alfanumerico sin espacio)
   //           (1) busca la palabra siguiente (alfanumerico con espacio)
   //           (2) Busca la palabra siguiente (numerico, punto y signo menos)
   //           (3) Busca la palabra siguiente (numerico)
   int              Posicion_palabra_anterior(const char *cad, const unsigned int pos, const unsigned int t_p);
   /// Retorna la posicion donde inicia la palabra siguiente en la cadena CAD a partir de la posicion POS, retornando -1 si esta al final de la cadena
   // Si T_P es (0) busca la palabra siguiente (alfanumerico)
   //           (1) busca la palabra siguiente (alfanumerico con espacios)
   //           (2) Busca la palabra siguiente (numerico, punto, signo menos o mas)
   //           (3) Busca la palabra siguiente (numerico)
   int              Posicion_palabra_siguiente(const char *cad, const unsigned int pos, const unsigned int t_p);

   /// Compara la cadena CAD1 con la cadena CAD2 ignorando minusculas y regresando verdadero si son iguales
   int              Compara_ignorando_minusculas(const char *cad1, const char *cad2);

   /// Cuenta el numero de veces que una cadena CBUS aparece en la cadena CADENA, si no lo encuentra retorna 0
   unsigned int     Numero_veces_cadena(const char *cadena, const char *cbus);
   /// Cuenta el numero de veces que un caracter CAR aparece en una cadena CEDENA, si no lo encuentra retorna 0
   unsigned int     Numero_veces_caracter(const char *cadena, const char car);

   /// Retorna (1) si el carcter es digito, en caso contrario retorna (0), acepta loa siguientes caracteres como digitos [0123456789]
   int              Es_caracter_digito(const char car);
   /// Retorna (1) si el carcter es numerico, en caso contrario retorna (0), acepta loa siguientes caracteres como numericos [0123456789.+-]
   int              Es_caracter_numerico(const char car);
   /// Retorna (1) si el carcter es alfabetico, en caso contrario retorna (0), acepta loa siguientes caracteres como alfabeticos [ABCDEFGHIJKLMNOPQRSTUVWXYZZabcdefghijklmnopqrstuvwxyz]
   int              Es_caracter_alfabetico(const char car);
   /// Retorna (1) si el carcter es alfanumerico, en caso contrario retorna (0), acepta loa siguientes caracteres como alfanumerico [ABCDEFGHIJKLMNOPQRSTUVWXYZZabcdefghijklmnopqrstuvwxyz …‚Š¡¢¢£—¤¥ -_0123456789+.]
   int              Es_caracter_alfnumerico(const char car);
   /// Retorna (1) si el caracter es espacio o tabulador, en caso contrario retorna (0)
   int              Es_caracter_espaciado(const char car);

   /// Retorna verdadero si la cadena s¢lo contiene una expresion numerica valida (ya sea en formato exponencial o numerico ordinario) en caso contrario retorna (0)
   int              Es_cadena_numero(const char *cad);
   /// Retorna verdadero si la cadena solo contiene caracteres alfabeticos, espacios, guion o subrrayado, en caso contrario retorna (0). Soporta caracteres como  …‚Š¡¢•£—¤¥
   int              Es_cadena_alfabetica(const char *cad);

   /// Retorna un 0 si la cadena CAD es vacia y 1 en caso contrario
   int              Es_cadena_vacia(const char *cad)
   {
      if (cad[0]) return 0;
      return 1;
   }

   /// Convierte el caracter CAR segun la siguiente convicción
   // Si T_P es   (1) comvierte de mayuscula a miniscula y vice versa
   //             (2) convierte a minuscula
   //             (3) convierte a mayuscula
   char             Convierte_may_min(const char car, const unsigned int t_p);

   /// Convierte a mayuscula los caracteres de la cadena CAD
   void             Convierte_mayusculas(char *cad);

   /// Convierte a minusculas los caracteres de la cadena CAD
   void             Convierte_minusculas(char *cad);

   /// Combierte el primer caracter de la palabra en mayuscula
   void             Convierte_ucfirst(char *cad);

   /// Combierte el primer caracter de cada palabra en mayuscula
   void             Convierte_ucwords(char *cad);

   /// Extrae de la cadena CAD el numero de caracteres indicados en N_C a partir de la posicion P_I partiendo de cero, retornando un puntero a ella
   unsigned int     Substr(const char *cad, const unsigned  int p_i, const unsigned int n_c, char *cadobj);


   /// Retorna la longitud de la cadena sin los espacios al final de esta
   unsigned int     Lg_cadena_sin_espacios_final(const char *cad);
   /// Retorna la longitud de la cadena sin espacios
   unsigned int     Lg_cadena_sin_espacios(const char *cad);

   /// Quita los espacios que existan al inicio y al final de la cadena retornando la longitud de la cadena
   unsigned int     trim(char *cad);
   /// Quita los espacios que existan al inicio y al fin de la cadena CAD dejandola en la cadena CADOBJ, retornando la longitud de la cadena
   unsigned int     trim(const char *cad, char *cadobj);


   /// Inserta el caracter CAR en la posicion POS recorriendo todos los caracteres siguientes
   void             Inserta_caracter(char *cad, const unsigned int pos, const char car);
   /// Alinea el contenido de la cadena CAD a la longitud LG y retorna esta en la cadena XCAD
   // Si tp es (IZQUIERDA) Alinea a la izquierda
   //          (CENTRADA)  Alinea al centro
   //          (DERECHA)   Alinea a la derecha
   void             Alinea_cadena(const char *cad, const unsigned int lg, const int tp, char *xcad);


   /// Quita de la cadena CAD, la(s) ocurrencia(s) del caracter CAR
   // si T_P es (1) Extrae todos los caracteres de la cadena
   //           (2) Extrae sólo la primera ocurrencia del caracter
   void             Quitar_caracter(char *cad, const char car, const unsigned int t_p = 1);

   /// Expande una cadena del tipo (1,2,4-7,9) dejandola como (1,2,4,5,6,7,9)
   void             Expander_Cadena_numerica_entera(const char *cad, char *xcad);


};

#endif



// Adiciones
// ucfirst Combierte el primer caracter de la primera palabra en mayuscula
// ucwords Combierte el primer caracter de cada palabra en mayuscula
// En cadenas hacer rutina que dado un agrupador [ad-hA-Z] retorne todos los caracteres que esten en el agrupador

