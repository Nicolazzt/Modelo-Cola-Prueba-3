#include "ColaEnvios.hpp"

#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO C (COLA ENLAZADA)
// Integrantes:
//   1. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
// ====================================================================
// Completen la implementacion de esta estructura.
// ====================================================================

ColaEnvios::Nodo::Nodo(const TextMessage& mensaje)
    : dato(mensaje), siguiente(nullptr)
{
}

ColaEnvios::ColaEnvios()
    : frente_(nullptr), final_(nullptr), cantidad(0)
{
}

ColaEnvios::ColaEnvios(const ColaEnvios& otra)
    : frente_(nullptr), final_(nullptr), cantidad(0)
{
    // TODO: completar.
    (void)otra;
}

ColaEnvios& ColaEnvios::operator=(const ColaEnvios& otra)
{
    // TODO: completar.
    (void)otra;
    return *this;
}

ColaEnvios::ColaEnvios(ColaEnvios&& otra) noexcept
    : frente_(nullptr), final_(nullptr), cantidad(0)
{
    // TODO: completar.
    (void)otra;
}

ColaEnvios& ColaEnvios::operator=(ColaEnvios&& otra) noexcept
{
    // TODO: completar.
    (void)otra;
    return *this;
}

bool ColaEnvios::vacia() const
{
    // TODO: completar.
    return false;
}

std::size_t ColaEnvios::tamanio() const
{
    // TODO: completar.
    return 0;
}

bool ColaEnvios::encolar(const TextMessage& mensaje)
{
    // TODO: completar.
    (void)mensaje;
    return false;
}

bool ColaEnvios::desencolar()
{
    // TODO: completar.
    return false;
}

const TextMessage* ColaEnvios::frente() const
{
    // TODO: completar.
    return nullptr;
}

TextMessage* ColaEnvios::frente()
{
    // TODO: completar.
    return nullptr;
}

void ColaEnvios::limpiar()
{
    // TODO: completar.
}

std::vector<TextMessage> ColaEnvios::aVector() const
{
    // TODO: completar.
    return {};
}

const TextMessage* ColaEnvios::buscarPorId(int id) const
{
    // TODO: completar.
    (void)id;
    return nullptr;
}

TextMessage* ColaEnvios::buscarPorId(int id)
{
    // TODO: completar.
    (void)id;
    return nullptr;
}

bool ColaEnvios::cancelar(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

bool ColaEnvios::moverAlFrente(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

bool ColaEnvios::moverAlFinal(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

void ColaEnvios::invertir()
{
    // TODO: completar.
}

bool ColaEnvios::guardarCSV(const std::string& ruta) const
{
    // TODO: completar.
    (void)ruta;
    return false;
}

bool ColaEnvios::cargarCSV(const std::string& ruta)
{
    // TODO: completar.
    (void)ruta;
    return false;
}
