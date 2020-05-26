# ConcuBread
Primer proyecto de la materia 75.59 - Técnicas de Programación Concurrente I
Nicolás Longo - 98271

# Documentación

## Comandos para compilar el programa:

```cmake .```
```make```

## Comandos para correr el programa:

Este ejecutable no recibe parámetros. Utiliza un archivo de configuración para definirlos que se encuentra en /config/ y se llama config.txt

```./ConcuBread```

Si se quiere ejecutar el chequeo de memoria con valgrind:

```valgrind --leak-check=full --show-leak-kinds=all ./ConcuBread```


## Archivos de prueba:
- pedidosCorto.txt:
	-	Son 5 pedidos en total.
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

En todos los casos los archivos de pedidos deben encontrarse en el path '/pedidos/'

## Lista de pedidos procesados (archivo de salida):
La salida para todos los archivos se encuentra en la carpeta '/entregados/' bajo el nombre de 'entregados.txt'


Latex (overleaf) link to share and edit:
https://es.overleaf.com/1532886356kxcxmtrhcvsf
