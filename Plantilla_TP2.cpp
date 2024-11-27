#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Estructura para representar un movimiento
struct Movimiento{
    int sueldo_anterior;
    int sueldo_posterior;
};
// Estructura para representar un plazo fijo
struct PlazoFijo{
    int plata_inicial;
    int dias;
    int interes;
    int total;
    bool en_proceso;
};
// Estructura para representar una cuenta bancaria
struct Cuenta{
    // Datos de la cuenta bancaria
    string nusuario, contrasenia;
    vector <PlazoFijo> plazos_fijos;
    vector <Movimiento> movimientos;
    int cantidad_dolares = 0, saldo_en_cuenta = 0;
};
// Función para mostrar el menú principal
void menu_principal(Cuenta usuario)
{
    cout << endl;
    cout << "Bienvenido/a al sistema bancario, " << usuario.nusuario << endl;
    cout << "Saldo en cuenta: $ " << usuario.saldo_en_cuenta << endl;
    cout << "Dolares: USD$ " << usuario.cantidad_dolares << endl;
    cout << "Plazos fijos armados: " << usuario.plazos_fijos.size() << endl;
    cout << endl;
    cout << "1 - Ingresar efectivo." << endl;
    cout << "2 - Retirar efectivo." << endl;
    cout << "3 - Comprar y/o vender dolares." << endl;
    cout << "4 - Retirar dolares." << endl;
    cout << "5 - Armar plazo fijo." << endl;
    cout << "6 - Cancelar plazo fijo." << endl;
    cout << "7 - Pedir prestamo." << endl;
    cout << "8 - Ver movimientos." << endl;
    cout << "9 - Actualizar datos." << endl;
    cout << "10 - Salir del sistema." << endl;
    cout << endl;
    cout << "Elegir una opcion del menu: " << endl;
}

// 1
void ingresar_efectivo(Cuenta &usuario,int opcion,Movimiento temporal, vector <Movimiento> &ingresos) {
    int efectivo_ingreso;
    cout<<"escriba la cantidad de efectivo a ingresar a su cuenta: ";
    cin>>efectivo_ingreso;
    temporal.sueldo_anterior = usuario.saldo_en_cuenta;
    usuario.saldo_en_cuenta += efectivo_ingreso;
    temporal.sueldo_posterior = usuario.saldo_en_cuenta;
    ingresos.push_back(temporal);
}

