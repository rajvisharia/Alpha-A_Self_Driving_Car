package com.example.jay.googlemaprouter.Map;

import android.graphics.Color;
import android.util.Log;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;

import org.w3c.dom.Node;

import java.util.ArrayList;

/**
 * Created by jay on 10/22/2017.
 */

public class MapCommands {

    public void addSource(LatLng pos,GoogleMap mMap)
    {

        mMap.addMarker(new MarkerOptions().position(pos).title("Source: "+pos.latitude+" , "+pos.longitude).icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_BLUE)));

    }

    public void addDestination(LatLng pos,GoogleMap mMap)
    {
        mMap.addMarker(new MarkerOptions().position(pos).title("Destination : "+pos.latitude+" , "+pos.longitude));
    }


    public void drowline(ArrayList<LatLng> points, GoogleMap mMap)
    {
        PolylineOptions lineOptions = new PolylineOptions();
        lineOptions.addAll(points);
        lineOptions.width(12);
        lineOptions.color(Color.BLUE);
        lineOptions.geodesic(true);
        mMap.addPolyline(lineOptions);

        for (int i = points.size()-2; i > 0 ; i--) {
            mMap.addMarker(new MarkerOptions().position(points.get(i)).title("Check Points "+points.get(i).latitude+" , "+points.get(i).longitude)
                    .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_VIOLET)));
        }

//        for(int i=1;i<points.size()-1;i++)
//        {
//            mMap.addMarker(new MarkerOptions().position(points.get(i)).title("Check Points "+i).icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_VIOLET)));
//        }

    }

}
