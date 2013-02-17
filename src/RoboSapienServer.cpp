/*
 * RoboSapienServer.cpp
 *  http://playground.arduino.cc//Main/RoboSapienServer
 */

#include "RoboSapienServer.h"

//// Include files
//#include <Ethernet.h>
//#include <string.h>
//
////////////////////////////////////////////////////////////////////
//// Begin Web Server specific variable deinitions
////////////////////////////////////////////////////////////////////
//
//char mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//
//// KNH, 02/09/2010 - Change IP address to use local subnet at home
////byte ip[] = { 10, 0, 0, 177 };
//char ip[] = { 192, 168, 1, 177 };
//
//// Server for web requests
//Server server(80);
//
//// Define field name in the submitted form
//#define SUBMIT_BUTTON_FIELDNAME "RSCmd"
//
//// String for HTTP request variables
//char pcHttpReqRsCmd[20] = {'\0'};
//
//
//volatile int viRobsapienUrlCmd = -1;  // A robosapien command sent over the URL of a webpage HTTP request

RoboSapienServer::RoboSapienServer() {
	// TODO Auto-generated constructor stub

}

RoboSapienServer::~RoboSapienServer() {
	// TODO Auto-generated destructor stub
}
//
//// Loop for RoboSapien functionality
//// Write only functionality - send the command from the web page to the robot, ignoring any input from the remote
//void RSLoop()
//{
//  // Has a new command come in from the server?
//  if(viRobsapienUrlCmd != -1)
//    {
//    // New command - send it to robot
//    Serial.print("Sending command to RoboSapien: ");
//    Serial.println(viRobsapienUrlCmd, HEX);
//    RSSendCommand(viRobsapienUrlCmd);
//
//    // Now clear command
//    viRobsapienUrlCmd = -1;
//    }
//}
//
////////////////////////////////////////////////////////////////////
//// Begin Webserver Specific Code
////////////////////////////////////////////////////////////////////
//
//// Print ourt MIME and HTML header at top of webpage
//void HtmlHeader(Client client)
//  {
//  client.println("HTTP/1.1 200 OK");
//  client.println("Content-Type: text/html");
//  client.println();
//  client.println("<HTML>\n<HEAD>");
//  client.println("  <TITLE>Kevin's Arduino Webserver</TITLE>");//
////  client.println("  <META HTTP-EQUIV=\"refresh\" CONTENT=\"5\">");
//  client.println("</HEAD><BODY bgcolor=\"#9bbad6\">");
//  }
//
//// Print the footer at the bottom of the webpage
//void HtmlFooter(Client client)
//  {
//  client.println("</BODY></HTML>");
//  }
//
//// Print a submit button with the indicated label wrapped in a form for the indicated hex command
//void SubmitButton(Client &client, char *pcLabel, int iCmd)
//  {
//  client.print("<form method=post action=\"/?");
//  client.print(iCmd, HEX);
//  client.print("\"><input type=submit value=\"");
//  client.print(pcLabel);
//  client.print("\" name=\"" SUBMIT_BUTTON_FIELDNAME "\">");
//  client.println("</form>");
//  }
//
//// Parse an HTTP request header one character at a time, seeking string variables
//void ParseHttpHeader(Client &client)
//  {
//  char c;
//
//  // Skip through until we hit a question mark (first one)
//  while((c = client.read()) != '?' && client.available())
//    {
//    // Debug - print data
//    Serial.print(c);
//    }
//
//  // Are we here for a question mark or did we run out of data?
//  if(client.available() > 2)
//    {
//    char pcUrlNum[3], *pc;
//
//    // We have enough data for a hex number - read it
//    for(int i=0; i < 2; i++)
//      {
//      // Read and dump data to debug port
//      Serial.print(c = pcUrlNum[i] = client.read());
//      }
//    // Null terminate string
//    pcUrlNum[2] = '\0';
//
//    // Get hex number
//    viRobsapienUrlCmd = strtol(pcUrlNum, &pc, 0x10);
//    }
//
//  // Skip through and discard all remaining data
//  while(client.available())
//    {
//    // Debug - print data
//    Serial.print(c = client.read());
//    }
//  }
//
//// Set up webserver functionality
//void WebServerSetup()
//{
//  Ethernet.begin(mac, ip);
//  server.begin();
//}
//
//// Web server loop
//void WebServerLoop()
//{
//  Client client = server.available();
//  boolean bPendingHttpResponse = false; // True when we've received a whole HTTP request and need to output the webpage
//  char c;  // For reading in HTTP request one character at a time
//
//  if (client) {
//    // Loop as long as there's a connection
//    while (client.connected()) {
//      // Do we have pending data (an HTTP request)?
//      if (client.available()) {
//
//        // Indicate we need to respond to the HTTP request as soon as we're done processing it
//        bPendingHttpResponse = true;
//
//        ParseHttpHeader(client);
//        }
//      else
//        {
//        // There's no data waiting to be read in on the client socket.  Do we have a pending HTTP request?
//        if(bPendingHttpResponse)
//          {
//          // Yes, we have a pending request.  Clear the flag and then send the webpage to the client
//          bPendingHttpResponse = false;
//
//          // send a standard http response header and HTML header
//          HtmlHeader(client);
//
//          // Put out a text header
//          client.println("<H1>Kevin's RoboSapien Webserver</H1>");
//
//          client.println("<table border cellspacing=0 cellpadding=5><tr>");
//          client.println("<td>");
//
//          // Create buttons
//          SubmitButton(client, "WakeUp", RSWakeUp);
//          SubmitButton(client, "Roar", RSRoar);
//          SubmitButton(client, "Whistle", RSWhistle);
//          SubmitButton(client, "High5", RSHigh5);
//          client.println("<br>");
//
//          client.println("</td><td>");
//
//          SubmitButton(client, "LeftArmUp", RSLeftArmUp);
//          SubmitButton(client, "LeftArmIn", RSLeftArmIn);
//          SubmitButton(client, "LeftArmOut", RSLeftArmOut);
//          SubmitButton(client, "LeftArmDown", RSLeftArmDown);
//          SubmitButton(client, "LeftArmSweep", RSLeftHandSweep);
//          client.println("<br>");
//
//          client.println("</td><td>");
//
//          SubmitButton(client, "RightArmUp", RSRightArmUp);
//          SubmitButton(client, "RightArmIn", RSRightArmIn);
//          SubmitButton(client, "RightArmOut", RSRightArmOut);
//          SubmitButton(client, "RightArmDown", RSRightArmDown);
//          SubmitButton(client, "RightArmSweep", RSRightHandSweep);
//          client.println("<br>");
//
//          client.println("</td></tr></table>");
//
//          client.print("<br><br><br>URL Hex no: ");
//          client.print(viRobsapienUrlCmd, HEX);
//          client.println("<br />");
//
//          // send HTML footer
//          HtmlFooter(client);
//
//          // give the web browser time to receive the data
//          delay(1);
//          client.stop();
//          }
//        }
//      }  // End while(connected)
//  }
//}
//
////////////////////////////////////////////////////////////////////
//// Begin arduino entry points
////////////////////////////////////////////////////////////////////
//
//void setup()
//{
//  // open the serial port at 9600 bps:
//  Serial.begin(9600);
//
//  // Print greeting
//  Serial.println("Kevin's RobSapien Server");
//
//  RSSetup();
//  WebServerSetup();
//}
//
//void loop()
//{
//  RSLoop();
//  WebServerLoop();
//}
