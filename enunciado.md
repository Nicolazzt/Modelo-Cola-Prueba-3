# Práctica Evaluada 03 — Modelo C: Cola de envíos pendientes (cancelar y prioridad)

**Asignatura:** Programación 2 (PR2) — Sección 02  
**Modalidad:** grupos de 3 o 4 integrantes  
**Lenguaje:** C++17, sin librerías externas  
**Duración:** miércoles 11 de noviembre de 2026, 12:00 p.m. – 2:00 p.m. (90 min de práctica + 30 min de revisión) + trabajo en casa  
**Puntaje:** 20 puntos (12 en clase + 8 en casa)  
**Estructura asignada:** cola enlazada (FIFO)

> [!IMPORTANT]
> **Medio de entrega:** correo electrónico a **`jdanieldp99@gmail.com`**.
> **No se adjuntan archivos `.cpp`.** El mensaje debe incluir **la captura de `make test` funcionando durante la clase** y **el enlace del repositorio** de GitHub/GitLab. Ver la plantilla completa en la **Sección 10**.
>
> **Fecha límite:** **miércoles 11 de noviembre de 2026, 11:59 p.m.** (el mismo día de la práctica).
> **Retardo:** **−5 puntos** sobre la nota final.
> **Puntos extra:** quienes entreguen el **resultado completo durante el tiempo de clase** recibirán puntos extra **a criterio del preparador**.

---

## 1. Contexto

En la Evaluación 1 modelaron un sistema de mensajería con usuarios, chats, mensajes y estados (`Pending → Sent → Delivered → Opened`). Ahora deben extender ese sistema con una **cola de envíos pendientes**: los mensajes se encolan cuando el usuario los escribe y se procesan en orden de llegada, como una bandeja de salida. Además, el usuario debe poder **cancelar un envío** antes de que se procese o **subir o bajar su prioridad** para que salga antes o después que los demás.

La cola debe implementarse **desde cero** con nodos enlazados. No se permite usar `std::queue` ni `std::deque`. El núcleo de mensajería (`User`, `TextMessage`, `Chat`) es una **adaptación mínima de la carpeta original de la Evaluación 1** y ya está resuelto en la carpeta `nucleo/` incluida en este modelo.

---

## 2. Qué debe implementar

### A. `ColaEnvios` (`ColaEnvios.hpp` / `.cpp`)

Cola enlazada de `TextMessage`. Cada nodo debe tener el mensaje y un apuntador al siguiente nodo. La cola debe recordar el frente y el final.

| Método | Comportamiento |
| :--- | :--- |
| `ColaEnvios()` | Cola vacía: `vacia() == true`, `tamanio() == 0`, `frente() == nullptr`. |
| `encolar(const TextMessage&)` | Inserta al final. Retorna `false` si ya existe un mensaje con el mismo `id`. |
| `desencolar()` | Retira el frente y libera el nodo. Retorna `false` si la cola está vacía. |
| `frente()` | Retorna apuntador al primer mensaje o `nullptr`. Debe existir versión `const` y no `const`. |
| `limpiar()` | Deja la cola vacía. |
| `aVector()` | Retorna los mensajes de **frente a final**, sin modificar la cola. |
| `buscarPorId(int id)` | Busca el mensaje con ese `id` en la cola y retorna un apuntador o `nullptr`. Debe existir versión `const` y no `const`. |
| `cancelar(int id)` | Elimina el mensaje con ese `id` esté donde esté en la cola, actualizando `frente_`, `final_` y `cantidad`. Retorna `false` si no existe. |
| `moverAlFrente(int id)` | Saca el mensaje de su posición y lo coloca en el frente (sube su prioridad). Retorna `false` si no existe. |
| `moverAlFinal(int id)` | Saca el mensaje de su posición y lo coloca al final (baja su prioridad). Retorna `false` si no existe. |
| `invertir()` | Invierte el orden de los nodos: el final pasa a ser el frente y viceversa. |
| `guardarCSV(ruta)` | Guarda una línea por mensaje, en orden FIFO. Retorna `false` si no puede abrir. |
| `cargarCSV(ruta)` | Limpia la cola y carga los mensajes conservando el orden. Retorna `false` si no puede abrir. |

