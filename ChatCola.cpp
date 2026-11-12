#include "ChatCola.hpp"

#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO C (COLA ENLAZADA)
// Integrantes:
//   1. Santiago Zerpa - C.I. V-32451779 - Rol: integracion de chatcola
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
// ====================================================================
// Completen la integracion de la cola con el chat.
// ====================================================================

ChatCola::ChatCola(int id, std::string nombre, std::vector<std::string> participantes)
    : Chat(id, std::move(nombre), std::move(participantes))
{
}

bool ChatCola::encolarMensaje(TextMessage mensaje)
{
    // el remitente debe participar en el chat
    if (!isParticipant(mensaje.getSenderId())) return false;
    // solo se encolan mensajes Pending
    if (mensaje.getStatus() != MessageStatus::Pending) return false;
    // el id no puede estar ni pendiente ni enviado
    if (pendientes.buscarPorId(mensaje.getId()) != nullptr) return false;
    if (buscarEnviado(mensaje.getId()) != nullptr) return false;
    return pendientes.encolar(mensaje);
}

bool ChatCola::procesarSiguiente()
{
    TextMessage* frente = pendientes.frente();
    if (frente == nullptr) return false;

    // copio el mensaje, lo marco Sent y lo guardo en enviados
    TextMessage copia = *frente;
    copia.markSent(getId());
    enviados.push_back(copia);

    pendientes.desencolar();
    return true;
}

std::size_t ChatCola::procesarTodos()
{
    std::size_t procesados = 0;
    while (procesarSiguiente()) {
        procesados++;
    }
    return procesados;
}

bool ChatCola::cancelarEnvio(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

bool ChatCola::subirPrioridad(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

bool ChatCola::bajarPrioridad(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

const TextMessage* ChatCola::siguientePendiente() const
{
    return pendientes.frente();
}

std::size_t ChatCola::cantidadPendientes() const
{
    // TODO: completar.
    return 0;
}

std::size_t ChatCola::cantidadEnviados() const
{
    // TODO: completar.
    return 0;
}

const std::vector<TextMessage>& ChatCola::getEnviados() const
{
    return enviados;
}

const ColaEnvios& ChatCola::getPendientes() const
{
    return pendientes;
}

const TextMessage* ChatCola::buscarEnviado(int id) const
{
    // TODO: completar.
    (void)id;
    return nullptr;
}
