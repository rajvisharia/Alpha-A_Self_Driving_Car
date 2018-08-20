package com.example.jay.googlemaprouter;

import android.bluetooth.BluetoothSocket;
import android.util.Log;

import com.example.jay.googlemaprouter.Bluetooth.BluetoothCommunicate;
import com.example.jay.googlemaprouter.Bluetooth.GPSData;
import com.example.jay.googlemaprouter.Map.mapGraph;
import com.example.jay.googlemaprouter.Map.mapNode;
import com.google.android.gms.maps.model.LatLng;

import org.junit.Test;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.ArrayList;

import static java.lang.Boolean.TRUE;
import static java.lang.Math.sqrt;
import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */


public class ExampleUnitTest {
   /* @Test
    public void addition_isCorrect() throws Exception {
        assertEquals(4, 2 + 2);
    }*/

//    @Test
//    public void distance_isCorrect() throws Exception
//    {
//        mapNode sourceNode = new mapNode(new LatLng(0,0));
//        mapNode destNode = new mapNode(new LatLng(1,1));
//        assertEquals(sqrt(2),sourceNode.getDistance(destNode),0);
//        assertEquals(sqrt(2),destNode.getDistance(sourceNode),0);
//
//        mapNode sourceNode1 = new mapNode(new LatLng(0,0));
//        mapNode destNode1 = new mapNode(new LatLng(0,0.5));
//        assertEquals(0.5,sourceNode1.getDistance(destNode1),0);
//        assertEquals(0.5,destNode1.getDistance(sourceNode1),0);
//
//        mapNode sourceNode2 = new mapNode(new LatLng(0,0));
//        mapNode destNode2= new mapNode(new LatLng(0,-0.5));
//        assertEquals(0.5,sourceNode2.getDistance(destNode2),0);
//        assertEquals(0.5,sourceNode1.getDistance(destNode1),0);
//
//        mapNode sourceNode5 = new mapNode(new LatLng(0,0));
//        mapNode destNode5= new mapNode(new LatLng(0,0));
//        assertEquals(0,sourceNode5.getDistance(destNode5),0.0);
//
//        mapNode sourceNode6 = new mapNode(new LatLng(37.125345,-121.232435));
//        mapNode destNode6= new mapNode(new LatLng(0,0));
//        assertEquals(sqrt((37.125345*37.125345)+(-121.232435*-121.232435)),sourceNode6.getDistance(destNode6),0.0);
//        assertEquals(sqrt((37.125345*37.125345)+(-121.232435*-121.232435)),destNode6.getDistance(sourceNode6),0.0);
//
//        mapNode sourceNode3 = new mapNode(new LatLng(37.125345,-121.232435));
//        mapNode destNode3= new mapNode(new LatLng(37.125345,-121.232435));
//        assertEquals(0,sourceNode3.getDistance(destNode3),0.0);
//        assertEquals(0,destNode3.getDistance(sourceNode3),0.0);
//
//        mapNode sourceNode4 = new mapNode(new LatLng(37.125345,-121.232435));
//        mapNode destNode4= new mapNode(new LatLng(37.125342,-121.232439));
//        assertEquals(sqrt((0.000003*0.000003)+(0.000004*0.000004)),sourceNode4.getDistance(destNode4),0.000001);
//        assertEquals(sqrt((0.000003*0.000003)+(0.000004*0.000004)),destNode4.getDistance(sourceNode4),0.000001);
//
//        mapNode sourceNode7 = new mapNode(new LatLng(37.125345,-121.232435));
//        mapNode destNode7= new mapNode(new LatLng(37.125045,-121.232035));
//        assertEquals(sqrt((0.0003*0.0003)+(0.0004*0.0004)),sourceNode7.getDistance(destNode7),0.000001);
//        assertEquals(sqrt((0.0003*0.0003)+(0.0004*0.0004)),destNode7.getDistance(sourceNode7),0.000001);
//
//    }
//
//    @Test
//    public void minDistance_isCorrect() throws Exception
//    {
//        mapGraph graph = new mapGraph();
//
//        ArrayList<Double> distance = new ArrayList<>();
//        ArrayList<Boolean> visited = new ArrayList<>();
//        distance.add(0.0);
//        visited.add(false);
//        distance.add(5.0);
//        visited.add(false);
//        distance.add(10.2);
//        visited.add(false);
//        distance.add(10.0);
//        visited.add(false);
//        assertEquals(0,graph.minDistance(distance,visited));
//
//        visited.set(0,true);
//        assertEquals(1,graph.minDistance(distance,visited));
//
//        visited.set(0,false);
//        distance.set(0,10.3);
//        assertEquals(1,graph.minDistance(distance,visited));
//
//        visited.set(1,true);
//        assertEquals(3,graph.minDistance(distance,visited));
//
//    }
//
    @Test
    public void maproute_isCorrect() throws Exception
    {
        mapGraph graph = new mapGraph();
        ArrayList route = new ArrayList();


        route.add(graph.v.get(9).latLng);
        route.add(graph.v.get(8).latLng);
        route.add(graph.v.get(11).latLng);
//        route.add(graph.v.get(7).latLng);
//        route.add(graph.v.get(10).latLng);
//        route.add(graph.v.get(6).latLng);
//        route.add(graph.v.get(4).latLng);
//        route.add(graph.v.get(2).latLng);
//        route.add(graph.v.get(1).latLng);
//        route.add(graph.v.get(0).latLng);
//
//        assertEquals(route,graph.maproute(graph.v.get(0),graph.v.get(9)));
//
////        mapNode val1 = new mapNode(new LatLng(37.335645,-121.882879));
////        route.clear();
////        route.add(val1.latLng);
////        route.add(graph.v.get(13).latLng);
////        route.add(graph.v.get(9).latLng);
////        assertEquals(route,graph.maproute(graph.v.get(9),val1));
//
//
//        route.clear();
//        route.add(graph.v.get(9).latLng);
//        route.add(graph.v.get(13).latLng);
//        assertEquals(route,graph.maproute(graph.v.get(13),graph.v.get(9)));
//
//        route.clear();
//        mapNode node1 = new mapNode(new LatLng(37.334244,-121.883104));
//        mapNode node2 = new mapNode(new LatLng(37.334328,-121.883104));
//        route.add(node2.latLng);
//        route.add(node1.latLng);
//        assertEquals(route,graph.maproute(node1,node2));
//
//        route.clear();
//        route.add(node1.latLng);
//        route.add(node2.latLng);
//        assertEquals(route,graph.maproute(node2,node1));
//
//        route.clear();
//        route.add(new LatLng(37.338868,-121.879728));
//        route.add(graph.v.get(14).latLng);
//        route.add(graph.v.get(15).latLng);
//        route.add(graph.v.get(16).latLng);
//        route.add(graph.v.get(17).latLng);
//        route.add(graph.v.get(18).latLng);
//        assertEquals(route,graph.maproute(graph.v.get(18),new mapNode(new LatLng(37.338868,-121.879728))));
//
//        assertNotEquals(2,graph.maproute(graph.v.get(13),graph.v.get(50)));

       // assertEquals(route,graph.maproute(new mapNode(new LatLng(37.335245, -121.881402)),new mapNode(new LatLng(37.335752, -121.881643))));


        /*
        * For the given function,
        * As we will add all the nodes in SJSU number of test cases might increase.
        */

    }