**Copia, movimiento y liberación (regla de tres/cinco):** copia profunda y movimiento seguro (el origen queda vacío), sin fugas ni dobles liberaciones.

### B. `ChatCola` (`ChatCola.hpp` / `.cpp`)

Hereda de `Chat`, usa una `ColaEnvios` para los pendientes y un `std::vector<TextMessage>` para los enviados.

| Método | Comportamiento |
| :--- | :--- |
| `encolarMensaje(TextMessage)` | Valida que el remitente participe, que el `id` no esté pendiente ni enviado y que el mensaje esté `Pending`. Luego lo encola. Retorna `false` si alguna validación falla. |
| `procesarSiguiente()` | Toma el frente, lo marca `Sent`, lo agrega a `enviados` y lo desencola. Retorna `false` si no hay pendientes. |
| `procesarTodos()` | Procesa todos los pendientes y retorna cuántos procesó. |
| `cancelarEnvio(int id)` | Cancela un mensaje pendiente antes de procesarlo. Retorna `false` si el `id` no está en la cola. |
| `subirPrioridad(int id)` | Mueve un mensaje pendiente al frente de la cola. Retorna `false` si el `id` no está en la cola. |
| `bajarPrioridad(int id)` | Mueve un mensaje pendiente al final de la cola. Retorna `false` si el `id` no está en la cola. |
| `siguientePendiente()` | Retorna el mensaje del frente o `nullptr`. |
| `cantidadPendientes()` | Retorna el tamaño de la cola. |
| `cantidadEnviados()` | Retorna la cantidad de mensajes ya enviados. |
| `getEnviados()` | Retorna el vector de enviados. |
| `getPendientes()` | Retorna la cola de pendientes. |
| `buscarEnviado(int id)` | Retorna apuntador al enviado o `nullptr`. |

### C. Reglas de estado

- Un mensaje se encola en estado `Pending`.
- Al procesarse, pasa a `Sent` y se registra en `enviados`.
- No se puede encolar un mensaje que ya esté `Sent`, `Delivered` o `Opened`.
- No se puede repetir el mismo `id` entre pendientes y enviados.
- `cancelarEnvio(id)` solo afecta a mensajes que sigan en la cola de pendientes.
- `subirPrioridad(id)` no cambia el estado del mensaje; solo lo mueve al frente.
- `bajarPrioridad(id)` no cambia el estado del mensaje; solo lo mueve al final.
- Los mensajes ya enviados no se pueden cancelar ni cambiar de prioridad.

---

## 3. Reglas técnicas

- **Memoria:** pueden usar apuntadores inteligentes (`std::shared_ptr`, `std::unique_ptr`, `std::weak_ptr`) o apuntadores normales con `new` y `delete`. Si usan apuntadores normales, deben liberar todos los nodos y evitar dobles liberaciones. La ausencia de fugas es parte de la evaluación.
- **No usar** `std::queue` ni `std::deque` para la estructura evaluada.
- Sí se permite `std::vector` para los enviados, los participantes y `aVector()`.
- Nada de atributos públicos en las clases evaluadas.
- Una clase por par `.hpp` / `.cpp`.
- Compilar con `make test` sin errores y, preferiblemente, sin advertencias con `-Wall -Wextra -Wpedantic`.
- Comentarios en el código sin acentos.
- No modifiquen los archivos de `nucleo/`: ya están resueltos.

---

## 4. Formato CSV de la cola

Cada línea representa un mensaje, de frente a final:

```text
id,"remitente","contenido",Estado
```

Ejemplo:

