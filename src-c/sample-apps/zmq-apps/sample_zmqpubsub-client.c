/*
 * ZMQ PUB/SUB sample program through Edison API
 * Copyright (c) 2014, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 */

/** @file sample_zmqpubsub-client.c

    Sample client program of ZMQ PUB/SUB

 */

#include <stdio.h>
#include <cJSON.h>
#include <stdbool.h>
#include <sys/types.h>
#include "edisonapi.h"
#include "util.h"

/** a callback function to be invoked when it receives any messages for the subscribed topic
 */
void message_callback(char *message, Context context){
    fprintf(stderr,"Message received in Client: %s\n", message);
}

/** a callback function to be invoked when the service is discovered
 */
void callback(void *handle, int32_t error_code, CommClientHandle *commHandle)
{
    if (commHandle != NULL) {
        while (1) {
            commHandle->subscribe("vehicle");
            commHandle->receive(message_callback);
            sleep(2);
        }
    } else {
        puts("\nComm Handle is NULL\n");
    }

}


/** The starting point of sample program
 */
int main(void) {

    void *handle;

	puts("Sample program to test the Edison ZMQ pub/sub plugin !!");
    ServiceQuery *query = (ServiceQuery *) parseServiceDescription("../serviceSpecs/temperatureServiceZMQPUBSUB.json");

    if (query) {
        fprintf(stderr,"query host address %s\n",query->address);
        fprintf(stderr,"query host port %d\n",query->port);
        fprintf(stderr,"query service name %s\n",query->service_name);
	    handle = (void *) discoverServices(query, callback);
	}

	return 0;
}
