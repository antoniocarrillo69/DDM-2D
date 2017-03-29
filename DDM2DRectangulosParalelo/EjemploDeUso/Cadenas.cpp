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


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Cadenas.hpp"


// Asigna un puntero de la longitud de la cadena y que contiene una copia de la cadena CAD
char *Cadenas::asignaPuntero(const char *cad)
{
   char *ptr = NULL;
   int lg;

   lg = strlen(cad);
//   if (lg < 64000l) {
   ptr = new char[lg+2];
   if (!ptr) exit(1);
   strcpy(ptr,cad);
//    } else {
//////////////////////////////////////////////////
// Avisar de posible error por solicitud excesiva
//////////////////////////////////////////////////
//   }
   return ptr;
}

// Asigna un puntero de longitud LG
char *Cadenas::asignaPuntero(const unsigned int lg)
{
   char *ptr = NULL;

   if (!lg) exit(1);
//   if (lg > 0 && lg < 64000l) {
   ptr = new char[lg+1];
   if (!ptr) exit(1);
   ptr[0] = 0;
//    } else {
//////////////////////////////////////////////////
// Avisar de posible error por solicitud nula o excesiva
//////////////////////////////////////////////////
//   }
   return ptr;
}

// Asigna un puntero de la longitud de la cadena CAD
char *Cadenas::asignaPunteroSinCopiar(const char *cad)
{
   char *ptr = NULL;
   int lg;

   lg = strlen(cad);
//   if (lg < 64000l) {
   ptr = new char[lg+2];
   if (!ptr) exit(1);
//    } else {
//////////////////////////////////////////////////
// Avisar de posible error por solicitud excesiva
//////////////////////////////////////////////////
//   }
   return ptr;
}



// Elimina espacios inecesario de la cadena CAD1 dejando el resultado en la cadena CAD2
void Cadenas::eliminaEspaciosInicesarios(const char *cad1, char *cad2)
{
   int sw = 0;
   char *ptr = cad2;
   // Se eliminan los espacios inacesarios dejando solo uno
   while (*cad1)
   {
      if (*cad1 == 32)
      {
         if (sw == 0) *ptr = *cad1, ptr++;
         sw = 1;
      }
      else *ptr = *cad1, ptr++, sw = 0;
      cad1++;
   }
   *ptr = 0;
   // se quitan los espacios al inicio y fin de la cadena
   trim(cad2);
}

// Elimina espacios inecesario de la cadena CAD
void Cadenas::eliminaEspaciosInicesarios(char *cad)
{
   char *xcad = asignaPunteroSinCopiar(cad);
   eliminaEspaciosInicesarios(cad,xcad);
   strcpy(cad,xcad);
   delete []xcad;
}



// Borra el contenido de la cadena, respetando la longitud de esta
void Cadenas::Borra_cadena(char *cad)
{
   while (*cad) *cad = 32, cad++;
}


// Borra de la cadena CAD el caracter especificado por la posici¢n POS, recorriendo el texto subsiguiente sin alterar su longitud
void Cadenas::Borra_caracter(char *cad, const unsigned int pos)
{
   if (!cad[0]) return;
   unsigned int i = 0;
   while (cad[i])
   {
      if (i >= pos) cad[i] = cad[i + 1];
      i++;
   }
   cad[i - 1] = 32;
   cad[i] = 0;
}


// Borra de la cadena CAD el caracter especificado por la posici¢n POS, recorriendo el texto subsiguiente sin alterar su longitud, retornando esta en XCAD
void Cadenas::Borra_caracter(const char *cad, const unsigned int pos, char *cadobj)
{
   cadobj[0] = 0;
   if (cad[0] == 0) return;
   unsigned int i = 0;
   while (*cad)
   {
      if (i == pos) cad++;
      *cadobj = *cad;
      cadobj++, cad++, i++;
   }
   *cadobj = 32;
   cadobj++;
   *cadobj = 0;
}




// Borra desde el inicio hasta la  posición POS de la cadena, respetando la longitud de esta
void Cadenas::Borra_cadena_ini_pos(char *cad, const unsigned int pos)
{
   unsigned int i = 0;
   while (*cad)
   {
      if (i <= pos) *cad = 32;
      cad++,i++;
   }
}


// Borra desde la posición POS hasta el final de la cadena, respetando la longitud de esta
void Cadenas::Borra_cadena_pos_fin(char *cad, const unsigned int pos)
{
   unsigned int i = 0;
   while (*cad)
   {
      if (i >= pos) *cad = 32;
      cad++,i++;
   }
}


// Indica la posición POS en que fuen encontrado el caracter CAR en la cadena CAD, retorna 0 si no lo encuentra y 1 si lo encuentra
int Cadenas::Busca_caracter(const char *cad, const char car, unsigned int &pos)
{
   pos = 0;
   while (*cad)
   {
      if (*cad == car) return 1;
      cad++,pos++;
   }
   return 0;
}

