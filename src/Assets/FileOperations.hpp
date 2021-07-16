// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains basic functions for handling files
*/

# ifndef FILE_OPERATIONS_HPP
# define FILE_OPERATIONS_HPP

# include <string>
# include <fstream>

// Opens a file
static std::ifstream OpenFile(const std::string& path) {

    std::ifstream file;
	file.open(path);
	if (!file) {
        throw std::logic_error("Failed to open file: " + path);
	}

    return file;

}

// Closes a file
static void CloseFile(std::ifstream& file) {
    
    if(file) {
        file.close();
    }

}


# endif /* end of include guard: FILE_OPERATIONS_HPP */