// 2
void retirar_efectivo(Cuenta &usuario,int opcion,Movimiento temporal, vector <Movimiento> &retiros) {
    int efectivo_retiro;
    int eleccion;
    cout<<"--RECUERDE QUE SOLO SE REALIZAN TRANSACCIONES CON BILLETES DE 100 PARA ARRIBA--"<<endl;
    cout<<"quiere retirar todo el dinero o quiere una parte?"<<endl;
    cout<<"1- TODO"<<endl;
    cout<<"2- PARTE"<<endl;
    cin>>eleccion;
    // la opcion TODO no cuenta para el ejercicio porque no es lo indicado, pero nos parecio una forma practica.
    if (eleccion==1){
        efectivo_retiro=usuario.saldo_en_cuenta;
        temporal.sueldo_anterior=usuario.saldo_en_cuenta;
        usuario.saldo_en_cuenta-=efectivo_retiro;
        temporal.sueldo_posterior=usuario.saldo_en_cuenta;
        retiros.push_back(temporal);
        while(efectivo_retiro>=1000){
            cout<<"*se da billete de 1000*"<<endl;
            efectivo_retiro-=1000;}
        while(efectivo_retiro>=500){
            cout<<"*se da billete de 5000*"<<endl;
            efectivo_retiro-=500;}
        while(efectivo_retiro>=200){
            cout<<"*se da billete de 200*"<<endl;
            efectivo_retiro-=200;}
        while(efectivo_retiro>=100){
            cout<<"*se da billete de 100*"<<endl;
            efectivo_retiro-=100;}                       
        cout<<"--TRANSACCION EXITOSA--"<<endl;
    }
    else if(eleccion==2){
        cout<<"ingrese el monto que desea retirar de su cuenta: ";

        cin>>efectivo_retiro;
        if(efectivo_retiro > usuario.saldo_en_cuenta){
            cout<<"*ERROR* estas queriendo retirar mas de lo que tenes en la cuenta."<<endl;
            cout<<"--REDIRIGIENDO AL MENU PRINCIPAL..."<<endl;
        }
        else if(efectivo_retiro % 100 != 0){
            cout<<"*ERROR* estas queriendo retirar cifras menores a 100."<<endl;
            cout<<"--REDIRIGIENDO AL MENU PRINCIPAL..."<<endl;
        }
        else{
            temporal.sueldo_anterior=usuario.saldo_en_cuenta;
            usuario.saldo_en_cuenta-=efectivo_retiro;
            temporal.sueldo_posterior=usuario.saldo_en_cuenta;
            retiros.push_back(temporal);
            while(efectivo_retiro>=1000){
                cout<<"*se da billete de 1000*"<<endl;
                efectivo_retiro-=1000;}
            while(efectivo_retiro>=500){
                cout<<"*se da billete de 5000*"<<endl;
                efectivo_retiro-=500;}
            while(efectivo_retiro>=200){
                cout<<"*se da billete de 200*"<<endl;
                efectivo_retiro-=200;}
            while(efectivo_retiro>=100){
                cout<<"*se da billete de 100*"<<endl;
                efectivo_retiro-=100;} 
            cout<<"--TRANSACCION EXITOSA--"<<endl;
        }
    }
    else{
        cout<<"*ERROR* opcion invalida"<<endl;
        cout<<"--REDIRIGIENDO AL MENU PRINCIPAL..."<<endl;
    }
}
// 3
void manejar_dolares(Cuenta &usuario, int opcion, Movimiento temporal, vector <Movimiento> &ingresos_dolares,vector <Movimiento> &ventas_dolares) {
    int var1,compra_dolres, venta_dolares, compra_pesos, venta_pesos, dolares_sugeridos;
    bool var=true;
    while(var){
        cout<<endl;
        cout<<"--SECCION DOLARES--"<<endl;
        cout<<"1- comprar dolares"<<endl;
        cout<<"2- vender dolares"<<endl;
        cout<<"3- salir"<<endl;
        cin>>var1;
        switch(var1){
        case 1:
            cout<<"--RECUERDE QUE SU SALDO ES DE $"<< usuario.saldo_en_cuenta <<" PESOS"<<endl;
            cout<<"--CADA DOLAR SON $1000 PESOS"<<endl;
            cout<<"cuantos dolares quiere comprar?"<<endl;
            cin>>compra_dolres;
            compra_pesos = compra_dolres * 1000;
            cout<<"La cantidad de pesos que le saldria la compra es de $" << compra_pesos <<" pesos"<<endl;
            if(compra_pesos <= usuario.saldo_en_cuenta){
                temporal.sueldo_anterior = usuario.cantidad_dolares;
                usuario.cantidad_dolares += compra_dolres;
                temporal.sueldo_posterior = usuario.cantidad_dolares;
                ingresos_dolares.push_back(temporal);
                usuario.saldo_en_cuenta -= compra_pesos;
                cout<<"--COMPRA REALIZADA CON EXITO--"<<endl;
            }
            else{
                dolares_sugeridos = usuario.saldo_en_cuenta/1000;
                cout<<"no tiene el dinero suficiente para realizar la compra, le alcanza para: $"<<dolares_sugeridos<<" dolares como maximo"<<endl;
            }
            break;
        case 2:
            // se revisa si tiene mas de 10 dolares en la cuenta
            if (usuario.cantidad_dolares < 10){
                cout<<"*ERROR* lo sentimos, solo se pueden vender dolares cuando tiene mas de 10 o mas en la cuenta"<<endl;
                cout<<endl;
                break;
            }
            
            cout<<"--RECUERDE QUE SU SALDO ES DE $"<< usuario.saldo_en_cuenta <<" PESOS Y $"<<usuario.cantidad_dolares<<" DOLARES"<<endl;
            cout<<"--CADA DOLAR SON $1000 PESOS"<<endl;
            cout<<"cuantos dolares quiere vender?"<<endl;
            cin>>venta_dolares;
            venta_pesos = venta_dolares * 1000;
            cout<<"La cantidad de pesos que le daria la venta es de $" << venta_pesos <<" pesos"<<endl;
            if(usuario.cantidad_dolares >= venta_dolares){
                temporal.sueldo_anterior = usuario.cantidad_dolares;
                usuario.cantidad_dolares -= venta_dolares;
                temporal.sueldo_posterior = usuario.cantidad_dolares;
                ventas_dolares.push_back(temporal);
                usuario.saldo_en_cuenta += venta_pesos;
                cout<<"--VENTA REALIZADA CON EXITO--"<<endl;
            }
            else{
                cout<<"pero no tiene la cantidad de dolares que quiere vender,"<<endl<<"puede vender los: $"<<usuario.cantidad_dolares<<" dolares de su cuenta como maximo"<<endl;
                cout<<endl;
            }
            break;
        case 3:
            var=false;
            break;    
    }
    }    
}

