# Practica Evaluada 03 - Modelo C (Cola de envios con cancelacion y prioridad)

Programacion 2 (PR2) - Seccion 02. C++17, sin librerias externas.

## Compilacion

```bash
make test    # verifica requisitos minimos
make main    # compila y ejecuta la demo
make clean
```

## Reparto de roles

| Integrante | C.I. | Rol |
| :--- | :--- | :--- |
| Santiago Zerpa | V-32451779 | ChatCola: encolarMensaje, procesarSiguiente, procesarTodos |
| Santiago Ruiz | V-32709123 | ChatCola: cancelarEnvio, subirPrioridad, bajarPrioridad |
| Nicolas Lopez | V-30024260 | ColaEnvios: encolar, desencolar, vaciar, tamanio, guardarCSV, cargarCSV, limpiar y frente |
| (completar) | | ColaEnvios |
| (completar) | | ColaEnvios |
| (completar) | | ColaEnvios |

## Aporte de Santiago Ruiz (ChatCola.cpp)

- `cancelarEnvio(int id)`: delega en `ColaEnvios::cancelar`. Solo afecta mensajes pendientes; retorna `false` si el id no esta en la cola (por ejemplo, si ya fue enviado).
- `subirPrioridad(int id)`: delega en `ColaEnvios::moverAlFrente`. No cambia el estado del mensaje.
- `bajarPrioridad(int id)`: delega en `ColaEnvios::moverAlFinal`. No cambia el estado del mensaje.

Estos tres metodos dependen de que `cancelar`, `moverAlFrente` y `moverAlFinal` esten implementados en `ColaEnvios.cpp`.

## Uso de IA

- **Claude (Anthropic):** ayudo a Santiago Ruiz a escribir `cancelarEnvio`, `subirPrioridad` y `bajarPrioridad` en `ChatCola.cpp`, a completar sus datos en el encabezado y a redactar esta seccion del README. El codigo fue revisado y comprendido por el autor.
