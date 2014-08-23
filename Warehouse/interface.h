/*
 * Warehouse
 * Copyright (C) 2013 Filipe Carvalho
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>

#include "structs.h"

void initialize_interface();

void menu_search(const warehouse *warehouses);
void menu_insert(warehouse *warehouses);
void menu_warehouse(warehouse *warehouses);
void menu_file(warehouse *warehouses);
void show_menu(const short int menu_number);

#endif // !INTERFACE_H