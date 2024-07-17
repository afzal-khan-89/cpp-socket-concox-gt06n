/*
 * MongoInstance.cpp
 *
 *  Created on: May 30, 2024
 *      Author: afz
 */

#include "MongoInstance.h"

using namespace mongodbm ;

MongoInstance::MongoInstance()
{
	// TODO Auto-generated constructor stub

}

MongoInstance::~MongoInstance()
{
	// TODO Auto-generated destructor stub
}

MongoInstance* MongoInstance::GetInstance ()
{
	  static MongoInstance objMongoDBInstance;
	  return &objMongoDBInstance;
}
void MongoInstance::createPool(std::string uri_)
{
	  if (!m_client_pool)
	  {
	    m_client_pool = (std::unique_ptr<mongocxx::pool>)
	    new mongocxx::pool { mongocxx::uri {uri_} };
	  }
}
mongocxx::pool::entry MongoInstance::getClientFromPool ()
{
	 return m_client_pool->acquire();
}