   @Test
    public void mapConnectRoute_isCorrect() throws Exception
   {
//       mapGraph graph = new mapGraph();
//       ArrayList<mapNode> nodeList = new ArrayList<mapNode>();
//       ArrayList<Integer> parantsNode = new ArrayList<Integer>();
//       ArrayList<LatLng> route = new ArrayList<LatLng>();
//
//       assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,0));
//       mapNode node = new mapNode(new LatLng(37.123242,-121.767565));
//       nodeList.add(node);
//       assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,0));
//       parantsNode.add(0);
//       assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,-1));
//       route.add(new LatLng(node.latLng.latitude,node.latLng.longitude));
//       assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,0));
//
//       mapNode node1 = new mapNode(new LatLng(37.123333,-121.767333));
//       mapNode node9 = new mapNode(new LatLng(37.123442,-121.767445));
//
//       nodeList.add(node1);
//       parantsNode.add(0);
//
//       route.clear();
//       route.add(new LatLng(node1.latLng.latitude,node1.latLng.longitude));
//       route.add(new LatLng(node.latLng.latitude,node.latLng.longitude));
//
//       assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,1));
//
//       nodeList.add(node9);
//       parantsNode.add(1);
//
//       route.clear();
//       route.add(new LatLng(node9.latLng.latitude,node9.latLng.longitude));
//       route.add(new LatLng(node1.latLng.latitude,node1.latLng.longitude));
//       route.add(new LatLng(node.latLng.latitude,node.latLng.longitude));
//
//       assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,2));
//
//       try {
//           assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,3));
//       } catch (RuntimeException expectedException) {
//           Log.i("Exception","I Expect this");
//       }
//
//       mapNode node2 = new mapNode(new LatLng(37.123322,-121.767313));
//       mapNode node3 = new mapNode(new LatLng(37.122442,-121.767425));
//       mapNode node4 = new mapNode(new LatLng(37.1243433,-121.767333));
//       mapNode node5 = new mapNode(new LatLng(37.123433,-121.767343));
//       mapNode node6 = new mapNode(new LatLng(37.123422,-121.767455));
//       mapNode node7 = new mapNode(new LatLng(37.123342,-121.767465));
//
//
//       nodeList.add(node2);
//       parantsNode.add(2);
//       nodeList.add(node3);
//       parantsNode.add(3);
//       nodeList.add(node4);
//       parantsNode.add(4);
//       nodeList.add(node5);
//       parantsNode.add(5);
//       nodeList.add(node6);
//       parantsNode.add(6);
//       nodeList.add(node7);
//       parantsNode.add(7);
//
//       route.clear();
//       route.add(new LatLng(node5.latLng.latitude,node5.latLng.longitude));
//       route.add(new LatLng(node4.latLng.latitude,node4.latLng.longitude));
//       route.add(new LatLng(node3.latLng.latitude,node3.latLng.longitude));
//       route.add(new LatLng(node2.latLng.latitude,node2.latLng.longitude));
//
//       route.add(new LatLng(node9.latLng.latitude,node9.latLng.longitude));
//       route.add(new LatLng(node1.latLng.latitude,node1.latLng.longitude));
//       route.add(new LatLng(node.latLng.latitude,node.latLng.longitude));
//       assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,6));
//
//       route.clear();
//       route.add(new LatLng(node7.latLng.latitude,node7.latLng.longitude));
//       route.add(new LatLng(node6.latLng.latitude,node6.latLng.longitude));
//       route.add(new LatLng(node5.latLng.latitude,node5.latLng.longitude));
//       route.add(new LatLng(node4.latLng.latitude,node4.latLng.longitude));
//       route.add(new LatLng(node3.latLng.latitude,node3.latLng.longitude));
//       route.add(new LatLng(node2.latLng.latitude,node2.latLng.longitude));
//
//       route.add(new LatLng(node9.latLng.latitude,node9.latLng.longitude));
//       route.add(new LatLng(node1.latLng.latitude,node1.latLng.longitude));
//       route.add(new LatLng(node.latLng.latitude,node.latLng.longitude));
//
//       assertEquals(route,graph.mapConnectRoute(nodeList,parantsNode,8));
//
//


   }

