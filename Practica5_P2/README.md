# API_cmdparser

Este módulo implementa un intérprete de comandos basado en una **Máquina de Estados Finitos (MEF)** para la interacción con sistemas embebidos vía UART. Permite el control de periféricos y la consulta de estados mediante una interfaz de consola serie.

## Arquitectura de la MEF

La lógica de recepción y procesamiento es **no bloqueante** y se divide en los siguientes estados:

* **CMD_IDLE**: Estado de espera. Descarta caracteres nulos y terminadores hasta detectar el inicio de una cadena válida.
* **CMD_RECEIVING**: Almacena caracteres en el `lineBuffer` y detecta el fin de línea (`\r` o `\n`). Incluye protección contra desbordamiento (*Overflow*).
* **CMD_PROCESS**: Utiliza `strtok` para la tokenización de la cadena en comando y argumentos. Normaliza el texto a mayúsculas para evitar errores de sensibilidad.
* **CMD_EXEC**: Compara el comando contra la base de funciones implementadas y ejecuta la acción en el hardware.
* **CMD_ERROR**: Gestiona e informa fallos específicos (comando desconocido, argumentos inválidos, buffer lleno).

## Comandos Implementados

| Comando | Acción |
| :--- | :--- |
| `HELP` | Despliega la lista de comandos disponibles y su uso. |
| `STATUS` | Informa por UART si el LED se encuentra encendido o apagado. |
| `LED ON` | Enciende el LED de forma permanente. |
| `LED OFF` | Apaga el LED de forma permanente. |
| `LED TOGGLE` | Alterna un parpadeo automático basado en un delay no bloqueante (500ms). |

## Características Principales

* **Manejo No Bloqueante**: El parpadeo del LED mediante `TOGGLE` se procesa independientemente de la recepción de comandos, asegurando que el sistema nunca se detenga.
* **Seguridad de Memoria**: El buffer de línea está limitado por `CMD_MAX_LINE`, evitando que entradas excesivamente largas corrompan la memoria.
* **Compatibilidad con Scripts**: El parser ignora líneas que comienzan con `#` o `//`, permitiendo el envío de archivos de comandos comentados.
* **Eco de Caracteres**: Implementa un eco automático hacia la terminal para que el usuario visualice lo que está escribiendo en tiempo real.

## Archivos del Módulo
- `API/inc/API_cmdparser.h`: Prototipos públicos, definiciones de tipos `cmd_status_t` y constantes de configuración.
- `API/src/API_cmdparser.c`: Implementación de la MEF, lógica de parpadeo y funciones de ejecución de comandos.

---
*Desarrollado como parte de la Especialización en Sistemas Embebidos.*