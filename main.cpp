/* Proyecto 1
Integrantes del grupo:
- Stiven Ortiz Noreña
- Carlos Santiago Rojas Calderón
- Javier Felipe Santana Diaz
*/

#include <iostream>
#include <fstream> // Incluimos la función para hacer uso de archivos.
#include <string.h>	// También incluimos la función de manejo de cadenas.

using namespace std;

int CantidadCarrito=0;

struct eCancion{ // Estructura para las canciones
	char Codigo[11]; // Con díez digitos podremos tener hasta 10.000.000.000 de canciones.
  	char Titulo[200]; // Las canciones usualmente tienen hasta 100 carácteres, pero añadimos 100 más por si es necesario.
	char Artista[100]; // Los artistas suelen tener nombre hasta de 25carácteres, para asegurar y si se necesita se incluye hasta 100.
  	char Letra[500][300]; //
  	char Duracion[8];
  	int Cont_L=1;
  	int Ventas=0;
    float Precio;
};

struct eCarrito{
    struct eCancion Cancion;
    int Cantidad=1;
}*Carrito;

struct eUsuarios{
	char Usuario[100];
  	char Correo[100];
  	char Contrasena[25];
  	int Compras;
    bool Admin=false;
}Usuario;


// Punto 1:

void InsertarCancion();
void ListarCanciones();
void ConsultarCancion();
void ModificarCancion();
void BorrarCancion();

//Punto 2:

void Registro();
bool InicioSesion();
void CerrarSesion();
void Admin();
void BuscarCanciones();
void CarritoDeCompras();
void Paginacion(struct eCancion Hayadas[], int Cantidad, int *Auxiliar, bool Pasa);
void AnadirCarrito(struct eCancion Hayadas[], int Cantidad, int seleccion);
void MostrarCarrito();

int main(){

    int opcion;
    do{
        system("CLS");
        cout<<"Bienvenido a "<<"NOMBRE DEL SIMULADOR"<<endl<<endl;
        cout<<"1.Iniciar Sesion"<<endl;
        cout<<"2.Registrarse"<<endl;
        cout<<"0.Salir"<<endl;
        cout<<"Ingrese una opcion: "; cin>>opcion;
        cout<<endl;

        switch (opcion){
            case 1:
                if(InicioSesion()==true){
                    Carrito=new eCarrito[CantidadCarrito];
                    Admin();
                }
                break;
            case 2:
                Registro();
                break;
            case 0:
                cout<<"Gracias, vuelva pronto!"<<endl;
                break;
            default:
                cout<<"La opcion ingresada es invalida"<<endl<<endl;
                system("PAUSE");
                break;
        }
    }while(opcion!=0);

    delete[] Carrito;

    return 0;
}

void InsertarCancion(){

  	struct eCancion rCancion;

  	system("CLS");
  	cin.ignore();

  	cout<<"Insertar Canciones"<<endl<<endl;
  	cout<<"Digite el codigo de la cancion: "<<endl;
  	cin.getline(rCancion.Codigo, sizeof(rCancion.Codigo));
  	cout<<"Digite el titulo de la cancion: "<<endl;
  	cin.getline(rCancion.Titulo, sizeof(rCancion.Titulo));
  	cout<<"Digite el artista"<<endl;
  	cin.getline(rCancion.Artista, sizeof(rCancion.Artista));
  	cout<<"Ingrese la letra de la canción renglon por renglon"<<endl;
  	cout<<"[Cuando finalice, haga un último renglón e ingrese \"-1\"]"<<endl<<endl;

  	for(int i=0; i<rCancion.Cont_L; i++){
    	char LetraTemp[300];
      	cin.getline(LetraTemp, sizeof(LetraTemp));

      	if(strcmp(LetraTemp, "-1")!=0){
        	strcpy(rCancion.Letra[i], LetraTemp);
          	rCancion.Cont_L++;
        }
    }
    cout<<endl;
  	cout<<"Ingrese la duracion de la cancion con el formato: 00:00 (minutos:segundos): "<<endl;
	cin.getline(rCancion.Duracion, sizeof(rCancion.Duracion));
  	cout<<"Ingrese el precio de la cancion"<<endl;
  	cin>>rCancion.Precio;

  	ofstream Archivo("Canciones.dat", ios::binary | ios::app);
  	if(Archivo){
    	Archivo.write((char *)&rCancion, sizeof(rCancion));
      	Archivo.close();
      	cout<<endl;
      	cout<<"¡Registro grabado correctamente!"<<endl<<endl;
      	system("PAUSE");
    }
}

