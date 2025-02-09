#pragma once
#ifndef _LABELSFIND_H_
#define _LABELSFIND_H_

#include <iostream>
#include <string>
#include <map>
#include <fstream>

void labelsFind(const std::string& filename, std::map<std::string, int>& labels, std::string& result);

#endif // !_LABELSFIND_H_


