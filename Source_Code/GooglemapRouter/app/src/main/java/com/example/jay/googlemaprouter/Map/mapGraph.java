package com.example.jay.googlemaprouter.Map;

import android.util.Log;

import com.google.android.gms.maps.model.LatLng;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.LinkedList;

import static java.lang.Math.abs;


public class mapGraph {
    public ArrayList<mapNode> v = new ArrayList<mapNode>();

    public mapGraph()
    {

        mapNode sfR9th = new mapNode(new LatLng(37.338133,-121.880469));
        mapNode sfR9th1 = new mapNode(new LatLng(37.337996,-121.880372));
        sfR9th.addChild(sfR9th1);
        sfR9th1.addChild(sfR9th);
        v.add(sfR9th);
        v.add(sfR9th1);
        mapNode sfR9th2 = new mapNode(new LatLng(37.337880,-121.880278));
        sfR9th2.addChild(sfR9th1);
        sfR9th1.addChild(sfR9th2);
        v.add(sfR9th2);
        mapNode sfR9th3 = new mapNode(new LatLng(37.337757,-121.880187));
        sfR9th2.addChild(sfR9th3);
        sfR9th3.addChild(sfR9th2);
        v.add(sfR9th3);
        mapNode sfR9th4 = new mapNode(new LatLng(37.337648,-121.880105));
        sfR9th4.addChild(sfR9th3);
        sfR9th3.addChild(sfR9th4);
        v.add(sfR9th4);
        mapNode sfR9th5 = new mapNode(new LatLng(37.337538,-121.880026));
        sfR9th4.addChild(sfR9th5);
        sfR9th5.addChild(sfR9th4);
        v.add(sfR9th5);
        mapNode sfR9th6 = new mapNode(new LatLng(37.337436,-121.879947));
        sfR9th6.addChild(sfR9th5);
        sfR9th5.addChild(sfR9th6);
        v.add(sfR9th6);
        mapNode sfR9th7 = new mapNode(new LatLng(37.337309,-121.879845));
        sfR9th6.addChild(sfR9th7);
        sfR9th7.addChild(sfR9th6);
        v.add(sfR9th7);
        mapNode ATM = new mapNode(new LatLng(37.337270,-121.879855));
        ATM.addChild(sfR9th7);
        sfR9th7.addChild(ATM);
        v.add(ATM);


        //Left side
        mapNode sfL9th = new mapNode(new LatLng(37.3380858,-121.880649));
        sfR9th.addChild(sfL9th);
        sfL9th.addChild(sfR9th);
        v.add(sfL9th);
        mapNode sfL9th1 = new mapNode(new LatLng(37.337941,-121.880540));
        sfL9th1.addChild(sfL9th);
        sfL9th.addChild(sfL9th1);
        v.add(sfL9th1);
        mapNode sfL9th2 = new mapNode(new LatLng(37.337815,-121.880461));
        sfL9th1.addChild(sfL9th2);
        sfL9th2.addChild(sfL9th1);
        v.add(sfL9th2);
        mapNode sfL9th3 = new mapNode(new LatLng(37.337725,-121.880395));
        sfL9th3.addChild(sfL9th2);
        sfL9th2.addChild(sfL9th3);
        v.add(sfL9th3);
        mapNode sfL9th4 = new mapNode(new LatLng(37.337577,-121.880291));
        sfL9th3.addChild(sfL9th4);
        sfL9th4.addChild(sfL9th3);
        v.add(sfL9th4);
        mapNode sfL9th5 = new mapNode(new LatLng(37.337476,-121.880223));
        sfL9th5.addChild(sfL9th4);
        sfL9th4.addChild(sfL9th5);
        v.add(sfL9th5);
        mapNode sfL9th6 = new mapNode(new LatLng(37.337362,-121.880122));
        sfL9th5.addChild(sfL9th6);
        sfL9th6.addChild(sfL9th5);
        v.add(sfL9th6);
        mapNode sfL9th7 = new mapNode(new LatLng(37.337223,-121.880011));
        sfL9th7.addChild(sfL9th6);
        sfL9th6.addChild(sfL9th7);
        v.add(sfL9th7);
        mapNode atmToEng = new mapNode(new LatLng(37.337161,-121.879978));
        ATM.addChild(atmToEng);
        atmToEng.addChild(ATM);
        v.add(atmToEng);

        //ATM to Eng

        mapNode atmToEng1 = new mapNode(new LatLng(37.336982, -121.880467));
        atmToEng1.addChild(atmToEng);
        atmToEng.addChild(atmToEng1);
        v.add(atmToEng1);

        mapNode atmToEng2Cross = new mapNode(new LatLng(37.336809, -121.880812));
        atmToEng1.addChild(atmToEng2Cross);
        atmToEng2Cross.addChild(atmToEng1);
        v.add(atmToEng2Cross);

        mapNode atmToEng3 = new mapNode(new LatLng(37.336626, -121.881205));
        atmToEng3.addChild(atmToEng2Cross);
        atmToEng2Cross.addChild(atmToEng3);
        v.add(atmToEng3);

        mapNode atmToEng4 = new mapNode(new LatLng(37.336488, -121.881494));
        atmToEng3.addChild(atmToEng4);
        atmToEng4.addChild(atmToEng3);
        v.add(atmToEng4);

        mapNode atmToEng5 = new mapNode(new LatLng(37.336353, -121.881781));
        atmToEng5.addChild(atmToEng4);
        atmToEng4.addChild(atmToEng5);
        v.add(atmToEng5);

        mapNode ATMEng = new mapNode(new LatLng(37.336268, -121.881969));
        atmToEng5.addChild(ATMEng);
        ATMEng.addChild(atmToEng5);
        v.add(ATMEng);

        //ATM to BBC
        mapNode BK = new mapNode(new LatLng(37.337063,-121.879727));
        ATM.addChild(BK);
        BK.addChild(ATM);
        v.add(BK);

        mapNode BusinessEnt = new mapNode(new LatLng(37.336973,-121.879639));
        BusinessEnt.addChild(BK);
        BK.addChild(BusinessEnt);
        v.add(BusinessEnt);

        mapNode SUgatewayCross = new mapNode(new LatLng(37.336722,-121.879388));
        BusinessEnt.addChild(SUgatewayCross);
        SUgatewayCross.addChild(BusinessEnt);
        v.add(SUgatewayCross);

        mapNode SULgatewayCross = new mapNode(new LatLng(37.336608,-121.879594));
        SUgatewayCross.addChild(SULgatewayCross);
        SULgatewayCross.addChild(SUgatewayCross);
        v.add(SULgatewayCross);

        mapNode BBC = new mapNode(new LatLng(37.336572,-121.879284));
        BBC.addChild(SUgatewayCross);
        SUgatewayCross.addChild(BBC);
        v.add(BBC);

        mapNode BBC1 = new mapNode(new LatLng(37.336484,-121.879217));
        BBC.addChild(BBC1);
        BBC1.addChild(BBC);
        v.add(BBC1);

        mapNode BBC2 = new mapNode(new LatLng(37.336362, -121.879123));
        BBC2.addChild(BBC1);
        BBC1.addChild(BBC2);
        v.add(BBC2);

        mapNode BBC3 = new mapNode(new LatLng(37.336261, -121.879053));
        BBC2.addChild(BBC3);
        BBC3.addChild(BBC2);
        v.add(BBC3);

        mapNode BBC4 = new mapNode(new LatLng(37.336128, -121.878949));
        BBC4.addChild(BBC3);
        BBC3.addChild(BBC4);
        v.add(BBC4);

        mapNode CP1 = new mapNode(new LatLng(37.335949, -121.878821));
        BBC4.addChild(CP1);
        CP1.addChild(BBC4);
        v.add(CP1);

        mapNode CP2 = new mapNode(new LatLng(37.335840, -121.878735));
        CP2.addChild(CP1);
        CP1.addChild(CP2);
        v.add(CP2);

        mapNode CP3 = new mapNode(new LatLng(37.335747, -121.878668));
        CP2.addChild(CP3);
        CP3.addChild(CP2);
        v.add(CP3);

        mapNode CP4 = new mapNode(new LatLng(37.335622, -121.878574));
        CP4.addChild(CP3);
        CP3.addChild(CP4);
        v.add(CP4);


        //LeftPart Rerurn way
        mapNode CPL4 = new mapNode(new LatLng(37.335502, -121.878763));
        CP4.addChild(CPL4);
        CPL4.addChild(CP4);
        v.add(CPL4);

        mapNode CPL3 = new mapNode(new LatLng(37.335711, -121.878920));
        CPL3.addChild(CPL4);
        CPL4.addChild(CPL3);
        v.add(CPL3);

        mapNode CPL2 = new mapNode(new LatLng(37.335845, -121.879006));
        CPL3.addChild(CPL2);
        CPL2.addChild(CPL3);
        v.add(CPL2);

        mapNode CPL1 = new mapNode(new LatLng(37.336020, -121.879144));
        CPL1.addChild(CPL2);
        CPL2.addChild(CPL1);
        v.add(CPL1);
        CP1.addChild(CPL1);
        CPL1.addChild(CP1);

        mapNode ART4 = new mapNode(new LatLng(37.336163, -121.879233));
        CPL1.addChild(ART4);
        ART4.addChild(CPL1);
        v.add(ART4);

        mapNode ART3 = new mapNode(new LatLng(37.336260, -121.879302));
        ART3.addChild(ART4);
        ART4.addChild(ART3);
        v.add(ART3);

        mapNode ART2 = new mapNode(new LatLng(37.336392, -121.879406));
        ART2.addChild(ART3);
        ART3.addChild(ART2);
        v.add(ART2);

        mapNode ART1 = new mapNode(new LatLng(37.336506, -121.879490));
        ART2.addChild(ART1);
        ART1.addChild(ART2);
        v.add(ART1);

        SULgatewayCross.addChild(ART1);
        ART1.addChild(SULgatewayCross);

        //Art Building Back Side
        mapNode ARTBack1 = new mapNode(new LatLng(37.335876, -121.879482));
        CPL1.addChild(ARTBack1);
        ARTBack1.addChild(CPL1);
        v.add(ARTBack1);

        mapNode ARTBack2 = new mapNode(new LatLng(37.335912, -121.879621));
        ARTBack1.addChild(ARTBack2);
        ARTBack2.addChild(ARTBack1);
        v.add(ARTBack2);

        mapNode ARTBack3 = new mapNode(new LatLng(37.335694, -121.880105));
        ARTBack3.addChild(ARTBack2);
        ARTBack2.addChild(ARTBack3);
        v.add(ARTBack3);

        //SU Side Gateway
        mapNode SUgat1 = new mapNode(new LatLng(37.336454, -121.879957));
        SUgat1.addChild(SULgatewayCross);
        SULgatewayCross.addChild(SUgat1);
        v.add(SUgat1);

        mapNode SUgat2 = new mapNode(new LatLng(37.336454, -121.879957));
        SUgat1.addChild(SUgat2);
        SUgat2.addChild(SUgat1);
        v.add(SUgat2);
        SUgat2.addChild(ARTBack3);
        ARTBack3.addChild(SUgat2);

        mapNode SUgat3 = new mapNode(new LatLng(37.336038, -121.880879));
        SUgat3.addChild(SUgat2);
        SUgat2.addChild(SUgat3);
        v.add(SUgat3);

        mapNode SUgat4 = new mapNode(new LatLng(37.335884, -121.881231));
        SUgat3.addChild(SUgat4);
        SUgat4.addChild(SUgat3);
        v.add(SUgat4);

        mapNode SUgate = new mapNode(new LatLng(37.335714, -121.881653)); //This is on Road
        SUgate.addChild(SUgat4);
        SUgat4.addChild(SUgate);
        v.add(SUgate);


        //7th Street

        mapNode Eng1 = new mapNode(new LatLng(37.336915, -121.882526));
        v.add(Eng1);

        mapNode Eng2 = new mapNode(new LatLng(37.336700, -121.882357));
        Eng1.addChild(Eng2);
        Eng2.addChild(Eng1);
        v.add(Eng2);

        mapNode Eng3 = new mapNode(new LatLng(37.336603, -121.882223));
        Eng3.addChild(Eng2);
        Eng2.addChild(Eng3);
        v.add(Eng3);
        ATMEng.addChild(Eng3);
        Eng3.addChild(ATMEng);

        //Added as testing requirement
//        mapNode Clkhall_slop = new mapNode(new LatLng(37.336184, -121.881893));
//        ATMEng.addChild(Clkhall_slop);
//        Clkhall_slop.addChild(ATMEng);
//        v.add(Clkhall_slop);

//        mapNode Clkhall_slop_to_SU2 = new mapNode(new LatLng(37.336160, -121.881875));
//        Clkhall_slop_to_SU2.addChild(ATMEng);
//        ATMEng.addChild(Clkhall_slop_to_SU2);
//        v.add(Clkhall_slop_to_SU2);

        mapNode Clkhall_slop_to_SU = new mapNode(new LatLng(37.336170, -121.881886));
        ATMEng.addChild(Clkhall_slop_to_SU);
        Clkhall_slop_to_SU.addChild(ATMEng);
        v.add(Clkhall_slop_to_SU);

        mapNode Clkhall_slop_start = new mapNode(new LatLng(37.336176, -121.881939));
        Clkhall_slop_to_SU.addChild(Clkhall_slop_start);
        Clkhall_slop_start.addChild(Clkhall_slop_to_SU);
        v.add(Clkhall_slop_start);


        mapNode Clkhall_slop1 = new mapNode(new LatLng(37.336128, -121.882054));
        Clkhall_slop1.addChild(Clkhall_slop_start);
        Clkhall_slop_start.addChild(Clkhall_slop1);
        v.add(Clkhall_slop1);

        mapNode Clkhall_slop2 = new mapNode(new LatLng(37.336096, -121.882132));
        Clkhall_slop1.addChild(Clkhall_slop2);
        Clkhall_slop2.addChild(Clkhall_slop1);
        v.add(Clkhall_slop2);

        mapNode Clkhall_slop_road = new mapNode(new LatLng(37.336052, -121.882213));
        Clkhall_slop2.addChild(Clkhall_slop_road);
        Clkhall_slop_road.addChild(Clkhall_slop2);
        v.add(Clkhall_slop_road);

        mapNode Clkhall_slop_road2 = new mapNode(new LatLng(37.336000, -121.882340));
        Clkhall_slop_road2.addChild(Clkhall_slop_road);
        Clkhall_slop_road.addChild(Clkhall_slop_road2);
        v.add(Clkhall_slop_road2);

        mapNode Clkhall_slop_road3 = new mapNode(new LatLng(37.335904, -121.882513));
        Clkhall_slop_road2.addChild(Clkhall_slop_road3);
        Clkhall_slop_road3.addChild(Clkhall_slop_road2);
        v.add(Clkhall_slop_road3);


        mapNode SU = new mapNode(new LatLng(37.336065, -121.881861));
        Clkhall_slop_to_SU.addChild(SU);
        SU.addChild(Clkhall_slop_to_SU);
        v.add(SU);

        mapNode SU1 = new mapNode(new LatLng(37.335901, -121.881775));
        SU1.addChild(SU);
        SU.addChild(SU1);
        v.add(SU1);

        SUgate.addChild(SU1);
        SU1.addChild(SUgate);

        mapNode CCBPDACross1 = new mapNode(new LatLng(37.335514, -121.881500));
        CCBPDACross1.addChild(SUgate);
        SUgate.addChild(CCBPDACross1);
        v.add(CCBPDACross1);

        mapNode CCBPDACross = new mapNode(new LatLng(37.335277, -121.881301));
        CCBPDACross.addChild(CCBPDACross1);
        CCBPDACross1.addChild(CCBPDACross);
        v.add(CCBPDACross);

        mapNode CCBPDACrossin = new mapNode(new LatLng(37.335255, -121.881409));
        CCBPDACross.addChild(CCBPDACrossin);
        CCBPDACrossin.addChild(CCBPDACross);
        v.add(CCBPDACrossin);


        mapNode StudentHC = new mapNode(new LatLng(37.334957, -121.881044));
        CCBPDACross.addChild(StudentHC);
        StudentHC.addChild(CCBPDACross);
        v.add(StudentHC);

        mapNode StudentHC2 = new mapNode(new LatLng(37.334680, -121.880844));
        StudentHC2.addChild(StudentHC);
        StudentHC.addChild(StudentHC2);
        v.add(StudentHC2);

        mapNode StudentHCEnd = new mapNode(new LatLng(37.334551, -121.880919));
        StudentHC2.addChild(StudentHCEnd);
        StudentHCEnd.addChild(StudentHC2);
        v.add(StudentHCEnd);

        //
        mapNode EngParking = new mapNode(new LatLng(37.336177, -121.883173));
        EngParking.addChild(Eng3);
        Eng3.addChild(EngParking);
        v.add(EngParking);

        mapNode IRC = new mapNode(new LatLng(37.335952, -121.883649));
        EngParking.addChild(IRC);
        IRC.addChild(EngParking);
        v.add(IRC);

        mapNode IRCRoad = new mapNode(new LatLng(37.335836, -121.883910));
        IRCRoad.addChild(IRC);
        IRC.addChild(IRCRoad);
        v.add(IRCRoad);

        mapNode LibCorner = new mapNode(new LatLng(37.335572, -121.884375));
        IRCRoad.addChild(LibCorner);
        LibCorner.addChild(IRCRoad);
        v.add(LibCorner);


        //Library to Student Union
        mapNode Library = new mapNode(new LatLng(37.335371, -121.884241));
        Library.addChild(LibCorner);
        LibCorner.addChild(Library);
        v.add(Library);

        mapNode libtry = new mapNode(new LatLng(37.335539, -121.883926));
        Library.addChild(libtry);
        libtry.addChild(Library);
        libtry.addChild(LibCorner);
        LibCorner.addChild(libtry);
        v.add(libtry);

        mapNode libRoad = new mapNode(new LatLng(37.335521, -121.883710));
        libRoad.addChild(libtry);
        libtry.addChild(libRoad);
        v.add(libRoad);

        mapNode libGarden = new mapNode(new LatLng(37.335501, -121.883342));
        libRoad.addChild(libGarden);
        libGarden.addChild(libRoad);
        v.add(libGarden);

        mapNode libGarden1 = new mapNode(new LatLng(37.335527, -121.883237));
        libGarden1.addChild(libGarden);
        libGarden.addChild(libGarden1);
        libGarden1.addChild(IRC);
        IRC.addChild(libGarden1);
        v.add(libGarden1);

        mapNode CCCross = new mapNode(new LatLng(37.335598, -121.883048));
        libGarden1.addChild(CCCross);
        CCCross.addChild(libGarden1);
        v.add(CCCross);

        mapNode CLCross = new mapNode(new LatLng(37.335672, -121.882897));
        CLCross.addChild(CCCross);
        CCCross.addChild(CLCross);
        v.add(CLCross);

        mapNode CLCrossIn = new mapNode(new LatLng(37.335877, -121.882978));
        CLCross.addChild(CLCrossIn);
        CLCrossIn.addChild(CLCross);
        v.add(CLCrossIn);

        mapNode CC = new mapNode(new LatLng(37.336022, -121.883084));
        CC.addChild(CLCrossIn);
        CLCrossIn.addChild(CC);
        EngParking.addChild(CC);
        CC.addChild(EngParking);
        v.add(CC);

        mapNode CLK = new mapNode(new LatLng(37.335804, -121.882449));
        CLCross.addChild(CLK);
        CLK.addChild(CLCross);
        v.add(CLK);
        Clkhall_slop_road.addChild(CLK);
        CLK.addChild(Clkhall_slop_road3);

        mapNode CLK_not_slop1 = new mapNode(new LatLng(37.335860, -121.882262));
        CLK_not_slop1.addChild(CLK);
        CLK.addChild(CLK_not_slop1);
        v.add(CLK_not_slop1);


        mapNode CLK_not_slop = new mapNode(new LatLng(37.335919, -121.882135));
        CLK_not_slop.addChild(CLK_not_slop1);
        CLK_not_slop1.addChild(CLK_not_slop);
        v.add(CLK_not_slop);

        mapNode CLK_not_slop_end = new mapNode(new LatLng(37.335978, -121.882025));
        CLK_not_slop.addChild(CLK_not_slop_end);
        CLK_not_slop_end.addChild(CLK_not_slop);
        v.add(CLK_not_slop_end);

        SU.addChild(CLK_not_slop);
        CLK_not_slop.addChild(SU);


        //Library Road
        mapNode SCI_MD = new mapNode(new LatLng(37.334922, -121.883938));
        Library.addChild(SCI_MD);
        SCI_MD.addChild(Library);
        v.add(SCI_MD);



    }

