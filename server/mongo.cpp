/*
 * mongo.cpp
 *
 *  Created on: Oct 16, 2023
 *  Author: afzal.
 *
 */

#include "mongo.h"
#include <string>

#include "MongoInstance.h"



using namespace mongodbm ;

Mongo::Mongo()
{


}

Mongo::~Mongo()
{

}



int Mongo::ping()
{
	mongodbm::MongoInstance::GetInstance()->createPool("mongodb://localhost:27017");
	auto cc = mongodbm::MongoInstance::GetInstance()->getClientFromPool();

	mongocxx::client &client = *cc ;
	db =  client["vts-db"];

	try
	{
		const auto ping_cmd = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1));
     	db.run_command(ping_cmd.view());
		std::cout << "Pinged your deployment. You successfully connected to MongoDB!" << std::endl ;
	}
	catch (const std::exception& e)
	{
	    std::cout<< "Exception: " << e.what() << std::endl;

	    return 0 ;

	}
	return 1 ;
}
void Mongo::save(ObjectInfo & object_info)
{

	mongodbm::MongoInstance::GetInstance()->createPool("mongodb://localhost:27017");
	auto cc = mongodbm::MongoInstance::GetInstance()->getClientFromPool();

	mongocxx::client &client = *cc ;
	db =  client["vts-db"];

    auto c = db["oritri"];

	auto insert_one_result = c.insert_one(make_document(
				kvp("latitude", "23.4453453"),
				kvp("longitude", "90.4534534"),
				kvp("speed", "40"),
				kvp("time", stol("12345678", nullptr, 10))
			));

}










































































































































