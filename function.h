/*
 ============================================================================
 Name        : function.h
 Author      : oosode
 Version     : 
 Date        : Dec 26, 2013
 Description : 
 ============================================================================
 */
#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <vector>
#include <string>

void StringExplode(std::string str, std::string separator, std::vector<std::string> *results)
{
    int found;
    results->clear();
    found = str.find_first_of(separator);

    if (separator==" ")
    {
    	while(found != (int)std::string::npos)
    	{
			if(found > 0)
			{
				results->push_back(str.substr(0,found));
			}
			str = str.substr(found+1);
			found = str.find_first_of(separator);
		}
		if (str.length() > 0)
		{
			results->push_back(str);
		}

    }
    else
    {
    	while(found != (int)std::string::npos)
    	{
    		if(found > 0)
    		{
				results->push_back(str.substr(0,found));
			}
    		else
			{
				std::string placeholder="";
				results->push_back(placeholder);
			}
			str = str.substr(found+1);
			found = str.find_first_of(separator);
		}
		if (str.length() >= 0)
		{
			results->push_back(str);
		}
    }
}
#endif /* FUNCTION_H_ */