// 4
void retirar_dolares(Cuenta &usuario, int opcion,Movimiento temporal, vector <Movimiento> &retiros_dolares) {
    bool var=true;
    int retiro_dolres;
    while (var)
    {
        cout<<"--RECUERDE QUE SOLO SE REALIZAN TRANSACCIONES CON BILLETES DE 10 PARA ARRIBA--"<<endl;
        cout<<"--Y QUE TIENE $"<<usuario.cantidad_dolares<<" DOLARES"<<endl;
        cout<<"cuantos dolares quiere retirar?"<<endl;
        cin>>retiro_dolres;

        if(retiro_dolres > usuario.cantidad_dolares){
            cout<<"*ERROR* solo puede retirar un monto inferior al que posee en su cuent"<<endl;
        }
        else if(retiro_dolres % 10 != 0){
            cout<<"*ERROR* solo se pueden dar billetes de 10, no inferiores"<<endl;
        }
        else{
            temporal.sueldo_anterior = usuario.cantidad_dolares;
            usuario.cantidad_dolares -= retiro_dolres;
            temporal.sueldo_posterior = usuario.cantidad_dolares;
            retiros_dolares.push_back(temporal);

            while(retiro_dolres>=100){
                cout<<"*se da billete de 100*"<<endl;
                retiro_dolres-=100;}
            while(retiro_dolres>=50){
                cout<<"*se da billete de 50*"<<endl;
                retiro_dolres-=50;}
            while(retiro_dolres>=20){
                cout<<"*se da billete de 20*"<<endl;
                retiro_dolres-=20;}
            while(retiro_dolres>=10){
                cout<<"*se da billete de 10*"<<endl;
                retiro_dolres-=10;}

            var=false;
        }
    }
}

