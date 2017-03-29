Métodos de Descomposición de Dominio

Los métodos de descomposición de dominio introducen desde la formulación matemática del problema una separación natural de las tareas a realizar por el método y simplifican considerablemente la transmisión de información entre los subdominios. En ellos, los sistemas físicos representados por su modelo son descompuestos en varios subdominios.

Los métodos de descomposición de dominio permiten tratar los problemas de tamaño considerable, empleando algoritmos paralelos en computadoras secuenciales y/o paralelas. Esto es posible ya que cualquier método de descomposición de dominio se basa en la suposición de que dado un dominio computacional este se puede particionar en subdominios entre los cuales puede o no existir traslape. Entonces,el problema es reformulado en términos de cada subdominio (empleando algún método del discretización) obteniendo una familia de subproblemas de tamaño reducido independientes en principio entre si, y que están acoplados a través de la solución en la interfaz de los subdominios que es desconocida.

De esta manera, podemos clasificar de forma burda a los métodos de descomposición de dominio, como aquellos en que: existe traslape entre los subdominios y en los que no existe traslape. A la primera clase pertenece el método de Schwarz (en el cual el tamaño del traslape es importante en la convergencia del método) y a los de la segunda clase pertenecen los métodos del tipo subestructuración (en el cual los subdominios sólo tienen en común los nodos de la frontera interior).

Estos métodos son un paradigma natural usado por la comunidad de modeladores. Los sistemas físicos son descompuestos en dos o más subdominios contiguos basados en consideraciones fenomenológicas. Estas descomposiciones basadas en dominios físicos son reflejadas en la ingeniería de software del código correspondiente.

Así, mediante los métodos de descomposición de dominio, la programación orientada a objetos (que nos permite dividir en niveles la semántica de los sistemas complejos tratando así con las partes, más manejables que el todo, permitiendo su extensión y un mantenimiento más sencillo) y esquemas de paralelización que usan el paso de mensajes, es posible construir aplicaciones que
coadyuven a la solución de problemas concomitantes en ciencia e ingeniería.

Esta metodología permite utilizar todas las capacidades del cómputo en paralelo (grids de decenas de clusters, cada uno con miles de procesadores interconectados por red con un creciente poder de cómputo medible en Peta Flops), así como el uso de una amplia memoria (ya sea distribuida y/o compartida del orden de Tera Bytes), permitiendo atacar una gran variedad de problemas que sin estas técnicas es imposible hacerlo de manera flexible y eficiente.

Pero hay que notar que existe una amplia gama de problemas que nos interesan resolver que superan las capacidades de cómputo actuales, ya sea por el tiempo requerido para su solución, por el consumo excesivo de memoria o ambos.

La lista de los métodos de descomposición de dominio y el tipo de problemas que pueden ser atacados por estos, es grande y está en constante evolución, ya que se trata de encontrar un equilibrio entre la complejidad del método (aunada a la propia complejidad del modelo), la eficiencia en el consumo de los recursos computacionales y la precisión esperada en la solución encontrada por los diversos métodos y las arquitecturas paralelas en la que se implante.

