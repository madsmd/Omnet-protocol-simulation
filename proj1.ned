simple Tic
{
    parameters:
        @display("i=block/routing");
        int size;
    gates:
        input in;
        output out;
}

simple Toc
{
    parameters:
        @display("i=block/process");
        int limit;
        bool error;
    gates:
        input in;
        output out;
}


network Proj1
{
    @display("bgb=619,274");
    submodules:
        tic: Tic {
            parameters:
                @display("i=,cyan;p=28,148");

        }
        toc: Toc {
            parameters:
                @display("i=,gold;p=259,148");
        }
    connections:
        tic.out --> {  delay = 150ms; datarate = 10Mbps; } --> toc.in;
        tic.in <-- {  delay = 150ms; datarate = 10Mbps; } <-- toc.out;
}
