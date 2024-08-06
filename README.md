# Tower_Defense

Repositorio del proyecto de fin de grado de Iván Mata

## Ejecutable

El juego en sí no puede ser subido a GitHub porque excede los limites de capacidad, pero se puede descargar su .zip del ejecutable Windows siguiendo este enlace: https://drive.google.com/drive/folders/1JQDNkFHGQ1NCCfLh0mA_HdDSgwylnThk?usp=sharing

## Preparación del entorno y abrir el proyecto

### Descargar las herramientas fundamentales y el proyecto
NOTA: Este tutorial de instalación es para Windows. Se requieren unos 50GB para el motor de juego, 10GB para su IDE, y 15GB para el proyecto.




#### Unreal Engine (Motor de juego)
Primero de todo, si no se dispone del iniciador de Epic Games, descargarlo usando el siguiente enlace: https://store.epicgames.com/es-ES/download

Después, se debe abrir el lanzador y seleccionar en la pestaña de Unreal Engine obtener e instalar la versión 5.0.3, ya que es sobre la que se ha desarrollado el trabajo. Este proceso puede tardar varios minutos.
![image](https://github.com/user-attachments/assets/01d4b7ad-3101-43ff-b632-7c585ce67f0d)

#### Virtual Studio Code y sus componentes (IDE)

##### .NET
Instalar .NET Core 3.1.24 usando el siguiente enlace (se debe bajar algo en la página ya que la primera versión que aparece no es la que nos interesa): https://dotnet.microsoft.com/es-es/download/dotnet/3.1 (se trata de una de las versiones sin vulnerabilidades de seguridad). 

##### Visual Studio
A continuación, instalar Visual Studio Community 2019 usando el siguiente enlace (a día de hoy el instalador no existe en la web oficial pero se puede adquirir en este repositorio drive): https://drive.google.com/drive/folders/1hQPwlHlzYXTOA2YRovmYxRpcE7TqGv-3?usp=sharing

Durante su instalación, marcar las siguientes opciones recuadradas en rojo que no están elegidas por defecto (su instalación puede durar varios minutos): ![image](https://github.com/user-attachments/assets/adebf3f5-53fe-42e2-8e77-9461c0e4d8d2)


Tras la instalación, abrir Visual Studio y registrarse con una cuenta de Microsoft.

##### Visual Studio Code (VSCode)

Finalmente, descargar VSCode usando el siguiente enlace: https://code.visualstudio.com/download (aceptar la licencia y elegir las opciones por defecto propuestas en el instalador)


### Abrir el proyecto

Descargar el zip del proyecto usando los siguientes botones del repositorio: ![image](https://github.com/user-attachments/assets/2444786a-bb66-4946-aa3d-de8c7107855b)



Tras esto, abre Unreal Engine 5.0.3. Al hacer esto, se debería haber creado un directorio llamado "Unreal Projects" en C:\Users\[TuUsuario]\Documents. Extrae los contenidos del zip del proyecto en ese directorio nuevo.

Reinicia Unreal Engine y ahora debería figurar el proyecto en la siguiente pantalla de bienvenida preparado para ser abierto: ![image](https://github.com/user-attachments/assets/2e69a358-ed2c-4a1d-a7b7-cb050ea95f38)  Alternativamente, se puede hacer click sobre el ejecutable del proyecto. En cualquier caso, se pedirá reconstruir los modulos seguramente: acepta y tras un par de minutos el proyecto se abrirá (esta espera solo ocurre la primera vez que se abre). Se puede verificar que en efecto se está cargando el proyecto aunque no lo parezca abriendo el administrador de tareas y verificando que los compiladores c++ de Microsoft están usando gran parte de la memoria del sistema durante esta espera.


### Navegar por el proyecto

#### Editores y aspectos visuales

Haciendo click en "Content Drawer" en la esquina inferior izquierda abre el sistema de carpetas donde se almacenan todos los recursos del juego (incluyendo las clases)

![image](https://github.com/user-attachments/assets/e9c4cfb5-8c46-44ab-8673-6dc47d92183c)

También te puedes mover por la escena usando "wasd" mientras se mantiene pulsado el click derecho del ratón.
En el directorio "niveles" se encuentran archivos "mapa" en los que pinchando en ellos te puedes cambiar entre los distintos ambientes diseñados e integrados en el juego.

#### Editor de código

Se puede ir a Tools > Abrir VSCode para abrir el IDE del proyecto y ver las clases c++ definidas en código:

![image](https://github.com/user-attachments/assets/aec8a406-0150-40c1-a5c9-15125f2a4e52)

Es posible que aparezca otro IDE que no sea VSCode en esa opción como el IDE a abrir, pero se puede editar siguiendo los siguientes pasos:

Pincha en "editar > preferencias del editor"

![image](https://github.com/user-attachments/assets/8f9aed66-8c40-4ff9-bc3f-87233443fa74)

En la nueva ventana abierta, bajo "General > Código fuente" se encuentra la opción para elegir el IDE adecuado.

![image](https://github.com/user-attachments/assets/0d56f2dc-8132-4e27-9d52-481d4bfd8d2f)


Dentro de VSCode, se puede ver el contenido en sí pinchando en los directorios "Source > Tower_Defense"

![image](https://github.com/user-attachments/assets/0a1ff5f6-0731-4098-a198-6b765237a3f5)






