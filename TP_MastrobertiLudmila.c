#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras de datos - Definen los "moldes" para nuestros datos

// Estructura para almacenar información de productos
typedef struct {
    int idProducto;           // Identificador único del producto
    char nombreProducto[21];  // Nombre del producto (máximo 20 caracteres + '\0')
    float precioProducto;     // Precio unitario del producto
} Producto;

// Estructura para almacenar información de ciudades
typedef struct {
    int codigoCiudad;        // Código único de la ciudad
    char nombreCiudad[21];   // Nombre de la ciudad (máximo 20 caracteres + '\0')
} Ciudad;

// Estructura para almacenar información de ventas
typedef struct {
    int numeroFactura;       // Número de factura de la venta
    char fechaVenta[9];      // Fecha en formato DDMMAAAA (8 caracteres + '\0')
    int idProducto;          // ID del producto vendido (referencia a Producto)
    int codigoCiudad;        // Código de la ciudad donde se vendió (referencia a Ciudad)
    float cantidadVendida;   // Cantidad de unidades vendidas
} Venta;

void mostrarMenu();                           // Muestra el menú principal
void borrarArchivos();                        // Borra/limpia los archivos de datos
void cargarProductos();                       // Permite cargar nuevos productos
void cargarCiudades();                        // Permite cargar nuevas ciudades
void cargarVentas();                         // Permite registrar nuevas ventas
void listadoPorCiudadYProducto();            // Muestra ventas agrupadas por ciudad y producto
void listadoPorProductoYCiudad();            // Muestra ventas agrupadas por producto y ciudad
void mostrarEstadisticas();                  // Muestra estadísticas de ventas
int buscarProducto(int idProducto, Producto *productoInfo);  // Busca un producto por ID
int buscarCiudad(int codigoCiudad, Ciudad *ciudadInfo);      // Busca una ciudad por código
void pausar();                               // Pausa la ejecución hasta que se presione ENTER

// Función principal - Punto de entrada del programa
int main() {
    int opcionUsuario;  // Variable para la opción elegida por el usuario

    // Bucle principal, se ejecuta hasta que el usuario elija salir
    do {
        mostrarMenu();                    // Mostrar las opciones disponibles
        printf("Elija una opcion: ");
        scanf("%d", &opcionUsuario);      // Leer la opción del usuario

        // Switch para ejecutar lo elegido
        switch(opcionUsuario) {
            case 1:
                borrarArchivos();         //  1: Borrar archivos
                break;
            case 2:
                cargarProductos();        // 2: Cargar productos
                break;
            case 3:
                cargarCiudades();         //  3: Cargar ciudades
                break;
            case 4:
                cargarVentas();           // 4: Cargar ventas
                break;
            case 5:
                listadoPorCiudadYProducto();  // 5: Listado por ciudad y producto
                break;
            case 6:
                listadoPorProductoYCiudad();  //  6: Listado por producto y ciudad
                break;
            case 7:
                mostrarEstadisticas();    //7: Mostrar estadísticas
                break;
            case 8:
                break;                    //  8: Salir (termina el bucle)
            default:
                printf("Opcion invalida.\n");  // Mensaje para opciones no válidas
        }

        // Si no eligió salir (opción 8), pausar para que el usuario vea el resultado
        if(opcionUsuario != 8) {
            pausar();
        }

    } while(opcionUsuario != 8);  // Continuar mientras no elija salir

    return 0;  // Terminar el programa exitosamente
}

//  mostrar el menú de opciones
void mostrarMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Borrar Archivos\n");              // Elimina todos los datos
    printf("2. Cargar Productos\n");             // Agregar nuevos productos
    printf("3. Cargar Ciudades\n");              // Agregar nuevas ciudades
    printf("4. Cargar Ventas\n");                // Registrar nuevas ventas
    printf("5. Listado x Ciudad y Producto\n");  // Reporte agrupado por ciudad
    printf("6. Listado x Producto y Ciudad\n");  // Reporte agrupado por producto
    printf("7. Estadisticas\n");                 // Mostrar estadísticas generales
    printf("8. Fin\n");                          // Salir del programa
    printf("=====================================\n");
}

