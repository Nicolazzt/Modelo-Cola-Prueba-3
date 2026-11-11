#include "ChatCola.hpp"

#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO C (COLA ENLAZADA)
// Integrantes:
//   1. Nombre y Apellido - Jose Peñaloza C.I. V- 32597715 - Rol: modelo c cola
//   2. Nombre y Apellido - Reyner Quintero C.I. V- 32591935 - Rol: modelo c cola
//   3. Nombre y Apellido - Santiago Ruiz C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - Santiago Zerpa C.I. V-XXXXXXXX - Rol:
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
    return pendientes tamanio;
}

std::size_t ChatCola::cantidadEnviados() const
{
    // TODO: completar.
    return enviados.size();
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
    for(const auto&message :enviados){

        if(message.getId() == id){

            return&message;
        }
    }
    return nullptr;
}
