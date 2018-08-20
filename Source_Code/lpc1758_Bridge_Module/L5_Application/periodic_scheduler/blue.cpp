/*
 * blue.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: Kathan Patel
 */

/*

 * blue.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: Kathan Patel
*/

#include "blue.h"
#include "printf_lib.h"


using namespace std;

int longitude_index = 0;
int latitude_index = 0;
int start_stop;
int checkpoint = 0;
double latitude[100] ;
double longitude[100] ;


int validate_store(char c[]){
    int i = 0;
    string temp = "";
    bool lat = false;
    bool longi = false;
    bool chkpnt = false;
    start_stop=-1;

    if (c[i] == '*'){
        i++;
        while(c[i] != '\n'){
			if(c[i] == '1'){
				start_stop = 1;
				return 1;
			}
			else if(c[i] == '0'){ //stop bit received
				start_stop = 0;
            	for(int j = 0; j < 100; j++){ //clearing the array of checkpoints
            		latitude[j] = 0;
            	}
            	latitude_index= 0; //resetting the index for lat
            	for(int j = 0; j < 100; j++){ //clearing the array of checkpoints
            		longitude[j] = 0;
            	}
            	longitude_index= 0; //resetting the index for long
				return 1;
			}
			i++;
        }
    }
    else if( c[i] == '#'){
        i++;
        while( c[i] != '@'){
            temp += c[i];
            i++;
        }
        lat = validate_latitude(temp);
        temp = "";
        i++;
        while( c[i] != '\n'){
            temp += c[i];
            i++;
        }
        longi = validate_longitude(temp);
        temp = "";
        if(lat & longi)
        return 2;
    }
    else if ( c[i] == '$'){
        i++;
        while( c[i] != '\n'){
            temp += c[i];
            i++;
        }
        chkpnt = validate_checkpoint(temp);
        temp = "";
        return 3;
    }
    return 0;
}

/*-----------function to validate LATITUDE------------*/
bool validate_latitude(string temp){
    double lati = atof(temp.c_str());
    if(lati >= -90 && lati <= 90){
        latitude[latitude_index] = lati;
       // u0_dbg_printf("rx_LATITUDE:%f @LATI_idx:%d ", lati, latitude_index);
        latitude_index++;
        return true;
    }
    return false;
}

/*-----------function to validate LONGITUDE------------*/
bool validate_longitude(string temp){
    double longi = atof(temp.c_str());
    if(longi >= -180 && longi <= 180){
        longitude[longitude_index] = longi;
       // u0_dbg_printf("rx_LONGITUDE:%f @LONGI_idx:%d \n", longi, longitude_index);
        longitude_index++;
        return true;
    }
    return false;
}

/*-----------function to validate CHECKPOINTS------------*/
bool validate_checkpoint(string temp){
    int size = temp.size();
    int i = 0;
    int checkpoints = 0;
    if(size == 0) return false;
    switch(size){
    case 3:
        checkpoints = checkpoints + (temp[i] - '0') * 100;
        i++;
        checkpoints = checkpoints + (temp[i] - '0') * 10;
        i++;
        checkpoints = checkpoints + (temp[i] - '0') * 1;
        break;
    case 2:
        checkpoints = checkpoints + (temp[i] - '0') * 10;
        i++;
        checkpoints = checkpoints + (temp[i] - '0') * 1;
        break;
    case 1:
        checkpoints = checkpoints + (temp[i] - '0') * 1;
        break;
    case 0:
        break;
    default:
        return false;
    }
    checkpoint = checkpoints;
    return true;
}

int get_startstop(){
    return start_stop;
}

double get_latitude(int index){
    return latitude[index];
}

double get_longitude(int index){
    return longitude[index];
}

int get_checkpoints(){
    return checkpoint;
}
