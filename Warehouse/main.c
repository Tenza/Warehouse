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

//Debug Only
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

#include <stdlib.h>

#include "interface.h"

void main(int argc, char *agrv[])
{
	initialize_interface();

	//_CrtDumpMemoryLeaks();

	exit(EXIT_SUCCESS);
}

/*
TODO: FEITO - Estruturas de dados
TODO: FEITO - Escrita de estruturas em ficheiro
TODO: FEITO - Leitura de ficheiro em estruturas
TODO: FEITO - Sistema de memória dinâmica
TODO: FEITO - Funções de criação dinâmica de dados
TODO: FEITO - Funções de interação com o utilizador
TODO: FEITO - Menu do utilizador v1
TODO: FEITO - Pesquisa de todos os produtos no armazem
TODO: FEITO - Funcao de escolha de corredor
TODO: FEITO - Pesquisa de todos os produtos num corredor
TODO: FEITO - Funcao de escolha de armário
TODO: FEITO - Pesquisa de todos os produtos num armário
TODO: FEITO - Menu do utilizador v2
TODO: FEITO - Pesquisa pelo numero de produto
TODO: FEITO - Pesquisa pelo numero de stock
TODO: FEITO - Problema com includes
TODO: FEITO - Colocar as estruturas no mesmo ficheiro
TODO: FEITO - Restruturação de ficheiros
TODO: FEITO - Código de impressão
TODO: FEITO - Gravar pesquisas em ficheiro
TODO: FEITO - Actualização de Stocks
TODO: FEITO - Adicionar novos produtos
TODO: FEITO - Processar ficheiro de produtos
TODO: FEITO - Processar ficheiro de encomendas
TODO: FEITO - Gerar caminho
TODO: FEITO - Sumario de vendas
TODO: FEITO - Suporte a ficheiro de dados do moodle
TODO: FEITO - Problema ao gerar caminho
TODO: FEITO - Ordenação e remoçao de duplicacoes
TODO: FEITO - Retestar funcoes de ficheiro
TODO: FEITO - Funções de remoção de dados
TODO: Array de warehouses (Criar ficheiro estático com nomes de outros ficheiros)
*/