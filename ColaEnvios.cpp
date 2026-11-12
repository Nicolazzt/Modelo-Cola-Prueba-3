#include "ColaEnvios.hpp"
#include <fstream>

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
    if(cantidad == 0)
    {
        return true;
    }else
    {
        return false;
    }
}

std::size_t ColaEnvios::tamanio() const
{
    return cantidad;
}

bool ColaEnvios::encolar(const TextMessage& mensaje)
{
    std::shared_ptr<Nodo> actual = frente_;



    while(actual != nullptr) 
    {
        if(actual->dato.getId() == mensaje.getId()) 
        {
            return false;
        }

        actual = actual->siguiente;
    }


    
    std::shared_ptr<Nodo> nuevo = std::make_shared<Nodo>(mensaje);
    if (final_ == nullptr)
    {
        final_ = nuevo;
        frente_ = nuevo;

    }else
    {
        final_->siguiente = nuevo;
        final_ = nuevo;

    }

    cantidad++;

    return true;

}

bool ColaEnvios::desencolar()
{
    if(final_ == nullptr)
    {
        return false;
    }

    frente_ = frente_->siguiente;

    //En caso de que haya existido solo 1 elemento en la cola y lo hayamos eliminado final tambien debe pasar a apuntar a nullptr
    if(frente_ == nullptr)
    {
        final_ = nullptr;
    }

    cantidad--;

    return true;
   
}

const TextMessage* ColaEnvios::frente() const

{
    if(vacia() == true)
    {
        return nullptr;
    }else
    {
        return &frente_->dato;
    }
}

TextMessage* ColaEnvios::frente()
{
     if(vacia() == true)
    {
        return nullptr;
    }else
    {
        return &frente_->dato;
    }
}

void ColaEnvios::limpiar()
{
    while(vacia()==false)
    {
        desencolar();
    }
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
    std::ofstream archivo(ruta);

    if(archivo.is_open() == false)
    {
        return false;
    }
    
    std::shared_ptr<Nodo> actual = frente_;

    while(actual != nullptr)
    {
        archivo << actual->dato.toCSV() << std::endl;
        
        actual = actual->siguiente;
    }

    archivo.close();

    return true;
}

bool ColaEnvios::cargarCSV(const std::string& ruta)
{
    std::ifstream archivo(ruta);

    if(archivo.is_open() == false)
    {
        return false;
    }

    limpiar();
    std::string linea;

    while(std::getline(archivo,linea))
    {
        if(linea.empty())
        {
            continue;
        }

        TextMessage Mensaje = TextMessage::fromCSV(linea);
        encolar(Mensaje);

    }

    archivo.close();

    return true;
    
    
}
