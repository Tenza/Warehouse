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
#include <ctype.h>

#include "application.h"
#include "appcore.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Shows the database tree. </summary>
///
/// <remarks>	Filipe, 11 Mai 2013. </remarks>
///
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
char* show_tree(const warehouse *warehouses)
{
	int i = 0;
	int j = 0;
	int k = 0;
	printable data = initialize_printable();

	insert_printable(&data, sprintf(data.print_temp, "Armazem: %s\n", warehouses->name));
	insert_printable(&data, sprintf(data.print_temp, "Corredores: %d\n", warehouses->hallways_size));

	for(i = 0; i < warehouses->hallways_size; i++)
	{
		insert_printable(&data, sprintf(data.print_temp, "\tArmarios: %d\n", warehouses->hallways[i].storages_size));

		for(j = 0; j < warehouses->hallways[i].storages_size; j++)
		{
			insert_printable(&data, sprintf(data.print_temp, "\t\tProdutos: %d\n", warehouses->hallways[i].storages[j].products_size));

			for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
			{
				insert_printable(&data, sprintf(data.print_temp, 
					"\t\t\t%d %d %d: Tipo %d Stock %d\n", i + 1, j + 1, k + 1, 
					warehouses->hallways[i].storages[j].products[k].product_type, 
					warehouses->hallways[i].storages[j].products[k].product_stock));
			}
		}
	}

	return data.print;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Shows all the products. </summary>
///
/// <remarks>	Filipe, 11 Mai 2013. </remarks>
///
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
char* show_products(const warehouse *warehouses)
{
	int i = 0;
	int j = 0;
	int k = 0;
	printable data = initialize_printable();

	for(i = 0; i < warehouses->hallways_size; i++)
	{
		for(j = 0; j < warehouses->hallways[i].storages_size; j++)
		{
			for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
			{
				insert_printable(&data, sprintf(data.print_temp, 
					"Produto %d existem %d em stock\n", 
					warehouses->hallways[i].storages[j].products[k].product_type, 
					warehouses->hallways[i].storages[j].products[k].product_stock));
			}
		}
	}

	insert_printable(&data, sprintf(data.print_temp, "Existem %d produtos no armazem\n", data.counter));

	return data.print;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Shows the products by hallway. </summary>
///
/// <remarks>	Filipe, 11 Mai 2013. </remarks>
///
/// <param name="warehouses">	 	[in,out] If non-null, the warehouses. </param>
/// <param name="hallway_number">	The hallway number. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
char* show_products_by_hallway(const warehouse *warehouses, const int hallway_number)
{
	int j = 0;
	int k = 0;
	printable data = initialize_printable();

	if (hallway_number >= 0)
	{
		for(j = 0; j < warehouses->hallways[hallway_number].storages_size; j++)
		{
			for(k = 0; k < warehouses->hallways[hallway_number].storages[j].products_size; k++)
			{
				insert_printable(&data, sprintf(data.print_temp, 
					"Produto %d existem %d em stock\n", 
					warehouses->hallways[hallway_number].storages[j].products[k].product_type, 
					warehouses->hallways[hallway_number].storages[j].products[k].product_stock));
			}
		}

		insert_printable(&data, sprintf(data.print_temp, "Existem %d produtos no corredor %d\n", data.counter, hallway_number + 1));
	}

	return data.print;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Shows the products by storage. </summary>
///
/// <remarks>	Filipe, 11 Mai 2013. </remarks>
///
/// <param name="warehouses">	 	[in,out] If non-null, the warehouses. </param>
/// <param name="hallway_number">	The hallway number. </param>
/// <param name="storage_number">	The storage number. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
char* show_products_by_storage(const warehouse *warehouses, const int hallway_number, const int storage_number)
{
	int k = 0;
	printable data = initialize_printable();

	if ((hallway_number >= 0) && (storage_number >= 0))
	{
		for(k = 0; k < warehouses->hallways[hallway_number].storages[storage_number].products_size; k++)
		{
			insert_printable(&data, sprintf(data.print_temp, 
				"Produto %d existem %d em stock\n", warehouses->hallways[hallway_number].storages[storage_number].products[k].product_type,
				warehouses->hallways[hallway_number].storages[storage_number].products[k].product_stock));
		}

		insert_printable(&data, sprintf(data.print_temp, "Existem %d produtos no armario %d do corredor %d\n", data.counter, storage_number + 1, hallway_number + 1));
	}

	return data.print;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Shows the products by storage.
/// </summary>
///
/// <remarks>	Filipe, 11 Mai 2013. </remarks>
/// <remarks>	
/// 	Assums that product_type is always bigger than 0 
/// 	The loop breaks because there is only one product type.
/// </remarks>
/// 
/// 
/// <param name="warehouses">  	[in,out] If non-null, the warehouses. </param>
/// <param name="product_type">	Type of the product. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
char* show_products_by_type(const warehouse *warehouses, const int product_type)
{
	int i = 0;
	int j = 0;
	int k = 0;
	printable data = initialize_printable();

	if(product_type > 0)
	{
		for(i = 0; i < warehouses->hallways_size; i++)
		{
			for(j = 0; j < warehouses->hallways[i].storages_size; j++)
			{
				for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
				{
					if(warehouses->hallways[i].storages[j].products[k].product_type == product_type)
					{
						insert_printable(&data, sprintf(data.print_temp, 
							"O produto %d com stock de %d encontra-se no corredor %d no armario %d\n", 
							warehouses->hallways[i].storages[j].products[k].product_type, 
							warehouses->hallways[i].storages[j].products[k].product_stock, i + 1, j + 1));
						break;
					}
				}
				if(data.counter != 0)
				{
					break;
				}
			}
			if(data.counter != 0)
			{
				break;
			}
		}
		if(data.counter == 0)
		{
			insert_printable(&data, sprintf(data.print_temp, "O produto %d nao foi encontrado\n", product_type));
		}
	}
	return data.print;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Shows the products by stock. </summary>
///
/// <remarks>	Filipe, 11 Mai 2013. </remarks>
///
/// <param name="warehouses">   	[in,out] If non-null, the warehouses. </param>
/// <param name="product_stock">	The product stock. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
char* show_products_by_stock(const warehouse *warehouses, const int product_stock)
{
	int i = 0;
	int j = 0;
	int k = 0;
	printable data = initialize_printable();
		
	if(product_stock > 0)
	{
		for(i = 0; i < warehouses->hallways_size; i++)
		{
			for(j = 0; j < warehouses->hallways[i].storages_size; j++)
			{
				for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
				{
					if(warehouses->hallways[i].storages[j].products[k].product_stock == product_stock)
					{
						insert_printable(&data, sprintf(data.print_temp, 
							"O produto %d tem stock de %d e encontra-se no corredor %d no armario %d\n", 
							warehouses->hallways[i].storages[j].products[k].product_type, 
							warehouses->hallways[i].storages[j].products[k].product_stock, i + 1, j + 1));
					}
				}
			}
		}

		insert_printable(&data, sprintf(data.print_temp, "Existem %d produtos com stock de %d\n", data.counter, product_stock));
	}

	return data.print;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Shows the sold products. </summary>
///
/// <remarks>	Filipe, 25 Mai 2013. </remarks>
///
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
/// <param name="save">		 	true to save. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
char* show_sold_products(const warehouse *warehouses, const boolean save)
{
	int i = 0;
	printable data = initialize_printable();

	if (warehouses->sold->products_size != 0)
	{
		insert_printable(&data, sprintf(data.print_temp, "Produtos vendidos: \n\n"));
		for(i = 0; i < warehouses->sold->products_size; i++)
		{
			insert_printable(&data, sprintf(data.print_temp, 
				"Produto: %d Stock: %d\n", 
				warehouses->sold->products[i].product_type, 
				warehouses->sold->products[i].product_stock));
		}
	}
	else
	{
		insert_printable(&data, sprintf(data.print_temp, "Nao existem produtos vendidos.\n"));
	}

	if (save)
	{
		FILE *print_data = get_file(SUMMARY_NAME, "w");

		if (print_data != NULL)
		{
			fprintf(print_data, "%s", data.print);
			fclose(print_data);
			free(data.print);
			data.print = NULL;
		}
	}

	return data.print;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Builds a path. </summary>
///
/// <remarks>	Filipe, 25 Mai 2013. </remarks>
///
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
/// <param name="order">	 	[in,out] If non-null, the order. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
char* build_path(const warehouse *warehouses, const storage *order)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int y = 0;
	boolean found = FALSE;
	boolean first_hallway = TRUE;
	printable data = initialize_printable();

	insert_printable(&data, sprintf(data.print_temp, "Entrar no armazem.\n\n"));

	for(i = 0; i < warehouses->hallways_size; i++)
	{
		for(j = 0; j < warehouses->hallways[i].storages_size; j++)
		{
			for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
			{
				for (y = 0; y < order->products_size; y++)
				{
					if(warehouses->hallways[i].storages[j].products[k].product_type == order->products[y].product_type)
					{
						if(first_hallway)
						{
							insert_printable(&data, sprintf(data.print_temp, 
								"\tEntrar no corredor %d\n\t\t - Encontrar armario %d\n\t\t - Retirar %d unidades do produto %d\n", i + 1, j + 1, 
								order->products[y].product_stock, 
								order->products[y].product_type));
							first_hallway = FALSE;
						}
						else
						{
							insert_printable(&data, sprintf(data.print_temp, "\t\t - Encontrar armario %d\n\t\t - Retirar %d unidades do produto %d\n", j + 1, 
								order->products[y].product_stock, 
								order->products[y].product_type));
						}
						found = TRUE;
					}
				}
			}
		}
		if(found)
		{
			insert_printable(&data, sprintf(data.print_temp, "\tSair do corredor %d\n\n", i + 1));
			first_hallway = TRUE;
			found = FALSE;
		}
	}

	insert_printable(&data, sprintf(data.print_temp, "Sair do armazem\n"));

	return data.print;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the stock. </summary>
///
/// <remarks>	Filipe, 25 Mai 2013. </remarks>
///
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
/// <param name="products">  	[in,out] If non-null, the products. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void update_stock(const warehouse *warehouses, FILE *products)
{
	int i = 0;
	product *p = NULL;
	storage *s = NULL;
	storage stock = read_textfile(products, TRUE);

	if (stock.products != NULL)
	{
		fix_duplicates(&stock);
		for(i = 0; i < stock.products_size; i++)
		{
			if(stock.products[i].product_stock > 0)
			{
				p = search_product(warehouses, stock.products[i].product_type);
				if(p != NULL)
				{
					printf("Stock do produto %d actualizado. (%d -> ", p->product_type, p->product_stock);
					p->product_stock += stock.products[i].product_stock;
					printf("%d)\n", p->product_stock);
				}
				else
				{
					s = search_storage(warehouses);
					insert_product(s, stock.products[i].product_type, stock.products[i].product_stock);
					printf("Produto %d adicionado com stock de %d.\n", stock.products[i].product_type, stock.products[i].product_stock);
				}
			}
			else
			{
				printf("O produto %d nao foi actualizado por nao ter um stock positivo.\n", 
					stock.products[i].product_type);
			}
		}

		free(stock.products);
	}
	else
	{
		printf("\nPor favor corrija o ficheiro e volte a tentar.\n");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Process the order. </summary>
///
/// <remarks>	Filipe, 25 Mai 2013. </remarks>
///
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
/// <param name="products">  	[in,out] If non-null, the products. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void process_order(const warehouse *warehouses, FILE *products)
{
	int i = 0;
	int count = 0;
	char *data = NULL;
	product *p = NULL;	
	storage order = read_textfile(products, FALSE);

	if (order.products != NULL)
	{

		fix_duplicates(&order);
		reorder_list(warehouses, &order);

		for(i = 0; i < order.products_size; i++)
		{
			p = search_product(warehouses, order.products[i].product_type);
			if(p != NULL)
			{
				if(p->product_stock >= order.products[i].product_stock)
				{
					count++;
				}
				else
				{
					printf("O produto %d nao tem stock suficiente.\n", order.products[i].product_type);
				}
			}
			else
			{
				printf("O produto %d nao foi encontrado.\n", order.products[i].product_type);
			}
		}

		if(order.products_size == count)
		{
			for (i = 0; i < order.products_size; i++)
			{
				p = search_product(warehouses, order.products[i].product_type);
				if(p != NULL)
				{
					printf("Vendida %d unidades do produto %d.\n", order.products[i].product_stock, order.products[i].product_type);
					p->product_stock -= order.products[i].product_stock;
					insert_product(warehouses->sold, order.products[i].product_type, order.products[i].product_stock);
				}
			}

			data = build_path(warehouses, &order);
			printf("%s", data);
			free(data);
		}

		free(order.products);
	}
	else
	{
		printf("\nPor favor corrija o ficheiro e volte a tentar.\n");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Fixes duplicates. </summary>
///
/// <remarks>	Filipe, 25 Mai 2013. </remarks>
///
/// <param name="order">	[in,out] If non-null, the order. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void fix_duplicates(storage *order)
{
	int i = 0;
	int j = 0;
	int k = 0;
		
	if(order->products_size > 0)
	{
		for(i = 0; i < order->products_size; i++)
		{
			for(j = i + 1; j < order->products_size; j++)
			{
				if(order->products[i].product_type == order->products[j].product_type)
				{
					order->products[i].product_stock += order->products[j].product_stock;
					order->products[j] = order->products[order->products_size - 1];
					order->products_size--;
					j--;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Reorder list. </summary>
///
/// <remarks>	Filipe, 25 Mai 2013. </remarks>
///
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
/// <param name="order">	 	[in,out] If non-null, the order. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void reorder_list(const warehouse *warehouses, storage *order)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int y = 0;
	int counter = 0;

	product aux;

	for(i = 0; i < warehouses->hallways_size; i++)
	{
		for(j = 0; j < warehouses->hallways[i].storages_size; j++)
		{
			for(k = 0; k < warehouses->hallways[i].storages[j].products_size; k++)
			{
				for(y = counter; y < order->products_size; y++)
				{
					if(warehouses->hallways[i].storages[j].products[k].product_type == order->products[y].product_type)
					{
						aux = order->products[counter];
						order->products[counter] = order->products[y];
						order->products[y] = aux;

						counter++;
						break;
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Choose a hallway. </summary>
///
/// <remarks>	Filipe, 12 Mai 2013. </remarks>
/// 
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
///
/// <returns>	The choosen hallway or -1 if fails (Zero based output) </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
int choose_hallway(const warehouse *warehouses)
{
	int i = 0;
	int option = 0;
	boolean loop = TRUE;

	if(warehouses->hallways_size > 0)
	{
		while(loop)
		{
			for(i = 1; i < warehouses->hallways_size + 1; i++)
			{
				printf("%d - Corredor\n", i);
			}

			printf("%d - Voltar\n\n", i);
			printf("Escolha um corredor: ");
			int_input(&option, 9);

			if (option > 0 && option < warehouses->hallways_size + 2)
			{
				if (option == warehouses->hallways_size + 1)
				{
					option = 0;
					loop = FALSE;
				}
				else
				{
					loop = FALSE;
				}			
			}
			else
			{
				printf("Essa opcao nao existe.\n\n");
			}
		}
	}
	else
	{
		printf("Nao existem corredores.\n\n");
	}

	return option - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Choose a storage</summary>
///
/// <remarks>	Filipe, 12 Mai 2013. </remarks>
/// <remarks>	
/// 	hallway is a pointer because if we go back from the choose_product and 
/// 	then back again, choose_product have to know the new hallway.  
/// </remarks>
/// 
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
/// <param name="hallway">   	[in,out] If non-null, the hallway. </param>
///
/// <returns>	The choosen storage or -1 if fails (Zero based output) </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
int choose_storage(const warehouse *warehouses, int *hallway)
{
	int i = 0;
	int option = 0;
	boolean loop = TRUE;

	if (*hallway >= 0)
	{
		if(warehouses->hallways[*hallway].storages_size > 0)
		{
			while(loop)
			{
				for(i = 1; i < warehouses->hallways[*hallway].storages_size + 1; i++)
				{
					printf("%d - Armario\n", i);
				}

				printf("%d - Voltar\n\n", i);
				printf("Escolha um armario: ");
				int_input(&option, 9);

				if (option > 0 && option < warehouses->hallways[*hallway].storages_size + 2)
				{
					if (option == warehouses->hallways[*hallway].storages_size + 1)
					{
						*hallway = choose_hallway(warehouses);
						if (*hallway < 0)
						{
							option = 0;
							loop = FALSE;
						}
					}
					else
					{
						loop = FALSE;
					}	
				}
				else
				{
					printf("Essa opcao nao existe.\n\n");
				}
			}
		}
		else
		{
			printf("Nao existem armarios no corredor %d.\n\n", *hallway + 1);
		}
	}

	return option - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Choose product. </summary>
///
/// <remarks>	Filipe, 12 Mai 2013. </remarks>
///	<remarks>
/// 	hallway and storage are pointers because if we go back 
/// 	we have to know the new hallway and storage.
/// </remarks>
/// 
/// <param name="warehouses">	[in,out] If non-null, the warehouses. </param>
/// <param name="hallway">   	[in,out] If non-null, the hallway. </param>
/// <param name="storage">   	[in,out] If non-null, the storage. </param>
///
/// <returns>	The choosen product or -1 if fails (Zero based output) </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
int choose_product(const warehouse *warehouses, int *hallway, int *storage)
{
	int i = 0;
	int option = 0;
	boolean loop = TRUE;

	if (*hallway >= 0 && *storage >= 0)
	{
		if(warehouses->hallways[*hallway].storages[*storage].products_size > 0)
		{
			while(loop)
			{
				for(i = 1; i < warehouses->hallways[*hallway].storages[*storage].products_size + 1; i++)
				{
					printf("%d - Produto: %d Stock: %d \n", i, 
						warehouses->hallways[*hallway].storages[*storage].products[i - 1].product_type, 
						warehouses->hallways[*hallway].storages[*storage].products[i - 1].product_stock);
				}

				printf("%d - Voltar\n\n", i);
				printf("Escolha um produto: ");
				int_input(&option, 9);

				if (option > 0 && option < warehouses->hallways[*hallway].storages[*storage].products_size + 2)
				{
					if (option == warehouses->hallways[*hallway].storages[*storage].products_size + 1)
					{
						*storage = choose_storage(warehouses, hallway);
						if (*storage < 0)
						{
							option = 0;
							loop = FALSE;
						}
					}
					else
					{
						loop = FALSE;
					}	
				}
				else
				{
					printf("Essa opcao nao existe.\n\n");
				}
			}
		}
		else
		{
			printf("Nao existem produtos no armario %d.\n\n", *storage + 1);
		}
	}

	return option - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Asks the user if the string recived should or not be saved. </summary>
///
/// <remarks>	Filipe, 24 Mai 2013. </remarks>
///
/// <param name="string">	[in,out] If non-null, the string. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void print_file(const char *string)
{
	int option = 0;
	boolean loop = TRUE;

	FILE *print_data = NULL;
	char filename[FILENAME_SIZE] = {0};

	while(loop)
	{
		printf("Gravar resultados em ficheiro?\n\n");
		printf("1 - Sim\n");
		printf("2 - Nao\n\n");

		printf("Opcao: ");
		int_input(&option, 2);

		if(option == 1)
		{
			get_filename(filename, FILENAME_SIZE);
			print_data = get_file(filename, "w");	

			if (print_data != NULL)
			{
				fprintf(print_data, "%s", string);
				fclose(print_data);
				printf("O ficheiro foi gravado com sucesso.\n\n");
			}
			else
			{
				printf("Nao foi possivel gravar o ficheiro\n\n");
			}

			loop = FALSE;
		}
		else if(option == 2)
		{
			loop = FALSE;
		}
		else
		{
			printf("Essa opcao nao existe.\n\n");
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Reads a textfile. </summary>
///
/// <remarks>	Filipe, 25 Mai 2013. </remarks>
///
/// <param name="products">			[in,out] If non-null, the products. </param>
/// <param name="read_fistline">	true to read the fistline. </param>
///
/// <returns>	The textfile. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
storage read_textfile(FILE *products, boolean read_fistline)
{
	int count = 1;
	int args_read = 0;
	char line[MAX_FGETS];
	boolean error = FALSE;

	int product_type = 0;
	int product_stock = 0;

	storage order;
	order.products = NULL;
	order.products_memory = 0;
	order.products_size = 0;

	while(fgets(line, MAX_FGETS, products) != NULL)
	{	
		args_read = sscanf(line, "%d: %d", &product_type, &product_stock);

		if (read_fistline)
		{		
			if (args_read == 2 && product_type != 0 && product_stock != 0)
			{
				insert_product(&order, product_type, product_stock);
			}
			else
			{
				printf("Linha %d com formato invalido.\n", count);
				error = TRUE;
			}
		}
		else
		{
			printf("A processar: %s\n", line);
			read_fistline = TRUE;
		}

		count++;
		product_type = 0;
		product_stock = 0;
	}

	if(error)
	{
		free(order.products);
		order.products = NULL;
		order.products_memory = 0;
		order.products_size = 0;
	}

	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// 	Opens a file, and in case of faliure asks the user on how to proceed.
/// </summary>
///
/// <remarks>	Filipe, 09 Fev 2011. </remarks>
/// <remarks>
///		fclose required on the returned pointer.
/// </remarks>
/// 
/// <param name="filename">	[in,out] If non-null, filename of the file. </param>
/// <param name="mode">	   	[in,out] If non-null, the mode. </param>
///
/// <returns>	null if it fails, else the file. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
FILE* get_file(const char *filename, const char *mode)
{
	int option = 0;

	FILE *database = NULL;
	boolean loop = TRUE;

	char filename_aux[FILENAME_SIZE] = {0};
	strcpy(filename_aux, filename);

	while(loop)
	{
		if ((database = fopen(filename_aux, mode)) != NULL)
		{
			loop = FALSE;		
		}
		else
		{
			if((strcmp(mode, "rb") == 0) || (strcmp(mode, "r") == 0))
			{		
				printf("Ocurreu um erro na leitura do ficheiro: %s\n\n", filename_aux);
				printf("1 - Voltar a tentar ler o ficheiro\n");
				printf("2 - Procurar outro ficheiro manualmente\n");
				printf("3 - Continuar sem ler ficheiro\n\n");
				
			}
			else if((strcmp(mode, "wb") == 0) || (strcmp(mode, "w") == 0) || (strcmp(mode, "a") == 0))
			{
				printf("Ocurreu um erro ao escrever no ficheiro: %s\n\n", filename_aux);
				printf("1 - Voltar a tentar escrever no ficheiro\n");
				printf("2 - Criar um novo ficheiro\n");
				printf("3 - Sair sem guardar os dados\n\n");
			}

			printf("Opcao: ");
			int_input(&option, 2);

			switch(option)
			{
				case 1:
					{
						break;
					}
				case 2:
					{
						get_filename(filename_aux, FILENAME_SIZE);
						break;
					}
				case 3:
					{
						loop = FALSE;
						database = NULL;
						break;
					}
				default:
					{
						printf("Essa opcao nao existe.\n\n");
						break;
					}
			}
		}
	}

	return database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Asks for a filename to write or read from. </summary>
///
/// <remarks>	Filipe, 09 Fev 2011. </remarks>
///
/// <param name="filename">	[in,out] If non-null, filename of the file. </param>
/// <param name="size">	   	The size. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void get_filename(char *filename, const int size)
{
	boolean loop = TRUE;

	while(loop)
	{
		printf("Nome do ficheiro: ");
		char_input(filename, size);

		if (strcmp(filename, "") != 0)
		{
			loop = FALSE;
		}
		else
		{
			printf("Escreva um nome para o ficheiro\n\n");
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///		Function that deals with char[] input.
/// </summary>
///
/// <remarks>	Filipe, 11 Fev 2011. </remarks>
/// <remarks>
///  	The value returned will always have the size of 'size' -1, the last char is \0.
/// 	The max value for 'size' is the same as the given array(string[size]).
/// 	Will always fail, if the value of 'size' is 0 or 1.
/// 	Returns 0 in case of failure.
/// </remarks>
///
/// <param name="string">	[in,out] If non-null, the string. </param>
/// <param name="size">  	The size. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void char_input(char *string, const int size)
{
	fgets(string, size, stdin);

	string[strcspn(string, "\r\n")] = '\0';

	if(strlen(string) == size - 1)
	{
		while (getchar() != '\n') {}
	}

	system("cls");
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Function that deals with integer input.
/// </summary>
///
/// <remarks>	Filipe, 11 Fev 2011. </remarks>
/// <remarks>
///		The value returned will always have the size of 'size'.
/// 	The max value for 'size' is the same as the length of the int range (2,147,483,647 ~ 9)
/// 	Will always fail, if the value of 'size' is 0 or 1.
/// 	Returns 0 in case of failure.
/// </remarks>
///
/// <param name="integer">	[in,out] If non-null, the integer. </param>
/// <param name="size">   	The size. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void int_input(int *integer, const int size)
{
	char *string = (char*) malloc(size);

	fgets(string, size, stdin);

	string[strcspn(string, "\r\n")] = '\0';

	if(strlen(string) == size - 1)
	{
		while (getchar() != '\n') {}
	}

	*integer = (int) strtol(string, NULL, 0);

	free(string);

	system("cls");
}