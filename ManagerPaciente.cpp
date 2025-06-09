#include "ManagerPaciente.h"
#include "Paciente.h"
#include "ArchivoPaciente.h"
#include "Fecha.h"
#include <iostream>

using namespace std;

void ManagerPaciente::crearNuevoPaciente() {
    Paciente paciente;
    ArchivoPaciente aPaciente("paciente.dat") ;

    string nombre,apellido,dni,telefono,email;
    int idPrestador,id,dia,mes,anio;
    bool bandera = false;

    while(bandera == false){
            bandera = true;
            cout<<"Ingrese el numero de dni: "<<endl;
            cin>>dni;
            if(!aPaciente.checkDni(dni)){
                bandera = false;
            }
    }


    cout<<"Ingrese el nombre del paciente: "<<endl;
    cin.ignore();
    getline(cin,nombre);

    cout<<"Ingrese el apellido del paciente: "<<endl;
    getline(cin,apellido);

    cout<<"Ingrese el nuemero de telefono: "<<endl;
    getline(cin,telefono);

    cout<<"Ingrese el email: "<<endl;
    getline(cin,email);

    cout<<"ingrese dia del mes en que nacio: "<<endl;
    cin>>dia;

    cout<<"Ingrese mes en el que nacio: "<<endl;
    cin>>mes;

    cout<<"Ingrese año en el que nacio: "<<endl;
    cin>>anio;

    cout<<"Ingrese el prestador: "<<endl;
    cin>>idPrestador;

    Fecha fechaNacimiento(dia,mes,anio);


    id = aPaciente.generarNuevoId();

    paciente = Paciente(id,dni,nombre,apellido,telefono,email,idPrestador,fechaNacimiento);

    if(aPaciente.Guardar(paciente)){
        cout << "Se guardo correctamente!" << endl;
      }else{
        cout << "Hubo un error inesperado, llame al de sistemas..." << endl;
      }


}

void ManagerPaciente::ListarTodos(){
    Paciente paciente;

    ArchivoPaciente aPaciente("paciente.dat");
    int cant = aPaciente.CantidadRegistros();

    for(int x = 0;x < cant;x++){
        paciente = aPaciente.Leer(x);
        cout<<paciente.toCSV()<<endl;
        cout<<endl;
        cout<<"--------"<<endl;
    }

}

void ManagerPaciente::MostrarPorDni(){

    Paciente paciente;
    ArchivoPaciente aPaciente("paciente.dat");
    string dni;

    cout<<"Ingrese numero del paciente que desea buscar"<<endl;
    cin>>dni;

    int idPaciente = aPaciente.BuscarPorDni(dni);
    paciente = aPaciente.Leer(idPaciente-1);

    cout<<"Datos del paciente: "<<endl;
    cout<<endl;
    cout << "ID: " << paciente.get_id() << endl;
    cout << "DNI: " << paciente.get_dni() << endl;
    cout << "Nombre: " << paciente.get_nombre() << endl;
    cout << "Apellido: " << paciente.get_apellido() << endl;
    cout << "Teléfono: " << paciente.get_telefono() << endl;
    cout << "Email: " << paciente.get_email() << endl;
    cout << "Fecha de nacimiento: " << paciente.get_fechaNacimiento().toString() << endl;
    cout << "ID Prestador: " << paciente.get_idPrestador() << endl;


}

void ManagerPaciente::EditarPaciente() {
    ArchivoPaciente aPaciente("paciente.dat");
    string dni;

    cout << "Ingrese el DNI del paciente que quiere editar: ";
    cin >> dni;

    int pos = aPaciente.BuscarPorDni(dni);
    if (pos == -1) {
        cout << "Paciente no encontrado." << endl;
        return;
    }

    Paciente paciente = aPaciente.Leer(pos);
    int opcion = 0;

    do {
        cout << "\n--- Editar Paciente ID: " << paciente.get_id() << " ---" << endl;
        cout << "1. Editar Nombre (actual: " << paciente.get_nombre() << ")" << endl;
        cout << "2. Editar Apellido (actual: " << paciente.get_apellido() << ")" << endl;
        cout << "3. Editar Teléfono (actual: " << paciente.get_telefono() << ")" << endl;
        cout << "4. Editar Email (actual: " << paciente.get_email() << ")" << endl;
        cout << "5. Editar Fecha de Nacimiento (actual: " << paciente.get_fechaNacimiento().toString() << ")" << endl;
        cout << "6. Editar ID Prestador (actual: " << paciente.get_idPrestador() << ")" << endl;
        cout << "7. Guardar y salir" << endl;
        cout << "0. Cancelar sin guardar" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                string nombre;
                cout << "Ingrese nuevo nombre: ";
                getline(cin, nombre);
                paciente.set_nombre(nombre);
                break;
            }
            case 2: {
                string apellido;
                cout << "Ingrese nuevo apellido: ";
                getline(cin, apellido);
                paciente.set_apellido(apellido);
                break;
            }
            case 3: {
                string telefono;
                cout << "Ingrese nuevo teléfono: ";
                getline(cin, telefono);
                paciente.set_telefono(telefono);
                break;
            }
            case 4: {
                string email;
                cout << "Ingrese nuevo email: ";
                getline(cin, email);
                paciente.set_email(email);
                break;
            }
            case 5: {
                int dia, mes, anio;
                cout << "Ingrese nuevo día de nacimiento: ";
                cin >> dia;
                cout << "Ingrese nuevo mes: ";
                cin >> mes;
                cout << "Ingrese nuevo año: ";
                cin >> anio;
                paciente.set_fechaNacimiento(Fecha(dia, mes, anio));
                break;
            }
            case 6: {
                int idPrestador;
                cout << "Ingrese nuevo ID de prestador: ";
                cin >> idPrestador;
                paciente.set_idPrestador(idPrestador);
                break;
            }
            case 7:
                if (aPaciente.Guardar(paciente, pos)) {
                    cout << "Paciente actualizado correctamente." << endl;
                } else {
                    cout << "Error al guardar el paciente." << endl;
                }
                return;
            case 0:
                cout << "Operación cancelada. No se realizaron cambios." << endl;
                return;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (true);
}