```text
1,"u1","Primer mensaje",pending
2,"u2","Segundo mensaje",pending
3,"u3","Tercer mensaje",pending
```

Al cargar, el primer mensaje del archivo debe quedar en el frente de la cola.

---

## 5. Estructura de la carpeta

Este modelo es **independiente**: todo lo necesario está dentro de `modelo_c_cola/`.

```text
modelo_c_cola/
├── enunciado.md
├── Makefile
├── main.cpp                ← demo propia (evaluada en A5)
├── ColaEnvios.hpp / .cpp   ← completar
├── ChatCola.hpp / .cpp     ← completar
├── nucleo/                 ← código dado (no evaluado)
│   ├── User.hpp / .cpp
│   ├── MessageStatus.hpp / .cpp
│   ├── TextMessage.hpp / .cpp
│   ├── Chat.hpp / .cpp
│   └── CSV.hpp
└── tests/test_modelo.cpp   ← suite automática
```

Los archivos `.hpp` y `.cpp` de `ColaEnvios` y `ChatCola`, y `main.cpp`, incluyen al inicio el bloque de **datos del grupo**. Deben completarlo.

---

## 6. Inicio rápido y verificación mínima

```bash
cd modelo_c_cola

make test        # verifica requisitos mínimos (NO asigna nota)
make main        # compila y ejecuta tu demo (main.cpp)
make clean
```

La suite `tests/test_modelo.cpp` **NO asigna nota**. Solo verifica si el esqueleto ya cumple los requisitos mínimos:

| Bloque | Qué verifica |
| :--- | :--- |
| 1. Estructura desde cero | Nodos, enlaces, inserciones y recorridos |
| 2. Operaciones núcleo | Búsquedas, cancelaciones, prioridad y operaciones propias del modelo |
| 3. Integración con mensajería | Uso real de la estructura dentro del chat |
| 4. Casos borde y robustez | Estructura vacía, ids inexistentes, copia y movimiento |
| 5. Persistencia CSV | Guardar y cargar conservando orden y datos |

Al final imprime `CUMPLE EL MINIMO` o `AÚN NO CUMPLE EL MINIMO` con el número de verificaciones superadas. La nota la asigna el preparador con la rúbrica.

**`main.cpp` es una plantilla que ustedes deben completar.** No lo evalúa la suite: forma parte de la rúbrica (A5) como demo propia del grupo.

---

## 7. Reparto del trabajo (grupos de 3 o 4)

La práctica está diseñada para que **no alcance con que una sola persona programe todo**. Cada integrante debe tener una responsabilidad verificable en Git.

### Grupos de 4

| Rol | Responsabilidad | Evidencia en Git |
| :--- | :--- | :--- |
| **Estructura** | Nodos, enlaces, encolar/desencolar, copia y liberación (regla de tres/cinco), recorridos | Rama `feature/estructura-<nombre>` y commits de los `.cpp` de la estructura |
| **Integración** | `ChatCola`, procesamiento FIFO, cancelación, prioridad, validaciones de participantes y estados | Rama `feature/integracion-<nombre>` y PR con revisión |
| **Pruebas y persistencia** | Casos borde, CSV, ejecución de `make test`, reporte de fallos | Rama `feature/tests-<nombre>` y comentarios en issues |
| **Main, documentación y QA** | `main.cpp`, README, `.gitignore`, tablero de issues, revisión final | Rama `feature/docs-<nombre>`, PR final y tag |

### Grupos de 3

| Rol | Responsabilidad |
| :--- | :--- |
| **Estructura** | Nodos, enlaces, operaciones, copia y liberación |
| **Integración + persistencia** | `ChatCola`, procesamiento, cancelación, prioridad, validaciones y CSV |
| **Pruebas + main + docs + Git** | Casos borde, demo, README, issues, PRs y tag |

> El rol no es excluyente: todos deben entender todo. La participación de cada integrante se evidencia en el historial de Git y en la observación durante la clase.