// Indica la posición en que fue encontrado cualquier caracter de la cadena CARS en la cadena CAD e indicando su posicion en la variable POS, si no fue encontrado
// retorna 0, si fue encontrado retorna 1
int Cadenas::Busca_caracteres(const char *cad,  const char *cars, unsigned int &pos)
{
   pos = 0;
   const char *xp;
   while (*cad)
   {
      xp = cars;
      while (*xp)
      {
         if (*cad == *xp) return 1;
         xp++;
      }
      cad++, pos++;
   }
   return 0;
}


// Busca una expresion dentro de otra
int Cadenas::Busca_expresion(const char *cad, const char *exp, unsigned int &pos)
{
   unsigned int xi, in, xpos;
   const char *DELIM = "{}[]()=><?&|:,.*-/+ ";
   pos = 0;
   const char *xp;
   char car = 0;
   if (exp[0] == 0 || exp[0] == 0) return 0;
   while (*cad)
   {
      if (*cad == *exp)
      {
         xi = 0, in = 1;
         xp = exp;
         while (*xp)
         {
            if (*(cad + xi) == 0 || *(cad + xi) != *xp)
            {
               in = 0;
               break;
            }
            xp ++,xi++;
         }
         if (in)
         {
            if ((car == 0 || Busca_caracter(DELIM,car,xpos)) && (!*(cad+xi) || Busca_caracter(DELIM,*(cad+xi),xpos))) return 1;
         }
      }
      car = *cad;
      cad++, pos++;
   }
   return 0;
}



// Remplaza de la cadena EXP la cedena buscada BUS por la cedena REM (todas las ocurrencias), retornando el numero de remplazos
unsigned int Cadenas::Busca_remplaza_expresion(char *exp, const char *bus, const char *rem)
{
   if (exp[0] == 0 || bus[0] == 0 || rem[0] == 0) return 0;
   char *xcad1, *xcad2;
   unsigned int lg_bus, lg_cad, lg_rem, pos, st = 0;
   lg_bus = strlen(bus);
   lg_rem = strlen(rem);
   while (Busca_expresion(exp,bus,pos))
   {
      lg_cad = strlen(exp);
      xcad1 = asignaPuntero(lg_cad + lg_rem + 10);
      xcad2 = asignaPuntero(lg_cad + lg_rem + 10);
      Substr(exp,0,pos,xcad1);
      Substr(exp,(pos+lg_bus),lg_cad,xcad2);
      sprintf(exp,"%s%s%s",xcad1,rem,xcad2);
      delete []xcad1;
      delete []xcad2;
      st ++;
   }
   return st;
}

// Busca en la cadena CAD los caracteres de la cadena XCAD, indicando la posici¢n donde inicia esta POS, retornando 0 si no la encuentra, y 1 si la encuentra
int Cadenas::Busca_cadena(const char *cad, const char *cbus, unsigned int &pos)
{
   unsigned int xi, in;
   pos = 0;
   const char *xp;

   if (cad[0] == 0 || cbus[0] == 0) return 0;
   while (*cad)
   {
      if (*cad == *cbus)
      {
         xi = 0, in = 1;
         xp = cbus;
         while (*xp)
         {
            if (*(cad + xi) == 0 || *(cad+xi) != *xp)
            {
               in = 0;
               break;
            }
            xp ++,xi++;
         }
         if (in) return 1;
      }
      cad++, pos++;
   }
   return 0;
}


// Busca en la cadena CAD los caracteres de la cadena XCAD iniciando en la posicion POS_INI, indicando la posici¢n donde inicia esta POS, retornando 0 si no la encuentra, y 1 si la encuentra
int Cadenas::Busca_cadena(const char *cad, const char *cbus, const unsigned int pos_ini, unsigned int &pos)
{
   unsigned int xi, in, lg;
   lg = strlen(cad);
   pos = 0;
   if (pos_ini >= lg) return 0;
   if (cad[0] == 0 || cbus[0] == 0) return 0;

   const char *xp;
   while (*cad)
   {
      if (pos >= pos_ini)
      {
         if (*cad == *cbus)
         {
            xi = 0, in = 1;
            xp = cbus;
            while (*xp)
            {
               if (*(cad + xi) == 0 || *(cad+xi) != *xp)
               {
                  in = 0;
                  break;
               }
               xp ++,xi++;
            }
            if (in) return 1;
         }
      }
      cad++, pos++;
   }
   return 0;
}

