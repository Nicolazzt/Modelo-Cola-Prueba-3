#pragma once

#include <string>
#include <vector>

#include "Chat.hpp"
#include "ColaEnvios.hpp"

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO C (COLA ENLAZADA)
// Integrantes:
//   1. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
// ====================================================================

class ChatCola : public Chat
{
private:
    ColaEnvios pendientes;
    std::vector<TextMessage> enviados;

public:
    ChatCola(int id, std::string nombre, std::vector<std::string> participantes);

    bool encolarMensaje(TextMessage mensaje);
    bool procesarSiguiente();
    std::size_t procesarTodos();

    bool cancelarEnvio(int id);
    bool subirPrioridad(int id);
    bool bajarPrioridad(int id);

    const TextMessage* siguientePendiente() const;
    std::size_t cantidadPendientes() const;
    std::size_t cantidadEnviados() const;
    const std::vector<TextMessage>& getEnviados() const;
    const ColaEnvios& getPendientes() const;
    const TextMessage* buscarEnviado(int id) const;
};