void ListarCanciones(){

	struct eCancion rCancion;
  	system("CLS");
  	cin.ignore();

  	cout<<"Lista de Canciones"<<endl<<endl;
  	cout<<" Codigo"<<"\t\t Titulo\t\t\t\t Duracion   Artista\t\t\t\t\t Precio"<<endl;

  	ifstream Archivo("Canciones.dat", ios::binary);
  	if(Archivo){
      while(!Archivo.eof()){
        if(Archivo.read((char *)&rCancion, sizeof(rCancion))){
            cout<<" ";
            for(int j=0; j<10; j++){
                cout<<rCancion.Codigo[j];
            }
            cout<<"      ";
            int aux=32;
            if(strlen(rCancion.Titulo)>=30){
                for(int j=0; j<30; j++){
                    aux--;
                    cout<<rCancion.Titulo[j];
                }
                for(int j=0; j<aux; j++){
                    cout<<" ";
                }
            }else{
                cout<<rCancion.Titulo;
                aux=aux-strlen(rCancion.Titulo);
                for(int j=0; j<aux; j++){
                    cout<<" ";
                }
            }
            cout<<rCancion.Duracion;
            for(int j=0; j<6; j++){
                cout<<" ";
            }
            aux=45;
            if(strlen(rCancion.Artista)>41){
                for(int j=0; j<41; j++){
                    aux--;
                    cout<<rCancion.Artista[j];
                }
                cout<<"..";
                for(int j=0; j<aux-2; j++){
                    cout<<" ";
                }
            }else{
                cout<<rCancion.Artista;
                aux=aux-strlen(rCancion.Artista);
                for(int j=0; j<aux; j++){
                    cout<<" ";
                }
            }
            cout<<rCancion.Precio<<endl;
        }
      }
      Archivo.close();
    }
    cout<<endl;
    system("PAUSE");

}

void ConsultarCancion(){

	struct eCancion rCancion;
  	char Codigo[11];
  	system("CLS");
  	cin.ignore();

  	cout<<"Consultar Cancion"<<endl<<endl;
  	cout<<"Digite el codigo de la cancion a buscar: "<<endl;
  	cin.getline(Codigo, sizeof(Codigo));

  	ifstream Archivo("Canciones.dat", ios::binary);
  	if(Archivo){
    	bool Encontro=false;
      	while(!Archivo.eof() && !Encontro){
          	if(Archivo.read((char *)&rCancion, sizeof(rCancion))){
              	if(strcmp(rCancion.Codigo, Codigo)==0){
                 	Encontro=true;
                }
            }
        }
      	if(Encontro){

          	cout<<"Codigo\t\tTitulo\t\tDuracion\tArtista\t\tPrecio"<<endl;
          	cout<< rCancion.Codigo <<"\t"<< rCancion.Titulo <<"\t\t"<< rCancion.Duracion <<"\t\t"<< rCancion.Artista <<"\t\t"<< rCancion.Precio<<endl;
          	char respuesta;
          	cout<<"¿Desea ver la letra de la cancion? (S/N): "; cin>>respuesta;
          	cout<<endl;
        	if(respuesta == 'S' || respuesta == 's'){
              	for(int i=0; i<rCancion.Cont_L; i++){
                 	cout<<rCancion.Letra[i]<<endl;
                }
            }
            cout<<endl;
          	system("PAUSE");
          	Archivo.close();
        }else{
          	cout<<"¡Ese codigo de cancion no existe!"<<endl;
          	system("PAUSE");
          	Archivo.close();
        }

    }else{
    	cout<<"¡No se pudo abrir el archivo!"<<endl;
      	system("PAUSE");
    }

}

void ModificarCancion(){
	struct eCancion rCancion;
  	char Codigo[11];
  	system("CLS");
  	cin.ignore();

  	cout<<"Modificar Cancion"<<endl<<endl;
  	cout<<"Digite el codigo de la cancion a modificar:"<<endl;
  	cin.getline(Codigo, sizeof(Codigo));

  	fstream Archivo("Canciones.dat", ios::binary|ios::in|ios::out);
  	if(Archivo){
        bool Encontro=false;
        while(!Archivo.eof()&&!Encontro){
    	    if(Archivo.read((char *)&rCancion, sizeof(rCancion))){
        	    if(strcmp(rCancion.Codigo, Codigo)==0){
            	    Encontro=true;
                 }
            }
        }
        if(Encontro){
            cout<<"Codito\tTitulo\tDuracion\tArtista\tPrecio\t"<<endl;
            cout<<rCancion.Codigo<<"\t"<<rCancion.Titulo<<"\t"<<rCancion.Duracion<<"\t"<<rCancion.Artista<<"\t"<<rCancion.Precio<<endl;
            cout<<"Digite el nuevo titulo: "<<endl;
            cin.getline(rCancion.Titulo, sizeof(rCancion.Titulo));
            cout<<"Digite la nueva duracion con el formato: 00:00 (minutos:segundos): "<<endl;
            cin.getline(rCancion.Duracion, sizeof(rCancion.Duracion));
            cout<<"Digite el nuevo artista: "<<endl;
            cin.getline(rCancion.Artista, sizeof(rCancion.Artista));
            cout<<"Digite el nuevo precio: "<<endl;
            cin>>rCancion.Precio;

            char respuesta;
            cout<<"¿Desea modificar la letra de la cancion? ingerese (S/N)"<<endl;
            cin>>respuesta;
            if(respuesta=='s'|| respuesta=='S'){
                cout<<"Ingrese la letra de la canción renglon por renglon"<<endl;
  	            cout<<"[Cuando finalice, haga un último renglón e ingrese \"-1\"]"<<endl<<endl;

                for(int i=0; i<rCancion.Cont_L; i++){
                    char LetraTemp[300];
                    cin.getline(LetraTemp, sizeof(LetraTemp));

                    if(strcmp(LetraTemp, "-1")!=0){
                        strcpy(rCancion.Letra[i], LetraTemp);
                        rCancion.Cont_L++;
                    }
                }
            }

            Archivo.seekg((int)(-1*sizeof(rCancion)), ios::cur);
            Archivo.write((char *)&rCancion, sizeof(rCancion));
            cout<<"¡Registro modificado correctamente!"<<endl<<endl;
            system("PAUSE");
        }else{
            cout<<"¡Ese codigo de cancion no existe!"<<endl<<endl;
            Archivo.close();
            system("PAUSE");
        }
    }else{
        cout<<"¡No se pudo abrir el archivo!"<<endl<<endl;
        system("PAUSE");
    }
}

