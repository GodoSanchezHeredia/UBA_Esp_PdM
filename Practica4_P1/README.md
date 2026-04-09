# Implementación de MEF Anti-rebote (Debounce) - Punto 1

Este proyecto implementa una Máquina de Estados Finitos (MEF) para eliminar los rebotes mecánicos de un pulsador, asegurando una lectura limpia de las entradas digitales en un sistema embebido.

##  Descripción
La lógica se basa en cuatro estados principales que filtran las transiciones rápidas (ruido) del pulsador mediante un retardo no bloqueante de **40 ms**.

### Estados de la MEF
- `BUTTON_UP`: Estado de reposo (botón sin presionar).
- `BUTTON_FALLING`: Detecta la transición inicial (posible rebote).
- `BUTTON_DOWN`: Estado estable de botón presionado.
- `BUTTON_RAISING`: Detecta la liberación del botón (posible rebote).

##  Funciones Implementadas
- `debounceFSM_init()`: Inicializa la MEF en el estado `BUTTON_UP`.
- `debounceFSM_update()`: Ejecuta la lógica de transición de estados y lectura de entradas. Se debe llamar periódicamente en el lazo principal.
- `buttonPressed()`: Acción ejecutada al detectar una presión válida (Enciende el LED).
- `buttonReleased()`: Acción ejecutada al detectar una liberación válida (Apaga el LED).

##  Especificaciones Técnicas
- **Tiempo de debounce:** 40 ms.
- **Mecanismo:** Retardos no bloqueantes (API_delay).
- **Entorno:** STM32 / ARM Cortex.