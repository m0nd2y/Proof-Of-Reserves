//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package inet.showcases.measurement.residencetime;

import inet.networks.base.WiredNetworkBase;
import inet.node.eigrp.EigrpRouter;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;
import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;

network ResidenceTimeMeasurementShowcase extends WiredNetworkBase
{
    submodules:
        server: StandardHost {
            @display("p=200,225");
        }
        switch0: EthernetSwitch {
            @display("p=250,225");
        }
        Router_T0: Router {
            @display("p=300,225");
        }
        Router_T1: Router {
            @display("p=350,225");
        }
        Router_T2: Router {
            @display("p=400,225");
        }
        Router_T3: Router {
            @display("p=450,225");
        }
        Router_T4: Router {
            @display("p=500,225");
        }
        Router_T5: Router {
            @display("p=550,225");
        }
        RouterS: Router {
            @display("p=800,225");
        }
        RouterP: Router {
            @display("p=850,125");
        }
        RouterQ: Router {
            @display("p=850,325");
        }
        RouterA: Router {
            @display("p=900,75");
        }
        RouterB: Router {
            @display("p=900,175");
        }
        RouterC: Router {
            @display("p=900,275");
        }
        RouterD: Router {
            @display("p=900,375");
        }
        Router1: Router {
            @display("p=950,50");
        }
        Router2: Router {
            @display("p=950,100");
        }
        Router3: Router {
            @display("p=950,150");
        }
        Router4: Router {
            @display("p=950,200");
        }
        Router5: Router {
            @display("p=950,250");
        }
        Router6: Router {
            @display("p=950,300");
        }
        Router7: Router {
            @display("p=950,350");
        }
        Router8: Router {
            @display("p=950,400");
        }
        switch1: EthernetSwitch {
            @display("p=1050,50");
        }
        switch2: EthernetSwitch {
            @display("p=1050,100");
        }
        switch3: EthernetSwitch {
            @display("p=1050,150");
        }
        switch4: EthernetSwitch {
            @display("p=1050,200");
        }
        switch5: EthernetSwitch {
            @display("p=1050,250");
        }
        switch6: EthernetSwitch {
            @display("p=1050,300");
        }
        switch7: EthernetSwitch {
            @display("p=1050,350");
        }
        switch8: EthernetSwitch {
            @display("p=1050,400");
        }
        destination1: StandardHost {
            @display("p=1200,50");
        }
        destination2: StandardHost {
            @display("p=1200,100");
        }
        destination3: StandardHost {
            @display("p=1200,150");
        }
        destination4: StandardHost {
            @display("p=1200,200");
        }
        destination5: StandardHost {
            @display("p=1200,250");
        }
        destination6: StandardHost {
            @display("p=1200,300");
        }
        destination7: StandardHost {
            @display("p=1200,350");
        }
        destination8: StandardHost {
            @display("p=1200,400");
        }
    connections:
        server.ethg++ <--> Eth1G <--> switch0.ethg++;
        switch0.ethg++ <--> Eth1G <--> Router_T0.ethg++;
        
        Router_T0.ethg++ <--> Eth1G <--> Router_T1.ethg++;
        Router_T1.ethg++ <--> Eth1G <--> Router_T2.ethg++;
        Router_T2.ethg++ <--> Eth1G <--> Router_T3.ethg++;
        Router_T3.ethg++ <--> Eth1G <--> Router_T4.ethg++;
        Router_T4.ethg++ <--> Eth1G <--> Router_T5.ethg++;
        Router_T5.ethg++ <--> Eth1G <--> RouterS.ethg++;
        
        RouterS.ethg++ <--> Eth1G <--> RouterQ.ethg++;
        RouterS.ethg++ <--> Eth1G <--> RouterP.ethg++;
        
        RouterP.ethg++ <--> Eth1G <--> RouterA.ethg++;
        RouterP.ethg++ <--> Eth1G <--> RouterB.ethg++;
        RouterQ.ethg++ <--> Eth1G <--> RouterC.ethg++;
        RouterQ.ethg++ <--> Eth1G <--> RouterD.ethg++;
        
        RouterA.ethg++ <--> Eth1G <--> Router1.ethg++;
        RouterA.ethg++ <--> Eth1G <--> Router2.ethg++;
        RouterB.ethg++ <--> Eth1G <--> Router3.ethg++;
        RouterB.ethg++ <--> Eth1G <--> Router4.ethg++;
        RouterC.ethg++ <--> Eth1G <--> Router5.ethg++;
        RouterC.ethg++ <--> Eth1G <--> Router6.ethg++;
        RouterD.ethg++ <--> Eth1G <--> Router7.ethg++;
        RouterD.ethg++ <--> Eth1G <--> Router8.ethg++;
        Router1.ethg++ <--> Eth1G <--> switch1.ethg++;
        Router2.ethg++ <--> Eth1G <--> switch2.ethg++;
        Router3.ethg++ <--> Eth1G <--> switch3.ethg++;
        Router4.ethg++ <--> Eth1G <--> switch4.ethg++;
        Router5.ethg++ <--> Eth1G <--> switch5.ethg++;
        Router6.ethg++ <--> Eth1G <--> switch6.ethg++;
        Router7.ethg++ <--> Eth1G <--> switch7.ethg++;
        Router8.ethg++ <--> Eth1G <--> switch8.ethg++;
        
        switch1.ethg++ <--> Eth1G <--> destination1.ethg++;
        switch2.ethg++ <--> Eth1G <--> destination2.ethg++;
        switch3.ethg++ <--> Eth1G <--> destination3.ethg++;
        switch4.ethg++ <--> Eth1G <--> destination4.ethg++;
        switch5.ethg++ <--> Eth1G <--> destination5.ethg++;
        switch6.ethg++ <--> Eth1G <--> destination6.ethg++;
        switch7.ethg++ <--> Eth1G <--> destination7.ethg++;
        switch8.ethg++ <--> Eth1G <--> destination8.ethg++;
}