---

## 8. Cronograma de la sesión

**Miércoles 11 de noviembre de 2026**

| Hora | Actividad |
| :--- | :--- |
| **12:00 – 12:10** | Formar grupos, asignar modelo, crear repositorio y tablero de issues |
| **12:10 – 12:20** | Leer el enunciado, acordar el diseño de nodos y firmar los headers |
| **12:20 – 1:05** | Implementar bloques 1-2 de la suite (estructura y operaciones núcleo) |
| **1:05 – 1:25** | Integrar con el chat (bloque 3) y ejecutar `make test` |
| **1:25 – 1:30** | Commit/PR de cierre, captura del resultado y checkpoint Git |
| **1:30 – 2:00** | Revisión del avance, captura de `make test` y `make main` y cierre de la entrega de clase |

Al terminar la clase deben estar resueltos, como mínimo, los **12 primeros puntos**. El resto (casos borde, persistencia y Git colaborativo) queda como **entrega de casa** desde las 2:00 p.m. hasta las **11:59 p.m. del mismo día**.

> **Puntos extra:** los grupos que entreguen el **resultado completo durante el tiempo de clase** recibirán puntos extra **a criterio del preparador**.

---

## 9. Git/GitHub obligatorio

Cada grupo debe entregar un repositorio con:

1. `README.md` con integrantes, modelo asignado, instrucciones de compilación, uso de IA y reparto de roles.
2. `.gitignore` que excluya `build/`, `*.o`, `*.exe`, binarios, archivos de prueba y temporales.
3. Una rama por integrante y commits con mensajes claros.
4. Al menos **2 Pull Requests** revisados por otro integrante y fusionados a `main`.
5. Un tag `v1.0-entrega` al final.
6. Enlace del repositorio en la entrega.

---

## 10. Rúbrica y entrega

La evaluación se distribuye así:

| Bloque | Puntos | Momento |
| :--- | ---: | :--- |
| A1. Estructura desde cero | 4.0 | En clase |
| A2. Operaciones núcleo | 3.0 | En clase |
| A3. Integración con mensajería | 3.0 | En clase |
| A4. Checkpoint Git | 1.0 | En clase |
| A5. Demo propia (`main.cpp`) | 1.0 | En clase |
| B1. Casos borde y robustez | 3.0 | En casa |
| B2. Persistencia CSV | 2.0 | En casa |
| B3. Git colaborativo y documentación | 3.0 | En casa |
| **Total** | **20.0** | |

La nota es **grupal** y luego se multiplica por el **factor individual** de la rúbrica, calculado con la participación real en Git y la observación durante la clase.

### 10.1. Qué se entrega y cómo

> [!IMPORTANT]
> **No se envían archivos `.cpp` adjuntos.** La entrega es un **mensaje por correo electrónico** a **`jdanieldp99@gmail.com`** con:
>
> 1. **Captura de pantalla** de `make test` y `make main` funcionando **durante la clase**, donde se vean el resultado (`CUMPLE` / `AÚN NO CUMPLE`), la terminal y la fecha/hora.
> 2. **Enlace del repositorio** de GitHub/GitLab (público o con acceso aceptado para el preparador).
> 3. **Nombres, cédulas y roles** de los integrantes.
> 4. **Modelo asignado:** C (cola FIFO con cancelación y prioridad).
> 5. **Resultado de `make test`:** `CUMPLE EL MINIMO` o `AÚN NO CUMPLE EL MINIMO`, indicando cuántas verificaciones se superaron.
> 6. **Herramientas de IA** utilizadas y para qué.

La captura de la clase es la evidencia del **checkpoint de 12 pts**. El repositorio es la evidencia del trabajo completo y de los **8 pts restantes**.

### 10.2. Formato del mensaje

**Asunto:**

```text
[PR2-B2026] Práctica 03 - Modelo C - <Apellido1, Apellido2, ...> - C.I. <V-XXXXXXXX>
```