// Busca si la cadena CBUS esta al inicio de la cadena CAD, retorna 1 si esta y 0 en caso contrario
int Cadenas::Busca_cadena_inicio(const char *cad, const char *cbus, const unsigned int tp)
{
   unsigned int pos;

   if (cad[0] == 0 || cbus[0] == 0) return 0;

   // Busca la cadena
   if (tp)
   {
      if (Busca_cadena_metacaracteres(cad, cbus, 0, pos))
      {
         if (pos == 0) return 1;
      }
   }
   else
   {
      if (Busca_cadena(cad, cbus, 0, pos))
      {
         if (pos == 0) return 1;
      }
   }
   return 0;
}

// Busca si la cadena CBUS esta al final de la cadena CAD, retorna 1 si esta y 0 en caso contrario
int Cadenas::Busca_cadena_final(const char *cad, const char *cbus, const unsigned int tp)
{
   unsigned int pos, lg_cad, lg_cbus;
   if (cad[0] == 0 || cbus[0] == 0) return 0;

   lg_cad = strlen(cad);
   lg_cbus = strlen(cbus);
   // Busca la cadena
   if (lg_cad < lg_cbus) return 0;
   if (tp)
   {
      if (Busca_cadena_metacaracteres(cad, cbus, lg_cad - lg_cbus, pos))
      {
         if (pos + lg_cbus >= lg_cad) return 1;
      }
   }
   else
   {
      if (Busca_cadena(cad, cbus, lg_cad - lg_cbus, pos))
      {
         if (pos + lg_cbus >= lg_cad) return 1;
      }
   }
   return 0;
}


// Busca si la cadena CBUS esta en la cadena CAD (soporta el metacaracteres ?), retorna 1 si esta y 0 en caso contrario
int Cadenas::Busca_cadena_metacaracteres(const char *cad, const char *cbus, const unsigned int pos_ini, unsigned int &pos)
{
   unsigned int xi, in, lg;
   lg = strlen(cad);
   pos = 0;
   if (pos_ini >= lg) return 0;
   if (cad[0] == 0 || cbus[0] == 0) return 0;

   const char *xp;
   while (*cad)
   {
      if (pos >= pos_ini)
      {
         if (*cad == *cbus || *cbus == '?')
         {
            xi = 0;
            in = 1;
            xp = cbus;
            while (*xp)
            {
               if (*(cad + xi) == 0 || ( *(cad + xi) != *xp && *xp != '?'))
               {
                  in = 0;
                  break;
               }
               xp ++,xi++;
            }
            if (in) return 1;
         }
      }
      cad++, pos++;
   }
   return 0;
}


// Busca en una cadena un patron, retornando 1 si lo encontra y 0 en caso contrario
// ^   Inicio de la cadena
// $   Fin de la cadena
// ?   Cualquier caracter
///////////////////////////////////////////////////////////
// Faltan [],[-],[^] no soporta \?
///////////////////////////////////////////////////////////
int Cadenas::Busca_patron(const char *cad, const char *patron)
{
   char sw_almacena;
   char sw_inicio_final = 0;
   char comando = 0;
   char sw_diagonal = 1;
   int  encontro, st = 0;
   unsigned int ind = 0, cind = 0, pos = 0, pos_enc, xpos;
   char cbus[100];

   if (cad[0] == 0 || patron[0] == 0) return 0;

   while (patron[cind])
   {
      if (patron[cind] == '\\' && sw_diagonal)
      {
         sw_diagonal = 0;
         cind++;
         continue;
      }
      if (Busca_caracter("^$*+",patron[cind],xpos) && sw_diagonal)
      {
         // Revisa si se formo la cadena a buscar
         if (ind)
         {
            switch (comando)
            {
            case 1:  // El patron esta en el inicio de la cadena
               encontro = Busca_cadena_inicio(cad,cbus,1);
               if (sw_inicio_final >= 2)
               {
                  if (st && encontro) st = 1;
                  else st = 0;
               }
               else
               {
                  if (encontro) st = 1;
               }
               break;
            case 2:  // El patron esta al final de la cadena
               encontro = Busca_cadena_final(cad,cbus,1);
               if (sw_inicio_final >= 2)
               {
                  if (st && encontro) st = 1;
                  else st = 0;
               }
               else
               {
                  if (encontro) st = 1;
               }
               break;
            default:
               encontro = Busca_cadena_metacaracteres(cad, cbus, pos, pos_enc);
               if (sw_inicio_final >= 1)
               {
                  if (st && encontro) st = 1;
                  else st = 0;
               }
               else
               {
                  if (encontro) st = 1;
               }
            }
            pos = pos_enc+ind;
            if (patron[cind] == '+') pos++;
            // Reinicializa la cadena a buscar
            cbus[0] = 0;
            ind = 0;
         }
      }


      sw_almacena = 1;
      if (sw_diagonal)
      {
         if (patron[cind] == '^') comando = 1, sw_almacena = 0, sw_inicio_final++;
         if (patron[cind] == '$') comando = 2, sw_almacena = 0, sw_inicio_final++;
         if (patron[cind] == '*') comando = 3, sw_almacena = 0, sw_inicio_final++;
         if (patron[cind] == '+') comando = 4, sw_almacena = 0, sw_inicio_final++;
      }
      sw_diagonal ++;
      if (sw_almacena)
      {
         // Almacena el caracter en la cadena de busqueda
         cbus[ind] = patron[cind];
         ind++;
         cbus[ind] = 0;
      }
      cind++;
   }

   // Revisa si se forma la cadena a buscar
   if (ind)
   {
      switch (comando)
      {
      case 1:  // El patron esta en el inicio de la cadena
         encontro = Busca_cadena_inicio(cad,cbus,1);
         if (sw_inicio_final >= 2)
         {
            if (st && encontro) st = 1;
            else st = 0;
         }
         else
         {
            if (encontro) st = 1;
         }
         break;
      case 2:  // El patron esta al final de la cadena
         encontro = Busca_cadena_final(cad,cbus,1);
         if (sw_inicio_final >= 2)
         {
            if (st && encontro) st = 1;
            else st = 0;
         }
         else
         {
            if (encontro) st = 1;
         }
         break;
      default:
         encontro = Busca_cadena_metacaracteres(cad, cbus, pos, pos_enc);
         if (sw_inicio_final >= 1)
         {
            if (st && encontro) st = 1;
            else st = 0;
         }
         else
         {
            if (encontro) st = 1;
         }
      }
   }
   // Retorna si fue encontrado o no el patron
   return st;
}



