simple Tx
{
    parameters:
        @display("i=block/routing");
        volatile double iaTime @unit(s);   // packet interarrival time

    gates:
        //input in;
        output out;
}
simple Shaper
{
    parameters:
        @display("i=block/process");


    gates:
        input in;
        output out;
}
simple Rx
{
    parameters:
        @display("i=block/process");
    gates:
        input in;
        //output out;
}


network Proj2
{
    submodules:
        tx: Tx {
            parameters:
                @display("i=block/tx,cyan;p=28,148");

        }
        shaper: Shaper {
            parameters:
                @display("i=block/bucket,blue;p=143,148");
        }
        rx: Rx {
            parameters:
                @display("i=block/rx,gold;p=259,148");
        }
        
    connections:
        tx.out --> {  delay = 500ms; datarate = 10Mbps; } --> shaper.in;
        rx.in <-- {  delay = 500ms; datarate = 10Mbps; } <-- shaper.out;
}
