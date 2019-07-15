package siwy.chat;

import java.net.InetAddress;

public class ServerClient 
{
	
	public String name;
	public InetAddress address;
	public int port;
	private final int ID;
	public int attempt = 0;
	

	public ServerClient(String name, InetAddress address, int port, final int ID)
	{
		this.name = name;
		this.address = address;
		this.port = port;
		this.ID = ID;
		
		//StringBuilder my_string = new StringBuilder(name);
		
//		for(int i = 0; i < my_string.length(); ++i)
//		{
//			if(my_string.charAt(i) == ' ')
//			{
//				my_string.
//			}
//		}
		//System.out.println("Size: " +my_string);
		//this.name = my_string.toString();
		if(name.length() > 40)
		{
			name = name.substring(3, 40);
		}
	}
	
	public int Get_ID()
	{
		return ID;
	}
}