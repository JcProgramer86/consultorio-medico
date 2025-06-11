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
        cout << "No se encontró un médico con ese DNI." << endl;
        return false;
    }
    Medico medicoEncontrado = aMedico.Leer(posicion);

    cout << "Datos actuales del médico: " << endl;
    cout << medicoEncontrado.toCSV() << endl;

    int opcion;
    do
    {
        cout << "\n--- Menú de modificación ---" << endl;
        cout << "1. Modificar DNI" << endl; // opcional si quieres permitir
        cout << "2. Modificar nombre" << endl;
        cout << "3. Modificar apellido" << endl;
        cout << "4. Modificar teléfono" << endl;
        cout << "5. Modificar email" << endl;
        cout << "6. Modificar fecha de nacimiento" << endl;
        cout << "7. Modificar id de especialidad" << endl;
        cout << "8. Modificar fecha de inicio de actividad" << endl;
        cout << "9. Modificar matrícula" << endl;
        cout << "10. Modificar estado (enabled)" << endl;
        cout << "11. Ver datos actuales" << endl;
        cout << "0. Guardar y salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
            case 1:
            {
                std::string nuevoDni;
                cout << "Ingrese el nuevo DNI: ";
                getline(cin, nuevoDni);
                // Validar si el nuevo DNI no existe ya:
                if (aMedico.checkDni(nuevoDni))
                {
                    medicoEncontrado.set_dni(nuevoDni);
                }
                else
                {
                    cout << "El DNI ya existe, no se puede modificar." << endl;
                }
                break;
            }
            case 2:
            {
                std::string nuevoNombre;
                cout << "Ingrese el nuevo nombre: ";
                getline(cin, nuevoNombre);
                medicoEncontrado.set_nombre(nuevoNombre);
                break;
            }
            case 3:
            {
                std::string nuevoApellido;
                cout << "Ingrese el nuevo apellido: ";
                getline(cin, nuevoApellido);
                medicoEncontrado.set_apellido(nuevoApellido);
                break;
            }
            case 4:
            {
                std::string nuevoTelefono;
                cout << "Ingrese el nuevo teléfono: ";
                getline(cin, nuevoTelefono);
                medicoEncontrado.set_telefono(nuevoTelefono);
                break;
            }
            case 5:
            {
                std::string nuevoEmail;
                cout << "Ingrese el nuevo email: ";
                getline(cin, nuevoEmail);
                medicoEncontrado.set_email(nuevoEmail);
                break;
            }
            case 6:
            {
                int dia, mes, anio;
                cout << "Ingrese nuevo día de nacimiento: ";
                cin >> dia;
                cout << "Ingrese nuevo mes de nacimiento: ";
                cin >> mes;
                cout << "Ingrese nuevo año de nacimiento: ";
                cin >> anio;
                cin.ignore();
                Fecha nuevaFechaNacimiento(dia, mes, anio);
                medicoEncontrado.set_fechaNacimiento(nuevaFechaNacimiento);
                break;
            }
            case 7:
            {
                int nuevoIdEspecialidad;
                cout << "Ingrese nuevo id de especialidad: ";
                cin >> nuevoIdEspecialidad;
                cin.ignore();
                medicoEncontrado.set_idEspecialidad(nuevoIdEspecialidad);
                break;
            }
            case 8:
            {
                int dia, mes, anio;
                cout << "Ingrese nuevo día de inicio de actividad: ";
                cin >> dia;
                cout << "Ingrese nuevo mes de inicio de actividad: ";
                cin >> mes;
                cout << "Ingrese nuevo año de inicio de actividad: ";
                cin >> anio;
                cin.ignore();
                Fecha nuevaFechaInicio(dia, mes, anio);
                medicoEncontrado.set_fechaInicioActividad(nuevaFechaInicio);
                break;
            }
            case 9:
            {
                std::string nuevaMatricula;
                cout << "Ingrese nueva matrícula: ";
                getline(cin, nuevaMatricula);
                medicoEncontrado.set_matricula(nuevaMatricula);
                break;
            }
            case 10:
            {
                int estado;
                cout << "Ingrese nuevo estado (1 = activo, 0 = inactivo): ";
                cin >> estado;
                cin.ignore();
                medicoEncontrado.set_enabled(estado == 1);
                break;
            }
            case 11:
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

    } while (opcion != 0);

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

    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++)
    {
        Medico medico = archivo.Leer(i);  // Usamos el método que devuelve Medico

        if (medico.get_enabled())
        {
            cout << medico.toCSV() << endl;
            hayActivos = true;
        }
    }

    if (!hayActivos)
    {
        cout << "No hay médicos activos para mostrar." << endl;
    }
}
