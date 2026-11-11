// ====================================================================
// PRACTICA 03 - MODELO C (COLA ENLAZADA)
// Verificador de requisitos minimos.
// NO asigna nota: solo indica si el esqueleto ya cumple lo minimo.
// La calificacion la realiza el preparador con la rubrica.
// ====================================================================

#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "ChatCola.hpp"
#include "ColaEnvios.hpp"
#include "TextMessage.hpp"

using namespace std;

static int total[6] = {0, 0, 0, 0, 0, 0};
static int superadas[6] = {0, 0, 0, 0, 0, 0};

static void test(int bloque, const string& nombre, bool ok)
{
    ++total[bloque];
    if (ok)
    {
        ++superadas[bloque];
    }

    cout << "  [" << (ok ? "OK" : "FALLA") << "] " << nombre << endl;
}

int main()
{
    cout << "====================================================================" << endl;
    cout << "         PRACTICA 03 - MODELO C: COLA ENLAZADA (C++)                " << endl;
    cout << "====================================================================\n" << endl;

    // ------------------------------------------------------------------
    // BLOQUE 1: ESTRUCTURA DESDE CERO
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 1: Estructura desde cero ---" << endl;

    ColaEnvios vacia;
    const bool b1_1 = vacia.vacia() && vacia.tamanio() == 0 && vacia.frente() == nullptr;
    test(1, "1.1 Cola recien creada: vacia, tamanio 0, frente nullptr", b1_1);

    ColaEnvios cola;
    TextMessage m1(1, "u1", "uno");
    TextMessage m2(2, "u1", "dos");
    TextMessage m3(3, "u2", "tres");
    const bool e1 = cola.encolar(m1);
    const bool e2 = cola.encolar(m2);
    const bool e3 = cola.encolar(m3);
    const bool b1_2 = e1 && e2 && e3 && cola.tamanio() == 3 && !cola.vacia() &&
                      cola.frente() != nullptr && cola.frente()->getId() == 1 &&
                      cola.aVector().size() == 3 &&
                      cola.aVector()[0].getId() == 1 &&
                      cola.aVector()[1].getId() == 2 &&
                      cola.aVector()[2].getId() == 3;
    test(1, "1.2 encolar() respeta FIFO y actualiza tamanio/frente", b1_2);

    const bool desencolo = cola.desencolar();
    const bool b1_3 = desencolo && cola.tamanio() == 2 &&
                      cola.frente() != nullptr && cola.frente()->getId() == 2;
    test(1, "1.3 desencolar() retira el frente y actualiza tamanio", b1_3);

    ColaEnvios colaUna;
    colaUna.encolar(m1);
    const bool sacaUna = colaUna.desencolar();
    const bool sacaVacia = colaUna.desencolar();
    const bool b1_4 = sacaUna && !sacaVacia && colaUna.vacia();
    test(1, "1.4 desencolar() retorna false cuando la cola ya esta vacia", b1_4);

    ColaEnvios colaVector;
    colaVector.encolar(m1);
    colaVector.encolar(m2);
    colaVector.encolar(m3);
    const vector<TextMessage> mensajes = colaVector.aVector();
    const bool b1_5 = mensajes.size() == 3 &&
                      mensajes[0].getId() == 1 &&
                      mensajes[1].getId() == 2 &&
                      mensajes[2].getId() == 3;
    test(1, "1.5 aVector() retorna los mensajes de frente a final", b1_5);

    cout << endl;

    // ------------------------------------------------------------------
    // BLOQUE 2: OPERACIONES NUCLEO
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 2: Operaciones nucleo ---" << endl;

    const bool frenteVacia = vacia.frente() == nullptr;
    const bool frenteCola = cola.frente() != nullptr && cola.frente()->getId() == 2;
    test(2, "2.1 frente() retorna el primer mensaje o nullptr", frenteVacia && frenteCola);

    ColaEnvios colaLimpiar;
    colaLimpiar.encolar(m1);
    colaLimpiar.encolar(m2);
    const bool teniaDos = colaLimpiar.tamanio() == 2;
    colaLimpiar.limpiar();
    const bool b2_2 = teniaDos && colaLimpiar.vacia() && colaLimpiar.tamanio() == 0 &&
                      colaLimpiar.frente() == nullptr;
    test(2, "2.2 limpiar() deja la cola vacia", b2_2);

    ColaEnvios original;
    original.encolar(m1);
    original.encolar(m2);
    ColaEnvios copia = original;
    const bool copiaOk = copia.tamanio() == 2 && copia.frente() != nullptr &&
                         copia.frente()->getId() == 1;
    copia.encolar(m3);
    const bool independiente = original.tamanio() == 2 && copia.tamanio() == 3;
    test(2, "2.3 Copia profunda: modificar la copia no afecta a la original", copiaOk && independiente);

    ColaEnvios movible;
    movible.encolar(m1);
    movible.encolar(m2);
    ColaEnvios movida = std::move(movible);
    const bool b2_4 = movida.tamanio() == 2 && movida.frente() != nullptr &&
                      movida.frente()->getId() == 1 && movible.vacia();
    test(2, "2.4 Movimiento seguro de la cola (regla de cinco)", b2_4);

    ColaEnvios colaBuscar;
    colaBuscar.encolar(m1);
    colaBuscar.encolar(m2);
    colaBuscar.encolar(m3);
    const TextMessage* encontrado = colaBuscar.buscarPorId(2);
    const bool b2_5 = encontrado != nullptr && encontrado->getId() == 2 &&
                      colaBuscar.buscarPorId(99) == nullptr && colaBuscar.tamanio() == 3;
    test(2, "2.5 buscarPorId() recorre la cola y retorna nullptr si no existe", b2_5);

    ColaEnvios colaCancelar;
    colaCancelar.encolar(m1);
    colaCancelar.encolar(m2);
    colaCancelar.encolar(m3);
    const bool cancelaMedio = colaCancelar.cancelar(2);
    const vector<TextMessage> trasCancelar = colaCancelar.aVector();
    const bool medioOk = cancelaMedio && colaCancelar.tamanio() == 2 &&
                         trasCancelar.size() == 2 &&
                         trasCancelar[0].getId() == 1 && trasCancelar[1].getId() == 3;
    const bool cancelaFrente = colaCancelar.cancelar(1);
    const bool frenteOk = cancelaFrente && colaCancelar.tamanio() == 1 &&
                          colaCancelar.frente() != nullptr &&
                          colaCancelar.frente()->getId() == 3;
    const bool cancelaFinal = colaCancelar.cancelar(3);
    const bool finalOk = cancelaFinal && colaCancelar.vacia() &&
                         colaCancelar.frente() == nullptr;
    const bool b2_6 = medioOk && frenteOk && finalOk && !colaCancelar.cancelar(99);
    test(2, "2.6 cancelar() funciona en frente, medio y final, y actualiza el estado", b2_6);

    ColaEnvios colaPrioridad;
    colaPrioridad.encolar(m1);
    colaPrioridad.encolar(m2);
    colaPrioridad.encolar(m3);
    const bool movioFrente = colaPrioridad.moverAlFrente(2);
    const vector<TextMessage> trasMover = colaPrioridad.aVector();
    const bool prioridadOk = movioFrente && colaPrioridad.tamanio() == 3 &&
                             trasMover.size() == 3 &&
                             trasMover[0].getId() == 2 && trasMover[1].getId() == 1 &&
                             trasMover[2].getId() == 3 &&
                             colaPrioridad.frente() != nullptr &&
                             colaPrioridad.frente()->getId() == 2;
    const bool movioFrenteFinal = colaPrioridad.moverAlFrente(3);
    const vector<TextMessage> trasMoverFrente = colaPrioridad.aVector();
    const bool frenteFinalOk = movioFrenteFinal && trasMoverFrente.size() == 3 &&
                               trasMoverFrente[0].getId() == 3 &&
                               trasMoverFrente[1].getId() == 2 &&
                               trasMoverFrente[2].getId() == 1;
    const bool b2_7 = prioridadOk && frenteFinalOk && !colaPrioridad.moverAlFrente(99);
    test(2, "2.7 moverAlFrente() sube un mensaje al frente y retorna false si no existe", b2_7);

    ColaEnvios colaBajar;
    colaBajar.encolar(m1);
    colaBajar.encolar(m2);
    colaBajar.encolar(m3);
    const bool movioFinalMedio = colaBajar.moverAlFinal(2);
    const vector<TextMessage> trasBajarMedio = colaBajar.aVector();
    const bool medioAlFinalOk = movioFinalMedio && colaBajar.tamanio() == 3 &&
                                trasBajarMedio.size() == 3 &&
                                trasBajarMedio[0].getId() == 1 &&
                                trasBajarMedio[1].getId() == 3 &&
                                trasBajarMedio[2].getId() == 2 &&
                                colaBajar.frente() != nullptr &&
                                colaBajar.frente()->getId() == 1;
    const bool movioFinalFrente = colaBajar.moverAlFinal(1);
    const vector<TextMessage> trasBajarFrente = colaBajar.aVector();
    const bool frenteAlFinalOk = movioFinalFrente && trasBajarFrente.size() == 3 &&
                                 trasBajarFrente[0].getId() == 3 &&
                                 trasBajarFrente[1].getId() == 2 &&
                                 trasBajarFrente[2].getId() == 1;
    ColaEnvios colaUnaSola;
    colaUnaSola.encolar(m1);
    const bool unaSolaOk = colaUnaSola.moverAlFinal(1) && colaUnaSola.tamanio() == 1 &&
                           colaUnaSola.frente() != nullptr &&
                           colaUnaSola.frente()->getId() == 1;
    const bool b2_8 = medioAlFinalOk && frenteAlFinalOk && unaSolaOk &&
                      colaBajar.moverAlFinal(1) && !colaBajar.moverAlFinal(99) &&
                      !vacia.moverAlFinal(1);
    test(2, "2.8 moverAlFinal() baja un mensaje al final y respeta los casos borde", b2_8);

    ColaEnvios colaInvertir;
    colaInvertir.encolar(m1);
    colaInvertir.encolar(m2);
    colaInvertir.encolar(m3);
    colaInvertir.invertir();
    const vector<TextMessage> trasInvertir = colaInvertir.aVector();
    const bool invirtio = colaInvertir.tamanio() == 3 && trasInvertir.size() == 3 &&
                          trasInvertir[0].getId() == 3 && trasInvertir[1].getId() == 2 &&
                          trasInvertir[2].getId() == 1 &&
                          colaInvertir.frente() != nullptr &&
                          colaInvertir.frente()->getId() == 3;
    const bool desencoloInvertida = colaInvertir.desencolar();
    const bool b2_9 = invirtio && desencoloInvertida && colaInvertir.tamanio() == 2 &&
                      colaInvertir.frente() != nullptr &&
                      colaInvertir.frente()->getId() == 2;
    test(2, "2.9 invertir() deja el final en el frente y conserva el tamanio", b2_9);

    cout << endl;

    // ------------------------------------------------------------------
    // BLOQUE 3: INTEGRACION CON MENSAJERIA
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 3: Integracion con mensajeria ---" << endl;

    ChatCola chat(1, "Equipo PR2", {"u1", "u2"});
    TextMessage c1(1, "u1", "hola");
    TextMessage c2(2, "u2", "segundo");
    const bool encolo = chat.encolarMensaje(c1);
    const TextMessage* pendiente = chat.siguientePendiente();
    const bool b3_1 = encolo && chat.cantidadPendientes() == 1 && pendiente != nullptr &&
                      pendiente->getId() == 1 && pendiente->getStatus() == MessageStatus::Pending;
    test(3, "3.1 encolarMensaje() deja el mensaje Pending en la cola", b3_1);

    chat.encolarMensaje(c2);
    const bool proceso = chat.procesarSiguiente();
    const TextMessage* enviado = chat.buscarEnviado(1);
    const bool b3_2 = proceso && chat.cantidadPendientes() == 1 &&
                      chat.cantidadEnviados() == 1 && enviado != nullptr &&
                      enviado->getStatus() == MessageStatus::Sent &&
                      chat.siguientePendiente() != nullptr &&
                      chat.siguientePendiente()->getId() == 2;
    test(3, "3.2 procesarSiguiente() envia el frente en orden FIFO", b3_2);

    TextMessage intruso(3, "u3", "no participo");
    const bool rechazoIntruso = chat.encolarMensaje(intruso);
    TextMessage duplicado(2, "u2", "duplicado");
    const bool rechazoDuplicado = chat.encolarMensaje(duplicado);
    const bool b3_3 = !rechazoIntruso && !rechazoDuplicado &&
                      chat.cantidadPendientes() == 1;
    test(3, "3.3 Se rechaza un remitente ajeno y un id duplicado", b3_3);

    ChatCola chatCancelar(5, "Cancelar", {"u1", "u2"});
    chatCancelar.encolarMensaje(TextMessage(1, "u1", "uno"));
    chatCancelar.encolarMensaje(TextMessage(2, "u2", "dos"));
    const bool cancelo = chatCancelar.cancelarEnvio(1);
    const bool b3_4 = cancelo && chatCancelar.cantidadPendientes() == 1 &&
                      chatCancelar.siguientePendiente() != nullptr &&
                      chatCancelar.siguientePendiente()->getId() == 2 &&
                      !chatCancelar.cancelarEnvio(99);
    test(3, "3.4 cancelarEnvio() quita un pendiente sin procesarlo", b3_4);

    ChatCola chatPriorizar(6, "Priorizar", {"u1", "u2"});
    chatPriorizar.encolarMensaje(TextMessage(1, "u1", "uno"));
    chatPriorizar.encolarMensaje(TextMessage(2, "u1", "dos"));
    chatPriorizar.encolarMensaje(TextMessage(3, "u2", "tres"));
    const bool subio = chatPriorizar.subirPrioridad(3);
    const bool b3_5 = subio && chatPriorizar.siguientePendiente() != nullptr &&
                      chatPriorizar.siguientePendiente()->getId() == 3 &&
                      chatPriorizar.procesarSiguiente() &&
                      chatPriorizar.buscarEnviado(3) != nullptr &&
                      chatPriorizar.siguientePendiente() != nullptr &&
                      chatPriorizar.siguientePendiente()->getId() == 1 &&
                      !chatPriorizar.subirPrioridad(99);
    test(3, "3.5 subirPrioridad() coloca el mensaje al frente y se procesa primero", b3_5);

    ChatCola chatBajar(9, "BajarPrioridad", {"u1", "u2"});
    chatBajar.encolarMensaje(TextMessage(1, "u1", "uno"));
    chatBajar.encolarMensaje(TextMessage(2, "u2", "dos"));
    chatBajar.encolarMensaje(TextMessage(3, "u2", "tres"));
    const bool bajo = chatBajar.bajarPrioridad(1);
    const vector<TextMessage> trasBajar = chatBajar.getPendientes().aVector();
    const bool bajoOk = bajo && trasBajar.size() == 3 &&
                        trasBajar[0].getId() == 2 && trasBajar[1].getId() == 3 &&
                        trasBajar[2].getId() == 1 &&
                        chatBajar.siguientePendiente() != nullptr &&
                        chatBajar.siguientePendiente()->getId() == 2;
    const bool procesoBajar = chatBajar.procesarSiguiente();
    const bool procesoBajarOk = procesoBajar && chatBajar.buscarEnviado(2) != nullptr &&
                                chatBajar.siguientePendiente() != nullptr &&
                                chatBajar.siguientePendiente()->getId() == 3;
    const bool bajoUltimo = chatBajar.bajarPrioridad(3);
    const bool b3_6 = bajoOk && procesoBajarOk && bajoUltimo &&
                      chatBajar.siguientePendiente() != nullptr &&
                      chatBajar.siguientePendiente()->getId() == 1 &&
                      !chatBajar.bajarPrioridad(99);
    test(3, "3.6 bajarPrioridad() manda un pendiente al final y se procesa ultimo", b3_6);

    cout << endl;

    // ------------------------------------------------------------------
    // BLOQUE 4: CASOS BORDE
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 4: Casos borde y robustez ---" << endl;

    ChatCola chatVacio(2, "Vacio", {"u1", "u2"});
    const bool b4_1 = !chatVacio.procesarSiguiente() && chatVacio.cantidadPendientes() == 0 &&
                      chatVacio.cantidadEnviados() == 0;
    test(4, "4.1 procesarSiguiente() retorna false si no hay pendientes", b4_1);

    ChatCola chatFifo(3, "Fifo", {"u1", "u2"});
    chatFifo.encolarMensaje(TextMessage(1, "u1", "a"));
    chatFifo.encolarMensaje(TextMessage(2, "u1", "b"));
    chatFifo.encolarMensaje(TextMessage(3, "u2", "c"));
    const bool p1 = chatFifo.procesarSiguiente();
    const bool p2 = chatFifo.procesarSiguiente();
    const bool p3 = chatFifo.procesarSiguiente();
    const vector<TextMessage>& enviados = chatFifo.getEnviados();
    const bool b4_2 = p1 && p2 && p3 && enviados.size() == 3 &&
                      enviados[0].getId() == 1 &&
                      enviados[1].getId() == 2 &&
                      enviados[2].getId() == 3;
    test(4, "4.2 Varios mensajes se procesan exactamente en orden FIFO", b4_2);

    ChatCola chatTodos(4, "Todos", {"u1", "u2"});
    chatTodos.encolarMensaje(TextMessage(1, "u1", "a"));
    chatTodos.encolarMensaje(TextMessage(2, "u1", "b"));
    chatTodos.encolarMensaje(TextMessage(3, "u2", "c"));
    const size_t procesados = chatTodos.procesarTodos();
    const size_t otraVez = chatTodos.procesarTodos();
    const bool b4_3 = procesados == 3 && otraVez == 0 &&
                      chatTodos.cantidadPendientes() == 0 &&
                      chatTodos.cantidadEnviados() == 3;
    test(4, "4.3 procesarTodos() procesa la cola completa y retorna el conteo", b4_3);

    ChatCola chatCancelarVacio(7, "CancelarVacio", {"u1", "u2"});
    const bool b4_4 = !chatCancelarVacio.cancelarEnvio(1) &&
                      !chatCancelarVacio.subirPrioridad(1) &&
                      !chatCancelarVacio.bajarPrioridad(1) &&
                      chatCancelarVacio.cantidadPendientes() == 0;
    test(4, "4.4 cancelarEnvio(), subirPrioridad() y bajarPrioridad() fallan con la cola vacia", b4_4);

    cout << endl;

    // ------------------------------------------------------------------
    // BLOQUE 5: PERSISTENCIA
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 5: Persistencia CSV ---" << endl;

    const string ruta = "test_cola.csv";
    ColaEnvios persistente;
    persistente.encolar(m1);
    persistente.encolar(m2);
    persistente.encolar(m3);
    const bool guardo = persistente.guardarCSV(ruta);
    ColaEnvios cargada;
    const bool cargo = cargada.cargarCSV(ruta);
    const vector<TextMessage> recuperados = cargada.aVector();
    ColaEnvios inexistente;
    const bool noCarga = inexistente.cargarCSV("archivo_inexistente_12345.csv");
    const bool b5 = guardo && cargo && recuperados.size() == 3 &&
                    recuperados[0].getId() == 1 &&
                    recuperados[1].getId() == 2 &&
                    recuperados[2].getId() == 3 &&
                    recuperados[0].getContent() == "uno" &&
                    !noCarga && inexistente.vacia();
    std::remove(ruta.c_str());
    test(5, "5.1 Guardar y cargar conserva el orden FIFO y el contenido", b5);

    // ------------------------------------------------------------------
    // VERIFICACION MINIMA
    // ------------------------------------------------------------------
    int totalOk = 0;
    int totalChecks = 0;
    for (int b = 1; b <= 5; ++b)
    {
        totalOk += superadas[b];
        totalChecks += total[b];
    }

    cout << "\n====================================================================" << endl;
    cout << "            VERIFICACION DE REQUISITOS MINIMOS                     " << endl;
    cout << "====================================================================" << endl;
    for (int b = 1; b <= 5; ++b)
    {
        cout << "  Bloque " << b << ": " << superadas[b] << " / " << total[b]
             << " verificaciones" << endl;
    }
    cout << "  TOTAL: " << totalOk << " / " << totalChecks
         << " verificaciones superadas" << endl;
    cout << "  RESULTADO: ";
    if (totalOk == totalChecks)
    {
        cout << "CUMPLE EL MINIMO" << endl;
    }
    else
    {
        cout << "AUN NO CUMPLE EL MINIMO" << endl;
    }
    cout << "\n  Esta suite NO asigna nota." << endl;
    cout << "  La calificacion la asigna el preparador con la rubrica:" << endl;
    cout << "  resultado grupal + aporte individual evidenciado en Git." << endl;
    cout << "====================================================================" << endl;

    return 0;
}
