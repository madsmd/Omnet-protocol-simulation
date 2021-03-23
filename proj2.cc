/*
 * proj2.cc
 * simulate token bucket algo
 *  Created on: Sep-2019
 *      Author: Mahesh M D
 */

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

#include "tictoc_m.h"

class Tx : public cSimpleModule
{
  private:
    Tictoc *msg1;
    Tictoc *nxtmsgEvent; //holds pointer to the timeout self-message of the next Message (data rate)
    int seq;
    cPar *iaTime;

    cOutVector VBR;

  protected:
    virtual Tictoc *generateNewMessage(int flag);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Tx);

void Tx::initialize()
{
    seq=0;
    iaTime = &par("iaTime");

    nxtmsgEvent = generateNewMessage(1);
    scheduleAt(simTime()+.1, nxtmsgEvent);

}
void Tx::handleMessage(cMessage *msg)
{
    Tictoc *ttmsg = check_and_cast<Tictoc *>(msg);

    if(ttmsg->getMsgType() == 1)
    {
        msg1 =  generateNewMessage(2);
        send(msg1,"out");
        VBR.record(seq);

        if(seq==15)
                    for (int i=0;i<15;i++)
                    {
                    msg1 =  generateNewMessage(2);
                            send(msg1,"out");
                            VBR.record(seq);

                    }
        scheduleAt(simTime()+iaTime->doubleValue(), nxtmsgEvent);
        //VBR.record(iaTime->doubleValue());
    }
}

Tictoc *Tx::generateNewMessage(int flag)
{
    // Generate a message with a different name every time.
    if(flag == 1)
    {
        char msgname[20];
        sprintf(msgname, "next message event");

        Tictoc *msg = new Tictoc(msgname);
        msg->setSeqNo(0);
        msg->setMsgType(1);
        return msg;
    }
    if(flag == 2)
    {
        char msgname[20];
        sprintf(msgname, "msg-%d", ++seq);

        Tictoc *msg = new Tictoc(msgname);
        msg->setSeqNo(seq);
        msg->setMsgType(2);
        return msg;
    }



}



class Shaper : public cSimpleModule
{
  private:
    Tictoc *nxtTokenEvent;
    Tictoc *nxtMsgEvent;
    Tictoc *msg1;
    simtime_t nxtToken;
    cQueue token;
    int TokenLen;

    cQueue Msg;
    int MsgLen;
    simtime_t nxtmsg;


  protected:
    virtual Tictoc *generateNewMessage(int flag);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Shaper);

void Shaper::initialize()
{
    nxtToken = .35;
    nxtmsg = .2;
    TokenLen = 5;
    MsgLen = 10;
    nxtTokenEvent = generateNewMessage(1);
  //  nxtMsgEvent = generateNewMessage(0);
    scheduleAt(simTime() + nxtToken, nxtTokenEvent);
}
void Shaper::handleMessage(cMessage *msg)
{
    Tictoc *ttmsg = check_and_cast<Tictoc *>(msg);

    if(ttmsg->getMsgType() == 1)
    {
        if(token.getLength() < TokenLen)
        {
            token.insert(msg);
            nxtTokenEvent = generateNewMessage(1);
        }

        if(Msg.getLength()>0)
        {
            msg1 =(Tictoc *) Msg.pop();
            send(msg1,"out");


            //delete
            token.pop();
      //      if(Msg.getLength()>0 && token.getLength()>0)
        //        scheduleAt(simTime() + nxtmsg, nxtMsgEvent);
        }
        nxtTokenEvent = generateNewMessage(1);
        scheduleAt(simTime() + nxtToken, nxtTokenEvent);
    }


    if(ttmsg->getMsgType() == 2)
    {
        if(Msg.getLength() < MsgLen)
            Msg.insert(msg);
        //else
          //  delete msg;

        if(token.getLength()>0)
        {
            msg1 =(Tictoc *) Msg.pop();
            send(msg1,"out");

            //delete
            token.pop();
 //           if(Msg.getLength()>0 && token.getLength()>0)
   //             scheduleAt(simTime() + nxtmsg, nxtMsgEvent);
        }
    }

//    if(ttmsg->getMsgType() == 0)
//    {
//        if(Msg.getLength()>0 && token.getLength()>0)
//        {
//            msg1 =(Tictoc *) Msg.pop();
//            send(msg1,"out");
//           // delete
//            token.pop();
//            if(Msg.getLength()>0 && token.getLength()>0)
//                scheduleAt(simTime() + nxtmsg, nxtMsgEvent);
//        }
//    }

}

Tictoc *Shaper::generateNewMessage(int flag)
{
    if(flag == 1)
    {
        char msgname[20];
        sprintf(msgname, "next Token event");

        Tictoc *msg = new Tictoc(msgname);
        msg->setSeqNo(0);
        msg->setMsgType(1);
        return msg;
    }
    /*if(flag == 0)
        {
            char msgname[20];
            sprintf(msgname, "next msg event");

            Tictoc *msg = new Tictoc(msgname);
            msg->setSeqNo(0);
            msg->setMsgType(0);
            return msg;
        }*/
}

class Rx : public cSimpleModule
{
private:
    cOutVector CBR;
    int seq;
protected:
    virtual void handleMessage(cMessage *msg) override;

};

Define_Module(Rx);
void Rx::handleMessage(cMessage *msg)
{
    Tictoc *ttmsg = check_and_cast<Tictoc *>(msg);
    seq = ttmsg->getSeqNo();
    CBR.record(seq);
}