// 5
void armar_plazo_fijo(Cuenta &usuario, int opcion) {
    bool var=true;
    while (var){
        int invertido_monto, invertido_dias, interes, invertido_gananacia;
        PlazoFijo plazo_usuario;

        cout<<"--RECUERDE QUE SU SALDO ES DE $"<<usuario.saldo_en_cuenta<<" PESOS--"<<endl;
        cout<<"cuantos pesos invertira en el plazo fijo?"<<endl;
        cin>>invertido_monto;

        cout<<"--RECUERDE QUE EL PLAZO FIJO TENDRA MINIMO 30 DIAS--"<<endl;
        cout<<"cuantos dias durara el plazo fijo?"<<endl;
        cin>>invertido_dias;

        if(invertido_monto > usuario.saldo_en_cuenta){
            cout<<"*ERROR* el monto que quiere invertir es mayor al saldo de su cuenta"<<endl;
            cout<<"--REINICIANDO OPERACION...--"<<endl;
            cout<<endl;
        }
        if(invertido_dias < 30){
            cout<<"*ERROR* recuerde que el plazo fijo durara minimo 30 dias"<<endl;
            cout<<"--REINICIANDO OPERACION...--"<<endl;
            cout<<endl;
        }

        else{
            usuario.saldo_en_cuenta -= invertido_monto;
            interes = (invertido_monto * invertido_dias * 70) / 36500;
            invertido_gananacia = invertido_monto + interes;

            cout<<"DINERO INVERTIDO: $"<< invertido_monto<<endl;
            cout<<"DIAS DE DURACION: "<< invertido_dias<<endl;
            cout<<"INTERES GENERADO: "<< interes<<endl;
            cout<<"DINERO AL FINAL DEL PLAZO: $"<<invertido_gananacia<<endl;

            plazo_usuario.plata_inicial = invertido_monto;
            plazo_usuario.dias = invertido_dias;
            plazo_usuario.interes = interes;
            plazo_usuario.total = invertido_gananacia;
            plazo_usuario.en_proceso = true;

            usuario.plazos_fijos.push_back(plazo_usuario);
            var = false;
        }
    }
}
// 6
void cancelar_plazo_fijo(Cuenta &usuario, int opcion) {
    int var;
    int indice = var-1;
    if(!usuario.plazos_fijos.empty()){
        cout<<"--PLAZOS FIJOS--"<<endl;

        for(int i = 0 ; i < usuario.plazos_fijos.size() ; i++){
            cout<<endl;
            cout<< i + 1 <<"- DINERO INVERTIDO: $"<< usuario.plazos_fijos[i].plata_inicial<<endl;
            cout<<"DIAS DE DURACION: "<< usuario.plazos_fijos[i].dias<<endl;
            cout<<endl;
        }
        cout<<"--INDICAR CON NUMERO QUE PLAZO DESEA CANCELAR--"<<endl;
        cin>>var;
        // se cambia el estado para identificar cual plazo se debe eliminar
        usuario.plazos_fijos[indice].en_proceso = false;

        if(usuario.plazos_fijos[indice].en_proceso == false){
            cout<<"--LOS $"<<usuario.plazos_fijos[indice].plata_inicial<<" PESOS FUERON DEPOSITADOS EN SU CUENTA--";
            usuario.saldo_en_cuenta += usuario.plazos_fijos[indice].plata_inicial;

            // en la linea de codigo de aabajo necesito borrar el plazo fijo indicado por el usuario, primero lo identifico con el estado
            // y despues uso el .erase que elimina el elemento de un vector. Para esto uso el begin + indice que agarra el primer elemento del vector
            // y le suma el indice que indico el usuario.
            // BASICAMENTE, .begin() + indice devuelve la posicion del plazo fijo elegido y .erase() lo elimina
            usuario.plazos_fijos.erase(usuario.plazos_fijos.begin()+indice);
            cout<<"--PLAZO "<<var<<" ELIMINADO--"<<endl;

        }
        else{
            cout<<"*ERROR*"<<endl;
        }
    }
    else{
        cout<<endl;
        cout<<"--USTED NO TIENE PLAZOS FIJOS--"<<endl;
        cout<<"--REDIRIGIENDO AL MENU...--"<<endl;
    }
}

