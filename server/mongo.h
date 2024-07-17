/*
 * mongo.h
 *
 *  Created on: Oct 16, 2023
 *      Author: afzal
 */

#ifndef MONGO_MONGO_H_
#define MONGO_MONGO_H_


using namespace std ;




#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include "../model/ObjectInfo.h"

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

namespace mongodbm {





class Mongo {

public:
	Mongo();
	virtual ~Mongo();
	bool connect();

	void save(ObjectInfo & object_info);
	int ping();

private:
	mongocxx::database db;



};




}

#endif /* MONGO_MONGO_H_ */
