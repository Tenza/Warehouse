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

#include "interface.h"
#include "appcore.h"
#include "application.h"

void initialize_interface()
{
	warehouse *warehouses = NULL;
	FILE *database = NULL;
	boolean loop = TRUE;
	int option;
	int db_type;

	database = get_file(DBNAME, "rb");
	db_type = identify(database);

	//db_type = 2;
	if(db_type == 0)
	{
		warehouses = initialize(database);
	}
	else if(db_type == 1)
	{
		warehouses = initialize_legacy(database);
	}
	else if(db_type == 2)
	{
		warehouses = initialize_random();
	}

	if(database != NULL)
	{
		fclose(database);
	}

	printf("Digite o numero da opcao a esquerda para navegar entre menus.\n\n");
	while(loop)
	{
		show_menu(1);
		int_input(&option, 3);

		switch(option)
		{
			case 1:
				{
					menu_search(warehouses);
					break;
				}
			case 2:
				{
					menu_insert(warehouses);
					break;
				}
			case 3:
				{
					menu_file(warehouses);
					break;
				}
			case 4:
				{
					menu_warehouse(warehouses);
					break;
				}
			case 9:
				{
					loop = FALSE;
					break;
				}
			default:
				{
					printf("Essa opcao nao existe.\n\n");
					break;
				}
		}
	}

	show_sold_products(warehouses, TRUE);
	shutdown(get_file(DBNAME, "wb"), warehouses, TRUE);
}

void menu_search(const warehouse *warehouses)
{
	boolean loop = TRUE;
	char *data = NULL;
	int option;

	while(loop)
	{
		show_menu(2);
		int_input(&option, 3);

		switch(option)
		{
			case 1:
				{
					data = show_tree(warehouses);								
					break;
				}
			case 2:
				{
					data = show_products(warehouses);
					break;
				}
			case 3:
				{
					data = show_products_by_hallway(warehouses, choose_hallway(warehouses));
					break;
				}
			case 4:
				{
					int hallway_number = choose_hallway(warehouses);
					int storage_number = choose_storage(warehouses, &hallway_number);

					data = show_products_by_storage(warehouses, hallway_number, storage_number);
					break;
				}
			case 5:
				{					
					printf("Numero do produto: ");
					int_input(&option, 9);

					if(option > 0)
					{
						data = show_products_by_type(warehouses, option);
					}			
					else
					{
						printf("Numero invalido\n\n");
					}
					break;
				}
			case 6:
				{
					printf("Stock do produto: ");
					int_input(&option, 9);

					if(option > 0)
					{
						data = show_products_by_stock(warehouses, option);
					}			
					else
					{
						printf("Numero invalido\n\n");
					}
					break;
				}
			case 7:
				{
					data = show_sold_products(warehouses, FALSE);
					break;
				}
			case 9:
				{
					loop = FALSE;
					break;
				}
			default:
				{
					printf("Essa opcao nao existe.\n\n");
					break;
				}
		}

		if (data != NULL)
		{
			printf("%s\n", data);
			print_file(data);
			free(data);
			data = NULL;
		}
	}
}

