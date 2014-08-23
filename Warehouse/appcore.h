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

#ifndef APPCORE_H
#define APPCORE_H

#include <stdio.h>

#include "structs.h"

int identify(FILE *database);
warehouse* initialize(FILE *database);
warehouse* initialize_legacy(FILE *database);
warehouse* initialize_random();
void shutdown(FILE *database, warehouse *warehouses, const boolean save);

void insert_hallway(warehouse *warehouses);
void insert_storage(hallway *hallways);
void insert_product(storage *storages, const int type, const int stock);
void insert_printable(printable *string, const int size);
void remove_hallway(warehouse *warehouses, const int hallway_index, const boolean product_reposition);
void remove_storage(warehouse *warehouses, const int hallway_index, const int storage_index, const boolean product_reposition);

storage* search_storage(const warehouse *warehouses);
product* search_product(const warehouse *warehouses, const int product_type);
boolean search_products(const warehouse *warehouses, const storage *product_type, const boolean check_stock);

printable initialize_printable();

#endif // !APPCORE_H