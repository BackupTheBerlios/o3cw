/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package o3cwjadmin;

/**
 *
 * @author alex
 */
public class Client
{
    int Send(byte [] data, int data_size)
    {
        try
        {
            System.out.println("Sending " + data_size + " bytes");
            java.io.OutputStream stream = sock.getOutputStream();
            String s=new String();
            s="HEAD\nlength="+data_size+"\n\n";
            stream.write(s.getBytes());
            stream.write(data);
            stream.flush();
        }
        catch (java.io.IOException ioe)
        {
            System.err.println("IOException: " + ioe);
        }
        
        return 0;
    }
    boolean Connect(String host, int port)
    {
        boolean result=false;
        try
        {
            sock = new java.net.Socket(host, port);
            result=true;
        }
        catch (java.net.UnknownHostException uhe)
        {
            System.out.println("UnknownHostException: " + uhe);
        }
        catch (java.io.IOException ioe)
        {
            System.err.println("IOException: " + ioe);
        }
        return result;
    }
    private java.net.Socket sock;
}