void menu_insert(warehouse *warehouses)
{
	boolean loop = TRUE;
	int option;
	int option2;

	while(loop)
	{
		show_menu(3);
		int_input(&option, 3);

		switch(option)
		{
			case 1:
				{
					int hallway_number = choose_hallway(warehouses);
					int storage_number = choose_storage(warehouses, &hallway_number);

					if ((hallway_number >= 0) && (storage_number >= 0))
					{	
						printf("Numero do produto: ");
						int_input(&option, 9);

						if(option > 0)
						{
							if(search_product(warehouses, option) == NULL)
							{
								printf("Stock do produto: ");
								int_input(&option2, 9);

								if(option2 > 0)
								{
									insert_product(&warehouses->hallways[hallway_number].storages[storage_number], option, option2);
									printf("Produto %d inserido\n\n", option);
								}			
								else
								{
									printf("Numero invalido\n\n");
								}
							}
							else
							{
								printf("Esse produto ja existe.\n\n");
							}
						}			
						else
						{
							printf("Numero invalido\n\n");
						}
					}
					break;
				}
			case 2:
				{
					int hallway_number = choose_hallway(warehouses);
					int storage_number = choose_storage(warehouses, &hallway_number);
					int product_number = choose_product(warehouses, &hallway_number, &storage_number);

					if ((hallway_number >= 0) && (storage_number >= 0) && (product_number >= 0))
					{
						printf("Novo valor de stock do produto: ");
						int_input(&option, 9);

						if (option > 0)
						{
							warehouses->hallways[hallway_number].storages[storage_number].products[product_number].product_stock = option;
							printf("Stock alterado para %d\n\n", option);
						}
						else
						{
							printf("Numero invalido\n\n");
						}
					}
					break;
				}
			case 9:
				{
					loop = FALSE;
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

void menu_file(warehouse *warehouses)
{
	boolean loop = TRUE;
	int option;

	FILE *load_data = NULL;
	char filename[FILENAME_SIZE] = {0};

	while(loop)
	{
		show_menu(4);
		int_input(&option, 3);

		switch(option)
		{
			case 1:
				{
					if((warehouses->hallways_size > 0) && (warehouses->hallways[warehouses->hallways_size - 1].storages_size > 0))
					{
						get_filename(filename, FILENAME_SIZE);
						load_data = get_file(filename, "r");	

						if (load_data != NULL)
						{
							update_stock(warehouses, load_data);
							fclose(load_data);
							printf("\n");
						}
						else
						{
							printf("Nao foi possivel carregar o ficheiro.\n\n");
						}
					}
					else
					{
						printf("Nao existem corredores ou armarios.\n\n");
					}
					break;
				}
			case 2:
				{
					if((warehouses->hallways_size > 0) && (warehouses->hallways[warehouses->hallways_size - 1].storages_size > 0))
					{
						get_filename(filename, FILENAME_SIZE);
						load_data = get_file(filename, "r");	

						if (load_data != NULL)
						{
							process_order(warehouses, load_data);
							fclose(load_data);
							printf("\n");
						}
						else
						{
							printf("Nao foi possivel carregar o ficheiro.\n\n");
						}
					}
					else
					{
						printf("Nao existem corredores ou armarios.\n\n");
					}
					break;
				}
			case 9:
				{
					loop = FALSE;
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

void menu_warehouse(warehouse *warehouses)
{
	boolean loop = TRUE;
	int option;

	while(loop)
	{
		show_menu(5);
		int_input(&option, 3);

		switch(option)
		{
			case 1:
				{
					insert_hallway(warehouses);
					insert_storage(&warehouses->hallways[warehouses->hallways_size - 1]);
					printf("Corredor adicionado.\n\n");
					break;
				}
			case 2:
				{
					if(warehouses->hallways_size > 0)
					{
						int hallway_number = choose_hallway(warehouses);
						if (hallway_number >= 0)
						{
							insert_storage(&warehouses->hallways[hallway_number]);
							printf("Armario adicionado.\n\n");
						}
					}
					else
					{
						printf("Nao existem corredores.\n\n");
					}
					break;
				}
				case 3:
				{
					int hallway_number = choose_hallway(warehouses);

					if (hallway_number >= 0)
					{
						if(warehouses->hallways_size > 1)
						{
							remove_hallway(warehouses, hallway_number, TRUE);
							printf("Corredor removido.\n\n");
						}
						else
						{
							printf("Nao e possivel remover o ultimo corredor.\n\n");
						}
					}
					break;
				}
				case 4:
				{
					int hallway_number = choose_hallway(warehouses);
					int storage_number = choose_storage(warehouses, &hallway_number);

					if ((hallway_number >= 0) && (storage_number >= 0))
					{
						if(warehouses->hallways[hallway_number].storages_size > 1)
						{
							remove_storage(warehouses, hallway_number, storage_number, TRUE);
							printf("Armario removido.\n\n");
						}
						else
						{
							printf("Nao e possivel remover o ultimo corredor.\n\n");
						}
					}
					break;
				}
			case 9:
				{
					loop = FALSE;
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

void show_menu(const short int menu_number)
{
	if(menu_number == 1)
	{
		printf("1 - Pesquisas e listagens\n");
		printf("2 - Inserir e alterar dados\n");
		printf("3 - Carregar ficheiros\n");
		printf("4 - Alterar armazem\n");
		printf("9 - Sair\n\n");	
	}
	else if(menu_number == 2)
	{
		printf("1 - Mostrar arvore do armazem\n");
		printf("2 - Listar todos os produtos do armazem\n");
		printf("3 - Listar todos os produtos de um corredor\n");
		printf("4 - Listar todos os produtos de um armario\n");
		printf("5 - Procurar por numero de produto\n");
		printf("6 - Procurar pelo stock de produto\n");	
		printf("7 - Mostrar produtos vendidos\n");
		printf("9 - Voltar\n\n");
	}
	else if(menu_number == 3)
	{
		printf("1 - Inserir produto\n");
		printf("2 - Alterar stock\n");
		printf("9 - Voltar\n\n");
	}
	else if(menu_number == 4)
	{
		printf("1 - Carregar ficheiro de stocks\n");
		printf("2 - Carregar ficheiro de encomenda\n");
		printf("9 - Voltar\n\n");
	}
	else if(menu_number == 5)
	{
		printf("1 - Inserir corredor\n");
		printf("2 - Inserir armario\n");
		printf("3 - Remover corredor\n");
		printf("4 - Remover armario\n");
		printf("9 - Voltar\n\n");
	}

	printf("Opcao: ");
}