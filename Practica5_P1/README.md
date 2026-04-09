# API_uart

Este módulo proporciona una interfaz de abstracción para el manejo de la comunicación serie (UART) en sistemas embebidos, garantizando la seguridad en el manejo de punteros y la validación de datos.

## Estructura
- `API/inc/API_uart.h`: Prototipos de funciones públicas.
- `API/src/API_uart.c`: Implementación privada y lógica de control.

## Funciones Principales
- **uartInit()**: Inicializa el periférico y envía un mensaje de configuración por terminal. Retorna `true` si la operación fue exitosa.
- **uartSendString(pstring)**: Envía una cadena completa (hasta el caracter nulo `\0`).
- **uartSendStringSize(pstring, size)**: Envía una cantidad específica de bytes (1-256).
- **uartReceiveStringSize(pstring, size)**: Recibe una cantidad fija de caracteres.

## Reglas de Implementación
* **Validación de Parámetros**: Se verifica que ningún puntero sea `NULL` y que los tamaños estén dentro del rango permitido (1 a 256).
* **Gestión de Errores**: Se valida el valor de retorno de cada función de la HAL (`HAL_OK`).
* **Encapsulamiento**: Uso de variables `static` para proteger el estado interno del módulo.