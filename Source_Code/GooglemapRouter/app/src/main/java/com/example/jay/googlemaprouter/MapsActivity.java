package com.example.jay.googlemaprouter;

import com.example.jay.googlemaprouter.Bluetooth.*;


import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.Color;
import android.speech.tts.TextToSpeech;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.example.jay.googlemaprouter.Map.MapCommands;
import com.example.jay.googlemaprouter.Map.mapGraph;
import com.example.jay.googlemaprouter.Map.mapNode;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CameraPosition;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Set;


public class MapsActivity extends FragmentActivity implements OnMapReadyCallback,
        GoogleMap.OnMapClickListener,TextToSpeech.OnInitListener{

    boolean flag = true;
    boolean BTConnected = false;
    private GoogleMap mMap;
    BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    BluetoothConnect bt_Thread;
    BluetoothSocket mmSocket;
    BluetoothCommunicate ble_communication;
    Switch bleSwitch;
    TextView compassData;
    LatLng gpsData;
    LatLng destination;
    BluetoothCommunicate ble_write;
    private TextToSpeech myTTS;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
        bluethoot_enable();
        bleSwitch = (Switch) findViewById(R.id.bleSwitch);
        compassData = (TextView)findViewById(R.id.CompassText);
        myTTS=new TextToSpeech(this,this) ;
    }

    public void onInit(int initStatus) {
        //check for successful instantiation

        if (initStatus == TextToSpeech.SUCCESS) {
            if(myTTS.isLanguageAvailable(Locale.US)==TextToSpeech.LANG_AVAILABLE)
                myTTS.setLanguage(Locale.US);
            myTTS.speak("WelCome to Alpha",TextToSpeech.QUEUE_FLUSH,null);
        }
        else if (initStatus == TextToSpeech.ERROR) {
            Toast.makeText(this, "Sorry! Text To Speech failed...", Toast.LENGTH_LONG).show();
        }
    }

    public void bluethoot_enable() {
        if (mBluetoothAdapter == null) {
            Toast.makeText(MapsActivity.this, "Your device does not support Bluetooth", Toast.LENGTH_LONG).show();
        } else if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, 1);
            Toast.makeText(MapsActivity.this, "Bluetooth Enabled", Toast.LENGTH_LONG).show();
        } else
            Toast.makeText(MapsActivity.this, "Bluetooth is already on", Toast.LENGTH_LONG).show();
    }

    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        while (!mBluetoothAdapter.isEnabled()) ;
        connect_alpha();

        gpsData = new LatLng(37.334610,-121.880783);
        destination = new LatLng(0,0);

        initListeners();
    }


    public void goStop(View view) {
        if (bt_Thread != null) {
            //Toast.makeText(MapsActivity.this,"Thread hai",Toast.LENGTH_LONG).show();
            mmSocket = bt_Thread.get_socket();
            ble_communication.setMmSocket(mmSocket);
        }
        if (!mBluetoothAdapter.isEnabled()) {
            Toast.makeText(MapsActivity.this, "Please enable Bluetooth", Toast.LENGTH_LONG).show();
        } else if (mmSocket == null || (!mmSocket.isConnected())) {
            bleSwitch.setChecked(false);
            Toast.makeText(MapsActivity.this, "Not connected to Alpha!", Toast.LENGTH_LONG).show();
        }
        //  checking for fake connection
        else if (mmSocket != null && (mmSocket.isConnected())) {
            Log.i("Main Activity", "reached1");

            try {
                byte[] mbyte = {0};
                mmSocket.getOutputStream().write(mbyte);
                BTConnected = true;
            } catch (Exception e) {
                BTConnected = false;
                Toast.makeText(MapsActivity.this, "Lost connected to Alpha!", Toast.LENGTH_LONG).show();
                try {
                    mmSocket.close();
                } catch (Exception ex) {
                    Log.e("Main Activity", "Exception closing socket" + ex.getMessage());
                }
                Log.i("Main Activity", "Exception Connection Lost");

            }
        }

        if (BTConnected && mmSocket.isConnected()) {
            Log.i("Main Activity", "inside connected. connection formed" + mmSocket.isConnected());

            byte[] buffer = new byte[24];
            final Button go_stop = (Button) findViewById(R.id.button1);
            if (flag) {
                mapGraph graph = new mapGraph();

                LatLng gps  = ble_communication.getcurrentPOS();
                if((gps.latitude !=0.0)&& (gps.latitude != - 0.0) && (gps.longitude != 0.0) && (gps.longitude != -0.0))
                    gpsData = gps;

                Log.i("Current POS : ",gpsData.latitude+" "+gpsData.longitude + " Destination : "+destination.latitude + " "+destination.longitude);
                ArrayList<LatLng> route = graph.maproute(new mapNode(gpsData), new mapNode(destination));
                /*Comment till this*/
                mMap.clear();
                MapCommands mapCommands = new MapCommands();
                mapCommands.addSource(route.get(route.size() - 1), mMap);
                mapCommands.addDestination(route.get(0), mMap);
                mapCommands.drowline(route, mMap);
                mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(route.get(route.size() - 1), 18));
                Toast.makeText(MapsActivity.this, "Sending Check Points "+ (route.size()-1), Toast.LENGTH_LONG).show();
                //  Toast.makeText(MapsActivity.this, "Sending Check Points "+ route.size(), Toast.LENGTH_LONG).show();

                String str = "$" + (route.size()-1) + "\n";
                buffer = str.getBytes();
                ble_write.write(buffer);

                buffer = "*0\n".getBytes();
                ble_write.write(buffer);
                buffer = "*0\n".getBytes();
                ble_write.write(buffer);

                for (int i = route.size()-2; i >= 0 ; i--) {
                    Log.i("BLE_Connect", " Check pints : "+route.get(i).latitude+" and "+route.get(i).longitude + " on Socket : "+mmSocket.toString());
                    str = "#" + route.get(i).latitude + "@" + route.get(i).longitude + "\n";
                    buffer = str.getBytes();
                    ble_write.write(buffer);

                }
                buffer = "*1\n".getBytes();
                ble_write.write(buffer);
                go_stop.setText("STOP");
                myTTS.speak("GO",TextToSpeech.QUEUE_FLUSH,null);
                flag = false;
            } else {
                buffer = "*0\n".getBytes();
                ble_write.write(buffer);
                buffer = "*0\n".getBytes();
                ble_write.write(buffer);
                go_stop.setText("GO");
                myTTS.speak("STOP",TextToSpeech.QUEUE_FLUSH,null);
                flag = true;
            }
        }
    }

    // Setting onclick event listener for the map
    @Override
    public void onMapClick(LatLng latLng) {
        destination = latLng;
        mMap.clear();
        mMap.addMarker(new MarkerOptions().position(destination).icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED)));
        Toast.makeText(MapsActivity.this,"Latitude : "+destination.latitude + "\n Longitude : "+destination.longitude, Toast.LENGTH_LONG).show();

    }

    /*
    This function will add listener
     */
    private void initListeners() {
        mMap.setOnMapClickListener(this);

    }

    public void connect_alpha() {

        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        for (BluetoothDevice device : pairedDevices) {
            if (device.getName().equals("HC-05")) {
                Log.i("Alpha", "got Alpha");

                //  Parcelable[] uuidExtra = (ParcelUuid[]) device.getUuids();

               /* for (Parcelable Dev_uuid : uuidExtra) {
                    Log.i("UUID : ", Dev_uuid.toString());
                }*/

                bt_Thread = new BluetoothConnect(device, mBluetoothAdapter, this);
                //
                bt_Thread.start();
                Log.i("Bluetooth Socket", "Socket stored");
                ble_communication = new BluetoothCommunicate(mmSocket,this,mMap);
                ble_communication.start();
                ble_write = new BluetoothCommunicate();
                //UpdateLocation();
            }
        }

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        try {
            Log.i("BLE_Connect", "App Closed");
            bt_Thread.cancel();
            if(mmSocket!=null)
                mmSocket.close();
            mmSocket = null;
            mBluetoothAdapter.disable();
            if(bt_Thread != null)
                bt_Thread.cancel();
            if(ble_communication != null)
                ble_communication.cancel();
        } catch (IOException closeException) {
            Log.i("BLE_Connect", "BLE_connect Exception" + closeException);
        }
    }


}