void BorrarCancion(){
    struct eCancion rCancion;
    char Codigo[11];
    system("CLS");
    cin.ignore();

    cout<<"Borrar cancion"<<endl<<endl;
    cout<<"Digite el codigo de la cancion a borrar: "<<endl;
    cin.getline(Codigo, sizeof(Codigo));
    ifstream Archivo1("Canciones.dat", ios::binary);
    if(Archivo1){
        bool Encontro=false;
        while (!Archivo1.eof() && !Encontro){
            if(Archivo1.read((char *)&rCancion, sizeof(rCancion))){
                if(strcmp(rCancion.Codigo, Codigo)==0){
                    Encontro=true;
                }
            }
        }
        if(Encontro){
            ofstream Archivo2("CancionesTemp.dat", ios::binary);
            Archivo1.seekg(0, ios::beg);
            while (!Archivo1.eof()){
                if(Archivo1.read((char *)&rCancion, sizeof(rCancion))){
                    if(strcmp(rCancion.Codigo, Codigo)!=0){
                        Archivo2.write((char *)&rCancion, sizeof(rCancion));
                    }
                }
            }
            Archivo1.close();
            Archivo2.close();
            remove("Canciones.dat");
            rename("CancionesTemp.dat", "Canciones.dat");
            cout<<"¡Canción borrada exitosamente!"<<endl<<endl;
            system("PAUSE");
        }else{
            Archivo1.close();
            cout<<"¡Codigo cancion inexistente!"<<endl<<endl;
            system("PAUSE");
        }
    }else{
        cout<<"¡No se pudo abrir el archivo!"<<endl<<endl;
        system("PAUSE");
    }
}

void Registro(){
    struct eUsuarios rUsuarios;

    system("CLS");
    cin.ignore();

    cout<<"Ingrese un nombre de usuario: "<<endl;
    cin.getline(rUsuarios.Usuario, sizeof(rUsuarios.Usuario));
    cout<<"Ingrese un correo electronico: "<<endl;
    cin.getline(rUsuarios.Correo, sizeof(rUsuarios.Correo));
    cout<<"Ingrese una contrasena: "<<endl;
    cin.getline(rUsuarios.Contrasena, sizeof(rUsuarios.Contrasena));
    rUsuarios.Admin=true;

    ofstream Archivo("Usuarios.dat", ios::binary | ios::app);
  	if(Archivo){
    	Archivo.write((char *)&rUsuarios, sizeof(rUsuarios));
      	Archivo.close();
      	cout<<"¡Registro exitoso!"<<endl<<endl;
      	system("PAUSE");
      	system("CLS");
    }
}

bool InicioSesion(){
    char identificador[100];
    char contrasena[25];

    system("CLS");
    cin.ignore();

    cout<<"Iniciar Sesion"<<endl<<endl;
    cout<<"Ingrese su correo o usuario:"<<endl;;
    cin.getline(identificador, sizeof(identificador));
    cout<<endl;
    cout<<"Ingrese su contrasena:"<<endl;
    cin.getline(contrasena, sizeof(contrasena));

    ifstream Archivo("Usuarios.dat", ios::binary);
    if(Archivo){
        bool identificador_b=false;
            while(!Archivo.eof()&&!identificador_b){
                if(Archivo.read((char *)&Usuario, sizeof(Usuario))){
                    if((strcmp(Usuario.Correo, identificador)==0) || (strcmp(Usuario.Usuario, identificador)==0)){
                        identificador_b=true;
                        if(strcmp(Usuario.Contrasena, contrasena)==0){
                            cout<<endl;
                            cout<<"¡Ha iniciado sesion correctamente!"<<endl<<endl;
                            system("PAUSE");
                            system("CLS");
                            return true;
                        }
                    }
                }
            }
            if(identificador_b){
                cout<<"¡Contraseña incorrecta!"<<endl<<endl;
                system("PAUSE");
                return false;
            }else{
                cout<<"¡El usuario o correo ingresado son inexistentes!"<<endl<<endl;
                system("PAUSE");
                system("CLS");
                return false;
            }
    }else{
        cout<<"¡No se ha podido abrir el archivo!"<<endl<<endl;
        system("PAUSE");
        system("CLS");
        return false;
    }

}