// Remplaza de la cadena CAD la cedena buscada BUS por la cedena REM (todas las ocurrencias), retornando el numero de remplazos
unsigned int Cadenas::Busca_remplaza_cadenas(char *cad, const char *bus, const char *rem)
{
   if (cad[0] == 0 || bus[0] == 0) return 0;
   char *xcad1, *xcad2;

   unsigned int lg_bus, lg_cad, lg_rem, pos, st = 0;
   lg_bus = strlen(bus);
   lg_rem = strlen(rem);
   while (Busca_cadena(cad,bus,pos))
   {
      lg_cad = strlen(cad);
      xcad1 = asignaPuntero(lg_cad + lg_rem + 10);
      xcad2 = asignaPuntero(lg_cad + lg_rem + 10);
      Substr(cad,0,pos,xcad1);
      Substr(cad,(pos+lg_bus),lg_cad,xcad2);
      sprintf(cad,"%s%s%s",xcad1,rem,xcad2);
      delete []xcad1;
      delete []xcad2;
      st ++;
   }
   return st;
}


// Retorna la posicion donde inicia la palabra anterior en la cadena CAD a partir de la posicion POS hasta el inicio de la cadena, retornando -1 si no se encuentra
// Si T_P es (0) busca la palabra siguiente (alfanumerico sin espacio)
//           (1) busca la palabra siguiente (alfanumerico con espacio)
//           (2) Busca la palabra siguiente (numerico, punto y signo menos)
//           (3) Busca la palabra siguiente (numerico)
int Cadenas::Posicion_palabra_anterior(const char *cad, const unsigned int pos, const unsigned int t_p)
{
   // Si esta al inicio de la cadena retorna -1
   if (!pos) return -1;
   unsigned int i = pos;
   int sw = 1;

   if (cad[0] == 0) return -1;

   if (i > strlen(cad)) i = strlen(cad) -1;
   // Busca la palabra anterior antes de los caracteres de espaciado
   while (cad[i] == 32 && i > 0) i--;
   // Busca donde inicia la palabra actual
   while (i > 0 && sw)
   {
      sw = 0;
      if (t_p == 0 && Es_caracter_alfnumerico(cad[i]) &&  cad[i] != 32) sw = 1;
      if (t_p == 1 && Es_caracter_alfabetico(cad[i])) sw = 1;
      if (t_p == 2 && Es_caracter_digito(cad[i])) sw = 1;
      if (t_p == 3 && Es_caracter_numerico(cad[i])) sw = 1;
      i--;
   }
   return i;
}


