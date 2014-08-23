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

#ifndef DATATYPES_H
#define DATATYPES_H

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Definition of the Boolean type. </summary>
///
/// <remarks>	Filipe, 03 Fev 2011. </remarks>
/// <remarks>
///		By default, enums are automatically given integer values starting from 0 by the compiler.
///		Therefore FALSE will be 0 and TRUE will be 1.
///	</remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
enum boolean
{ 
	FALSE, 
	TRUE
};
typedef enum boolean boolean;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Definition of the Printable Type. </summary>
///
/// <remarks>	Filipe, 24 Mai 2013. </remarks>
/// <remarks>
/// 	string			Dont touch directly - Use insert_string function to deal with this field
///		string_size		Dont touch directly - Sent as argument for insert_string
///		string_memory	Dont touch directly - Use insert_string function to deal with this field
///		counter			Dont touch directly - Incremented each time string_temp is added
///		string_temp		Temporary field for a single string, filled by sprintf.
///		
///		How to use:
///			char *data = NULL;
///			data = function_call();
///				printable data = initialize_printable();
///				insert_printable(&data, sprintf(data.print_temp, "%d", counter));
///				return data.print;
///			printf("%s\n", data);
///			free(data);
/// </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct printable
{
	char *print;
	int print_size;
	int print_memory;

	int counter;
	char print_temp[MAX_PRINT];
};
typedef struct printable printable;

#endif // !DATATYPES_H