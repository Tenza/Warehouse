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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>

#include "structs.h"

char* show_tree(const warehouse *warehouses);
char* show_products(const warehouse *warehouses);
char* show_products_by_hallway(const warehouse *warehouses, const int hallway_number);
char* show_products_by_storage(const warehouse *warehouses, const int hallway_number, const int storage_number);
char* show_products_by_type(const warehouse *warehouses, const int product_type);
char* show_products_by_stock(const warehouse *warehouses, const int product_stock);
char* show_sold_products(const warehouse *warehouses, const boolean save);
char* build_path(const warehouse *warehouses, const storage *order);

void update_stock(const warehouse *warehouses, FILE *products);
void process_order(const warehouse *warehouses, FILE *products);
void fix_duplicates(storage *order);
void reorder_list(const warehouse *warehouses, storage *order);

int choose_hallway(const warehouse *warehouses);
int choose_storage(const warehouse *warehouses, int *hallway);
int choose_product(const warehouse *warehouses, int *hallway, int *storage);

void print_file(const char *string);
storage read_textfile(FILE *products, boolean read_fistline);

FILE* get_file(const char *filename, const char *mode);
void get_filename(char *filename, const int size);
void char_input(char *string, const int size);
void int_input(int *integer, const int size);

#endif // !APPLICATION_H
