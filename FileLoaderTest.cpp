//
//  FileLoaderTest.cpp
//  
//
//  Created by Alex Rao on 6/10/18.
//

#include <stdio.h>
#include "FileLoader.h"
#include <sstream>
using namespace std;

class FileLoader;

int main(){

    string path = "products_in.txt";
    BST<Product> p(FileLoader::loadProducts(path));

    path = "Customers.txt";
    BST<Customer> c(FileLoader::loadCustomers(path));

    path = "Employees.txt";
    BST<Employee> e(FileLoader::loadEmployees(path));

}