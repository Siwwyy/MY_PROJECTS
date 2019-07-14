package siwy.chat;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;


//CTRL + SHIFT + O -> To delete unused imports


public class Client 
{
	
	
	/*
	 * Connection classes
	 * VERY IMPORTANT
	 */
	private String username ,address;
	private int port;

	private DatagramSocket socket;
	private InetAddress ip;	//IP Address
	private Thread send_thread; //Thread for sending
	private int ID = -1;
	
	///////////////////////////////////////////////////////////////////////
	
	
	public Client(String name, String address, int port) 
	{
		this.username = name;
		this.address = address;
		this.port = port;
	}
	
	
	public boolean Open_Connection(String Address)
	{
		try 
		{
			socket = new DatagramSocket();
			ip = InetAddress.getByName(Address);
		} 
		catch (UnknownHostException e) 
		{
			e.printStackTrace();
			return false;
		} 
		catch (SocketException e) 
		{
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
	
	public String Receive()
	{
		byte[] data = new byte[1024];
		DatagramPacket packet = new DatagramPacket(data,data.length);
		
		try 
		{
			socket.receive(packet);
		} 
		catch (IOException e)
		{
			e.printStackTrace();
		}
		String message = new String(packet.getData());
		return message;
	}
	
	
	public void Send(final byte[] data)
	{
		send_thread = new Thread("send")
		{
			public void run()
			{
				DatagramPacket packet = new DatagramPacket(data,data.length, ip, port);
				try 
				{
					socket.send(packet);
				} 
				catch (IOException e) 
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		};
		send_thread.start();
	}
	
	
	public void Set_ID(int ID)
	{
		this.ID = ID;
	}
	
	
	public String Get_Name()
	{
		return this.username;
	}
	
	
	public String Get_Address()
	{
		return this.address;
	}
	
	
	public int Get_Port()
	{
		return this.port;
	}
	
	public int Get_ID()
	{
		return this.ID;
	}
}