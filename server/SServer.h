/*
 * SServer.h
 *
 *  Created on: Aug 14, 2023
 *      Author: afzal
 */

#ifndef SERVER_SSERVER_H_
#define SERVER_SSERVER_H_

#include <string>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <map>


using namespace std;

class SServer {
public:
	SServer();
	virtual ~SServer();

	void create(int port);
};

#endif /* SERVER_SSERVER_H_ */