void pausar() {

    // Limpiar completamente el buffer y esperar ENTER
    while (getchar() != '\n');
}

// Función para borrar/limpiar todos los archivos de datos
void borrarArchivos() {
    FILE *archivo;  // Puntero para manejar archivos

    // Crear archivo productos.txt vacío (modo "w" sobrescribe el archivo existente)
    archivo = fopen("productos.txt", "w");
    if (archivo != NULL) {
        fclose(archivo);  // Cerrar el archivo inmediatamente (queda vacío)
    }

    // Crear archivo ciudades.txt vacío
    archivo = fopen("ciudades.txt", "w");
    if (archivo != NULL) {
        fclose(archivo);
    }

    // Crear archivo ventas.txt vacío
    archivo = fopen("ventas.txt", "w");
    if (archivo != NULL) {
        fclose(archivo);
    }


}

// Función para cargar/agregar nuevos productos
void cargarProductos() {
    FILE *archivo;          // Puntero para manejar el archivo
    Producto productoInfo;  // Variable para almacenar temporalmente los datos del producto

    // Abrir archivo en modo "a" (append) y va  agrega al final sin borrar lo existente
    archivo = fopen("productos.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir archivo productos.txt\n");
        return;  // Salir de la función si no se puede abrir el archivo
    }

    printf("\n=== CARGA DE PRODUCTOS ===\n");
    printf("Ingrese codigo del producto (0 para terminar): ");
    scanf("%d", &productoInfo.idProducto);

    // Bucle para cargar múltiples productos (termina cuando se ingresa 0)
    while (productoInfo.idProducto != 0) {
        Producto tempProducto;  // aca va a verificar si ya existe el producto

        // Verificar si el producto ya existe
        if (buscarProducto(productoInfo.idProducto, &tempProducto)) {
            printf("El producto con codigo %d ya existe.\n", productoInfo.idProducto);
        } else {
            // Si no existe, pedir mas datos
            printf("Ingrese descripcion del producto: ");
            scanf(" %20[^\n]", productoInfo.nombreProducto);  // Leer hasta 20 caracteres incluyendo espacios
            printf("Ingrese precio: ");
            scanf("%f", &productoInfo.precioProducto);

            // Escribir en el archivo en formato texto: ID|Nombre|Precio
            fprintf(archivo, "%d|%s|%.2f\n", productoInfo.idProducto,
                   productoInfo.nombreProducto, productoInfo.precioProducto);
        }

        system("cls");
        printf("\n=== CARGA DE PRODUCTOS ===\n");

        // Solicitar el siguiente producto
        printf("Ingrese codigo del producto: ");
        scanf("%d", &productoInfo.idProducto);
    }

    fclose(archivo);  // Cerrar el archivo
}

void cargarCiudades() {
    FILE *archivo;
    Ciudad ciudadInfo;

    archivo = fopen("ciudades.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir archivo ciudades.txt\n");
        return;
    }

  system("cls");
printf("\n=== CARGA DE CIUDADES ===\n");
printf("Ingrese codigo de ciudad (0 para terminar): ");
scanf("%d", &ciudadInfo.codigoCiudad);

while (ciudadInfo.codigoCiudad != 0) {
    Ciudad tempCiudad;

    if (buscarCiudad(ciudadInfo.codigoCiudad, &tempCiudad)) {
        printf("La ciudad con codigo %d ya existe.\n", ciudadInfo.codigoCiudad);
    } else {
        printf("Ingrese nombre de la ciudad: ");
        scanf(" %20[^\n]", ciudadInfo.nombreCiudad);
        fprintf(archivo, "%d|%s\n", ciudadInfo.codigoCiudad, ciudadInfo.nombreCiudad);
    }

    system("cls");
    printf("\n=== CARGA DE CIUDADES ===\n");
    printf("Ingrese codigo de ciudad (0 para terminar): ");
    scanf("%d", &ciudadInfo.codigoCiudad);
}


    fclose(archivo);
}

