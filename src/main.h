#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>
#include <iostream>
#include <json/json.h>
#include <curl/curl.h>
#include <thread>
#include "analysis.h"
#include "JSONdata.h"
#include "IEX.h"

void AcquireIEXdata(JSONdata &, const std::string &, const std::string &);

#endif
