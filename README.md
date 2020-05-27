# ConcuBread
Primer proyecto de la materia 75.59 - Técnicas de Programación Concurrente I
Nicolás Longo - 98271

En la carpeta root se encontrarán el informe y una carpeta images en la que se encuentran los diagramas del Informe (para poder consultarlos también por fuera).
Luego, en la carpeta ConcuBread se encuentra el código propiamente dicho.
A continuación, la documentación


# Documentación

## Comandos para compilar el programa:

```cmake .```

```make```

### Comandos para correr el programa:

Este ejecutable no recibe parámetros. Utiliza un archivo de configuración para definirlos. Este se encuentra en '/config/', se llama 'config.txt' y permite setear los siguientes parámetros:
	-	Cantidad de Recepcionistas
	-	Cantidad de Maestros Panaderos
	-	Cantidad de Maestros Pizzeros
	-	Cantidad de Repartidores
	-	Archivo de pedidos (este archivo debe colocarse en el directorio '/pedidos/'')


```./ConcuBread```

Si se quiere ejecutar el chequeo de memoria con valgrind:

```valgrind --leak-check=full --show-leak-kinds=all ./ConcuBread```


### Archivos de prueba:
- pedidosCorto.txt:
	-	Son 5 pedidos en total
	-	Pedidos de panes: 3
	-	Pedidos de pizza: 2

- pedidosRazonable.txt:
	-	Son 25 pedidos en total
	-	Pedidos de panes: 12
	-	Pedidos de pizza: 13

- pedidosEstres01.txt:
	-	Son 150 pedidos en total
	-	Pedidos de panes: 72
	-	Pedidos de pizza: 78

- pedidosEstres02.txt:
	-	Son 1050 pedidos en total
	-	Pedidos de panes: 504
	-	Pedidos de pizza: 546

En todos los casos, como ya se mencionó, el archivo de pedidos debe encontrarse en el path '/pedidos/'

### Lista de pedidos procesados (archivo de salida):
La salida para todos los archivos se encuentra en el directorio '/entregados/' bajo el nombre de 'entregados.txt'

### Archivos de log:
Los archivos de log se almacenan en el directorio '/logfiles/' y poseen en su nombre el timestamp correspondiente al inicio de la ejecución.

Latex project (overleaf) link to share and edit:
https://es.overleaf.com/1532886356kxcxmtrhcvsf
