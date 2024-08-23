/*
 * SServer.cpp
 *
 *  Created on: Aug 14, 2023
 *      Author: afzal
 */
#include "SServer.h"
#include "../model/ObjectInfo.h"

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include "../model/ObjectInfo.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "mongo.h"
#include "MongoInstance.h"

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

using namespace std;


#define PROTOCOL_NO_LOGIN       	0x01
#define PROTOCOL_HEARTBIT       	0x13
#define PROTOCOL_LOCATION 			0x12
#define PROTOCOL_ALARM 				0x16


//
//typedef struct{
//	 char imei[18];
//	 long time;
//	 char latitude[16];
//	 char longitude[16];
//	 char data_status[2];
//	 int  speed ;
//	 char fuel[6];
//	 char temp[6];
//	 char gsm_strength;
//	 int sat_view;
//	 char hdop[12];
//	 char pdop[12];
//	 int course;
//	 char sensor[3] ;
//}Vehicle_info_t;

typedef struct{
	 long time;
	 char imei[18];
	 char latitude[16];
	 char longitude[16];
	 char data_status[2];
	 uint16_t speed ;
	 uint16_t fuel;
	 uint8_t temp;
	 uint8_t gsm_strength;
	 uint8_t sat_view;
	 char hdop[12];
	 char pdop[12];
	 uint16_t course;
	 uint16_t sensor ;

	 uint8_t device_voltage_level;


}Vehicle_info_t;

typedef struct{
	uint8_t *src;
	uint8_t resp_packet[128];
	uint16_t resp_crc ;
}Packet_t;

SServer::SServer()
{
	// TODO Auto-generated constructor stub

}

SServer::~SServer()
{
	// TODO Auto-generated destructor stub
}






static const uint16_t crctab16[]=
{
		0X0000,0X1189,0X2312,0X329B,0X4624,0X57AD,0X6536,0X74BF,
		0X8C48,0X9DC1,0XAF5A,0XBED3,0XCA6C,0XDBE5,0XE97E,0XF8F7,
		0X1081,0X0108,0X3393,0X221A,0X56A5,0X472C,0X75B7,0X643E,
		0X9CC9,0X8D40,0XBFDB,0XAE52,0XDAED,0XCB64,0XF9FF,0XE876,
		0X2102,0X308B,0X0210,0X1399,0X6726,0X76AF,0X4434,0X55BD,
		0XAD4A,0XBCC3,0X8E58,0X9FD1,0XEB6E,0XFAE7,0XC87C,0XD9F5,
		0X3183,0X200A,0X1291,0X0318,0X77A7,0X662E,0X54B5,0X453C,
		0XBDCB,0XAC42,0X9ED9,0X8F50,0XFBEF,0XEA66,0XD8FD,0XC974,
		0X4204,0X538D,0X6116,0X709F,0X0420,0X15A9,0X2732,0X36BB,
		0XCE4C,0XDFC5,0XED5E,0XFCD7,0X8868,0X99E1,0XAB7A,0XBAF3,
		0X5285,0X430C,0X7197,0X601E,0X14A1,0X0528,0X37B3,0X263A,
		0XDECD,0XCF44,0XFDDF,0XEC56,0X98E9,0X8960,0XBBFB,0XAA72,
		0X6306,0X728F,0X4014,0X519D,0X2522,0X34AB,0X0630,0X17B9,
		0XEF4E,0XFEC7,0XCC5C,0XDDD5,0XA96A,0XB8E3,0X8A78,0X9BF1,
		0X7387,0X620E,0X5095,0X411C,0X35A3,0X242A,0X16B1,0X0738,
		0XFFCF,0XEE46,0XDCDD,0XCD54,0XB9EB,0XA862,0X9AF9,0X8B70,
		0X8408,0X9581,0XA71A,0XB693,0XC22C,0XD3A5,0XE13E,0XF0B7,
		0X0840,0X19C9,0X2B52,0X3ADB,0X4E64,0X5FED,0X6D76,0X7CFF,
		0X9489,0X8500,0XB79B,0XA612,0XD2AD,0XC324,0XF1BF,0XE036,
		0X18C1,0X0948,0X3BD3,0X2A5A,0X5EE5,0X4F6C,0X7DF7,0X6C7E,
		0XA50A,0XB483,0X8618,0X9791,0XE32E,0XF2A7,0XC03C,0XD1B5,
		0X2942,0X38CB,0X0A50,0X1BD9,0X6F66,0X7EEF,0X4C74,0X5DFD,
		0XB58B,0XA402,0X9699,0X8710,0XF3AF,0XE226,0XD0BD,0XC134,
		0X39C3,0X284A,0X1AD1,0X0B58,0X7FE7,0X6E6E,0X5CF5,0X4D7C,
		0XC60C,0XD785,0XE51E,0XF497,0X8028,0X91A1,0XA33A,0XB2B3,
		0X4A44,0X5BCD,0X6956,0X78DF,0X0C60,0X1DE9,0X2F72,0X3EFB,
		0XD68D,0XC704,0XF59F,0XE416,0X90A9,0X8120,0XB3BB,0XA232,
		0X5AC5,0X4B4C,0X79D7,0X685E,0X1CE1,0X0D68,0X3FF3,0X2E7A,
		0XE70E,0XF687,0XC41C,0XD595,0XA12A,0XB0A3,0X8238,0X93B1,
		0X6B46,0X7ACF,0X4854,0X59DD,0X2D62,0X3CEB,0X0E70,0X1FF9,
		0XF78F,0XE606,0XD49D,0XC514,0XB1AB,0XA022,0X92B9,0X8330,
		0X7BC7,0X6A4E,0X58D5,0X495C,0X3DE3,0X2C6A,0X1EF1,0X0F78,
};