    public ArrayList<LatLng> maproute(mapNode source,mapNode destination)
    {
        ArrayList<LatLng> route = new ArrayList<LatLng>();
        ArrayList<mapNode> nodeList = new ArrayList<mapNode>();
        ArrayList<Integer> parentNodeList = new ArrayList<Integer>();
        ArrayList<Double> distance = new ArrayList<Double>();
        ArrayList<Boolean> visited = new ArrayList<Boolean>();

        mapNode node = source;
        nodeList.add(node);
        distance.add(0.0);
        visited.add(true);
        parentNodeList.add(0);
        int num = 0;

        mapNode nearDest = nearestCheckpoints(destination,source);
        Log.i("Checkpoint","nearest"+ nearDest.latLng.latitude + " "+ nearDest.latLng.longitude);

        if(nearDest.latLng.equals(source.latLng))
        {
            route.add(destination.latLng);
            route.add(source.latLng);
            return route;
        }

            node = nearestCheckpoints(source,destination);
        Log.i("Checkpoint","nearest"+ node.latLng.latitude + " "+ node.latLng.longitude);

            if(!node.latLng.equals(nodeList.get(0).latLng))
            {
                nodeList.add(node);
                distance.add(source.getDistance(node));
                visited.add(true);
                parentNodeList.add(num);
                num = 1;
            }

//        if(!(source.getDistance(destination) < source.getDistance(nearDest)))
//        {
            while(!node.latLng.equals(nearDest.latLng))
            {
                //Log.d("Node", "maproute: next node "+node.latLng.toString());
                for(int i=0;i<node.childNodes.size();i++)
                {
                    if(!nodeList.contains(node.childNodes.get(i)))
                    {
                        nodeList.add(node.childNodes.get(i));
                        distance.add(distance.get(num)+node.getDistance(node.childNodes.get(i)));
                        visited.add(false);
                        parentNodeList.add(num);
                      //  Log.i("initial : ","Latlong "+node.childNodes.get(i).latLng+i+" parent Node "+num);
                    }
                    else
                    {
                        if(distance.get(nodeList.indexOf(node.childNodes.get(i)))>(distance.get(num)+node.getDistance(node.childNodes.get(i))))
                        {
                            int index = nodeList.indexOf(node.childNodes.get(i));
                            distance.set(nodeList.indexOf(node.childNodes.get(i)),distance.get(num)+node.getDistance(node.childNodes.get(i)));
                            parentNodeList.set(index,num);
                         //   Log.i("update : ","Latlong "+node.childNodes.get(i).latLng+i+" parent Node "+num);
                        }
                    }
                }

                num = minDistance(distance,visited);
                node = nodeList.get(num);
                visited.set(num,true);
            }

   //     }

        if(!nearDest.latLng.equals(destination.latLng))
        {
            nodeList.add(destination);
            parentNodeList.add(num);
            num = nodeList.size()-1;
        }
//
//        for(int i=0;i<nodeList.size()-1;i++)
//        {
//            Log.i("ROuting array : ",i + "     "+ nodeList.get(i).latLng+"     "+parentNodeList.get(i)+"     "+distance.get(i));
//        }

        try
        {
            route = mapConnectRoute(nodeList,parentNodeList,num);
        }catch(RuntimeException expectedException) {
            Log.e("Routing Exception",expectedException.getMessage());
            route.add(source.latLng);
        }

        return route;
    }

