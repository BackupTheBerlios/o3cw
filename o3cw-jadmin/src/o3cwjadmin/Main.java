/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package o3cwjadmin;

/**
 *
 * @author alex
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        int total_size=0;
        // TODO code application logic here
        
        Client clnt=new Client();
        
        if (clnt.Connect("127.0.0.1", 25005)==false)
        {
            System.out.println("Connection failed.");
            return;
        }
        
        java.util.Scanner in = new java.util.Scanner(System.in);
        String instr="";
        java.util.Queue<String> tosend=new java.util.LinkedList<String>();

        while (instr.equals("\\q")==false)
        {
            instr=in.nextLine();
            if (instr.length()==0)
            {
                System.out.println("Send!");
                int send_len=total_size+tosend.size()*4;
                byte [] send_buff= new byte[send_len];
                
                java.nio.ByteBuffer bbuffer = java.nio.ByteBuffer.wrap(send_buff);
                bbuffer.order(java.nio.ByteOrder.LITTLE_ENDIAN);
                
                while (tosend.size()>0)
                {
                    String a = (String) tosend.poll();
                    
                    bbuffer.putInt(a.length());
                    System.out.println("bytebuff size is "+bbuffer.position() +" now");
                    bbuffer.put(a.getBytes());
                    System.out.println("bytebuff size is "+bbuffer.position() +" now");
                }

                clnt.Send(send_buff, send_len);
                //tosend="";
                total_size=0;
            }
            else
            {
                
                tosend.offer(new String(instr));
                total_size+=instr.length();
            }
        }
        
    }

}
