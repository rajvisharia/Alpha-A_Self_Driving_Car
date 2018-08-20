package com.example.jay.googlemaprouter.Bluetooth;

import com.google.android.gms.maps.model.LatLng;

/**
 * Created by jay on 11/19/2017.
 */

public class GPSData {
    public LatLng latLng;
    public float headingAngle;
    public GPSData(LatLng latLng,float headingAngle)
    {
        this.latLng = latLng;
        this.headingAngle = headingAngle;
    }
}