    public ArrayList<LatLng> mapConnectRoute(ArrayList<mapNode> nodeList, ArrayList<Integer> parentList,int num)
    {
        ArrayList route = new ArrayList();

        if((nodeList.size()==0) || (parentList.size()==0) || (num<0)) return route;
        while(num!=0)
        {
            if(num>=nodeList.size())
            {
                throw new RuntimeException("Invalid Routing");
            }
            route.add(nodeList.get(num).latLng);
            num = parentList.get(num);
        }
        route.add(nodeList.get(num).latLng);
        return route;
    }

    public mapNode nearestCheckpoints(mapNode val1,mapNode val2)
    {
        int index = -1;
        double min = Double.MAX_VALUE;

        for(int i=0;i<v.size();i++)
        {
//            Changing min > v.get(i).getDistance(val1)

            if(min > (v.get(i).getDistance(val1)))
            {
                if(v.get(i).getDistance(val2) <= val2.getDistance(val1))

                {  min = v.get(i).getDistance(val1);
                    index = i;
                    Log.i("nearest Check point",i+"");
                }
            }
        }
        if(index == -1)
            return val2;
        return v.get(index);
    }

    public int minDistance(ArrayList<Double> distance,ArrayList<Boolean> visited)
    {
        double min = Double.MAX_VALUE;
        int index = -1;
        for(int i=0;i<distance.size();i++)
        {
            if((min > distance.get(i)) && (visited.get(i)==false))
            {
                min = distance.get(i);
                index = i;
            }

        }
        return index;
    }

}
