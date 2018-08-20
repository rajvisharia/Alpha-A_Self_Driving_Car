package com.example.jay.googlemaprouter.Map;

import com.google.android.gms.maps.model.LatLng;

import java.util.LinkedList;

import static java.lang.Math.acos;
import static java.lang.Math.cos;
import static java.lang.Math.pow;
import static java.lang.Math.sin;
import static java.lang.Math.sqrt;

/**
 * Created by jay on 11/3/2017.
 */

public class mapNode {
    public  LatLng latLng;
    LinkedList<mapNode> childNodes = new LinkedList<>();

    public mapNode(){
        this.latLng = new LatLng(0,0);
    }

    public mapNode(LatLng mapNode)
    {
        this.latLng = mapNode;
    }

    public void addChild(mapNode child)
    {
        childNodes.add(child);
    }

//    double toRad(double degree) {
//        return degree/180 *  3.14159265358979323846;
//    }

    public double getDistance(mapNode otherNode)
    {
        double R = 6371000; // metres
        double φ1 = Math.toRadians(this.latLng.latitude);
        double φ2 = Math.toRadians(otherNode.latLng.latitude);
        double Δφ = Math.toRadians(otherNode.latLng.latitude-this.latLng.latitude);
        double Δλ = Math.toRadians(otherNode.latLng.longitude-this.latLng.longitude);

        double a = Math.sin(Δφ/2) * Math.sin(Δφ/2) +
                Math.cos(φ1) * Math.cos(φ2) *
                        Math.sin(Δλ/2) * Math.sin(Δλ/2);
        double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));

        double d = R * c;

//        double d = Math.sqrt(((this.latLng.latitude - otherNode.latLng.latitude)*(this.latLng.latitude - otherNode.latLng.latitude))+
//        (this.latLng.longitude - otherNode.latLng.longitude)*(this.latLng.longitude - otherNode.latLng.longitude));
        return d;
    }

//    @Override
//    public boolean equals(Object o)
//    {
//        mapNode other = (mapNode)o;
//        return (this.latLng == other.latLng);
//    }
}
