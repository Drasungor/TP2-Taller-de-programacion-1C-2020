# TP2-Taller-de-programación-1C-2020

Nombre: Agustín Cambiano

Padrón: 102291

URL: https://github.com/Drasungor/TP2-Taller-de-programacion-1C-2020.git


## Trabajo práctico No 2: Recolectores y productores

&nbsp;&nbsp;&nbsp;&nbsp;El presente trabajo tiene el objetivo de describir el
funcionamiento de una sección del programa realizado para cumlpir con la
consigna de desarrollar un ejecutable que
genera puntos de beneficio según los trabajadores y materiales disponibles.  
&nbsp;&nbsp;&nbsp;&nbsp;La sección a desarrollar es aquella que se encarga de
cargar los recursos en el inventario y luego descargarlos para consumirlos y
generar así puntos de beneficio. Para esto se crearon las clases "Gatherers",
"GatherersGroup", "Producers", "ProducersGroup", "Inventory" y "BlockingQueue".

### <ins>Clases</ins>

#### Inventory
&nbsp;&nbsp;&nbsp;&nbsp;El inventario es una clase protegida contra condiciones
de carrera. Se utiliza para guardar los recursos recolectados, actúa como
un buffer que comunica Gatherers con Producers. Almacena los recursos
proporcionados por los GatherersGroup, y descarga los recursos pedidos por
ProducersGroup. La única operación bloqueante que tiene es la que consume los
recursos pedidos, ya que espera a que estos se encuentren disponibles
(notificando cuando se agrega un recurso o se cierra la entrada a todos los
threads que se encuentren esperando para consumir recursos) para poder ser
consumidos o a que se cierre la entrada del inventario.

#### ProducersGroup
&nbsp;&nbsp;&nbsp;&nbsp;Esta clase representa un grupo de productores, es
decir, una cantidad de productores de un tipo de productor específico. Se
encarga de pedir al inventario los recursos que necesite y con estos generar
la cantidad de puntos de beneficio apropiada hasta que se cierre la entrada
del inventario y no se encuentre disponible la cantidad necesaria de los
recursos a consumir para generar los puntos de beneficio. Para hacer esto
genera una cantidad recibida de threads, que realizan este trabajo
simultáneamente y por separado. Al crearse recibe los recursos que va a
consumir para generar los puntos de beneficio, los puntos de beneficio que
generará y la cantidad de productores que representa, es decir, la cantidad
de threads que generará.

#### Producers
&nbsp;&nbsp;&nbsp;&nbsp;Representa todos los productores existentes, almacena
un ProducersGroup por cada tipo de productor existente y a cada uno le
proporciona la cantidad de productores que debe representar y qué tipo de
productor debe representar (pasándole los recursos que debe consumir y los
puntos de beneficio que producen).

#### BlockingQueue
&nbsp;&nbsp;&nbsp;&nbsp;Esta clase representa una cola bloqueante, es decir,
una cola que cuando un thread intenta obtener un elemento almacenado se
bloquea hasta que haya al menos un elemento en la cola o la cola esté cerrada.
Cuando se agrega un elemento a la cola o esta es cerrada, se notifica a todos
los threads que están intentando sacar un elemento.

#### GatherersGroup
&nbsp;&nbsp;&nbsp;&nbsp;Esta clase representa un grupo de recolectores, es
decir, una cantidad de recolectores de un tipo de recolector específico. Se
encarga de sacar un recurso de la cola bloqueante correspondiente y
otorgarselo al inventario para que lo almacene, este trabajo es realizado
hasta que la cola de la cual se sacan los recursos esté cerrada y no tenga
más elementos. Para hacer esto genera una cantidad recibida de threads, que
realizan este trabajo simultáneamente y por separado. Al crearse recibe una
referencia a la cola de la que sacará los recursos a almacenar y la cantidad
de recolectores que representa, es decir, la cantidad de threads a ejecutar.

#### Gatherers
&nbsp;&nbsp;&nbsp;&nbsp;Representa todos los recolectores existentes, almacena
un GatherersGroup por cada tipo de recolector existente y a cada uno le
proporciona la cantidad de recoletores que representa y la cola de la que
sacará los recursos.



![Diagrama_de_clases](/img/Diagrama de clases.png)

Este es un ejemplo de texto que da entrada a una lista genérica de elementos:

- Elemento 1
- Elemento 2
- Elemento 3

Este es un ejemplo de texto que da entrada a una lista numerada:

1. Elemento 1
2. Elemento 2
3. Elemento 3

Al texto en Markdown puedes añadirle formato como **negrita** o *cursiva* de una manera muy sencilla.
