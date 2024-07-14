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

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

#define PROTOCOL_NO_LOGIN       	0x01
#define PROTOCOL_HEARTBIT_LOGIN 	0x13
#define PROTOCOL_LOCATION 			0x12

typedef struct{
	uint8_t *content;
	uint16_t len;
}Message_t;
typedef struct{
	uint8_t start_bits[2];
	uint8_t packet_length;
	uint8_t protocol_number;

	Message_t  message ;

	uint8_t info_serial_no[2];
	uint8_t error_check[2];
	uint8_t stop_byts[2];

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
























void handle_login(const uint8_t * packet, int sockfd)
{
	uint8_t resp_pkt[32];
	uint8_t imei[28] ;
	uint8_t information_serial_num[3];
	int packet_length = *packet ;

	uint16_t error_check  = (0xff00 & (packet[packet_length-1] << 8)) ;
	error_check  |= (0x00ff & packet[packet_length]);


	memset(imei, 0, sizeof(imei));

	printf("protocol login . packet : ");
	for(int i=0; i < packet_length; i++)
	{
		printf("%x  ", packet[i+1]);
	}
    printf("\n");


	printf("for checksum  : ");
	for(int i=0; i < packet_length-1; i++)
	{
		printf("%x  ", packet[i]);
	}
    printf("\n");



	uint8_t imei_indx = 0 ;
	memset(imei, 0, sizeof(imei));
	imei[imei_indx++]= packet[2] + 48;
	for(int i=1; i<8; i++)
	{
		imei[imei_indx++] = 48+((0xF0 & packet[i+2])>>4);
		imei[imei_indx++] = 48+(0x0F & packet[i+2]);
	}

	information_serial_num[0]=packet[10];
	information_serial_num[1]=packet[11];
	information_serial_num[2]= 0 ;

	printf("imei %s \n", imei);
	printf("information serial number  %s \n", information_serial_num);
	printf("error_check %d\n", error_check);
	printf("est error code %d \n", GetCrc16(packet, 12));


	memset(resp_pkt, 0, sizeof(resp_pkt));
//	resp_pkt[0] = 0x78;
//	resp_pkt[1] = 0x78;
//	resp_pkt[2] = 5 ;
//	resp_pkt[3] = packet[1];
//	resp_pkt[4] = information_serial_num[0];
//	resp_pkt[5] = information_serial_num[1];
//
//	uint16_t resp_crc = GetCrc16(&resp_pkt[2], 4) ;
//
//	resp_pkt[6] = (uint8_t)(resp_crc >> 8) ;
//	resp_pkt[7] = (uint8_t)(0x00ff & resp_crc) ;
//
//	resp_pkt[8] = 0x0d;
//	resp_pkt[9] = 0x0a;

//	printf("resp packet crc %d ", resp_crc);
//	printf("resp_packet packet : ");
	for(int i=0; i < packet_length; i++)
	{
		printf("%x  ", resp_pkt[i]);
	}
    printf("\n");

	//send(sockfd, (void*)sesp_pkt, strlen(sesp_pkt), MSG_NOSIGNAL);


}
void handle_heartbit(const uint8_t * packet, int sockfd)
{
	//uint8_t packet_length = packet[0];
	uint8_t protocol_number = packet[1];
	//const uint8_t *information_content = &packet[2];
	const uint8_t *serial_numer = &packet[7];
	//const uint8_t *error_check = &packet[9];


	printf("hartbit-packet\n");


	uint8_t resp_packet[16];
	memset(resp_packet, 0, sizeof(resp_packet));
	resp_packet[0] = 0x78;
	resp_packet[1] = 0x78;
	resp_packet[2] = 5 ;
	resp_packet[3] = protocol_number;
	resp_packet[4] = *serial_numer;
	resp_packet[5] = (*serial_numer+1);

	uint16_t resp_crc = GetCrc16(&resp_packet[2], 4) ;
	resp_packet[6] = (uint8_t)(resp_crc >> 8) ;
	resp_packet[7] = (uint8_t)(0x00ff & resp_crc) ;

	resp_packet[8] = 0x0d;
	resp_packet[9] = 0x0a;


	send(sockfd, (void*)resp_packet, 10, MSG_NOSIGNAL);

}
void handle_location_msg(const uint8_t * packet, int sockfd)
{
	uint8_t date[7];
	//uint8_t gps_quality=0;
	uint8_t latitude[4];
	uint8_t longitude[4];
	uint8_t speed ;
	uint8_t course[2] ;
	uint8_t serial_number[2];
	uint8_t error_check[2];

	uint32_t latitude_l;
	uint32_t longitude_l;



	//uint8_t packet_length = packet[0];
	//uint8_t protocol_number = packet[1];
	//const uint8_t *information_content = &packet[2];
	//const uint8_t *serial_numer = &packet[7];
	//const uint8_t *error_check = &packet[9];
	memcpy(date,  &packet[2], 6);
	//gps_quality = packet[8] ;

	memset(latitude,  0, sizeof(latitude));
	memset(longitude,  0, sizeof(longitude));

	memcpy(latitude,  &packet[9], 4);
	memcpy(longitude,  &packet[13], 4);
	//speed = packet[17];

	memcpy(course, &packet[18], 2);
	memcpy(serial_number, &packet[28], 2);
	memcpy(error_check,  &packet[30], 2 ) ;

	uint16_t resp_crc  = (0xff00 & (error_check[0] << 8)) ;
	resp_crc  |= (0x00ff & error_check[1]);

	uint16_t esp_esp_crc = GetCrc16(&packet[0], 30) ;

	printf("location-packet\n");
	printf("crc get %d  and  estimated crc %d\n", resp_crc, esp_esp_crc);

	if(esp_esp_crc == resp_crc)
	{
		latitude_l = (0xff000000  &  (packet[9] << 24)) ;
		latitude_l |= (0x00ff0000  &  (packet[10] << 16)) ;
		latitude_l |= (0x0000ff00  &  (packet[11] << 8)) ;
		latitude_l |= (0x000000ff  &  packet[12] ) ;



		longitude_l = (0xff000000  &  (packet[13] << 24)) ;
		longitude_l |= (0x00ff0000  &  (packet[14] << 16)) ;
		longitude_l |= (0x0000ff00  &  (packet[15] << 8)) ;
		longitude_l |= (0x000000ff  &  packet[16] ) ;

		float lat_f = latitude_l ;
		float lon_f = longitude_l;

		lat_f /= 1800000 ;

		lon_f /= 1800000 ;

		speed = packet[17];

		printf("latitude %.6f  longitude %.6f  speed %d  \n", lat_f, lon_f,  speed);
	}
}













void handle_connection(int sockfd)
{
    uint8_t buffer[10240];
    uint8_t resp_packet[32];


	uint8_t imei[32];
	uint8_t latitude[8];
	uint8_t longitude[8];
	uint8_t time[8];
	uint8_t course[3];
	uint8_t temp[3];
	uint8_t fuel[4];
	uint8_t sensor ; //engline door
	uint8_t gps_satellites_no;
	uint8_t speed;

	uint8_t crc[2];



	//Packet_t  packet;
    uint8_t * pkt_start_ptr ;
//	char latitude[14];
//	char longitude[14];
//	char speed[50];
//
//	char vehicle[52];
//
//	int flag = 0, index = 0  ;

 //   char terminal_id[32] = { 0 };
 //   uint8_t packet[28] ; //={ 0 };
 //   char * bufferPtr = buffer ;

//    mongocxx::instance instance{};  // This should be done only once.
//    mongocxx::uri uri("mongodb://localhost:27017");
//    mongocxx::client client(uri);
//    mongocxx::database db =  client["vtsDB"];


   // std::string response = "received ...\n";
   // const char* responseChar = response.c_str();
    memset(buffer, 0, 10240);
    memset(resp_packet, 0, sizeof(resp_packet));

    memset(imei, 0, sizeof(imei));
    memset(latitude, 0, sizeof(latitude));
    memset(longitude, 0, sizeof(longitude));
    memset(time, 0, sizeof(time));
    memset(course, 0, sizeof(course));
    memset(temp, 0, sizeof(temp));
    memset(fuel, 0, sizeof(imei));
    memset(imei, 0, sizeof(imei));
    memset(crc, 0, sizeof(crc));


    while(recv(sockfd, buffer, 10240, 0) > 0)
    {
        for(int i=0;; i++)
        {
        	printf("%x  ", buffer[i]);
        	if(buffer[i]==0x0a && buffer[i-1]==0x0d)	break;
        }
        printf("\n");

    	for(int i=0; i<10240; i++)
    	{
    		if(buffer[i]==0x78 && buffer[i+1]==0x78)
    		{
    			pkt_start_ptr = &buffer[i+2];
    	        switch(buffer[i+3])
    	        {
    	        	case PROTOCOL_NO_LOGIN:
    	        		handle_login(pkt_start_ptr, sockfd);
    	        		{
        	        		resp_packet[0] = 0x78;
        	        		resp_packet[1] = 0x78;
        	        		resp_packet[2] = 5 ;
        	        		resp_packet[3] = buffer[i+3];
        	        		resp_packet[4] = buffer[i+12];
        	        		resp_packet[5] = buffer[i+13];

        	        		uint16_t resp_crc = GetCrc16(&resp_packet[2], 4) ;

        	        		resp_packet[6] = (uint8_t)(resp_crc >> 8) ;
        	        		resp_packet[7] = (uint8_t)(0x00ff & resp_crc) ;

        	        		resp_packet[8] = 0x0d;
        	        		resp_packet[9] = 0x0a;
    	        		}
    	        		//	printf("resp packet crc %d ", resp_crc);
    	        		printf("login packet :  ");
    	        		send(sockfd, (void*)resp_packet, 10, MSG_NOSIGNAL);
    	        		break;
    	        	case PROTOCOL_HEARTBIT_LOGIN:
    	        		//handle_heartbit(pkt_start_ptr, sockfd);
    	        		printf("hartbit-packet\n");
    	        		//memset(resp_packet, 0, sizeof(resp_packet));
    	        		{
           	        		uint16_t resp_crc;
        	        		resp_packet[0] = 0x78;
        	        		resp_packet[1] = 0x78;
        	        		resp_packet[2] = 5 ;
        	        		resp_packet[3] = buffer[i+3];
        	        		resp_packet[4] = buffer[i+9];
        	        		resp_packet[5] = buffer[i+10];

        	        		resp_crc = GetCrc16(&resp_packet[2], 4) ;
        	        		resp_packet[6] = (uint8_t)(resp_crc >> 8) ;
        	        		resp_packet[7] = (uint8_t)(0x00ff & resp_crc) ;

        	        		resp_packet[8] = 0x0d;
        	        		resp_packet[9] = 0x0a;
    	        		}
    	        		send(sockfd, (void*)resp_packet, 10, MSG_NOSIGNAL);
    	        		break;
    	        	case PROTOCOL_LOCATION:
    	          		memcpy(time,  &buffer[i+4], 6);
    	          		gps_satellites_no = buffer[i+10];
    	          		memcpy(latitude,  &buffer[i+11], 4);
    	          		memcpy(longitude,  &buffer[i+15], 4);
    	          		speed = buffer[i+19];
    	          		memcpy(course,  &buffer[i+20], 2);
    	          		memcpy(crc,  &buffer[32], 2 ) ;
    	          		{
        	        		float lat_f, lon_f ;
        	        		int lat_int, long_int ;

        	        		uint16_t cal_crc = GetCrc16(&buffer[2], 30) ;
        	        		uint16_t rvc_crc  = (0xff00 & (crc[0] << 8)) ;

        	        		rvc_crc  |= (0x00ff & crc[1]);

        	        		printf("rvc_crc %d  and  cal_crc  %d\n", rvc_crc, cal_crc);

        	        		if(rvc_crc == cal_crc)
        	        		{
        	        			lat_int =  (0xff000000  &  (buffer[i+11] << 24)) ;
        	        			lat_int |= (0x00ff0000  &  (buffer[i+12] << 16)) ;
        	        			lat_int |= (0x0000ff00  &  (buffer[i+13] << 8)) ;
        	        			lat_int |= (0x000000ff  &  (buffer[i+14] )) ;

        	        			long_int =  (0xff000000  &  (buffer[13] << 24)) ;
        	        			long_int |= (0x00ff0000  &  (buffer[14] << 16)) ;
        	        			long_int |= (0x0000ff00  &  (buffer[15] << 8)) ;
        	        			long_int |= (0x000000ff  &  buffer[16] ) ;

        	        			lat_f = lat_int ;
        	        			lon_f = long_int;

        	        			lat_f /= 1800000 ;
        	        			lon_f /= 1800000 ;

        	        			printf("latitude %.6f  longitude %.6f  speed %d  \n", lat_f, lon_f,  speed);
        	        		}
    	          		}
       	        		//handle_location_msg(pkt_start_ptr, sockfd);
    	        		break;
    	        	default:
    	        		break;
    	        }
    		}
    	}
        //bzero(buffer, 10240);
        memset(buffer, 0, 10240);

    }
    close(sockfd);
    return;
}

void SServer::create(int port){
    int sockfd;
    struct sockaddr_in serv_addr;

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











