// 7
void pedir_prestamo(Cuenta &usuario, int opcion, vector <Movimiento> &prestamos,Movimiento temporal) {
    bool condicion=true;
    int opcion_prestamo;

    while(condicion){
        cout<<"--PRESTAMOS--"<<endl;
        cout<<endl;
        cout<<"1- PRESTAMO 1"<<endl
        <<"--SOLO ACCESIBLE PARA USUARIOS CON MAS DE $20000 PESOS--"<<endl
        <<"--SE LE ACREDITARIA EL 5 PORCIENTO DEL SALDO DE SU CUENTA A LA CARTERA"<<endl;
        cout<<endl;
        cout<<"2- PRESTAMO 2"<<endl
        <<"--SOLO ACCESIBLE PARA USUARIOS CON MAS DE $50000 PESOS--"<<endl
        <<"--SE LE ACREDITARIA EL 10 PORCIENTO DEL SALDO DE SU CUENTA A LA CARTERA"<<endl;
        cout<<endl;
        cout<<"3- PRESTAMO 3"<<endl
        <<"--SOLO ACCESIBLE PARA USUARIOS CON MAS DE $100000 PESOS--"<<endl
        <<"--SE LE ACREDITARIA EL 15 PORCIENTO DEL SALDO DE SU CUENTA A LA CARTERA"<<endl;
        cout<<endl;
        cout<<"4- SALIR"<<endl;
        cin>>opcion_prestamo;    

        switch(opcion_prestamo){
            case 1:
                if(usuario.saldo_en_cuenta <= 20000){
                    cout<<"*ERROR* no cumple con la condicion"<<endl;
                    condicion=false;
                    break;
                }
                else{
                    temporal.sueldo_anterior = usuario.saldo_en_cuenta;
                    usuario.saldo_en_cuenta += (usuario.saldo_en_cuenta*5)/100;
                    temporal.sueldo_posterior = usuario.saldo_en_cuenta;
                    prestamos.push_back(temporal);
                    cout<<"--ACREDITACION EXITOSA--"<<endl;
                }
                break;
            case 2:
                if(usuario.saldo_en_cuenta<=50000){
                    cout<<"*ERROR* no cumple con la condicion"<<endl;
                    condicion=false;
                    break;
                }
                else{
                    temporal.sueldo_anterior = usuario.saldo_en_cuenta;
                    usuario.saldo_en_cuenta += (usuario.saldo_en_cuenta*10)/100;
                    temporal.sueldo_posterior = usuario.saldo_en_cuenta;
                    prestamos.push_back(temporal);
                    cout<<"--ACREDITACION EXITOSA--"<<endl;
                }
                break;
            case 3:
                if(usuario.saldo_en_cuenta<=100000){
                    cout<<"*ERROR* no cumple con la condicion"<<endl;
                    condicion=false;
                    break;
                }
                else{
                    temporal.sueldo_anterior = usuario.saldo_en_cuenta;
                    usuario.saldo_en_cuenta += (usuario.saldo_en_cuenta*15)/100;
                    temporal.sueldo_posterior = usuario.saldo_en_cuenta;
                    prestamos.push_back(temporal);
                    cout<<"--ACREDITACION EXITOSA--"<<endl;
                }
                break;
            case 4:
                condicion=false;
                break;    
            default:
                cout<<"*ERROR* opcion invalida"<<endl;
                break;            
        }    
}
}
// 8
void ver_movimientos(Cuenta usuario,vector <Movimiento> ingresos,vector <Movimiento> retiros,vector <Movimiento> prestamos,vector <Movimiento> ingresos_dolares,vector <Movimiento> ventas_dolares,vector <Movimiento> retiros_dolares) {
    int var;
    cout<<"--MOVIMIENTOS DE LA CUENTA--"<<endl;
    cout<<"-SI QUIERE VER INFO DETALLADA ESCRIBA EL NUMERO  LA DERECHA DEL MOVIMIENTO-"<<endl;
    cout<<"-ESCRIBA 'menu' PARA IR HACIA ESTE-"<<endl;
    cout<<ingresos.size()<<" INGRESOS PESOS --1"<<endl;
    cout<<retiros.size()<<" RETIROS PESOS --2"<<endl;
    cout<<ingresos_dolares.size()<<" INGRESOS DOLARES --3"<<endl;
    cout<<ventas_dolares.size()<<" VENTAS DOLARES --4"<<endl;
    cout<<retiros_dolares.size()<<" RETIROS DOLRES --5"<<endl;
    cout<<usuario.plazos_fijos.size()<<" PLAZOS FIJOS --6"<<endl;
    cout<<prestamos.size()<<" PRESTAMOS --7"<<endl;
    cout<<"MENU --8"<<endl;
    cout<<endl;
    cout<<"INGRESE OPCION:"<<endl;
    cin>>var;

    cout<<endl;
    if(!ingresos.empty() && var==1){
        cout<<"--INGRESO PESOS--"<<endl;
        for(int i = 0; i < (ingresos.size()); i++){
            cout<<"SALDO ANTERIOR: "<<ingresos[i].sueldo_anterior<<endl;
            cout<<"SALDO POSTERIOR: "<<ingresos[i].sueldo_posterior<<endl;
        }
    }
    if(!retiros.empty() && var==2){
        cout<<"--RETIRO PESOS--"<<endl;
        for(int i = 0; i < retiros.size(); i++){
            cout<<"SALDO ANTERIOR: "<<retiros[i].sueldo_anterior<<endl;
            cout<<"SALDO POSTERIOR: "<<retiros[i].sueldo_posterior<<endl;
        }
    }
    if(!ingresos_dolares.empty() && var==3){
        cout<<"--INGRESO DOLARES--"<<endl;
        for(int i = 0; i < ingresos_dolares.size(); i++){
            cout<<"SALDO ANTERIOR: "<<ingresos_dolares[i].sueldo_anterior<<endl;
            cout<<"SALDO POSTERIOR: "<<ingresos_dolares[i].sueldo_posterior<<endl;
        }
    }
    if(!ventas_dolares.empty() && var==4){
        cout<<"--VENTA DOLARES--"<<endl;
        for(int i = 0; i < ventas_dolares.size(); i++){
            cout<<"SALDO ANTERIOR: "<<ventas_dolares[i].sueldo_anterior<<endl;
            cout<<"SALDO POSTERIOR: "<<ventas_dolares[i].sueldo_posterior<<endl;
        }
    }
    if(!retiros_dolares.empty() && var==5){
        cout<<"--RETIRO DOLARES--"<<endl;
        for(int i = 0; i < retiros_dolares.size()-1; i++){
            cout<<"SALDO ANTERIOR: "<<retiros_dolares[i].sueldo_anterior<<endl;
            cout<<"SALDO POSTERIOR: "<<retiros_dolares[i].sueldo_posterior<<endl;
        }
    }
        if(!usuario.plazos_fijos.empty() && var==6){
        cout<<"--PLAZOS FIJOS--"<<endl;
        for(int i = 0; i < usuario.plazos_fijos.size() ; i++){
            if(usuario.plazos_fijos[i].en_proceso){
                cout<<"DINERO INVERTIDO: $"<< usuario.plazos_fijos[i].plata_inicial<<endl;
                cout<<"DIAS DE DURACION: "<< usuario.plazos_fijos[i].dias<<endl;
                cout<<"INTERES GENERADO: "<< usuario.plazos_fijos[i].interes<<endl;
                cout<<"DINERO AL FINAL DEL PLAZO: $"<<usuario.plazos_fijos[i].total<<endl;
            }
        }
    }
        if(!prestamos.empty() && var==7){
        cout<<"--PRESTAMOS--"<<endl;
        for(int i = 0; i < prestamos.size(); i++){
            cout<<"SALDO ANTERIOR: "<<prestamos[i].sueldo_anterior<<endl;
            cout<<"SALDO POSTERIOR: "<<prestamos[i].sueldo_posterior<<endl;
        }
    }
}   