void cargarVentas() {
    FILE *archivo;
    Venta ventaInfo;
    Producto productoInfo;
    Ciudad ciudadInfo;

    archivo = fopen("ventas.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir archivo ventas.txt\n"); //aca si el archivo esta "vacio" va tirar "error"
        return;
    }

    printf("\n=== CARGA DE VENTAS ===\n");

    while (1) {
        printf("Ingrese numero de factura (0 para volver al menu): ");
        scanf("%d", &ventaInfo.numeroFactura);
        if (ventaInfo.numeroFactura == 0) break;

        printf("Ingrese fecha (DDMMAAAA): ");
        scanf(" %8s", ventaInfo.fechaVenta);

        // Validar producto
        while (1) {
            printf("Ingrese codigo de producto: ");
            scanf("%d", &ventaInfo.idProducto);

            if (ventaInfo.idProducto == 0) {
                fclose(archivo);
                return;
            }

            if (!buscarProducto(ventaInfo.idProducto, &productoInfo)) { //aca si no existe tal codigo tira que no fue encontrado
                printf("Producto no encontrado.\n");
            } else {
                printf("Producto encontrado: %s\n", productoInfo.nombreProducto); //Aca va a seguir
                break;
            }
        }

        // Validar ciudad
        while (1) {
            printf("Ingrese codigo de ciudad (0 para volver al menu): ");
            scanf("%d", &ventaInfo.codigoCiudad);

            if (ventaInfo.codigoCiudad == 0) {
                fclose(archivo);
                return;
            }

            if (!buscarCiudad(ventaInfo.codigoCiudad, &ciudadInfo)) {
                printf("Ciudad no encontrada. Intente nuevamente.\n");
            } else {
                printf("Ciudad encontrada: %s\n", ciudadInfo.nombreCiudad);
                break;
            }
        }

        printf("Ingrese cantidad: ");
        scanf("%f", &ventaInfo.cantidadVendida);

        // muestra una especie de resumen
        fprintf(archivo, "%d|%s|%d|%d|%.2f\n", ventaInfo.numeroFactura,
               ventaInfo.fechaVenta, ventaInfo.idProducto,
               ventaInfo.codigoCiudad, ventaInfo.cantidadVendida);
       printf("\n");  // Espacio entre ventas
        system("cls");  // Limpiar pantalla después de cada venta
        printf("\n=== CARGA DE VENTAS ===\n");
    }

    fclose(archivo);
}

int buscarProducto(int idProducto, Producto *productoInfo) {
    FILE *archivo;
    char linea[100];

    archivo = fopen("productos.txt", "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        // Parsear la línea usando el delimitador |
        char *token = strtok(linea, "|");
        if (token != NULL) {
            int id = atoi(token);
            if (id == idProducto) {
                productoInfo->idProducto = id;

                token = strtok(NULL, "|");
                if (token != NULL) {
                    strcpy(productoInfo->nombreProducto, token);
                }

                token = strtok(NULL, "|");
                if (token != NULL) {
                    productoInfo->precioProducto = atof(token);
                }

                fclose(archivo);
                return 1;
            }
        }
    }

    fclose(archivo);
    return 0;
}

int buscarCiudad(int codigoCiudad, Ciudad *ciudadInfo) {
    FILE *archivo;
    char linea[100];

    archivo = fopen("ciudades.txt", "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo)) {

        char *token = strtok(linea, "|");
        if (token != NULL) {
            int codigo = atoi(token);
            if (codigo == codigoCiudad) {
                ciudadInfo->codigoCiudad = codigo;

                token = strtok(NULL, "|\n");
                if (token != NULL) {
                    strcpy(ciudadInfo->nombreCiudad, token);
                }

                fclose(archivo);
                return 1;
            }
        }
    }

    fclose(archivo);
    return 0;
}