    @Test
    public void nearestCheckpoints_isCorrect() throws Exception
    {
        mapGraph graph = new mapGraph();
        mapNode source = new mapNode(new LatLng(37.335073,-121.881128));
        mapNode destination = new mapNode(new LatLng(37.336602,-121.882277));

     //   assertEquals(0,source.getDistance(destination),0);
        assertEquals(new LatLng(37.336602,-121.882277),graph.nearestCheckpoints(destination,source).latLng);

    }


//    @Test
//    public void readStrToLalLong_isCorrect() throws Exception {
//        BluetoothCommunicate bleComm = new BluetoothCommunicate(null);
//        InputStream input = new ByteArrayInputStream("#37.123456@-121.345123*90.00\n".getBytes());
//        LatLng pos = new LatLng(37.123456,-121.345123);
//        float angle = 90;
//        GPSData gpsData = new GPSData(pos,angle);
//        GPSData data = bleComm.readStrToLalLong(input);
//        assertEquals(gpsData.latLng,data.latLng);
//        assertEquals(gpsData.headingAngle,data.headingAngle,0);
//
//
//        InputStream input1 = new ByteArrayInputStream("#37.123444@-121.345223*20\n".getBytes());
//        LatLng pos1 = new LatLng(37.123444,-121.345223);
//        float angle1 = 20;
//        GPSData gpsData1 = new GPSData(pos1,angle1);
//        GPSData data1 = bleComm.readStrToLalLong(input1);
//        assertEquals(gpsData1.latLng,data1.latLng);
//        assertEquals(gpsData1.headingAngle,data1.headingAngle,0);
//
//
//        input = new ByteArrayInputStream("".getBytes());
//        assertEquals(null,bleComm.readStrToLalLong(input));
//
//        input = new ByteArrayInputStream("#".getBytes());
//        assertEquals(null,bleComm.readStrToLalLong(input));
//
//        input = new ByteArrayInputStream("#37.12345".getBytes());
//        assertEquals(null,bleComm.readStrToLalLong(input));
//
//        input = new ByteArrayInputStream("#37.123456@".getBytes());
//        assertEquals(null,bleComm.readStrToLalLong(input));
//
//        input = new ByteArrayInputStream("#37.123456@-121.345".getBytes());
//        assertEquals(null,bleComm.readStrToLalLong(input));
//
//        input = new ByteArrayInputStream("#37.123456@-121.34532323232".getBytes());
//        assertEquals(null,bleComm.readStrToLalLong(input));
//
//        input = new ByteArrayInputStream("#37.1234561111111111111111111111111111111111111@-121.345323232321111111111111111111111111111111111111111111111*70.00\n".getBytes());
//        pos = new LatLng(37.1234561111111111111111111111111111111111111,-121.345323232321111111111111111111111111111111111111111111111);
//        angle = 70;
//        GPSData gpsData2 = new GPSData(pos,angle);
//        GPSData data2 = bleComm.readStrToLalLong(input);
//        assertEquals(gpsData2.latLng,data2.latLng);
//        assertEquals(gpsData2.headingAngle,data2.headingAngle,0);
//    }

}