// 9
void actualizar_datos(Cuenta &usuario, int opcion, string name) {
    ifstream file_ent("datos.txt");
    ofstream file_temp("temporal.txt");
    string linea;
    bool encontrado = false;

    if (!file_ent.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }

    if (!file_temp.is_open()) {
        cout << "Error al crear el archivo temporal." << endl;
        return;
    }
    
    string auxil;
    cout<<"que deseas cambiar, tu contrasena o tu usuario"<<endl;
    cin>>auxil;
    if(auxil=="usuario"){
        string newname;
        cout<<"que nombre le queres poner?"<<endl;
        cin>>newname;
        //aca reemplazar el nombre de usuario por la variable newname
        while (getline(file_ent, linea)) {
        stringstream ss(linea);
        string nusuario, contrasenia, saldo, dolares, resto;
        getline(ss, nusuario, ',');       // Extrae nombre de usuario
        getline(ss, contrasenia, ',');    // Extrae contrasena
        getline(ss, saldo, ',');          // Extrae saldo
        getline(ss, dolares, ',');        // Extrae dólares
        getline(ss, resto);               // Extrae lo restante

        if (nusuario == name) {
            // Si encontramos al usuario, actualizamos saldo y dólares
            encontrado = true;
            file_temp << newname << "," << contrasenia << ","
                    << usuario.saldo_en_cuenta << "," 
                    << usuario.cantidad_dolares << "," 
                    << resto << endl;
        } else {
            // Escribimos la línea original en el archivo temporal
            file_temp << linea << endl;
        }
    }

    file_ent.close();
    file_temp.close();

    }
    else if(auxil=="contrasena"){
        
        string newcon, checon;
        cout<<"que contrasena le queres poner?"<<endl;
        cin>>newcon;
        cout<<"confirmar contrasena"<<endl;
        cin>>checon;
        if(newcon==checon){
            //aca reemplazar la contrasena en el txt por newcon
            while (getline(file_ent, linea)) {
        stringstream ss(linea);
        string nusuario, contrasenia, saldo, dolares, resto;
        getline(ss, nusuario, ',');       // Extrae nombre de usuario
        getline(ss, contrasenia, ',');    // Extrae contrasena
        getline(ss, saldo, ',');          // Extrae saldo
        getline(ss, dolares, ',');        // Extrae dólares
        getline(ss, resto);               // Extrae lo restante

        if (nusuario == name) {
            // Si encontramos al usuario, actualizamos saldo y dólares
            encontrado = true;
            file_temp << nusuario<< "," << checon << ","
                    << usuario.saldo_en_cuenta << "," 
                    << usuario.cantidad_dolares << "," 
                    << resto << endl;
        } else {
            // Escribimos la línea original en el archivo temporal
            file_temp << linea << endl;
        }
    }

    file_ent.close();
    file_temp.close();
        }
    }
    if (encontrado) {
        // Reemplazamos el archivo original con el temporal
        remove("datos.txt");
        rename("temporal.txt", "datos.txt");
        cout << "Datos del usuario actualizados con éxito." << endl;
    } else {
        // Eliminamos el archivo temporal si no se encontró el usuario
        remove("temporal.txt");
        cout << "Usuario no encontrado." << endl;
    }
}

