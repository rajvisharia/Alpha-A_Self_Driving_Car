package com.example.jay.googlemaprouter.Bluetooth;

import android.bluetooth.BluetoothDevice;
import java.lang.reflect.Method;

/**
 * Created by jay on 10/22/2017.
 */

public class BluetoothPair {

    void pairDevice(BluetoothDevice device) {
        try {
            Method method = device.getClass().getMethod("createBond", (Class[]) null);
            method.invoke(device, (Object[]) null);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    void unpairDevice(BluetoothDevice device) {
        try {
            Method method = device.getClass().getMethod("removeBond", (Class[]) null);
            method.invoke(device, (Object[]) null);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }


}
