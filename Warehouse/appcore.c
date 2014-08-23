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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "appcore.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Identifies the given database. </summary>
///
/// <remarks>	Filipe, 15 Mai 2013. </remarks>
///
/// <param name="database">	Pointer to the database, can be a NULL. </param>
///
/// <returns>	The type of initialization to be used. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
int identify(FILE *database)
{
	int result = 0;
	char db[WH_NAME_SIZE] = {0};

	if (database != NULL)
	{
		fread(&db, sizeof(db), 1, database);
		rewind(database);

		if(strcmp(db, WH_NAME) != 0)
		{
			result = 1;
		}		
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Reads the file, alocates memory and fills the structures with the readed data.
/// 	The alocated memory is incrised by a factor of ALLOC_FACTOR to spare some realocation calls.
/// </summary>
///
/// <remarks>	Filipe, 15 Mai 2013. </remarks>
///
/// <param name="database">	Pointer to the database, can be a NULL. </param>
///
/// <returns>	Pointer to the main struct warehouse. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
warehouse* initialize(FILE *database)
{
	int i = 0;
	int j = 0;
	int k = 0;

	warehouse *warehouses = NULL;
	
	warehouses = (warehouse*) calloc(1, sizeof(warehouse));
	warehouses->sold = (storage*) calloc(1, sizeof(storage));
	strcpy(warehouses->name, WH_NAME);

	if (database != NULL)
	{
		fread(&warehouses->name, sizeof(warehouses->name), 1, database);
		fread(&warehouses->hallways_size, sizeof(warehouses->hallways_size), 1, database);

		warehouses->hallways_memory = warehouses->hallways_size * ALLOC_FACTOR;
		warehouses->hallways = (hallway*) calloc(warehouses->hallways_memory, sizeof(hallway));

		for(i = 0; i < warehouses->hallways_size; i++)
		{
			fread(&warehouses->hallways[i].storages_size, sizeof(warehouses->hallways[i].storages_size), 1, database);

			warehouses->hallways[i].storages_memory = warehouses->hallways[i].storages_size * ALLOC_FACTOR;
			warehouses->hallways[i].storages = (storage*) calloc(warehouses->hallways[i].storages_memory, sizeof(storage));

			for(j = 0; j < warehouses->hallways[i].storages_size; j++)
			{
				fread(&warehouses->hallways[i].storages[j].products_size, sizeof(warehouses->hallways[i].storages[j].products_size), 1, database);

				warehouses->hallways[i].storages[j].products_memory = warehouses->hallways[i].storages[j].products_size * ALLOC_FACTOR;
				warehouses->hallways[i].storages[j].products = (product*) calloc(warehouses->hallways[i].storages[j].products_memory, sizeof(product));

				for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
				{
					fread(&warehouses->hallways[i].storages[j].products[k].product_type, sizeof(warehouses->hallways[i].storages[j].products[k].product_type), 1, database);
					fread(&warehouses->hallways[i].storages[j].products[k].product_stock, sizeof(warehouses->hallways[i].storages[j].products[k].product_stock), 1, database);
				}
			}
		}
	}

	return warehouses;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Reads the file, alocates memory and fills the structures with the readed data.
/// 	The alocated memory is incrised by a factor of ALLOC_FACTOR to spare some realocation calls.
/// </summary>
///
/// <remarks>	Filipe, 15 Mai 2013. </remarks>
///
/// <param name="database">	Pointer to the database, can be a NULL. </param>
///
/// <returns>	Pointer to the main struct warehouse. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
warehouse* initialize_legacy(FILE *database)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int hws = 0;
	int sts = 0;

	warehouse *warehouses = NULL;
	
	warehouses = (warehouse*) calloc(1, sizeof(warehouse));
	warehouses->sold = (storage*) calloc(1, sizeof(storage));
	strcpy(warehouses->name, WH_NAME);

	if (database != NULL)
	{
		fread(&hws, sizeof(warehouses->hallways_size), 1, database);
		fread(&sts, sizeof(warehouses->hallways->storages_size), 1, database);

		warehouses->hallways_size = hws;
		warehouses->hallways_memory = warehouses->hallways_size * ALLOC_FACTOR;
		warehouses->hallways = (hallway*) calloc(warehouses->hallways_memory, sizeof(hallway));
		
		for(i = 0; i < warehouses->hallways_size; i++)
		{
			warehouses->hallways[i].storages_size = sts;
			warehouses->hallways[i].storages_memory = warehouses->hallways[i].storages_size * ALLOC_FACTOR;
			warehouses->hallways[i].storages = (storage*) calloc(warehouses->hallways[i].storages_memory, sizeof(storage));

			for(j = 0; j < warehouses->hallways[i].storages_size; j++)
			{
				fread(&warehouses->hallways[i].storages[j].products_size, sizeof(warehouses->hallways[i].storages[j].products_size), 1, database);

				warehouses->hallways[i].storages[j].products_memory = warehouses->hallways[i].storages[j].products_size * ALLOC_FACTOR;
				warehouses->hallways[i].storages[j].products = (product*) calloc(warehouses->hallways[i].storages[j].products_memory, sizeof(product));

				for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
				{
					fread(&warehouses->hallways[i].storages[j].products[k].product_type, sizeof(warehouses->hallways[i].storages[j].products[k].product_type), 1, database);
					fread(&warehouses->hallways[i].storages[j].products[k].product_stock, sizeof(warehouses->hallways[i].storages[j].products[k].product_stock), 1, database);
				}
			}
		}
	}

	return warehouses;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Alocates memory and fills the structures with random data.
/// 	The alocated memory is incrised by a factor of ALLOC_FACTOR to spare some realocation calls.
/// </summary>
///
/// <remarks>	Filipe, 15 Mai 2013. </remarks>
/// <remarks>	This function can insert multiple products in diferent locations. </remarks>
///
/// <param name="database">	Pointer to the database, can be a NULL. </param>
///
/// <returns>	Pointer to the main struct warehouse. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
warehouse* initialize_random()
{
	int i = 0;
	int j = 0;
	int k = 0;

	int hw = 0; // Number of Hallways
	int st = 0; // Number of Storages
	int pr = 0; // Number of Products

	warehouse *warehouses = NULL;

	srand((unsigned int)time(NULL));

	warehouses = (warehouse*) calloc(1, sizeof(warehouse));
	strcpy(warehouses->name, "Warehouse");

	hw = rand() % 100 + 1;
	warehouses->hallways_size = hw;
	warehouses->hallways_memory = hw * ALLOC_FACTOR;
	warehouses->hallways = (hallway*) calloc(warehouses->hallways_memory, sizeof(hallway));

	for(i = 0; i < hw; i++)
	{
		st = rand() % 100 + 1;
		warehouses->hallways[i].storages_size = st;
		warehouses->hallways[i].storages_memory = st * ALLOC_FACTOR;
		warehouses->hallways[i].storages = (storage*) calloc(warehouses->hallways[i].storages_memory, sizeof(storage));

		for(j = 0; j < st; j++)
		{
			pr = rand() % 100 + 1;
			warehouses->hallways[i].storages[j].products_size = pr;
			warehouses->hallways[i].storages[j].products_memory = pr * ALLOC_FACTOR;
			warehouses->hallways[i].storages[j].products = (product*) calloc(warehouses->hallways[i].storages[j].products_memory, sizeof(product));

			for(k = 0; k < pr; k++)
			{
				warehouses->hallways[i].storages[j].products[k].product_type = rand() % 1000 + 1;;
				warehouses->hallways[i].storages[j].products[k].product_stock = rand() % 1000 + 1;;			
			}
		}
	}

	return warehouses;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Saves the warehouse to a file and frees the memory. </summary>
///
/// <remarks>	Filipe, 15 Mai 2013. </remarks>
///
/// <param name="warehouses">	Pointer to warehouses. </param>
/// <param name="database">  	Pointer to the database. </param>
/// <param name="save">		 	true to save the data. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void shutdown(FILE *database, warehouse *warehouses, const boolean save)
{
	int i = 0;
	int j = 0;
	int k = 0;

	if(save)
	{
		if (database != NULL)
		{		
			fwrite(&warehouses->name, sizeof(warehouses->name), 1, database);
			fwrite(&warehouses->hallways_size, sizeof(warehouses->hallways_size), 1, database);

			for(i = 0; i < warehouses->hallways_size; i++)
			{
				fwrite(&warehouses->hallways[i].storages_size, sizeof(warehouses->hallways[i].storages_size), 1, database);

				for(j = 0; j < warehouses->hallways[i].storages_size; j++)
				{
					fwrite(&warehouses->hallways[i].storages[j].products_size, sizeof(warehouses->hallways[i].storages[j].products_size), 1, database);

					for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
					{
						fwrite(&warehouses->hallways[i].storages[j].products[k].product_type, sizeof(warehouses->hallways[i].storages[j].products[k].product_type), 1, database);
						fwrite(&warehouses->hallways[i].storages[j].products[k].product_stock, sizeof(warehouses->hallways[i].storages[j].products[k].product_stock), 1, database);
					}
				}
			}

			fclose(database);
		}
	}

	for(i = 0; i < warehouses->hallways_size; i++)
	{
		for(j = 0; j <  warehouses->hallways[i].storages_size; j++)
		{
			free(warehouses->hallways[i].storages[j].products);
		}
		free(warehouses->hallways[i].storages);
	}

	free(warehouses->sold->products);
	free(warehouses->hallways);
	free(warehouses->sold);
	free(warehouses);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Realocates a struct, updates the current size, initializes the next struct.
/// </summary>
///
/// <remarks>	Filipe, 15 Mai 2013. </remarks>
///
/// <param name="warehouses">	Pointer to warehouses. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void insert_hallway(warehouse *warehouses)
{
	hallway *h = NULL;

	if(warehouses->hallways_size >= warehouses->hallways_memory)
	{
		if (warehouses->hallways_size == 0)
		{
			warehouses->hallways_memory++;			
		}
		else
		{
			warehouses->hallways_memory = warehouses->hallways_size * ALLOC_FACTOR;
		}
		
		h = (hallway*) realloc(warehouses->hallways, warehouses->hallways_memory * sizeof(hallway));

		if(h != NULL)
		{
			warehouses->hallways = h;
		}

	}

	warehouses->hallways[warehouses->hallways_size].storages_size = 0;
	warehouses->hallways[warehouses->hallways_size].storages_memory = 0;
	warehouses->hallways[warehouses->hallways_size].storages = NULL;

	warehouses->hallways_size++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Realocates a struct, updates the current size, initializes the next struct.
/// </summary>
///
/// <remarks>	Filipe, 15 Mai 2013. </remarks>
///
/// <param name="hallways">	Pointer to hallways. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void insert_storage(hallway *hallways)
{
	storage *s = NULL;

	if(hallways->storages_size >= hallways->storages_memory)
	{
		if (hallways->storages_size == 0)
		{
			hallways->storages_memory++;			
		}
		else
		{
			hallways->storages_memory = hallways->storages_size * ALLOC_FACTOR;
		}
		
		s = (storage*) realloc(hallways->storages, hallways->storages_memory * sizeof(storage));

		if(s != NULL)
		{
			hallways->storages = s;
		}
	}

	hallways->storages[hallways->storages_size].products_size = 0;
	hallways->storages[hallways->storages_size].products_memory = 0;
	hallways->storages[hallways->storages_size].products = NULL;

	hallways->storages_size++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///  <summary>
/// 	Realocates a struct, updates the current size, initializes the next struct.
/// </summary>
///
/// <remarks>	Filipe, 15 Mai 2013. </remarks>
/// <remarks>	
/// 	Before the use of this struct, use the function 'search_product'
/// 	to make sure that the product only exists in one place
/// </remarks>
///
/// <param name="storages">	Pointer to storages. </param>
/// <param name="type">	   	The type. </param>
/// <param name="stock">   	The stock. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void insert_product(storage *storages, const int type, const int stock)
{
	product *p = NULL;

	if(storages->products_size >= storages->products_memory)
	{
		if (storages->products_size == 0)
		{
			storages->products_memory++;			
		}
		else
		{
			storages->products_memory = storages->products_size * ALLOC_FACTOR;
		}
		
		p = (product*) realloc(storages->products, storages->products_memory * sizeof(product));

		if(p != NULL)
		{
			storages->products = p;
		}
	}

	storages->products[storages->products_size].product_type = type;
	storages->products[storages->products_size].product_stock = stock;

	storages->products_size++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Inserts a printable. </summary>
///
/// <remarks>	Filipe, 24 Mai 2013. </remarks>
///
/// <param name="string">	[in,out] If non-null, the string. </param>
/// <param name="size">  	The size. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void insert_printable(printable *string, const int size)
{
	char *s = NULL;
	boolean copy = FALSE;

	if (string->print_memory == 0)
	{
		copy = TRUE;
	}

	string->counter++;
	string->print_size += size;

	if(string->print_size >= string->print_memory)
	{
		string->print_memory = string->print_size * ALLOC_FACTOR;
		s = (char*) realloc(string->print, string->print_memory);

		if (s != NULL)
		{
			string->print = s;
		}
	}

	if(copy)
	{
		strcpy(string->print, string->print_temp);
	}
	else
	{
		strcat(string->print, string->print_temp);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Removes the hallway.
/// 	The selected hallway is replaced with the last one, and its products are redistributed.
/// </summary>
///
/// <remarks>	Filipe, 10 Jun 2013. </remarks>
///
/// <param name="warehouses">		 	[in,out] If non-null, the warehouses. </param>
/// <param name="hallway_index">	 	Zero-based index of the hallway. </param>
/// <param name="product_reposition">	true to calculate every product reposition. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void remove_hallway(warehouse *warehouses, const int hallway_index, const boolean product_reposition)
{
	int i = 0;
	int j = 0;
	hallway aux;
	storage *s = NULL;

	if(warehouses->hallways_size > 1)
	{
		aux = warehouses->hallways[hallway_index];
		warehouses->hallways[hallway_index] = warehouses->hallways[warehouses->hallways_size - 1];
		warehouses->hallways_size--;

		for(i = 0; i < aux.storages_size; i++)
		{
			if(!product_reposition)
			{
				s = search_storage(warehouses);
			}
			for(j = 0; j < aux.storages[i].products_size; j++)
			{
				if(product_reposition)
				{
					s = search_storage(warehouses);
				}

				insert_product(s, aux.storages[i].products[j].product_type, aux.storages[i].products[j].product_stock);
			}

			free(aux.storages[i].products);
		}
	
		free(aux.storages);		
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// 	Removes the storage.
/// 	The selected storage is replaced with the last, one and its products are redistributed.
/// </summary>
///
/// <remarks>	Filipe, 10 Jun 2013. </remarks>
///
/// <param name="warehouses">		 	[in,out] If non-null, the warehouses. </param>
/// <param name="hallway_index">	 	Zero-based index of the hallway. </param>
/// <param name="storage_index">	 	Zero-based index of the storage. </param>
/// <param name="product_reposition">	true to calculate every product reposition. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void remove_storage(warehouse *warehouses, const int hallway_index, const int storage_index, const boolean product_reposition)
{
	int i = 0;
	storage aux;
	storage *s = NULL;

	if(warehouses->hallways[hallway_index].storages_size > 1)
	{
		aux = warehouses->hallways[hallway_index].storages[storage_index];
		warehouses->hallways[hallway_index].storages[storage_index] = warehouses->hallways[hallway_index].storages[warehouses->hallways[hallway_index].storages_size - 1];
		warehouses->hallways[hallway_index].storages_size--;

		if(!product_reposition)
		{
			s = search_storage(warehouses);
		}
		for(i = 0; i < aux.products_size; i++)
		{
			if(product_reposition)
			{
				s = search_storage(warehouses);
			}

			insert_product(s, aux.products[i].product_type, aux.products[i].product_stock);
		}
		
		free(aux.products);		
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Search for the storage with less products. </summary>
///
/// <remarks>	Filipe, 24 Mai 2013. </remarks>
///
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
///
/// <returns>	null if it fails, else the found storage. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
storage* search_storage(const warehouse *warehouses)
{
	int i = 0;
	int j = 0;
	int k = 0;

	int p_size = 0;
	storage *s = NULL;

	for(i = 0; i < warehouses->hallways_size; i++)
	{
		for(j = 0; j < warehouses->hallways[i].storages_size; j++)
		{
			if(p_size > warehouses->hallways[i].storages[j].products_size || s == NULL)
			{
				s = &warehouses->hallways[i].storages[j];
				p_size = warehouses->hallways[i].storages[j].products_size;
			}
		}
	}

	return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Search for a product. </summary>
///
/// <remarks>	Filipe, 24 Mai 2013. </remarks>
///
/// <param name="warehouses">  	[in,out] If non-null, the warehouses. </param>
/// <param name="product_type">	Type of the product. </param>
///
/// <returns>	null if it fails, else the found product. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
product* search_product(const warehouse *warehouses, const int product_type)
{
	int i = 0;
	int j = 0;
	int k = 0;
	boolean found = FALSE;

	product *p = NULL;
	
	for(i = 0; i < warehouses->hallways_size; i++)
	{
		for(j = 0; j < warehouses->hallways[i].storages_size; j++)
		{
			for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
			{
				if(warehouses->hallways[i].storages[j].products[k].product_type == product_type)
				{
					p = &warehouses->hallways[i].storages[j].products[k];
					found = TRUE;
					break;
				}
			}
			if(found)
			{
				break;
			}
		}
		if(found)
		{
			break;
		}
	}

	return p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Seach multiple products and stocks. </summary>
///
/// <remarks>	Filipe, 24 Mai 2013. </remarks>
///
/// <param name="warehouses">  	[in,out] If non-null, the warehouses. </param>
/// <param name="product_type">	[in,out] If non-null, type of the product. </param>
/// <param name="check_stock"> 	true to check stock. </param>
///
/// <returns>	true if it succeeds, false if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
boolean search_products(const warehouse *warehouses, const storage *product_type, const boolean check_stock)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int y = 0;
	int count = 0;
	boolean result = FALSE;

	for(i = 0; i < warehouses->hallways_size; i++)
	{
		for(j = 0; j < warehouses->hallways[i].storages_size; j++)
		{
			for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
			{
				for (y = 0; y < product_type->products_size; y++)
				{
					if(warehouses->hallways[i].storages[j].products[k].product_type == product_type->products[y].product_type)
					{
						if(check_stock)
						{
							if(warehouses->hallways[i].storages[j].products[k].product_stock >= product_type->products[y].product_stock)
							{
								count++;
							}
						}
						else
						{
							count++;
						}						
					}
				}
			}
		}
	}

	if(count == product_type->products_size)
	{
		result = TRUE;
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Initializes the printable struct. </summary>
///
/// <remarks>	Filipe, 24 Mai 2013. </remarks>
///
/// <returns>	. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
printable initialize_printable()
{
	printable string;

	string.print = NULL;
	string.print_memory = 0;
	string.print_size = 0;
	string.counter = 0;

	return string;
}