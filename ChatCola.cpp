#include "ChatCola.hpp"

#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO C (COLA ENLAZADA)
// Integrantes:
//   1. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
// ====================================================================
// Completen la integracion de la cola con el chat.
// ====================================================================

ChatCola::ChatCola(int id, std::string nombre, std::vector<std::string> participantes)
    : Chat(id, std::move(nombre), std::move(participantes))
{
}

bool ChatCola::encolarMensaje(TextMessage mensaje)
{
    // TODO: completar.
    (void)mensaje;
    return false;
}

bool ChatCola::procesarSiguiente()
{
    // TODO: completar.
    return false;
}

std::size_t ChatCola::procesarTodos()
{
    // TODO: completar.
    return 0;
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
