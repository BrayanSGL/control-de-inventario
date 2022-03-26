#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <windows.h>

using namespace std;

int menu();
bool check(string Product);
void add(ofstream &data);
void view(ifstream &data);
void search(ifstream &data);
void sell(ifstream &data);
void erase(ifstream &data);

int main()
{
    ofstream inventoryWrite;
    ifstream inventoryRead;

    int option;
    do
    {
        system("cls");
        option = menu();
        switch (option)
        {
        case 1:
            sell(inventoryRead);
            break;
        case 2:
            search(inventoryRead);
            break;
        case 3:
            view(inventoryRead);
            break;
        case 4:
            add(inventoryWrite);
            break;
        case 5:
            erase(inventoryRead);
            break;
        }
    } while (option != 6);

    return 0;
}

int menu()
{
    int option;
    system("cls");
    cout << "---> CONTROL DE INVENTARIO SUPERSTORE <---\n\n******** Menu *******\n1.Producto vendido\n2.Buscar producto\n3.Ver inventario\n4.Agregar a inventario\n5.Eliminar un producto\n6.Salir\n\nOpcion: "; //  menu
    cin >> option;
    if (option >= 1 && option <= 6)
    {
        return option;
    }
    else
    {
        cout << "Opcion no valida" << endl;
    }
    system("pause");
    menu();
}

void add(ofstream &data)
{
    system("cls");
    string product;
    int price, quantity;
    data.open("./source/inventory.txt", ios::out | ios::app);
    cout << "Producto :";
    cin >> product;
    cout << "Precio :";
    cin >> price;
    cout << "Cantidad :";
    cin >> quantity;
    if (check(product))
    {
        data << product << " " << price << " " << quantity << endl;
    }
    data.close();
}

bool check(string Product)
{
    ifstream read("./source/inventory.txt", ios::in);
    string product;
    int price, quantity;

    read >> product;
    while (!read.eof())
    {
        read >> price;
        read >> quantity;
        if (Product == product)
        {
            read.close();
            cout << "Este producto ya existe (No se agregara)" << endl;
            system("pause");
            return false;
        }
        read >> product;
    }
    read.close();
    return true;
}

void view(ifstream &data)
{
    system("cls");
    string product;
    int price, quantity;
    data.open("./source/inventory.txt", ios::in);
    if (data.is_open())
    {
        cout << "---> INVENTARIO  <---" << endl;
        data >> product;
        while (!data.eof())
        {
            data >> price;
            data >> quantity;
            cout << "Producto:   " << product << endl;
            cout << "Precio:     $" << price << endl;
            cout << "Cantidad:   " << quantity << endl;
            cout << "---------------------------" << endl;
            data >> product;
        }
        data.close();
    }
    else
    {
        cout << "El archivo del inventario no existe" << endl;
    }
    system("pause");
}

void search(ifstream &data)
{
    system("cls");
    data.open("./source/inventory.txt", ios::in);
    if (data.is_open())
    {
        string product, auxProduct;
        int price, quantity;
        bool found = false;
        cout << "Ingrese el nombre del producto: ";
        cin >> auxProduct;
        data >> product;
        while (!data.eof() && !found)
        {
            data >> price;
            data >> quantity;
            if (product == auxProduct)
            {
                cout << "Producto:   " << product << endl;
                cout << "Precio:     $" << price << endl;
                cout << "Cantidad:   " << quantity << endl;
                cout << "---------------------------" << endl;
                found = true;
            }

            data >> product;
        }
        data.close();

        if (!found)
        {
            cout << "Producto no encontrado" << endl;
        }
    }
    else
    {
        cout << "El archivo del inventario no existe" << endl;
    }
    system("pause");
}

void sell(ifstream &data)
{
    system("cls");
    data.open("./source/inventory.txt", ios::in);
    ofstream aux("./source/auxiliary.txt", ios::out);
    if (data.is_open())
    {
        string product, auxProduct;
        int price, quantity, auxQuantity;
        bool found = false;
        cout << "Producto a vender: ";
        cin >> auxProduct;
        data >> product;
        while (!data.eof())
        {
            data >> price;
            data >> quantity;
            if (product == auxProduct)
            {
                cout << "Cantidad de productos que va a vender: ";
                cin >> auxQuantity;
                auxQuantity = quantity - auxQuantity;
                aux << product << " " << price << " " << auxQuantity << "\n";
                found = true;
            }
            else
            {
                aux << product << " " << price << " " << quantity << "\n";
            }

            data >> product;
        }
        data.close();
        aux.close();
        if (!found)
        {
            cout << "Producto no encontrado" << endl;
            Sleep(2000);
        }
    }
    else
    {
        cout << "No se encuenta el archivo" << endl;
    }
    remove("./source/inventory.txt");
    rename("./source/auxiliary.txt", "./source/inventory.txt");
}

void erase(ifstream &data)
{
    system("cls");
    data.open("./source/inventory.txt", ios::in);
    ofstream aux("./source/auxiliary.txt", ios::out);
    if (data.is_open())
    {
        string product, auxProduct;
        int price, quantity, auxQuantity;
        bool found = false;
        cout << "Producto a eliminar: ";
        cin >> auxProduct;
        data >> product;
        while (!data.eof())
        {
            data >> price;
            data >> quantity;
            if (product == auxProduct)
            {
                cout << product << " Se ha elimidado del inventario correctamente \n";
                Sleep(2000);
                found = true;
            }
            else
            {
                aux << product << " " << price << " " << quantity << "\n";
            }

            data >> product;
        }
        if (!found)
        {
            cout << "Producto no encontrado" << endl;
            Sleep(2000);
        }
        data.close();
        aux.close();
    }
    else
    {
        cout << "No se encuenta el archivo" << endl;
    }
    remove("./source/inventory.txt");
    rename("./source/auxiliary.txt", "./source/inventory.txt");
}