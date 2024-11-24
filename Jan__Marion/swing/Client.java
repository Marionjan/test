/**
 * @file Client.java
 * @brief Client Java program to communicate with the C++ server.
 * 
 * This class establishes a connection to a C++ server, sends requests, 
 * and handles responses. It reads user input from the terminal, sends 
 * requests to the server, and displays the server's responses.
 * 
 * @author Eric Lecolinet
 * @version 1.0
 * @date 2015
 */

 import java.io.*;
 import java.net.*;
 
 /**
  * This class represents a simple client that communicates with a server.
  * It connects to a server, sends requests, and receives responses.
  */
  /**
  * @class Client
  * @brief Represents a client that communicates with a server.
  */
 public class Client {
   private static final long serialVersionUID = 1L;
   static final String DEFAULT_HOST = "localhost";
   static final int DEFAULT_PORT = 3331;
   private Socket sock;
   private BufferedReader input;
   private BufferedWriter output;
 
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
   /**
    * Main method that connects to the server and handles communication.
    * It continuously prompts the user for a request, sends it to the server,
    * and displays the response.
    *
    * @param argv Command line arguments for the host and port.
    */
   public static void main(String argv[]) {
     String host = DEFAULT_HOST;
     int port = DEFAULT_PORT;
     if (argv.length >= 1) host = argv[0];
     if (argv.length >= 2) port = Integer.parseInt(argv[1]);
     
     Client client = null;
     
     try {
       client = new Client(host, port);
     } catch (Exception e) {
       System.err.println("Client: Couldn't connect to " + host + ":" + port);
       System.exit(1);
     }
     
     System.out.println("Client connected to " + host + ":" + port);
 
     // Create a BufferedReader to read from the console
     BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));
     
     while (true) {
       System.out.print("Request: ");
       try {
         String request = cin.readLine();
         String response = client.send(request);
         System.out.println("Response: " + response);
       } catch (java.io.IOException e) {
         System.err.println("Client: IO error");
         return;
       }
     }
   }
 
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
   /**
    * Initializes the client by establishing a connection to the server.
    * 
    * @param host The server's host address.
    * @param port The server's port number.
    * @throws UnknownHostException If the host cannot be resolved.
    * @throws IOException If an I/O error occurs while opening the socket or streams.
    */
   public Client(String host, int port) throws UnknownHostException, IOException {
     try {
       sock = new java.net.Socket(host, port);
     } catch (java.net.UnknownHostException e) {
       System.err.println("Client: Couldn't find host " + host + ":" + port);
       throw e;
     } catch (java.io.IOException e) {
       System.err.println("Client: Couldn't reach host " + host + ":" + port);
       throw e;
     }
     
     try {
       input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
       output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
     } catch (java.io.IOException e) {
       System.err.println("Client: Couldn't open input or output streams");
       throw e;
     }
   }
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
   /**
    * Sends a request to the server and returns the server's response.
    * This method blocks if the server does not respond.
    * 
    * @param request The request string to be sent to the server.
    * @return The response from the server, or null if an error occurs.
    */
   public String send(String request) {
     // Send the request to the server
     try {
       request += "\n";  // Add line separator
       output.write(request, 0, request.length());
       output.flush();
     } catch (java.io.IOException e) {
       System.err.println("Client: Couldn't send message: " + e);
       return null;
     }
     
     // Receive the result from the server
     try {
       return input.readLine();
     } catch (java.io.IOException e) {
       System.err.println("Client: Couldn't receive message: " + e);
       return null;
     }
   }
 }
 