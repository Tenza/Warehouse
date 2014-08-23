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

#ifndef PARAMETERS_H
#define PARAMETERS_H

//Aplication parameters
#define DBNAME "database.bin"		//DBNAME: default name for the database (used in initialize and shutdown)
#define SUMMARY_NAME "summary.txt"	//SUMMARY_NAME: default name for the summary of products
#define ALLOC_FACTOR 2				//ALLOC_FACTOR: number of times that the memory grow in relation to the real size
#define FILENAME_SIZE 30			//FILENAME_SIZE: maximum input size for the database file

#define MAX_PRODUCTS 1000000		//NOT IN USE
#define MAX_PRINT 1000				//MAX_STRING: maximum size for the temporary string in the printable structure.
#define MAX_FGETS 100				//MAX_FGETS: maximum size for each readed line in the textfiles (orders and stock).

//Warehouse parameters
#define WH_NAME_SIZE 100			//WH_NAME_SIZE: maximum size for the name of the WareHouse
#define WH_NAME "Warehouse"			//WH_NAME: Identifys the database type by adding this to the top of the file

#endif