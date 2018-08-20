package com.example.jay.googlemaprouter.Bluetooth;

import android.app.Activity;
import android.bluetooth.BluetoothSocket;
import android.graphics.Color;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.jay.googlemaprouter.Map.mapNode;
import com.example.jay.googlemaprouter.R;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.Circle;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

import static java.lang.Double.parseDouble;
import static java.lang.Float.parseFloat;

/**
 * Created by jay on 10/22/2017.
 */

public class BluetoothCommunicate extends Thread{
    private static BluetoothSocket mmSocket;
    private  InputStream mmInStream;
    private  OutputStream mmOutStream;
    private byte[] buffer = new byte[12];
    private TextView compassData;
    private Activity mParent;
    private GoogleMap mMap;
    private static GPSData currentPOS;
    private boolean closeFlag = true;
    private Circle circle;
    private  int count = 0;
    public BluetoothCommunicate()
    {
        //currentPOS =    new GPSData(new LatLng(0.0,0.0),0);
    }
    public BluetoothCommunicate(BluetoothSocket socket,Activity parentActivity,GoogleMap parentMap) {
        mmSocket = socket;
        mMap = parentMap;
        mParent = parentActivity;
        compassData = (TextView)mParent.findViewById(R.id.CompassText);
        currentPOS =  new GPSData(new LatLng(0.0,0.0),0);

        circle = mMap.addCircle(new CircleOptions()
                .strokeWidth(4)
                .radius(4)
                .center(new LatLng(37.334610,-121.880783))
                .strokeColor(Color.parseColor("#B20000"))
                .fillColor(Color.parseColor("#FF1919")));
        //    mMap.addMarker(new MarkerOptions().position(currentPOS.latLng).title("Marker in SJSU").icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_BLUE)));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(new LatLng(37.334610,-121.880783), 18));
    }

    public void setMmSocket(BluetoothSocket socket) {
        mmSocket = socket;
    }

    public LatLng getcurrentPOS()
    {
        Log.i("in thread",currentPOS.latLng+"");
        return  currentPOS.latLng;
    }
    public void  run()
    {

        while(closeFlag)
        {
            try{
                Thread.sleep(100);
            }catch (Exception e){}
            final GPSData gps;
            InputStream inputStream =  null;
            // Log.i("Bluetooth","Start Reading : mmsocket : "+mmSocket.toString());
            if(mmSocket != null) {
                try {
                    inputStream = mmSocket.getInputStream();
                } catch (IOException e) {
                    Log.i("Bluetooth", "Exception received data : " + e);
                }
                gps = readStrToLalLong(inputStream);
                if(gps != null) {
                    if ((gps.latLng.latitude != 0.0) && (gps.latLng.latitude != -0.0) && (gps.latLng.longitude != 0.0) && (gps.latLng.longitude != -0.0)) {
                        currentPOS = gps;
                     //   Log.i("Current Data", currentPOS.latLng.latitude + " " + currentPOS.latLng.longitude + " " + currentPOS.headingAngle);
                    }
                }
                mParent.runOnUiThread((new Runnable() {
                    @Override
                    public void run() {

                        if(count ==10)
                        if ((currentPOS.latLng.latitude != 0.0) && (currentPOS.latLng.latitude != -0.0)
                                && (currentPOS.latLng.longitude != -0.0) && currentPOS.latLng.longitude != 0.0) {
                            circle.remove();
                        //    circle.setCenter(currentPOS.latLng);
                               circle =  mMap.addCircle(new CircleOptions()
                                        .strokeWidth(4)
                                        .radius(4)
                                        .center(currentPOS.latLng)
                                        .strokeColor(Color.parseColor("#B20000"))
                                        .fillColor(Color.parseColor("#FF1919")));
                            count = 0;
                        }
                        count ++;
//                                    CameraPosition currentPlace = new CameraPosition.Builder()
//                                            .target(currentPOS.latLng)
//                                            .bearing(currentPOS.headingAngle)..build();
//                                    mMap.moveCamera(CameraUpdateFactory.newCameraPosition(currentPlace));
                        compassData.setText(gps.headingAngle + "");
                        //   Toast.makeText(mParent,"Not connected to Alpha!",Toast.LENGTH_LONG).show();
                    }
                }
                ));
            }

        }

    }



    public GPSData readStrToLalLong(InputStream inputStream)
    {

        //   Log.i("Ble Communication","Inside read 1");
        String in_str;
        float angle = 0;
        LatLng latLng;
        double curr_longitude = 0.0;
        double curr_latitude = 0.0;

        do
        {
            try
            {
                inputStream.read(buffer,0,1);
            }
            catch (Exception e)
            {
                Log.e("Ble Read","Exception: # "+e);
                //return new GPSData(new LatLng(0.0,0.0),0);
            }
            in_str = new String(buffer);
            //      Log.i("Bluetooth","received data : waiting For # "+in_str.substring(0,1));
        }while(!in_str.substring(0,1).equals("#"));

        in_str = "";
        String str;
        do {
            try
            {
                inputStream.read(buffer,0,1);
            }
            catch (Exception e)
            {
                Log.e("Ble Read","Exception: @"+e);
                // return new GPSData(new LatLng(0.0,0.0),0);
            }
            str = new String(buffer);
            in_str= in_str.concat(str.substring(0,1));
            //    Log.i("Bluetooth","received data : waiting For @ "+str.substring(0,1));
        }while(!str.substring(0,1).equals("@"));

        //   Log.i("Bluetooth Read","received data : Latitude "+in_str.substring(0,in_str.length()-1));
        try {
            curr_latitude = parseDouble(in_str.substring(0, in_str.length() - 1));
        }catch (Exception e){}
        in_str = "";
        do {

            try
            {
                inputStream.read(buffer,0,1);
            }
            catch (Exception e)
            {
                Log.e("Ble Read","Exception: *"+e);
                //    return new GPSData(new LatLng(0.0,0.0),0);
            }

            str = new String(buffer);
            in_str = in_str.concat(str.substring(0,1));
            //     Log.i("Bluetooth","received data : waiting For * "+str.substring(0,1));
        }while(!str.substring(0,1).equals("*"));

        try {
            curr_longitude = parseDouble(in_str.substring(0, in_str.length() - 1));
        }catch (Exception e){}
        //   Log.i("Bluetoth Read","Longitude"+curr_longitude);
        in_str = "";
        do {

            try
            {
                inputStream.read(buffer,0,1);
            }
            catch (Exception e)
            {
                Log.e("Ble Read","Exception: "+e);
                //    return new GPSData(new LatLng(0.0,0.0),0);
            }

            str = new String(buffer);
            in_str = in_str.concat(str.substring(0,1));
            //  Log.i("Bluetooth","Waiting for new Line"+str.substring(0,1));
        }while(!str.substring(0,1).equals("\n"));

        //    Log.i("Ble Communication","Inside read 0");
        try {
            angle = parseFloat(in_str);
        }catch (Exception e){}

     //   Log.i("Bluetoth Read","Heading Angle "+angle + mmSocket.toString());

        latLng = new LatLng(curr_latitude,curr_longitude);

        GPSData gpsData = new GPSData(latLng,angle);

        return  gpsData;
    }

    public void write(byte[] bytes) {
        try {
            mmOutStream = mmSocket.getOutputStream();
            mmOutStream.write(bytes);
            Log.i("Bluetooth","Transmitted on "+mmSocket.toString());
        } catch (IOException e) {
            Log.i("Bluetooth","Exception Write data : "+e);
        }
    }

    public void cancel()
    {
        closeFlag = false;
    }
}
