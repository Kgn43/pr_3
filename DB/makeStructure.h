#ifndef MAKESTRUCTURE_H
#define MAKESTRUCTURE_H

#include <nlohmann/json.hpp>
#include <sys/stat.h>
#include <utility>
#include <fstream>
#include "userQuery.h"

void makeStructure(nlohmann::json structure);
void lotNames(const nlohmann::json& structureJSON);

#endif //MAKESTRUCTURE_H