// Retorna la posicion donde inicia la palabra siguiente en la cadena CAD a partir de la posicion POS, retornando -1 si esta al final de la cadena
// Si T_P es (0) busca la palabra siguiente (alfanumerico)
//           (1) busca la palabra siguiente (alfanumerico con espacios)
//           (2) Busca la palabra siguiente (numerico, punto, signo menos o mas)
//           (3) Busca la palabra siguiente (numerico)
int Cadenas::Posicion_palabra_siguiente(const char *cad, const unsigned int pos, const unsigned int t_p)
{
   // Revisa que la poscion no sea mayor que la longitud de la cadena
   if (pos > strlen(cad)) return -1;
   if (cad[0] == 0) return -1;
   unsigned int i = pos;
   int  sw = 1;
   if (cad[i] == 32)
   {
      // Si empieza con espacios buscar el siguiente caracter distinto de estos y regrasara su posicion
      while (cad[i] == 32) i++;
   }
   else
   {
      // Busca hasta el final de la actual palabra
      while (cad[i] && sw)
      {
         sw = 0;
         if (!t_p && Es_caracter_alfnumerico(cad[i]) &&  cad[i] != 32) sw = 1;
         if (t_p == 1 && Es_caracter_alfabetico(cad[i])) sw = 1;
         if (t_p == 2 && Es_caracter_digito(cad[i])) sw = 1;
         if (t_p == 3 && Es_caracter_numerico(cad[i])) sw = 1;
         i++;
      }
      while (cad[i] == 32) i++;
   }
   // Si es el final de la cadena retorna -1, en caso contrario regresa la posici¢n de la siguiente palabra
   if (!cad[i]) return (-1);
   return i;
}


// Compara la cadena CAD1 con la cadena CAD2 ignorando minusculas y regresando verdadero si son iguales
int Cadenas::Compara_ignorando_minusculas(const char *cad1, const char *cad2)
{
   char xcar1, xcar2;
   if (cad1[0] == 0 || cad2[0] == 0) return 0;
   while (*cad1)
   {
      xcar1 = Convierte_may_min(*cad1, 3);
      xcar2 = Convierte_may_min(*cad2, 3);
      if (xcar1 != xcar2) return 0;
      cad1++,cad2++;
   }
   if (*cad2) return 0;
   return 1;
}


// Cuenta el numero de veces que una cadena CBUS aparece en la cadena CADENA, si no lo encuentra retorna cero
unsigned int Cadenas::Numero_veces_cadena(const char *cadena, const char *cbus)
{
   const char *pcbus;
   int i, xi;
   unsigned int nv = 0;

   if (cadena[0] == 0 || cbus[0] == 0) return 0;

   while (*cadena)
   {
      if (*cadena == *cbus)
      {
         pcbus = cbus;
         i = xi = 0;
         while (*(pcbus+xi))
         {
            if (*(cadena+i) != *(pcbus+xi)) break;
            xi++,i++;
         }
         if (!*(pcbus+xi)) nv++;
      }
   }
   return nv;
}


// Cuenta el numero de veces que un caracter CAR aparece en una cadena CEDENA, si no lo encuentra retorna cero
unsigned int Cadenas::Numero_veces_caracter(const char *cadena, const char car)
{
   unsigned int nv = 0;
   while (*cadena)
   {
      if (*cadena == car) nv ++;
      cadena++;
   }
   return nv;
}


// Retorna (1) si el carcter es digito, en caso contrario retorna (0), acepta loa siguientes caracteres como digitos [0123456789]
int Cadenas::Es_caracter_digito(const char car)
{
   if (car > 47 && car < 58) return 1;
   return 0;
}


// Retorna (1) si el carcter es alfanumerico, en caso contrario retorna (0), acepta loa siguientes caracteres como alfanumerico [ABCDEFGHIJKLMNOPQRSTUVWXYZZabcdefghijklmnopqrstuvwxyz …‚Š¡¢¢£—¤¥ -_0123456789+.]
int Cadenas::Es_caracter_alfnumerico(const char car)
{
   if (Es_caracter_alfabetico(car) || Es_caracter_digito(car)) return 1;
   return 0;
}


// Retorna (1) si el caracter es espacio o tabulador, en caso contrario retorna (0)
int Cadenas::Es_caracter_espaciado(const char car)
{
   if (car == ' ' || car == '\t') return 1;
   return 0;
}



// Retorna (1) si el carcter es alfabetico, en caso contrario retorna (0), acepta loa siguientes caracteres como alfabeticos [ABCDEFGHIJKLMNOPQRSTUVWXYZZabcdefghijklmnopqrstuvwxyz]
int Cadenas::Es_caracter_alfabetico(const char car)
{
   if ((car > 64 && car < 91) || (car > 96 && car < 123)) return 1;
   return 0;
}

// Retorna (1) si el carcter es numerico, en caso contrario retorna (0), acepta loa siguientes caracteres como numericos [0123456789.+-]
int Cadenas::Es_caracter_numerico(const char car)
{
   if ((car > 47 && car < 58) || car == 43 || car == 45 || car == 46) return 1;
   return 0;
}