**Cuerpo:**

```text
Profesor Jesús Díaz y equipo de preparaduría,

Entrego la Práctica Evaluada 03 correspondiente al Modelo C (cola FIFO con cancelación y prioridad).

Datos del grupo:
- Integrante 1: <Nombre y Apellido> - C.I. <V-XXXXXXXX> - Rol: <rol>
- Integrante 2: <Nombre y Apellido> - C.I. <V-XXXXXXXX> - Rol: <rol>
- Integrante 3: <Nombre y Apellido> - C.I. <V-XXXXXXXX> - Rol: <rol>
- Integrante 4 (si aplica): <Nombre y Apellido> - C.I. V-XXXXXXXX - Rol: <rol>

Enlace del repositorio:
<https://github.com/usuario/repositorio>

Evidencia:
- Captura de make test durante la clase: adjunta al correo.
- Resultado de make test: <CUMPLE EL MINIMO / AUN NO CUMPLE EL MINIMO> — <X>/<Y> verificaciones.
- Demo propia: `main.cpp` compila y se ejecuta con `make main`.
- Tag de entrega: v1.0-entrega.

Herramientas de IA utilizadas:
<ninguna / ChatGPT / Claude / Copilot / otra> — uso: <para qué>.

Quedo atento a cualquier observación.
```

### 10.3. Fechas y penalización

- **Fecha límite final:** **miércoles 11 de noviembre de 2026, 11:59 p.m.** (el mismo día de la práctica).
- **Retardo:** **−5 puntos** sobre la nota final.
- **Puntos extra:** quienes entreguen el **resultado completo durante el tiempo de clase** recibirán puntos extra **a criterio del preparador**.
- Si el repositorio no es accesible o el enlace está roto, la entrega se considera **no recibida** hasta que se corrija.
- El código debe estar **en el repositorio**, no en el correo. No se aceptan `.cpp`, `.zip`, `.exe` ni `.o` adjuntos.

---

## 11. Uso de inteligencia artificial

Se permite usar asistentes de IA como apoyo (ChatGPT, Claude, Copilot, etc.), pero:

- Deben declararlo en el `README.md` indicando **qué herramienta** usaron y **para qué**.
- Son responsables de todo el código entregado: deben poder explicar cada clase, cada método y cada decisión, especialmente el manejo del frente/final, la cancelación en medio de la cola y el cambio de prioridad.
- Si un integrante no participó en el repositorio ni durante la clase, se aplica el factor individual de la rúbrica.
- No se permite entregar código generado sin comprenderlo ni adaptarlo al modelo asignado.

---

## 12. Checklist rápido

- [ ] La cola funciona vacía, con un mensaje y con varios.
- [ ] `encolar` y `desencolar` respetan FIFO.
- [ ] `frente` retorna el primer mensaje o `nullptr`.
- [ ] `aVector` retorna de frente a final.
- [ ] `buscarPorId`, `cancelar`, `moverAlFrente`, `moverAlFinal` e `invertir` funcionan sin romper la cola.
- [ ] La copia es profunda y el movimiento deja el origen vacío.
- [ ] `ChatCola` valida participante, duplicados y estado.
- [ ] `procesarSiguiente` y `procesarTodos` respetan el orden de llegada.
- [ ] `cancelarEnvio` quita un pendiente, `subirPrioridad` lo mueve al frente y `bajarPrioridad` al final.
- [ ] No se puede cancelar ni cambiar la prioridad de un mensaje ya enviado.
- [ ] No se puede encolar un mensaje ya enviado.
- [ ] El CSV conserva el orden FIFO y el contenido.
- [ ] No hay `std::queue`; la memoria se libera correctamente.
- [ ] El repositorio tiene ramas, PRs, README, `.gitignore` y tag.

---

*Modelo C de la Práctica Evaluada 03 — PR2 Sección 02, ULA.*