uint16_t GetCrc16(const uint8_t *pData,int nLength)
{
	uint16_t fcs=0xffff;//initialization
	while(nLength>0){
		fcs=(fcs>>8)^crctab16[(fcs^*pData)&0xff];
		nLength--;
		pData++;
	}
	return~fcs;//negated
}

void parse_login_packet(Packet_t * packet, Vehicle_info_t *vehicle)
{
	uint16_t crc ;
	int imei_indx = 1 ;
	printf("login packet\n");

	memset(vehicle->imei, 0, sizeof(vehicle->imei));
	memcpy(vehicle->imei, "_", 1);
	vehicle->imei[imei_indx++]= packet->src[2] + 48;

	printf("imei hex %x :", packet->src[2]);
	for(int ii=3; ii<=9; ii++)
	{
			printf("%x ", packet->src[ii]);
			vehicle->imei[imei_indx++] = 48+((0x0f & (packet->src[ii])>>4));
			vehicle->imei[imei_indx++] = 48+(0x0f & (packet->src[ii]));
	}
	printf("\n");
	printf("login packet : imei %s \n", vehicle->imei );

	packet->resp_packet[0] = 0x78;               //start byte
	packet->resp_packet[1] = 0x78;		         //start byte
	packet->resp_packet[2] = 5 ;                 // length
	packet->resp_packet[3] = packet->src[1];     //protocol number
	packet->resp_packet[4] = packet->src[10];    //serial number
	packet->resp_packet[5] = packet->src[11];    //serial number

	crc = GetCrc16(&packet->resp_packet[2], 4) ;

	packet->resp_packet[6] = (uint8_t)(crc >> 8) ;      //crc
	packet->resp_packet[7] = (uint8_t)(0x00ff & crc) ;  //crc

	packet->resp_packet[8] = 0x0d;			     //stop byte
	packet->resp_packet[9] = 0x0a;			     //stop byte

}
void parse_hartbit_packet(Packet_t * packet, Vehicle_info_t *vehicle)
{


	if(packet->src[2] & (1<<1))					// packet->src[2] terminal information
	{
		vehicle->sensor = (1<<1);
		printf("engine on \n");
	}else 	printf("engine off \n");

	if(packet->src[2] & (1<<7))					// packet->src[2] terminal information
	{
		vehicle->sensor = (1<<7);
		printf("Oil and electricity disconnected \n");

	}else 	printf("Oil and electricity connected \n");


	uint16_t crc ;
	packet->resp_packet[0] = 0x78;			    //start byte
	packet->resp_packet[1] = 0x78;			    //start byte
	packet->resp_packet[2] = 5 ;			    //length
	packet->resp_packet[3] = packet->src[1];	//protocol number
	packet->resp_packet[4] = packet->src[7];	//serial number
	packet->resp_packet[5] = packet->src[8];    //serial number

	crc= GetCrc16(&packet->resp_packet[2], 4) ;

	packet->resp_packet[6] = (uint8_t)(crc >> 8) ;
	packet->resp_packet[7] = (uint8_t)(0x00ff & crc) ;

	packet->resp_packet[8] = 0x0d;    		   //stop byte
	packet->resp_packet[9] = 0x0a;    		   //stop byte

	//  printf("hartbit-packet-resp  \n");
	//  for(int kk=0; kk<10; kk++){  printf("%x ", resp_packet[kk]) ; }  printf("\n");
}
void parse_location_packet(Packet_t * packet, Vehicle_info_t *vehicle)
{
  	double lat_f, lon_f ;
    int lat_int, long_int ;

    uint16_t cal_crc ;
    uint16_t rcv_crc ;

	printf("time hex : ");	for(int i=0; i<6; i++){ printf("%x ", packet->src[2+i]) ; }		printf("\n");

    struct tm t = {0};  // Initalize to all 0's
    memset(&t, 0, sizeof(tm)); // Initalize to all 0's
    t.tm_year = 100+packet->src[2];  // This is year-1900, so 112 = 2012
    t.tm_mon = packet->src[3] - 1;
    t.tm_mday = packet->src[4];
    t.tm_hour = packet->src[5];
    t.tm_min = packet->src[6];
    t.tm_sec = packet->src[7];

    time_t time_epoch = mktime(&t);
    vehicle->time = (long)time_epoch;

    printf("TIME : %u \n", vehicle->time );

  	//memcpy(vehicle->course,  &packet->src[18], 2);
    vehicle->sat_view = packet->src[8];

    cal_crc = GetCrc16(&packet->src[0], 30) ;
    rcv_crc  = (0xff00 & (packet->src[30] << 8)) ;
    rcv_crc  |= (0x00ff &  packet->src[31]);

    printf("location packet rvc_crc %d  and  cal_crc  %d\n", rcv_crc , cal_crc);

    if( rcv_crc == cal_crc)
    {
    	vehicle->speed = packet->src[17];

    	lat_int =  (0xff000000  &  (packet->src[9] << 24)) ;
    	lat_int |= (0x00ff0000  &  (packet->src[10] << 16)) ;
    	lat_int |= (0x0000ff00  &  (packet->src[11] << 8)) ;
    	lat_int |= (0x000000ff  &  (packet->src[12] )) ;

    	long_int =  (0xff000000  &  (packet->src[13] << 24)) ;
    	long_int |= (0x00ff0000  &  (packet->src[14] << 16)) ;
    	long_int |= (0x0000ff00  &  (packet->src[15] << 8)) ;
    	long_int |= (0x000000ff  &  packet->src[16] ) ;

    	lat_f = lat_int ;
    	lon_f = long_int;

    	lat_f /= 1800000 ;
    	lon_f /= 1800000 ;

    	//printf("latitude %.6f  longitude %.6f  speed %d  \n", lat_f, lon_f,  speed);
    	sprintf((char*)vehicle->latitude, "%f", lat_f);
    	sprintf((char*)vehicle->longitude, "%f", lon_f);

        printf("latitudef %.6f  longitudef %.6f  \n", lat_f, lon_f);
        printf("speed %d \n", vehicle->speed);

        printf("location packet :  lat %.6f  lon %.6f \n", vehicle->latitude,  vehicle->longitude );
    }

 //   printf("location packet : time  "); for(int i=0; i<6; i++) { printf("%x  ",  vehicle->time[i]); } printf("\n");

}
void parse_alarm_pacet(Packet_t * packet, Vehicle_info_t *vehicle)
{
    double lat_f, lon_f ;
    int lat_int, long_int ;

    uint16_t rvc_crc ;
	uint16_t cal_crc ;

    struct tm t = {0};  // Initalize to all 0's
    memset(&t, 0, sizeof(tm)); // Initalize to all 0's
    t.tm_year = 100+packet->src[2];  // This is year-1900, so 112 = 2012
    t.tm_mon = packet->src[3] - 1;
    t.tm_mday = packet->src[4];
    t.tm_hour = packet->src[5];
    t.tm_min = packet->src[6];
    t.tm_sec = packet->src[7];

    time_t time_epoch = mktime(&t);
    vehicle->time = (long)time_epoch;

	printf("time hex : ");	for(int i=0; i<6; i++){ printf("%x ", packet->src[2+i]) ; }		printf("\n");
    printf("TIME : %u \n", vehicle->time );

    vehicle->sat_view =  (0x0f & packet->src[8]);



//  	memcpy(vehicle->course,  &packet->src[18], 2);
//
//  	vehicle->sat_view[0] = packet->src[8];;
//  	vehicle->speed[0] =  packet->src[17];
//
//  	vehicle->course[0] =  packet->src[18];
// 		vehicle->course[1] =  packet->src[19];

 	rvc_crc   = (0xff00 & (packet->src[36] << 8)) ;
 	rvc_crc  |= (0x00ff & packet->src[37]);

 	cal_crc = GetCrc16(&packet->src[0], 36) ;

    printf("alarm packet : rvc_crc %d  and  cal_crc  %d\n", rvc_crc, cal_crc);

	if(rvc_crc == cal_crc)
	{
    	vehicle->speed = packet->src[17];

    	lat_int =  (0xff000000  &  (packet->src[9] << 24)) ;
    	lat_int |= (0x00ff0000  &  (packet->src[10] << 16)) ;
    	lat_int |= (0x0000ff00  &  (packet->src[11] << 8)) ;
    	lat_int |= (0x000000ff  &  (packet->src[12] )) ;

    	long_int =  (0xff000000  &  (packet->src[13] << 24)) ;
    	long_int |= (0x00ff0000  &  (packet->src[14] << 16)) ;
    	long_int |= (0x0000ff00  &  (packet->src[15] << 8)) ;
    	long_int |= (0x000000ff  &  packet->src[16] ) ;

    	lat_f = lat_int ;
    	lon_f = long_int;

    	lat_f /= 1800000 ;
    	lon_f /= 1800000 ;

    	//printf("latitude %.6f  longitude %.6f  speed %d  \n", lat_f, lon_f,  speed);
    	sprintf((char*)vehicle->latitude, "%f", lat_f);
    	sprintf((char*)vehicle->longitude, "%f", lon_f);

        printf("latitudef %.6f  longitudef %.6f  \n", lat_f, lon_f);
        printf("speed %d \n", vehicle->speed);

        printf("location packet :  lat %.6f  lon %.6f \n", vehicle->latitude,  vehicle->longitude );
	}

	vehicle->device_voltage_level = packet->src[30] ;
	vehicle->gsm_strength = packet->src[31] ;
}

