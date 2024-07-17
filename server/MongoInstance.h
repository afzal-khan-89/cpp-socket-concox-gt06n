/*
 * MongoInstance.h
 *
 *  Created on: May 30, 2024
 *      Author: afz
 */

#ifndef MONGO_MONGOINSTANCE_H_
#define MONGO_MONGOINSTANCE_H_

#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <iostream>
#include <memory>

namespace mongodbm {

	class MongoInstance {

	private:
	   mongocxx::instance m_dbInstance;
	   std::unique_ptr<mongocxx::pool> m_client_pool;
	   MongoInstance();

	public:

		virtual ~MongoInstance();
		static MongoInstance* GetInstance () ;
		void createPool(std::string uri_) ;
		mongocxx::pool::entry getClientFromPool () ;
	};

}

#endif