void f5_datos(Cuenta usuario, string name, int pf) {
    ifstream file_ent("datos.txt");
    ofstream file_temp("temporal.txt");
    string linea;
    bool encontrado = false;

    if (!file_ent.is_open()) {
        cout << "*ERROR*" << endl;
        return;
    }

    if (!file_temp.is_open()) {
        cout << "*ERROR*" << endl;
        return;
    }

    // Leer línea por línea del archivo original
    while (getline(file_ent, linea)) {
        stringstream ss(linea);
        string nusuario, contrasenia, saldo, dolares, resto;
        getline(ss, nusuario, ',');       // Extrae nombre de usuario
        getline(ss, contrasenia, ',');    // Extrae contrasena
        getline(ss, saldo, ',');          // Extrae saldo
        getline(ss, dolares, ',');        // Extrae dólares
        getline(ss, resto);               // Extrae lo restante

        if (nusuario == name) {
            // Si encontramos al usuario, actualizamos saldo y dólares
            encontrado = true;
            file_temp << nusuario << "," << contrasenia << ","
                    << usuario.saldo_en_cuenta << "," 
                    << usuario.cantidad_dolares << "," 
                    << pf+(usuario.plazos_fijos.size()) << endl;
        } else {
            // Escribimos la línea original en el archivo temporal
            file_temp << linea << endl;
        }
    }

    file_ent.close();
    file_temp.close();

    if (encontrado) {
        // Reemplazamos el archivo original con el temporal
        remove("datos.txt");
        rename("temporal.txt", "datos.txt");
        cout << "--ACTUALIZACION EXITOSA--" << endl;
    } else {
        // Eliminamos el archivo temporal si no se encontró el usuario
        remove("temporal.txt");
    }
}


