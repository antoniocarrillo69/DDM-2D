/** @mainpage Grupo de Modelación Matemática y Computacional
 *
 * @section intro_sec Introducción
 *
 * La presente documentación es un esfuerzo del grupo de Modelación Matemática 
 * y Computacional en que se llevan a cabo actividades como el acopio, 
 * la organización, la documentación y publicación de algoritmos, métodos, 
 * modelos, paquetes, sitios afines, etc, para el uso de investigadores y 
 * estudiantes interesados en dichas disciplinas. 
 *
 * @subsection sub1 ¿Para que fue desarrollado el programa? 
 * El programa ha sido desarrollado con fines académicos y de investigación, más específicamente, para probar diferentes métodos de discretización (FEM y FDM) usados en la solución 
 * de problemas de ecuaciones diferenciales parciales con valores en la frontera. Este trabajo es realizado por alumnos del posgrado (en ciencias de la tierra como de 
 * ciencias en computación de la UNAM) para probar las metodologías que desarrollan en sus respectivos trabajos académicos. Estos programas son liberados como software
 * libre bajo la licencia GPL. 

 * @subsection sub2 ¿Qué es el software libre? 
 * En primer lugar, un software cuyo secreto de fabricación (el llamado "código fuente", algo así como los "planos" del programa) es conocido y difundido libremente. El 
 * autor del software concede a cualquiera el derecho a usar su obra, a modificarla y a adaptarla a sus necesidades específicas. Este derecho de libre uso a veces se 
 * otorga sin restricciones (licencias tipo BSD) y otras veces con la única condición de que toda mejora se distribuya con las mismas condiciones de uso que tiene 
 * originalmente y por tanto siga estando libremente disponible para todo el mundo (licencias tipo copyleft, como la GPL de la Free Software Foundation). A diferencia de 
 * lo que sucede con el software propietario cuyo único objetivo es la rentabilidad económica y no el hacer buenas herramientas, la comunidad del software libre se 
 * empeña en la búsqueda de una buena adecuación entre las necesidades y el propio producto, esto es, busca a la vez la calidad y la eficiencia social que otorga la 
 * libertad de uso. 

 * @subsection sub3 ¿Qué tipo de dato de punto flotante se usa en el programa? 
 * Se pueden usar double y long double, el tipo de dato se define en el archivo Definiciones.hpp al comentar o descomentar la directiva de compilación __Double__, por 
 * omisión el tipo de dato usado es double, al ser este aceptado en todos los compiladores de C++. 

 * @section comp_sec ¿Cómo compilo y ejecuto el programa? 
 * Primeramente hay que bajar los fuentes de cada ejemplo (en el código de los ejemplos sólo cambia la función principal Principal.cpp y el archivo Problema.cpp).
 
 * Si compila en LINUX o UNIX usar: 

 * $ g++ -O1 *.cpp -o ejemp 

 * Para ejecutar el programa ya compilado 

 * $ ./ejemp 

 * Si compila en Windows, recomendamos el uso del compilador MinGW Minimalist GNU for Windows (Compilador de linea para C, C++, Fortran, Ada, Java, Pascal, ObjC, etc, 
 *  para 32 y 64 bits) usando las mismas opciones que anteriormente se describieron. 


 * @section license_sec Licencia
 * Este programa es software libre. Puede redistribuirlo y/o modificarlo 
 * bajo los términos de la Licencia Pública General de GNU según es                  
 * publicada por la Free Software Foundation, bien de la versión 2 de               
 * dicha Licencia o bien (según su elección) de cualquier versión                   
 * posterior.                                                               
                                                                         
 * Este programa se distribuye con la esperanza de que sea útil, pero SIN   
 * NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin      
 * garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la        
 * Licencia Pública General de GNU para más detalles.                       
                                                                         
 * Debería haber recibido una copia de la Licencia Pública General junto    
 * con este programa. Si no ha sido así, escriba a la Free Software         
 * Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.            
 * 
 * 
 */

