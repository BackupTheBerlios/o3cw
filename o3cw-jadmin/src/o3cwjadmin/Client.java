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
    private java.net.Socket sock;
    private int body_len=0;
    boolean reading_head=true;
    String body = new String();
    java.util.Queue<Command> commands=new java.util.LinkedList<Command>();
    
    int Send(byte [] data, int data_size)
    {
        try
        {
            System.out.println("Sending " + data_size + " bytes");
            java.io.OutputStream stream = sock.getOutputStream();
            String s=new String();
            s="HEAD\nlength="+data_size+"\n\n";
            stream.write(s.getBytes());
            stream.write(data, 0, data_size);
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
    
    int ReceiveCommand()
    {
        int result=0;
        try
        {
            java.io.InputStream stream = sock.getInputStream();
            byte buff[]=new byte[512];
            int new_data_size=stream.available();
            String s=new String();
            int really_read=0;
            while (new_data_size>0)
            {
//                System.out.println("new data aviable="+new_data_size);
                int actually_read=new_data_size;
                if (actually_read>512)
                    actually_read=512;
                /* Some new data aviable -read it */
                if (body_len==0)
                {
                    reading_head=true;
                    really_read=stream.read(buff, 0, actually_read);
                }
                else if (body_len<512)
                    really_read=stream.read(buff, 0, body_len);
                else
                    really_read=stream.read(buff, 0, 512);
                
                String n=new String(buff,0,really_read);

                s=s.concat(n);
                
//                System.out.println("s=["+s+"]");
                
                if (reading_head==true)
                {
                    if (s.indexOf("HEAD")>0)
                    {
 //                       System.out.println("HEAD found!");
                    }

                    int length_begin=s.indexOf("length=");
                    if (length_begin>0)
                    {
                        length_begin+=7;
                        int length_end=s.substring(length_begin).indexOf("\n");
                        if (length_end>0)
                        {
                            length_end+=length_begin;
                            String body_len_str=s.substring(length_begin, length_end);
                            try
                            {
                                body_len=Integer.parseInt(body_len_str);
                            }
                            catch (NumberFormatException nfe)
                            {
                                System.out.println("Wrong length format in package head: "+nfe);
                                body_len=0;
                            }
//                            System.out.println("LENGTH="+body_len);
                            body="";
                        }
                    }
                    int body_begin=s.indexOf("\n\n");
                    if (body_begin>0)
                    {
                        reading_head=false;
                        s=s.substring(body_begin+2);
                    }
                }
                
                if (reading_head==false && s.length()>0)
                {
                    body=body.concat(s);
                    body_len-=s.length();
                    if (body_len==0)
                    {
//                        System.out.println("New body aviable, size="+body.length());
                        result++;
                        Command cmd=new Command();
                        cmd.Parse(body);
                        commands.add(cmd);
                        body="";
                    }
                }
                
                new_data_size=stream.available();
            }
        }
        
        catch (java.io.IOException ioe)
        {
            System.err.println("IOException: " + ioe);
        }
            
        
        return result;
    }
}
