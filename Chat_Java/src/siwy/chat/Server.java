package siwy.chat;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Server implements Runnable
{
	private List<ServerClient> Clients_List = new ArrayList<ServerClient>();
	
	private int port;
	private DatagramSocket socket;
	private Thread run_thread, manage_thread, send_thread, receive_thread;
	private boolean running = false;
	
	public Server(int port)
	{
		this.port = port;
		try 
		{
			socket = new DatagramSocket(port);
		} 
		catch (SocketException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		run_thread = new Thread(this, "Server");
		run_thread.start();
	}

	@Override
	public void run() 
	{
		// TODO Auto-generated method stub
		running = true;
		System.out.println("Server started on port: " + port);
		Manage_Clients();
		Receive();
	}

	private void Receive() 
	{
		// TODO Auto-generated method stub
		receive_thread = new Thread("Manage")
		{
			public void run()
			{
				while(running)
				{
					byte[] data = new byte[1024];
					//Receiving something
					DatagramPacket packet = new DatagramPacket(data, data.length);
					try 
					{
						socket.receive(packet);
						//packet.getPort();
						//packet.getAddress();
					} 
					catch (IOException e) 
					{
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					//String new_string = new String(packet.getData());
					process(packet);
					//Clients_List.add(new ServerClient("Siwy", packet.getAddress(), packet.getPort(), 50));
					//System.out.println(Clients_List.get(0).address.toString() + ":" + Clients_List.get(0).port);
					//System.out.println(new_string);
				}
			}
		};
		receive_thread.start();
	}
	
	
	private void SendToAll(String message)
	{
		for(int i = 0; i < Clients_List.size(); i++)
		{
			ServerClient client = Clients_List.get(i);
			send(message.getBytes(), client.address, client.port);
		}
	}
	
	
	private void send(final byte[] data, final InetAddress address, final int port)
	{
		send_thread = new Thread("Send")
		{
			public void run()
			{
				DatagramPacket packet = new DatagramPacket(data, data.length, address, port);
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
	
	
	private void Send(String message, InetAddress address, int port)
	{
		message += "/e/";	//terminate, means the end of string message
		send(message.getBytes(), address, port);
	}
	
	
	private void process(DatagramPacket packet)
	{
		String from_packet = new String(packet.getData());
		if(from_packet.startsWith("/c/") == true)	//c means that it is a client
		{
			//int random_value = new Random().nextInt();	//for unique ID 
			//int random_value = new SecureRandom().nextInt();	//for unique ID 
			//UUID id = UUID.randomUUID();
			//id.
			//int random_value = new SecureRandom().nextInt();	//for unique ID 
			int id = UniqueIdentifier.Get_Identifier();
			System.out.println("Identifier: " + id);
			//Clients_List.add(new ServerClient(from_packet.substring(3,from_packet.length()), packet.getAddress(), packet.getPort(), random_value));
			//Clients_List.add(new ServerClient(from_packet.substring(3,from_packet.length()), packet.getAddress(), packet.getPort(), Integer.parseInt(id.toString())));
			Clients_List.add(new ServerClient(from_packet.substring(3,from_packet.length()), packet.getAddress(), packet.getPort(), id));
			System.out.println(from_packet.substring(3,from_packet.length()));
			String ID = "/c/" + id;
			Send(ID,packet.getAddress(),packet.getPort());
		}
		else if(from_packet.startsWith("/m/") == true)
		{
			//String message = from_packet.substring(3,from_packet.length());
			SendToAll(from_packet);
		}
		else if(from_packet.startsWith("/d/") == true)
		{
			String ID = from_packet.split("/d/|/e/")[1];
			System.out.println("in /d/ here");
			Disconnect(Integer.parseInt(ID),true);
		}
		else
		{
			System.out.println(from_packet);
		}
		System.out.println(from_packet);
	}
	
	
	private void Disconnect(int ID, boolean status)
	{
		ServerClient c = null;
		for(int i = 0; i < Clients_List.size(); ++i)
		{
			if(Clients_List.get(i).Get_ID() == ID)
			{
				c = Clients_List.get(i);
				Clients_List.remove(i);
				break;
			}
		}
		
		String message = "";
		if(status == true)
		{
			message = "Client: " + c.name + " ( " + c.Get_ID() + " ) @ " + c.address.toString() + " Port: " + c.port + " disconnected! \n";
		}
		else
		{
			message = "Client: " + c.name + " ( " + c.Get_ID() + " ) @ " + c.address.toString() + " Port: " + c.port + " timed out! \n";
		}
		System.out.println(message);
	}
	
	
	private void Manage_Clients() 
	{
		// TODO Auto-generated method stub
		manage_thread = new Thread("Manage")
		{
			public void run()
			{
				while(running)
				{
					//Managing something
				}
			}
		};
		manage_thread.start();
	}
}