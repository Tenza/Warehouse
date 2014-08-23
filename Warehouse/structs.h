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

#ifndef STRUCTS_H
#define STRUCTS_H

#include "parameters.h"
#include "datatypes.h"

struct product
{
	int product_type;
	int product_stock;
};
typedef struct product product;

struct storage
{
	int products_size;
	int products_memory;
	product *products;
};
typedef struct storage storage;

struct hallway
{
	int storages_size;
	int storages_memory;
	storage *storages;
};
typedef struct hallway hallway;

struct warehouse
{
	char name[WH_NAME_SIZE];
	int hallways_size;
	int hallways_memory;
	hallway *hallways;
	storage *sold;
};
typedef struct warehouse warehouse;

#endif // !STRUCTS_H