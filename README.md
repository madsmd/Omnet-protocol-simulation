# Omnet-protocol-simulation
Simulating Go-Back-N protocol and a Traffic Shapper on Omnett++

Go-Back-N protocol: 
The objective of this project is to model, simulate, and analyze the Go-Back-N protocol. Go-Back-N protocol is based on sliding window flow control method.

At the start of the simulation, the TIC(source) should send a control message to TOC(destination) providing its window size and type of the message, which is configured in the TOC. The window size is set at the time of initialization via the omnetpp.ini file. The TOC then replies to the query from TIC confirming the window size.

The query_reply message from TOC (indicating the Window size) should be used as a trigger by TIC to start sending the frames/packets. The TOC should then send a Receive Ready (i.e., RR message) or Receive Not Ready (RNR) message in case it receives or not receives frames transmitted from TIC.

The simulation model should be able to correctly demonstrate the operation of the Go Back N flow control mechanism in case of
1. No packet loss or errors.
2. In case of packet loss or errors.


Token-bucket-algorithm
The objective of this project is to model, simulate, and analyze token bucket algorithm using omnet++. 
Station-A(Source) is sending packets towards Station-B(sink) via the Traffic Shaper. The traffic from Station-A is randomly generated following Poisson distribution. That is, the inter-arrival time between packets is Poisson distributed and hence is of variable packet rate. The traffic shaper will queue the incoming packets from A and then “schedule” them at a constant bit rate towards Station-B. Thus the traffic between Station A and the Traffic Shaper is VBR(Variable Bit Rate), while between the Traffic Shaper and Station-B is CBR(Constant Bit Rate). The traffic Shaper must be based on token bucket algorithm.

The queue inside the Traffic Shaper should be a FIFO queue with a fixed size and constant service time. Set the output rate of the Traffic Shaper to some constant value x pps (packets per second) while experiment with
1. Different mean inter-arrival times from Station-A towards the Traffic Shaper.
2. Different size of the token bucket (β) to control maximum burst size
3. Different token rates (p)
