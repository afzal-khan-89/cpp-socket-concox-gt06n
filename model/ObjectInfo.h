/*
 * ObjectInfo.h
 *
 *  Created on: Aug 13, 2023
 *      Author: afzal
 */

#ifndef MODEL_OBJECTINFO_H_
#define MODEL_OBJECTINFO_H_

#include <string>

using namespace std ;

class ObjectInfo {
public:
	ObjectInfo();
	virtual ~ObjectInfo();


	string vehicle;
	string latitude;
	string longitude;
	string speed ;

};

#endif /* MODEL_OBJECTINFO_H_ */
