#ifndef GLOBAL_HPP
# define GLOBAL_HPP

# include <iostream>
# include <string>
# include <vector>
# include <thread>
# include <chrono>
# include <stdexcept>
# include <memory>
# include <cstdlib>
# include <cstdio>
# include <optional>
# include <algorithm>
# include <utility>

# include <time.h>
# include <sys/time.h>
# include <unistd.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>

using std::string;
using std::vector;

using std::optional;
using std::unique_ptr;

using std::cout;
using std::endl;

using std::cerr;

void    getProjectName(string& projectName);
void	getPaintingSize(int& paintWidth, int& paintHeight);

void    launch(const string& projectName, const int globalWidth, \
	const int globalHeight, const int paintWidth, const int paintHeight);

int     main(void);

#endif
