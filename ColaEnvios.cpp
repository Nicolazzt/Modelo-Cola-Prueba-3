#include "ColaEnvios.hpp"

#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO C (COLA ENLAZADA)
// Integrantes:
//   1. Reyner Quintero - C.I. V-32591935 - Rol:
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
// ====================================================================

ColaEnvios::Nodo::Nodo(const TextMessage& mensaje)
    : dato(mensaje), siguiente(nullptr)
{
}

ColaEnvios::ColaEnvios()
    : frente_(nullptr), final_(nullptr), cantidad(0)
{
}

bool ColaEnvios::vacia() const
{
    return frente_ == nullptr;
}

std::size_t ColaEnvios::tamanio() const
{
    return cantidad;
}

bool ColaEnvios::encolar(const TextMessage& mensaje)
{
    if (buscarPorId(mensaje.getId()) != nullptr)
    {
        return false;
    }

    auto nuevo = std::make_shared<Nodo>(mensaje);
    if (vacia())
    {
        frente_ = nuevo;
        final_ = nuevo;
    }
    else
    {
        final_->siguiente = nuevo;
        final_ = nuevo;
    }
    cantidad++;
    return true;
}

bool ColaEnvios::desencolar()
{
    if (vacia())
    {
        return false;
    }

    frente_ = frente_->siguiente;
    cantidad--;

    if (frente_ == nullptr)
    {
        final_ = nullptr;
    }
    return true;
}

const TextMessage* ColaEnvios::frente() const
{
    if (vacia())
    {
        return nullptr;
    }
    return &(frente_->dato);
}

TextMessage* ColaEnvios::frente()
{
    if (vacia())
    {
        return nullptr;
    }
    return &(frente_->dato);
}

void ColaEnvios::limpiar()
{
    frente_ = nullptr;
    final_ = nullptr;
    cantidad = 0;
}

std::vector<TextMessage> ColaEnvios::aVector() const
{
    std::vector<TextMessage> vec;
    auto actual = frente_;
    while (actual != nullptr)
    {
        vec.push_back(actual->dato);
        actual = actual->siguiente;
    }
    return vec;
}

const TextMessage* ColaEnvios::buscarPorId(int id) const
{
    auto actual = frente_;
    while (actual != nullptr)
    {
        if (actual->dato.getId() == id)
        {
            return &(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

TextMessage* ColaEnvios::buscarPorId(int id)
{
    auto actual = frente_;
    while (actual != nullptr)
    {
        if (actual->dato.getId() == id)
        {
            return &(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ColaEnvios::cancelar(int id)
{
    if (vacia())
    {
        return false;
    }

    if (frente_->dato.getId() == id)
    {
        return desencolar();
    }

    auto actual = frente_;
    while (actual->siguiente != nullptr)
    {
        if (actual->siguiente->dato.getId() == id)
        {
            auto aBorrar = actual->siguiente;
            actual->siguiente = aBorrar->siguiente;

            if (aBorrar == final_)
            {
                final_ = actual;
            }

            cantidad--;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool ColaEnvios::moverAlFrente(int id)
{
    if (vacia())
    {
        return false;
    }

    if (frente_->dato.getId() == id)
    {
        return true;
    }

    auto actual = frente_;
    while (actual->siguiente != nullptr)
    {
        if (actual->siguiente->dato.getId() == id)
        {
            auto nodo = actual->siguiente;
            actual->siguiente = nodo->siguiente;

            if (nodo == final_)
            {
                final_ = actual;
            }

            nodo->siguiente = frente_;
            frente_ = nodo;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool ColaEnvios::moverAlFinal(int id)
{
    if (vacia())
    {
        return false;
    }

    if (final_->dato.getId() == id)
    {
        return true;
    }

    if (frente_->dato.getId() == id)
    {
        auto nodo = frente_;
        frente_ = frente_->siguiente;

        nodo->siguiente = nullptr;
        final_->siguiente = nodo;
        final_ = nodo;
        return true;
    }

    auto actual = frente_;
    while (actual->siguiente != nullptr)
    {
        if (actual->siguiente->dato.getId() == id)
        {
            auto nodo = actual->siguiente;
            actual->siguiente = nodo->siguiente;

            nodo->siguiente = nullptr;
            final_->siguiente = nodo;
            final_ = nodo;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void ColaEnvios::invertir()
{
    if (vacia() || cantidad == 1)
    {
        return;
    }

    std::shared_ptr<Nodo> anterior = nullptr;
    std::shared_ptr<Nodo> actual = frente_;
    final_ = frente_;

    while (actual != nullptr)
    {
        auto siguienteNodo = actual->siguiente;
        actual->siguiente = anterior;
        anterior = actual;
        actual = siguienteNodo;
    }
    frente_ = anterior;
}

bool ColaEnvios::guardarCSV(const std::string& ruta) const
{
    (void)ruta;
    return false;
}

bool ColaEnvios::cargarCSV(const std::string& ruta)
{
    (void)ruta;
    return false;
}