void listadoPorCiudadYProducto() {
    FILE *archivo;
    char linea[200];
    Venta ventaInfo;
    Producto productoInfo;
    Ciudad ciudadInfo;
    int ciudadActual = -1;
    float totalCiudad = 0;
    float totalGeneral = 0;

    archivo = fopen("ventas.txt", "r");
    if (archivo == NULL) {
        printf("No hay ventas registradas.\n");
        return;
    }

    printf("\n=== Listado de ventas por Ciudad y Producto ===\n\n");

    while (fgets(linea, sizeof(linea), archivo)) {
        // Parsear la línea de venta
        char *token = strtok(linea, "|");
        if (token == NULL) continue;
        ventaInfo.numeroFactura = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(ventaInfo.fechaVenta, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        ventaInfo.idProducto = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        ventaInfo.codigoCiudad = atoi(token);

        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        ventaInfo.cantidadVendida = atof(token);

        if (ventaInfo.codigoCiudad != ciudadActual) {
            if (ciudadActual != -1) {
                printf("Total %s $ %.2f\n\n", ciudadInfo.nombreCiudad, totalCiudad);
            }

            ciudadActual = ventaInfo.codigoCiudad;
            totalCiudad = 0;

            if (buscarCiudad(ventaInfo.codigoCiudad, &ciudadInfo)) {
                printf("Ciudad %d- %s:\n", ventaInfo.codigoCiudad, ciudadInfo.nombreCiudad);
            }
        }

        if (buscarProducto(ventaInfo.idProducto, &productoInfo)) {
            float total = ventaInfo.cantidadVendida * productoInfo.precioProducto;
            printf("Producto %d- %s Cant. %.0f precio %.2f Total $ %.2f\n",
                   ventaInfo.idProducto, productoInfo.nombreProducto,
                   ventaInfo.cantidadVendida, productoInfo.precioProducto, total);
            totalCiudad += total;
            totalGeneral += total;
        }
    }

    if (ciudadActual != -1) {
        printf("Total %s $ %.2f\n\n", ciudadInfo.nombreCiudad, totalCiudad);
    }

    printf("Total General $ %.2f\n", totalGeneral);

    fclose(archivo);
}

void listadoPorProductoYCiudad() {
    FILE *archivo;
    char linea[200];
    Venta ventaInfo;
    Producto productoInfo;
    Ciudad ciudadInfo;
    int productoActual = -1;
    float totalProducto = 0;
    float totalGeneral = 0;

    archivo = fopen("ventas.txt", "r");
    if (archivo == NULL) {
        printf("No hay ventas registradas.\n");
        return;
    }

    printf("\n=== Listado de ventas por Producto y Ciudad ===\n\n");

    while (fgets(linea, sizeof(linea), archivo)) {
        // Parsear la línea de venta
        char *token = strtok(linea, "|");
        if (token == NULL) continue;
        ventaInfo.numeroFactura = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(ventaInfo.fechaVenta, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        ventaInfo.idProducto = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        ventaInfo.codigoCiudad = atoi(token);

        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        ventaInfo.cantidadVendida = atof(token);

        if (ventaInfo.idProducto != productoActual) {
            if (productoActual != -1) {
                printf("Total %s $ %.2f\n\n", productoInfo.nombreProducto, totalProducto);
            }

            productoActual = ventaInfo.idProducto;
            totalProducto = 0;

            if (buscarProducto(ventaInfo.idProducto, &productoInfo)) {
                printf("Producto %d- %s:\n", ventaInfo.idProducto, productoInfo.nombreProducto);
            }
        }

        if (buscarCiudad(ventaInfo.codigoCiudad, &ciudadInfo)) {
            float total = ventaInfo.cantidadVendida * productoInfo.precioProducto;
            printf("Ciudad %d- %s Cant. %.0f precio %.2f Total $ %.2f\n",
                   ventaInfo.codigoCiudad, ciudadInfo.nombreCiudad,
                   ventaInfo.cantidadVendida, productoInfo.precioProducto, total);
            totalProducto += total;
            totalGeneral += total;
        }
    }

    if (productoActual != -1) {
        printf("Total %s $ %.2f\n\n", productoInfo.nombreProducto, totalProducto);
    }

    printf("Total General $ %.2f\n", totalGeneral);

    fclose(archivo);
}

typedef struct {
    int codigo;
    char nombre[21];
    float totalVendido;
    int cantidadVentas;
} EstadisticaCiudad;

typedef struct {
    int id;
    char nombre[21];
    float totalVendido;
    int cantidadVentas;
} EstadisticaProducto;

void mostrarEstadisticas() {
    FILE *archivo;
    char linea[200];
    Venta ventaInfo;
    Producto productoInfo;
    Ciudad ciudadInfo;

    EstadisticaCiudad estadCiudades[100];
    EstadisticaProducto estadProductos[100];
    int numCiudades = 0, numProductos = 0;

    // Inicializar arrays
    for(int i = 0; i < 100; i++) {
        estadCiudades[i].codigo = -1;
        estadCiudades[i].totalVendido = 0;
        estadCiudades[i].cantidadVentas = 0;
        estadProductos[i].id = -1;
        estadProductos[i].totalVendido = 0;
        estadProductos[i].cantidadVentas = 0;
    }

    archivo = fopen("ventas.txt", "r");
    if (archivo == NULL) {
        printf("No hay ventas registradas.\n");
        return;
    }

    // Procesar ventas y acumular estadísticas
    while (fgets(linea, sizeof(linea), archivo)) {
        // Parsear la línea de venta
        char *token = strtok(linea, "|");
        if (token == NULL) continue;
        ventaInfo.numeroFactura = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(ventaInfo.fechaVenta, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        ventaInfo.idProducto = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        ventaInfo.codigoCiudad = atoi(token);

        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        ventaInfo.cantidadVendida = atof(token);

        if (buscarProducto(ventaInfo.idProducto, &productoInfo) &&
            buscarCiudad(ventaInfo.codigoCiudad, &ciudadInfo)) {

            float totalVenta = ventaInfo.cantidadVendida * productoInfo.precioProducto;

            // Buscar o crear estadística de ciudad
            int indiceCiudad = -1;
            for(int i = 0; i < numCiudades; i++) {
                if(estadCiudades[i].codigo == ventaInfo.codigoCiudad) {
                    indiceCiudad = i;
                    break;
                }
            }

            if(indiceCiudad == -1) {
                indiceCiudad = numCiudades++;
                estadCiudades[indiceCiudad].codigo = ventaInfo.codigoCiudad;
                strcpy(estadCiudades[indiceCiudad].nombre, ciudadInfo.nombreCiudad);
            }

            estadCiudades[indiceCiudad].totalVendido += totalVenta;
            estadCiudades[indiceCiudad].cantidadVentas++;

            // Buscar o crear estadística de producto
            int indiceProducto = -1;
            for(int i = 0; i < numProductos; i++) {
                if(estadProductos[i].id == ventaInfo.idProducto) {
                    indiceProducto = i;
                    break;
                }
            }

            if(indiceProducto == -1) {
                indiceProducto = numProductos++;
                estadProductos[indiceProducto].id = ventaInfo.idProducto;
                strcpy(estadProductos[indiceProducto].nombre, productoInfo.nombreProducto);
            }

            estadProductos[indiceProducto].totalVendido += totalVenta;
            estadProductos[indiceProducto].cantidadVentas++;
        }
    }

    fclose(archivo);

    printf("\n======================= ESTADISTICAS DE VENTAS =======================\n");

    // Estadísticas por Ciudad
    if(numCiudades > 0) {
        printf("\nEstadisticas por Ciudad:\n");
        printf("Cod  | Ciudad               | Total    | Operac | Promedio\n");
        printf("-----------------------------------------------------------------\n");

        float totalGeneralCiudades = 0;
        int totalOperacionesCiudades = 0;

        for(int i = 0; i < numCiudades; i++) {
            float promedio = estadCiudades[i].totalVendido / estadCiudades[i].cantidadVentas;
            printf("%-4d | %-20s | %8.2f | %6d | %8.2f\n",
                   estadCiudades[i].codigo, estadCiudades[i].nombre,
                   estadCiudades[i].totalVendido, estadCiudades[i].cantidadVentas, promedio);

            totalGeneralCiudades += estadCiudades[i].totalVendido;
            totalOperacionesCiudades += estadCiudades[i].cantidadVentas;
        }

        printf("-----------------------------------------------------------------\n");
        printf("TOTAL| %-20s | %8.2f | %6d | %8.2f\n",
               "GENERAL", totalGeneralCiudades, totalOperacionesCiudades,
               totalGeneralCiudades / totalOperacionesCiudades);

        // Encontrar máximos y mínimos
        int ciudadMaxVentas = 0, ciudadMinVentas = 0;
        for(int i = 1; i < numCiudades; i++) {
            if(estadCiudades[i].totalVendido > estadCiudades[ciudadMaxVentas].totalVendido) {
                ciudadMaxVentas = i;
            }
            if(estadCiudades[i].totalVendido < estadCiudades[ciudadMinVentas].totalVendido) {
                ciudadMinVentas = i;
            }
        }

        printf("\nResumen Ciudades:\n");
        printf("Mayor venta: %s (%.2f)\n", estadCiudades[ciudadMaxVentas].nombre, estadCiudades[ciudadMaxVentas].totalVendido);
        printf("Menor venta: %s (%.2f)\n", estadCiudades[ciudadMinVentas].nombre, estadCiudades[ciudadMinVentas].totalVendido);
        printf("Promedio por ciudad: %.2f\n", totalGeneralCiudades / numCiudades);
    }

    // Estadísticas por Producto
    if(numProductos > 0) {
        printf("\nEstadisticas por Producto:\n");
        printf("ID   | Producto             | Total    | Operac | Promedio\n");
        printf("-----------------------------------------------------------------\n");

        float totalGeneralProductos = 0;
        int totalOperacionesProductos = 0;

        for(int i = 0; i < numProductos; i++) {
            float promedio = estadProductos[i].totalVendido / estadProductos[i].cantidadVentas;
            printf("%-4d | %-20s | %8.2f | %6d | %8.2f\n",
                   estadProductos[i].id, estadProductos[i].nombre,
                   estadProductos[i].totalVendido, estadProductos[i].cantidadVentas, promedio);

            totalGeneralProductos += estadProductos[i].totalVendido;
            totalOperacionesProductos += estadProductos[i].cantidadVentas;
        }

        printf("-----------------------------------------------------------------\n");
        printf("TOTAL| %-20s | %8.2f | %6d | %8.2f\n",
               "GENERAL", totalGeneralProductos, totalOperacionesProductos,
               totalGeneralProductos / totalOperacionesProductos);

        // Encontrar máximos y mínimos
        int productoMaxVentas = 0, productoMinVentas = 0;
        for(int i = 1; i < numProductos; i++) {
            if(estadProductos[i].totalVendido > estadProductos[productoMaxVentas].totalVendido) {
                productoMaxVentas = i;
            }
            if(estadProductos[i].totalVendido < estadProductos[productoMinVentas].totalVendido) {
                productoMinVentas = i;
            }
        }

        printf("\nResumen Productos:\n");
        printf("Mayor venta: %s (%.2f)\n", estadProductos[productoMaxVentas].nombre, estadProductos[productoMaxVentas].totalVendido);
        printf("Menor venta: %s (%.2f)\n", estadProductos[productoMinVentas].nombre, estadProductos[productoMinVentas].totalVendido);
        printf("Promedio por producto: %.2f\n", totalGeneralProductos / numProductos);
    }
}