// Rutina que retorna verdadero si la cadena solo contiene una expresion numerica valida (ya sea en formato exponencial o numerico ordinario) en caso contrario retorna (0)
int Cadenas::Es_cadena_numero(const char *cad)
{
   int numeros = 0, p_dec = 0, not_exp = 0, sig = 0, st = 1, i = 0;
   char car_ant = 0;
   while (*cad)
   {
      if (*cad > 47 && *cad < 58) numeros ++;
      else
      {
         switch (*cad)
         {
         case '.':
            p_dec ++;
            break;
         case 'e':
         case 'E':
            if (!numeros) st = 0;
            not_exp ++;
            break;
         case '+':
         case '-':
            if (!i) break;
            if (numeros && !not_exp) st = 0;
            if (!(car_ant == 'e' || car_ant == 'E')) st = 0;
            sig ++;
            break;
         case 32:
            break;
         default:
            st = 0;
         }
      }
      car_ant = *cad;
      i ++, cad++;
   }
   if (car_ant == 'e' || car_ant == 'E' || car_ant == '+' || car_ant == '-' || p_dec > 1 || not_exp > 1 || sig > 1 || !numeros) st = 0;
   return st;
}


// Rutina que retorna verdadero si la cadena solo contiene caracteres alfabeticos, espacios, guion o subrrayado, en caso contrario retorna (0). Soporta caracteres como  …‚Š¡¢•£—¤¥
int Cadenas::Es_cadena_alfabetica(const char *cad)
{
   while (*cad)
   {
      if (!Es_caracter_alfabetico(*cad)) return 0;
      cad++;
   }
   return 1;
}

// Convierte el caracter CAR segun la siguiente convicción
// Si T_P es   (1) comvierte de mayuscula a miniscula y vice versa
//             (2) convierte a minuscula
//             (3) convierte a mayuscula
char Cadenas::Convierte_may_min(const char car, const unsigned int t_p)
{
   char x_c = car;
   // Convierte a minusculas
   if (t_p == 2)
   {
      if (car >= 'A' && car <= 'Z') x_c = car + ' ';
      if (car == 'Ñ') x_c = 'ñ';
      if (car == 'Á') x_c = 'á';
      if (car == 'À') x_c = 'à';
      if (car == 'É') x_c = 'é';
      if (car == 'È') x_c = 'è';
      if (car == 'Í') x_c = 'í';
      if (car == 'Ì') x_c = 'ì';
      if (car == 'Ó') x_c = 'ó';
      if (car == 'Ò') x_c = 'ò';
      if (car == 'Ú') x_c = 'ú';
      if (car == 'Ù') x_c = 'ù';
      if (car == 'Ü') x_c = 'ü';
   }
   // Convierte a mayusculas
   if (t_p == 3)
   {
      if (car >= 'a' && car <= 'z') x_c = car - ' ';
      if (car == 'ñ') x_c = 'Ñ';
      if (car == 'á') x_c = 'Á';
      if (car == 'à') x_c = 'À';
      if (car == 'é') x_c = 'É';
      if (car == 'è') x_c = 'È';
      if (car == 'í') x_c = 'Í';
      if (car == 'ì') x_c = 'Ì';
      if (car == 'ó') x_c = 'Ó';
      if (car == 'ò') x_c = 'Ò';
      if (car == 'ú') x_c = 'Ú';
      if (car == 'ù') x_c = 'Ù';
      if (car == 'ü') x_c = 'Ü';
   }
   // Convierte de mayusculas a minusculas y viseversa
   if (t_p == 1)
   {
      if (car >= 'A' && car <= 'Z') x_c = car + ' ';
      else if (car >= 'a' && car <= 'z') x_c = car - ' ';
      if (car == 'ñ') x_c = 'ñ';
      else if (car == 'Ñ') x_c = 'ñ';
      if (car == 'á') x_c = 'Á';
      else if (car == 'Á') x_c = 'á';
      if (car == 'à') x_c = 'À';
      else if (car == 'À') x_c = 'à';
      if (car == 'é') x_c = 'É';
      else if (car == 'É') x_c = 'é';
      if (car == 'è') x_c = 'È';
      else if (car == 'È') x_c = 'è';
      if (car == 'í') x_c = 'Í';
      else if (car == 'Í') x_c = 'í';
      if (car == 'ì') x_c = 'Ì';
      else if (car == 'Ì') x_c = 'ì';
      if (car == 'ó') x_c = 'Ó';
      else if (car == 'Ó') x_c = 'ó';
      if (car == 'ò') x_c = 'Ò';
      else if (car == 'Ò') x_c = 'ò';
      if (car == 'ú') x_c = 'Ú';
      else if (car == 'Ú') x_c = 'ú';
      if (car == 'ù') x_c = 'Ù';
      else if (car == 'Ù') x_c = 'ù';
      if (car == 'ü') x_c = 'Ü';
      else if (car == 'Ü') x_c = 'ü';
   }
   return x_c;
}


// Convierte a mayuscula los caracteres de la cadena CAD
void Cadenas::Convierte_mayusculas(char *cad)
{
   while (*cad)
   {
      *cad = Convierte_may_min(*cad,3);
      cad++;
   }
}

