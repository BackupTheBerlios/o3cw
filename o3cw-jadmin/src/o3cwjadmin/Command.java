/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package o3cwjadmin;

/**
 *
 * @author alex
 */
public class Command
{
    private java.util.Queue<String> cmds=new java.util.LinkedList<String>();
    
    boolean CmdAviable()
    {
        if (cmds.size()>0)
            return true;
        return false;
    }
    
    String Pop()
    {
        String result=null;
        if (cmds.size()>0)
            result=cmds.poll();
        return result;
    }
    
    int Parse(String data)
    {
//        System.out.println("Parsing...[" +data+"]");
        int result=0;
        java.nio.ByteBuffer bbuffer = java.nio.ByteBuffer.wrap(data.getBytes());
        bbuffer.order(java.nio.ByteOrder.LITTLE_ENDIAN);
        
        boolean stop=false;
        
        while (bbuffer.hasRemaining()==true && stop==false)
        {
            if (bbuffer.remaining()>=4)
            {
                int l=bbuffer.getInt();
                if (l>0)
                {
                    byte b[]=new byte[l];
                    
                    if (bbuffer.remaining()>=l)
                        bbuffer.get(b,0,l);
                    else
                        stop=true;
                    
                    cmds.offer(new String(b));
                }
            }
            else
                stop=true;
        }
        return result;
    }
}
