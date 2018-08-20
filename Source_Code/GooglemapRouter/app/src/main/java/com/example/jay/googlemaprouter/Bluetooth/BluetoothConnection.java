package com.example.jay.googlemaprouter.Bluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.os.ParcelUuid;
import android.os.Parcelable;
import android.util.Log;
import android.widget.Toast;


import java.util.Set;
import java.util.UUID;

/**
 * Created by jay on 10/22/2017.
 */

public class BluetoothConnection {

    BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

    private static Context context;

    public BluetoothConnection(Context c) {
        context = c;
    }

    public void bluethoot_enable() {
        if (!mBluetoothAdapter.isEnabled()) {
            mBluetoothAdapter.enable();
            // Toast.makeText(MapsActivity.this,"Bluethooth Enabled", Toast.LENGTH_LONG).show();
        } else
            Toast.makeText(context, "Bluethooth is already on", Toast.LENGTH_LONG).show();
    }

    public void bluethoot_disable() {
        mBluetoothAdapter.disable();
        Toast.makeText(context, "Bluethooth is Turned off", Toast.LENGTH_LONG).show();
    }


}