// Convierte a minusculas los caracteres de la cadena CAD
void Cadenas::Convierte_minusculas(char *cad)
{
   while (*cad)
   {
      *cad = Convierte_may_min(*cad,2);
      cad++;
   }
}


// Combierte el primer caracter de la palabra en mayuscula
void Cadenas::Convierte_ucfirst(char *cad)
{
   while (*cad)
   {
      if (Es_caracter_alfabetico(*cad))
      {
         *cad = Convierte_may_min(*cad,3);
         return;
      }
      cad++;
   }
}

// Combierte el primer caracter de la palabra en mayuscula entendiendo por paralbra la que inicia despues de un caracter de espaciado
void Cadenas::Convierte_ucwords(char *cad)
{
   while (*cad)
   {
      if (Es_caracter_alfabetico(*cad))
      {
         *cad = Convierte_may_min(*cad,3);
         while (*cad && !Es_caracter_espaciado(*cad)) cad++;
      }
      else cad++;
   }
}



// Extrae de la cadena CAD el numero de caracteres indicados en N_C a partir de la posicion P_I partiendo de cero, retornando un puntero a ella
unsigned int Cadenas::Substr(const char *cad, const unsigned int p_i, const unsigned int n_c, char *cadobj)
{
   unsigned int i = 0, xi = 0;
   // Lee toda la cadena
   while (*cad)
   {
      // extrae la porci¢n indicada de esta
      if (i >= p_i)
      {
         if (xi >= n_c) break;
         *cadobj = *cad;
         cadobj++,xi++;
      }
      cad++,i++;
   }
   *cadobj = 0;
   return xi;
}


// Retorna la longitud de la cadena sin los espacios al final de esta
unsigned int Cadenas::Lg_cadena_sin_espacios_final(const char *cad)
{
   unsigned int i = 0, pos = 0;
   const char *ptr = cad;
   while (*ptr)
   {
      if (*ptr != ' ') pos = i;
      ptr++,i++;
   }
   if (!pos)
   {
      // Si la cadena es nula o solo cuenta con un caracter
      if (!*cad || *cad == 32) return 0;
   }
   return (pos+1);
}


// Retorna la longitud de la cadena sin espacios
unsigned int Cadenas::Lg_cadena_sin_espacios(const char *cad)
{
   unsigned int i = 0;
   const char *ptr = cad;
   while (*ptr)
   {
      if (*ptr != ' ') i++;
      ptr++;
   }
   return (i);
}


// Quita los espacios que existan al inicio y al final de la cadena retornando la longitud de la cadena
unsigned int Cadenas::trim(char *cad)
{
   unsigned int ind, i, pos;

   i = 0;
   // Salta los espacios en blanco al inicio de la cadena
   while (cad[i] == 32) i++;
   if (!cad[i])
   {
      cad[0] = 0;
      return 0;
   }
   ind = pos = 0;
   // Copia hasta el final de la cadena
   while (cad[i])
   {
      cad[ind] = cad[i];
      if (cad[ind] != 32) pos = ind;
      ind++,i++;
   }
   pos++;
   cad[pos] = 0;
   return pos;
}


// Quita los espacios que existan al inicio y al fin de la cadena CAD dejandola en la cadena CADOBJ, retornando la longitud de la cadena
unsigned int Cadenas::trim(const char *cad, char *cadobj)
{
   unsigned int ind = 0, i = 0, pos = 0;
   // Salta los espacios al inicio de la cadena
   while (cad[i] == 32) i++;
   if (!cad[i])
   {
      cadobj[0] = 0;
      return 0;
   }
   // Copia el resto de la cadena
   while (cad[i])
   {
      cadobj[ind] = cad[i];
      if (cadobj[ind] != 32) pos = ind;
      i++, ind++;
   }
   pos++;
   cadobj[pos] = 0;
   return pos;
}


// Inserta el caracter CAR en la posicion POS recorriendo todos los caracteres siguientes
void Cadenas::Inserta_caracter(char *cad, const unsigned int pos, const char car)
{
   unsigned int i = 0;
   char xcar = car ,ycar = 0;
   while (*cad)
   {
      if (i >= pos) ycar = *cad, *cad = xcar, xcar = ycar;
      cad++, i++;
   }
   *cad = ycar;
   cad++;
   *cad = 0;
}


