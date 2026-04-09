# Módulo API_debounce - Practica4 Punto 2

Este punto consiste en la modularización de la lógica de anti-rebote en un driver reutilizable y su aplicación en un programa que alterna frecuencias de parpadeo.

##  Estructura del Proyecto
El módulo se organiza siguiendo las buenas prácticas de abstracción para sistemas embebidos:
- `/drivers/API/inc/API_debounce.h`: Prototipos de funciones públicas y tipos de datos.
- `/drivers/API/src/API_debounce.c`: Implementación privada, MEF y variables de estado.

## Características del Módulo
- **Encapsulamiento:** El tipo `debounceState_t` y la variable de estado son privados (`static`) dentro del archivo `.c`.
- **Detección de Flanco:** Implementa una bandera interna que se activa en el flanco descendente (`BUTTON_FALLING` a `BUTTON_DOWN`).
- **Función `readKey()`:** Permite al usuario consultar si el botón fue presionado. Es de tipo "lectura y limpieza" (devuelve el estado y lo resetea a `false`).

## Aplicación Principal
El programa principal utiliza el módulo `API_debounce` y `API_delay` para:
1. Monitorear el estado del pulsador mediante `debounceFSM_update()`.
2. Consultar cambios con `readKey()`.
3. Alternar la frecuencia de parpadeo de un LED entre **100 ms** y **500 ms** cada vez que se confirma una pulsación.

