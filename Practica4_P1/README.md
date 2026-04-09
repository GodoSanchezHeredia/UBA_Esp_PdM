# UBA_Esp_PdM
# Practica 3: Modularización P3

Implementar un módulo de software para trabajar con retardos no bloqueantes a partir de las funciones creadas en la práctica 2.

## Punto 1

Encapsular las funciones necesarias para usar retardos no bloqueantes en un archivo fuente API_delay.c con su correspondiente archivo de cabecera API_delay.h, y ubicar estos archivos en la carpeta API creada. `Core/API`:

* **API_delay.h**: Definición de tipos de datos (`tick_t`, `bool_t`) y la estructura `delay_t`.
* **API_delay.c**: Implementación .

### Componentes de la estructura `delay_t`
- `startTime`: Almacena el tiempo de inicio del retardo.
- `duration`: Duración del retardo en milisegundos.
- `running`: Flag booleano que indica si el retardo está activo.

## Funciones Principales

1.  **`delayInit`**: Configura la duración del retardo e inicializa el estado en `false`.
2.  **`delayRead`**: La función más crítica. Utiliza una máquina de estados para:
    * Si el retardo no está ejecutándose, toma el tiempo actual y se activa.
    * Si está ejecutándose, compara el tiempo actual con el de inicio para verificar si se cumplió el tiempo.
3.  **`delayWrite`**: Permite actualizar la duración de un retardo ya existente.
4.  **`delayIsRunning`**: Esta función debe devolver una copia del valor del campo running de la estructura delay_t