// Alinea el contenido de la cadena CAD a la longitud LG y retorna esta en la cadena XCAD
// Si tp es (IZQUIERDA) Alinea a la izquierda
//          (CENTRADA)  Alinea al centro
//          (DERECHA)   Alinea a la derecha
void Cadenas::Alinea_cadena(const char *cad, const unsigned int lg, const int tp, char *xcad)
{
   char *tmp = asignaPunteroSinCopiar(cad);
   unsigned int xlg, i, md, xi;

   xlg = trim(cad, tmp);
   if (xlg >= lg)
   {
      strcpy(xcad,tmp);
      delete []tmp;
      return;
   }
   switch (tp)
   {
   case IZQUIERDA: // Alineada a la izquierda
      strcpy(xcad,tmp);
      for (i = xlg; i < lg; i ++) xcad[i] = ' ';
      break;
   case CENTRADA: // Alineada al centro
      md = (lg - xlg) / 2;
      for (i = 0; i < md; i ++) xcad[i] = ' ';
      for (i = 0; i < xlg; i ++) xcad[i + md] = tmp[i];
      for (i = (md + xlg); i < lg; i ++) xcad[i] = ' ';
      break;
   case DERECHA: // Alineada a la izquierda
      for (i = 0; i < (lg - xlg); i ++) xcad[i] = ' ';
      for (i = (lg - xlg), xi = 0; i < lg; i ++, xi ++) xcad[i] = tmp[xi];
      break;
   }
   xcad[lg] = 0;
   delete []tmp;
}


// Quita de la cadena CAD, la(s) ocurrencia(s) del caracter CAR
// si T_P es (1) Extrae todos los caracteres de la cadena
//           (2) Extrae sólo la primera ocurrencia del caracter
void Cadenas::Quitar_caracter(char *cad, const char car, const unsigned int t_p)
{
   unsigned int i = 0, xi = 0, sw = 1;
   switch (t_p)
   {
   case 1:
      while (cad[i])
      {
         if (cad[i] != car) cad[xi++] = cad[i];
         i++;
      }
      cad[xi] = 0;
      break;
   case 2:
      while (cad[i])
      {
         if (sw)
         {
            if (cad[i] != car) cad[xi++] = cad[i];
            else sw = 0;
         }
         else cad[xi++] = cad[i];
         i++;
      }
      cad[xi] = 0;
      break;
   }
}


// Expande una cadena del tipo (1,2,4-7,9) dejandola como (1,2,4,5,6,7,9)
void Cadenas::Expander_Cadena_numerica_entera(const char *cad, char *xcad)
{
   int sw, i = 0, xi = 0, xxi, lg = 0, minimo, maximo, ind;
   char xcad1[1000], xcad2[100], xcad3[100];

   while (cad[i])
   {
      if (cad[i] != ',') xcad1[xi] = cad[i], xi++;
      else
      {
         xcad1[xi] = 0;
         xi = 0, sw = 0;
         while (xcad1[xi])
         {
            if (xcad1[xi] == '-')
            {
               sw = 1;
               break;
            }
            xi++;
         }
         if (!sw)
         {
            xi = 0;
            if (lg)
            {
               xcad[lg] = ',';
               lg ++;
            }
            while (xcad1[xi]) xcad[lg] = xcad1[xi], xi++, lg++;
         }
         else
         {
            xcad1[xi] = 0;
            minimo = atoi(xcad1);
            xxi = 0;
            while (xcad1[xi+1+xxi]) xcad2[xxi] = xcad1[xi+1+xxi], xxi++;
            maximo = atoi(xcad2);
            xcad[lg] = 0;
            if (lg > 0) strcat(xcad,",");
            for (ind = minimo; ind < maximo; ind++)
            {
               sprintf(xcad3,"%i",ind);
               strcat(xcad,xcad3);
               strcat(xcad,",");
            }
            sprintf(xcad3,"%i",ind);
            strcat(xcad,xcad3);
            lg = strlen(xcad);
         }
         xi = 0;
      }
      i++;
   }
   // Si se termina la cadena fuente
   xcad1[xi] = 0;
   xi = 0, sw = 0;
   while (xcad1[xi])
   {
      if (xcad1[xi] == '-')
      {
         sw = 1;
         break;
      }
      xi++;
   }
   if (!sw)
   {
      xi = 0;
      if (lg)
      {
         xcad[lg] = ',';
         lg ++;
      }
      while (xcad1[xi]) xcad[lg] = xcad1[xi], xi++, lg++;
   }
   else
   {
      xcad1[xi] = 0;
      minimo = atoi(xcad1);
      xxi = 0;
      while (xcad1[xi+1+xxi]) xcad2[xxi] = xcad1[xi+1+xxi], xxi++;
      maximo = atoi(xcad2);
      xcad[lg] = 0;
      if (lg > 0) strcat(xcad,",");
      for (ind = minimo; ind < maximo; ind++)
      {
         sprintf(xcad3,"%i",ind);
         strcat(xcad,xcad3);
         strcat(xcad,",");
      }
      sprintf(xcad3,"%i",ind);
      strcat(xcad,xcad3);
      lg = strlen(xcad);
   }
   xcad[lg] = 0;
}