void BuscarCanciones(){
    struct eCancion rCancion;
    system("CLS");
    cin.ignore();
    char palabra_frase_clave[150];

    cout<<"---Busqueda de Canciones----"<<endl<<endl;
    cout<<"Ingrese la palabra o frase clave (MAX 150 caracteres): "<<endl;
    cin.getline(palabra_frase_clave, sizeof(palabra_frase_clave));

    int Palabras=0;
    char Copia[150];
    char *Separador;

    strlwr(palabra_frase_clave);
    strcpy(Copia, palabra_frase_clave);

    Separador=strtok(Copia, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
    while (Separador!=NULL){
        Palabras++;
        Separador=strtok(NULL, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
    }

    char **ArregloPalabras;
    ArregloPalabras=new char*[Palabras];

    Palabras=0;

    strcpy(Copia, palabra_frase_clave);

    Separador=strtok(Copia, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
    while(Separador!=NULL){
        ArregloPalabras[Palabras]=new char[strlen(Separador)];
        strcpy(ArregloPalabras[Palabras], Separador);
        Palabras++;
        Separador=strtok(NULL, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
    }

    ifstream Archivo("Canciones.dat", ios::binary);
    if(Archivo){
        int CancionesConcuerdan=0;
        struct eCancion *CancionesEncontradas;
        CancionesEncontradas=new eCancion[CancionesConcuerdan];
        while(!Archivo.eof()){
            if(Archivo.read((char *)&rCancion, sizeof(rCancion))){
                char frase[300];
                bool acierta=false;
                char **ArregloPalabrasFrase;
                int PalabrasFrase=0;

                strcpy(frase, rCancion.Titulo);
                strlwr(frase);
                strcpy(Copia, frase);
                Separador=strtok(Copia, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                while (Separador!=NULL){
                    if(strlen(Separador)>2){
                        PalabrasFrase=PalabrasFrase+1;
                    }
                    Separador=strtok(NULL, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                }

                ArregloPalabrasFrase=new char*[PalabrasFrase];
                PalabrasFrase=0;
                strcpy(Copia, frase);

                Separador=strtok(Copia, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                while (Separador!=NULL){
                    if(strlen(Separador)>2){
                        PalabrasFrase=PalabrasFrase+1;
                        ArregloPalabrasFrase[PalabrasFrase-1]=new char[strlen(Separador)];
                        strcpy(ArregloPalabrasFrase[PalabrasFrase-1], Separador);
                    }
                    Separador=strtok(NULL, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                }
                for(int i=0; i<Palabras; i++){
                    if(!acierta){
                        for(int j=0; j<PalabrasFrase; j++){
                            if(strcmp(ArregloPalabrasFrase[j], ArregloPalabras[i])==0 && !acierta){
                                acierta=true;
                            }
                        }
                    }
                }
                delete[] ArregloPalabrasFrase;

                if(!acierta){
                    strcpy(frase, rCancion.Artista);
                    strlwr(frase);
                    strcpy(Copia, frase);
                    Separador=strtok(Copia, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                    while (Separador!=NULL){
                        if(strlen(Separador)>2){
                            PalabrasFrase=PalabrasFrase+1;
                        }
                        Separador=strtok(NULL, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                    }

                    ArregloPalabrasFrase=new char*[PalabrasFrase];
                    PalabrasFrase=0;
                    strcpy(Copia, frase);

                    Separador=strtok(Copia, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                    while (Separador!=NULL){
                        if(strlen(Separador)>2){
                            PalabrasFrase=PalabrasFrase+1;
                            ArregloPalabrasFrase[PalabrasFrase-1]=new char[strlen(Separador)];
                            strcpy(ArregloPalabrasFrase[PalabrasFrase-1], Separador);
                        }
                        Separador=strtok(NULL, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                    }
                    for(int i=0; i<Palabras; i++){
                        if(!acierta){
                            for(int j=0; j<PalabrasFrase; j++){
                                if(strcmp(ArregloPalabrasFrase[j], ArregloPalabras[i])==0 && !acierta){
                                    acierta=true;
                                }
                            }
                        }
                    }
                    delete[] ArregloPalabrasFrase;
                }

                if(!acierta){
                    strcpy(frase, rCancion.Codigo);
                    for(int l=0; l<Palabras; l++){
                        if(strcmp(frase, ArregloPalabras[l])==0){
                            acierta=true;
                        }
                    }
                }

                if(!acierta){
                    for(int a=0; a<rCancion.Cont_L; a++){
                        if(!acierta){
                            int PalabrasFrase=0;
                            strcpy(frase, rCancion.Letra[a]);
                            strlwr(frase);
                            strcpy(Copia, frase);

                            Separador=strtok(Copia, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                            while (Separador!=NULL){
                                PalabrasFrase=PalabrasFrase+1;
                                Separador=strtok(NULL, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                            }

                            ArregloPalabrasFrase=new char*[PalabrasFrase];
                            PalabrasFrase=0;

                            strcpy(Copia, frase);

                            Separador=strtok(Copia, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                            while (Separador!=NULL){
                                PalabrasFrase=PalabrasFrase+1;
                                ArregloPalabrasFrase[PalabrasFrase-1]=new char[strlen(Separador)];
                                strcpy(ArregloPalabrasFrase[PalabrasFrase-1], Separador);
                                Separador=strtok(NULL, " ,.;:!¡'¿?{}()$%/\\#-─~*+");
                            }
                            for(int i=0; i<Palabras; i++){
                                if(!acierta){
                                    for(int j=0; j<PalabrasFrase; j++){
                                        if(strcmp(ArregloPalabrasFrase[j], ArregloPalabras[i])==0 && !acierta && (i+1)!=Palabras && (i+2)!=Palabras && (j+1)!=PalabrasFrase && (j+2)!=PalabrasFrase){
                                            if(strcmp(ArregloPalabrasFrase[j+1], ArregloPalabras[i+1])==0){
                                                if(strcmp(ArregloPalabrasFrase[j+2], ArregloPalabras[i+2])==0){
                                                    acierta=true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    delete[] ArregloPalabrasFrase;
                }

                if(acierta){
                    CancionesConcuerdan++;
                    struct eCancion *TempCanciones;
                    TempCanciones = new eCancion[CancionesConcuerdan];

                    for(int i=0; i<CancionesConcuerdan-1; i++){
                        TempCanciones[i]=CancionesEncontradas[i];
                    }
                    delete[] CancionesEncontradas;

                    TempCanciones[CancionesConcuerdan-1]=rCancion;

                    CancionesEncontradas=new eCancion[CancionesConcuerdan];

                    for(int j=0; j<CancionesConcuerdan; j++){
                        CancionesEncontradas[j]=TempCanciones[j];
                    }
                    delete[] TempCanciones;
                }
            }
        }

        for(int i=0; i<Palabras; i++){
            delete[] ArregloPalabras[i];
        }
        delete[] ArregloPalabras;

        if(CancionesConcuerdan>0){
            if(CancionesConcuerdan<=10){
                int seleccion;
                do{
                    system("CLS");
                    cout<<"Se han encontado "<<CancionesConcuerdan<<" canciones:"<<endl<<endl;
                    cout<<"Indice Codigo"<<"\t\t Titulo\t\t\t\t Duracion   Artista\t\t\t\t Precio"<<endl;
                    for(int i=0; i<CancionesConcuerdan; i++){

                        cout<<"  ["<<i<<"]  ";
                        for(int j=0; j<10; j++){
                            cout<<CancionesEncontradas[i].Codigo[j];
                        }
                        cout<<"        ";
                        int aux=32;
                        if(strlen(CancionesEncontradas[i].Titulo)>=30){
                            for(int j=0; j<30; j++){
                                aux--;
                                cout<<CancionesEncontradas[i].Titulo[j];
                            }
                            for(int j=0; j<aux; j++){
                                cout<<" ";
                            }
                        }else{
                            cout<<CancionesEncontradas[i].Titulo;
                            aux=aux-strlen(CancionesEncontradas[i].Titulo);
                            for(int j=0; j<aux; j++){
                                cout<<" ";
                            }
                        }
                        cout<<CancionesEncontradas[i].Duracion;
                        for(int j=0; j<6; j++){
                            cout<<" ";
                        }
                        aux=37;
                        if(strlen(CancionesEncontradas[i].Artista)>34){
                            for(int j=0; j<34; j++){
                                aux--;
                                cout<<CancionesEncontradas[i].Artista[j];
                            }
                            cout<<"..";
                            for(int j=0; j<aux-2; j++){
                                cout<<" ";
                            }
                        }else{
                            cout<<CancionesEncontradas[i].Artista;
                            aux=aux-strlen(CancionesEncontradas[i].Artista);
                            for(int j=0; j<aux; j++){
                                cout<<" ";
                            }
                        }
                        cout<<CancionesEncontradas[i].Precio<<endl;
                    }
                    cout<<"\n-Si desea agregar una o mas canciones al carrito de compras ingrese el indice uno por uno."<<endl;
                    cout<<"-Si desea salir digite -1;"<<endl<<endl;
                    cout<<"Digite aqui: "; cin>>seleccion;
                    cout<<endl;
                    if(seleccion>=0 && seleccion<=10){
                        AnadirCarrito(CancionesEncontradas, CancionesConcuerdan, seleccion);
                    }
                }while(seleccion!=-1);
                seleccion=0;
            }else{
                int seleccion=-2, Aux=1;
                do{
                    if(seleccion==-2){
                        Paginacion(CancionesEncontradas, CancionesConcuerdan, &Aux, false);
                    }
                    cout<<"\n-Si desea agregar una o mas canciones al carrito de compras ingrese el indice uno por uno."<<endl;
                    cout<<"-Si desea seguir paginando ingrese -2"<<endl;
                    cout<<"-Si desea salir digite -1;"<<endl<<endl;
                    cout<<"Digite aqui: "; cin>>seleccion;
                    cout<<endl;
                    if(seleccion>-1){
                        AnadirCarrito(CancionesEncontradas, CancionesConcuerdan, seleccion);
                        Paginacion(CancionesEncontradas, CancionesConcuerdan, &Aux, true);
                    }
                }while(seleccion!=-1);
                seleccion=-2; Aux=1;
            }
        }else{
            system("CLS");
            cout<<"No se han encontrado canciones que coincidan con la frase o la palabra clave"<<endl<<endl;
            system("PAUSE");
            cout<<endl;
        }
        if(CancionesConcuerdan>0){
        delete[] CancionesEncontradas;
        CancionesConcuerdan=0;
        }
        Archivo.close();
        cout<<"Saliendo..."<<endl<<endl;
        system("PAUSE");
    }else{
        cout<<"¡No se pudo abrir el archivo!"<<endl<<endl;
        system("PAUSE");
    }
    strcpy(Copia, "x");
    strcpy(palabra_frase_clave, "x");
}

void Admin(){
    if(Usuario.Admin){
        int opcion;
        do{
            system("CLS");
            cout<<"NOMBRE DEL SIMULADOR"<<endl<<endl;
            cout<<"Bienvenido administrador "<<Usuario.Usuario<<"!"<<endl;
            cout<<"---Menu---"<<endl<<endl;
            cout<<"1. Insertar cancion\n2. Modificar cancion\n3. Consultar cancion\n4. Eliminar Cancion\n5. Listar canciones\n6. Buscar canciones\n7. Mostrar carrito\n0. Cerrar sesion"<<endl<<endl;
            cout<<"Ingrese su opicion: "; cin>>opcion;
            cout<<endl;

            switch(opcion){
                case 1:
                    InsertarCancion();
                    break;
                case 2:
                    ModificarCancion();
                    break;
                case 3:
                    ConsultarCancion();
                    break;
                case 4:
                    BorrarCancion();
                    break;
                case 5:
                    ListarCanciones();
                    break;
                case 6:
                    BuscarCanciones();
                    break;
                case 7:
                    MostrarCarrito();
                    break;
                case 0:
                    cout<<"Cerrando sesion..."<<endl<<endl;
                    system("PAUSE");
                    CerrarSesion();
                    break;
                default:
                    cout<<"La opcion ingresada es invalida"<<endl<<endl;
                    system("PAUSE");
                    break;
            }
        }while(opcion!=0);
    }else{
        int opcion;
        do{
            cout<<"NOMBRE DEL SIMULADOR"<<endl<<endl;
            cout<<"Bienvenido usuario "<<Usuario.Usuario<<"!"<<endl;
            cout<<"---Menu---"<<endl<<endl;
            cout<<"\n1. Consultar cancion\n2. Buscar canciones\n3. Listar canciones\n0. Salir"<<endl<<endl;
            cout<<"Ingrese su opicion: "; cin>>opcion;

            switch(opcion){
                case 1:
                    ConsultarCancion();
                    break;
                case 2:
                    BuscarCanciones();
                    break;
                case 3:
                    ListarCanciones();
                    break;
                case 0:
                    cout<<"Cerrando sesion..."<<endl;
                    system("PAUSE");
                    cout<<endl;
                    CerrarSesion();
                    break;
                default:
                    cout<<"La opcion ingresada es invalida"<<endl;
                    break;
            }
        }while(opcion!=0);
    }
}

void Paginacion(struct eCancion Hayadas[], int Cantidad, int *Auxiliar, bool Pasa){
    float Verificacion;
    int PaginasTotales, aux, contador=0;

    Verificacion=Cantidad;
    Verificacion=Verificacion/10;
    PaginasTotales=Cantidad/10;
    Verificacion=Verificacion-PaginasTotales;
    if(Verificacion>0){
        PaginasTotales=(Cantidad/10)+1;
    }else{
        PaginasTotales=Cantidad/10;
    }

    int Pagina=*Auxiliar;
    while(Pagina!=0){
        system("CLS");
        cout<<"Se han encontado "<<Cantidad<<" canciones:"<<endl<<endl;
        cout<<"Indice Codigo"<<"\t\t Titulo\t\t\t\t Duracion   Artista\t\t\t\t Precio"<<endl;
        if(Pagina!=PaginasTotales){
            for(int i=(Pagina*10)-10; i<Pagina*10; i++){
                cout<<"  ["<<i<<"]  ";
                for(int j=0; j<10; j++){
                    cout<<Hayadas[i].Codigo[j];
                }
                cout<<"        ";
                int aux=32;
                if(strlen(Hayadas[i].Titulo)>=30){
                    for(int j=0; j<30; j++){
                        aux--;
                        cout<<Hayadas[i].Titulo[j];
                    }
                    for(int j=0; j<aux; j++){
                        cout<<" ";
                    }
                }else{
                    cout<<Hayadas[i].Titulo;
                    aux=aux-strlen(Hayadas[i].Titulo);
                    for(int j=0; j<aux; j++){
                        cout<<" ";
                    }
                }
                cout<<Hayadas[i].Duracion;
                for(int j=0; j<6; j++){
                    cout<<" ";
                }
                aux=37;
                if(strlen(Hayadas[i].Artista)>34){
                    for(int j=0; j<34; j++){
                        aux--;
                        cout<<Hayadas[i].Artista[j];
                    }
                    cout<<"..";
                    for(int j=0; j<aux-2; j++){
                        cout<<" ";
                    }
                }else{
                    cout<<Hayadas[i].Artista;
                    aux=aux-strlen(Hayadas[i].Artista);
                    for(int j=0; j<aux; j++){
                        cout<<" ";
                    }
                }
                cout<<Hayadas[i].Precio<<endl;
            }
        }else{
            for(int i=(Pagina*10)-10; i<Cantidad; i++){
                cout<<"  ["<<i<<"]  ";
                for(int j=0; j<10; j++){
                    cout<<Hayadas[i].Codigo[j];
                }
                cout<<"        ";
                int aux=32;
                if(strlen(Hayadas[i].Titulo)>=30){
                    for(int j=0; j<30; j++){
                        aux--;
                        cout<<Hayadas[i].Titulo[j];
                    }
                    for(int j=0; j<aux; j++){
                        cout<<" ";
                    }
                }else{
                    cout<<Hayadas[i].Titulo;
                    aux=aux-strlen(Hayadas[i].Titulo);
                    for(int j=0; j<aux; j++){
                        cout<<" ";
                    }
                }
                cout<<Hayadas[i].Duracion;
                for(int j=0; j<6; j++){
                    cout<<" ";
                }
                aux=37;
                if(strlen(Hayadas[i].Artista)>34){
                    for(int j=0; j<34; j++){
                        aux--;
                        cout<<Hayadas[i].Artista[j];
                    }
                    cout<<"..";
                    for(int j=0; j<aux-2; j++){
                        cout<<" ";
                    }
                }else{
                    cout<<Hayadas[i].Artista;
                    aux=aux-strlen(Hayadas[i].Artista);
                    for(int j=0; j<aux; j++){
                        cout<<" ";
                    }
                }
                cout<<Hayadas[i].Precio<<endl;
            }
        }
        *Auxiliar=Pagina;
        cout<<"\nSe encuentra en la pagina "<<Pagina<<" de "<< PaginasTotales <<endl;
        if(!Pasa){
            cout<<"-Si desea quedarse en la pagina actual ingrese 0"<<endl;
            cout<<"-Si desea ver otra pagina ingrese el numero de la pagina que desea ver"<<endl<<endl;
            cout<<"Ingrese su respuesta aqui: "; cin>>Pagina;
            if(Pagina>PaginasTotales || Pagina<=-1){
                system("CLS");
                cout<<"La pagina ingresada no existe!"<<endl;
                system("PAUSE");
                Pagina=aux;
                if(contador==0){
                    Pagina=*Auxiliar;
                }
            }else{
                contador++;
                aux=Pagina;
            }
        }else{
            Pagina=0;
        }
    }
    if(Pagina==0){
        Pagina=*Auxiliar;
    }
}

void AnadirCarrito(struct eCancion Hayadas[], int Cantidad, int seleccion){
    system("CLS");

    bool bandera=false;

    for(int i=0; i<CantidadCarrito; i++){
        if(strcmp(Carrito[i].Cancion.Codigo, Hayadas[seleccion].Codigo)==0 && !bandera){
            Carrito[i].Cantidad=Carrito[i].Cantidad+1;
            cout<<"La cancion ["<< Hayadas[seleccion].Titulo <<" - "<< Hayadas[seleccion].Artista<<"] se ha anadida nuevamente al carrito de compras con exito"<<endl<<endl;
            bandera=true;
        }
    }

    if(!bandera){
        CantidadCarrito++;
        struct eCarrito *temp;
        temp=new eCarrito[CantidadCarrito];
        for(int i=0; i<CantidadCarrito-1; i++){
            temp[i]=Carrito[i];
        }
        delete[] Carrito;
        temp[CantidadCarrito-1].Cancion=Hayadas[seleccion];
        Carrito=new eCarrito[CantidadCarrito];
        for(int i=0; i<CantidadCarrito; i++){
            Carrito[i].Cancion=temp[i].Cancion;
        }
        delete[] temp;
        cout<<"La cancion ["<< Hayadas[seleccion].Titulo <<" - "<< Hayadas[seleccion].Artista<<"] ha sido anadida al carrito de compras con exito"<<endl<<endl;
    }
    system("PAUSE");
    system("CLS");
}

void CerrarSesion(){
    struct eUsuarios rUsuario;

    fstream Archivo("Usuarios.dat", ios::binary|ios::in|ios::out);
  	if(Archivo){
        bool Encontro=false;
        while(!Archivo.eof()&&!Encontro){
    	    if(Archivo.read((char *)&rUsuario, sizeof(rUsuario))){
        	    if(strcmp(rUsuario.Correo, Usuario.Correo)==0){
            	    Encontro=true;
                 }
            }
        }
        if(Encontro){

            strcpy(rUsuario.Usuario, Usuario.Usuario);
            strcpy(rUsuario.Correo, Usuario.Correo);
            strcpy(rUsuario.Contrasena, Usuario.Contrasena);
            rUsuario.Compras=Usuario.Compras;

            Archivo.seekg((int)(-1*sizeof(rUsuario)), ios::cur);
            Archivo.write((char *)&rUsuario, sizeof(rUsuario));
        }else{
            Archivo.close();
        }
  	}

    strcpy(Usuario.Correo, "NA");
    strcpy(Usuario.Contrasena, "NA");
    strcpy(Usuario.Usuario, "NA");
    Usuario.Admin=false;
    Usuario.Compras=0;
    cout<<"\nSe ha cerrado sesión correctamente"<<endl<<endl;
    system("PAUSE");
    system("CLS");
}

void MostrarCarrito(){
    system("CLS");

    float PrecioTotal=0, PrecioUnidadYCantidad;

    cout<<"--Mostrando Carrito--"<<endl<<endl;
    cout<<"Indice\tCodigo\t\tTitulo\t\t\tDuracion\tArtista\t\tPrecio c/u\tCantidad\tPrecio"<<endl;

    for(int i=0; i<CantidadCarrito; i++){
        cout<<"   "<<i<<"\t";

        int aux=24;
        for(int j=0; j<10; j++){
            cout<<Carrito[i].Cancion.Codigo[j];
        }
        cout<<"      ";
        if(strlen(Carrito[i].Cancion.Titulo)>=20){
            for(int j=0; j<20; j++){
                aux--;
                cout<<Carrito[i].Cancion.Titulo[j];
            }
            for(int j=0; j<aux; j++){
                cout<<" ";
            }
        }else{
            cout<<Carrito[i].Cancion.Titulo;
            aux=aux-strlen(Carrito[i].Cancion.Titulo);
            for(int j=0; j<aux; j++){
                cout<<" ";
            }
        }
        cout<<Carrito[i].Cancion.Duracion;
        for(int j=0; j<11; j++){
            cout<<" ";
        }
        aux=16;
        if(strlen(Carrito[i].Cancion.Artista)>=14){
            for(int j=0; j<14; j++){
                aux--;
                cout<<Carrito[i].Cancion.Artista[j];
            }
            for(int j=0; j<aux; j++){
                cout<<" ";
            }
        }else{
            cout<<Carrito[i].Cancion.Artista;
            aux=aux-strlen(Carrito[i].Cancion.Artista);
            for(int j=0; j<aux; j++){
                cout<<" ";
            }
        }
        cout<<Carrito[i].Cancion.Precio;
        aux=0;
        int numaux2=Carrito[i].Cancion.Precio;
        while(numaux2!=0){
            numaux2=numaux2/10;
            aux++;
        }
        aux=16-aux;
        for(int j=0; j<aux; j++){
            cout<<" ";
        }
        cout<<Carrito[i].Cantidad;
        aux=0;
        numaux2=Carrito[i].Cantidad;
        while(numaux2!=0){
            numaux2=numaux2/10;
            aux++;
        }
        aux=16-aux;
        for(int j=0; j<aux; j++){
            cout<<" ";
        }

        PrecioUnidadYCantidad=Carrito[i].Cancion.Precio*Carrito[i].Cantidad;

        cout<<PrecioUnidadYCantidad<<endl;

        PrecioTotal=PrecioTotal+PrecioUnidadYCantidad;
    }
    cout<<"Precio Total: "<<PrecioTotal<<endl<<endl;
    system("PAUSE");
    cout<<endl;
    cout<<"Saliendo..."<<endl<<endl;
    system("PAUSE");
    system("CLS");
}
