# include <iostream>
# include "Medico.h"
#include "Fecha.h"
# include "ManagerMedico.h"
# include "ArchivoMedico.h"
using namespace std;



void ManagerMedico::registrarNuevoMedico()
{

    Medico medico;
    ArchivoMedico aMedico("medicos.dat");

    int id, idEspecialidad=0, dia, mes, anio;
    string dni, nombre,  apellido, telefono,  email, matricula;
    bool bandera = false;

    while(bandera == false)
    {
        bandera = true;
        cout<<"Ingrese el numero de DNI: "<<endl;
        cin>>dni;
        if(!aMedico.checkDni(dni))
        {
            bandera = false;
        }
    }


    cout<<"Ingrese el Nombre del medico: "<<endl;
    cin.ignore();
    getline(cin,nombre);

    cout<<"Ingrese el Apellido del medico: "<<endl;
    getline(cin,apellido);

    cout<<"Ingrese el numero de telefono: "<<endl;
    getline(cin,telefono);

    cout<<"Ingrese el email: "<<endl;
    getline(cin,email);

    cout << "Ingrese la matrícula del médico: " << endl;
    getline(cin, matricula);

    cout<<"Ingrese dia del mes en que nacio: "<<endl;
    cin>>dia;

    cout<<"Ingrese mes en el que nacio: "<<endl;
    cin>>mes;

    cout<<"Ingrese año en el que nacio: "<<endl;
    cin>>anio;
    Fecha fechaNacimiento(dia,mes,anio);
    cout<<"ingrese dia del mes en que inicio actividad: "<<endl;
    cin>>dia;

    cout<<"Ingrese mes en el que inicio actividad: "<<endl;
    cin>>mes;

    cout<<"Ingrese año en el que inicio actividad: "<<endl;
    cin>>anio;
    Fecha fechaInicioActividad(dia, mes,anio);

    bool enabled = true;

    id = aMedico.generarNuevoId();

    medico= Medico( id, dni,  nombre,  apellido, telefono, email,  fechaNacimiento, idEspecialidad, fechaInicioActividad,  matricula,  enabled);

    if(aMedico.Guardar(medico))
    {
        cout << "Se guardo correctamente!" << endl;
    }
    else
    {
        cout << "Hubo un error inesperado, llame al de sistemas..." << endl;
    }

}
// ← Método que devuelve un objeto Medico
Medico ManagerMedico::buscarMedicoPorDni(const std::string& dni)
{
    ArchivoMedico aMedico("medicos.dat");//aca lo tengo que buscar
    int posicion=aMedico.BuscarPorDni(dni);//posicion en la que esta este medico en el archivo dat

    if (posicion==   -1)
    {
        cout << "No se encontro un medico con ese DNI"<< endl;
        return Medico();//retorno el objeto medico vacio en este caso
    }
    else
    {
        Medico medicoEncontrado= aMedico.Leer(posicion);
        return medicoEncontrado;
    }
}
void ManagerMedico::buscarYMostrarMedicoPorDni()
{
    string dni;
    cout << "Ingrese el DNI del médico a buscar: ";
    cin >> dni;

    Medico medicoEncontrado = buscarMedicoPorDni(dni);

    if (medicoEncontrado.get_id() != -1)
    {
        cout << medicoEncontrado.toCSV() << endl;
    }
    else
    {
        cout << "No se encontró un médico con ese DNI." << endl;
    }
}

bool ManagerMedico::modificarMedicoPorDni()
{
    std::string dni;
    cout << "Ingrese el DNI del médico que desea modificar: ";
    cin >> dni;
    cin.ignore();

    ArchivoMedico aMedico("medicos.dat");
    int posicion = aMedico.BuscarPorDni(dni);

    if (posicion == -1)
    {
        cout << "No se encontro un medico con ese DNI" << endl;
        return false;
    }
    Medico medicoEncontrado = aMedico.Leer(posicion);
    cout << "Datos actuales del medico:  " << endl;
    cout << medicoEncontrado.toCSV() << endl;

    int opcion;
    do
    {
        cout << "\n--- Menú de modificación ---" << endl;
        cout << "1. Modificar teléfono" << endl;
        cout << "2. Modificar email" << endl;
        cout << "3. Modificar apellido" << endl;
        cout << "4. Ver datos actuales" << endl;
        cout << "0. Guardar y salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            string nuevoTelefono;
            cout << "Ingrese el nuevo teléfono: ";
            getline(cin, nuevoTelefono);
            medicoEncontrado.set_telefono(nuevoTelefono);
            break;
        }
        case 2:
        {
            string nuevoEmail;
            cout << "Ingrese el nuevo email: ";
            getline(cin, nuevoEmail);
            medicoEncontrado.set_email(nuevoEmail);
            break;
        }
        case 3:
        {
            string nuevoApellido;
            cout << "Ingrese el nuevo apellido: ";
            getline(cin, nuevoApellido);
            medicoEncontrado.set_apellido(nuevoApellido);
            break;
        }
        case 4:
        {
            cout << "Datos actuales del médico:" << endl;
            cout << medicoEncontrado.toCSV() << endl;
            break;
        }
        case 0:
            cout << "Guardando cambios..." << endl;
            break;
        default:
            cout << "Opción inválida." << endl;
        }

    }
    while (opcion != 0);

    if (aMedico.Guardar(medicoEncontrado, posicion))
    {
        cout << "Datos actualizados correctamente." << endl;
        return true;
    }
    else
    {
        cout << "Error al guardar los cambios." << endl;
        return false;
    }
}

void ManagerMedico::listarMedicos()
{
    ArchivoMedico archivo("medicos.dat");
    int cantidad = archivo.CantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay médicos cargados." << endl;
        return;
    }

    Medico* lista = new Medico[cantidad];
    archivo.Leer(cantidad, lista);

    for (int i = 0; i < cantidad; i++)
    {
        if (lista[i].get_enabled())    // Mostrar solo los activos
        {
            cout << lista[i].toCSV() << endl;
        }
    }

    delete[] lista;  // Liberar memoria
}