void handle_connection(int sockfd)
{
	Vehicle_info_t vehicle;
	Packet_t packet;

    uint8_t buffer[10240];

	//mongocxx::client& m_client;
	std::string m_dbName;
	std::string m_collectionName;
	mongocxx::database v_db;
	mongocxx::collection _collection;
	mongodbm::Mongo mongo ;


    auto cc = mongodbm::MongoInstance::GetInstance()->getClientFromPool();
	mongocxx::client &client = *cc ;
	v_db =  client["vts-db"];

    memset(vehicle.imei, 0, sizeof(vehicle.imei));
    memset(vehicle.latitude, 0, sizeof(vehicle.latitude));
    memset(vehicle.longitude, 0, sizeof(vehicle.longitude));
    memset(vehicle.data_status, 0, sizeof(vehicle.data_status));
    memset(vehicle.hdop, 0, sizeof(vehicle.hdop));
    memset(vehicle.pdop, 0, sizeof(vehicle.pdop));




    int mongo_update = 0 ;

    while(recv(sockfd, buffer, 10240, 0) > 0)
    {
        for(int i=0;;i++)
        {
        	printf("%x  ", buffer[i]);
        	if((buffer[i]==0x0a && buffer[i-1]==0x0d) || (i >= 1023)) 	break;
        }
        printf("\n");

    	for(int idx=0; idx<10240; idx++)
    	{
    		if(buffer[idx]==0x78 && buffer[idx+1]==0x78)
    		{
    			idx += 2 ;
    			packet.src = &buffer[idx];

    	        switch(buffer[idx+1])
    	        {
    	        	case PROTOCOL_NO_LOGIN:
    	        		parse_login_packet(&packet, &vehicle);
    	        		{
    	        			string lat;
    	        			string lon;
    	        			_collection = v_db[(char*)vehicle.imei];
    	        			auto opts = mongocxx::options::find{};
    	        			opts.sort(make_document(kvp("_id", -1)));
    	        			opts.limit(1);
    	        			auto cursor = _collection.find({}, opts);
    	        			for (auto&& doc : cursor)
    	        			{
    	        			//	bsoncxx::document::element e = doc["latitude"];
    	        				lat =  doc["latitude"].get_string().value.to_string() ;
    	        				lon =  doc["longitude"].get_string().value.to_string() ;
    	        				vehicle.speed = doc["speed"].get_int32().value ;
    	        			//uint64_t value = doc["time"].get_int64().value;
    	        				std::cout << "last-lat: " <<lat << "    last-lon:" << lon << std::endl;
        	        			strcpy(vehicle.latitude, lat.c_str());
        	        			strcpy(vehicle.longitude, lon.c_str());
           	        			std::cout << "lat: " <<vehicle.latitude <<  " lon:" << vehicle.longitude << "   speed"  << vehicle.speed << std::endl ;
    	        			}
    	        		}
     	        		send(sockfd, (void*)packet.resp_packet, 10, MSG_NOSIGNAL);
    	        		break;
    	        	case PROTOCOL_HEARTBIT:
    	        		printf("hartbit-packet\n");
    	        		parse_hartbit_packet(&packet, &vehicle);
    	        		send(sockfd, (void*)packet.resp_packet, 10, MSG_NOSIGNAL);
    	        		mongo_update  = 1 ;
    	        		break;
    	        	case PROTOCOL_LOCATION:
    	        		//printf("location-packet\n");
    	        		parse_location_packet(&packet, &vehicle);
    	          		mongo_update  = 1 ;
    	        		break;
    	        	case PROTOCOL_ALARM:
    	        		printf("alarm-packet\n");
    	        		parse_alarm_pacet(&packet, &vehicle);
    	        		mongo_update  = 1 ;
    	        		break;
    	        	default:
    	        		break;
    	        }

    	        if(mongo_update == 1)
    	        {
        	    	auto insert_one_result = _collection.insert_one(make_document(
        	    			kvp("imei", vehicle.imei),
        	    			kvp("time",  vehicle.time),
        	    			kvp("status", vehicle.data_status),
							kvp("latitude", vehicle.latitude),
							kvp("longitude", vehicle.longitude),
							kvp("speed", vehicle.speed),
							kvp("fuel", vehicle.fuel),
        	    			kvp("temp", vehicle.temp),
        	    			kvp("gsmstrength", vehicle.gsm_strength),
							kvp("satview", vehicle.sat_view),
							kvp("hdop", vehicle.hdop),
							kvp("pdop", vehicle.pdop),
        	    			kvp("course", vehicle.course),
							kvp("sensor", vehicle.sensor)
        	    		));

 //   	        	kvp("time", stol(speed, nullptr, 10))
    	        }
    		}
    	}
        memset(buffer, 0, 10240);
    }
    close(sockfd);
    printf("client closed \n");
    return;
}

void SServer::create(int port){
    int sockfd;
    struct sockaddr_in serv_addr;

    mongodbm::MongoInstance::GetInstance()->createPool("mongodb://localhost:27017");
   // mongodbm::MongoDBInstance::GetInstance()->createPool(mongodb_uri_path);


    //Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("Error: Failed to initialize socket.\n");
        exit(1);
    }

    //Bind socket
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_port          = htons(port);
    serv_addr.sin_addr.s_addr   = INADDR_ANY;
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error: Failed to bind socket to address.\n");
        exit(1);
    }
    while(1)
    {
        int newsockfd = -1;
        struct sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);

        cout<<"waiting for socket .."<<endl;

        listen(sockfd, 5);

        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if(newsockfd < 0)
        {
            perror("Error: Failed to connect to incoming connection.\n");
        }

        std::thread t1 (handle_connection, newsockfd);
        t1.detach();
    }
    return;
}











































