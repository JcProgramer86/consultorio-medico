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