int main(){
    vector <Cuenta> usuarios;
    Cuenta usuario;
    Movimiento movimiento2;
    vector <Movimiento> ingresos;
    vector <Movimiento> retiros;
    vector <Movimiento> prestamos;
    vector <Movimiento> ingresos_dolares;
    vector <Movimiento> retiros_dolares;
    vector <Movimiento> ventas_dolares;
    int var1;
    int saldoDB, dolaresDB, pfBD;
    ifstream archivo;
    bool usuarioEncontrado = false, contrasenaCorrecta = false, sesion1 = true;
    string nusuario, contrasena, linea, usuarioBD, contrasenaBD,saldoDB2, dolaresDB2,cantidad_plazo_fijosBD;
    
    cout << "         --$-- SISTEMA BANCARIO --$--" << endl;
    cout << "-inrgese sus datos, si tiene una cuenta sera loggeado con esta, sino le registraremos una-" << endl;
    cout << "NOMBRE DE USUARIO: ";
    getline(cin, nusuario);
    cout << "CONTRASENA: ";
    getline(cin, contrasena);

    archivo.open("datos.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "*ERROR* abriendo aarchivo de la DB" << endl;
        return 1;
    }

    // Lectura del archivo y comparación
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, usuarioBD, ',');      // Extraer usuario
        getline(ss, contrasenaBD, ',');   // Extraer contrasena
        getline(ss, saldoDB2, ',');
        getline(ss, dolaresDB2, ',');
        getline(ss, cantidad_plazo_fijosBD, '.');


        if (nusuario == usuarioBD) {
            usuarioEncontrado = true;
            if (contrasena == contrasenaBD) {
                contrasenaCorrecta = true;
                //aca extraer los datos de el txt

                break; // Ambos son correctos, salir del bucle
            }
        }
    }
    archivo.close();

    // Comprobar resultados
    if (usuarioEncontrado) {
        if (contrasenaCorrecta) {
            //usuario.saldo_en_cuenta+=saldoDB;
            cout << "--SESION INICIADA CORRECTAMENTE--" << endl;
            cout<<"--CUENTA--"<<endl<<"SALDO: $"<<saldoDB2<<", DOLARES: $"<<dolaresDB2<<", PLAZOS FIJOS: "<<cantidad_plazo_fijosBD<<endl;
            //sacamos del txt los valores de la cuenta 
            saldoDB = stoi(saldoDB2);// como paso string a int
            dolaresDB= stoi(dolaresDB2);
            pfBD= stoi(cantidad_plazo_fijosBD);
            
            usuario.saldo_en_cuenta = saldoDB;
            usuario.cantidad_dolares = dolaresDB; 

            sesion1=true;
        } else {
            cout << "*ERROR* la contrasenia esta mal puesta" << endl;
            sesion1=false;
            return 1;

        }
    } else {
        cout << "--USUARIO NO DETECTADO--" << endl;
        cout << "--CREANDO NUEVO USUARIO--" << endl;
        ofstream archivoRegistro("datos.txt", ios::app);
        if (archivoRegistro.is_open()) {
            archivoRegistro << nusuario << "," << contrasena << ",." << endl;
            archivoRegistro.close();
            sesion1 = true;
            usuario.nusuario = nusuario;
            usuario.contrasenia = contrasena;
            usuarios.push_back(usuario);
            
        } else {
            cout << "*ERROR* no se abrio el archivo para registrar el usuario." << endl;
        }
    }
    
    if(sesion1){
        while (var1 != 10){
            menu_principal(usuario);
            cin >> var1;
            switch (var1){
            case 1:
                ingresar_efectivo(usuario, var1,movimiento2,ingresos);
                break;
            case 2:
                retirar_efectivo(usuario, var1,movimiento2,retiros);
                break;
            case 3:
                manejar_dolares(usuario, var1,movimiento2,ingresos_dolares,ventas_dolares);
                break;
            case 4:
                retirar_dolares(usuario, var1,movimiento2,retiros_dolares);
                break;
            case 5:
                armar_plazo_fijo(usuario, var1);
                break;
            case 6:
                cancelar_plazo_fijo(usuario, var1);
                break;
            case 7:
                pedir_prestamo(usuario, var1,prestamos,movimiento2);
                break;
            case 8:
                ver_movimientos(usuario,ingresos,retiros,prestamos,ingresos_dolares,ventas_dolares,retiros_dolares);
                break;
            case 9:
                actualizar_datos(usuario, var1, nusuario);
                break;
            case 10:
                saldoDB2 = usuario.saldo_en_cuenta;
                cout << "Gracias por utilizar nuestro sistema " << usuario.nusuario << ", vuelva pronto." << endl;
                f5_datos(usuario, nusuario, pfBD);
                break;

            default:
                cout << "*ERROR* opcion invalida" << endl;
                break;
            }
        }
    }
    
}
