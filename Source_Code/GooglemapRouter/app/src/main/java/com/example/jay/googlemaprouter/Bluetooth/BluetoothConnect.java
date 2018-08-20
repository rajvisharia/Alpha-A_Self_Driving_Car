package com.example.jay.googlemaprouter.Bluetooth;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;
import android.widget.Switch;
import android.widget.Toast;

import com.example.jay.googlemaprouter.MapsActivity;
import com.example.jay.googlemaprouter.R;

import java.io.IOException;
import java.util.UUID;

public class BluetoothConnect extends Thread{
    private BluetoothSocket mmSocket;
    private final BluetoothDevice mmDevice;
    private BluetoothAdapter mBluetoothAdapter;
    private Activity mParent;
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
    boolean closeFlag = true;
    private BluetoothCommunicate bleComm;


    public BluetoothConnect(BluetoothDevice device, BluetoothAdapter mBluetoothAdapter, Activity parentActivity) {
        this.mBluetoothAdapter = mBluetoothAdapter;
        mParent = parentActivity;
   //     BluetoothSocket tmp = null;
         bleComm = new BluetoothCommunicate();
        mmDevice = device;
        return;
    }
    public void run() {
       // mBluetoothAdapter.cancelDiscovery();
        Log.i("Bluetooth","Inside running thread...... " );
        while(closeFlag)
        {
           // Log.i("Ble Connection","In1");

            if(mmSocket== null || (!mmSocket.isConnected()))
            {
                if(mmSocket!=null)
                {
                    try {
                        mmSocket.close();
                        mmSocket = null;
                    }catch (Exception ex)
                    {
                        Log.e("Main Activity","Exception closing socket" + ex.getMessage());
                    }
                }
                Log.i("Ble Connection","mmSocke is null or not connected");
                //set the UI elements n parent
                mParent.runOnUiThread((new Runnable() {
                    @Override
                    public void run() {
                        Switch bleSwitch= (Switch) mParent.findViewById(R.id.bleSwitch);
                        bleSwitch.setChecked(false);
                     //   Toast.makeText(mParent,"Not connected to Alpha!",Toast.LENGTH_LONG).show();
                    }
                }));
                tryToConnect();
            }
            //checking for lost connection (socket exists from our side but closed from other. recreate socket)

            else{
            try {
                byte[] mbyte = {0};
                mmSocket.getOutputStream().write(mbyte) ;
            }
            catch (Exception e)
            {
                try {
                    mmSocket.close();
                    mmSocket = null;
                }catch (Exception ex)
                {
                    Log.e("Main Activity","Exception closing socket" + ex.getMessage());
                }
                Log.i("Main Activity","Exception Connection Lost");
                //set the UI elements n parent
                mParent.runOnUiThread((new Runnable() {
                    @Override
                    public void run() {
                        Switch bleSwitch= (Switch) mParent.findViewById(R.id.bleSwitch);
                        bleSwitch.setChecked(false);
                        Toast.makeText(mParent,"Not connected to Alpha!",Toast.LENGTH_LONG).show();
                    }
                }));
                tryToConnect();
            }

            try {
                Thread.sleep(1000);
            }
           catch(Exception e)
           {
               Log.i("Bluetooth","Thread sleep error - trying to connect" + e.getMessage() );
           }

        }}
    }

public void tryToConnect()
{
    Log.i("Bluetooth","Inside Try to connect" );
    BluetoothSocket tmp = null;
    try {
        //tmp =(BluetoothSocket) mmDevice.getClass().getMethod("createRfcommSocket", new Class[] {int.class}).invoke(mmDevice,1);

        tmp = mmDevice.createRfcommSocketToServiceRecord(MY_UUID);
    } catch (Exception e) {
        Log.i("Bluetooth","Error in create Socket " + e.toString() );
    }

    mmSocket = tmp;
    Log.i("Bluetooth","created new Socket " );
    if(mmSocket != null) {
        try {
            Log.i("BLE_Connect", "trying to Connect");
            mmSocket.connect();
            Log.i("BLE_Connect", "Connected");
            //set the UI elements n parent
            mParent.runOnUiThread((new Runnable() {
                @Override
                public void run() {
                    Switch bleSwitch = (Switch) mParent.findViewById(R.id.bleSwitch);
                    bleSwitch.setChecked(true);
                    Toast.makeText(mParent, "Connected to Alpha!", Toast.LENGTH_LONG).show();
                }
            }));
            bleComm.setMmSocket(mmSocket);
            Log.i("Ble Connect","Update Socket");
        } catch (IOException connectException) {
            Log.i("BLE_Connect", "BLE_connect Exception occurred" + connectException);
        }
    }
}
    public BluetoothSocket get_socket()
    {
        return mmSocket;
    }


    public void cancel() {
        try {
            mmSocket.close();
            mmSocket = null;
            closeFlag = false;
        } catch (IOException e) { }
    }
}