# TP2-Taller-de-programacion-1C-2020


-CAMBIAR LOS INSERTS DE LOS MAPS POR ASIGNACIONES CON EL OPERADOR []
-VER SI HAY QUE JUNTAR LOS ENUMS EN UN UNICO .h
-VER SI TENGO QUE HACER UNA FUNCION QUE TIRE LOS THREADS PARA UN GRUPO
DE TRABAJADORES, SINO LOS TIRA EN EL CONSTRUCTOR
-Pasar la lectura del archivo a CollectorsAndProducers y tirar la funcion
de threads desde ahi, despues se cargan los materiales y despues se hace el
join
-Ver si hay que borrar Producers.cpp y Producers.h
-Cambiar los join por release_gatherers y get_produced_points
-CAMBIAR TODOS LOS MAPS POR UNORDERED MAPS
-AGREGAR CONST A LAS FUNCIONES QUE NO MODIFIQUEN LOS OBJETOS QUE LLAMAN
-CAMBIAR EL requested_resources[it->first] por un it->second PORQUE ESO ES
O(1) Y LO PRIMERO ES O(log(n))
-BORRAR EL CONSTRUCTOR POR COPIA DE GATHERES y ProducersGroup PORQUE ESTA
IMPLICITAMENTE BORRADO
